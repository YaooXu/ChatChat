//#ifndef FRILIST_H
#pragma once
//#define FRILIST_H
#include <QToolBox>
#include <QToolButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QList>
#include <QDebug>
#include <QAction>
#include <QMenu>
#include <QString>

#include "chatchat.h"
#include "chatroom.h"


class FriList : public QToolBox
{
    Q_OBJECT
public:
    FriList(QTcpSocket *p_sock, QString uID, QWidget *parent=0,Qt::WindowFlags f=0);

    void setLay_friend();   //好友页布局
    void setLay_family();
    void setLay_colleague();
    void setLay_classmate();
    void setLay_blc();
    void add_friend(QString id,QString user,QString icon);  //添加好友
    void add_family(QString id,QString user,QString icon);  //添加家人
    void add_colleague(QString id,QString user,QString icon); //添加同事
    void add_classmate(QString id,QString user,QString icon); //添加同学
    void add_blacklist(QString id,QString name,QString iconc);   //添加黑名单
    void clear_list();
    bool is_empty();

    QString userid;
    QTcpSocket *p_Friend_sock = nullptr;


private:
    QToolButton *toolBtn1;

    QList <QToolButton *>friend_list;   //好友列表
    QList <QToolButton *>family_list;
    QList <QToolButton *>colleague_list;
    QList <QToolButton *>classmate_list;
    QList <QToolButton *>blacklist_list;

    QGroupBox *friend_box;   //好友页
    QGroupBox *family_box;
    QGroupBox *colleague_box;
    QGroupBox *classmate_box;
    QGroupBox *blacklist_box;

    QVBoxLayout *layout_fri;    //好友页布局
    QVBoxLayout *layout_family;
    QVBoxLayout *layout_colleague;
    QVBoxLayout *layout_classmate;
    QVBoxLayout *layout_blacklist;

    QAction * buttonAction1;
    QAction * buttonAction2;
    QAction * buttonAction3;
    QMenu * buttonMenu;

public slots:
    //bool eventFilter(QObject *watched, QEvent *event);
    void create_Chatroom(QString uID);

};



//#endif // DRAWER_H
