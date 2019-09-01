#include "chatchat.h"
#include "ui_chatchat.h"

Chatchat::Chatchat(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Chatchat)
{
    ui->setupUi(this);
    this->setWindowTitle("Chatchat");

    //第一部分：用户个人信息
    QPushButton *p_User_icon = new QPushButton(this);
    p_User_icon->setIcon(QPixmap(":/src/img/1.jpg"));

    QLabel *p_User_name = new QLabel(this);
    p_User_name->setText("用户名");
    QLabel *p_User_personal = new QLabel(this);
    p_User_personal->setText("个人介绍");

    QHBoxLayout *one_Layout = new QHBoxLayout(this);
    QVBoxLayout *one_right_Layout = new QVBoxLayout(this);

    one_right_Layout->addWidget(p_User_name);
    one_right_Layout->addWidget(p_User_personal);

    one_Layout->addWidget(p_User_icon);
    one_Layout->addLayout(one_right_Layout);



    QVBoxLayout *main_Laylou = new QVBoxLayout();
//    mainLayout->setMargin(30);  //表示控件与窗体的左右边距
//    mainLayout->setSpacing(40); //表示各个控件之间的上下间距

    main_Laylou->addLayout(one_Layout);




    QWidget *win=new QWidget();

    QLineEdit *line=new QLineEdit(win);
    line->setText("Line");

    QTextEdit *text=new QTextEdit(win);
    text->setText("text");

    QLabel *label=new QLabel(win);
    label->setText("label");

    QPushButton *quit=new QPushButton(win);
    quit->setText("Quit");


    QHBoxLayout *Hbox=new QHBoxLayout(win);//水平布局管理器（父管理器）；
    QVBoxLayout *Vbox_left=new QVBoxLayout;//垂直布局管理器（子管理器）；
    QVBoxLayout *Vbox_right=new QVBoxLayout;

    Vbox_left->addWidget(line);
    Vbox_left->addWidget(text);
    Vbox_right->addWidget(label);
    Vbox_right->addWidget(quit);

    //设定每个布局管理器中的部件间间隔
    Hbox->setSpacing(50);
    Vbox_left->setSpacing(25);
    Vbox_right->setSpacing(25);

    //父布局管理器添加addLayout();
    //整个界面有水平和垂直两个布局管理，根布局为水平，子布局为垂直
    //将部件加入左右两个垂直布局管理器中
    //再将左右两个垂直布局管理器加入水平布局管理器
    Hbox->addLayout(Vbox_left);
    Hbox->addLayout(Vbox_right);


    win->show();

}

Chatchat::~Chatchat()
{
    delete ui;
}

