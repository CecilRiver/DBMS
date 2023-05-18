#include"user.h"
#include<iostream>
#include"convert.h"
/*用户管理模块*/

//用整型数组进行加密
int a[] = {4,5,3,2,4,5,1};
//输入密码，返回值为输入的密码
QString EnterPassword()
{
    char password[100];
    int index = 0;
    while(1)
    {
        char ch;
        ch = getch();
        //退格键
        if(ch == 8)
        {
            if(index != 0)
            {
                cout << char(8) << " "<<char(8);
                index--;
            }
        }
        //回车键
        else if(ch=='\r')
        {
            password[index] = '\0';
            cout << endl;
            break;
        }
        //密码支持英文字母（大小写）和数字
        else if((ch<='Z'&&ch>='A')||(ch<='z'&&ch>='a')||(ch<='9'&&ch>='0'))
        {
            cout<<"*";
            password[index++] = ch;
        }

    }

    string p(password);
    QString ps = QString::fromStdString(p);
    return ps;

}

//判断用户名和密码是否存在、是否匹配
bool JudgeUser(User user)
{
    int usernum = 0;
    QString u,p;
    //指定文件

    //QFile inputFile1(QDir::currentPath()+"/user.txt");
    QFile inputFile1("D:/download/DBMS1.0/DBMS/user.txt");
    //只读打开
    if(!inputFile1.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        cout << "fail to open user file!"<<endl;
        return false;
    }

    QTextStream in1(&inputFile1);
    //文件第一行是用户数量
    usernum = in1.readLine().toInt();
    for(int i =0;i<usernum;i++)
    {
        u = in1.readLine();
        p = in1.readLine();
        string u1,p1;
        u1 = u.toStdString();
        p1 = p.toStdString();
        decode(p1,a);
        u = stringtoqstring(u1);
        p = stringtoqstring(p1);
        //匹配成功
        if(u==user.username && p==user.password)
            return true;

    }
    //匹配失败
    inputFile1.close();
    return false;
}

//对写入文件的密码进行加密操作
void encryption(string& c, int a[])
{
    for(int i =0,j=0;c[j];j++,i=(i+1)%7)
    {
        c[j] += a[i];
        c[j] %= 90;
    }
}

//解密
void decode(string& c,int a[])
{
    for(int i =0,j=0;c[j];j++,i=(i+1)%7)
    {
        c[j] -=a[i];
        if(c[j] < 48)
        {
            c[j] += 90;
        }
    }
}

//注册用户
int regUser(User user)
{
    vector<QString> lines;

    //检查用户名和密码规范
    if(user.username.size()>UNLEN||user.password.size()>PWDLEN) return 2;
        for(int i=0;i<user.username.size();i++)
        {
            if(!((user.username[i]<='z'&&user.username[i]>='a')||(user.username[i]<='Z'&&user.username[i]>='A')||(user.username[i]<='9'&&user.username[i]>='0'))) return 2;
        }
        for(int i=0;i<user.password.size();i++)
        {
            if(!((user.password[i]<='z'&&user.password[i]>='a')||(user.password[i]<='Z'&&user.password[i]>='A')||(user.password[i]<='9'&&user.password[i]>='0'))) return 2;
        }

     int usernum = 0;
     //指定文件

     //QFile f1(QDir::currentPath()+"/user.txt");
     QFile f1("D:/download/DBMS1.0/DBMS/user.txt");

        if(!f1.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            cout<<"用户文件打开失败!"<<endl;
            return 3;
        }

      //读取文件信息
        QTextStream in1(&f1);
            usernum = in1.readLine().toInt();
            for(int i=0;i<usernum;i++)
            {
                QString u,p;
                u = in1.readLine();
                lines.push_back(u);
                p = in1.readLine();
                lines.push_back(p);
                //找到用户名，即用户名已存在
                if(u==user.username)
                    return 1;
            }

        //未找到相同的用户名，则写入文件
            f1.close();
                f1.open(QIODevice::WriteOnly|QIODevice::Text);
                usernum++;
                //十进制数字转为QString
                QString qusernum = QString::number(usernum,10);
                QTextStream qts1(&f1);
                qts1<<qusernum<<Qt::endl;
                   for (vector<QString>::iterator iter=lines.begin();iter!=lines.end();iter++)
                   {
                       qts1<<(*iter)<<Qt::endl;
                   }
                   string p1 = user.password.toStdString();
                   //密码加密
                   encryption(p1,a);
                   QString p = QString::fromStdString(p1);
                   qts1<<user.username<<Qt::endl;
                   qts1<<p<<Qt::endl;
                   f1.flush();
                   f1.close();

                   //创建用户的表空间文件
                   QDir *temp = new QDir;

                   QString folder = "D:/download/DBMS1.0/DBMS/";
                   folder += user.username;
                   bool exist = temp->exists(folder);
                   if(!exist)
                   {
                       bool ok = temp->mkdir(folder);
                       if(ok)
                       {
                           QFile f2(folder+"/database.txt");
                           f2.open(QIODevice::WriteOnly|QIODevice::Text);
                           QTextStream qts4(&f2);
                           qts4<<QString::number(0,10)<<Qt::endl;
                           f2.flush();
                           f2.close();
                           return 0;
                       }

                       else
                       {

                           return 3;
                       }
                   }

                   return 0;

}
