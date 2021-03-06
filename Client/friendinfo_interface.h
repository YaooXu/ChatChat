//#ifndef FRIENDINFO_INTERFACE_H
#pragma once
//#define FRIENDINFO_INTERFACE_H

#include <QDialog>
#include <QTcpSocket>
#include "../utils/chat_proto.h"
#include "main_weight.h"
#include "string"


namespace Ui {
class friendinfo_interface;
}

class friendinfo_interface : public QDialog
{
    Q_OBJECT

public:
    explicit friendinfo_interface(QWidget *parent = nullptr,QString fri_ID=nullptr,int fri_Icon=1,QString fri_Name=nullptr,int fri_Sex=0,QString fri_des=nullptr,QString fri_tel=nullptr);
    ~friendinfo_interface();

private:
    Ui::friendinfo_interface *ui;
    QString ID;
    int Icon;
    QString Name;
    int Sex;
    QString Description;
    QString tel;
};

//#endif // FRIENDINFO_INTERFACE_H
