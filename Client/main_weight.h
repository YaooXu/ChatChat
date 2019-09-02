//#ifndef MAIN_WEIGHT_H
#pragma once
//#define MAIN_WEIGHT_H

#include <QWidget>
#include <QStackedLayout>


#include "chatchat.h"
#include "login.h"
#include "frilist.h"
#include "chatroom.h"


namespace Ui {
class main_Weight;
}

class Main_Weight : public QWidget
{
    Q_OBJECT

public:
    explicit Main_Weight(QWidget *parent = nullptr);
    void init_main_Weight();
    ~Main_Weight();

    int userid;
    QString passwd;
    QString username;
    QString usericon;
//    Chatroom *p_Chatroom_List[1024];


private:
    Ui::main_Weight *ui;
    QPushButton *p_User_icon;//头像按钮
    QLabel *p_User_name;//用户名
    QLabel *p_User_personal;//个人介绍
    QPushButton *p_Message_Button;//消息按钮
    QPushButton *p_Friend_Button;//好友按钮
    QPushButton *p_Group_Button;//群组按钮
    QListWidget *p_Message_List;
    FriList *p_Friend_List;
    QToolButton *p_Message_Item[1024];
    QPushButton *p_Setting;//设置按钮
    QPushButton *p_Add_Friend;//添加好友按钮

    QVBoxLayout *main_Layout;

    QStackedLayout *three_Layout;
    QHBoxLayout *four_Layout;


public slots:
    //bool eventFilter(QObject *watched, QEvent *event);
    void create_Chatroom();


private slots:
    void on_clicked_Friend_Button();
    void on_clicked_Message_Button();

};

//#endif // MAIN_WEIGHT_H
