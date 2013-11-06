#include "qdataparser.h"

QDataParser::QDataParser()
{
}

QDataParser::~QDataParser()
{}

QCCNode* QDataParser::parse(QString& str)
{
    return 0;
}

QString QDataParser::parse(QCCNode*)
{
    return "";
}

QCCNode* QXmlDataParser::parse(QString& str)
{
    QXmlStreamReader reader(str);

    QCCNode* root = 0;
    QCCNode* parent = 0;
    while(reader.atEnd() == false)
    {
        QXmlStreamReader::TokenType token = reader.readNext();

        if(token == QXmlStreamReader::StartElement)
        {
            QXmlStreamAttributes attr = reader.attributes();

            //QCCNode* node = QCCNode::createCCNodeByType( reader.name() );

            QCCNode* node = 0;
            if(reader.name() == CLASS_TYPE_CCLAYER)
            {
                node = QCCNode::createCCNodeByType(CLASS_TYPE_CCLAYER);
                this->parseCCLayer((QCCLayer*)node, attr);
            }
            else if(reader.name() == CLASS_TYPE_CCSPRITE)
            {
                node = QCCNode::createCCNodeByType(CLASS_TYPE_CCSPRITE);
                this->parseCCSprite((QCCSprite*)node, attr);
            }
            else if(reader.name() == CLASS_TYPE_CCCONTAINERLAYER)
            {
                node = QCCNode::createCCNodeByType(CLASS_TYPE_CCCONTAINERLAYER);
                this->parseCCContainerLayer((QCCContainerLayer*)node, attr);
            }

            //qDebug()<<reader.name();
            Q_ASSERT(node != 0);

            if(root == 0)
            {
                root = node;
                parent = node;
            }
            else
            {
                parent->m_children.append(node);
                node->m_parent = parent;
                parent = node;
            }
        }
        else if(token == QXmlStreamReader::EndElement)
        {
            parent = parent->m_parent;
        }
    }

    if (reader.hasError() == true)
    {
        Q_ASSERT(0);
        return 0;
    }

    return root;
}

void QXmlDataParser::parseCCNode(QCCNode* node, QXmlStreamAttributes& attr)
{
    if(attr.hasAttribute("name") == true)
    {
        node->m_name = attr.value("name").toString();
    }

    if(attr.hasAttribute("x") == true)
    {
        node->m_x = attr.value("x").toInt();
    }

    if(attr.hasAttribute("y") == true)
    {
        node->m_y = attr.value("y").toInt();
    }

    if(attr.hasAttribute("z") == true)
    {
        node->m_z = attr.value("z").toInt();
    }

    if(attr.hasAttribute("width") == true)
    {
        node->m_width = attr.value("width").toInt();
    }

    if(attr.hasAttribute("height") == true)
    {
        node->m_height = attr.value("height").toInt();
    }
}

void QXmlDataParser::parseCCLayer(QCCLayer* node, QXmlStreamAttributes& attr)
{
    this->parseCCNode(node, attr);
}

void QXmlDataParser::parseCCLayerColor(QCCLayerColor* node, QXmlStreamAttributes& attr)
{
    if(attr.hasAttribute("opacity") == true)
    {
        node->m_opacity = attr.value("opacity").toInt();
    }

    this->parseCCLayer(node, attr);
}

void QXmlDataParser::parseCCSprite(QCCSprite* node, QXmlStreamAttributes& attr)
{
    if(attr.hasAttribute("filePath") == true)
    {
        node->m_filePath = attr.value("filePath").toString();
    }

    this->parseCCLayerColor(node, attr);
}

void QXmlDataParser::parseCCContainerLayer(QCCContainerLayer* node, QXmlStreamAttributes& attr)
{
    if(attr.hasAttribute("containerConfigFilePath") == true)
    {
        node->m_containerConfigFilePath = attr.value("containerConfigFilePath").toString();
    }

    this->parseCCLayer(node, attr);
}

QString QXmlDataParser::parse(QCCNode* node)
{
    QString str = QString();
    QXmlStreamWriter stream(&str);
    stream.writeStartDocument();
    this->parseNode(node, &stream);
    stream.writeEndDocument();
    return str;
}

void QXmlDataParser::parseNode(QCCNode* node, QXmlStreamWriter* stream)
{
    stream->writeStartElement(node->m_classType);

    if(node->m_classType == CLASS_TYPE_CCLAYER)
    {
        this->parseCCLayer( (QCCLayer*)node, stream);
    }
    else if(node->m_classType == CLASS_TYPE_CCSPRITE)
    {
        this->parseCCSprite( (QCCSprite*)node, stream);
    }
    else if(node->m_classType == CLASS_TYPE_CCCONTAINERLAYER)
    {
        this->parseCCContainerLayer( (QCCContainerLayer*)node, stream );
    }

    for(int i = 0; i < node->m_children.size(); ++i)
    {
        QCCNode* subNode = node->m_children.at(i);
        this->parseNode(subNode, stream);
    }

    stream->writeEndElement();
}

void QXmlDataParser::parseCCNode(QCCNode* node, QXmlStreamWriter* stream)
{
    stream->writeAttribute("name", node->m_name);

    if(node->m_x != 0)
    {
        stream->writeAttribute("x", QString("%1").arg(node->m_x));
    }

    if(node->m_y != 0)
    {
        stream->writeAttribute("y", QString("%1").arg(node->m_y));
    }

    if(node->m_z != 0)
    {
        stream->writeAttribute("z", QString("%1").arg(node->m_z));
    }

    if(node->m_width != 0)
    {
        stream->writeAttribute("width", QString("%1").arg(node->m_width));
    }

    if(node->m_height != 0)
    {
        stream->writeAttribute("height", QString("%1").arg(node->m_height));
    }
}

void QXmlDataParser::parseCCLayer(QCCLayer* node, QXmlStreamWriter* stream)
{
    this->parseCCNode(node, stream);
}

void QXmlDataParser::parseCCLayerColor(QCCLayerColor* node, QXmlStreamWriter* stream)
{
    this->parseCCLayer(node, stream);

    if(node->m_opacity != 255)
    {
        stream->writeAttribute("opacity", QString("%1").arg(node->m_opacity));
    }
}

void QXmlDataParser::parseCCSprite(QCCSprite* node, QXmlStreamWriter* stream)
{
    this->parseCCLayerColor(node, stream);

    stream->writeAttribute("filePath", QString("%1").arg(node->m_filePath));
}

void QXmlDataParser::parseCCContainerLayer(QCCContainerLayer* node, QXmlStreamWriter* stream)
{
    this->parseCCLayer(node, stream);
    stream->writeAttribute("containerConfigFilePath", QString("%1").arg(node->m_containerConfigFilePath));
}

QCCNode* QLuaDataParser::parse(QString& str)
{
    return 0;
}
