#include "connection.hpp"
#include "connectionpool.hpp"
#include <iostream>
using namespace std;

// 数据库配置信息
string server = "127.0.0.1";
string user = "colin";
string password = "123456";
string dbname = "connpool";
// 连接池配置信息
int initSize = 10;
int maxSize = 1024;
int maxIdelTime = 6; // 秒
int connTimeout = 10; // 秒

int main(){
    clock_t begin = clock();
    // 压力测试1: 单线程单连接循环插入1000条数据
    // clock_t begin = clock();
    // for(int i = 0; i < 1000; i++){
    //     Connection conn;
    //     conn.connect(server, user, password, dbname);
    //     char sql[1024] = {0};
    //     sprintf(sql, "insert into user(name, age, sex) values('zhangsan', 20, 'male')");
    //     conn.update(sql);
    // }
    // clock_t end = clock();
    // cout << (end - begin) << "ms" << endl;
    // return 0;

    // 压力测试2: 单线程连接池循环插入1000条数据
    // ConnectionPool* connpool = ConnectionPool::getInstance();
    // for(int i = 0; i < 100; i++){
    //     shared_ptr<Connection> conn = connpool->getConnction();
    //     char sql[1024] = {0};
    //     sprintf(sql, "insert into user(name, age, sex) values('zhangsan', 20, 'male')");
    //     conn->update(sql);
    // }

    // 压力测试3: 4线程单连接循环插入1000条数据
    // thread t1([](){
    //     for(int i = 0; i < 250; i++){
    //         Connection conn;
    //         conn.connect(server, user, password, dbname);
    //         char sql[1024] = {0};
    //         sprintf(sql, "insert into user(name, age, sex) values('zhangsan', 20, 'male')");
    //         conn.update(sql);
    //     }
    // });
    // thread t2([](){
    //     for(int i = 0; i < 250; i++){
    //         Connection conn;
    //         conn.connect(server, user, password, dbname);
    //         char sql[1024] = {0};
    //         sprintf(sql, "insert into user(name, age, sex) values('zhangsan', 20, 'male')");
    //         conn.update(sql);
    //     }
    // });
    // thread t3([](){
    //     for(int i = 0; i < 250; i++){
    //         Connection conn;
    //         conn.connect(server, user, password, dbname);
    //         char sql[1024] = {0};
    //         sprintf(sql, "insert into user(name, age, sex) values('zhangsan', 20, 'male')");
    //         conn.update(sql);
    //     }
    // });
    // thread t4([](){
    //     for(int i = 0; i < 250; i++){
    //         Connection conn;
    //         conn.connect(server, user, password, dbname);
    //         char sql[1024] = {0};
    //         sprintf(sql, "insert into user(name, age, sex) values('zhangsan', 20, 'male')");
    //         conn.update(sql);
    //     }
    // });
    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();

    // 压力测试4: 4线程连接池循环插入1000条数据
    // thread t1([](){
    //     ConnectionPool* connpool = ConnectionPool::getInstance();
    //     for(int i = 0; i < 250; i++){
    //         shared_ptr<Connection> conn = connpool->getConnction();
    //         char sql[1024] = {0};
    //         sprintf(sql, "insert into user(name, age, sex) values('zhangsan', 20, 'male')");
    //         conn->update(sql);
    //     }
    // });
    // thread t2([](){
    //     ConnectionPool* connpool = ConnectionPool::getInstance();
    //     for(int i = 0; i < 250; i++){
    //         shared_ptr<Connection> conn = connpool->getConnction();
    //         char sql[1024] = {0};
    //         sprintf(sql, "insert into user(name, age, sex) values('zhangsan', 20, 'male')");
    //         conn->update(sql);
    //     }
    // });
    // thread t3([](){
    //     ConnectionPool* connpool = ConnectionPool::getInstance();
    //     for(int i = 0; i < 250; i++){
    //         shared_ptr<Connection> conn = connpool->getConnction();
    //         char sql[1024] = {0};
    //         sprintf(sql, "insert into user(name, age, sex) values('zhangsan', 20, 'male')");
    //         conn->update(sql);
    //     }
    // });
    // thread t4([](){
    //     ConnectionPool* connpool = ConnectionPool::getInstance();
    //     for(int i = 0; i < 250; i++){
    //         shared_ptr<Connection> conn = connpool->getConnction();
    //         char sql[1024] = {0};
    //         sprintf(sql, "insert into user(name, age, sex) values('zhangsan', 20, 'male')");
    //         conn->update(sql);
    //     }
    // });
    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();

    clock_t end = clock();
    cout << (end - begin) << "ms" << endl;
    return 0;
}