#include "regroup_interface.h"
#include "ui_regroup_interface.h"
#include "QDebug"

regroup_interface::regroup_interface(QWidget *parent,QString userid, QString ID2,QTcpSocket *p_socket) :
    QDialog(parent),
    ui(new Ui::regroup_interface)
{
    ui->setupUi(this);
    ID1=userid;
    ID2_temp=ID2;
    p_regroup_socket=p_socket;
}

regroup_interface::~regroup_interface()
{
    delete ui;
}

void regroup_interface::on_friend_pushButton_clicked()
{
    //qDebug()<<ID2_temp;
    int groupID=1;

    uint32_t len=0;
    Json::Value message;
    message["ID1"]=ID1.toStdString().c_str();
    message["ID2"]=ID2_temp.toStdString().c_str();
    message["group_id"]=groupID;
    uint8_t *pData=encode(FRIEND_GROUP_CHANGE_REQ,message,len);
    p_regroup_socket->write((char*)pData,len);

    close();
}

void regroup_interface::on_family_pushButton_clicked()
{
    //qDebug()<<ID2_temp;
    int groupID=2;

    uint32_t len=0;
    Json::Value message;
    message["ID1"]=ID1.toStdString().c_str();
    message["ID2"]=ID2_temp.toStdString().c_str();
    message["group_id"]=groupID;
    uint8_t *pData=encode(FRIEND_GROUP_CHANGE_REQ,message,len);
    p_regroup_socket->write((char*)pData,len);

    close();
}

void regroup_interface::on_colleague_pushButton_clicked()
{
    //qDebug()<<ID2_temp;
    int groupID=3;

    uint32_t len=0;
    Json::Value message;
    message["ID1"]=ID1.toStdString().c_str();
    message["ID2"]=ID2_temp.toStdString().c_str();
    message["group_id"]=groupID;
    uint8_t *pData=encode(FRIEND_GROUP_CHANGE_REQ,message,len);
    p_regroup_socket->write((char*)pData,len);

    close();
}

void regroup_interface::on_classmate_pushButton_clicked()
{
    //qDebug()<<ID2_temp;
    int groupID=4;

    uint32_t len=0;
    Json::Value message;
    message["ID1"]=ID1.toStdString().c_str();
    message["ID2"]=ID2_temp.toStdString().c_str();
    message["group_id"]=groupID;
    uint8_t *pData=encode(FRIEND_GROUP_CHANGE_REQ,message,len);
    p_regroup_socket->write((char*)pData,len);

    close();
}

void regroup_interface::on_blacklist_pushButton_clicked()
{
    //qDebug()<<ID2_temp;
    int groupID=5;

    uint32_t len=0;
    Json::Value message;
    message["ID1"]=ID1.toStdString().c_str();
    message["ID2"]=ID2_temp.toStdString().c_str();
    message["group_id"]=groupID;
    uint8_t *pData=encode(FRIEND_GROUP_CHANGE_REQ,message,len);
    p_regroup_socket->write((char*)pData,len);

    close();
}
