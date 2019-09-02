#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstdio>
#include <map>
#include <vector>
#include "../utils/chat_proto.cpp"
#include "mysql_helper.h"
#include "unrepeatId.h"

using namespace std;

// 服务器上用户ID到连接信息的映射
map<int, User_connect_info *> ID2info;

void user_login(const char *ID, const char *password,
                User_connect_info *pUser_conect_info) {
    int RESPTYPE = LOGIN_REP;

    uint32_t len = 0;  // 数据包长度
    int status = 0;    // 服务器状态
    Json::Value response;

    char sqlStr[1024] = {0};
    sprintf(sqlStr, "%s'%s'", "select Password from User where Id=", ID);
    printf("sqlStr=%s\n", sqlStr);
    MYSQL *mysql = mysql_init(NULL);  // 创建一个MYSQL句柄并初始化
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    if (mysql_query(mysql, sqlStr) != 0) {
        printf("%s\n", mysql_error(mysql));
        close_connection(mysql);

        response["status"] = EDATABASE_WRECK;
        uint8_t *pData = encode(RESPTYPE, response, len);
        send(pUser_conect_info->user_fd, pData, len, 0);
    }

    MYSQL_RES *result;
    result = mysql_store_result(mysql);  // result为数据库中取出的密码列表
    close_connection(mysql);
    MYSQL_ROW row;
    do {
        if (result == NULL) {
            printf("%s\n", mysql_error(mysql));
            status = EDATABASE_WRECK;
            break;
        }
        if ((row = mysql_fetch_row(result)) == NULL) {
            printf("ID: %s 不存在\n", ID);
            status = EUSER_NOTEXSIT;
            break;
        }

        if (strcmp(row[0], password) == 0) {
            printf("ID：%s 登录成功\n", ID);
            status = NORMAL;
            break;
        } else {
            printf("ID:%s 密码错误\n", ID);
            status = EPASSWORD_WRONG;
            break;
        }
    } while (0);

    if (status == NORMAL) {
        // 登录成功,建立映射
        ID2info[atoi(ID)] = pUser_conect_info;
    }
    response["status"] = status;
    uint8_t *pData = encode(RESPTYPE, response, len);
    send(pUser_conect_info->user_fd, pData, len, 0);

    delete[] pData;
}

void user_register(const char *name, const char *password,
                   User_connect_info *pUser_conect_info) {
    int RESPTYPE = REGISTER_REP;
    uint32_t len = 0;  // 数据包长度
    int status = 0;    // 服务器状态
    Json::Value response;

    char field[50] = "Name,Password";
    char table_name[50] = "User";
    char message[50] = {0};
    sprintf(message, "'%s','%s'", name, password);

    /*数据库连接*/
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    int res = insert_data(mysql, field, table_name, message);
    if (res == 0) {
        status = NORMAL;
    } else {
        status = EDATABASE_WRECK;
    }

    int ID = getUnrepeatId();
    close_connection(mysql);


    char str[25];
    sprintf(str, "%d", ID);
    // printf("integer = %d string = %s\n", ID, string);

    response["status"] = status;
    response["ID"] = str;
    
    uint8_t *pData = encode(RESPTYPE, response, len);
    send(pUser_conect_info->user_fd, pData, len, 0);
}

void *handClient(void *arg) {
    char buf[1024] = {0};
    struct User_connect_info *pUser_conect_info =
        static_cast<struct User_connect_info *>(arg);
    int confd = pUser_conect_info->user_fd;
    int len;

    MyProtoDeCode myDecode;

    // 等待用户请求
    while (1) {
        if ((len = recv(confd, buf, sizeof(buf), 0)) == 0) {
            printf("用户 %d 已退出， Ip: %s\n", pUser_conect_info->user_id,

                   pUser_conect_info->ipaddr);
            ID2info.erase(pUser_conect_info->user_id);
            delete[] pUser_conect_info;
            pthread_exit(NULL);
        } else if (len == -1) {
            // TODO: 异常解决
            continue;
        } else {
            // 解码器初始化
            printf("Recive message from IP: %s, fd: %d, begin decode\n",
                   pUser_conect_info->ipaddr, pUser_conect_info->user_fd);
            myDecode.clear();
            myDecode.init();

            uint8_t *pData = (uint8_t *)buf;
            if (!myDecode.parser(pData, len)) {
                printf("parser falied!\n");
            } else {
                printf("parser successfully!, len = %d\n", len);
            }

            MyProtoMsg *pMsg = myDecode.front();  // 协议消息的指针
            int server_id = pMsg->head.server_id;

            if (server_id == REGISTER_REQ) {
                // 注册
                const char *name = pMsg->body["name"].asCString();
                const char *password = pMsg->body["password"].asCString();
                user_register(name, password, pUser_conect_info);
            } else if (server_id == LOGIN_REQ) {
                // 登录, 已测试
                const char *ID = pMsg->body["ID"].asCString();
                const char *password = pMsg->body["password"].asCString();
                user_login(ID, password, pUser_conect_info);
            } else if (LOGIN_REQ == RECENT_LIST_REQ) {
                const char *ID = pMsg->body["ID"].asCString();
                // 最近消息列表
            } else if (server_id == FRIEND_LIST_REQ) {
                const char *ID = pMsg->body["ID"].asCString();
                // 好友列表
            } else if (server_id == FRIEND_ADD_REQ) {
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                const char *group_id = pMsg->body["group_id"].asCString();
                // 好友添加
            } else if (server_id == FRIEND_DELETE_REQ) {
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                // 好友删除
            } else if (server_id == FRIEND_VERIFY_REQ) {
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                const char *choose = pMsg->body["choose"].asCString();
                const char *group_id = pMsg->body["group_id"].asCString();
                // ID1处理ID2的添加申请
            } else if (server_id == FRIEND_GROUP_CHANGE_REQ) {
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                const char *group_id = pMsg->body["group_id"].asCString();
                // 分组改变
            } else if (server_id == GET_FRIEND_INF_REQ) {
                const char *ID = pMsg->body["ID"].asCString();
                // 好友信息请求
            } else if (server_id == GET_MY_INF_REQ) {
                const char *ID = pMsg->body["ID"].asCString();
                // 自身信息
            } else if (server_id == CHANGE_MY_INF_REQ) {
                const char *ID = pMsg->body["ID"].asCString();
                int photo = pMsg->body["photo"].asInt();
                const char *name = pMsg->body["name"].asCString();
                const char *sex = pMsg->body["sex"].asCString();
                const char *tel = pMsg->body["tel"].asCString();
                const char *question = pMsg->body["question"].asCString();
                const char *answer = pMsg->body["answer"].asCString();
                const char *description = pMsg->body["description"].asCString();
                // 修改个人信息
            } else if (server_id == MESSAGE_SEND) {
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                const char *message = pMsg->body["message"].asCString();
                // 消息发送
            } else if (server_id == HISTORY_MESSAGE_REQ) {
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                // 聊天记录
            }
        }
        // send(confd,buf,strlen(buf),0);
    }
}

int PORT = 8888;

int main() {
    int i = 0;
    pthread_t tid;
    struct sockaddr_in server_addr, client_addr;
    socklen_t server_addr_len = sizeof(server_addr);

    memset(&server_addr, 0, server_addr_len);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = ntohs(PORT);

    if (1 != inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr)) {
        perror("Invalid IP");
        exit(1);
    }
    int listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 端口复用
    int opt = 1;
    // sockfd为需要端口复用的套接字
    setsockopt(listen_sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&opt,
               sizeof(opt));

    if (bind(listen_sockfd, (const sockaddr *)&server_addr, server_addr_len) ==
        -1) {
        perror("Bind error");
        printf("Server bind port: %d failed!\n", PORT);
        exit(1);
    }

    listen(listen_sockfd, 10);
    printf("Start listening...\n");

    char buf[1024] = {0};

    while (1) {
        int confd = accept(listen_sockfd, (struct sockaddr *)&client_addr,
                           (socklen_t *)&server_addr_len);

        if (confd == -1) {
            perror("connect error");
            // TODO: 针对连接错误的处理
            continue;
        }

        printf("newclient Ip=%s\t,Port=%d\n", inet_ntoa(client_addr.sin_addr),
               ntohs(client_addr.sin_port));

        struct User_connect_info *new_user = new User_connect_info();
        // 客户端的部分信息，此时还未登录
        strcpy(new_user->ipaddr, inet_ntoa(client_addr.sin_addr));
        new_user->user_fd = confd;

        // 给每个用户创建一个线程
        pthread_create(&tid, NULL, handClient, new_user);
    }
}
