#include"SQLanalysis.h"


int sqlAnalysis(QString sql,vector<QString> &sqlkey)
{
    //存放正则表达式
    vector<QString> regVector;
    //对应的正则表达式的捕获数量
    vector<int> regSize;

    //匹配创建数据库的正则:0
    regVector.push_back(QString("create(?:\\s*)database(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*);"));
    regSize.push_back(1);
    //匹配重命名数据库的正则:1
    regVector.push_back(QString("rename(?:\\s*)database(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*)to(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*);"));
    regSize.push_back(2);
     //匹配删除数据库的正则:2
    regVector.push_back(QString("drop(?:\\s*)database(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*);"));
    regSize.push_back(1);
     //匹配使用数据库的正则:3
    regVector.push_back(QString("use(?:\\s*)database(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*);"));
    regSize.push_back(1);
    //匹配展示数据库的正则:4
    regVector.push_back(QString("show(?:\\s*)databases(?:\\s*);"));
    regSize.push_back(0);
    //匹配初始化数据库的正则:5
    regVector.push_back(QString("initialize(?:\\s*)database(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*);"));
    regSize.push_back(1);


    //开始解析sql语句
    for (unsigned int i = 0; i < regVector.size(); i++)
    {
        QRegExp reg(regVector[i],Qt::CaseInsensitive);
        //传入的sql语句和每个正则表达式进行匹配
        //匹配的第一个字符的位置，从0开始，若为-1则不匹配
        int pos = reg.indexIn(sql);
        //若匹配
        if (pos >= 0)
        {
            for (int j = 0; j < regSize[i]; j++)
            {
                //将对应的值放入sqlkey
                sqlkey.push_back(reg.cap(j + 1));
            }
            //返回数据库操作对应的编号，从0开始
            return i;
        }
    }
    //没有对应的操作，返回-1，表示该类型操作暂未支持，或者sql语句错误
    return -1;
}


int sqlAnalysisTable(QString sql,vector<QString> &sqlkey,QString DBname)
{
    //存放正则表达式
    vector<QString> regVector;
    //匹配创建表的正则：0
    regVector.push_back(QString("create\\s+table\\s+(\\w+)\\s*\\((.*)\\)\\s*;"));
    //匹配向表中插入数据的正则：1
    regVector.push_back(QString("insert\\s+into\\s+([^\\s]+)\\s*\\(([^\\)]+)\\)\\s*values\\s*\\(([^\\)]+)\\)\\s*;"));

    //开始解析sql语句

        //是否符合创建表的语法
        QRegularExpression re(regVector[0],QRegularExpression::CaseInsensitiveOption);
        QRegularExpressionMatch match = re.match(sql);
        if(match.hasMatch())
        {
            QString tableName = match.captured(1);
            QString columns = match.captured(2);

            sqlkey.push_back(tableName);

            QRegularExpression columnRe("\\s*(\\w+)\\s+(\\w+)\\s*");
            QRegularExpressionMatchIterator i = columnRe.globalMatch(columns);
            while (i.hasNext()) {
                QRegularExpressionMatch columnMatch = i.next();
                QString columnName = columnMatch.captured(1);
                QString columnType = columnMatch.captured(2);
                sqlkey.push_back(columnName);
                sqlkey.push_back(columnType);

            }
            return 0;
        }

        //是否符合插入表的语法

       QRegularExpression re1(regVector[1],QRegularExpression::CaseInsensitiveOption);

        QRegularExpressionMatch match1 = re1.match(sql);

        if (match1.hasMatch()) {
            QString tableName = match1.captured(1);
               QStringList columns = match1.captured(2).split(",");
               QStringList values = match1.captured(3).split(",");
             //存储表名
            sqlkey.push_back(tableName);
            //存储列数量
            sqlkey.push_back(QString::number(columns.size()));
            //存储列名
            for(int i=0;i<columns.size();i++)
               sqlkey.push_back(columns.at(i).simplified());
            //存储数值
            for(int i=0;i<values.size();i++)
               sqlkey.push_back(values.at(i).simplified());

          return 1;
        }


    return -1;

}
