#pragma once

#include <arpa/inet.h>
#include <jsoncpp/json/json.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <queue>
#include <vector>

// 发给服务器的server_id
#define REGISTER_REQ 1000
#define LOGIN_REQ 1001
#define RECENT_LIST_REQ 1002    //请求最近消息列表

#define FRIEND_LIST_REQ 1003    //请求好友列表
#define FRIEND_FIND_REQ 1004
#define FRIEND_ADD_REQ 1014
#define FRIEND_DELETE_REQ 1005
#define FRIEND_VERIFY_REQ 1006
#define FRIEND_GROUP_CHANGE_REQ 1007

#define CREATE_GROUP_REQ 1008
#define GET_FRIEND_INF_REQ 1009
#define GET_MY_INF_REQ 1010
#define CHANGE_MY_INF_REQ 1011
#define MESSAGE_SEND 1012
#define HISTORY_MESSAGE_REQ 1013

// 服务器给客户端的server_id
// 分为NOTI 直接通知
// REP 对于请求的回应
#define REGISTER_REP 5000
#define LOGIN_REP 5001
#define RECENT_LIST_REP 5002    //返回最近联系人消息
#define FRIEND_LIST_REP 5003    //返回好友列表
#define FRIEND_FIND_REP 5004
#define FRIEND_DELETE_REP 5005
#define FRIEND_VERIFY_REP 5006
#define FRIEND_APPLI_NOTI 5007
#define FRIEND_GROUP_CHANGE_REP 5008
#define CREATE_GROUP_REP 5009
#define GET_FRIEND_INF_REP 5010
#define GET_MY_INF_REP 5011
#define CHANGE_MY_INF_REP 5012
#define MESSAGE_NOTI 5013
#define SYSTEM_NOTI 5014
#define HISTORY_MESSAGE_REP 5015
#define FRIEND_ADD_REP 5016

// 服务器状态码
#define NORMAL 0
#define EPASSWORD_WRONG 1
#define EUSER_NOTEXSIT 2
#define EDATABASE_WRECK 3
#define EOPPOSITE_SIDE_OFFLINE 4
// #define

// 得到当前时间
const char *get_time();

const uint8_t MY_PROTO_MAGIC = 88;                    //
const uint32_t MY_PROTO_MAX_SIZE = 10 * 1024 * 1024;  // 10M
const uint32_t MY_PROTO_HEAD_SIZE = 8;

// 解析器状态
typedef enum MyProtoParserStatus {
    PARSER_INIT = 0,
    PARSER_HAED_FINISH = 1,
    PARSER_BODY_FINISH = 2,
} MyProtoParserStatus;

/*
协议头
*/
struct MyProtoHead {
    uint8_t version;  //协议版本号
    uint8_t magic;    //协议魔数
    uint16_t server_id;  //协议复用的服务号，标识协议之上的不同服务
    uint32_t len;  //整体数据包长度（协议头长度+变长json协议体长度）
};

/*
协议消息体
*/
struct MyProtoMsg {
    MyProtoHead head;  //协议头
    Json::Value body;  //协议体
};

/*
MyProto打包类
*/
class MyProtoEnCode {
public:
    //协议消息体打包函数
    static uint8_t *encode(MyProtoMsg *pMsg, uint32_t &len);

private:
    //协议头打包函数
    static void headEncode(uint8_t *pData, MyProtoMsg *pMsg);
};

/*
MyProto解包类
*/
class MyProtoDeCode {
public:
    void init();
    void clear();
    bool parser(void *data, size_t len);
    bool empty();
    MyProtoMsg *front();
    void pop();

private:
    bool parserHead(uint8_t **curData, uint32_t &leftLen, uint32_t &parserLen,
                    bool &parserBreak);
    bool parserBody(uint8_t **curData, uint32_t &leftLen, uint32_t &parserLen,
                    bool &parserBreak);

private:
    MyProtoMsg mCurMsg;                    //当前解析中的协议消息体
    std::queue<MyProtoMsg *> mMsgQ;        //解析好的协议消息队列
    std::vector<uint8_t> mCurReserved;     //未解析的网络字节流
    MyProtoParserStatus mCurParserStatus;  //当前解析状态
};

void myProtoMsgPrint(MyProtoMsg &msg);

uint8_t *encode(uint16_t server_id, Json::Value root, uint32_t &len);

// 请求好友列表返回的结构体
class User_in_list {
public:
    char *ID;
    int photo_id;
    char *name;
    int sex_id;
    char *tel;
    char *description;
    char *last_login_time;
    int group_id;
    int online;
};

// 请求最近联系人列表返回的结构体
class User_in_recent {
public:
    char *ID;
    char *last_message;
    char *time;
};

// 查询自身时返回的结构体
class User_info {
public:
    char *ID;
    int photo_id;
    char *name;
    int sex_id;
    char *tel;
    char *question;
    char *answer;
    char *description;
    char *last_login_time;
};

// 用户连接信息
class User_connect_info {
public:
    int user_id;
    int user_fd;
    char ipaddr[32];
};

// 发送的消息
class Message {
public:
    char *ID1;
    char *ID2;
    char *content;
    char *time;
};

MyProtoMsg *decode2Msg(const char *buf, int len);

User_in_list *decode2User_list(const char *buf, int buf_len, int &length);

User_info *decode2User_info(const char *buf, int buf_len, int &length);

User_in_recent *decode2User_recent(const char *buf, int buf_len, int &length);

Message *decode2Message(MyProtoMsg *pMsg, int len);
