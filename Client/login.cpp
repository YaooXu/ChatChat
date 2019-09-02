#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
    init_Login();
    connect(loginBtn,SIGNAL(clicked()), this, SLOT(loginBtnOnclick()));
    connect(logoutBtn,SIGNAL(clicked()), this, SLOT(logoutBtnOnclick()));
//    connect*()

    sock.connectToHost("192.168.157.129", 8888);
    connect(&sock, SIGNAL(connected()), this, SLOT(handconnect()));
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


    QGridLayout *layout1 = new QGridLayout(this);
    layout1->addWidget(lable0, 0, 0);
    layout1->addWidget(lineEditUserID, 0, 1);

    layout1->addWidget(lable1, 1, 0);
    layout1->addWidget(lineEditPasswd, 1, 1);


    layout1->addWidget(loginBtn, 2, 0);
    layout1->addWidget(logoutBtn, 2, 1);

    layout1->setColumnStretch(0, 1);
    layout1->setColumnStretch(1, 1);

    layout1->setMargin(15);
    layout1->setSpacing(10);
    layout1->setSizeConstraint(QLayout::SetFixedSize);

    islogin = false;
    setWindowIcon(QPixmap(":/src/img/1.jpg"));//设置窗口图标
    lineEditUserID->setFocus();//设置lineEditUserID控件具有输入焦点

    //设置窗口没有边框
    setWindowFlags(Qt::FramelessWindowHint);


    //设置对话框背景颜色或图片
    setAutoFillBackground(true);
    QPalette palette;
    //palette.setColor(QPalette::Background, QColor(Qt::blue));
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/src/img/1.jpg")));//设置登陆背景
    setPalette(palette);
}


void Login::loginBtnOnclick()
{
    if (lineEditUserID->text().isEmpty())//如果lineEditUserID控件内容为空，提示用户错误
    {
        QMessageBox::information(this, tr("错误"), tr("用户ID不能为空"));
        lineEditUserID->setFocus();
    }
    else
    {
        bool ok = true;
        userid = lineEditUserID->text().toInt(&ok);

        if (!ok)//如果lineEditUserID控件内容不是数字，提示用户错误
        {
            QMessageBox::information(this, tr("错误"), tr("用户ID必须是数字"));
            lineEditUserID->setFocus();
        }else
        {
            passwd = lineEditPasswd->text();

            qDebug() << "进入点击事件";

            QString sendbuf = "2|";
            QString uName = lineEditUserID->text();
            sendbuf += uName;
            sendbuf += "|";
            sendbuf += passwd;
            qDebug() << sendbuf;
            sendbuf.toStdString().c_str();

            char*  ch;
            QByteArray ba = sendbuf.toLatin1(); // must
            ch=ba.data();
            printf("发送 %s\n", ch);
            sock.write(ch);

        }
    }
}

void Login::logoutBtnOnclick()
{
    close();
}

void Login::handconnect()
{
    loginBtn->setEnabled(true);
    QMessageBox::information(this, "zzz", "连接成功！");
    connect(&sock, SIGNAL(readyRead()), this, SLOT(handData()));
}

void Login::handData()
{
    QByteArray recvBuf =  sock.readAll();
    QString buf(recvBuf);
    qDebug() << buf;
    //0|xxx
    QStringList slist = buf.split("|");
    if(slist.at(0) == "1")
    {
        QMessageBox::information(this, "提示", "Login success!");
        islogin = true;

        qDebug() << "islogin" << islogin;
        close();
        return;
    }
    else if(slist.at(0) == "0")
    {
        islogin = false;
        QMessageBox::warning(this, "Error!", slist.at(1));
    }
    return;
}
