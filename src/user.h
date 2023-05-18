#ifndef USER_H
#define USER_H
#include <QCoreApplication>
#include <string>
#include <QFile>
#include <QTextStream>
#include <conio.h>
#include <QDir>

using namespace std;
//宏定义
#define UNLEN 5//用户名最大长度
#define PWDLEN 10//密码最大长度
typedef struct
{
    QString username;
    QString password;
}User;
/*用户管理模块*/
QString EnterPassword();//输入密码，返回值为输入的密码
bool JudgeUser(User user);//判断用户名和密码是否存在、是否匹配
void encryption(string& c, int a[]);//对写入文件的密码进行加密操作
void decode(string& c,int a[]);//解密
int regUser(User user);//注册用户

#endif // USER_H
