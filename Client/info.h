#include <QWidget>
#include<QDebug>
#include"repository.h"
#include "../utils/chat_proto.h"
#include<QTcpSocket>
namespace Ui {
class info;
}

class info : public QWidget
{
    Q_OBJECT

public:
    explicit info(QTcpSocket *p_socket, QWidget *parent = nullptr);
    ~info();
    QString name;
    QString ID;
    QString ans;
    QString sex;
    QString tel;
    QString question;
    QString mood;
    QString last_date;
    QString photo;
    QTcpSocket *ptr_socket;
    void updat_info(User_info*);
    int photo_num;
private slots:
    void on_submit_clicked();

    void on_photo_clicked();

    void on_update_clicked();

    void change_photo(int);



signals:

    void send_signal(int);

private:
    Ui::info *ui;
    repository *pt;

};

//#endif // INFO_H
