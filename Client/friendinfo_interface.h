//#ifndef FRIENDINFO_INTERFACE_H
#pragma once
//#define FRIENDINFO_INTERFACE_H

#include <QDialog>
#include <QTcpSocket>
#include "../utils/chat_proto.h"


namespace Ui {
class friendinfo_interface;
}

class friendinfo_interface : public QDialog
{
    Q_OBJECT

public:
    explicit friendinfo_interface(QWidget *parent = nullptr,QString ID2=nullptr,QTcpSocket *p_socket=nullptr);
    ~friendinfo_interface();

private:
    Ui::friendinfo_interface *ui;
    QString ID2_temp;
    QTcpSocket *p_finfo_sock;
};

//#endif // FRIENDINFO_INTERFACE_H
