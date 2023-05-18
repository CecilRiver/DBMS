#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QFileDialog>
#include <string>
#include <iostream>
#include <QDebug>
#include <vector>
#include <map>
# include <bitset>
# include <fstream>
//#include <bits/stdc++.h>
#include "user.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void SetUser(QString username);

private slots:

   // void on_pushButton_clicked();

  //  void on_pushButton_2_clicked();

    void on_Execute_clicked();

    void on_pushButton_clicked();

private:
    Ui::Widget *ui;
    User user;
    QString DBname;




};
#endif // WIDGET_H
