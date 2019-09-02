#pragma once

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QTcpSocket>
#include <QByteArray>

#include "chatchat.h"
#include "main_weight.h"
#include "reg.h"


namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QTcpSocket *p_socket, QWidget *parent = nullptr);
    ~Login();

    bool islogin;
    void init_Login();
    int userid;
    QString passwd;
    QString username;
    QString usericon;

    QTcpSocket *p_login_socket;

private slots:
    void loginBtnOnclick();
    void logoutBtnOnclick();
    void handconnect();
    void handData();
    void change_reg();

private:
    Ui::Login *ui;

    QLabel *lable0;
    QLabel *lable1;
    QLineEdit *lineEditUserID;
    QLineEdit *lineEditPasswd;
    QPushButton *loginBtn;
    QPushButton *logoutBtn;
    QPushButton *regBtn;
    QPushButton *forget;


};

//#endif // LOGIN_H
