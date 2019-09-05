#ifndef DIALOGREC_H
#define DIALOGREC_H

#include <QDialog>
#include <QFileDialog>

#include <QUdpSocket>
#include <QFile>
#include "chatroom.h"
#include "my_include.h"

namespace Ui {
    class DialogRec;
}

class DialogRec : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRec(QString sender, QWidget *parent = 0);
    ~DialogRec();
    void fileName(QString , QString);
    void initSocket();
    void set_file_recever(QString recip);
    QString getIP();

    QString sender_ip;
    QFile *file = nullptr;

protected:
    //这是一个虚函数，继承自QEvent.只要重写了这个虚函数，当你按下窗口右上角的"×"时，就会调用重写的此函数.
    void closeEvent(QCloseEvent*event);


private slots:

    void fs(const QString & );
    void readPendingDatagrams();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::DialogRec *ui;
    QString file_name;
    QUdpSocket *udpSocket;

    QFileDialog *fDialog;
    QString filee;

};

#endif // DIALOGREC_H
