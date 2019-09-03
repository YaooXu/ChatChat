#include "chat_proto.h"

using namespace std;

const char *get_time() {
    time_t tt;
    time(&tt);
    tt = tt + 8 * 3600;  // transform the time zone
    tm *t = gmtime(&tt);

    char *res = new char[25];
    sprintf(res, "%d-%02d-%02d %02d:%02d:%02d\n", t->tm_year + 1900, t->tm_mon + 1,
           t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    return res;
}

void myProtoMsgPrint(MyProtoMsg &msg) {
    string jsonStr = "";
    Json::FastWriter fWriter;
    jsonStr = fWriter.write(msg.body);
    std::cout << msg.body["op"] << endl;

    printf(
        "Head[version=%d,magic=%d,server_id=%d,len=%d]\n"
        "Body:%s",
        msg.head.version, msg.head.magic, msg.head.server_id, msg.head.len,
        jsonStr.c_str());
}

void MyProtoEnCode::headEncode(uint8_t *pData, MyProtoMsg *pMsg) {
    //设置协议头版本号为1
    *pData = 1;
    ++pData;

    //设置协议头魔数
    *pData = MY_PROTO_MAGIC;
    ++pData;

    //设置协议服务号，把head.server_id本地字节序转换为网络字节序
    *(uint16_t *)pData = htons(pMsg->head.server_id);
    pData += 2;

    //设置协议总长度，把head.len本地字节序转换为网络字节序
    *(uint32_t *)pData = htonl(pMsg->head.len);
}

/*

return:
    pData: 包含协议头以及内容的无符号字符串
*/
uint8_t *MyProtoEnCode::encode(MyProtoMsg *pMsg, uint32_t &len) {
    uint8_t *pData = NULL;
    Json::FastWriter fWriter;

    //协议json体序列化
    string bodyStr = fWriter.write(pMsg->body);
    //计算协议消息序列化后的总长度
    len = MY_PROTO_HEAD_SIZE + (uint32_t)bodyStr.size();
    pMsg->head.len = len;
    //申请协议消息序列化需要的空间
    pData = new uint8_t[len];
    //打包协议头
    // headEncode(pData, pMsg);
    MyProtoEnCode::headEncode(pData, pMsg);
    //打包协议体
    memcpy(pData + MY_PROTO_HEAD_SIZE, bodyStr.data(), bodyStr.size());

    return pData;
}

void MyProtoDeCode::init() { mCurParserStatus = PARSER_INIT; }

void MyProtoDeCode::clear() {
    MyProtoMsg *pMsg = NULL;

    while (!mMsgQ.empty()) {
        pMsg = mMsgQ.front();
        delete pMsg;
        mMsgQ.pop();
    }
}

/*
uint8_t **curData: 使用双重指针以修改指针的值
uint32_t &leftLen: 当前还需解析的字符串长度
*/
bool MyProtoDeCode::parserHead(uint8_t **curData, uint32_t &leftLen,
                               uint32_t &parserLen, bool &parserBreak) {
    // parserBreak:协议头是否解析完成
    parserBreak = false;

    if (leftLen < MY_PROTO_HEAD_SIZE) {
        parserBreak = true;  //终止解析
        return true;
    }

    uint8_t *pData = *curData;
    //解析版本号
    mCurMsg.head.version = *pData;
    pData++;
    //解析魔数
    mCurMsg.head.magic = *pData;
    pData++;
    //魔数不一致，则返回解析失败
    if (MY_PROTO_MAGIC != mCurMsg.head.magic) {
        return false;
    }
    //解析服务号
    mCurMsg.head.server_id = ntohs(*(uint16_t *)pData);
    pData += 2;
    //解析协议消息体的长度
    mCurMsg.head.len = ntohl(*(uint32_t *)pData);
    //异常大包，则返回解析失败
    if (mCurMsg.head.len > MY_PROTO_MAX_SIZE) {
        return false;
    }

    //解析指针向前移动MY_PROTO_HEAD_SIZE字节
    (*curData) += MY_PROTO_HEAD_SIZE;
    leftLen -= MY_PROTO_HEAD_SIZE;
    parserLen += MY_PROTO_HEAD_SIZE;
    mCurParserStatus = PARSER_HAED_FINISH;

    return true;
}

bool MyProtoDeCode::parserBody(uint8_t **curData, uint32_t &leftLen,
                               uint32_t &parserLen, bool &parserBreak) {
    parserBreak = false;
    uint32_t jsonSize = mCurMsg.head.len - MY_PROTO_HEAD_SIZE;
    if (leftLen < jsonSize) {
        parserBreak = true;  //终止解析
        return true;
    }

    Json::Reader reader;  // json解析类
    if (!reader.parse((char *)(*curData), (char *)((*curData) + jsonSize),
                      mCurMsg.body, false)) {
        return false;
    }

    //解析指针向前移动jsonSize字节
    (*curData) += jsonSize;
    leftLen -= jsonSize;
    parserLen += jsonSize;
    mCurParserStatus = PARSER_BODY_FINISH;

    return true;
}

bool MyProtoDeCode::parser(void *data, size_t len) {
    if (len <= 0) {
        return false;
    }

    // 当前还需解析的字符串长度
    uint32_t leftLen = 0;
    // 已经解析的字符串长度
    uint32_t parserLen = 0;
    uint8_t *curData = NULL;

    curData = (uint8_t *)data;
    //把当前要解析的网络字节流写入未解析完字节流之后
    while (len--) {
        mCurReserved.push_back(*curData);
        ++curData;
    }

    leftLen = mCurReserved.size();
    curData = (uint8_t *)&mCurReserved[0];

    //只要还有未解析的网络字节流，就持续解析
    while (leftLen > 0) {
        bool parserBreak = false;
        //解析协议头
        if (PARSER_INIT == mCurParserStatus ||
            PARSER_BODY_FINISH == mCurParserStatus) {
            if (!parserHead(&curData, leftLen, parserLen, parserBreak)) {
                return false;
            }

            if (parserBreak)
                break;
        }

        //解析完协议头，解析协议体
        if (PARSER_HAED_FINISH == mCurParserStatus) {
            if (!parserBody(&curData, leftLen, parserLen, parserBreak)) {
                return false;
            }

            if (parserBreak)
                break;
        }

        if (PARSER_BODY_FINISH == mCurParserStatus) {
            //拷贝解析完的消息体放入队列中
            MyProtoMsg *pMsg = NULL;
            pMsg = new MyProtoMsg;
            *pMsg = mCurMsg;
            mMsgQ.push(pMsg);
        }
    }

    if (parserLen > 0) {
        //删除已经被解析的网络字节流
        mCurReserved.erase(mCurReserved.begin(),
                           mCurReserved.begin() + parserLen);
    }

    return true;
}

bool MyProtoDeCode::empty() { return mMsgQ.empty(); }

MyProtoMsg *MyProtoDeCode::front() {
    MyProtoMsg *pMsg = NULL;
    pMsg = mMsgQ.front();
    return pMsg;
}

void MyProtoDeCode::pop() { mMsgQ.pop(); }

/**************************************************/
/*名称：encode
/*描述：把server_id 还有要发送的Json序列化
/*作成日期：2019-8-31
/*参数：
参数1：名称 server_id、参数类型 uint16_t、输入参数、含义：请求的服务类型
参数2：名称 message、类型 Json::Value、输入参数、含义：准备发送的Json对象
参数3：名称 len、类型 len、输出参数、含义：实际要send的字符串长度
/*返回值：返回值名称 pData、类型 unsigned char*、含义: 序列化之后的字符串
/*作者：徐遥
/***************************************************/
uint8_t *encode(uint16_t server_id, Json::Value message, uint32_t &len) {
    MyProtoMsg msg;

    msg.head.server_id = server_id;
    msg.body = message;

    uint8_t *pData = MyProtoEnCode::encode(&msg, len);

    return pData;
}

MyProtoMsg *decode2Msg(const char *buf, int len) {
    // 把字符串解析为协议结构体
    // 返回一个协议结构体指针
    MyProtoDeCode myDecode;
    myDecode.clear();
    myDecode.init();

    uint8_t *pData = (uint8_t *)buf;
    if (!myDecode.parser(pData, len)) {
        printf("parser falied!\n");
    } else {
        printf("parser successfully!, len = %d\n", len);
    }

    MyProtoMsg *pMsg = myDecode.front();  // 协议消息的指针
    return pMsg;
}
/*
发送结构体数组的Json格式:
{
    "length": int,
    "list":[
        {
            "name": char *,
            "ID": char *,
            XXXXXX
        },
        {
            "name": char *,
            "ID": char *,
            XXXXXX
        }
    ]
}
*/
User_in_list *decode2User_list(MyProtoMsg *pMsg, int &length) {
    // 客户端直接从字符串解包出User_in_list结构体数组
    // MyProtoMsg *pMsg = decode2Msg(buf, buf_len);
    // 结构体数组长度
    length = pMsg->body["length"].asInt();
    User_in_list *pUsers_in_list = new User_in_list[length];

    for (int i = 0; i < length; i++) {
        // 需要强制转化一下,不然不能从const char * -> char *
        pUsers_in_list[i].ID = (char *)pMsg->body["list"][i]["ID"].asCString();
        pUsers_in_list[i].group_id = pMsg->body["list"][i]["group_id"].asInt();
        pUsers_in_list[i].name =
            (char *)pMsg->body["list"][i]["name"].asCString();
        pUsers_in_list[i].sex_id = pMsg->body["list"][i]["sex_id"].isInt();
        pUsers_in_list[i].tel =
            (char *)pMsg->body["list"][i]["tel"].asCString();
        pUsers_in_list[i].description =
            (char *)pMsg->body["list"][i]["description"].asCString();
        pUsers_in_list[i].last_login_time =
            (char *)pMsg->body["list"][i]["last_login_time"].asCString();
        pUsers_in_list[i].photo_id = pMsg->body["list"][i]["photo_id"].asInt();
        pUsers_in_list[i].online = pMsg->body["list"][i]["online"].asInt();
    }
    printf("User_in_list结构体数组长度: %d\n", length);
    return pUsers_in_list;
}

User_info *decode2User_info(MyProtoMsg *pMsg, int buf_len, int &length) {
    // 客户端直接从字符串解包出User_in_list结构体数组
    // 查寻自己的信息
//    MyProtoMsg *pMsg = decode2Msg(buf, buf_len);
    // 结构体数组长度
    length = pMsg->body["length"].asInt();
    User_info *pUser_info = new User_info[length];

    for (int i = 0; i < length; i++) {
        // 需要强制转化一下,不然不能从const char * -> char *
        pUser_info[i].ID = (char *)pMsg->body["list"][i]["ID"].asCString();
        pUser_info[i].photo_id = pMsg->body["list"][i]["photo_id"].asInt();
        pUser_info[i].name = (char *)pMsg->body["list"][i]["name"].asCString();
        pUser_info[i].sex_id = pMsg->body["list"][i]["sex_id"].asInt();
        pUser_info[i].tel = (char *)pMsg->body["list"][i]["tel"].asCString();
        pUser_info[i].question =
            (char *)pMsg->body["list"][i]["question"].asCString();
        pUser_info[i].answer =
            (char *)pMsg->body["list"][i]["answer"].asCString();
        pUser_info[i].description =
            (char *)pMsg->body["list"][i]["description"].asCString();
        pUser_info[i].last_login_time =
            (char *)pMsg->body["list"][i]["last_login_time"].asCString();
    }
    printf("User_info结构体数组长度: %d\n", length);
    return pUser_info;
}

User_in_recent *decode2User_recent(MyProtoMsg *pMsg, int &length){
    // MyProtoMsg *pMsg = decode2Msg(buf, buf_len);
    // 结构体数组长度
    length = pMsg->body["length"].asInt();
    User_in_recent *pUser_recent = new User_in_recent[length];

    for (int i = 0; i < length; i++) {
        // 需要强制转化一下,不然不能从const char * -> char *
        pUser_recent[i].ID = (char *)pMsg->body["list"][i]["ID"].asCString();
        pUser_recent[i].last_message = (char *)pMsg->body["list"][i]["last_message"].asCString();
        pUser_recent[i].time = (char *)pMsg->body["list"][i]["time"].asCString();
    }
    printf("User_info结构体数组长度: %d\n", length);
    return pUser_recent;
}


Message *decode2Message(MyProtoMsg *pMsg) {
//    MyProtoMsg *pMsg = decode2Msg(buf, len);
    Message *pMessage = new Message();
    pMessage->ID1 = (char *)pMsg->body["ID1"].asCString();
    pMessage->ID2 = (char *)pMsg->body["ID2"].asCString();
    pMessage->content = (char *)pMsg->body["content"].asCString();
    pMessage->time = (char *)pMsg->body["time"].asCString();
    return pMessage;
}


static char *get_my_ip() {
    struct ifaddrs *ifaddr, *ifa;
    int family, s;
    char *host = NULL;

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return NULL;
    }

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        if (!strcmp(ifa->ifa_name, "lo"))
            continue;
        if (family == AF_INET) {
            if ((host = (char *)malloc(NI_MAXHOST)) == NULL)
                return NULL;
            s = getnameinfo(ifa->ifa_addr,
                            (family == AF_INET) ? sizeof(struct sockaddr_in)
                                                : sizeof(struct sockaddr_in6),
                            host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0) {
                return NULL;
            }
            freeifaddrs(ifaddr);
            return host;
        }
    }
    return NULL;
}
// DEMO 实际使用的时候要注释掉main
// int main() {
//     Json::Value message;
//     message["name"] = "xy";
//     uint32_t len = 0;
//     uint8_t *pData = encode(1, message, len);

//     printf("%d\n", len);
//     // uint32_t len = 0;
//     // uint8_t *pData = NULL;
//     // MyProtoMsg msg1;
//     // MyProtoMsg msg2;
//     // MyProtoDeCode myDecode;
//     // MyProtoEnCode myEncode;

//     // msg1.head.server_id = 1;
//     // msg1.body["ID"] = "0001";
//     // msg1.body["name"] = "xy";
//     // msg1.body["sex"] = "male";
//     // msg1.body["tel"] = "123";

//     // // msg2.head.server_id = 2;
//     // // msg2.body["op"] = "get";
//     // // msg2.body["key"] = "id";

//     // myDecode.init();
//     // pData = myEncode.encode(&msg1, len);

//     // if (!myDecode.parser(pData, len)) {
//     //     cout << "parser falied!" << endl;
//     // } else {
//     //     cout << "msg1 parser successful!" << endl;
//     // }

//     // // pData = myEncode.encode(&msg2, len);

//     // // if (!myDecode.parser(pData, len)) {
//     // //     cout << "parser falied!" << endl;
//     // // } else {
//     // //     cout << "msg2 parser successful!" << endl;
//     // // }

//     // MyProtoMsg *pMsg = NULL;
//     // while (!myDecode.empty()) {
//     //     pMsg = myDecode.front();
//     //     // myProtoMsgPrint(*pMsg);
//     //     cout << (*pMsg).body["ID"] << endl;
//     //     myDecode.pop();
//     // }

//     return 0;
// }
