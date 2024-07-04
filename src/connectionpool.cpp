#include "connectionpool.hpp"
#include "public.hpp"

ConnectionPool::ConnectionPool(){
    // 创建初始连接
    for(int i = 0; i < _initSize; i++){
        Connection* conn = new Connection();
        conn->connect(_ip, _user, _password, _dbname);
        conn->refAliveTime();
        _connQue.push(conn);
        _connCnt++;
    }
    // 创建并启动生产连接的线程
    thread produce(bind(&ConnectionPool::produceConnTask, this));
    produce.detach();
    // 创建并启动回收多余空闲连接的线程
    thread scan(bind(&ConnectionPool::scanConnTask, this));
    scan.detach();
}

ConnectionPool* ConnectionPool::getInstance(){
    // 通过创建静态局部对象实现线程安全
    static ConnectionPool pool;
    return &pool;
}

shared_ptr<Connection> ConnectionPool::getConnction(){
    // 对连接队列加锁
    unique_lock<mutex> lock(_queMutex);
    // 如果队列为空则消费者释放锁并等待生产者通知队列不为空
    while(_connQue.empty()){
        // 如果是超时造成的解除等待则返回空指针
        if(cv_status::timeout == cv.wait_for(lock, chrono::seconds(_connTimeout))){
            LOG("get mysql connection timeout...");
            return nullptr;
        }
    }
    // 自定义智能指针的析构函数, 使得创建的connection资源不会被回收, 而是重新push到队列中
    shared_ptr<Connection> conn(_connQue.front(), [&](Connection* ptrconn){
        unique_lock<mutex> lock(_queMutex);
        ptrconn->refAliveTime();
        _connQue.push(ptrconn);
    });
    _connQue.pop();
    // cout << "线程池中的线程数为: " << _connQue.size() << endl;
    cv.notify_all();
    return conn;
}

void ConnectionPool::produceConnTask(){
    for(;;){
        // 对连接队列加锁
        unique_lock<mutex> lock(_queMutex);
        // 如果队列不为空则生产者释放锁并等待消费者通知队列为空
        while(!_connQue.empty()){
            cv.wait(lock);
        }
        // 被通知队列为空,判断创建的线程是否到达上限
        if(_maxSize > _connCnt){
            // 如果没有到达上限则创建新的连接
            Connection* conn = new Connection();
            conn->connect(_ip, _user, _password, _dbname);
            conn->refAliveTime();
            _connQue.push(conn);
            _connCnt++;
        }
        // 唤醒因队列为空而解锁等待的消费者线程
        cv.notify_all();
    }
}

void ConnectionPool::scanConnTask(){
    for(;;){
        // 通过线程sleep定时扫描队列
        this_thread::sleep_for(chrono::seconds(_maxIdelTime));
        // 线程苏醒之后抢占队列的互斥锁进行扫描
        unique_lock<mutex> lock(_queMutex);
        while(_connCnt > _initSize){
            // 只需判断队头连接的存活时间
            Connection* p = _connQue.front();
            if(p->getAliveTime() >= _maxIdelTime * 1000){
                _connQue.pop();
                _connCnt--;
                delete p;
            }
            else{
                break;
            }
        }
    }
}