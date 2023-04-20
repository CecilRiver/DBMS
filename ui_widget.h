/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QTextBrowser *textBrowser;
    QPushButton *Execute;
    QTextEdit *Qstatements;
    QPushButton *pushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1041, 673);
        textBrowser = new QTextBrowser(Widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(510, 100, 381, 261));
        Execute = new QPushButton(Widget);
        Execute->setObjectName(QString::fromUtf8("Execute"));
        Execute->setGeometry(QRect(190, 370, 121, 41));
        Execute->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-radius:10px;\n"
"border:2px solid #000000;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ecf5ff;\n"
"    color: #409eff;\n"
"}"));
        Qstatements = new QTextEdit(Widget);
        Qstatements->setObjectName(QString::fromUtf8("Qstatements"));
        Qstatements->setGeometry(QRect(40, 100, 441, 261));
        Qstatements->setStyleSheet(QString::fromUtf8(""));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(50, 370, 121, 41));
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"border-radius:10px;\n"
"border:2px solid #000000;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #ecf5ff;\n"
"    color: #409eff;\n"
"}"));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        Execute->setText(QCoreApplication::translate("Widget", "\346\211\247\350\241\214SQL\350\257\255\345\217\245", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "\347\224\250\346\210\267\346\225\260\346\215\256\345\272\223\345\244\207\344\273\275", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
