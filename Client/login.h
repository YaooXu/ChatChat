#pragma once

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QTcpSocket>
#include <QByteArray>

#include "chatchat.h"
#include "main_weight.h"



namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    bool islogin;
    void init_Login();
    int userid;
    QString passwd;

private slots:
    void loginBtnOnclick();
    void logoutBtnOnclick();
    void handconnect();
    void handData();

private:
    Ui::Login *ui;

    QTcpSocket sock;

    QLabel *lable0;
    QLabel *lable1;
    QLineEdit *lineEditUserID;
    QLineEdit *lineEditPasswd;
    QPushButton *loginBtn;
    QPushButton *logoutBtn;
};

