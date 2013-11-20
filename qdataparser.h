#ifndef QDATAPARSER_H
#define QDATAPARSER_H

#include "qccnode.h"

class QDataParser
{
public:
    virtual QCCNode* readUIFile(QString filePath);
    virtual bool writeUIFile(QString filePath, QCCNode* root);
};

class QXmlDataParser : public QDataParser
{
public:
    virtual QCCNode* readUIFile(QString filePath);
    virtual bool writeUIFile(QString filePath, QCCNode* root);

private:
    QCCNode* parse(QString&);
    QString parse(QCCNode*);

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



#endif // QDATAPARSER_H
