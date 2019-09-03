#include "repository.h"
#include "ui_repository.h"

repository::repository(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::repository)
{
    ui->setupUi(this);
}

repository::~repository()
{
    delete ui;
}
