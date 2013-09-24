#ifndef QDATAPARSER_H
#define QDATAPARSER_H

#include "qccnode.h"

#define DATA_FORMAT_XML 1
#define DATA_FORMAT_LUA 2

class QDataParser
{
public:
    QDataParser();
    virtual QCCNode* parse(QString&);
};

class QXmlDataParser : public QDataParser
{
public:
    virtual QCCNode* parse(QString&);

private:
    void parseCCNode(QCCNode*, QXmlStreamAttributes&);
    void parseCCLayer(QCCLayer*, QXmlStreamAttributes&);
    void parseCCLayerColor(QCCLayerColor*, QXmlStreamAttributes&);
    void parseCCSprite(QCCSprite*, QXmlStreamAttributes&);
};

class QLuaDataParser : public QDataParser
{
public:
    virtual QCCNode* parse(QString&);
};



#endif // QDATAPARSER_H
