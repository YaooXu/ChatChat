#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <mysql/mysql.h>  


#define HOST    "localhost"
#define USER    "root"
#define PASSWD  "123456"
#define DB_NAME "TESTDB"

void my_error(const char *err_string, int line);    // 错误处理函数
void mysql_connect(MYSQL *mysql);                   // 连接mysql数据库
int insert_data(MYSQL *mysql, char field[],char table_name[],char message[]);                 // 插入数据
int update_data(MYSQL *mysql ,char table_name[],char new_field_and_value[],char find_field[],char find_value[]);        // 修改数据
int delete_data(MYSQL *mysql,char table_name[],char del_name[],char del_value[]);//删除数据
void close_connection(MYSQL *mysql);                // 关闭mysql数据库


// int main()
// {
//     int num;

//     MYSQL *mysql = mysql_init(NULL);           
//     if (!mysql) {
//         my_error("mysql_init", __LINE__);
//     }
//     mysql_connect(mysql);
//     while(1)
//     {    scanf("%d",&num);
//         if (num==0){
//         char field[500]={0};
//         char table_name[500]={0};
//         char message[500]={0};
//         printf("void insert_data(MYSQL *mysql, char field[],char table_name[],char message[]);\n");
//         scanf("%s%s%s",field,table_name,message);
//         insert_data(mysql,field,table_name,message);
//         }
//         else if(num==1)
//         {
//         char table_name[505]={0};
//         char new_field[505]={0};
//         char new_value[505]={0};
//         char find_field[505]={0};
//         char find_value[505]={0};
//         printf("int update_data(MYSQL *mysql ,char table_name[],char new_value[],char find_field[],char find_value[]);\n");
//         scanf("%s%s%s%s",table_name,new_value,find_field,find_value);
//         update_data(mysql,table_name,new_value,find_field,find_value);
//         }
//         else if(num==2)
//         {
//         char table_name[505]={0};
//         char del_name[505]={0};
//         char del_value[505]={0};
//         printf("int delete_data(MYSQL *mysql,char table_name[],char del_name[],char del_value[]);\n");
//         scanf("%s%s%s",table_name,del_name,del_value);
//         delete_data(mysql,table_name,del_name,del_value);
//         }
    
    
//     }
// }



void my_error(const char *err_string, int line) 
{
    fprintf(stderr, "line: %d ", line);
    perror(err_string);
    exit(1);
}

/* 连接mysql数据库 */  
void mysql_connect(MYSQL *mysql)
{  
    if(!mysql_real_connect(mysql, HOST, USER, PASSWD, DB_NAME, 0, NULL, 0)) {  
        printf("Failed to connect:%s\n", mysql_error(mysql));  
        my_error("mysql_real_connect", __LINE__);
    }  
    printf("Connect database sucessfully!\n\n");
}  

/* 插入数据 field用逗号分隔开
返回值为0表示成功插入
message example：sprintf(message,"'%s','%s'",uName,pWord);
 */
int insert_data(MYSQL *mysql, char field[],char table_name[],char message[])
{  
    int t;  
    char *head = "insert into ";  
    char query[200];
    char *left = "(";  
    char *right = ") ";  
    char *values = "values";  
    /* 把几个变量字符串连接成一个完整的mysql命令 */  
    sprintf(query, "%s%s%s%s%s%s%s%s%s", head, table_name, left, 
                            field, right, values, left, message, right);
    printf("%s\n", query);  

    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("Failed to query: %s\n", mysql_error(mysql));  
        return -1;
    }  
    printf("\nInsert sucessfully!\n\n");
    return 0;
}  

/* 删除数据 
table_name:要删除的数据所在表
del_name和del_value:要删除的条件列名和值
返回值为0表示删除成功
*/
int delete_data(MYSQL *mysql,char table_name[],char del_name[],char del_value[])
{  
    int t;
    char *head = "delete from ";  
    char query[200];  
    sprintf(query, "%s%s where %s =\"%s\"", head, table_name, del_name,del_value);
    printf("%s\n", query);

    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("Failed to query: %s\n", mysql_error(mysql));  
        return -1;
    }
    printf("Delete data sucessfully!\n");  
    return 0;
}  

/* 更新数据 为了实现同时更新多组数据写的不是很好看
成功更新返回0
table_name:要更新的表名
new_value:set要更新的值具体见下方格式
find_field和find_value:寻找的列名和值
注意 new_value 格式应为 sex='1', country='china' ,name='guxiao'这样的
*/
int update_data(MYSQL *mysql ,char table_name[],char new_field_and_value[],char find_field[],char find_value[])
{  
    int t;
    char *head = "update ";
    char query[100];
    sprintf(query, "%s%s set %s where %s='%s'", head, table_name, new_field_and_value,find_field, find_value);
    printf("%s\n", query);

    t = mysql_real_query(mysql, query, strlen(query));
    if (t) {  
        printf("Failed to query: %s\n", mysql_error(mysql));  
        return -1;
    }
    printf("Update data sucessfully!\n");
    return 0;
}

void close_connection(MYSQL *mysql)
{
    mysql_close(mysql);
}