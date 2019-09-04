#include "main_weight.h"
#include "ui_main_weight.h"


Main_Weight::Main_Weight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_Weight)
{
    //    init_main_Weight();
    //    setWindowFlags(Qt::WindowStaysOnBottomHint);
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


    qDebug() << "登录成功";
    userid = lg->userid;
    qDebug() << "从login里面赋值id" << userid;
    //        QByteArray ba = lg.userid.toLatin1(); //填写用户信息，未完成
    //        My_info->ID=ba.data();
    init_main_Weight();
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
    //
    //    p_User_icon->setIcon(QPixmap(":/src/img/1.png"));
    p_User_icon->setFlat(false);//设置外观是否为扁平状
    p_User_icon->setIconSize(QSize(100, 100));
    connect(p_User_icon,SIGNAL(clicked()),this,SLOT(create_info()));


    p_User_name = new QLabel();
    //p_User_name->setText("用户名");
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
    //    on_clicked_Message_Button();

    p_Friend_List = new FriList(p_socket, userid);


    three_Layout->addWidget(p_Message_List);


    qDebug() << "Friend初始化";

    //Todo:这里初始化好友列表，下一步从服务器访问消息
    //    on_clicked_Friend_Button();


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
    uint32_t len = 0;
    Json::Value message;
    message["ID"] = userid.toStdString().c_str();
    qDebug() << "userid = " << userid;
    uint8_t *pData = encode(RECENT_LIST_REQ, message, len);

    qDebug() << "向服务器请求最近消息列表, length : " << len;
    p_socket->write((char *)pData, len);

}

void Main_Weight::on_clicked_Friend_Button()
{
    //Todo:从服务器访问好友列表
    uint32_t len = 0;
    Json::Value message;
    message["ID"] = userid.toStdString().c_str();
    uint8_t *pData = encode(FRIEND_LIST_REQ, message, len);

    qDebug() << "向服务器请求好友列表, length : " << len;
    p_socket->write((char *)pData, len);

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
    char recvBuf[10000];
    int len = p_socket->read(recvBuf, 10000);

    qDebug() <<"收到服务器消息,长度为" << len;

    // 建立一个解码器对象
    MyProtoDeCode myDecode;
    myDecode.clear();
    myDecode.init();

    // 需要转化为uint8_t类型字符串
    uint8_t *pData = (uint8_t *)recvBuf;
    if (!myDecode.parser(pData, len)) {
        qDebug() << "parser falied!\n";
    } else {
        qDebug() << "parser successfully!, len = " << len;
    }

    qDebug() << "已解包的包个数" << myDecode.mMsgQ.size();

    MyProtoMsg *pMsg;
    // 解码的结果存在结构体的一个队列里,直接通过.front访问
    // !!!
    while (!myDecode.empty()) {
        pMsg= myDecode.front();  // 协议消息的指针
        myDecode.pop();

        int server_id = pMsg->head.server_id;

        qDebug() << "收到的消息头为: " << server_id;

        switch (server_id) {
        case REGISTER_REP://处理注册成功信号

            break;
        case LOGIN_REP://处理登录成功信号

            break;
        case RECENT_LIST_REP://处理返回最近联系人列表
        {
            int num = 0;
            User_in_recent *recent_message_List = decode2User_recent(pMsg, num);//num是这个list的长度
            qDebug() << "收到服务器最近联系列表，个数为: " << num;
            set_Message_List(recent_message_List, num);

        }
            break;
        case FRIEND_LIST_REP://处理返回的好友列表
        {
            int num = 0;
            User_in_list *friend_List = decode2User_list(pMsg, num);//num是这个list的长度
            qDebug() << "收到服务器最近联系列表，个数为: " << num;
            set_Friend_List(friend_List, num);
        }
            break;
        case MESSAGE_NOTI://服务器发送消息到客户端
        {
            Message *p_message = decode2Message(pMsg);
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
            break;
        }
        case GET_MY_INF_REP:{
            self_info = new info(p_socket);
            connect(self_info,SIGNAL(send_signal(int)),this,SLOT(change_main_photo(int)));
            connect(self_info,SIGNAL(send_des(QString)),this,SLOT(change_description(QString)));
            connect(self_info,SIGNAL(send_name(QString)),this,SLOT(change_name(QString)));
            int length = 0;
            User_info *pUser_info = decode2User_info(pMsg, length);
            int x=pUser_info->photo_id;
            QString name=pUser_info->name;
            name="昵称:"+name;
            p_User_name->setText(name);
            QString mood=pUser_info->description;
            mood="个性签名："+mood;
            p_User_personal->setText(mood);
            QString image_name;
            image_name.sprintf(":/src/img/%d.png",x);
            p_User_icon->setIcon(QPixmap(image_name));
            self_info->updat_info(pUser_info);
            break;
        }
        case CHANGE_MY_INF_REP:{
            qDebug()<<pMsg->body["status"].asInt()<<"信息修改反馈";
            if(pMsg->body["status"].asInt()==NORMAL){

                QString msg="恭喜您已经修改成功";
                QMessageBox::information(this, "成功", msg, QMessageBox::Yes | QMessageBox::No);
            }
            break;

        }
        case FRIEND_ADD_FIRST_REP:{
            int status = pMsg->body["status"].asInt();
            if(status==0)
            {
                QMessageBox::warning(this,"title","成功发送");
            }
            else {
                {
                    QMessageBox::warning(this,"title","发送失败");
                }
            }
            break;
        }
        case FRIEND_ADD_NOTI:{
            int length=0;
            User_in_list *p_message = decode2User_list(pMsg,length);
            QString claimer_ID=p_message->ID;
            QString claimer_Name=p_message->name;
            receive_addfri_interface *receive_addfri = new receive_addfri_interface(nullptr,userid,claimer_ID,claimer_Name,p_socket);
            receive_addfri->show();
            break;
        }
        case FRIEND_ADD_SECOND_REP:{
            int status = pMsg->body["status"].asInt();
            int result = pMsg->body["accept"].asInt();    //协议中没有留出，之后要在协议里加
            if(result==0)
            {
                QMessageBox::warning(this,"title","您和对方已是好友");
            }
            else
            {
                QMessageBox::warning(this,"title","对方拒绝了您的申请");
            }
            break;

        }
        case GET_FRIEND_INF_REP:{
            int length=0;
            User_in_list *p_message = decode2User_list(pMsg,length);
            QString ID = p_message->ID;
            int Icon=p_message->photo_id;
            QString Name = p_message->name;
            int Sex = p_message->sex_id;
            QString Description = p_message->description;

            friendinfo_interface *friendinfo = new friendinfo_interface(nullptr,ID,Icon,Name,Sex,Description);
            friendinfo->show();
            break;
        }default:
            break;
        }
        delete pMsg;
    }
    return;
}

//Todo:list按照time排序
void Main_Weight::set_Message_List(User_in_recent *p_list, int num)
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

    for (int i = 0; i < num; i++)
    {
        QWidget *tmp_three_widget = new QWidget();
        QVBoxLayout *three_Item_Layout = new QVBoxLayout();
        tmp_three_widget->setLayout(three_Item_Layout);
        QString tmp_id(QString(p_list[i].ID));
        qDebug() << "message id = " << tmp_id;
        //        QString str(QString(p_list->)); //设置用户名
        p_Message_Item[i] = new QToolButton();
        //        p_Message_Item[i]->setSizeHint(QSize(400, 100));
        p_Message_Item[i]->setObjectName(tmp_id);//设置好友ID2对应toolbutton的name
        p_Message_Item[i]->setText(tmp_id);    //设置文字标签
        //        QString imagename;
        //        imagename.sprintf(":/src/img/%d.png", p_list->);//设置头像
        p_Message_Item[i]->setIcon(aIcon);     //设置图标
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

void Main_Weight::set_Friend_List(User_in_list *p_list, int num)
{   
    //Todo:将好友列表加载
    if(p_Friend_List != nullptr)
    {
        qDebug() << "set_Friend_List:清空";
        three_Layout->removeWidget(p_Friend_List);
        p_Friend_List->clear_list();
        for(int i = 0; i < num; i++)
        {
            QString tmp_id = QString(p_list[i].ID);
            QString tmp_name = QString(p_list[i].name);
            QString tmp_icon = QString::number(p_list[i].photo_id);
            int is_online = p_list[i].online;
            int tmp_group_id = p_list[i].group_id;
            switch (tmp_group_id) {
            case 1:
                p_Friend_List->add_friend(tmp_id, tmp_name, tmp_icon);
                break;
            case 2:
                p_Friend_List->add_family(tmp_id, tmp_name, tmp_icon);
                break;
            case 3:
                p_Friend_List->add_colleague(tmp_id, tmp_name, tmp_icon);
                break;
            case 4:
                p_Friend_List->add_classmate(tmp_id, tmp_name, tmp_icon);
                break;
            case 5:
                p_Friend_List->add_blacklist(tmp_id, tmp_name, tmp_icon);
                break;
            default:
                break;
            }


        }

        three_Layout->addWidget(p_Friend_List);
        three_Layout->setCurrentIndex(1);
    }
    else {
        //Todo:空指针不用管

    }

}

void Main_Weight::create_addfri()
{
    addfri_interface * addfri=new addfri_interface(nullptr,userid,p_socket);
    addfri->show();
}

void Main_Weight::create_info()
{
    self_info->show();
}

void Main_Weight::change_main_photo(int x){
    QString imagename2;

    imagename2.sprintf(":/src/img/%d.png",x);
    //p_User_name->setText("tzy");
    p_User_icon->setIcon(QPixmap(imagename2));
    //qDebug()<<"changephoto to " << imagename2;

}
void Main_Weight::change_description(QString des){
    des="个性签名："+des;
    p_User_personal->setText(des);
    //qDebug()<<"sad";
}
void Main_Weight::change_name(QString name){
    name="昵称："+name;
    p_User_name->setText(name);

}
