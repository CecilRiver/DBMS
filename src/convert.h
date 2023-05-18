#ifndef CONVERT_H
#define CONVERT_H


#include <QCoreApplication>
#include <string>
using namespace std;
/*类型转换函数*/
string inttostring(int tempint);
string doubletostring(double d);
string floattostring(float f);
string qstringtostring(QString qs);
string booltostring(bool b);

QString inttoqstring(int i);
QString doubletoqstring(double d);
QString floattoqstring(float f);
QString booltoqstring(bool b);

int qstringtoint(QString qs);
float qstringtofloat(QString qs);
double qstringtodouble(QString qs);
bool qstringtobool(QString qs);

int stringtoint(string s);
float stringtofloat(string s);
double stringtodouble(string s);
QString stringtoqstring(string s);
bool stringtobool(string s);

#endif // CONVERT_H
