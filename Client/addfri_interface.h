#ifndef ADDFRI_INTERFACE_H
#define ADDFRI_INTERFACE_H

#include <QDialog>
#include <qdebug.h>
#include <QTcpSocket>
#include "../utils/chat_proto.h"

namespace Ui {
class addfri_interface;
}

class addfri_interface : public QDialog
{
    Q_OBJECT

public:
    explicit addfri_interface(QWidget *parent = nullptr,QString userID=nullptr,QTcpSocket *p_socket=nullptr);
    ~addfri_interface();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addfri_interface *ui;
    QString ID1;
    QTcpSocket *p_addfri_sock;
};

#endif // ADDFRI_INTERFACE_H
