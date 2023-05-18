#include "login.h"
#include "ui_login.h"
#include <string>
#include <iostream>
#include "widget.h"
#include <QMessageBox>
#include"user.h"

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    //设置密码不可见
    ui->Qpassword->setEchoMode(QLineEdit::Password);
}

login::~login()
{
    delete ui;
}


void login::on_pushButton_2_clicked()
{
    User user;
    //读取用户名,用户名以大写方式接收
    user.username=ui->Qusername->text().toUpper();
    //读取密码
    user.password=ui->Qpassword->text();
    if (JudgeUser(user))
       {
        cout<<"login successfully"<<endl;
        this->close();
        Widget *w=new Widget;
        w->show();
        w->SetUser(user.username);

    }
    else
    {
        QMessageBox::warning (this,tr("fail to log in"),tr("error"),QMessageBox::Ok);
        ui->Qusername->clear();
        ui->Qpassword->clear();
    }

}

void login::on_pushButton_clicked()
{
    User user;
    //读取用户名
    user.username=ui->Qusername->text().toUpper();
    //读取密码
    user.password=ui->Qpassword->text();

    switch(regUser(user))
    {
    case 0:
        cout<<"Registion success!"<<endl;
        break;
    case 1:
        cout<<"Registion failed because this user exists!"<<endl;
        break;
    case 2:
        cout<<"Registion failed because account or password is not valid!"<<endl;//账号最多5位最少1位，密码最多10位最少1位，只能由字母（区分大小写）和数字组成
        break;
    case 3:
        cout<<"Registion failed because of system error!"<<endl;//一般是文件不存在
        break;
    default:
        break;
    }

}

