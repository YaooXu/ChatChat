//#ifndef REGROUP_INTERFACE_H
#pragma once
//#define REGROUP_INTERFACE_H

#include <QDialog>

namespace Ui {
class regroup_interface;
}

class regroup_interface : public QDialog
{
    Q_OBJECT

public:
    explicit regroup_interface(QWidget *parent = nullptr,QString ID2=NULL);
    ~regroup_interface();

private slots:
    void on_friend_pushButton_clicked();

    void on_family_pushButton_clicked();

    void on_colleague_pushButton_clicked();

    void on_classmate_pushButton_clicked();

    void on_blacklist_pushButton_clicked();

private:
    Ui::regroup_interface *ui;
    QString ID2_temp;
};

//#endif // REGROUP_INTERFACE_H
