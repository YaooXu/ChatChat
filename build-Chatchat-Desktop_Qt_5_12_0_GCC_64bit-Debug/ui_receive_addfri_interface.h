/********************************************************************************
** Form generated from reading UI file 'receive_addfri_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RECEIVE_ADDFRI_INTERFACE_H
#define UI_RECEIVE_ADDFRI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_receive_addfri_interface
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_ID;
    QLabel *label_Name;
    QPushButton *acceptButton;
    QPushButton *refuseButton;
    QComboBox *comboBox;

    void setupUi(QDialog *receive_addfri_interface)
    {
        if (receive_addfri_interface->objectName().isEmpty())
            receive_addfri_interface->setObjectName(QString::fromUtf8("receive_addfri_interface"));
        receive_addfri_interface->resize(400, 300);
        label = new QLabel(receive_addfri_interface);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 20, 171, 20));
        label_2 = new QLabel(receive_addfri_interface);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 70, 67, 17));
        label_3 = new QLabel(receive_addfri_interface);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 130, 67, 17));
        label_ID = new QLabel(receive_addfri_interface);
        label_ID->setObjectName(QString::fromUtf8("label_ID"));
        label_ID->setGeometry(QRect(210, 70, 67, 17));
        label_Name = new QLabel(receive_addfri_interface);
        label_Name->setObjectName(QString::fromUtf8("label_Name"));
        label_Name->setGeometry(QRect(210, 130, 67, 17));
        acceptButton = new QPushButton(receive_addfri_interface);
        acceptButton->setObjectName(QString::fromUtf8("acceptButton"));
        acceptButton->setGeometry(QRect(60, 250, 89, 25));
        refuseButton = new QPushButton(receive_addfri_interface);
        refuseButton->setObjectName(QString::fromUtf8("refuseButton"));
        refuseButton->setGeometry(QRect(210, 250, 89, 25));
        comboBox = new QComboBox(receive_addfri_interface);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(140, 180, 86, 25));

        retranslateUi(receive_addfri_interface);

        QMetaObject::connectSlotsByName(receive_addfri_interface);
    } // setupUi

    void retranslateUi(QDialog *receive_addfri_interface)
    {
        receive_addfri_interface->setWindowTitle(QApplication::translate("receive_addfri_interface", "Dialog", nullptr));
        label->setText(QApplication::translate("receive_addfri_interface", "\346\202\250\346\224\266\345\210\260\344\272\206\346\267\273\345\212\240\345\245\275\345\217\213\350\257\267\346\261\202", nullptr));
        label_2->setText(QApplication::translate("receive_addfri_interface", "ID", nullptr));
        label_3->setText(QApplication::translate("receive_addfri_interface", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_ID->setText(QApplication::translate("receive_addfri_interface", "TextLabel", nullptr));
        label_Name->setText(QApplication::translate("receive_addfri_interface", "TextLabel", nullptr));
        acceptButton->setText(QApplication::translate("receive_addfri_interface", "\346\216\245\345\217\227", nullptr));
        refuseButton->setText(QApplication::translate("receive_addfri_interface", "\346\213\222\347\273\235", nullptr));
        comboBox->setItemText(0, QApplication::translate("receive_addfri_interface", "\345\245\275\345\217\213", nullptr));
        comboBox->setItemText(1, QApplication::translate("receive_addfri_interface", "\344\272\262\344\272\272", nullptr));
        comboBox->setItemText(2, QApplication::translate("receive_addfri_interface", "\345\220\214\344\272\213", nullptr));
        comboBox->setItemText(3, QApplication::translate("receive_addfri_interface", "\345\220\214\345\255\246", nullptr));
        comboBox->setItemText(4, QApplication::translate("receive_addfri_interface", "\351\273\221\345\220\215\345\215\225", nullptr));

    } // retranslateUi

};

namespace Ui {
    class receive_addfri_interface: public Ui_receive_addfri_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RECEIVE_ADDFRI_INTERFACE_H
