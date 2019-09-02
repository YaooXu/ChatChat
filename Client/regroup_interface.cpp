#include "regroup_interface.h"
#include "ui_regroup_interface.h"
#include "QDebug"

regroup_interface::regroup_interface(QWidget *parent, QString ID2) :
    QDialog(parent),
    ui(new Ui::regroup_interface)
{
    ui->setupUi(this);
    ID2_temp=ID2;
}

regroup_interface::~regroup_interface()
{
    delete ui;
}

void regroup_interface::on_friend_pushButton_clicked()
{
    qDebug()<<ID2_temp;

    close();
}

void regroup_interface::on_family_pushButton_clicked()
{
    qDebug()<<ID2_temp;

    close();
}

void regroup_interface::on_colleague_pushButton_clicked()
{
    qDebug()<<ID2_temp;

    close();
}

void regroup_interface::on_classmate_pushButton_clicked()
{
    qDebug()<<ID2_temp;

    close();
}

void regroup_interface::on_blacklist_pushButton_clicked()
{
    qDebug()<<ID2_temp;

    close();
}
