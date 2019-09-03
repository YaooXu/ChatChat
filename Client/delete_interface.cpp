#include "delete_interface.h"
#include "ui_delete_interface.h"
#include "QDebug"

delete_interface::delete_interface(QWidget *parent,QString userID, QString ID2,QTcpSocket *p_socket) :
    QDialog(parent),
    ui(new Ui::delete_interface)
{
    ui->setupUi(this);
    ID1=userID;
    ID2_temp=ID2;
    p_delfri_sock=p_socket;
}

delete_interface::~delete_interface()
{
    delete ui;
}



void delete_interface::on_pushButton_yes_clicked()
{
    //qDebug()<<ID2_temp;
    uint32_t len=0;
    Json::Value message;
    message["ID1"]=ID1.toStdString().c_str();
    message["ID2"]=ID2_temp.toStdString().c_str();
    uint8_t *pData=encode(FRIEND_DELETE_REQ,message,len);
    p_delfri_sock->write((char*)pData,len);

    close();
}

void delete_interface::on_pushButton_no_clicked()
{
    close();
}
