#ifndef GROUP_CHAT_H
#define GROUP_CHAT_H
#include "chatroom.h"
#include <QWidget>

namespace Ui {
class group_chat;
}

class group_chat : public QWidget
{
    Q_OBJECT

public:
    explicit group_chat(QTcpSocket *p_socket,QString uID1,QString name,QWidget *parent = nullptr);
    ~group_chat();
    void add_msg1(QString delivername, QString msg);
    QString uID1;
    QString name;
   // QString uID2;
private slots:
    void on_pushButton_2_clicked();

private:
    Ui::group_chat *ui;
    QTcpSocket *ptr_socket;
};

#endif // GROUP_CHAT_H
