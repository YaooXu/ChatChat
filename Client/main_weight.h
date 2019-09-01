#ifndef MAIN_WEIGHT_H
#define MAIN_WEIGHT_H

#include <QWidget>
#include "chatchat.h"
#include "login.h"

namespace Ui {
class main_Weight;
}

class main_Weight : public QWidget
{
    Q_OBJECT

public:
    explicit main_Weight(QWidget *parent = nullptr);
    void init_main_Weight();
    ~main_Weight();

private:
    Ui::main_Weight *ui;
    QPushButton *p_User_icon;//头像按钮
    QLabel *p_User_name;//用户名
    QLabel *p_User_personal;//个人介绍
    QPushButton *p_Message_Button;//消息按钮
    QPushButton *p_Friend_Button;//好友按钮
    QPushButton *p_Group_Button;//群组按钮
    QListWidget *p_Message_List;
    QListWidgetItem *p_Message_Item[1024];
    QPushButton *p_Setting;//设置按钮
    QPushButton *p_Add_Friend;//添加好友按钮






private slots:

};

#endif // MAIN_WEIGHT_H
