#include <arpa/inet.h>
#include <mysql/mysql.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstdio>
#include <map>
#include <vector>
#include "UnrepeatId.h"
#include "mysql_helper.h"
#include "utils/chat_proto.cpp"

using namespace std;
map<int, int> ID2info;

class UserInformation {
public:
    int user_id;
    int user_fd;
    char ipaddr[32];
};

void user_login(const char *ID, const char *password,
                UserInformation *pUser_info) {
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
        send(pUser_info->user_fd, pData, len, 0);
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
            printf("ID:%s 密码错误\n");
            status = EPASSWORD_WRONG;
            break;
        }
    } while (0);

    response["status"] = status;
    uint8_t *pData = encode(RESPTYPE, response, len);
    send(pUser_info->user_fd, pData, len, 0);

    delete[] pData;
}

void user_register(const char *name, const char *password,
                  UserInformation *pUser_info) {
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

    response["status"] = status;
    uint8_t *pData = encode(RESPTYPE, response, len);
    send(pUser_info->user_fd, pData, len, 0);
}

void *handClient(void *arg) {
    char buf[1024] = {0};
    struct UserInformation *pUser_info =
        static_cast<struct UserInformation *>(arg);
    int confd = pUser_info->user_fd;
    int len;

    MyProtoDeCode myDecode;

    // 等待用户请求
    while (1) {
        if ((len = recv(confd, buf, sizeof(buf), 0)) == 0) {
            printf("用户 %d 已退出， Ip: %s", pUser_info->user_id,
                   pUser_info->ipaddr);
            ID2info.erase(pUser_info->user_id);
            delete[] pUser_info;
            pthread_exit(NULL);
        } else if (len == -1) {
            // TODO: 异常解决
            continue;
        } else {
            // 解码器初始化
            myDecode.clear();
            myDecode.init();

            uint8_t *pData = NULL;
            if (!myDecode.parser(pData, len)) {
                printf("parser falied!\n");
            } else {
                printf("parser successful!\n");
            }

            MyProtoMsg *pMsg = myDecode.front();  // 协议消息的指针
            switch (pMsg->head.server_id) {
            case REGISTER_REQ:
                const char *name = pMsg->body["name"].asCString();
                const char *password = pMsg->body["password"].asCString();
                // 注册
                user_register(name, password, pUser_info);
                break;

            case LOGIN_REQ:
                // 登录
                const char *ID = pMsg->body["ID"].asCString();
                const char *password = pMsg->body["password"].asCString();
                user_login(ID, password, pUser_info);
                break;

            case RECENT_LIST_REQ:
                const char *ID = pMsg->body["ID"].asCString();
                // 最近消息列表
                break;

            case FRIEND_LIST_REQ:
                const char *ID = pMsg->body["ID"].asCString();
                // 好友列表
                break;

            case FRIEND_ADD_REQ:
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                const char *group_id = pMsg->body["group_id"].asCString();
                // 好友添加
                break;

            case FRIEND_DELETE_REQ:
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                // 好友删除
                break;

            case FRIEND_VERIFY_REQ:
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                const char *choose = pMsg->body["choose"].asCString();
                const char *group_id = pMsg->body["group_id"].asCString();
                // ID1处理ID2的添加申请
                break;

            case FRIEND_GROUP_CHANGE_REQ:
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                const char *group_id = pMsg->body["group_id"].asCString();
                // 分组改变
                break;

            case GET_FRIEND_INF_REQ:
                const char *ID = pMsg->body["ID"].asCString();
                // 好友信息请求
                break;

            case GET_MY_INF_REQ:
                const char *ID = pMsg->body["ID"].asCString();
                // 自身信息
                break;

            case CHANGE_MY_INF_REQ:
                const char *ID = pMsg->body["ID"].asCString();
                int photo = pMsg->body["photo"].asInt();
                const char *name = pMsg->body["name"].asCString();
                const char *sex = pMsg->body["sex"].asCString();
                const char *tel = pMsg->body["tel"].asCString();
                const char *question = pMsg->body["question"].asCString();
                const char *answer = pMsg->body["answer"].asCString();
                const char *description = pMsg->body["description"].asCString();
                // 修改个人信息
                break;

            case MESSAGE_SEND:
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                const char *message = pMsg->body["message"].asCString();
                // 消息发送
                break;

            case HISTORY_MESSAGE_REQ:
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                // 聊天记录
                break;
            }
        }
        // send(confd,buf,strlen(buf),0);
    }
}

int main() {
    int i = 0;
    pthread_t tid;
    struct sockaddr_in myaddr;
    struct sockaddr_in cliaddr;
    int socklen = sizeof(cliaddr);

    memset(&myaddr, 0, sizeof(myaddr));

    myaddr.sin_family = AF_INET;
    myaddr.sin_addr.s_addr = inet_addr("172.17.210.103");
    myaddr.sin_port = htons(15129);

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == 0) {
        printf("socket error\n");
        return -1;
    }

    //给描述符绑定地址
    if (bind(listen_fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) != 0) {
        printf("bind error\n");
        return -1;
    }

    listen(listen_fd, 10);
    printf("Start listening...");

    char buf[1024] = {0};

    while (1) {
        int confd = accept(listen_fd, (struct sockaddr *)&cliaddr,
                           (socklen_t *)&socklen);

        if (confd == -1) {
            perror("connect error");
            // TODO: 针对连接错误的处理
            continue;
        }
        // int user_id = 0;

        // ID2info[user_id] = confd;
        // struct UserInformation *newuser = new struct UserInformation(
        //     {user_id, confd, *inet_ntoa(cliaddr.sin_addr)});

        printf("newclient Ip=%s\t,Port=%d\n", inet_ntoa(cliaddr.sin_addr),
               ntohs(cliaddr.sin_port));

        struct UserInformation *new_user = new UserInformation();
        // 客户端的部分信息，此时还未登录
        strcpy(new_user->ipaddr, inet_ntoa(cliaddr.sin_addr));
        new_user->user_fd = confd;

        // 给每个用户创建一个线程
        pthread_create(&tid, NULL, handClient, new_user);
    }
}
