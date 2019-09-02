#include "delete_interface.h"
#include "ui_delete_interface.h"
#include "QDebug"

delete_interface::delete_interface(QWidget *parent, QString ID2) :
    QDialog(parent),
    ui(new Ui::delete_interface)
{
    ui->setupUi(this);
    ID2_temp=ID2;
}

delete_interface::~delete_interface()
{
    delete ui;
}



void delete_interface::on_pushButton_yes_clicked()
{
    qDebug()<<ID2_temp;

    close();
}

void delete_interface::on_pushButton_no_clicked()
{
    qDebug()<<ID2_temp;

    close();
}
