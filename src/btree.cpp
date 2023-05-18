#include "btree.h"
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDataStream>


// B 树节点的构造函数
BTreeNode::BTreeNode(int t, bool leaf)
{
    this->t = t;
    this->leaf = leaf;
    this->n = 0;
    this->keys = new QString[2 * t - 1];
    this->children = new BTreeNode*[2 * t];
}

// B 树节点的析构函数
BTreeNode::~BTreeNode()
{
    delete[] keys;
    delete[] children;
}

// 在 B 树节点中进行遍历操作
void BTreeNode::traverse()
{
    int i;
    for (i = 0; i < n; i++)
    {
        // 如果当前节点不是叶子节点，则递归遍历子节点
        if (!leaf)
            children[i]->traverse();
        qDebug() << keys[i];
    }

    // 遍历最后一个子节点（如果有）
    if (!leaf)
        children[i]->traverse();
}

// 在 B 树节点中进行搜索操作
BTreeNode* BTreeNode::search(const QString& key)
{
    int i = 0;
    while (i < n && key > keys[i])
        i++;

    if (keys[i] == key)
        return this;

    if (leaf)
        return nullptr;

    return children[i]->search(key);
}

// 在非满节点中插入键值
void BTreeNode::insertNonFull(const QString& key)
{
    int i = n - 1;
    if (leaf)
    {
        while (i >= 0 && key < keys[i])
        {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
        n++;
    }
    else
    {
        while (i >= 0 && key < keys[i])
            i--;

        if (children[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, children[i + 1]);

            if (key > keys[i + 1])
                i++;
        }
        children[i + 1]->insertNonFull(key);
    }
}

// 分裂子节点
void BTreeNode::splitChild(int i, BTreeNode* y)
{
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf)
    {
        for (int j = 0; j < t; j++)
            z->children[j] = y->children[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        children[j + 1] = children[j];

    children[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];

    n++;
}

// 将节点写入文件
void BTreeNode::writeToFile(QDataStream& stream)
{
    stream << leaf;
    stream << n;
    for (int i = 0; i < n; i++)
        stream << keys[i];
    for (int i = 0; i <= n; i++)
        children[i]->writeToFile(stream);
}

// 从文件中读取节点
void BTreeNode::readFromFile(QDataStream& stream)
{
    stream >> leaf;
    stream >> n;
    keys = new QString[2 * t - 1];
    for (int i = 0; i < n; i++)
        stream >> keys[i];
    children = new BTreeNode*[2 * t];
    for (int i = 0; i <= n; i++)
    {
        children[i] = new BTreeNode(t, leaf);
        children[i]->readFromFile(stream);
    }
}

// B 树的构造函数
BTree::BTree(int t)
{
    this->t = t;
    root = nullptr;
}

// B 树的析构函数
BTree::~BTree()
{
    delete root;
}

// 在 B 树中插入键值
void BTree::insert(const QString& key)
{
    if (root == nullptr)
    {
        root = new BTreeNode(t, true);
        root->keys[0] = key;
        root->n = 1;
    }
    else
    {
        if (root->n == 2 * t - 1)
        {
            BTreeNode* s = new BTreeNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < key)
                i++;
            s->children[i]->insertNonFull(key);

            root = s;
        }
        else
        {
            root->insertNonFull(key);
        }
    }
}

// 在 B 树中进行搜索操作
int BTree::search(const QString& key)
{
    if (root == nullptr)
    {
        qDebug() << "BTree is empty.";

    }

    BTreeNode* result = root->search(key);

    if (result != nullptr)
    {
        filename = filename.left(filename.size()-4);
        filename += "value.txt";
        readValue(filename);
       return  keyValuePairs.value(key);

    }
    else
        qDebug() << "Key not found: " << key;
}





void BTreeNode::writeNode(QDataStream& stream)
{
    stream << leaf;
    stream << n;
    for (int i = 0; i < n; i++)
        stream << keys[i];

    if (!leaf)
    {
        for (int i = 0; i <= n; i++)
            children[i]->writeNode(stream);
    }
}

void BTreeNode::readNode(QDataStream& stream)
{
    stream >> leaf;
    stream >> n;

    keys = new QString[2 * t - 1];
    for (int i = 0; i < n; i++)
        stream >> keys[i];

    if (!leaf)
    {
        children = new BTreeNode*[2 * t];
        for (int i = 0; i <= n; i++)
        {
            children[i] = new BTreeNode(t, leaf);
            children[i]->readNode(stream);
        }
    }
}

void BTree::writeRecursive(BTreeNode* node, QDataStream& stream)
{
    node->writeNode(stream);

    if (!node->leaf)
    {
        for (int i = 0; i <= node->n; i++)
            writeRecursive(node->children[i], stream);
    }
}

BTreeNode* BTree::readRecursive(QDataStream& stream)
{
    BTreeNode* node = new BTreeNode(t, true);
    node->readNode(stream);

    if (!node->leaf)
    {
        node->children = new BTreeNode*[2 * t];
        for (int i = 0; i <= node->n; i++)
            node->children[i] = readRecursive(stream);
    }

    return node;
}

void BTree::writeToFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        qDebug() << "Failed to open file for writing.";
        return;
    }

    QDataStream stream(&file);

    stream << t; // Write the degree of the B-tree
    writeRecursive(root, stream);

    file.close();
}

void BTree::readFromFile(const QString& fileName)
{

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Failed to open file for reading.";
        return;
    }
    filename = fileName;
    QDataStream stream(&file);
    stream >> t; // Read the degree of the B-tree
    root = readRecursive(stream);

    file.close();
}

void BTree::writeValue(const QString& fileName,const QMap<QString, int>& keyValuePairs)
{
    QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "Failed to open file for writing.";
            return;
        }

        QDataStream stream(&file);
        stream << keyValuePairs;

        file.close();
}

void BTree:: readValue(const QString& fileName)
{
    QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            qDebug() << "Failed to open file for reading.";
        }

        QDataStream stream(&file);
        QMap<QString, int> keyValue;
        stream >> keyValue;
        keyValuePairs = keyValue;
        file.close();

}


