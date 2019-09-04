#include "addfri_interface.h"
#include "ui_addfri_interface.h"

addfri_interface::addfri_interface(QWidget *parent,QString userID,QTcpSocket *p_socket) :
    QDialog(parent),
    ui(new Ui::addfri_interface)
{
    ui->setupUi(this);
    ID1=userID;
    p_addfri_sock=p_socket;
    //p_socket->connectToHost("192.168.137.129", 8888);
}

addfri_interface::~addfri_interface()
{
    delete ui;
}

void addfri_interface::on_pushButton_clicked()
{
    QString ID2=ui->lineEdit->text();
    qDebug()<<ID2;
    int groupID=ui->comboBox->currentIndex()+1;
    qDebug()<<groupID;

    uint32_t len=0;
    Json::Value message;
    message["ID1"]=ID1.toStdString().c_str();
    message["ID2"]=ID2.toStdString().c_str();
    message["group_id"]=groupID;
    uint8_t *pData=encode(FRIEND_ADD_REQ,message,len);
    p_addfri_sock->write((char*)pData,len);


    close();

}
