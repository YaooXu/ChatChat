#include "info.h"
#include "ui_info.h"
#include "../utils/chat_proto.h"
#include "jsoncpp/json/json.h"
#include<stdio.h>
info::info(QTcpSocket *p_socket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
     this->setFixedSize(400,524);
    this->ptr_socket = p_socket;
    pt=new repository();
    ui->photo->setIcon(QPixmap(":/src/img/1.png"));
    ui->photo->setIconSize(QSize(200,200));
    connect(pt,SIGNAL(sendsignal(int)),this,SLOT(change_photo(int)));
    //connect(ui->update,SIGNAL(clicked()),this,SLOT(on_pushButton_clicked()));
   // connect(ui->submit,SIGNAL(clicked()),this,SLOT(on_submit_clicked()));

}

info::~info()
{
    delete ui;
}

void info::on_submit_clicked()//读数据
{
    name=ui->name_edit->text();
    ans=ui->ans_edit->text();
    sex=ui->sex_edit->text();
    tel=ui->tel_edit->text();
    mood=ui->mood_edit->text();
    question=ui->ques_edit->text();
    //photo=imagename;
    char *p_name=(char*)name.data();
    char *p_ans=(char*)ans.data();
    char *p_sex=(char*)sex.data();
    char *p_tel=(char*)tel.data();
    char *p_mood=(char*)mood.data();
    char *p_question=(char*)question.data();
    Json::Value message;
    message["name"]=p_name;
    message["answer"]=p_ans;
    int sex_id;
    if(sex=="未知")
       sex_id=0;
    if(sex=="男")
        sex_id=1;
    if(sex=="女")
        sex_id=2;
    message["sex_id"]=sex_id;
    message["tel"]=p_tel;
    message["description"]=p_mood;
    message["question"]=p_question;
    message["photo_id"]=photo_num;
    uint32_t len = 0;
    uint8_t *pData = encode(CHANGE_MY_INF_REQ, message, len);
    ptr_socket->write((char*)pData,len);

}

void info::on_photo_clicked()
{

   pt->show();
}


void info::on_update_clicked()
{

    ui->name_edit->setEnabled(true);
    //ui->Id_edit->setEnabled(true);
    ui->ans_edit->setEnabled(true);
    ui->sex_edit->setEnabled(true);
    ui->tel_edit->setEnabled(true);
    ui->mood_edit->setEnabled(true);
    ui->ques_edit->setEnabled(true);
}
void info::change_photo(int x){
    QString imagename;
    photo_num=x;
    imagename.sprintf(":/src/img/%d.png",x);
    emit send_signal(photo_num);
    ui->photo->setIcon(QPixmap(imagename));
    ui->photo->setIconSize(QSize(200,200));
}
void info::updat_info(User_info * p){
    ui->Id_edit->setText(p->ID);
    ui->name_edit->setText(p->name);
    if(p->sex_id==0)
        ui->sex_edit->setText("未知");
    if(p->sex_id==1)
        ui->sex_edit->setText("男");
    if(p->sex_id=2)
        ui->sex_edit->setText("女");
    ui->ans_edit->setText(p->answer);
    ui->tel_edit->setText(p->tel);
    ui->mood_edit->setText(p->description);
    ui->ques_edit->setText(p->question);
    photo_num=p->photo_id;
    QString image_name1;
    image_name1.sprintf(":/src/img/%d.png",photo_num);
    ui->photo->setIcon(QPixmap(image_name1));

}
