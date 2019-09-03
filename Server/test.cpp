#include "../utils/chat_proto.cpp"
#include "mysql_helper.h"

void send_friend_list() {
    const char *ID = "123456";
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
        "select Groupint,Id,Name,Photo,Sex,Email,Description,LastLoginTime  "
        "from Friend join User where User.Id=Friend.id2 and Friend.id1='%s'",
        ID);
    printf("%s\n", sqlStr);
    if (mysql_query(mysql, sqlStr) != 0) {
        // 查询失败,直接返回
        printf("%s\n", mysql_error(mysql));
        close_connection(mysql);

        status = EDATABASE_WRECK;
        response["status"] = EDATABASE_WRECK;
        uint8_t *pData = encode(RESPTYPE, response, len);
        // send(pUser_conect_info->user_fd, pData, len, 0);
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
        map<int, int> ID2info;
        ID2info[123672] = 1;

        for (int i = 0; i < num_row; i++) {
            mysql_row = mysql_fetch_row(result);

            for (int j = 0; j < num_col; j++) {
                printf("[Row %d,Col %d]==>[%s], is NULL:%d\n", i, j,
                       mysql_row[j], mysql_row[j] == NULL);
            }

            user["ID"] = mysql_row[1];
            user["photo_id"] = mysql_row[3] == NULL ? 0 : atoi(mysql_row[3]);
            user["name"] = mysql_row[2];
            // 当指针为NULL的时候直接赋值会段错误!
            user["sex_id"] = mysql_row[4] == NULL ? 0 : atoi(mysql_row[4]);
            user["tel"] = mysql_row[8] == NULL ? "" : mysql_row[8];
            user["description"] = mysql_row[6] == NULL ? "" : mysql_row[6];
            user["last_login_time"] = mysql_row[7] == NULL ? "" : mysql_row[7];
            user["group_id"] = mysql_row[0] == NULL ? 0 : atoi(mysql_row[0]);
            int online = ID2info.count(atoi(mysql_row[1]));
            user["online"] = online;

            response["list"].append(user);
        }

        response["status"] = status;
        uint8_t *pData = encode(RESPTYPE, response, len);
        // send(pUser_conect_info->user_fd, pData, len, 0);

        // 解包测试
        char *buf = (char *)pData;
        int num = 0;
        User_in_list *pUser_in_list = decode2User_list(buf, len, num);
        for (int i = 0; i < num; i++) {
            printf("%s, %s, %d, %d, %d\n", pUser_in_list[i].name,
                   pUser_in_list[i].description, pUser_in_list[i].photo_id,
                   pUser_in_list[i].group_id, pUser_in_list[i].online);
        }
    }
}

/*最近联系人*/
int get_recent_user() {
    int status, RESPTYPE = RECENT_LIST_REP;
    uint32_t len = 0;
    char ID[50] = {"123456"};
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char sqlStr[1024] = {0};
    sprintf(sqlStr,
            "select tem.id,tem.Content,tem.Time FROM ((select Id1 as "
            "id,Content,Time  from ChatContent where Id2='%s') union (select "
            "Id2 as id,Content,Time  from ChatContent where Id1='%s')  order "
            "by Time desc)as tem group by tem.id",
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
        printf("row: %d,col: %d\n", num_row, num_col);
        for (int i = 0; i < num_row; i++) {
            mysql_row = mysql_fetch_row(result);
            for (int j = 0; j < num_col; j++) {
                printf("[Row %d,Col %d]==>[%s]\n", i, j, mysql_row[j]);
            }
            user["ID"] = mysql_row[0];
            user["last_message"] = mysql_row[1];
            user["time"] = mysql_row[2];
            response["list"].append(user);
        }
    } while (0);

    response["status"] = status;
    uint8_t *pData = encode(RESPTYPE, response, len);
    // send(pUser_conect_info->user_fd, pData, len, 0);

    // 解包测试
    char *buf = (char *)pData;
    int num = 0;
    User_in_recent *pUser_in_recent = decode2User_recent(buf, len, num);
    for (int i = 0; i < num; i++) {
        printf("%s, %s, %s\n", pUser_in_recent[i].ID,
               pUser_in_recent[i].last_message, pUser_in_recent[i].time);
    }
}

/*获取聊天记录*/
int get_chat_content() {
    char id1[505] = {"123456"};
    char id2[505] = {"123672"};
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char sqlStr[1024] = {0};
    sprintf(sqlStr,
            "select Id1,Id2,Time,Content from ChatContent where "
            "Id1='%s' and Id2='%s' or Id1='%s' and Id2='%s'",
            id1, id2, id2, id1);
    printf("%s\n", sqlStr);
    if (mysql_query(mysql, sqlStr) != 0) {
        printf("%s\n", mysql_error(mysql));
        close_connection(mysql);
        return -1;
    }
    MYSQL_RES *result;
    result = mysql_store_result(mysql);
    close_connection(mysql);
    if (result == NULL) {
        printf("%s\n", mysql_error(mysql));
        return -1;
    }
    int num_row, num_col;
    MYSQL_ROW mysql_row;
    num_row = mysql_num_rows(result);
    num_col = mysql_num_fields(result);
    printf("row: %d,col: %d\n", num_row, num_col);
    for (int i = 0; i < num_row; i++) {
        mysql_row = mysql_fetch_row(result);
        for (int j = 0; j < num_col; j++) {
            printf("[Row %d,Col %d]==>[%s]\n", i, j, mysql_row[j]);
        }
    }
}

/*好友申请通知*/
int add_friend_info() {
    int online = 1;
    User_connect_info *friend_connect_info = new User_connect_info();
    strcpy(friend_connect_info->ipaddr, "127.0.0.1");
    friend_connect_info->user_id = 996190;
    friend_connect_info->user_fd = 888;
    const char *ID = "123456";
    int status, RESPTYPE = FRIEND_ADD_REP;
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
            "select Id,Name,Photo,Sex,Email,Description,LastLoginTime "
            "from User where Id='%s'",
            ID);
    printf("%s\n", sqlStr);
    do {
        if (mysql_query(mysql, sqlStr) != 0) {
            // 查询失败,直接返回
            printf("%s\n", mysql_error(mysql));
            close_connection(mysql);

            status = EDATABASE_WRECK;
            break;
        }
    } while (0);
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
            user["ID"] = mysql_row[0];
            user["photo_id"] = mysql_row[2] == NULL ? 0 : atoi(mysql_row[2]);
            user["name"] = mysql_row[1];
            // 当指针为NULL的时候直接赋值会段错误!
            user["sex_id"] = mysql_row[3] == NULL ? 0 : atoi(mysql_row[3]);
            user["tel"] = mysql_row[7] == NULL ? "" : mysql_row[7];
            user["description"] = mysql_row[5] == NULL ? "" : mysql_row[5];
            user["last_login_time"] = mysql_row[6] == NULL ? "" : mysql_row[6];
            user["online"] = online;
            response["list"].append(user);
        }

        response["status"] = status;
        uint8_t *pData = encode(RESPTYPE, response, len);
        // send(pUser_conect_info->user_fd, pData, len, 0);

        // 解包测试
        char *buf = (char *)pData;
        int num = 0;
        User_in_list *pUser_in_list = decode2User_list(buf, len, num);
        for (int i = 0; i < num; i++) {
            printf("%s, %s, %d, %d, %d\n", pUser_in_list[i].name,
                   pUser_in_list[i].description, pUser_in_list[i].photo_id,
                   pUser_in_list[i].sex_id, pUser_in_list[i].online);
        }
    }
}
/*添加好友*/
int add_friend() {
    char id1[505] = {"123456"};
    char id2[505] = {"123672"};
    char group1[505] = {"0"};
    char group2[505] = {"1"};
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char value[505] = {0};
    sprintf(value, "'%s','%s','%s'", id1, id2, group1);
    char field[50] = "Id1,Id2,Groupint";
    char table_name[50] = "Friend";
    int state = insert_data(mysql, field, table_name, value);
    // sprintf(value, "'%s','%s','%s'", id2, id1, group2);
    state += insert_data(mysql, field, table_name, value);
    close_connection(mysql);
}
/*删除好友*/
int delete_friend() {
    char id1[505] = {"123456"};
    char id2[505] = {"123672"};
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
}
/*修改好友分组*/
int change_friend_group() {
    char id1[505] = {"123456"};
    char id2[505] = {"123672"};
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char value[505] = {0};
    sprintf(value, "'%s','%s'", id1, id2);
    int state = update_data(mysql, "Friend", "GroupInt='2'", "Id1,Id2", value);
    close_connection(mysql);
}
/*新增一条聊天记录*/
int insert_chat_content() {
    char id1[505] = {"123456"};
    char id2[505] = {"123672"};
    int readstate1 = 0;
    int readstate2 = 1;
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char value[505] = {0};
    char content[505] = {"你好"};
    sprintf(value, "'%s','%s','%d','%d',NOW(),'%s'", id1, id2, readstate1,
            readstate2, content);
    insert_data(mysql, "Id1,Id2,ReadState1,ReadState2,Time,Content",
                "ChatContent", value);
    close_connection(mysql);
}
/*用户信息更新*/
int update_user_info() {
    char ID[50] = {"123456"};
    char name[50] = {"lisa"};
    int photo = 0;
    int sex = 2;
    char email[50] = {"lisa@163.com"};
    char telephone[50] = {""};
    char value[505] = {0};
    char description[505] = {"喵喵喵"};
    sprintf(value,
            "Name='%s',Photo='%d',Sex='%d',Email='%s',Telephone='%s',"
            "Description='%s'",
            name, photo, sex, email, telephone, description);
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char ids[505];
    sprintf(ids, "'%s'", ID);
    update_data(mysql, "User", value, "Id", ids);
    mysql_close(mysql);
}

void get_user_information() {
    const char *ID = "123456";
    // select * from Friend join User where Friend.Id1=User.Id and Id="123456";
    int status, RESPTYPE = GET_MY_INF_REP;  // TODO:这个状态码要改
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
        // send(pUser_conect_info->user_fd, pData, len, 0);
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
        // send(pUser_conect_info->user_fd, pData, len, 0);
        // Name,Photo,Sex,Email,Telephone,Question,Answer,Description,LastLoginTime
        // 解包测试
        char *buf = (char *)pData;
        int num = 0;
        User_info *pUser_info = decode2User_info(buf, len, num);
        for (int i = 0; i < num; i++) {
            printf("%s, %d,%s, %d, %s, %s, %s, %s, %s, %s\n", pUser_info[i].ID,
                   pUser_info[i].photo_id, pUser_info[i].name,
                   pUser_info[i].sex_id, pUser_info[i].tel,
                   pUser_info[i].question, pUser_info[i].answer,
                   pUser_info[i].description, pUser_info[i].last_login_time);
        }
    }
}

int main() {
    add_friend_info();
    return 0;
}