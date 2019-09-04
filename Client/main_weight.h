//#ifndef MAIN_WEIGHT_H
#pragma once
//#define MAIN_WEIGHT_H

#include <QWidget>
#include <QStackedLayout>


#include "my_include.h"
#include "login.h"
#include "frilist.h"
#include "chatroom.h"
#include "addfri_interface.h"
#include "info.h"


namespace Ui {
class main_Weight;
}

class Main_Weight : public QWidget
{
    Q_OBJECT

public:
    explicit Main_Weight(QWidget *parent = nullptr);
    ~Main_Weight();

    QString userid;
    QString username;
    QString usericon;
    QTcpSocket *p_socket;
    QMap<QString, Chatroom*> Map_Chatroom;//ID1的好友ID2对应chatroom的指针
    QMap<QString, QTcpSocket*> Map_Socket;//ID对应用户的socket指针

    User_info *My_info;

    void init_main_Weight();
    void set_Message_List(User_in_recent *p_list, int num);
    void set_Friend_List(User_in_list *p_list, int num);




private:
    Ui::main_Weight *ui;
    QPushButton *p_User_icon;//头像按钮
    QLabel *p_User_name;//用户名
    QLabel *p_User_personal;//个人介绍
    QPushButton *p_Message_Button;//消息按钮
    QPushButton *p_Friend_Button;//好友按钮
    QPushButton *p_Group_Button;//群组按钮
    QListWidget *p_Message_List = nullptr;//最近消息列表
    FriList *p_Friend_List= nullptr;//用户好友列表
    QToolButton *p_Message_Item[1024];
    QPushButton *p_Setting;//设置按钮
    QPushButton *p_Add_Friend;//添加好友按钮
    Login *lg;
    QVBoxLayout *main_Layout;
    info *self_info;
    QStackedLayout *three_Layout;
    QHBoxLayout *four_Layout;


public slots:
    void create_Chatroom(QString uID);
    void hand_message();
    void create_Chatroom_whz();
    void create_addfri();
    void create_info();
    void change_main_photo(int);
    void change_description(QString);
    void change_name(QString);
private slots:
    void on_clicked_Friend_Button();
    void on_clicked_Message_Button();
    void log_in();
signals:
    void log_signal(int);


};



//#endif // MAIN_WEIGHT_H
