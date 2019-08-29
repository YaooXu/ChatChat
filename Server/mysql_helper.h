#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <mysql/mysql.h>  
#include "mysql_helper.c"


void my_error(const char *err_string, int line);    // 错误处理函数
void mysql_connect(MYSQL *mysql);                   // 连接mysql数据库
int insert_data(MYSQL *mysql, char field[],char table_name[],char message[]);              // 插入数据
int update_data(MYSQL *mysql ,char table_name[],char new_field_and_value[],char find_field[],char find_value[]);        // 修改数据
int delete_data(MYSQL *mysql,char table_name[],char del_name[],char del_value[]);//删除数据
void close_connection(MYSQL *mysql);                // 关闭mysql数据库

