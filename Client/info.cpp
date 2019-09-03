#include "info.h"
#include "ui_info.h"
#include "../utils/chat_proto.h"
#include "jsoncpp/json/json.h"
#include<stdio.h>
info::info(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info)
{
    ui->setupUi(this);
     this->setFixedSize(400,524);
    pt=new repository();
    ui->photo->setIcon(QPixmap(":/new/prefix1/1.png"));
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
    message["sex"]=p_sex;
    message["tel"]=p_tel;
    message["description"]=p_mood;
    message["question"]=p_question;

    uint32_t len = 0;
    uint8_t *pData = encode(CHANGE_MY_INF_REQ, message, len);

    //send(sockfd, pData, len, 0);
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
    imagename.sprintf(":/new/prefix1/%d.png",x);
    ui->photo->setIcon(QPixmap(imagename));
    ui->photo->setIconSize(QSize(200,200));
}
