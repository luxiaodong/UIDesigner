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
    void parse(QCCNode*);

    QMap<QString,QString> parseLine(QString&);
    QString parseSingleNode(QMap<QString,QString>&);

private:
    QCCNode* findParentNode(QString nameList, QCCNode* root);

private:
    QStringList m_lines;
};

#endif // QLUADATAPARSER_H
