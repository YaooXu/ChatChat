/********************************************************************************
** Form generated from reading UI file 'dialogrec.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGREC_H
#define UI_DIALOGREC_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DialogRec
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_path;
    QPushButton *pushButton_3;
    QLabel *label_3;
    QLabel *label_map;

    void setupUi(QDialog *DialogRec)
    {
        if (DialogRec->objectName().isEmpty())
            DialogRec->setObjectName(QString::fromUtf8("DialogRec"));
        DialogRec->resize(592, 517);
        pushButton = new QPushButton(DialogRec);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(180, 300, 51, 41));
        pushButton_2 = new QPushButton(DialogRec);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(260, 300, 41, 41));
        label = new QLabel(DialogRec);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 40, 531, 101));
        label_2 = new QLabel(DialogRec);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 170, 111, 41));
        lineEdit = new QLineEdit(DialogRec);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(210, 170, 171, 41));
        lineEdit_path = new QLineEdit(DialogRec);
        lineEdit_path->setObjectName(QString::fromUtf8("lineEdit_path"));
        lineEdit_path->setGeometry(QRect(210, 230, 171, 41));
        pushButton_3 = new QPushButton(DialogRec);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(390, 230, 61, 41));
        label_3 = new QLabel(DialogRec);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 230, 141, 41));
        label_map = new QLabel(DialogRec);
        label_map->setObjectName(QString::fromUtf8("label_map"));
        label_map->setGeometry(QRect(70, 70, 210, 150));
        label_map->raise();
        pushButton->raise();
        pushButton_2->raise();
        label->raise();
        label_2->raise();
        lineEdit->raise();
        lineEdit_path->raise();
        pushButton_3->raise();
        label_3->raise();

        retranslateUi(DialogRec);
        QObject::connect(pushButton_2, SIGNAL(clicked()), DialogRec, SLOT(close()));
        QObject::connect(pushButton, SIGNAL(clicked()), DialogRec, SLOT(accept()));

        QMetaObject::connectSlotsByName(DialogRec);
    } // setupUi

    void retranslateUi(QDialog *DialogRec)
    {
        DialogRec->setWindowTitle(QApplication::translate("DialogRec", "Dialog", nullptr));
        pushButton->setText(QApplication::translate("DialogRec", "\346\230\257", nullptr));
        pushButton_2->setText(QApplication::translate("DialogRec", "\345\220\246", nullptr));
        label->setText(QString());
        label_2->setText(QApplication::translate("DialogRec", "\346\226\207\344\273\266\345\220\215\357\274\232", nullptr));
        pushButton_3->setText(QApplication::translate("DialogRec", "..", nullptr));
        label_3->setText(QApplication::translate("DialogRec", "\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        label_map->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogRec: public Ui_DialogRec {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGREC_H
