#include "repository.h"
#include "ui_repository.h"

repository::repository(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::repository)
{
    ui->setupUi(this);
    this->setFixedSize(409,401);
    ui->one->setIcon(QPixmap(":/src/img/1.png"));
    ui->two->setIcon(QPixmap(":/src/img/2.png"));
    ui->three->setIcon(QPixmap(":/src/img/3.png"));
    ui->four->setIcon(QPixmap(":/src/img/4.png"));
    ui->five->setIcon(QPixmap(":/src/img/5.png"));
    ui->six->setIcon(QPixmap(":/src/img/6.png"));
    ui->seven->setIcon(QPixmap(":/src/img/7.png"));
    ui->eight->setIcon(QPixmap(":/src/img/8.png"));
    ui->nine->setIcon(QPixmap(":/src/img/9.png"));
    ui->ten->setIcon(QPixmap(":/src/img/10.png"));
    ui->eleven->setIcon(QPixmap(":/src/img/11.png"));
    ui->twelve->setIcon((QPixmap(":/src/img/12.png")));
    ui->thirteen->setIcon(QPixmap(":/src/img/13.png"));
    ui->fourteen->setIcon(QPixmap("::/src/img/14.png"));
    ui->fifteen->setIcon(QPixmap(":/src/img/15.png"));
    ui->sixteen->setIcon(QPixmap(":/src/img/16.png"));
    ui->seventeen->setIcon(QPixmap(":/src/img/17.png"));
    ui->eighteen->setIcon(QPixmap(":/src/img/18.png"));
    ui->nineteen->setIcon(QPixmap(":/src/img/19.png"));
    ui->twenty->setIcon(QPixmap("::/src/img/20.png"));
    ui->one->setIconSize(QSize(200,200));
    ui->two->setIconSize(QSize(200,200));
    ui->three->setIconSize(QSize(200,200));
    ui->four->setIconSize(QSize(200,200));
    ui->five->setIconSize(QSize(200,200));
    ui->six->setIconSize(QSize(200,200));
    ui->seven->setIconSize(QSize(200,200));
    ui->eight->setIconSize(QSize(200,200));
    ui->nine->setIconSize(QSize(200,200));
    ui->ten->setIconSize(QSize(200,200));
    ui->eleven->setIconSize(QSize(200,200));
    ui->twelve->setIconSize(QSize(200,200));
    ui->thirteen->setIconSize(QSize(200,200));
    ui->fourteen->setIconSize(QSize(200,200));
    ui->fifteen->setIconSize(QSize(200,200));
    ui->sixteen->setIconSize(QSize(200,200));
    ui->seventeen->setIconSize(QSize(200,200));
    ui->eighteen->setIconSize(QSize(200,200));
    ui->nineteen->setIconSize(QSize(200,200));
    ui->twenty->setIconSize(QSize(200,200));

}

repository::~repository()
{
    delete ui;
}

void repository::on_two_clicked()
{
    int x=2;
    emit sendsignal(x);
    this->close();
}

void repository::on_one_clicked()
{
    int x=1;
    emit sendsignal(x);
    this->close();
}

void repository::on_three_clicked()
{
    int x=3;
    emit sendsignal(x);
    this->close();
}

void repository::on_four_clicked()
{
    int x=4;
    emit sendsignal(x);
    this->close();
}

void repository::on_five_clicked()
{
    int x=5;
    emit sendsignal(x);
    this->close();
}

void repository::on_seven_clicked()
{
    int x=7;
    emit sendsignal(x);
    this->close();
}

void repository::on_eight_clicked()
{
    int x=8;
    emit sendsignal(x);
    this->close();
}

void repository::on_nine_clicked()
{
    int x=9;
    emit sendsignal(x);
    this->close();
}

void repository::on_ten_clicked()
{
    int x=10;
    emit sendsignal(x);
    this->close();
}

void repository::on_eleven_clicked()
{
    int x=11;
    emit sendsignal(x);
    this->close();
}

void repository::on_twelve_clicked()
{
    int x=12;
    emit sendsignal(x);
    this->close();
}

void repository::on_thirteen_clicked()
{
    int x=13;
    emit sendsignal(x);
    this->close();
}

void repository::on_six_clicked()
{
    int x=6;
    emit sendsignal(x);
    this->close();
}

void repository::on_fourteen_clicked()
{
    int x=14;
    emit sendsignal(x);
    this->close();
}

void repository::on_fifteen_clicked()
{
    int x=15;
    emit sendsignal(x);
    this->close();
}

void repository::on_sixteen_clicked()
{
    int x=16;
    emit sendsignal(x);
    this->close();
}

void repository::on_seventeen_clicked()
{
    int x=17;
    emit sendsignal(x);
    this->close();
}
void repository::on_eighteen_clicked()
{
    int x=18;
    emit sendsignal(x);
    this->close();
}

void repository::on_nineteen_clicked()
{
    int x=19;
    emit sendsignal(x);
    this->close();
}

void repository::on_twenty_clicked()
{
    int x=20;
    emit sendsignal(x);
    this->close();
}
