#ifndef SQLANALYSIS_H
#define SQLANALYSIS_H
#include <QCoreApplication>
#include <vector>
#include<QRegularExpression>
#include<QDebug>
#include"table.h"
using namespace std;
/*SQL语句分析*/
//解析sql语法并返回各部分内容
int sqlAnalysis(QString sql,vector<QString> &sqlkey);

int sqlAnalysisTable(QString sql,vector<QString> &sqlkey,QString DBname);
#endif // SQLANALYSIS_H
