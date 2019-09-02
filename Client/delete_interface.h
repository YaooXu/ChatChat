//#ifndef DELETE_INTERFACE_H
#pragma once
//#define DELETE_INTERFACE_H

#include <QDialog>

namespace Ui {
class delete_interface;
}

class delete_interface : public QDialog
{
    Q_OBJECT

public:
    explicit delete_interface(QWidget *parent = nullptr,QString ID2=NULL);
    ~delete_interface();

private slots:


    void on_pushButton_yes_clicked();

    void on_pushButton_no_clicked();

private:
    Ui::delete_interface *ui;
    QString ID2_temp;
};

//#endif // DELETE_INTERFACE_H
