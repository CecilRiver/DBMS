#ifndef TABLE_H
#define TABLE_H
#include"btree.h"
#include <vector>
#include <set>
#include <QCoreApplication>
#include<QDebug>
using namespace std;


//创建表
bool createTable(QString user,QString DBname,vector<QString> sqlkey);
//插入数值
bool insertIntoTable(QString user,QString DBname,vector<QString> sqlkey);
//删除表
bool dropTable(QString user,QString DBname,vector<QString> sqlkey);
//添加字段
bool addField(QString user,QString DBname,vector<QString> sqlkey);
//修改字段
bool modifyField(QString user,QString DBname,vector<QString> sqlkey);
//删除字段
bool dropField(QString user,QString DBname,vector<QString> sqlkey);
//创建索引
bool createIndex(QString user,QString DBname,vector<QString> sqlkey);
//删除文件或文件夹
bool DeleteFileOrFolder(QString &strPath);


#endif // TABLE_H
