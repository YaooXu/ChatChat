#include "main_weight.h"
#include "ui_main_weight.h"


Main_Weight::Main_Weight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_Weight)
{
//    init_main_Weight();
    p_socket = new QTcpSocket();
    lg = new Login(p_socket);
    lg->resize(700, 100);
    lg->show();

//    lg.islogin = true;



    connect(lg,SIGNAL(loginSuccess()),this,SLOT(log_in()));

}

Main_Weight::~Main_Weight()
{
    delete ui;
}
void Main_Weight::log_in(){

        init_main_Weight();
        qDebug() << "登录成功";
        userid = lg->userid;
//        QByteArray ba = lg.userid.toLatin1(); //填写用户信息，未完成
//        My_info->ID=ba.data();

        this->show();
        connect(p_socket, SIGNAL(readyRead()), this, SLOT(hand_message()));
        if(p_socket->isOpen())
        {
            Map_Socket.insert(userid, p_socket);
            qDebug() << "main:success connect socket!";
        }


}
void Main_Weight::init_main_Weight()
{

    this->setWindowTitle("QQ");

    p_User_icon = new QPushButton();
    p_User_icon->setFixedSize(100, 100);
    p_User_icon->setIcon(QPixmap(":/src/img/1.jpg"));
    p_User_icon->setFlat(false);//设置外观是否为扁平状
    p_User_icon->setIconSize(QSize(100, 100));
    connect(p_User_icon,SIGNAL(clicked()),this,SLOT(create_info()));


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
    on_clicked_Friend_Button();


    three_Layout->setCurrentIndex(0);


    p_Setting = new QPushButton();
    p_Setting->setText("设置");
    p_Add_Friend = new QPushButton();
    p_Add_Friend->setText("添加好友");
    connect(p_Add_Friend,SIGNAL(clicked()),this,SLOT(create_addfri()));

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

    //main_Layout->setStretch(0, 2);
    //main_Layout->setStretch(1, 1);
    //main_Layout->setStretch(3, 6);
    //main_Layout->setStretch(4, 1);
}

void Main_Weight::on_clicked_Message_Button()
{
    //Todo：给服务器发送消息
    set_Message_List();

}

void Main_Weight::on_clicked_Friend_Button()
{
    //Todo:从服务器访问好友列表
    if(p_Friend_List == nullptr)
    {
        set_Friend_List();
    }
    else {
        three_Layout->setCurrentIndex(1);
    }

}

void Main_Weight::create_Chatroom(QString uID)
{
    //Todo:如果之前的chatroom关闭了，要将Map_Chatroom[uID]设置为null
    qDebug() << "准备创建聊天室，ID1 = " << userid << ", ID2 = " << uID;
    if(Map_Chatroom[uID] == nullptr)
    {
        Chatroom *p_tmp = new Chatroom(p_socket, userid, uID);
        Map_Chatroom.insert(uID, p_tmp);//创建了一个聊天窗口，插入map
        p_tmp->setWindowTitle("Chatroom:" + userid + " to " + uID);
        p_tmp->resize(700, 600);
        p_tmp->show();
    }
    else {
        Map_Chatroom[uID]->show();
    }
}



void Main_Weight::create_Chatroom_whz()
{

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
    case REGISTER_REP://处理注册成功信号

        break;
    case LOGIN_REP://处理登录成功信号

        break;
    case RECENT_LIST_REP://处理返回最近联系人列表
    {

    }
        break;
    case MESSAGE_NOTI://服务器发送消息到客户端
    {
        Message *p_message = decode2Message(pMsg, len);
        qDebug() << "收到服务器的消息, ID1 = " << QString(p_message->ID1) << ", ID2 = "<< QString(p_message->ID2);
        qDebug() << "content: " << QString(p_message->content);
        //注意：message是好友发给ID1的，所以userid为ID2，而好友为ID1
        QString tmp_ID2 = QString(p_message->ID1);
        QString tmp_content = QString(p_message->content);
        if(Map_Chatroom[tmp_ID2] == nullptr)
        {
            create_Chatroom(tmp_ID2);
        }
        else {
            Map_Chatroom[tmp_ID2]->show();
        }

        Map_Chatroom[tmp_ID2]->add_msg(tmp_ID2, tmp_content);
    }


        break;
    default:
        break;
    }

    return;
}


void Main_Weight::set_Message_List()
{
    //先解除连接，清空list
    for(int i = 0; i < p_Message_List->count(); i++)
    {
        disconnect(p_Message_Item[i], SIGNAL(clicked()), this, SLOT(create_Chatroom()));
        delete p_Message_Item[i];
    }
    p_Message_List->clear();
    QIcon aIcon;//假设头像
    aIcon.addFile(":/src/img/1.jpg");

    for (int i=0;i<1;i++)
    {
        QWidget *tmp_three_widget = new QWidget();
        QVBoxLayout *three_Item_Layout = new QVBoxLayout();
        tmp_three_widget->setLayout(three_Item_Layout);
        QString tmp_id("100040");
        QString str = QString::asprintf("用户 %s",i);
        p_Message_Item[i] = new QToolButton();
//        p_Message_Item[i]->setSizeHint(QSize(400, 100));
        p_Message_Item[i]->setObjectName(tmp_id);//设置好友ID2对应toolbutton的name

        p_Message_Item[i]->setText(tmp_id);       //设置文字标签
        p_Message_Item[i]->setIcon(aIcon);     //设置图标
//        p_Message_Item[i]->installEventFilter(this);//p_Message_Item的点击事件由main_weight来处理
        p_Message_Item[i]->setIconSize(QSize(100, 100));//设置p_Message_Item大小和图像一致
        p_Message_Item[i]->setAutoRaise(true);//设置p_Message_Item自动浮起界面风格
        p_Message_Item[i]->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);//设置p_Message_Item文字在图像旁边
        p_Message_Item[i]->setToolTip(tr("未知"));//设置p_Message_Item 鼠标提示为“未知”

        //设置点击事件的槽函数
        //必须用用lambda表达式才能传递参数
        connect(p_Message_Item[i], &QToolButton::clicked, this, [=](){create_Chatroom(p_Message_Item[i]->objectName());});
//        connect(p_Message_Item[i], SIGNAL(clicked(p_Message_Item[i]->objectName())), this, SLOT(create_Chatroom(p_Message_Item[i]->objectName())));
        qDebug() << "设置Toolbutton的name: " << p_Message_Item[i]->objectName();
        three_Item_Layout->addWidget(p_Message_Item[i]);

//        p_Message_Item->setCheckState(Qt::Unchecked);      //设置为选中状态

        QListWidgetItem *aItem = new QListWidgetItem(p_Message_List);
        aItem->setSizeHint(QSize(400, 100));
        p_Message_List->addItem(aItem);
        p_Message_List->setItemWidget(aItem, tmp_three_widget);

    }

    three_Layout->setCurrentIndex(0);

}

void Main_Weight::set_Friend_List()
{
    //set好友列表
    if(p_Friend_List != nullptr && !p_Friend_List->is_empty())
    {
        three_Layout->removeWidget(p_Friend_List);
        p_Friend_List->clear_list();

        //p_Friend_List->add_friend("10002","赵满刚","01");
        three_Layout->addWidget(p_Friend_List);
        three_Layout->setCurrentIndex(1);
    }
    else {
        //Todo:预加载p_Friend_List
        p_Friend_List = new FriList(p_socket, userid);
        p_Friend_List->add_friend("10001","kid","1");
        p_Friend_List->add_friend("10002","赵满刚","2");
        p_Friend_List->add_family("10003","shr2","3");
        p_Friend_List->add_colleague("10004","shr3","4");
        p_Friend_List->add_classmate("10005","shr4","5");
        p_Friend_List->add_blacklist("10006","shr5","5");
        three_Layout->addWidget(p_Friend_List);

    }

    //Todo:将好友列表加载

    qDebug() << "set_Friend_List:清空";

}

void Main_Weight::create_addfri()
{
    addfri_interface * addfri=new addfri_interface(nullptr,userid,p_socket);
    addfri->show();
}

void Main_Weight::create_info()
{
    info *self_info = new info(nullptr);
    self_info->show();
}
