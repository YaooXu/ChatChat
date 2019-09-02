#include "friendinfo_interface.h"
#include "ui_friendinfo_interface.h"

friendinfo_interface::friendinfo_interface(QWidget *parent,QString ID2) :
    QDialog(parent),
    ui(new Ui::friendinfo_interface)
{
    ui->setupUi(this);
    ID2_temp=ID2;
}

friendinfo_interface::~friendinfo_interface()
{
    delete ui;
}
