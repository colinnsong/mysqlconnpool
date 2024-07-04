#ifndef CONNECTIONPOOL_H
#define CONNECTIONPOOL_H

#include "connection.hpp"
#include <iostream>
#include <queue>
#include <string>
#include <mutex>
#include <atomic>
#include <memory>
#include <thread>
#include <functional>
#include <condition_variable>
using namespace std;

class ConnectionPool{
public:
    // 获取单例对象的静态接口函数
    static ConnectionPool* getInstance();
    // 给外部提供获取从队列中获取空闲连接的接口
    shared_ptr<Connection> getConnction();

private:
    // 单例设计模式需要将构造函数设置成私有
    ConnectionPool();
    // 运行在连接生产线程中用来创建新连接的函数
    void produceConnTask();
    // 扫描超过maxIdleTime的空闲连接并进行回收
    void scanConnTask();

    // 数据库配置信息
    string _ip = "127.0.0.1";
    string _user = "colin";
    string _password = "123456";
    string _dbname = "connpool";

    // 连接池的初始连接数量
    int _initSize = 10;
    // 连接池的最大连接数量
    int _maxSize = 1024;
    // 连接池的最大空闲时间
    int _maxIdelTime = 1;
    // 获取连接池的超时时间
    int _connTimeout = 10;
    // 记录新创建的连接数量
    atomic_int _connCnt;
    // 存储mysql连接的队列
    queue<Connection*> _connQue;
    // 保证connQue上的线程安全的互斥锁
    mutex _queMutex;
    // 条件变量控制进程同步
    condition_variable cv;
};

#endif