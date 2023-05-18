#ifndef DATABASE_H
#define DATABASE_H

#include <QCoreApplication>
#include<QFile>
#include <string>
#include <QFile>
#include <QTextStream>
#include<stdio.h>
#include<iostream>
#include<vector>
#include <QDir>

using namespace std;
//在屏幕上打印当前用户的所有数据库名
bool showdatabases(QString user,QString& databases);
//创建数据库实体
bool createDBEntity(QString user,QString DBname);
//重命名数据库实体
bool renameDBEntity(QString user,QString newName,QString oldName);
//删除数据库实体
bool dropDBEntity(QString user,QString DBname);
//使用数据库
bool useDBEntity(QString user,QString DBname);
//初始化数据库
bool initDBEntity(QString user,QString DBname);
//备份数据库
bool backupDBEntity(QString user);
//删除文件或文件夹
bool DeleteFileOrFolder(QString &strPath);

#endif // DATABASE_H
