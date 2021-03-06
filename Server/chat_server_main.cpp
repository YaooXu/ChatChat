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

// 判断当前ID是否在线
int is_online(int ID) { return ID2info.count(ID); }
int is_online(const char *ID) { return ID2info.count(atoi(ID)); }

void send_user_info(const char *ID, User_connect_info *pUser_connect_info) {
    // 登录时向客户端发送的自身信息
    int status, RESPTYPE = GET_MY_INF_REP;
    uint32_t len = 0;
    int int_ID = atoi(ID);
    Json::Value response;

    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char sqlStr[1024] = {0};
    sprintf(sqlStr,
            "select "
            "Name,Photo,Sex,Email,Telephone,Question,Answer,Description,"
            "LastLoginTime from User where Id='%s'",
            ID);
    printf("%s\n", sqlStr);
    if (mysql_query(mysql, sqlStr) != 0) {
        // 查询失败,直接返回
        printf("%s\n", mysql_error(mysql));

        close_connection(mysql);
        status = EDATABASE_WRECK;
        response["status"] = EDATABASE_WRECK;
        uint8_t *pData = encode(RESPTYPE, response, len);
        // send(pUser_connect_info->user_fd, pData, len, 0);
        return;
    }

    MYSQL_RES *result;
    result = mysql_store_result(mysql);
    close_connection(mysql);

    if (result == NULL) {
        printf("%s\n", mysql_error(mysql));
        status = EDATABASE_WRECK;
    } else {
        int num_row, num_col;
        MYSQL_ROW mysql_row;
        num_row = mysql_num_rows(result);
        num_col = mysql_num_fields(result);

        // 结构体数组长度
        response["length"] = num_row;

        Json::Value user;
        printf("row: %d,col: %d\n", num_row, num_col);

        // 在线测试
        for (int i = 0; i < num_row; i++) {
            mysql_row = mysql_fetch_row(result);

            for (int j = 0; j < num_col; j++) {
                printf("[Row %d,Col %d]==>[%s], is NULL:%d\n", i, j,
                       mysql_row[j], mysql_row[j] == NULL);
            }
            user["ID"] = ID;
            user["name"] = mysql_row[0];
            // 当指针为NULL的时候直接赋值会段错误!
            user["photo_id"] = mysql_row[1] == NULL ? 0 : atoi(mysql_row[1]);
            user["sex_id"] = mysql_row[2] == NULL ? 0 : atoi(mysql_row[2]);
            user["email"] = mysql_row[3] == NULL ? "" : mysql_row[3];
            user["tel"] = mysql_row[4] == NULL ? "" : mysql_row[4];
            user["question"] = mysql_row[5] == NULL ? "" : mysql_row[5];
            user["answer"] = mysql_row[6] == NULL ? "" : mysql_row[6];
            user["description"] = mysql_row[7] == NULL ? "" : mysql_row[7];
            user["last_login_time"] = mysql_row[8] == NULL ? "" : mysql_row[8];
            response["list"].append(user);
        }

        response["status"] = status;
        uint8_t *pData = encode(RESPTYPE, response, len);
        send(pUser_connect_info->user_fd, pData, len, 0);
        // Name,Photo,Sex,Email,Telephone,Question,Answer,Description,LastLoginTime
        // 解包测试

        // char *buf = (char *)pData;
        // int num = 0;
        // User_info *pUser_in_list = decode2User_info(buf, len, num);
        // for (int i = 0; i < num; i++) {
        //     printf("%s, %d,%s, %d, %s, %s, %s, %s, %s, %s\n",
        //            pUser_in_list[i].ID, pUser_in_list[i].photo_id,
        //            pUser_in_list[i].name, pUser_in_list[i].sex_id,
        //            pUser_in_list[i].tel, pUser_in_list[i].question,
        //            pUser_in_list[i].answer, pUser_in_list[i].description,
        //            pUser_in_list[i].last_login_time);
    }
}

/* 发送好友列表*/
void send_friend_list(const char *ID, User_connect_info *pUser_connect_info) {
    // select * from Friend join User where Friend.Id1=User.Id and Id="123456";
    int status, RESPTYPE = FRIEND_LIST_REP;
    uint32_t len = 0;
    int int_ID = atoi(ID);
    Json::Value response;

    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char sqlStr[1024] = {0};
    sprintf(
        sqlStr,
        "select "
        "Groupint,Id,Name,Photo,Sex,Email,Description,LastLoginTime,Telephone  "
        "from Friend join User where User.Id=Friend.ID2 and Friend.ID1='%s'",
        ID);
    printf("%s\n", sqlStr);
    if (mysql_query(mysql, sqlStr) != 0) {
        // 查询失败,直接返回
        printf("%s\n", mysql_error(mysql));
        close_connection(mysql);

        status = EDATABASE_WRECK;
    } else {
        // 查询成功
        MYSQL_RES *result;
        result = mysql_store_result(mysql);
        close_connection(mysql);

        if (result == NULL) {
            // 未知错误
            printf("%s\n", mysql_error(mysql));
            status = EDATABASE_WRECK;
        } else {
            // 正真成功
            int num_row, num_col;
            MYSQL_ROW mysql_row;
            num_row = mysql_num_rows(result);
            num_col = mysql_num_fields(result);

            // 结构体数组长度
            response["length"] = num_row;

            Json::Value user;
            printf("ID:%s 共有 %d 个好友\n", ID, num_row);

            // // 在线测试
            // map<int, int> ID2info;
            // ID2info[123672] = 1;

            for (int i = 0; i < num_row; i++) {
                mysql_row = mysql_fetch_row(result);

                for (int j = 0; j < num_col; j++) {
                    printf("[Row %d,Col %d]==>[%s], is NULL:%d\n", i, j,
                           mysql_row[j], mysql_row[j] == NULL);
                }

                user["ID"] = mysql_row[1];
                user["photo_id"] =
                    mysql_row[3] == NULL ? 0 : atoi(mysql_row[3]);
                user["name"] = mysql_row[2];
                // 当指针为NULL的时候直接赋值会段错误!
                user["sex_id"] = mysql_row[4] == NULL ? 0 : atoi(mysql_row[4]);
                user["tel"] = mysql_row[8] == NULL ? "" : mysql_row[8];
                user["description"] = mysql_row[6] == NULL ? "" : mysql_row[6];
                user["last_login_time"] =
                    mysql_row[7] == NULL ? "" : mysql_row[7];
                user["group_id"] =
                    mysql_row[0] == NULL ? 0 : atoi(mysql_row[0]);
                user["online"] = is_online(mysql_row[1]);

                response["list"].append(user);
            }
        }
    }
    response["status"] = status;
    uint8_t *pData = encode(RESPTYPE, response, len);
    send(pUser_connect_info->user_fd, pData, len, 0);

    // // 解包测试
    // char *buf = (char *)pData;
    // int num = 0;
    // User_in_list *pUser_in_list = decode2User_list(buf, len, num);
    // for (int i = 0; i < num; i++) {
    //     printf("%s, %s, %d, %d, %d\n", pUser_in_list[i].name,
    //            pUser_in_list[i].description, pUser_in_list[i].photo_id,
    //            pUser_in_list[i].group_id, pUser_in_list[i].online);
    // }
}

void send_friend_info(const char *ID, User_connect_info *pUser_connect_info) {
    int status, RESPTYPE = GET_FRIEND_INF_REP;
    uint32_t len = 0;
    int int_ID = atoi(ID);
    Json::Value response;

    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char sqlStr[1024] = {0};
    sprintf(sqlStr,
            "select "
            "Id,Name,Photo,Sex,Email,Description,LastLoginTime,Telephone "
            "from User where Id='%s'",
            ID);
    printf("%s\n", sqlStr);
    if (mysql_query(mysql, sqlStr) != 0) {
        // 查询失败,直接返回
        printf("%s\n", mysql_error(mysql));
        close_connection(mysql);
        status = EDATABASE_WRECK;
    } else {
        // 查询成功
        MYSQL_RES *result;
        result = mysql_store_result(mysql);
        close_connection(mysql);

        if (result == NULL) {
            // 未知错误
            printf("%s\n", mysql_error(mysql));
            status = EDATABASE_WRECK;
        } else {
            int num_row, num_col;
            MYSQL_ROW mysql_row;
            num_row = mysql_num_rows(result);
            num_col = mysql_num_fields(result);

            // 结构体数组长度
            response["length"] = num_row;

            Json::Value user;

            for (int i = 0; i < num_row; i++) {
                mysql_row = mysql_fetch_row(result);
                for (int j = 0; j < num_col; j++) {
                    printf("[Row %d,Col %d]==>[%s], is NULL:%d\n", i, j,
                           mysql_row[j], mysql_row[j] == NULL);
                }

                user["ID"] = mysql_row[0];
                user["photo_id"] =
                    mysql_row[2] == NULL ? 0 : atoi(mysql_row[2]);
                user["name"] = mysql_row[1];
                // 当指针为NULL的时候直接赋值会段错误!
                user["sex_id"] = mysql_row[3] == NULL ? 0 : atoi(mysql_row[3]);
                user["tel"] = mysql_row[7] == NULL ? "" : mysql_row[7];
                user["description"] = mysql_row[5] == NULL ? "" : mysql_row[5];
                user["last_login_time"] =
                    mysql_row[6] == NULL ? "" : mysql_row[6];
                user["group_id"] = 0;
                user["online"] = is_online(mysql_row[0]);
                response["list"].append(user);
            }
        }
    }
    response["status"] = status;
    uint8_t *pData = encode(RESPTYPE, response, len);
    send(pUser_connect_info->user_fd, pData, len, 0);
    // // 解包测试
    // char *buf = (char *)pData;
    // int num = 0;
    // User_in_list *pUser_in_list = decode2User_list(buf, len, num);
    // for (int i = 0; i < num; i++) {
    //     printf("%s, %s, %d, %d, %d\n", pUser_in_list[i].name,
    //            pUser_in_list[i].description, pUser_in_list[i].photo_id,
    //            pUser_in_list[i].group_id, pUser_in_list[i].online);
    // }
}

void send_recent_list(const char *ID, User_connect_info *pUser_connect_info) {
    printf("开始准备最近联系人列表\n");

    int status, RESPTYPE = RECENT_LIST_REP;
    uint32_t len = 0;
    // char ID[50] = {"123456"};
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char sqlStr[1024] = {0};
    sprintf(
        sqlStr,
        "select temp.id,temp.Content,temp.Time,User.Photo from (select "
        "tem.id,tem.Content,tem.Time FROM ((select Id1 as id,Content,Time  "
        "from ChatContent where Id2='%s') union (select Id2 as "
        "id,Content,Time  from ChatContent where Id1='%s')  order by Time "
        "desc)as tem group by tem.id) as temp join User where temp.id=User.id",
        ID, ID);
    printf("%s\n", sqlStr);
    Json::Value user;
    Json::Value response;
    do {
        if (mysql_query(mysql, sqlStr) != 0) {
            printf("%s\n", mysql_error(mysql));
            close_connection(mysql);
            status = EDATABASE_WRECK;
            break;
        }
        MYSQL_RES *result;
        result = mysql_store_result(mysql);
        close_connection(mysql);
        if (result == NULL) {
            printf("%s\n", mysql_error(mysql));
            status = EDATABASE_WRECK;
            break;
        }

        int num_row, num_col;

        MYSQL_ROW mysql_row;
        num_row = mysql_num_rows(result);
        num_col = mysql_num_fields(result);
        response["length"] = num_row;

        printf("最近联系人共有%d人\n", num_row);
        printf("row: %d,col: %d\n", num_row, num_col);

        for (int i = 0; i < num_row; i++) {
            mysql_row = mysql_fetch_row(result);
            // for (int j = 0; j < num_col; j++) {
            //     printf("[Row %d,Col %d]==>[%s]\n", i, j, mysql_row[j]);
            // }
            user["ID"] = mysql_row[0] == NULL ? "xxxxxx" : mysql_row[0];
            user["last_message"] = mysql_row[1] == NULL ? "" : mysql_row[1];
            user["time"] = mysql_row[2] == NULL ? "" : mysql_row[2];
            user["photo_id"] = atoi(mysql_row[3]) == 0 ? 1 : atoi(mysql_row[3]);
            response["list"].append(user);
        }
    } while (0);

    response["status"] = status;
    uint8_t *pData = encode(RESPTYPE, response, len);
    send(pUser_connect_info->user_fd, pData, len, 0);

    // // 解包测试
    // char *buf = (char *)pData;
    // int num = 0;
    // User_in_recent *pUser_in_recent = decode2User_recent(buf, len, num);
    // for (int i = 0; i < num; i++) {
    //     printf("%s, %s, %s\n", pUser_in_recent[i].ID,
    //            pUser_in_recent[i].last_message, pUser_in_recent[i].time);
    // }
}

// 得到当前在线列表
/*
{
    "length": int,
    "list":[
        {
            "ID", str,
            "IP": str
        },
        {

        }
    ]
}
*/
// 得到当前在线用户，并转化为pData,len为传出参数
uint8_t *get_group_list(uint32_t &len) {
    // uint32_t len = 0;  // 数据包长度
    Json::Value response;

    int length = 0;
    map<int, User_connect_info *>::iterator iter;
    for (iter = ID2info.begin(); iter != ID2info.end(); iter++) {
        length += 1;
        Json::Value user;
        int ID = iter->first;
        User_connect_info *pUser_connect_info = iter->second;
        char str[25];
        sprintf(str, "%d", ID);

        user["ID"] = str;
        user["IP"] = pUser_connect_info->ipaddr;

        printf("%s %s\n", user["ID"].asCString(), user["IP"].asCString());

        response["list"].append(user);
    }
    response["length"] = length;
    uint8_t *pData = encode(CURENT_GROUP_LIST, response, len);
    return pData;
}

// 发送当前在线列表
void send_group_list() {
    uint32_t len;
    uint8_t *pData = get_group_list(len);
    map<int, User_connect_info *>::iterator iter;
    for (iter = ID2info.begin(); iter != ID2info.end(); iter++) {
        User_connect_info *tmp = iter->second;
        send(tmp->user_fd, pData, len, 0);
    }
}

void user_login(const char *ID, const char *password,
                User_connect_info *pUser_connect_info) {
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
        send(pUser_connect_info->user_fd, pData, len, 0);
        return;  // 得终止
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
        ID2info[atoi(ID)] = pUser_connect_info;
    }
    response["status"] = status;
    uint8_t *pData = encode(RESPTYPE, response, len);
    send(pUser_connect_info->user_fd, pData, len, 0);

    if (status == NORMAL) {
        // 登录成功继续发送好友列表,个人信息列表
        printf("发送初始信息\n");
        send_user_info(ID, pUser_connect_info);
        // sleep(1);
        send_friend_list(ID, pUser_connect_info);
        // sleep(1);
        send_recent_list(ID, pUser_connect_info);
        // 登记连接信息
        pUser_connect_info->user_id = atoi(ID);

        send_group_list();
    }
    delete[] pData;
}

void file_trans(const char *ID1, const char *ID2, const char *file_name,
                User_connect_info *pUser_connect_info) {
    uint32_t len = 0;  // 数据包长度
    int status = 0;    // 服务器状态
    Json::Value response;

    if (is_online(ID2)) {
        // 对方在线
        status = NORMAL;
        response["status"] = status;
        response["ID1"] = ID1;
        response["ID2"] = ID2;
        response["IP1"] = pUser_connect_info->ipaddr;
        response["file_name"] = file_name;

        uint8_t *pData = encode(FILE_TRANS_NOTI, response, len);
        // ID2的连接信息, 通知ID2有文件传输请求
        User_connect_info *pUser_connect_info2 = ID2info[atoi(ID2)];
        send(pUser_connect_info2->user_fd, pData, len, 0);

        delete[] pData;
        // 给ID1发送 文件发送请求发送成功通知
        Json::Value response1;
        response1["status"] = status;
        pData = encode(FILE_TRANS_REP, response, len);
        send(pUser_connect_info->user_fd, pData, len, 0);
    } else {
        // 对方不在线
        status = EOPPOSITE_SIDE_OFFLINE;
        response["status"] = status;

        uint8_t *pData = encode(FILE_TRANS_REP, response, len);
        send(pUser_connect_info->user_fd, pData, len, 0);
    }

    return;
}

void user_register(const char *name, const char *password,
                   User_connect_info *pUser_connect_info) {
    int RESPTYPE = REGISTER_REP;
    uint32_t len = 0;  // 数据包长度
    int status = 0;    // 服务器状态
    Json::Value response;

    int ID = getUnrepeatId();
    char field[50] = "Id,Name,Password,LastLoginTime";
    char table_name[50] = "User";
    char message[50] = {0};
    sprintf(message, "'%d','%s','%s',NOW()", ID, name, password);
    /*数据库连接*/
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
        status = EDATABASE_WRECK;
    } else {
        mysql_connect(mysql);
        int res = insert_data(mysql, field, table_name, message);
        if (res == 0) {
            status = NORMAL;
        } else {
            status = EDATABASE_WRECK;
        }

        close_connection(mysql);

        // printf("integer = %d string = %s\n", ID, string);
    }
    char str[25];
    sprintf(str, "%d", ID);
    response["status"] = status;
    if (status == NORMAL) {
        response["ID"] = str;
    }

    uint8_t *pData = encode(RESPTYPE, response, len);
    send(pUser_connect_info->user_fd, pData, len, 0);
}

void update_user_info(const char *ID, const char *name, int photo_id,
                      int sex_id, const char *tel, const char *description,
                      const char *question, const char *answer,
                      User_connect_info *pUser_connect_info) {
    int RESPTYPE = CHANGE_MY_INF_REP;
    uint32_t len = 0;  // 数据包长度
    int status = 0;    // 服务器状态
    Json::Value response;
    char email[50] = {""};
    char value[512] = {0};
    sprintf(value,
            "Name='%s',Photo='%d',Sex='%d',Email='%s',Telephone='%s',"
            "Description='%s',Question='%s',Answer='%s'",
            name, photo_id, sex_id, email, tel, description, question, answer);
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
        status = EDATABASE_WRECK;
    } else {
        mysql_connect(mysql);
        char ids[512];
        sprintf(ids, "'%s'", ID);
        int ret = update_data(mysql, "User", value, "Id", ids);
        if (ret == 0) {
            // 成功
            status = NORMAL;
        } else {
            status = EDATABASE_WRECK;
        }
        mysql_close(mysql);
        response["status"] = status;
        uint8_t *pData = encode(RESPTYPE, response, len);
        send(pUser_connect_info->user_fd, pData, len, 0);
    }
}

int insert_chat_content(const char *ID1, const char *ID2, const char *content,
                        int readstate2) {
    // readstate 表示对方是否接受
    int readstate1 = 0;
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char value[505] = {0};
    sprintf(value, "'%s','%s','%d','%d',NOW(),'%s'", ID1, ID2, readstate1,
            readstate2, content);
    insert_data(mysql, "Id1,Id2,ReadState1,ReadState2,Time,Content",
                "ChatContent", value);
    close_connection(mysql);
}

// 返回值:给ID2发送申请消息是否成功
int friend_add_noti(const char *ID1, const char *ID2,
                    User_connect_info *pUser_connect_info) {
    // 给ID2发送申请信息
    int status, RESPTYPE = FRIEND_ADD_NOTI;
    uint32_t len = 0;
    int int_ID = atoi(ID1);
    Json::Value response;

    if (!is_online(ID2)) {
        // ID2不在线,返回EOPPOSITE_SIDE_OFFLINE
        return EOPPOSITE_SIDE_OFFLINE;
    }

    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
        return EDATABASE_WRECK;
    }

    mysql_connect(mysql);
    char sqlStr[1024] = {0};
    sprintf(sqlStr,
            "select Id,Name,Photo,Sex,Email,Description,LastLoginTime "
            "from User where Id='%s'",
            ID1);
    printf("%s\n", sqlStr);

    if (mysql_query(mysql, sqlStr) != 0) {
        // 查询失败,直接返回
        printf("%s\n", mysql_error(mysql));
        close_connection(mysql);

        return EDATABASE_WRECK;
    } else {
        MYSQL_RES *result;
        result = mysql_store_result(mysql);
        close_connection(mysql);
        if (result == NULL) {
            printf("%s\n", mysql_error(mysql));
            return EDATABASE_WRECK;
        } else {
            int num_row, num_col;
            MYSQL_ROW mysql_row;
            num_row = mysql_num_rows(result);
            num_col = mysql_num_fields(result);

            // 结构体数组长度
            response["length"] = num_row;

            Json::Value user;
            printf("row: %d,col: %d\n", num_row, num_col);

            // 在线测试
            for (int i = 0; i < num_row; i++) {
                mysql_row = mysql_fetch_row(result);

                for (int j = 0; j < num_col; j++) {
                    printf("[Row %d,Col %d]==>[%s], is NULL:%d\n", i, j,
                           mysql_row[j], mysql_row[j] == NULL);
                }
                user["ID"] = mysql_row[0];
                user["photo_id"] =
                    mysql_row[2] == NULL ? 0 : atoi(mysql_row[2]);
                user["name"] = mysql_row[1];
                // 当指针为NULL的时候直接赋值会段错误!
                user["sex_id"] = mysql_row[3] == NULL ? 0 : atoi(mysql_row[3]);
                user["tel"] = mysql_row[7] == NULL ? "" : mysql_row[7];
                user["description"] = mysql_row[5] == NULL ? "" : mysql_row[5];
                user["last_login_time"] =
                    mysql_row[6] == NULL ? "" : mysql_row[6];
                user["online"] = is_online(ID2);
                response["list"].append(user);
            }
        }
    }

    // 到这一步都是成功了
    response["status"] = status;
    uint8_t *pData = encode(FRIEND_ADD_NOTI, response, len);
    // ID2的连接信息
    User_connect_info *pUser_connect_info2 = ID2info[atoi(ID2)];
    // TODO: 给ID1申请反馈
    send(pUser_connect_info2->user_fd, pData, len, 0);
    return NORMAL;

    // 解包测试
    // char *buf = (char *)pData;
    // int num = 0;
    // User_in_list *pUser_in_list = decode2User_list(buf, len, num);
    // for (int i = 0; i < num; i++) {
    //     printf("%s, %s, %d, %d, %d\n", pUser_in_list[i].name,
    //            pUser_in_list[i].description, pUser_in_list[i].photo_id,
    //            pUser_in_list[i].sex_id, pUser_in_list[i].online);
}

// 好友请求申请(第一次请求)
void friend_add_req(const char *ID1, const char *ID2, int group_id,
                    User_connect_info *pUser_connect_info) {
    int status;
    uint32_t len = 0;
    int int_ID = atoi(ID1);
    Json::Value response;

    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
        status = EDATABASE_WRECK;
    } else {
        mysql_connect(mysql);

        char value[505] = {0};
        // 暂时把ID2加到ID1的-group_id里
        sprintf(value, "'%s','%s','%d'", ID1, ID2, -group_id);
        char field[50] = "Id1,Id2,Groupint";
        char table_name[50] = "Friend";
        int state = insert_data(mysql, field, table_name, value);

        if (state == 0) {
            // 插入成功, 尝试通知ID2
            status = friend_add_noti(ID1, ID2, pUser_connect_info);
        } else {
            status = EDATABASE_WRECK;
        }
    }
    response["status"] = status;
    uint8_t *pData = encode(FRIEND_ADD_FIRST_REP, response, len);
    send(pUser_connect_info->user_fd, pData, len, 0);
}

int send_message_to_all(const char *buf, int len,
                        User_connect_info *pUser_connect_info) {
    // Message *message = new Message();
    // strcpy(message->ID1, "12345");
    // strcpy(message->ID2, "guxiao");
    // strcpy(message->content, "hello");
    // strcpy(message->time, "10:00");
    map<int, User_connect_info *>::iterator iter;
    for (iter = ID2info.begin(); iter != ID2info.end(); iter++) {
        int id = iter->first;
        User_connect_info *user = iter->second;
        if (id == pUser_connect_info->user_id) {
            // 不再给发送者发送消息
            continue;
        }
        // response["ID1"] = message->ID1;
        // response["ID2"] = message->ID2;
        // response["content"] = message->content;
        // response["time"] = message->time;
        // TODO:response["state"]=
        // uint8_t *pData = encode("请求头", response, len);
        send(user->user_fd, buf, len, 0);
    }
}

// 好友请求申请(第二次请求)
void friend_add_req2(const char *ID1, const char *ID2, int group_id, int choose,
                     User_connect_info *pUser_connect_info) {
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char value[505] = {0};
    char field[50] = "Id1,Id2,Groupint";
    char table_name[50] = "Friend";
    int state;
    if (choose == 0)  //接受
    {
        sprintf(value, "'%s','%s','%d'", ID2, ID1, group_id);
        state = insert_data(mysql, field, table_name, value);
        sprintf(value, "'%s','%s'", ID1, ID2);
        state = update_data(mysql, table_name, "Groupint=-Groupint", "Id1,Id2",
                            value);
    } else {
        sprintf(value, "'%s','%s'", ID1, ID2);
        state = delete_data(mysql, table_name, "Id1,Id2", value);
    }
    close_connection(mysql);
    int status;
    Json::Value response;
    if (state == 0) {
        status = NORMAL;
    } else {
        status = EDATABASE_WRECK;
    }
    response["status"] = status;
    response["accept"] = choose;
    uint32_t len = 0;
    uint8_t *pData = encode(FRIEND_ADD_SECOND_REP, response, len);
    User_connect_info *pUser_connect_info1 = ID2info[atoi(ID1)];
    send(pUser_connect_info1->user_fd, pData, len, 0);
}

// ID1请求给ID2发消息
void send_message(const char *ID1, const char *ID2, const char *content,
                  User_connect_info *pUser1_connect_info) {
    // int RESPTYPE = MESSAGE_NOTI;
    uint32_t len = 0;  // 数据包长度
    int status = 0;    // 服务器状态
    Json::Value response_to1, response_to2;

    if (is_online(ID2)) {
        // ID2在线
        printf("%s 在线, 准备发送消息\n", ID2);
        User_connect_info *pUser2_connect_info = ID2info[atoi(ID2)];

        const char *time = get_time();
        response_to2["status"] = NORMAL;
        response_to2["ID1"] = ID1;
        response_to2["ID2"] = ID2;
        response_to2["time"] = time;
        response_to2["content"] = content;
        response_to1["status"] = NORMAL;

        uint8_t *pData = encode(MESSAGE_NOTI, response_to2, len);
        if (send(pUser2_connect_info->user_fd, pData, len, 0) > 0) {
            // 确定发送成功之后再插入数据
            insert_chat_content(ID1, ID2, content, 1);
            delete[] pData;

            // 给ID1发送 消息发送反馈
            response_to1["status"] = NORMAL;
            pData = encode(MESSAGE_REP, response_to1, len);
            send(pUser1_connect_info->user_fd, pData, len, 0);
        }
    } else {
        // TODO:离线消息处理
        printf("%s 不在线\n", ID2);
        response_to1["status"] = EOPPOSITE_SIDE_OFFLINE;
        uint8_t *pData = encode(MESSAGE_REP, response_to1, len);
        send(pUser1_connect_info->user_fd, pData, len, 0);

        // 暂时插入数据库
        insert_chat_content(ID1, ID2, content, 0);
    }
    return;
}

/*修改好友分组*/
void change_friend_group(const char *id1, const char *id2, int groupint,
                         User_connect_info *pUser1_connect_info) {
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char value[505] = {0};
    sprintf(value, "'%s','%s'", id1, id2);
    char group[505] = {0};
    sprintf(group, "GroupInt='%d'", groupint);
    int state = update_data(mysql, "Friend", group, "Id1,Id2", value);
    close_connection(mysql);
    int status = NORMAL;
    if (state == 0) {
        status = NORMAL;
    } else {
        status = EDATABASE_WRECK;
    }
    uint32_t len = 0;
    Json::Value response;
    response["status"] = status;
    uint8_t *pData = encode(FRIEND_GROUP_CHANGE_REP, response, len);
    send(pUser1_connect_info->user_fd, pData, len, 0);
}

/*删除好友*/
void delete_friend(const char *id1, const char *id2,
                   User_connect_info *pUser1_connect_info) {
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char value[505] = {0};
    sprintf(value, "'%s','%s'", id1, id2);
    int state = delete_data(mysql, "Friend", "Id1,Id2", value);
    sprintf(value, "'%s','%s'", id2, id1);
    state += delete_data(mysql, "Friend", "Id1,Id2", value);
    close_connection(mysql);
    int status = NORMAL;
    if (state == 0) {
        status = NORMAL;
    } else {
        status = EDATABASE_WRECK;
    }
    uint32_t len = 0;
    Json::Value response;
    response["status"] = status;
    uint8_t *pData = encode(FRIEND_DELETE_REP, response, len);
    send(pUser1_connect_info->user_fd, pData, len, 0);
}

void *handClient(void *arg) {
    char buf[1024] = {0};
    struct User_connect_info *pUser_connect_info =
        static_cast<struct User_connect_info *>(arg);
    int confd = pUser_connect_info->user_fd;
    int len;

    MyProtoDeCode myDecode;

    // 等待用户请求
    while (1) {
        if ((len = recv(confd, buf, sizeof(buf), 0)) == 0) {
            printf("用户 %d 已退出， Ip: %s\n", pUser_connect_info->user_id,
                   pUser_connect_info->ipaddr);
            ID2info.erase(pUser_connect_info->user_id);
            delete[] pUser_connect_info;
            // 向所有人再次更新在线列表
            send_group_list();
            pthread_exit(NULL);
        } else if (len == -1) {
            // TODO: 异常解决
            continue;
        } else {
            // 解码器初始化
            printf("Recive message from IP: %s, fd: %d, begin decode\n",
                   pUser_connect_info->ipaddr, pUser_connect_info->user_fd);
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

            printf("server_id = %d\n", server_id);

            if (server_id == REGISTER_REQ) {
                // 注册
                const char *name = pMsg->body["name"].asCString();
                const char *password = pMsg->body["password"].asCString();
                user_register(name, password, pUser_connect_info);
            } else if (server_id == LOGIN_REQ) {
                // 登录, 已测试
                const char *ID = pMsg->body["ID"].asCString();
                const char *password = pMsg->body["password"].asCString();
                user_login(ID, password, pUser_connect_info);
            } else if (server_id == RECENT_LIST_REQ) {
                // 最近消息列表
                const char *ID = pMsg->body["ID"].asCString();
                send_recent_list(ID, pUser_connect_info);
            } else if (server_id == FRIEND_LIST_REQ) {
                // 好友列表
                const char *ID = pMsg->body["ID"].asCString();
                send_friend_list(ID, pUser_connect_info);
            } else if (server_id == FRIEND_ADD_REQ) {
                // 好友添加
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                int group_id = pMsg->body["group_id"].asInt();
                friend_add_req(ID1, ID2, group_id, pUser_connect_info);
            } else if (server_id == FRIEND_DELETE_REQ) {
                // 好友删除
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                delete_friend(ID1, ID2, pUser_connect_info);
            } else if (server_id == FRIEND_VERIFY_REQ) {
                // ID1处理ID2的添加申请
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                int choose = pMsg->body["choose"].asInt();
                int group_id = pMsg->body["group_id"].asInt();
                friend_add_req2(ID1, ID2, group_id, choose, pUser_connect_info);
            } else if (server_id == FRIEND_GROUP_CHANGE_REQ) {
                // 分组改变
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                int group_id = pMsg->body["group_id"].asInt();
                change_friend_group(ID1, ID2, group_id, pUser_connect_info);
            } else if (server_id == GET_FRIEND_INF_REQ) {
                // 好友信息请求
                const char *ID = pMsg->body["ID"].asCString();
                send_friend_info(ID, pUser_connect_info);
            } else if (server_id == GET_MY_INF_REQ) {
                // 自身信息
                const char *ID = pMsg->body["ID"].asCString();
                send_user_info(ID, pUser_connect_info);
            } else if (server_id == CHANGE_MY_INF_REQ) {
                // 修改个人信息
                const char *ID = pMsg->body["ID"].asCString();
                int photo_id = pMsg->body["photo_id"].asInt();
                const char *name = pMsg->body["name"].asCString();
                int sex_id = pMsg->body["sex_id"].asInt();
                const char *tel = pMsg->body["tel"].asCString();
                const char *question = pMsg->body["question"].asCString();
                const char *answer = pMsg->body["answer"].asCString();
                const char *description = pMsg->body["description"].asCString();
                update_user_info(ID, name, photo_id, sex_id, tel, description,
                                 question, answer, pUser_connect_info);
            } else if (server_id == MESSAGE_SEND) {
                // 消息发送
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                const char *content = pMsg->body["content"].asCString();
                send_message(ID1, ID2, content, pUser_connect_info);
            } else if (server_id == HISTORY_MESSAGE_REQ) {
                // TODO:聊天记录
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
            } else if (server_id == FILE_TRANS_REQ) {
                // 文件传输!!!!!!!!!!!!!!!!!!!!!!!!!
                const char *ID1 = pMsg->body["ID1"].asCString();
                const char *ID2 = pMsg->body["ID2"].asCString();
                const char *file_name = pMsg->body["file_name"].asCString();
                file_trans(ID1, ID2, file_name, pUser_connect_info);
            } else if (server_id == MESSAGE_GROUP_SEND) {
                // 局域网聊天
                send_message_to_all(buf, len, pUser_connect_info);
            }
        }
        // send(confd,buf,strlen(buf),0);
    }
}

int PORT = 5117;

int main() {
    char *IP = get_my_ip();
    printf("%s\n", IP);

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
