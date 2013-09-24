#include "qdataparser.h"

QDataParser::QDataParser()
{
}

QCCNode* QDataParser::parse(QString& str)
{
    return 0;
}

QCCNode* QXmlDataParser::parse(QString& str)
{
    QXmlStreamReader reader(str);

    while(reader.atEnd() == false)
    {
        QXmlStreamReader::TokenType token = reader.readNext();

        if(token == QXmlStreamReader::StartDocument)
        {
        }
        else if(token == QXmlStreamReader::EndDocument)
        {}
        else if(token == QXmlStreamReader::StartElement)
        {
            QXmlStreamAttributes attr = reader.attributes();
            if (reader.name() == "sprite")
            {
                QCCSprite* node = new QCCSprite();
                this->parseCCSprite(node, attr);
            }
        }
        else if(token == QXmlStreamReader::EndElement)
        {}
        else if(token == QXmlStreamReader::Characters)
        {
            //qDebug()<<reader.text();
        }
        else if(token == QXmlStreamReader::Comment)
        {}
        else
        {}
    }

    if (reader.hasError() == true)
    {
        Q_ASSERT(0);
        return 0;
    }

    return 0;
}

void QXmlDataParser::parseCCNode(QCCNode* node, QXmlStreamAttributes& attr)
{
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

QCCNode* QLuaDataParser::parse(QString& str)
{
    return 0;
}
