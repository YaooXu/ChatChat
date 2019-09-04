/********************************************************************************
** Form generated from reading UI file 'chatchat.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATCHAT_H
#define UI_CHATCHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chatchat
{
public:
    QWidget *centralWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Chatchat)
    {
        if (Chatchat->objectName().isEmpty())
            Chatchat->setObjectName(QString::fromUtf8("Chatchat"));
        Chatchat->resize(700, 1446);
        centralWidget = new QWidget(Chatchat);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Chatchat->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(Chatchat);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Chatchat->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Chatchat);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Chatchat->setStatusBar(statusBar);

        retranslateUi(Chatchat);

        QMetaObject::connectSlotsByName(Chatchat);
    } // setupUi

    void retranslateUi(QMainWindow *Chatchat)
    {
        Chatchat->setWindowTitle(QApplication::translate("Chatchat", "Chatchat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chatchat: public Ui_Chatchat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATCHAT_H
