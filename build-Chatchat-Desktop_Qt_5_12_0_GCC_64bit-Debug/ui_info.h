/********************************************************************************
** Form generated from reading UI file 'info.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFO_H
#define UI_INFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_info
{
public:
    QLabel *name;
    QLabel *ID;
    QLabel *sex;
    QLabel *tel;
    QLineEdit *name_edit;
    QPushButton *update;
    QLabel *Id_edit;
    QLineEdit *sex_edit;
    QLineEdit *tel_edit;
    QLabel *ques;
    QLineEdit *ques_edit;
    QLabel *ans;
    QLineEdit *ans_edit;
    QLabel *mood;
    QLineEdit *mood_edit;
    QPushButton *submit;
    QToolButton *photo;

    void setupUi(QWidget *info)
    {
        if (info->objectName().isEmpty())
            info->setObjectName(QString::fromUtf8("info"));
        info->resize(400, 524);
        name = new QLabel(info);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(20, 70, 67, 17));
        ID = new QLabel(info);
        ID->setObjectName(QString::fromUtf8("ID"));
        ID->setGeometry(QRect(20, 30, 67, 17));
        sex = new QLabel(info);
        sex->setObjectName(QString::fromUtf8("sex"));
        sex->setGeometry(QRect(10, 110, 67, 17));
        tel = new QLabel(info);
        tel->setObjectName(QString::fromUtf8("tel"));
        tel->setGeometry(QRect(10, 150, 67, 17));
        name_edit = new QLineEdit(info);
        name_edit->setObjectName(QString::fromUtf8("name_edit"));
        name_edit->setEnabled(false);
        name_edit->setGeometry(QRect(120, 60, 113, 25));
        update = new QPushButton(info);
        update->setObjectName(QString::fromUtf8("update"));
        update->setGeometry(QRect(100, 390, 89, 25));
        Id_edit = new QLabel(info);
        Id_edit->setObjectName(QString::fromUtf8("Id_edit"));
        Id_edit->setGeometry(QRect(120, 30, 171, 20));
        sex_edit = new QLineEdit(info);
        sex_edit->setObjectName(QString::fromUtf8("sex_edit"));
        sex_edit->setEnabled(false);
        sex_edit->setGeometry(QRect(120, 100, 113, 25));
        tel_edit = new QLineEdit(info);
        tel_edit->setObjectName(QString::fromUtf8("tel_edit"));
        tel_edit->setEnabled(false);
        tel_edit->setGeometry(QRect(120, 140, 113, 25));
        ques = new QLabel(info);
        ques->setObjectName(QString::fromUtf8("ques"));
        ques->setGeometry(QRect(10, 180, 67, 17));
        ques_edit = new QLineEdit(info);
        ques_edit->setObjectName(QString::fromUtf8("ques_edit"));
        ques_edit->setEnabled(false);
        ques_edit->setGeometry(QRect(120, 180, 181, 25));
        ans = new QLabel(info);
        ans->setObjectName(QString::fromUtf8("ans"));
        ans->setGeometry(QRect(10, 220, 67, 17));
        ans_edit = new QLineEdit(info);
        ans_edit->setObjectName(QString::fromUtf8("ans_edit"));
        ans_edit->setEnabled(false);
        ans_edit->setGeometry(QRect(120, 220, 113, 25));
        mood = new QLabel(info);
        mood->setObjectName(QString::fromUtf8("mood"));
        mood->setGeometry(QRect(20, 260, 67, 17));
        mood_edit = new QLineEdit(info);
        mood_edit->setObjectName(QString::fromUtf8("mood_edit"));
        mood_edit->setEnabled(false);
        mood_edit->setGeometry(QRect(120, 260, 181, 25));
        submit = new QPushButton(info);
        submit->setObjectName(QString::fromUtf8("submit"));
        submit->setGeometry(QRect(210, 390, 89, 25));
        photo = new QToolButton(info);
        photo->setObjectName(QString::fromUtf8("photo"));
        photo->setGeometry(QRect(280, 20, 91, 91));

        retranslateUi(info);

        QMetaObject::connectSlotsByName(info);
    } // setupUi

    void retranslateUi(QWidget *info)
    {
        info->setWindowTitle(QApplication::translate("info", "info", nullptr));
        name->setText(QApplication::translate("info", "\345\247\223\345\220\215", nullptr));
        ID->setText(QApplication::translate("info", "ID", nullptr));
        sex->setText(QApplication::translate("info", "   \346\200\247\345\210\253", nullptr));
        tel->setText(QApplication::translate("info", "   \347\224\265\350\257\235", nullptr));
        update->setText(QApplication::translate("info", "\346\233\264\346\226\260", nullptr));
        Id_edit->setText(QString());
        ques->setText(QApplication::translate("info", "\345\257\206\344\277\235\351\227\256\351\242\230", nullptr));
        ans->setText(QApplication::translate("info", "   \347\255\224\346\241\210", nullptr));
        mood->setText(QApplication::translate("info", "\345\277\203\346\203\205", nullptr));
        submit->setText(QApplication::translate("info", "\344\277\256\346\224\271", nullptr));
        photo->setText(QApplication::translate("info", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class info: public Ui_info {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_H
