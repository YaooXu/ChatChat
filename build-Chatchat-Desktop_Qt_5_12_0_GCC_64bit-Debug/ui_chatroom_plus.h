/********************************************************************************
** Form generated from reading UI file 'chatroom_plus.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATROOM_PLUS_H
#define UI_CHATROOM_PLUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chatroom_Plus
{
public:
    QWidget *centralwidget;
    QListWidget *listWidget;
    QWidget *widget;
    QTextEdit *textEdit;
    QPushButton *pushButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Chatroom_Plus)
    {
        if (Chatroom_Plus->objectName().isEmpty())
            Chatroom_Plus->setObjectName(QString::fromUtf8("Chatroom_Plus"));
        Chatroom_Plus->resize(1096, 842);
        centralwidget = new QWidget(Chatroom_Plus);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(10, 0, 801, 471));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget{background-color: rgb(247, 247, 247); color:rgb(51,51,51); border: 1px solid  rgb(247, 247, 247);outline:0px;}\n"
"QListWidget::Item{background-color: rgb(247, 247, 247);}\n"
"QListWidget::Item:hover{background-color: rgb(247, 247, 247); }\n"
"QListWidget::item:selected{\n"
"	background-color: rgb(247, 247, 247);\n"
"	color:black; \n"
"    border: 1px solid  rgb(247, 247, 247);\n"
"}\n"
"QListWidget::item:selected:!active{border: 1px solid  rgb(247, 247, 247); background-color: rgb(247, 247, 247); color:rgb(51,51,51); } "));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 550, 721, 200));
        widget->setMinimumSize(QSize(0, 200));
        widget->setMaximumSize(QSize(16777215, 200));
        textEdit = new QTextEdit(widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 10, 621, 161));
        sizePolicy.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
        textEdit->setSizePolicy(sizePolicy);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(420, 92, 101, 51));
        Chatroom_Plus->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(Chatroom_Plus);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Chatroom_Plus->setStatusBar(statusbar);

        retranslateUi(Chatroom_Plus);

        QMetaObject::connectSlotsByName(Chatroom_Plus);
    } // setupUi

    void retranslateUi(QMainWindow *Chatroom_Plus)
    {
        Chatroom_Plus->setWindowTitle(QApplication::translate("Chatroom_Plus", "MainWindow", nullptr));
        pushButton->setText(QApplication::translate("Chatroom_Plus", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chatroom_Plus: public Ui_Chatroom_Plus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATROOM_PLUS_H
