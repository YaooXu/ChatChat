//#ifndef CHATROOM_H
//#define CHATROOM_H
#pragma once
#include <QWidget>

#include "chatchat.h"



class Chatroom : public QWidget
{
    Q_OBJECT
public:
    explicit Chatroom(QWidget *parent = nullptr);
//    Chatroom(Main_Weight *w, QWidget *parent = nullptr);
//    Chatroom(const QIcon icon, int ID, QString name, Main_Weight *w, QWidget *parent = nullpr);

    ~Chatroom();
    void add_msg(QString delivername, QString msg);

    QPushButton *pushButton;

signals:

public slots:
    void on_pushButton_clicked();
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_toolButton_1_clicked(bool checked);
    void on_toolButton_2_clicked(bool checked);
    void on_toolButton_3_clicked(bool checked);
    void on_toolButton_4_clicked();
    void on_lineEdit_returnPressed();
    void on_toolButton_clicked();
//    Main_Weight *main_w;

private:
    void init_widget();

    QTextBrowser *textBrowser;
    QFontComboBox *fontComboBox;
    QComboBox *comboBox;
    QToolButton *toolButton_1;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton;

    QLineEdit *lineEdit;

    int userID;
    QString username;
    QColor color;

};

//#endif // CHATROOM_H
