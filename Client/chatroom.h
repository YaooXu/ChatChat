//#ifndef CHATROOM_H
//#define CHATROOM_H
#pragma once
#include <QWidget>
#include <QGridLayout>
#include "my_include.h"
#include "sliderdemo.h"

#include<QTextEdit>


class Chatroom : public QWidget
{
    Q_OBJECT
public:
    explicit Chatroom(QTcpSocket *p_sock, QString uID1, QString uID2, QWidget *parent = nullptr);
//    Chatroom(Main_Weight *w, QWidget *parent = nullptr);
//    Chatroom(const QIcon icon, int ID, QString name, Main_Weight *w, QWidget *parent = nullpr);

    ~Chatroom();
    void add_msg(QString delivername, QString msg);


    void sendData();
    QString getIP();

    SliderDemo *tmp;

    QTcpSocket *p_chat_socket;
    QString uID1;
    QString uID2;
    QPushButton *pushButton;

    QFileDialog *fDialog;
    QUdpSocket *udpSocket;
    QFile *file = nullptr;
    QString files_name;
    QString ip, serverIP;
    QHostAddress recip;

signals:

public slots:
    void on_pushButton_clicked();
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_toolButton_1_clicked(bool checked);
    void on_toolButton_2_clicked(bool checked);
    void on_toolButton_3_clicked(bool checked);
    void on_toolButton_4_clicked();
    void on_lineEdit_returnPressed();
    void on_send_file_Button_clicked();
    void readPendingDatagrams();

    void requser_send_files(const QString & fs);
//    void set_file_recever(QString recip);
//    Main_Weight *main_w;

protected:
    //这是一个虚函数，继承自QEvent.只要重写了这个虚函数，当你按下窗口右上角的"×"时，就会调用重写的此函数.
    void closeEvent(QCloseEvent*event);

private:
    void init_widget();

    QTextBrowser *textBrowser;
    QFontComboBox *fontComboBox;
    QComboBox *comboBox;
    QToolButton *toolButton_1;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *send_file_Button;

    QLineEdit *lineEdit;

    QColor color;

};

//#endif // CHATROOM_H
