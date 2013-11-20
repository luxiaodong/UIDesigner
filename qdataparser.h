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
    void parseCCLabelTTF(QCCLabelTTF*, QXmlStreamAttributes&);
    void parseCCMenuItemImage(QCCMenuItemImage*, QXmlStreamAttributes&);
    void parseCCContainerLayer(QCCContainerLayer*, QXmlStreamAttributes&attr);

    void parseNode(QCCNode*, QXmlStreamWriter*);
    void parseCCNode(QCCNode*, QXmlStreamWriter*);
    void parseCCLayer(QCCLayer*, QXmlStreamWriter*);
    void parseCCLayerColor(QCCLayerColor*, QXmlStreamWriter*);
    void parseCCSprite(QCCSprite*, QXmlStreamWriter*);
    void parseCCLabelTTF(QCCLabelTTF*, QXmlStreamWriter*);
    void parseCCMenuItemImage(QCCMenuItemImage*, QXmlStreamWriter*);
    void parseCCContainerLayer(QCCContainerLayer*, QXmlStreamWriter*);
};

class QLuaDataParser : public QDataParser
{
public:
    virtual QCCNode* parse(QString&);
    virtual QString parse(QCCNode*);
};



#endif // QDATAPARSER_H
