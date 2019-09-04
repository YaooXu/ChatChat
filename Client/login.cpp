#include "login.h"
#include "ui_login.h"
#include <cstring>

Login::Login(QTcpSocket *p_socket, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
    p_login_socket = p_socket;
    init_Login();
    connect(loginBtn,SIGNAL(clicked()), this, SLOT(loginBtnOnclick()));
    connect(logoutBtn,SIGNAL(clicked()), this, SLOT(logoutBtnOnclick()));
    connect(regBtn,SIGNAL(clicked()), this, SLOT(change_reg()));
    //    connect*()

    p_login_socket->connectToHost("182.92.193.104", 5117);
//    p_login_socket->connectToHost("127.0.0.1", 5117);
    connect(p_login_socket, SIGNAL(connected()), this, SLOT(handconnect()));
}

Login::~Login()
{
    delete ui;
}

void Login::init_Login()
{
    lable0 = new QLabel;
    lable0->setText(tr("用户ID"));
    lineEditUserID = new QLineEdit;

    lable1 = new QLabel;
    lable1->setText(tr("密码"));
    lineEditPasswd = new QLineEdit;
    lineEditPasswd->setEchoMode(QLineEdit::Password);//设置为密码框


    loginBtn = new QPushButton;
    loginBtn->setText(tr("登录"));
    logoutBtn = new QPushButton;
    logoutBtn->setText(tr("取消"));
    regBtn=new QPushButton;
    regBtn->setText(tr("注册"));
    forget=new QPushButton;
    forget->setText(tr("忘记密码"));


    QGridLayout *layout1 = new QGridLayout(this);
    layout1->addWidget(lable0, 0, 0);
    layout1->addWidget(lineEditUserID, 0, 1);

    layout1->addWidget(lable1, 1, 0);
    layout1->addWidget(lineEditPasswd, 1, 1);


    layout1->addWidget(loginBtn, 2, 0);
    layout1->addWidget(logoutBtn, 2, 1);

    layout1->addWidget(regBtn,3,0);
    layout1->addWidget(forget,3,1);

    layout1->setColumnStretch(0, 1);
    layout1->setColumnStretch(1, 1);

    layout1->setMargin(15);
    layout1->setSpacing(10);
    layout1->setSizeConstraint(QLayout::SetFixedSize);

    islogin = false;
    setWindowIcon(QPixmap(":/src/img/1.png"));//设置窗口图标
    //  lineEditUserID->setFocus();//设置lineEditUserID控件具有输入焦点

    //设置窗口没有边框
    setWindowFlags(Qt::FramelessWindowHint);


    //设置对话框背景颜色或图片
    setAutoFillBackground(true);
    QPalette palette;
    //palette.setColor(QPalette::Background, QColor(Qt::blue));
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/src/24.JPG")));//设置登陆背景
    setPalette(palette);
}


void Login::loginBtnOnclick()
{
    if (lineEditUserID->text().isEmpty())//如果lineEditUserID控件内容为空，提示用户错误
    {
        QMessageBox::information(this, tr("错误"), tr("用户ID不能为空"));
        //lineEditUserID->setFocus();
    }
    else
    {
        bool ok = true;
        //        userid = lineEditUserID->text().toInt(&ok);

        if (!ok)//如果lineEditUserID控件内容不是数字，提示用户错误
        {
            QMessageBox::information(this, tr("错误"), tr("用户ID必须是数字"));
            //  lineEditUserID->setFocus();
        }else
        {
            passwd = lineEditPasswd->text();

            qDebug() << "进入点击事件";

            QString uID = lineEditUserID->text();
            userid = uID;
            // 编码
            uint32_t len = 0;
            Json::Value message;
            message["ID"] = uID.toStdString().c_str();
            message["password"] = passwd.toStdString().c_str();
            uint8_t *pData = encode(LOGIN_REQ, message, len);

            qDebug() << "length : " << len;
            p_login_socket->write((char *)pData, len);

        }
    }
}

void Login::logoutBtnOnclick()
{
    this->close();
}

void Login::handconnect()
{
    //loginBtn->setEnabled(true);
    QMessageBox::information(this, "提示", "连接成功！");
    connect(p_login_socket, SIGNAL(readyRead()), this, SLOT(handData()));
}

void Login::handData()
{
    // 解码需要用到长度,所以只能用sock.read
    char recvBuf[1024];
    int len = p_login_socket->read(recvBuf, 1024);

    qDebug() << len;

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

    qDebug() << pMsg->body["status"].asInt();

    switch(server_id){
    case LOGIN_REP:
        if (pMsg->body["status"].asInt() == NORMAL) {
            qDebug() << "OK!";
            //登录成功,islogin设置为true,解除readyread槽函数
            islogin = true;
            emit loginSuccess();
            disconnect(p_login_socket, SIGNAL(readyRead()), this, SLOT(handData()));
            close();
            return;

        } else if (pMsg->body["status"].asInt() == EPASSWORD_WRONG){
            QString msg="不好意思，用户密码错误";
            QMessageBox::information(this, "失败", msg, QMessageBox::Yes | QMessageBox::No);
        } else if (pMsg->body["status"].asInt() == EUSER_NOTEXSIT) {
            QString msg="不好意思，用户不存在";
            QMessageBox::information(this, "失败", msg, QMessageBox::Yes | QMessageBox::No);
        } else {
            QString msg="不好意思，由于未知原因请您重新登录。";
            QMessageBox::information(this, "失败", msg, QMessageBox::Yes | QMessageBox::No);
        }
        break;
    case REGISTER_REP:
        qDebug()<<pMsg->body["status"].asInt();
        if(pMsg->body["status"].asInt()==NORMAL){
             QString ID = QString(pMsg->body["ID"].asCString());
             QString msg="恭喜您已经注册成功，您的ID为："+ID;
             QMessageBox::information(this, "成功", msg, QMessageBox::Yes | QMessageBox::No);
             qDebug()<<ID;
        }
        else{
            QString msg="不好意思，请您重新注册";
            QMessageBox::information(this, "失败", msg, QMessageBox::Yes | QMessageBox::No);

        }

         //QMessageBox::information(this, tr("错误"), tr("用户ID必须是数字"));d

        break;
    }
    // status为状态码,只有NORMAL才是正常


    return;
}

void Login::change_reg(){
    setWindowFlag(Qt::WindowStaysOnTopHint,false);
    reg * u= new reg(p_login_socket);
    u->show();
    return;

}
