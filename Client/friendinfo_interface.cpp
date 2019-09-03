#include "friendinfo_interface.h"
#include "ui_friendinfo_interface.h"

friendinfo_interface::friendinfo_interface(QWidget *parent,QString ID2,QTcpSocket *p_socket) :
    QDialog(parent),
    ui(new Ui::friendinfo_interface)
{
    ui->setupUi(this);
    ID2_temp=ID2;
    p_finfo_sock=p_socket;

    uint32_t len=0;
    Json::Value message;
    message["ID2"]=ID2_temp.toStdString().c_str();
    uint8_t *pData=encode(GET_FRIEND_INF_REQ,message,len);
    p_finfo_sock->write((char*)pData,len);


}

friendinfo_interface::~friendinfo_interface()
{
    delete ui;
}
