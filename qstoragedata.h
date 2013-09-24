#ifndef QSTORAGEDATA_H
#define QSTORAGEDATA_H

#include "qdataparser.h"

class QStorageData
{
public:
    QStorageData();
    void test();

public:
    QString resourceDir();
    void setResourceDir(QString&);

    QCCNode* parseUIFile(QString filePath);

private:
    QCCNode* m_root;

public:
    QString m_lastError;
};

#endif // QSTORAGEDATA_H
