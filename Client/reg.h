#ifndef REG_H
#define REG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QTcpSocket>
#include <QByteArray>
#include <QWidget>
#include "chatchat.h"
namespace Ui {
class reg;
}

class reg : public QWidget
{
    Q_OBJECT

public:
    explicit reg(QWidget *parent = nullptr);
    ~reg();
    void init_reg();
    reg(QTcpSocket * ptr_socket, QWidget *parent = nullptr);

private:
    Ui::reg *ui;
    QLabel *lable0;
    QLabel *lable1;
    QLineEdit *name;
    QLineEdit *password;
    QPushButton *submit;
    QString name_text;
    QString password_text;
    QTcpSocket *ptr_socket;
private slots:
    void submit_click();

};

#endif // REG_H
