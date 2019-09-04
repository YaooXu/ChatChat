/********************************************************************************
** Form generated from reading UI file 'addfri_interface.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDFRI_INTERFACE_H
#define UI_ADDFRI_INTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_addfri_interface
{
public:
    QLabel *label;
    QLineEdit *lineEdit;
    QComboBox *comboBox;
    QPushButton *pushButton;

    void setupUi(QDialog *addfri_interface)
    {
        if (addfri_interface->objectName().isEmpty())
            addfri_interface->setObjectName(QString::fromUtf8("addfri_interface"));
        addfri_interface->resize(400, 300);
        label = new QLabel(addfri_interface);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(126, 40, 101, 20));
        lineEdit = new QLineEdit(addfri_interface);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(120, 90, 113, 25));
        comboBox = new QComboBox(addfri_interface);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(130, 150, 86, 25));
        pushButton = new QPushButton(addfri_interface);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(120, 220, 89, 25));

        retranslateUi(addfri_interface);

        QMetaObject::connectSlotsByName(addfri_interface);
    } // setupUi

    void retranslateUi(QDialog *addfri_interface)
    {
        addfri_interface->setWindowTitle(QApplication::translate("addfri_interface", "Dialog", nullptr));
        label->setText(QApplication::translate("addfri_interface", "\350\276\223\345\205\245\345\245\275\345\217\213\347\232\204ID", nullptr));
        comboBox->setItemText(0, QApplication::translate("addfri_interface", "\345\245\275\345\217\213", nullptr));
        comboBox->setItemText(1, QApplication::translate("addfri_interface", "\345\256\266\344\272\272", nullptr));
        comboBox->setItemText(2, QApplication::translate("addfri_interface", "\345\220\214\344\272\213", nullptr));
        comboBox->setItemText(3, QApplication::translate("addfri_interface", "\345\220\214\345\255\246", nullptr));
        comboBox->setItemText(4, QApplication::translate("addfri_interface", "\351\273\221\345\220\215\345\215\225", nullptr));

        pushButton->setText(QApplication::translate("addfri_interface", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addfri_interface: public Ui_addfri_interface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDFRI_INTERFACE_H
