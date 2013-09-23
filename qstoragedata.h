#ifndef QSTORAGEDATA_H
#define QSTORAGEDATA_H

#include "qccnode.h"

class QStorageData
{
public:
    QStorageData();
    void test();
public:
    //考虑碰到嵌套可以递归调用
    QString resourceDir();
    void setResourceDir(QString&);

    //void writeSingleNode();

public:
    QCCNode* m_root;
};

#endif // QSTORAGEDATA_H
