/********************************************************************************
** Form generated from reading UI file 'group_chat.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUP_CHAT_H
#define UI_GROUP_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_group_chat
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *pre_text;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTextBrowser *text_Browser;
    QTextBrowser *p_textBrowser;

    void setupUi(QWidget *group_chat)
    {
        if (group_chat->objectName().isEmpty())
            group_chat->setObjectName(QString::fromUtf8("group_chat"));
        group_chat->resize(596, 505);
        label = new QLabel(group_chat);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(6, 10, 81, 20));
        label_2 = new QLabel(group_chat);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(340, 10, 67, 17));
        pre_text = new QLineEdit(group_chat);
        pre_text->setObjectName(QString::fromUtf8("pre_text"));
        pre_text->setGeometry(QRect(20, 384, 311, 41));
        label_4 = new QLabel(group_chat);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 450, 67, 17));
        lineEdit_3 = new QLineEdit(group_chat);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(110, 450, 113, 25));
        pushButton = new QPushButton(group_chat);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(480, 450, 89, 25));
        pushButton_2 = new QPushButton(group_chat);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(350, 390, 89, 25));
        text_Browser = new QTextBrowser(group_chat);
        text_Browser->setObjectName(QString::fromUtf8("text_Browser"));
        text_Browser->setGeometry(QRect(30, 50, 301, 321));
        p_textBrowser = new QTextBrowser(group_chat);
        p_textBrowser->setObjectName(QString::fromUtf8("p_textBrowser"));
        p_textBrowser->setGeometry(QRect(350, 50, 181, 321));

        retranslateUi(group_chat);

        QMetaObject::connectSlotsByName(group_chat);
    } // setupUi

    void retranslateUi(QWidget *group_chat)
    {
        group_chat->setWindowTitle(QApplication::translate("group_chat", "Form", nullptr));
        label->setText(QApplication::translate("group_chat", "\350\201\212\345\244\251\345\256\244", nullptr));
        label_2->setText(QApplication::translate("group_chat", "\345\234\250\347\272\277\347\224\250\346\210\267\357\274\232", nullptr));
        label_4->setText(QApplication::translate("group_chat", "\347\224\250\346\210\267\345\220\215", nullptr));
        pushButton->setText(QApplication::translate("group_chat", "\345\205\263\351\227\255", nullptr));
        pushButton_2->setText(QApplication::translate("group_chat", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class group_chat: public Ui_group_chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUP_CHAT_H
