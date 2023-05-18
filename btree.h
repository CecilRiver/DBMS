#ifndef BTREE_H
#define BTREE_H
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDataStream>
using namespace std;


// B 树节点的定义
class BTreeNode
{
public:
    BTreeNode(int t, bool leaf);
    ~BTreeNode();

    void traverse();

    BTreeNode* search(const QString& key);

    void insertNonFull(const QString& key);

    void splitChild(int i, BTreeNode* y);

    void writeToFile(QDataStream& stream);

    void readFromFile(QDataStream& stream);
    void writeNode(QDataStream& stream);
    void readNode(QDataStream& stream);

private:
    bool leaf;
    int t;
    int n;
    QString* keys;
    BTreeNode** children;

    friend class BTree;
};

// B 树的定义
class BTree
{
public:
    BTree(int t);
    ~BTree();

    void insert(const QString& key);

    int search(const QString& key);

    void writeToFile(const QString& fileName);

    void readFromFile(const QString& fileName);
    void writeRecursive(BTreeNode* node, QDataStream& stream);
    void writeValue(const QString& fileName,const QMap<QString, int>& keyValuePairs);
    void readValue(const QString& fileName);
    BTreeNode* readRecursive(QDataStream& stream);
private:
    QMap<QString, int> keyValuePairs;
    QString filename;
    BTreeNode* root;
    int t;
};

#endif // BTREE_H
