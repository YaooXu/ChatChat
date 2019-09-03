#include "reg.h"
#include "ui_reg.h"

reg::reg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reg)
{
    ui->setupUi(this);
    init_reg();
}

reg::reg(QTcpSocket * ptr_socket, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reg)
{
    ui->setupUi(this);
    this->ptr_socket = ptr_socket;
    init_reg();
    connect(submit,SIGNAL(clicked()), this, SLOT(submit_click()));
}

reg::~reg()
{
    delete ui;
}

void reg::init_reg(){

    lable0 = new QLabel;
    lable0->setText(tr("姓名"));
    name = new QLineEdit;

    lable1 = new QLabel;
    lable1->setText(tr("密码"));
    password = new QLineEdit;
    password->setEchoMode(QLineEdit::Password);//设置为密码框
    submit = new QPushButton;
    submit->setText(tr("提交"));
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(lable0, 0, 0);
    layout->addWidget(name, 0, 1);
    layout->addWidget(lable1, 1, 0);
    layout->addWidget(password, 1, 1);
    layout->addWidget(submit, 2,1);
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);

    layout->setMargin(15);
    layout->setSpacing(10);
    layout->setSizeConstraint(QLayout::SetFixedSize);


}

void reg::submit_click(){
    name_text=name->text();
    password_text=password->text();
    uint32_t len = 0;
    Json::Value message;
    message["name"] = name_text.toStdString().c_str();
    message["password"] = password_text.toStdString().c_str();
    uint8_t *pData = encode(REGISTER_REQ, message, len);

    qDebug() << "length : " << len;
    ptr_socket->write((char *)pData, len);
    this->close();
}
