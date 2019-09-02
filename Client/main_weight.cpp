#include "main_weight.h"
#include "ui_main_weight.h"


Main_Weight::Main_Weight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_Weight)
{
    p_socket = new QTcpSocket();
    Login lg(p_socket);
    lg.resize(700, 100);
    lg.exec();
//    lg.islogin = true;

    if(lg.islogin)
    {
        init_main_Weight();
        connect(p_socket, SIGNAL(readyRead()), this, SLOT(hand_message()));
        if(p_socket->isOpen())
        {
            qDebug() << "main:success connect!";
        }

        ui->setupUi(this);
    }
    else {
        QMessageBox::warning(this, "main_Layout", "未连接到服务器！");
        close();
    }


}

Main_Weight::~Main_Weight()
{
    delete ui;
}

//主窗口的信号过滤函数，watched代表是哪个控件触发了信号，event代表触发了具体什么信号
//bool Main_Weight::eventFilter(QObject *watched, QEvent *event)
//{
//    if(event->type() == QEvent::MouseButtonPress)//如果是鼠标按键信号
//    {
//        int i = watched->objectName().toInt();
//        child[i]->hide();
//         child[i]->showNormal();//将p_Message_Item下对应的child显示到屏幕
//        qDebug() << "点击！！！" << i;
//    }
//    return Main_Weight::eventFilter(watched, event);//其他信号交给父类进行默认处理
//}

void Main_Weight::init_main_Weight()
{

    this->setWindowTitle("QQ");

    p_User_icon = new QPushButton();
    p_User_icon->setFixedSize(200, 200);
    p_User_icon->setIcon(QPixmap(":/src/img/1.jpg"));
    p_User_icon->setFlat(false);//设置外观是否为扁平状
    p_User_icon->setIconSize(QSize(200, 200));


    p_User_name = new QLabel();
    p_User_name->setText("用户名");
    p_User_personal = new QLabel();
    p_User_personal->setText("个人介绍");


    QHBoxLayout *one_Layout = new QHBoxLayout();
    QVBoxLayout *one_right_Layout = new QVBoxLayout();

    one_right_Layout->addWidget(p_User_name);
    one_right_Layout->addWidget(p_User_personal);

    one_Layout->addWidget(p_User_icon);
    one_Layout->addLayout(one_right_Layout);


    p_Message_Button = new QPushButton();
    p_Message_Button->setText("消息");
    connect(p_Message_Button, SIGNAL(clicked()), this, SLOT(on_clicked_Message_Button()));
    p_Friend_Button = new QPushButton();
    p_Friend_Button->setText("好友");
    connect(p_Friend_Button, SIGNAL(clicked()), this, SLOT(on_clicked_Friend_Button()));
    p_Group_Button = new QPushButton();
    p_Group_Button->setText("群组");

    QHBoxLayout *two_Layout = new QHBoxLayout();
    two_Layout->addWidget(p_Message_Button);
    two_Layout->addWidget(p_Friend_Button);
    two_Layout->addWidget(p_Group_Button);

    //第三部分:QStackedlayout，先初始化message，然后初始化friend
    three_Layout = new QStackedLayout();
    p_Message_List = new QListWidget();

    //Todo:这里初始化消息列表，下一步从服务器访问消息
    qDebug() << "Message初始化";
    on_clicked_Message_Button();


    three_Layout->addWidget(p_Message_List);


    qDebug() << "Friend初始化";
    //Todo:这里初始化好友列表，下一步从服务器访问消息
    p_Friend_List = new FriList();
    p_Friend_List->add_friend("10001","kid","00");
    p_Friend_List->add_friend("10002","赵满刚","01");
    p_Friend_List->add_family("10003","shr2","02");
    p_Friend_List->add_colleague("10004","shr3","03");
    p_Friend_List->add_classmate("10005","shr4","04");
    p_Friend_List->add_blacklist("10006","shr5","05");

    three_Layout->addWidget(p_Friend_List);
    three_Layout->setCurrentIndex(0);


    p_Setting = new QPushButton();
    p_Setting->setText("设置");
    p_Add_Friend = new QPushButton();
    p_Add_Friend->setText("添加好友");

    four_Layout = new QHBoxLayout();
    four_Layout->addWidget(p_Setting);
    four_Layout->addWidget(p_Add_Friend);

    main_Layout = new QVBoxLayout(this);
    main_Layout->setMargin(30);  //表示控件与窗体的左右边距
    main_Layout->setSpacing(40); //表示各个控件之间的上下间距




    main_Layout->addLayout(one_Layout);
    main_Layout->addLayout(two_Layout);

    main_Layout->addLayout(three_Layout);
    main_Layout->addLayout(four_Layout);

    main_Layout->setStretch(0, 2);
    main_Layout->setStretch(1, 1);
    main_Layout->setStretch(3, 6);
    main_Layout->setStretch(4, 1);
}


void Main_Weight::on_clicked_Message_Button()
{
    //Todo：从服务器获取消息列表

    QIcon aIcon;//假设头像
    aIcon.addFile(":/src/img/1.jpg");

    for (int i=0;i<20;i++)
    {
        QWidget *tmp_three_widget = new QWidget();
        QVBoxLayout *three_Item_Layout = new QVBoxLayout();
        tmp_three_widget->setLayout(three_Item_Layout);

        QString str = QString::asprintf("用户 %d",i);
        p_Message_Item[i] = new QToolButton();
//        p_Message_Item[i]->setSizeHint(QSize(400, 100));
        p_Message_Item[i]->setObjectName(QString(i));
        p_Message_Item[i]->setText(str);       //设置文字标签
        p_Message_Item[i]->setIcon(aIcon);     //设置图标
//        p_Message_Item[i]->installEventFilter(this);//p_Message_Item的点击事件由main_weight来处理
        p_Message_Item[i]->setIconSize(QSize(100, 100));//设置p_Message_Item大小和图像一致
        p_Message_Item[i]->setAutoRaise(true);//设置p_Message_Item自动浮起界面风格
        p_Message_Item[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置p_Message_Item文字在图像旁边
        p_Message_Item[i]->setToolTip(tr("未知"));//设置p_Message_Item 鼠标提示为“未知”

        connect(p_Message_Item[i], SIGNAL(clicked()), this, SLOT(create_Chatroom()));

        three_Item_Layout->addWidget(p_Message_Item[i]);

//        p_Message_Item->setCheckState(Qt::Unchecked);      //设置为选中状态

        QListWidgetItem *aItem = new QListWidgetItem(p_Message_List);
        aItem->setSizeHint(QSize(400, 100));
        p_Message_List->addItem(aItem);
        p_Message_List->setItemWidget(aItem, tmp_three_widget);

    }

    three_Layout->setCurrentIndex(0);

}

void Main_Weight::on_clicked_Friend_Button()
{
    //Tode://Todo:从服务器访问好友列表
    three_Layout->setCurrentIndex(1);

}

void Main_Weight::create_Chatroom()
{
        Chatroom *p_tmp = new Chatroom();
        p_tmp->setWindowTitle("Chatroom");
        p_tmp->resize(700, 600);
        p_tmp->show();
}

void Main_Weight::hand_message()
{
    // 解码需要用到长度,所以只能用sock.read
    char recvBuf[1024];
    int len = p_socket->read(recvBuf, 1024);

    qDebug() <<"收到服务器消息,长度为" << len;

    // 建立一个解码器对象
    MyProtoDeCode myDecode;
    myDecode.clear();
    myDecode.init();

    // 需要转化为uint8_t类型字符串
    uint8_t *pData = (uint8_t *)recvBuf;
    if (!myDecode.parser(pData, len)) {
        printf("parser falied!\n");
    } else {
        printf("parser successfully!, len = %d\n", len);
    }

    // 解码的结果存在结构体的一个队列里,直接通过.front访问
    MyProtoMsg *pMsg = myDecode.front();  // 协议消息的指针

    int server_id = pMsg->head.server_id;

    switch (server_id) {
    case LOGIN_REP:

        break;
    default:
        break;
    }




    // status为状态码,只有NORMAL才是正常
    qDebug() << pMsg->body["status"].asInt();
    if (pMsg->body["status"].asInt() == NORMAL) {
        qDebug() << "OK!";
        //登录成功,islogin设置为true,解除readyread槽函数

        return;

    } else if (pMsg->body["status"].asInt() == EPASSWORD_WRONG){
        qDebug() << "PASSWORD WRONG";
    } else if (pMsg->body["status"].asInt() == EUSER_NOTEXSIT) {
        qDebug() << "USER NOT EXSIT";
    } else {
        qDebug() << "UNKOWN ERROR";
    }

    return;
}
