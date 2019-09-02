//#ifndef FRIENDINFO_INTERFACE_H
#pragma once
//#define FRIENDINFO_INTERFACE_H

#include <QDialog>

namespace Ui {
class friendinfo_interface;
}

class friendinfo_interface : public QDialog
{
    Q_OBJECT

public:
    explicit friendinfo_interface(QWidget *parent = nullptr,QString ID2=nullptr);
    ~friendinfo_interface();

private:
    Ui::friendinfo_interface *ui;
    QString ID2_temp;
};

//#endif // FRIENDINFO_INTERFACE_H
