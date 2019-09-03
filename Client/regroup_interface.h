//#ifndef REGROUP_INTERFACE_H
#pragma once
//#define REGROUP_INTERFACE_H

#include <QDialog>
#include <qdebug.h>
#include <QTcpSocket>
#include "../utils/chat_proto.h"

namespace Ui {
class regroup_interface;
}

class regroup_interface : public QDialog
{
    Q_OBJECT

public:
    explicit regroup_interface(QWidget *parent = nullptr,QString userid=nullptr,QString ID2=nullptr,QTcpSocket *p_socket=nullptr);
    ~regroup_interface();

private slots:
    void on_friend_pushButton_clicked();

    void on_family_pushButton_clicked();

    void on_colleague_pushButton_clicked();

    void on_classmate_pushButton_clicked();

    void on_blacklist_pushButton_clicked();

private:
    Ui::regroup_interface *ui;
    QString ID1;
    QString ID2_temp;
    QTcpSocket *p_regroup_socket;
};

//#endif // REGROUP_INTERFACE_H
