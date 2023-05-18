#include "convert.h"
string inttostring(int tempint){
    char t[256];
    string s;
    sprintf(t, "%d", tempint);
    s = t;
    return s;
}

string doubletostring(double d)
{
    char t[256];
    string s;
    sprintf(t, "%lf", d);
    s = t;
    return s;
}

string floattostring(float f)
{
    char t[256];
    string s;
    sprintf(t, "%f", f);
    s = t;
    return s;
}

string qstringtostring(QString qs)
{
    return qs.toStdString();
}

string booltostring(bool b)
{
    if(b) return "T";
    else return "F";
}

int stringtoint(string s)
{
    return stoi(s);
}

float stringtofloat(string s)
{
    return stof(s);
}

double stringtodouble(string s)
{
    return stod(s);
}

QString stringtoqstring(string s)
{
    return QString::fromStdString(s);
}

bool stringtobool(string s)
{
    if(s=="T") return true;
    else return false;
}

QString inttoqstring(int i)
{
    return stringtoqstring(inttostring(i));
}

QString doubletoqstring(double d)
{
    return stringtoqstring(doubletostring(d));
}

QString floattoqstring(float f)
{
    return stringtoqstring(floattostring(f));
}

QString booltoqstring(bool b)
{
    return stringtoqstring(booltostring(b));
}

int qstringtoint(QString qs)
{
    return stringtoint(qstringtostring(qs));
}

float qstringtofloat(QString qs)
{
    return stringtofloat(qstringtostring(qs));
}

double qstringtodouble(QString qs)
{
    return stringtodouble(qstringtostring(qs));
}

bool qstringtobool(QString qs)
{
    return stringtobool((qstringtostring(qs)));
}
