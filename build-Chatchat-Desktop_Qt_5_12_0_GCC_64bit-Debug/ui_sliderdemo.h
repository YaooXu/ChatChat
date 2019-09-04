/********************************************************************************
** Form generated from reading UI file 'sliderdemo.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDERDEMO_H
#define UI_SLIDERDEMO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SliderDemo
{
public:
    QWidget *centralwidget;
    QProgressBar *progressBar;
    QPushButton *btn_Start;
    QPushButton *btn_Stop;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SliderDemo)
    {
        if (SliderDemo->objectName().isEmpty())
            SliderDemo->setObjectName(QString::fromUtf8("SliderDemo"));
        SliderDemo->resize(687, 434);
        centralwidget = new QWidget(SliderDemo);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(20, 60, 651, 111));
        progressBar->setValue(24);
        btn_Start = new QPushButton(centralwidget);
        btn_Start->setObjectName(QString::fromUtf8("btn_Start"));
        btn_Start->setGeometry(QRect(100, 240, 151, 91));
        btn_Stop = new QPushButton(centralwidget);
        btn_Stop->setObjectName(QString::fromUtf8("btn_Stop"));
        btn_Stop->setGeometry(QRect(300, 240, 171, 91));
        SliderDemo->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(SliderDemo);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        SliderDemo->setStatusBar(statusbar);

        retranslateUi(SliderDemo);

        QMetaObject::connectSlotsByName(SliderDemo);
    } // setupUi

    void retranslateUi(QMainWindow *SliderDemo)
    {
        SliderDemo->setWindowTitle(QApplication::translate("SliderDemo", "MainWindow", nullptr));
        btn_Start->setText(QApplication::translate("SliderDemo", "\345\274\200\345\247\213", nullptr));
        btn_Stop->setText(QApplication::translate("SliderDemo", "\347\273\223\346\235\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SliderDemo: public Ui_SliderDemo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDERDEMO_H
