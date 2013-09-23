#ifndef QSTORAGEDATA_H
#define QSTORAGEDATA_H

#include "qdefine.h"

class QStorageData
{
public:
    QStorageData();
    //考虑碰到嵌套可以递归调用
    QString resourceDir();
    void setResourceDir(QString&);

    //void writeSingleNode();

public:
    QCCNode* m_root;
};

#endif // QSTORAGEDATA_H
