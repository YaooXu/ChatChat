#ifndef RECEIVE_ADDFRI_INTERFACE_H
#define RECEIVE_ADDFRI_INTERFACE_H

#include <QDialog>
#include <QTcpSocket>
#include "../utils/chat_proto.h"

namespace Ui {
class receive_addfri_interface;
}

class receive_addfri_interface : public QDialog
{
    Q_OBJECT

public:
    explicit receive_addfri_interface(QWidget *parent = nullptr,QString userID=nullptr,QString claimer_ID=nullptr, QString claimer_Name=nullptr,QTcpSocket *p_socket=nullptr);
    ~receive_addfri_interface();

private slots:
    void on_pushButton_clicked();

    void on_acceptButton_clicked();

    void on_refuseButton_clicked();

private:
    Ui::receive_addfri_interface *ui;
    QString ID1;
    QString ID2;
    QString Name;
    int group_ID;
    QTcpSocket *p_receive_addri_sock;
};

#endif // RECEIVE_ADDFRI_INTERFACE_H
