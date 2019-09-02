/********************************************************************************
** Form generated from reading UI file 'regroup_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGROUP_INTERFACE_H
#define UI_REGROUP_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_regroup_interface
{
public:
    QPushButton *friend_pushButton;
    QPushButton *family_pushButton;
    QPushButton *colleague_pushButton;
    QPushButton *classmate_pushButton;
    QPushButton *blacklist_pushButton;

    void setupUi(QDialog *regroup_interface)
    {
        if (regroup_interface->objectName().isEmpty())
            regroup_interface->setObjectName(QString::fromUtf8("regroup_interface"));
        regroup_interface->resize(339, 293);
        friend_pushButton = new QPushButton(regroup_interface);
        friend_pushButton->setObjectName(QString::fromUtf8("friend_pushButton"));
        friend_pushButton->setGeometry(QRect(110, 30, 89, 25));
        family_pushButton = new QPushButton(regroup_interface);
        family_pushButton->setObjectName(QString::fromUtf8("family_pushButton"));
        family_pushButton->setGeometry(QRect(110, 80, 89, 25));
        colleague_pushButton = new QPushButton(regroup_interface);
        colleague_pushButton->setObjectName(QString::fromUtf8("colleague_pushButton"));
        colleague_pushButton->setGeometry(QRect(110, 130, 89, 25));
        classmate_pushButton = new QPushButton(regroup_interface);
        classmate_pushButton->setObjectName(QString::fromUtf8("classmate_pushButton"));
        classmate_pushButton->setGeometry(QRect(110, 180, 89, 25));
        blacklist_pushButton = new QPushButton(regroup_interface);
        blacklist_pushButton->setObjectName(QString::fromUtf8("blacklist_pushButton"));
        blacklist_pushButton->setGeometry(QRect(110, 230, 89, 25));

        retranslateUi(regroup_interface);

        QMetaObject::connectSlotsByName(regroup_interface);
    } // setupUi

    void retranslateUi(QDialog *regroup_interface)
    {
        regroup_interface->setWindowTitle(QApplication::translate("regroup_interface", "Dialog", nullptr));
        friend_pushButton->setText(QApplication::translate("regroup_interface", "\345\245\275\345\217\213", nullptr));
        family_pushButton->setText(QApplication::translate("regroup_interface", "\345\256\266\344\272\272", nullptr));
        colleague_pushButton->setText(QApplication::translate("regroup_interface", "\345\220\214\344\272\213", nullptr));
        classmate_pushButton->setText(QApplication::translate("regroup_interface", "\345\220\214\345\255\246", nullptr));
        blacklist_pushButton->setText(QApplication::translate("regroup_interface", "\351\273\221\345\220\215\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class regroup_interface: public Ui_regroup_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGROUP_INTERFACE_H
