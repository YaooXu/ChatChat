#pragma once

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QTcpSocket>
#include <QByteArray>
#include <QListView>
#include <QListWidget>
#include <QLabel>
#include <QStackedWidget>
#include <QButtonGroup>
#include <QDebug>
#include <QMessageBox>
#include <QTcpSocket>
#include <QByteArray>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QToolBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QTextBrowser>
#include <QFontComboBox>
#include <QComboBox>
#include <QDateTime>
#include <QColorDialog>
#include <QObject>

#include "chat_proto.h" // 暂时这样添加,直接把我整个源文件包含进来,但是可能会有重复定义

namespace Ui {
class Chatchat;
}

class Chatchat : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chatchat(QWidget *parent = nullptr);
    ~Chatchat();

private:
    Ui::Chatchat *ui;
    QTcpSocket *p_sock;

    QVBoxLayout *left_Layout;
    QPushButton *user_Button;
    QPushButton *message_Button;
    QPushButton *friend_Button;
    QPushButton *group_Button;
    QPushButton *setting_Button;
};

//#endif // CHATCHAT_H
