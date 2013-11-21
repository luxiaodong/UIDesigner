#ifndef QLUADATAPARSER_H
#define QLUADATAPARSER_H

#include "qdataparser.h"

class QLuaDataParser : public QDataParser
{
public:
    virtual QCCNode* readUIFile(QString filePath);
    virtual bool writeUIFile(QString filePath, QCCNode* root);

private:
    QCCNode* parse(QStringList&);
    QString parse(QCCNode*);

    QMap<QString,QString> parseLine(QString&);

private:
    QString m_fileName;
    QString m_rootStr;
};

#endif // QLUADATAPARSER_H
