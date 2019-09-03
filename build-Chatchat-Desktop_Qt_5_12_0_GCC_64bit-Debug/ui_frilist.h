/********************************************************************************
** Form generated from reading UI file 'frilist.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRILIST_H
#define UI_FRILIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frilist
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *frilist)
    {
        if (frilist->objectName().isEmpty())
            frilist->setObjectName(QString::fromUtf8("frilist"));
        frilist->resize(400, 300);
        menuBar = new QMenuBar(frilist);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        frilist->setMenuBar(menuBar);
        mainToolBar = new QToolBar(frilist);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        frilist->addToolBar(mainToolBar);
        centralWidget = new QWidget(frilist);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frilist->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(frilist);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        frilist->setStatusBar(statusBar);

        retranslateUi(frilist);

        QMetaObject::connectSlotsByName(frilist);
    } // setupUi

    void retranslateUi(QMainWindow *frilist)
    {
        frilist->setWindowTitle(QApplication::translate("frilist", "frilist", nullptr));
    } // retranslateUi

};

namespace Ui {
    class frilist: public Ui_frilist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRILIST_H
