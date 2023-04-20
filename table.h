#ifndef TABLE_H
#define TABLE_H
#include <vector>
#include <set>
#include <QCoreApplication>
using namespace std;
typedef struct
{
    //字段名
    QString name;
    //字段类型
    QString type;
}Field;
typedef struct
{
    //约束条件名
    QString name;
    //约束条件类型，0代表主键，1代表外键，2代表unique，3代表not null，4代表check，5代表default
    int type;
    //施加约束的列，主键允许加于多列

    vector<QString> colnos;
    //外键需要
    //参考的表名
    QString outertable;
    //参考的列名
    QString outerprino;

    //check需要
    //0代表是连续型范围，存在最大和最小值；1代表是离散型范围，用集合表示，值从集合的元素中选择
    int checktype;
    //最大值
    QString max;
    //最小值
    QString min;
    //取值的集合
    set<QString> valueset;

    //defalut需要
    //默认值
    QString defaultvalue;
}Constraint;
/*表管理模块*/

//创建表
bool createTable(QString user,QString DBname,vector<QString> sqlkey);
//插入数值
bool insertIntoTable(QString user,QString DBname,vector<QString> sqlkey);



#endif // TABLE_H
