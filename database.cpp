#include"database.h"
#include"QDateTime"

//展示数据库
bool showdatabases(QString user,QString& databases)
{
    //QString folder = "D:/download/DBMS1.0/DBMS/"+user+"/database.txt";
    QString folder = QDir::currentPath()+"/"+user+"/database.txt";
    //打开文件
    QFile file(folder);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        std::cout<<"file fails to open!"<<Qt::endl;
        return false;
    }

     QTextStream in1(&file);
     int  databaseNum = in1.readLine().toInt();
     databases ="用户名："+user+" 下有"+QString::number(databaseNum) +"个数据库\n";
     QStringList list;
     QString temp;
     for(int i =0;i<databaseNum;i++)
     {
        temp = in1.readLine();
        list = temp.split("#");
        //databases += "  数据库名称："+list.at(0)+"  创建时间："+list.at(1)+"  其中表的数量："+list.at(2)+"\n";
        databases += " database name "+list.at(0)+"  Create time: "+list.at(1)+"  number of table :"+list.at(2)+"\n";
     }
      file.close();
      return true;
}
//创建数据库实体
bool createDBEntity(QString user,QString DBname)
{
    //获取系统现在的时间
    QDateTime begin_time = QDateTime::currentDateTime();
    QString begin =begin_time .toString("yyyy.MM.dd hh:mm:ss.zzz");

    QStringList list;
    vector<QString> lines;
    //QString folder = QDir::currentPath()+"/";
    QString folder = "D:/download/DBMS1.0/DBMS/";
    folder += user;
    folder += "/database.txt";
    int databaseNum = 0;
    QFile file(folder);


    //读取文件
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        std::cout<<"file fails to open!"<<Qt::endl;
        return false;
    }

    QTextStream in1(&file);
        databaseNum = in1.readLine().toInt();
        for(int i=0;i<databaseNum;i++)
        {
            QString temp;
            temp = in1.readLine();
            lines.push_back(temp);

            list = temp.split("#");

            //找到相同数据库名，即该数据库名已存在
            if(list.at(0)==DBname)
            {
                std::cout<<"this database already exists!"<<Qt::endl;
                return false;
            }
        }
        //未找到相同数据库名，则创建该数据库
        file.close();
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        databaseNum++;

        //十进制数字转为QString
        QString num = QString::number(databaseNum,10);
        QTextStream qts1(&file);
        //写入该用户拥有的数据库数量
        qts1<<num<<Qt::endl;
        //写入原本存在的数据
        for (vector<QString>::iterator iter=lines.begin();iter!=lines.end();iter++)
        {
            qts1<<(*iter)<<Qt::endl;
        }
        //写入新添加的数据
        DBname = DBname +"#"+begin+"#0";
         qts1<<DBname<<Qt::endl;

         return true;

}
//重命名数据库实体
bool renameDBEntity(QString user,QString oldName,QString newName)
{

    vector<QString> lines;
    QString folder = "D:/download/DBMS1.0/DBMS/";
    folder += user;
    folder += "/database.txt";
    int databaseNum = 0;
    QFile file(folder);

    QStringList list;

    //读取文件
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        std::cout<<"file fails to open!"<<Qt::endl;
        return false;
    }
     bool flag = false;
     QTextStream in1(&file);
     databaseNum = in1.readLine().toInt();
     for(int i=0;i<databaseNum;i++)
     {
         QString temp;
         temp = in1.readLine();
         list = temp.split("#");
         if(list.at(0)!=oldName)
         {
          lines.push_back(temp);
         }else
         {
             //新名称替代旧名称
             lines.push_back(newName+"#"+list.at(1)+"#"+list.at(2));
             flag = true;
         }

     }
     if(!flag)
     {
         std::cout<<"this database does not exist!"<<Qt::endl;
         return false;
     }
     file.close();
     //写入文件
     file.open(QIODevice::WriteOnly|QIODevice::Text);
     //十进制数字转为QString
     QString num = QString::number(databaseNum,10);
     QTextStream qts1(&file);
     //写入该用户拥有的数据库数量
     qts1<<num<<Qt::endl;
     //写入其他的数据
     for (vector<QString>::iterator iter=lines.begin();iter!=lines.end();iter++)
     {
         qts1<<(*iter)<<Qt::endl;
     }

     return true;
}
//删除数据库实体
bool dropDBEntity(QString user,QString DBname)
{
    vector<QString> lines;
    QString folder = "D:/download/DBMS1.0/DBMS/";
    folder += user;
    folder += "/database.txt";
    int databaseNum = 0;
    QFile file(folder);

    QStringList list;

    //读取文件
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        std::cout<<"file fails to open!"<<Qt::endl;
        return false;
    }
    bool flag = false;
    QTextStream in1(&file);
        databaseNum = in1.readLine().toInt();
        for(int i=0;i<databaseNum;i++)
        {
            QString temp;
            temp = in1.readLine();
            list = temp.split("#");
            if(list.at(0)!=DBname)
            {
             lines.push_back(temp);
            }else
            {
                //去除该数据库
                flag = true;
            }

        }
        if(!flag)
        {
            std::cout<<"this database does not exist!"<<Qt::endl;
            return false;
        }else
        {
            databaseNum--;
        }
        file.close();
        //写入文件
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        //十进制数字转为QString
        QString num = QString::number(databaseNum,10);
        QTextStream qts1(&file);
        //写入该用户拥有的数据库数量
        qts1<<num<<Qt::endl;
        //写入其他的数据
        for (vector<QString>::iterator iter=lines.begin();iter!=lines.end();iter++)
        {
            qts1<<(*iter)<<Qt::endl;
        }

        //删除文件夹
        QString folder1 = "D:/download/DBMS1.0/DBMS/"+user+"/"+DBname;
        DeleteFileOrFolder(folder1);

        return true;
}

//使用数据库
bool useDBEntity(QString user,QString DBname)
{
    //首先查看该数据库是否已经建立
    QStringList list;

    QString folder = "D:/download/DBMS1.0/DBMS/";
    folder += user;
    folder += "/database.txt";
    int databaseNum = 0;
    QFile file(folder);


    //读取文件
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        std::cout<<"file fails to open!"<<Qt::endl;
        return false;
    }
    bool flag = false;
    QTextStream in1(&file);
        databaseNum = in1.readLine().toInt();
        for(int i=0;i<databaseNum;i++)
        {
            QString temp;
            temp = in1.readLine();

            list = temp.split("#");

            //找到相同数据库名，即该数据库已存在
            if(list.at(0)==DBname)
            {
                flag = true;
                break;
            }
        }
        if(!flag)
        {
            //cout<<"This database does not exist！"<<endl;
            return false;
        }
       //再查看该数据库是否已经初始化
        folder ="D:/download/DBMS1.0/DBMS/"+user+"/"+DBname;
        QDir *temp = new QDir;
        bool exist = temp->exists(folder);
        if(!exist)
        {
           //cout<<"This database does not be initialized！"<<endl;
               return false;

        }else
            return true;

}

//初始化数据库
bool initDBEntity(QString user,QString DBname)
{
    //首先查找该数据库是否已经创建
    QStringList list;

    QString folder = "D:/download/DBMS1.0/DBMS/";
    folder += user;
    folder += "/database.txt";
    int databaseNum = 0;
    QFile file(folder);


    //读取文件
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        std::cout<<"file fails to open!"<<Qt::endl;
        return false;
    }
    bool flag = false;
    QTextStream in1(&file);
        databaseNum = in1.readLine().toInt();
        for(int i=0;i<databaseNum;i++)
        {
            QString temp;
            temp = in1.readLine();

            list = temp.split("#");

            //找到相同数据库名，即该数据库已存在
            if(list.at(0)==DBname)
            {
                flag = true;
                break;
            }
        }
        if(!flag)
        {
            //cout<<"This database does not exist！"<<endl;
            return false;
        }
        //创建该数据库文件夹
        folder = "D:/download/DBMS1.0/DBMS/"+user+"/"+DBname;
        QDir *temp = new QDir;
        bool exist = temp->exists(folder);
        if(!exist)
        {
           if(temp->mkdir(folder))
               return true;
            else
               return false;

        }else
            return true;


}

//备份数据库
bool backupDBEntity(QString user)
{
    vector<QString> lines;
    QString folder = "D:/download/DBMS1.0/DBMS/";
    folder += user;
    folder += "/BUdatabase.txt";
    QString source ="D:/download/DBMS1.0/DBMS/"+user+"/database.txt";

    QFile f1(source);
    if(!f1.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        std::cout<<"file fails to open!"<<Qt::endl;
        return false;
    }

    QTextStream in1(&f1);
    int databaseNum = in1.readLine().toInt();
        for(int i=0;i<databaseNum;i++)
        {
            QString temp;
            temp = in1.readLine();
            lines.push_back(temp);

        }

        f1.close();

        QFile f2(folder);
        f2.open(QIODevice::WriteOnly|QIODevice::Text);

        QString num = QString::number(databaseNum,10);
        QTextStream qts1(&f2);
        //备份数据库数量
        qts1<<num<<Qt::endl;
        //备份数据库
        for (vector<QString>::iterator iter=lines.begin();iter!=lines.end();iter++)
        {
            qts1<<(*iter)<<Qt::endl;
        }

        return true;

}
//删除文件或文件夹
bool DeleteFileOrFolder(QString &strPath)//要删除的文件夹或文件的路径
{
    if (strPath.isEmpty() || !QDir().exists(strPath))//是否传入了空的路径||路径是否存在
        return false;

    QFileInfo FileInfo(strPath);

    if (FileInfo.isFile())//如果是文件
        QFile::remove(strPath);
    else if (FileInfo.isDir())//如果是文件夹
    {
        QDir qDir(strPath);
        qDir.removeRecursively();
    }
    return true;
}
