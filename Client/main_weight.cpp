#include "main_weight.h"
#include "ui_main_weight.h"


main_Weight::main_Weight(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::main_Weight)
{
    Login lg;
    lg.resize(400, 200);
    lg.exec();
    if(lg.islogin)
    {
        init_main_Weight();
        ui->setupUi(this);
    }
    else {
        QMessageBox::warning(this, "main_Layout", "未连接到服务器！");
    }


}

main_Weight::~main_Weight()
{
    delete ui;
}

void main_Weight::init_main_Weight()
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
    p_Friend_Button = new QPushButton();
    p_Friend_Button->setText("好友");
    p_Group_Button = new QPushButton();
    p_Group_Button->setText("群组");

    QHBoxLayout *two_Layout = new QHBoxLayout();
    two_Layout->addWidget(p_Message_Button);
    two_Layout->addWidget(p_Friend_Button);
    two_Layout->addWidget(p_Group_Button);


    p_Message_List = new QListWidget();


    QIcon aIcon;//假设头像
    aIcon.addFile(":/src/img/1.jpg");

    for (int i=0;i<20;i++)
    {
        QString str = QString::asprintf("用户 %d",i);
        p_Message_Item[i] = new QListWidgetItem;
        p_Message_Item[i]->setSizeHint(QSize(400, 100));
        p_Message_Item[i]->setText(str);       //设置文字标签
        p_Message_Item[i]->setIcon(aIcon);     //设置图标
//        p_Message_Item->setCheckState(Qt::Unchecked);      //设置为选中状态

        p_Message_List->addItem(p_Message_Item[i]);
    }


    p_Setting = new QPushButton();
    p_Setting->setText("设置");
    p_Add_Friend = new QPushButton();
    p_Add_Friend->setText("添加好友");

    QHBoxLayout *four_Layout = new QHBoxLayout();
    four_Layout->addWidget(p_Setting);
    four_Layout->addWidget(p_Add_Friend);

    QVBoxLayout *main_Layout = new QVBoxLayout(this);
    main_Layout->setMargin(30);  //表示控件与窗体的左右边距
    main_Layout->setSpacing(40); //表示各个控件之间的上下间距

    main_Layout->addLayout(one_Layout);
    main_Layout->addLayout(two_Layout);
    main_Layout->addWidget(p_Message_List);
    main_Layout->addLayout(four_Layout);

//    main_Layout->setStretch(0, 1);
//    main_Layout->setStretch(1, 4);
//    main_Layout->setStretch(3, 7);
//    main_Layout->setStretch(4, 5);
}

