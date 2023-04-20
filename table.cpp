#include "table.h"
#include<QDir>
#include<QTextStream>



bool createTable(QString user,QString DBname,vector<QString> sqlkey)
{
    //在对应的数据库文件夹下创建表文件夹
    sqlkey.at(0) = sqlkey.at(0).toUpper();
    QString folder = QDir::currentPath()+"/"+user+"/"+DBname+"/"+sqlkey.at(0);
    QDir *temp = new QDir;
    bool exist = temp->exists(folder);
    if(!exist)
    {
        if(!temp->mkdir(folder))
            return false;
    }
    //在表文件夹下创建column.txt，保存表的列名和属性
    folder += "/column.txt";
    QFile file(folder);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        return false;
    }
    else
    {
         QTextStream qts1(&file);
         for(unsigned int i = 1;i<sqlkey.size();i = i+2)
             qts1<<sqlkey.at(i)+"#"+sqlkey.at(i+1)<<Qt::endl;

    }
    //database.txt中对应数据库里的表数量加一
    folder = QDir::currentPath()+"/"+user+"/database.txt";
    QFile file1(folder);
    QStringList list;

    //读取文件
    if(!file1.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        return false;
    }
    QTextStream in1(&file1);
    vector<QString> lines;
     int databaseNum = in1.readLine().toInt();
     int number;
     for(int i=0;i<databaseNum;i++)
     {
         QString temp;
         temp = in1.readLine();
         list = temp.split("#");
         //找到对应数据库
         if(list.at(0)==DBname)
         {
          number = list.at(2).toInt();
          number++;
          lines.push_back(list.at(0)+"#"+list.at(1)+"#"+QString::number(number,10));

         }else
         {
          lines.push_back(temp);
         }
     }
     file1.close();

     file1.open(QIODevice::WriteOnly|QIODevice::Text);
     //十进制数字转为QString
     QString num = QString::number(databaseNum,10);
     QTextStream qts(&file1);
     //写入该用户拥有的数据库数量
     qts<<num<<Qt::endl;
     //写入其他的数据
     for (vector<QString>::iterator iter=lines.begin();iter!=lines.end();iter++)
     {
         qts<<(*iter)<<Qt::endl;
     }


     //创建记录文件，第一行写上当前记录数：0
     QString folder_temp = QDir::currentPath()+"/"+user+"/"+DBname+"/"+sqlkey.at(0)+"/record.txt";
     QFile file_temp(folder_temp);
     if(!file_temp.open(QIODevice::WriteOnly|QIODevice::Text))
     {
         return false;
     }
     else
     {
          QTextStream qts_temp(&file_temp);
           qts_temp<<QString::number(0);
     }

     return true;




}

//插入数值
bool insertIntoTable(QString user,QString DBname,vector<QString> sqlkey)
{
    sqlkey.at(0) = sqlkey.at(0).toUpper();
    //打开记录文件
    QString folder = QDir::currentPath()+"/"+user+"/"+DBname+"/"+sqlkey.at(0)+"/record.txt";
    QFile file(folder);

    if(!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        return false;
    }
    //记录数+1
    QString firstLine = file.readLine();
        file.seek(0);
        int temp = firstLine.toInt();
        temp++;
        firstLine = QString::number(temp);
        file.write(firstLine.toUtf8());
        file.close();
    //追加
    if(!file.open(QIODevice::WriteOnly|QIODevice::Append))
    {
        return false;
    }
    else
    {
         QTextStream qts1(&file);
         int number = sqlkey.at(1).toInt();
         qts1<<Qt::endl;
         for(unsigned int i = 2+number;i<sqlkey.size();i = i+number)
         {
             for(int j = 0;j<number;j++)
             {
                 if(j==number-1)
                 {
                     qts1<<sqlkey.at(i+j);
                 }
                 else
                 {
                     qts1<<sqlkey.at(i+j)+"#";
                 }

             }
             qts1<<Qt::endl;
         }


    }
    file.close();
    return true;

}

