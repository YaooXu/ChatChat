#include <arpa/inet.h>
#include <jsoncpp/json/json.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <vector>

#ifndef _CHAT_PROTO_H
#define _CHAT_PROTO_H

#define REGISTER 0
#define LOGIN 1
#define GET_INFORMATION 2
/*



*/

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

uint8_t *encode(uint16_t server_id, Json::Value root);



#endif