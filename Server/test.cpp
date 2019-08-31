#include"mysql_helper.h"


/* 获得好友列表*/
int get_friend_list()
{
    char id[50]={"123456"};
    //select * from Friend join User where Friend.Id1=User.Id and Id="123456";
    MYSQL *mysql = mysql_init(NULL);  
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char sqlStr[1024]={0};
    sprintf(sqlStr,"select Groupint,Id,Name,Photo,Sex,Email,Description,LastLoginTime  from Friend join User where User.Id=Friend.id2 and Friend.id1='%s'",id);
    printf("%s\n",sqlStr);
    if(mysql_query(mysql,sqlStr) != 0)
	{
		printf("%s\n",mysql_error(mysql));
		close_connection(mysql);
		return -1;
	}
    MYSQL_RES *result;
	result = mysql_store_result(mysql);
	close_connection(mysql);
    if(result == NULL)
	{
		printf("%s\n",mysql_error(mysql));
		return -1;
	}
    int num_row,num_col;
    MYSQL_ROW mysql_row;
    num_row=mysql_num_rows(result);
    num_col=mysql_num_fields(result);
    printf("row: %d,col: %d\n",num_row,num_col);
    for(int i=0;i<num_row;i++)
        {
        mysql_row=mysql_fetch_row(result);
        for(int j=0;j<num_col;j++)
            {
                 printf("[Row %d,Col %d]==>[%s]\n",i,j,mysql_row[j]);
            }
        } 

}
/*最近联系人*/
int get_recent_user()
{
    char id[50]={"123456"};
    MYSQL *mysql = mysql_init(NULL);  
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char sqlStr[1024]={0};
    sprintf(sqlStr,"select Id1,Id2,Content from ChatContent where Id1='%s' or Id2 ='%s' order by Time desc limit 1;",id,id);
    printf("%s\n",sqlStr);
    if(mysql_query(mysql,sqlStr) != 0)
	{
		printf("%s\n",mysql_error(mysql));
		close_connection(mysql);
		return -1;
	}
    MYSQL_RES *result;
	result = mysql_store_result(mysql);
	close_connection(mysql);
    if(result == NULL)
	{
		printf("%s\n",mysql_error(mysql));
		return -1;
	}
    int num_row,num_col;
    MYSQL_ROW mysql_row;
    num_row=mysql_num_rows(result);
    num_col=mysql_num_fields(result);
    printf("row: %d,col: %d\n",num_row,num_col);
    for(int i=0;i<num_row;i++)
        {
        mysql_row=mysql_fetch_row(result);
        for(int j=0;j<num_col;j++)
            {
                 printf("[Row %d,Col %d]==>[%s]\n",i,j,mysql_row[j]);
            }
        }  

}

/*获取聊天记录*/
int get_chat_content()
{
    char id1[505]={"123456"};
    char id2[505]={"123672"};
    MYSQL *mysql = mysql_init(NULL);           
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char sqlStr[1024]={0};
	sprintf(sqlStr, "select Id1,Id2,ReadState,Time,Content from ChatContent where Id1='%s' and Id2='%s' or Id1='%s' and Id2='%s'",id1,id2,id2,id1);
    printf("%s\n",sqlStr);
    if(mysql_query(mysql,sqlStr) != 0)
	{
		printf("%s\n",mysql_error(mysql));
		close_connection(mysql);
		return -1;
	}
    MYSQL_RES *result;
	result = mysql_store_result(mysql);
	close_connection(mysql);
    if(result == NULL)
	{
		printf("%s\n",mysql_error(mysql));
		return -1;
	}
    int num_row,num_col;
    MYSQL_ROW mysql_row;
    num_row=mysql_num_rows(result);
    num_col=mysql_num_fields(result);
    printf("row: %d,col: %d\n",num_row,num_col);
    for(int i=0;i<num_row;i++)
        {
        mysql_row=mysql_fetch_row(result);
        for(int j=0;j<num_col;j++)
            {
                 printf("[Row %d,Col %d]==>[%s]\n",i,j,mysql_row[j]);
            }
        }  
}
/*添加好友*/
int add_friend()
{
    char id1[505]={"123456"};
    char id2[505]={"123672"};
    char group1[505]={"0"};
    char group2[505]={"1"};
    MYSQL *mysql = mysql_init(NULL);           
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char value[505]={0};
    sprintf(value,"'%s','%s','%s'",id1,id2,group1);
    char field[50]="Id1,Id2,Groupint";
    char table_name[50]="Friend";
    int state=insert_data(mysql,field,table_name,value);
    sprintf(value,"'%s','%s','%s'",id2,id1,group2);
    state+=insert_data(mysql,field,table_name,value);
    close_connection(mysql);
}
/*删除好友*/
int delete_friend()
{
    char id1[505]={"123456"};
    char id2[505]={"123672"};
    MYSQL *mysql = mysql_init(NULL);  
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char value[505]={0};
    sprintf(value,"'%s','%s'",id1,id2);
    int state=delete_data(mysql,"Friend","Id1,Id2",value);
    sprintf(value,"'%s','%s'",id2,id1);
    state+=delete_data(mysql,"Friend","Id1,Id2",value);
    close_connection(mysql);
}
/*修改好友分组*/
int change_friend_group()
{
    char id1[505]={"123456"};
    char id2[505]={"123672"};
    MYSQL *mysql = mysql_init(NULL);  
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char value[505]={0};
    sprintf(value,"'%s','%s'",id1,id2);
    int state=update_data(mysql,"Friend","GroupInt='2'","Id1,Id2",value);
    close_connection(mysql);
}
/*新增一条聊天记录*/
int insert_chat_content()
{
    char id1[505]={"123456"};
    char id2[505]={"123672"};
    int readstate=0;
    MYSQL *mysql = mysql_init(NULL);  
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char value[505]={0};
    char content[505]={"你好"};
    sprintf(value,"'%s','%s','%d',NOW(),'%s'",id1,id2,readstate,content);
    insert_data(mysql,"Id1,Id2,ReadState,Time,Content","ChatContent",value);
    close_connection(mysql);

}
/*用户信息更新*/
int update_user_info()
{
    char id[50] ={"996190"};
    char name[50]={"lisa"};
    int photo=0;
    int sex=2;
    char email[50]={"lisa@163.com"};
    char telephone[50]={""};
    char value[505]={0};
    char description[505]={"喵喵喵"};
    sprintf(value,"Name='%s',Photo='%d',Sex='%d',Email='%s',Telephone='%s',Description='%s'",name,photo,sex,email,telephone,description);
    MYSQL *mysql = mysql_init(NULL);  
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char ids[505];
    sprintf(ids,"'%s'",id);
    update_data(mysql,"User",value,"Id",ids);
    mysql_close(mysql);
}



int main()
{
    get_recent_user();
    return 0;
}