#include"mysql_helper.h"



int getChatContent()
{
    char id1[505]={"123456"};
    char id2[505]={"123672"};
    MYSQL *mysql = mysql_init(NULL);           
    if (!mysql) {
        my_error("mysql_init", __LINE__);
    }
    mysql_connect(mysql);
    char sqlStr[1024]={0};
	sprintf(sqlStr, "select Id1,Id2,Time,Content from ChatContent where Id1='%s' and Id2='%s' or Id1='%s' and Id2='%s'",id1,id2,id2,id1);
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
int addFriend()
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
    sprintf(value,"%s,%s,%s",id1,id2,group1);
    char field[50]="Id1,Id2,Groupint";
    char table_name[50]="Friend";
    insert_data(mysql,field,table_name,value);
    sprintf(value,"%s,%s,%s",id2,id1,group2);
    insert_data(mysql,field,table_name,value);
    close_connection(mysql);
}



// scp -P 22 ./file_trans.c root@182.92.193.104:./


int main()
{
  getChatContent();
    return 0;
}