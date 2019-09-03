//#ifndef DELETE_INTERFACE_H
#pragma once
//#define DELETE_INTERFACE_H

#include <QDialog>
#include <QTcpSocket>
#include "../utils/chat_proto.h"

namespace Ui {
class delete_interface;
}

class delete_interface : public QDialog
{
    Q_OBJECT

public:
    explicit delete_interface(QWidget *parent = nullptr,QString userID=nullptr,QString ID2=nullptr,QTcpSocket *p_socket=nullptr);
    ~delete_interface();

private slots:


    void on_pushButton_yes_clicked();

    void on_pushButton_no_clicked();

private:
    Ui::delete_interface *ui;
    QString ID1;
    QString ID2_temp;
    QTcpSocket *p_delfri_sock;
};

//#endif // DELETE_INTERFACE_H
