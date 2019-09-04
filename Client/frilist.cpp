#include "frilist.h"
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDebug>
#include <delete_interface.h>
#include <regroup_interface.h>
#include <friendinfo_interface.h>

static QString ID2_temp;

FriList::FriList(QTcpSocket *p_sock, QString uID, QWidget *parent,Qt::WindowFlags f)
    :QToolBox(parent,f)
{
    p_Friend_sock = p_sock;
    userid = uID;
    friend_box = new QGroupBox;
    blacklist_box = new QGroupBox;
    family_box = new QGroupBox;
    colleague_box = new QGroupBox;
    classmate_box = new QGroupBox;
    this->setLay_friend();
    this->setLay_family();
    this->setLay_colleague();
    this->setLay_classmate();
    this->setLay_blc();

    buttonAction1 = new QAction("重新分组",this);
    buttonAction2 = new QAction("删除好友",this);
    buttonAction3 = new QAction("查看好友资料",this);
    buttonMenu = new QMenu(this);
    buttonMenu->addAction(buttonAction1);
    buttonMenu->addAction(buttonAction2);
    buttonMenu->addAction(buttonAction3);
    connect( buttonAction1, &QAction::triggered, [=]()
    {
        qDebug()<<"重新分组";
        regroup_interface * regroup_friend = new regroup_interface(nullptr,userid,ID2_temp,p_Friend_sock);
        regroup_friend->show();

    });
    connect( buttonAction2, &QAction::triggered, [=]()
    {
        qDebug()<<"删除好友";
        delete_interface * delete_friend = new delete_interface(nullptr,userid,ID2_temp,p_Friend_sock);  //此处只是实验，ID2是好友的ID，参数还应有socket,ID1
        delete_friend->show();
    });
    connect( buttonAction3, &QAction::triggered, [=]()
    {
        qDebug()<<"查看好友资料";
        uint32_t len=0;
        Json::Value message;
        message["ID"]=ID2_temp.toStdString().c_str();
        uint8_t *pData=encode(GET_FRIEND_INF_REQ,message,len);
        p_Friend_sock->write((char*)pData,len);
    });
}



void FriList::setLay_friend()
{
    //好友页布局
    layout_fri = new QVBoxLayout(friend_box);
    layout_fri->setMargin(45);
    layout_fri->setAlignment(Qt::AlignLeft);
    this->addItem((QWidget*)friend_box,QStringLiteral("我的好友"));
}

void FriList::setLay_family()
{
    layout_family = new QVBoxLayout(family_box);
    layout_family->setMargin(45);
    layout_family->setAlignment(Qt::AlignLeft);
    this->addItem((QWidget*)family_box,QStringLiteral("家人"));
}

void FriList::setLay_colleague()
{
    layout_colleague = new QVBoxLayout(colleague_box);
    layout_colleague->setMargin(45);
    layout_colleague->setAlignment(Qt::AlignLeft);
    this->addItem((QWidget*)colleague_box,QStringLiteral("同事"));
}

void FriList::setLay_classmate()
{
    layout_classmate = new QVBoxLayout(classmate_box);
    layout_classmate->setMargin(45);
    layout_classmate->setAlignment(Qt::AlignLeft);
    this->addItem((QWidget*)classmate_box,QStringLiteral("同学"));
}

void FriList::setLay_blc()
{
    layout_blacklist = new QVBoxLayout(blacklist_box);
    layout_fri->setMargin(45);
    layout_fri->setAlignment(Qt::AlignLeft);
    this->addItem((QWidget*)blacklist_box,QStringLiteral("黑名单"));
}




void FriList::add_friend(QString id, QString user, QString icon)//通过此类函数实现动态好友列表，即每刷新一次，重新将所 有好友add进去
{
    QToolButton *tempButton = new QToolButton;
    QString iconpath = QString(":/src/img/%1.jpg").arg(icon);//头像
    QString text = QString("%1").arg(user);//昵称
    QString ID2=id;//好友ID
    tempButton->setText(text);
    qDebug()<<iconpath;
    tempButton->setIcon(QPixmap(iconpath));
    tempButton->setIconSize(QSize(100,30)); //设置按钮尺寸
    tempButton->setObjectName(id);//设置好友ID2对应toolbutton的name

    tempButton->setAutoRaise(true);   //当鼠标离开时，按钮恢复为弹起状态
    tempButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); //设置按钮文字显示在图标旁边

    tempButton->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tempButton,&QToolButton::customContextMenuRequested,[=]()
    {
        ID2_temp=ID2;
        buttonMenu->exec(QCursor::pos());
    });

    //通过点击创建聊天窗口
//    connect(tempButton, SIGNAL(clicked()), this, SLOT(create_Chatroom(tempButton->objectName())));
    connect(tempButton, &QToolButton::clicked, this, [=](){create_Chatroom(tempButton->objectName());});


    friend_list.append(tempButton);
    layout_fri->addWidget(friend_list.last());
}

void FriList::add_blacklist(QString id, QString name, QString icon)
{
    QToolButton *tempButton = new QToolButton;
    QString iconpath = QString(":/src/img/%1.jpg").arg(icon);
    QString text = QString("%1").arg(name);
    QString ID2=id;//好友ID
    tempButton->setText(text);
    qDebug()<<iconpath;
    tempButton->setIcon(QPixmap(iconpath));
    tempButton->setIconSize(QSize(100,30));
    tempButton->setObjectName(id);//设置好友ID2对应toolbutton的name
    tempButton->setAutoRaise(true);
    tempButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    tempButton->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tempButton,&QToolButton::customContextMenuRequested,[=]()
    {
        ID2_temp=ID2;
        buttonMenu->exec(QCursor::pos());
    });
    connect(tempButton, &QToolButton::clicked, this, [=](){create_Chatroom(tempButton->objectName());});

    blacklist_list.append(tempButton);
    layout_blacklist->addWidget(blacklist_list.last());

}

void FriList::add_family(QString id, QString name, QString icon)
{
    QToolButton *tempButton = new QToolButton;
    QString iconpath = QString(":/src/img/%1.jpg").arg(icon);
    QString text = QString("%1").arg(name);
    QString ID2=id;//好友ID
    tempButton->setText(text);
    qDebug()<<iconpath;
    tempButton->setIcon(QPixmap(iconpath));
    tempButton->setIconSize(QSize(100,30));
    tempButton->setObjectName(id);//设置好友ID2对应toolbutton的name
    tempButton->setAutoRaise(true);
    tempButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    tempButton->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tempButton,&QToolButton::customContextMenuRequested,[=]()
    {
        ID2_temp=ID2;
        buttonMenu->exec(QCursor::pos());
    });
    connect(tempButton, &QToolButton::clicked, this, [=](){create_Chatroom(tempButton->objectName());});

    family_list.append(tempButton);
    layout_family->addWidget(family_list.last());
}

void FriList::add_colleague(QString id, QString name, QString icon)
{
    QToolButton *tempButton = new QToolButton;
    QString iconpath = QString(":/src/img/%1.jpg").arg(icon);
    QString text = QString("%1").arg(name);
    QString ID2=id;//好友ID
    tempButton->setText(text);
    qDebug()<<iconpath;
    tempButton->setIcon(QPixmap(iconpath));
    tempButton->setIconSize(QSize(100,30));
    tempButton->setObjectName(id);//设置好友ID2对应toolbutton的name
    tempButton->setAutoRaise(true);
    tempButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    tempButton->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tempButton,&QToolButton::customContextMenuRequested,[=]()
    {
        ID2_temp=ID2;
        buttonMenu->exec(QCursor::pos());
    });
    connect(tempButton, &QToolButton::clicked, this, [=](){create_Chatroom(tempButton->objectName());});

    colleague_list.append(tempButton);
    layout_colleague->addWidget(colleague_list.last());
}

void FriList::add_classmate(QString id, QString name, QString icon)
{
    QToolButton *tempButton = new QToolButton;
    QString iconpath = QString(":/src/img/%1.png").arg(icon);
    QString text = QString("%1").arg(name);
    QString ID2=id;//好友ID
    tempButton->setText(text);
    qDebug()<<iconpath;
    tempButton->setIcon(QPixmap(iconpath));
    tempButton->setIconSize(QSize(100,30));
    tempButton->setObjectName(id);//设置好友ID2对应toolbutton的name
    tempButton->setAutoRaise(true);
    tempButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    tempButton->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(tempButton,&QToolButton::customContextMenuRequested,[=]()
    {
        ID2_temp=ID2;
        buttonMenu->exec(QCursor::pos());
    });
    connect(tempButton, &QToolButton::clicked, this, [=](){create_Chatroom(tempButton->objectName());});

    classmate_list.append(tempButton);
    layout_classmate->addWidget(classmate_list.last());
}

void FriList::create_Chatroom(QString uID)
{
        Chatroom *p_tmp = new Chatroom(p_Friend_sock, userid, uID);
        p_tmp->resize(700, 600);
        p_tmp->show();
}

void FriList::clear_list()
{
    while(!friend_list.empty())
    {
        disconnect(friend_list.last(),0,0,0);
        layout_fri->removeWidget(friend_list.last());
        friend_list.last()->~QToolButton();
        friend_list.pop_back();
    }
    while(!blacklist_list.empty())
    {
        disconnect(blacklist_list.last(),0,0,0);
        layout_fri->removeWidget(blacklist_list.last());
        blacklist_list.last()->~QToolButton();
        blacklist_list.pop_back();
    }
    while(!family_list.empty())
    {
        disconnect(family_list.last(),0,0,0);
        layout_family->removeWidget(family_list.last());
        family_list.last()->~QToolButton();
        family_list.pop_back();
    }
    while(!colleague_list.empty())
    {
        disconnect(colleague_list.last(),0,0,0);
        layout_colleague->removeWidget(colleague_list.last());
        colleague_list.last()->~QToolButton();
        colleague_list.pop_back();
    }
    while(!classmate_list.empty())
    {
        disconnect(classmate_list.last(),0,0,0);
        layout_classmate->removeWidget(classmate_list.last());
        classmate_list.last()->~QToolButton();
        classmate_list.pop_back();
    }
}

bool FriList::is_empty()
{
    bool tmp = true;
    if(!friend_list.empty())
    {
        tmp = false;
    }
    if(!blacklist_list.empty())
    {
        tmp = false;
    }
    if(!family_list.empty())
    {
        tmp = false;
    }
    if(!colleague_list.empty())
    {
        tmp = false;
    }
    if(!classmate_list.empty())
    {
        tmp = false;
    }
    return tmp;
}
