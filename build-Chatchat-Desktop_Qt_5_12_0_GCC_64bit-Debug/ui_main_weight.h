/********************************************************************************
** Form generated from reading UI file 'main_weight.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WEIGHT_H
#define UI_MAIN_WEIGHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_Weight
{
public:

    void setupUi(QWidget *main_Weight)
    {
        if (main_Weight->objectName().isEmpty())
            main_Weight->setObjectName(QString::fromUtf8("main_Weight"));
        main_Weight->resize(623, 1244);

        retranslateUi(main_Weight);

        QMetaObject::connectSlotsByName(main_Weight);
    } // setupUi

    void retranslateUi(QWidget *main_Weight)
    {
        main_Weight->setWindowTitle(QApplication::translate("main_Weight", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class main_Weight: public Ui_main_Weight {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WEIGHT_H
