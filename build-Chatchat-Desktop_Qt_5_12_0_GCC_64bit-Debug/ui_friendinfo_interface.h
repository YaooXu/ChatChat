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
#include <QtWidgets/QPushButton>

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
    QPushButton *iconButton;
    QLabel *label_ID;
    QLabel *label_name;
    QLabel *label_sex;
    QLabel *label_tel;
    QLabel *label_description;

    void setupUi(QDialog *friendinfo_interface)
    {
        if (friendinfo_interface->objectName().isEmpty())
            friendinfo_interface->setObjectName(QString::fromUtf8("friendinfo_interface"));
        friendinfo_interface->resize(400, 348);
        label = new QLabel(friendinfo_interface);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 40, 21, 17));
        label_2 = new QLabel(friendinfo_interface);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 80, 67, 17));
        label_3 = new QLabel(friendinfo_interface);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 170, 67, 17));
        label_4 = new QLabel(friendinfo_interface);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 210, 67, 17));
        label_5 = new QLabel(friendinfo_interface);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(70, 250, 67, 17));
        label_6 = new QLabel(friendinfo_interface);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(70, 290, 81, 17));
        label_7 = new QLabel(friendinfo_interface);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(160, 10, 71, 17));
        iconButton = new QPushButton(friendinfo_interface);
        iconButton->setObjectName(QString::fromUtf8("iconButton"));
        iconButton->setGeometry(QRect(200, 80, 89, 71));
        label_ID = new QLabel(friendinfo_interface);
        label_ID->setObjectName(QString::fromUtf8("label_ID"));
        label_ID->setGeometry(QRect(200, 40, 67, 17));
        label_name = new QLabel(friendinfo_interface);
        label_name->setObjectName(QString::fromUtf8("label_name"));
        label_name->setGeometry(QRect(200, 170, 67, 17));
        label_sex = new QLabel(friendinfo_interface);
        label_sex->setObjectName(QString::fromUtf8("label_sex"));
        label_sex->setGeometry(QRect(200, 210, 67, 17));
        label_tel = new QLabel(friendinfo_interface);
        label_tel->setObjectName(QString::fromUtf8("label_tel"));
        label_tel->setGeometry(QRect(200, 250, 67, 17));
        label_description = new QLabel(friendinfo_interface);
        label_description->setObjectName(QString::fromUtf8("label_description"));
        label_description->setGeometry(QRect(200, 290, 67, 17));

        retranslateUi(friendinfo_interface);

        QMetaObject::connectSlotsByName(friendinfo_interface);
    } // setupUi

    void retranslateUi(QDialog *friendinfo_interface)
    {
        friendinfo_interface->setWindowTitle(QApplication::translate("friendinfo_interface", "Dialog", nullptr));
        label->setText(QApplication::translate("friendinfo_interface", "ID", nullptr));
        label_2->setText(QApplication::translate("friendinfo_interface", "\345\244\264\345\203\217", nullptr));
        label_3->setText(QApplication::translate("friendinfo_interface", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_4->setText(QApplication::translate("friendinfo_interface", "\346\200\247\345\210\253", nullptr));
        label_5->setText(QApplication::translate("friendinfo_interface", "\347\224\265\350\257\235\345\217\267\347\240\201", nullptr));
        label_6->setText(QApplication::translate("friendinfo_interface", "\344\270\252\344\272\272\346\217\217\350\277\260", nullptr));
        label_7->setText(QApplication::translate("friendinfo_interface", "\345\245\275\345\217\213\344\277\241\346\201\257", nullptr));
        iconButton->setText(QApplication::translate("friendinfo_interface", "PushButton", nullptr));
        label_ID->setText(QApplication::translate("friendinfo_interface", "TextLabel", nullptr));
        label_name->setText(QApplication::translate("friendinfo_interface", "TextLabel", nullptr));
        label_sex->setText(QApplication::translate("friendinfo_interface", "TextLabel", nullptr));
        label_tel->setText(QApplication::translate("friendinfo_interface", "TextLabel", nullptr));
        label_description->setText(QApplication::translate("friendinfo_interface", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class friendinfo_interface: public Ui_friendinfo_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDINFO_INTERFACE_H
