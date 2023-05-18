#include"SQLanalysis.h"
#include<QDebug>


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
    //匹配删除表的正则：2
    regVector.push_back(QString("drop(?:\\s*)table(?:\\s*)(\\b[a-z0-9_]+\\b)(?:\\s*);"));
    //匹配添加字段的正则：3
    regVector.push_back(QString("alter\\s+table\\s+([^\\s]+)\\s+add\\s+column\\s+([^\\s]+)\\s+([^\\s]+)\\s*;"));
    //匹配修改字段的正则：4
    regVector.push_back(QString("alter\\s+table\\s+([^\\s]+)\\s+modify\\s+column\\s+([^\\s]+)\\s+([^\\s]+)\\s*;"));
    //匹配删除字段的正则：5
    regVector.push_back(QString("alter\\s+table\\s+([^\\s]+)\\s+drop\\s+column\\s+([^\\s]+)\\s+([^\\s]+)\\s*;"));
    //匹配创建索引的正则：6
    regVector.push_back(QString("create\\s+index\\s+(\\w+)\\s+on\\s+(\\w+)\\s*\\(([^\\)]+)\\)\\s*;"));


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





        //是否符合添加字段的语法

       QRegularExpression re3(regVector[3],QRegularExpression::CaseInsensitiveOption);

        QRegularExpressionMatch match3 = re3.match(sql);

        if (match3.hasMatch()) {
            QString tableName = match3.captured(1);
            QString column = match3.captured(2);

            QString field = match3.captured(3);

             //存储表名
            sqlkey.push_back(tableName);
            //存储列数量
            sqlkey.push_back(column);

            sqlkey.push_back(field);

          return 3;
        }

        //是否符合修改字段的语法

       QRegularExpression re4(regVector[4],QRegularExpression::CaseInsensitiveOption);

        QRegularExpressionMatch match4 = re4.match(sql);

        if (match4.hasMatch()) {
            QString tableName = match4.captured(1);
            QString column = match4.captured(2);

            QString field = match4.captured(3);

             //存储表名
            sqlkey.push_back(tableName);
            //存储列数量
            sqlkey.push_back(column);

            sqlkey.push_back(field);

          return 4;
        }

        //是否符合删除字段的语法

       QRegularExpression re5(regVector[5],QRegularExpression::CaseInsensitiveOption);

        QRegularExpressionMatch match5 = re5.match(sql);

        if (match5.hasMatch()) {
            QString tableName = match5.captured(1);
            QString column = match5.captured(2);

            QString field = match5.captured(3);

             //存储表名
            sqlkey.push_back(tableName);
            //存储列数量
            sqlkey.push_back(column);

            sqlkey.push_back(field);

          return 5;
        }

        //是否符合创建索引的语法
        QRegularExpression re6(regVector[6],QRegularExpression::CaseInsensitiveOption);

         QRegularExpressionMatch match6 = re6.match(sql);
         if (match6.hasMatch()) {
             // 获取索引名
             QString indexName = match6.captured(1);
             //获取表名
             QString tableName = match6.captured(2);
             // 获取列名
             QString columns = match6.captured(3);

             // 存取索引名称
             sqlkey.push_back(indexName);
             //存储表名
             sqlkey.push_back(tableName);
             //存储列数量
             sqlkey.push_back(columns);

           return 6;
         }



        for (unsigned int i = 0; i < regVector.size(); i++)
        {
            QRegExp reg(regVector[i],Qt::CaseInsensitive);
            //传入的sql语句和每个正则表达式进行匹配
            //匹配的第一个字符的位置，从0开始，若为-1则不匹配
            int pos = reg.indexIn(sql);
            //若匹配
            if (pos >= 0)
            {
                for (int j = 0; j < 1; j++)
                {
                    //将对应的值放入sqlkey
                    sqlkey.push_back(reg.cap(j + 1));
                }
                //返回数据库操作对应的编号，从0开始
                return 2;
            }
        }

    return -1;

}
