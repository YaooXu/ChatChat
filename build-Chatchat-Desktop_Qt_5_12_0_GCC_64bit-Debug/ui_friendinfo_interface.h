/********************************************************************************
** Form generated from reading UI file 'friendinfo_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDINFO_INTERFACE_H
#define UI_FRIENDINFO_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_friendinfo_interface
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QDialog *friendinfo_interface)
    {
        if (friendinfo_interface->objectName().isEmpty())
            friendinfo_interface->setObjectName(QString::fromUtf8("friendinfo_interface"));
        friendinfo_interface->resize(400, 300);
        label = new QLabel(friendinfo_interface);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 40, 21, 17));
        label_2 = new QLabel(friendinfo_interface);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 70, 67, 17));
        label_3 = new QLabel(friendinfo_interface);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 150, 67, 17));
        label_4 = new QLabel(friendinfo_interface);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 180, 67, 17));
        label_5 = new QLabel(friendinfo_interface);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(70, 210, 67, 17));
        label_6 = new QLabel(friendinfo_interface);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(70, 240, 81, 17));
        label_7 = new QLabel(friendinfo_interface);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(130, 10, 131, 17));

        retranslateUi(friendinfo_interface);

        QMetaObject::connectSlotsByName(friendinfo_interface);
    } // setupUi

    void retranslateUi(QDialog *friendinfo_interface)
    {
        friendinfo_interface->setWindowTitle(QApplication::translate("friendinfo_interface", "Dialog", nullptr));
        label->setText(QApplication::translate("friendinfo_interface", "ID", nullptr));
        label_2->setText(QApplication::translate("friendinfo_interface", "photo", nullptr));
        label_3->setText(QApplication::translate("friendinfo_interface", "name", nullptr));
        label_4->setText(QApplication::translate("friendinfo_interface", "sex", nullptr));
        label_5->setText(QApplication::translate("friendinfo_interface", "tel", nullptr));
        label_6->setText(QApplication::translate("friendinfo_interface", "description", nullptr));
        label_7->setText(QApplication::translate("friendinfo_interface", "Friend Information", nullptr));
    } // retranslateUi

};

namespace Ui {
    class friendinfo_interface: public Ui_friendinfo_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDINFO_INTERFACE_H
