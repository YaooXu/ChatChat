#include "friendinfo_interface.h"
#include "ui_friendinfo_interface.h"

friendinfo_interface::friendinfo_interface(QWidget *parent,QString fri_ID,int fri_Icon,QString fri_Name,int fri_Sex,QString fri_des,QString fri_tel) :
    QDialog(parent),
    ui(new Ui::friendinfo_interface)
{
    ui->setupUi(this);
    ID=fri_ID;
    Icon=fri_Icon;
    Name=fri_Name;
    Sex=fri_Sex;
    Description=fri_des;
    tel=fri_tel;


    ui->label_ID->setText(ID);
    ui->label_name->setText(Name);
    if(Sex==0)
    {
        ui->label_sex->setText("未知");
    }
    if(Sex==1)
    {
        ui->label_sex->setText("男");
    }
    if(Sex==2)
    {
        ui->label_sex->setText("女");
    }
    ui->label_description->setText(Description);
    QString iconpath = QString(":/src/img/%1.jpg").arg(Icon);
    ui->iconButton->setIcon(QPixmap(iconpath));
    ui->label_tel->setText(tel);
}

friendinfo_interface::~friendinfo_interface()
{
    delete ui;
}
