#include <QWidget>
#include<QDebug>
#include"repository.h"
namespace Ui {
class info;
}

class info : public QWidget
{
    Q_OBJECT

public:
    explicit info(QWidget *parent = nullptr);
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
private slots:
    void on_submit_clicked();

    void on_photo_clicked();

    void on_update_clicked();

    void change_photo(int);

signals:

    void sendsignal(int);

private:
    Ui::info *ui;
    repository *pt;

};

//#endif // INFO_H
