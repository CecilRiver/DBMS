/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *Qusername;
    QLineEdit *Qpassword;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QString::fromUtf8("login"));
        login->resize(400, 300);
        label = new QLabel(login);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 60, 71, 31));
        label_2 = new QLabel(login);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 100, 71, 31));
        pushButton = new QPushButton(login);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(80, 190, 91, 31));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-radius:10px;\n"
"border:2px solid #000000;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ecf5ff;\n"
"    color: #FF3030;\n"
"}"));
        pushButton_2 = new QPushButton(login);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(240, 190, 91, 31));
        pushButton_2->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-radius:10px;\n"
"border:2px solid #000000;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ecf5ff;\n"
"    color: #FF3030;\n"
"}"));
        Qusername = new QLineEdit(login);
        Qusername->setObjectName(QString::fromUtf8("Qusername"));
        Qusername->setGeometry(QRect(140, 60, 171, 31));
        Qusername->setStyleSheet(QString::fromUtf8("border-radius:10px;\n"
"border:2px solid #000000;"));
        Qpassword = new QLineEdit(login);
        Qpassword->setObjectName(QString::fromUtf8("Qpassword"));
        Qpassword->setGeometry(QRect(140, 100, 171, 31));
        Qpassword->setStyleSheet(QString::fromUtf8("border-radius:10px;\n"
"border:2px solid #000000;"));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("login", "<html><head/><body><p><span style=\" font-weight:700;\">\347\224\250\346\210\267\345\220\215\357\274\232</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("login", "<html><head/><body><p><span style=\" font-weight:700;\">\345\257\206\347\240\201\357\274\232</span></p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("login", "\346\263\250\345\206\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("login", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
