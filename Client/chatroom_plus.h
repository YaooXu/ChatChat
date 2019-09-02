#ifndef CHATROOM_PLUS_H
#define CHATROOM_PLUS_H

#include <QMainWindow>

namespace Ui {
class Chatroom_Plus;
}

class Chatroom_Plus : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chatroom_Plus(QWidget *parent = nullptr);
    ~Chatroom_Plus();

private:
    Ui::Chatroom_Plus *ui;
};

#endif // CHATROOM_PLUS_H
