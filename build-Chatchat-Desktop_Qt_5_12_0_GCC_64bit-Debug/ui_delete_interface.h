/********************************************************************************
** Form generated from reading UI file 'delete_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DELETE_INTERFACE_H
#define UI_DELETE_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_delete_interface
{
public:
    QPushButton *pushButton_yes;
    QPushButton *pushButton_no;
    QLabel *label;

    void setupUi(QDialog *delete_interface)
    {
        if (delete_interface->objectName().isEmpty())
            delete_interface->setObjectName(QString::fromUtf8("delete_interface"));
        delete_interface->resize(248, 149);
        pushButton_yes = new QPushButton(delete_interface);
        pushButton_yes->setObjectName(QString::fromUtf8("pushButton_yes"));
        pushButton_yes->setGeometry(QRect(50, 90, 51, 25));
        pushButton_no = new QPushButton(delete_interface);
        pushButton_no->setObjectName(QString::fromUtf8("pushButton_no"));
        pushButton_no->setGeometry(QRect(150, 90, 41, 25));
        label = new QLabel(delete_interface);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(76, 40, 101, 20));

        retranslateUi(delete_interface);

        QMetaObject::connectSlotsByName(delete_interface);
    } // setupUi

    void retranslateUi(QDialog *delete_interface)
    {
        delete_interface->setWindowTitle(QApplication::translate("delete_interface", "Dialog", nullptr));
        pushButton_yes->setText(QApplication::translate("delete_interface", "\347\241\256\345\256\232", nullptr));
        pushButton_no->setText(QApplication::translate("delete_interface", "\345\217\226\346\266\210", nullptr));
        label->setText(QApplication::translate("delete_interface", "\347\241\256\345\256\232\345\210\240\351\231\244\345\245\275\345\217\213\357\274\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class delete_interface: public Ui_delete_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DELETE_INTERFACE_H
