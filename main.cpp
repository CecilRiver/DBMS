#include "widget.h"
#include "login.h"
#include <QApplication>
#include<QRegularExpression>

int main(int argc, char *argv[])
{



    QApplication a(argc, argv);
    login l;
    l.show();
    return a.exec();
}

