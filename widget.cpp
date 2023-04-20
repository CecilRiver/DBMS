#include "widget.h"
#include "ui_widget.h"
#include"SQLanalysis.h"
#include"database.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

//设置用户名
 void Widget:: SetUser(QString username)
 {
     user.username = username;
 }


void Widget::on_Execute_clicked()
{

    ui->textBrowser->clear();
    QString curuser = user.username;

    QString statement = ui->Qstatements->toPlainText();

    QRegExp reg("use(?:\\s*)bjtuSQL(?:\\s*);",Qt::CaseInsensitive);
    if(reg.indexIn(statement) >=0)
    {
        DBname = QString();
        ui->textBrowser->setText("RETURN TO databases!");
        return ;
    }

    if(DBname.isNull())
    {
        vector<QString> sqlkey;
        int sqlType = sqlAnalysis(statement,sqlkey);


            switch(sqlType)
             {
             //创建数据库
              case 0:
                if(createDBEntity(curuser,sqlkey.at(0).toUpper()))
                {
                    ui->textBrowser->setText("Create database successfully!");
                }

                 else
                 {
                    ui->textBrowser->setText("Failed to create!");
                 }
                 break;
                //重命名数据库
            case 1:
                if(renameDBEntity(curuser,sqlkey.at(0).toUpper(),sqlkey.at(1).toUpper()))
                {
                    ui->textBrowser->setText("Rename database successfully!");
                }
                else
                {
                    ui->textBrowser->setText("Failed to rename databse!");

                }
                break;
                //删除数据库
            case 2:
                if(dropDBEntity(curuser,sqlkey.at(0).toUpper()))
                {
                    ui->textBrowser->setText("Drop database successfully!");
                }
                else
                {
                     ui->textBrowser->setText("Failed to drop database!");
                }
                break;
            case 3://使用数据库
                if(useDBEntity(curuser,sqlkey.at(0).toUpper()))
                {
                    DBname = sqlkey.at(0).toUpper();
                    ui->textBrowser->setText("Database changed!");

                }
                else
                {
                   ui->textBrowser->setText("Failed to use this database!");
                }
                break;
              //展示数据库
            case 4:
            {
                QString databases;
                if(showdatabases(curuser,databases))
                {
                    ui->textBrowser->setText(databases);
                }
                else
               {
                    ui->textBrowser->setText("Failed to show databases!");

               }
                break;
            }
                //初始化数据库
            case 5:
                if(initDBEntity(curuser,sqlkey.at(0).toUpper()))
                {
                    ui->textBrowser->setText("Initialize database successfully!");
                }
                else
                {
                     ui->textBrowser->setText("Failed to initialize database!");
                }
                break;

            case -1:
                 ui->textBrowser->setText("syntax error!");
                break;
            default:
                break;


             }
    }
    else
    {
        vector<QString> sqlkey;
        int sqlType = sqlAnalysisTable(statement,sqlkey,DBname);

        switch(sqlType)
        {
            case 0:
            if(createTable(curuser,DBname,sqlkey))
            {
                ui->textBrowser->setText("create table successfully!");
            }
            else
            {
                ui->textBrowser->setText("Failed to create table!");
            }
                 break;

            case 1:
            if(insertIntoTable(curuser,DBname,sqlkey))
            {

                  ui->textBrowser->append("insert into table successfully!");
            }
            else
            {
               ui->textBrowser->setText("Failed to insert into table!");
            }


           break;

        case -1:
             ui->textBrowser->setText("syntax error!");
            break;

           default:
            break;


        }

    }



}


void Widget::on_pushButton_clicked()
{
    if(backupDBEntity(user.username))
    {
        cout<<"Back up database successfully!"<<endl;
    }else
    {
        cout<<"Fail to back up database!"<<endl;
    }
}

