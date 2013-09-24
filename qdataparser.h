#ifndef QDATAPARSER_H
#define QDATAPARSER_H

#include "qccnode.h"

#define DATA_FORMAT_XML 1
#define DATA_FORMAT_LUA 2

class QDataParser
{
public:
    QDataParser();
    ~QDataParser();
    virtual QCCNode* parse(QString&);
    virtual QString parse(QCCNode*);
};

class QXmlDataParser : public QDataParser
{
public:
    virtual QCCNode* parse(QString&);
    virtual QString parse(QCCNode*);

private:
    void parseCCNode(QCCNode*, QXmlStreamAttributes&);
    void parseCCLayer(QCCLayer*, QXmlStreamAttributes&);
    void parseCCLayerColor(QCCLayerColor*, QXmlStreamAttributes&);
    void parseCCSprite(QCCSprite*, QXmlStreamAttributes&);

    void parseNode(QCCNode*, QXmlStreamWriter*);
    void parseCCNode(QCCNode*, QXmlStreamWriter*);
    void parseCCLayer(QCCLayer*, QXmlStreamWriter*);
    void parseCCLayerColor(QCCLayerColor*, QXmlStreamWriter*);
    void parseCCSprite(QCCSprite*, QXmlStreamWriter*);
};

class QLuaDataParser : public QDataParser
{
public:
    virtual QCCNode* parse(QString&);
};



#endif // QDATAPARSER_H