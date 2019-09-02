#include "chatroom_plus.h"
#include "ui_chatroom_plus.h"

Chatroom_Plus::Chatroom_Plus(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chatroom_Plus)
{
    ui->setupUi(this);
}

Chatroom_Plus::~Chatroom_Plus()
{
    delete ui;
}
