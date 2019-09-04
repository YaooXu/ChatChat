#include "receive_addfri_interface.h"
#include "ui_receive_addfri_interface.h"

receive_addfri_interface::receive_addfri_interface(QWidget *parent,QString userID,QString claimer_ID, QString claimer_Name,QTcpSocket *p_socket) :
    QDialog(parent),
    ui(new Ui::receive_addfri_interface)
{
    ui->setupUi(this);
    ID1=claimer_ID;
    ID2=userID;
    Name=claimer_Name;
    ui->label_ID->setText(ID1);
    ui->label_Name->setText(Name);
    p_receive_addri_sock=p_socket;
}

receive_addfri_interface::~receive_addfri_interface()
{
    delete ui;
}

void receive_addfri_interface::on_acceptButton_clicked()
{
    int group_ID=ui->comboBox->currentIndex()+1;
    int i=0;

    uint32_t len=0;
    Json::Value message;
    message["ID1"]=ID1.toStdString().c_str();
    message["ID2"]=ID2.toStdString().c_str();
    message["group_id"]=group_ID;
    message["choose"]=i;
    uint8_t *pData=encode(FRIEND_VERIFY_REQ,message,len);

    p_receive_addri_sock->write((char*)pData,len);

    close();
}

void receive_addfri_interface::on_refuseButton_clicked()
{
    int group_ID=ui->comboBox->currentIndex()+1;
    int i=1;

    uint32_t len=0;
    Json::Value message;
    message["ID1"]=ID1.toStdString().c_str();
    message["ID2"]=ID2.toStdString().c_str();
    message["group_id"]=group_ID;
    message["choose"]=i;
    uint8_t *pData=encode(FRIEND_VERIFY_REQ,message,len);
    qDebug()<<pData;
    p_receive_addri_sock->write((char*)pData,len);

    close();
}
