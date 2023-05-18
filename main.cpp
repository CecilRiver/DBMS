#include "widget.h"
#include "login.h"
#include <QApplication>
#include<QRegularExpression>
#include"btree.h";

int main(int argc, char *argv[])
{

    BTree newBTree(3); // 创建一个新的 B 树
       newBTree.readFromFile("D://download//DBMS1.0//DBMS//123//TEST//TEST//ww.txt");
       qDebug()<<newBTree.search("a");
       qDebug()<<newBTree.search("c");
    QApplication a(argc, argv);
    login l;
    l.show();
    return a.exec();
}

