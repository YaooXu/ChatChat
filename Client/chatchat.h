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
