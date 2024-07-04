#ifndef CONNECTION_H
#define CONNECTION_H

#include <mysql/mysql.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class Connection
{
public:
    // 初始化数据库连接
    Connection();
    // 释放数据库连接资源
    ~Connection();
    // 连接数据库
    bool connect(string, string, string, string);
    // 更新操作
    bool update(string sql);
    // 查询操作
    MYSQL_RES* query(string sql);
    // 获取当前连接
    MYSQL* getConnection();
    // 刷新连接的空闲时间起点
    void refAliveTime(){_aliveTime = clock();}
    // 返回连接空闲时间
    clock_t getAliveTime(){return clock() - _aliveTime;}
private:
    MYSQL *_conn;
    // 进入队列的时间
    clock_t _aliveTime;
};

#endif