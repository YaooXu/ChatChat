#ifndef CHATROOM_PLUS_H
#define CHATROOM_PLUS_H

#include <QMainWindow>
#include "chatchat.h"
#include "qnchatmessage.h"

namespace Ui {
class Chatroom_Plus;
}

class Chatroom_Plus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chatroom_Plus(QWidget *parent = nullptr);
    ~Chatroom_Plus();

    void dealMessage(QNChatMessage *messageW, QListWidgetItem *item, QString text, QString time, QNChatMessage::User_Type type);
    void dealMessageTime(QString curMsgTime);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Chatroom_Plus *ui;
};

#endif // CHATROOM_PLUS_H
