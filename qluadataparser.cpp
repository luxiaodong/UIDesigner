#include "qluadataparser.h"

QCCNode* QLuaDataParser::readUIFile(QString filePath)
{
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly) == false)
    {
        return 0;
    }

    m_fileName = filePath.split("/").last();
    m_fileName.remove(".lua");
    m_rootStr = QString("uidata");

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QStringList list;
    QString prefix = QString("%1.%2.").arg(m_rootStr, m_fileName);
    while(stream.atEnd() == false)
    {
        QString line = stream.readLine().trimmed();
        if((line.left(2) != QString("--")) && (line.contains(prefix) == true))
        {
            list.append(line.remove(prefix));
        }
    }

    file.close();
    return this->parse(list);
}

bool QLuaDataParser::writeUIFile(QString filePath, QCCNode* root)
{
    return false;
}

QCCNode* QLuaDataParser::parse(QStringList& list)
{
    QCCNode* root = 0;
    QCCNode* parent = 0;

    foreach(QString single, list)
    {
        QCCNode* node = 0;

        //解析单个行
        qDebug()<<single;
    }

    return 0;








//    while(reader.atEnd() == false)
//    {
//        QXmlStreamReader::TokenType token = reader.readNext();

//        if(token == QXmlStreamReader::StartElement)
//        {
//            QXmlStreamAttributes attr = reader.attributes();

//            //QCCNode* node = QCCNode::createCCNodeByType( reader.name() );

//            QCCNode* node = 0;
//            if(reader.name() == CLASS_TYPE_CCSPRITE)
//            {
//                node = QCCNode::createCCNodeByType(CLASS_TYPE_CCSPRITE);
//                this->parseCCSprite((QCCSprite*)node, attr);
//            }

//            //qDebug()<<reader.name();
//            Q_ASSERT(node != 0);

//            if(root == 0)
//            {
//                root = node;
//                parent = node;
//            }
//            else
//            {
//                parent->m_children.append(node);
//                node->m_parent = parent;
//                parent = node;
//            }
//        }
//        else if(token == QXmlStreamReader::EndElement)
//        {
//            parent = parent->m_parent;
//        }
//    }

//    if (reader.hasError() == true)
//    {
//        Q_ASSERT(0);
//        return 0;
//    }

//    return root;




}

QMap<QString,QString> QLuaDataParser::parseLine(QString& line)
{

}

QString QLuaDataParser::parse(QCCNode* root)
{}

//uidata = uidata or {};

//if uidata.login == nil then

// uidata.login = {};
// uidata.login.bg = {classType="CCSprite",x="149",y="101",z="1",width="298",height="204",filePath="set_dt_list_on.png"}
// uidata.login.bg.children = {};
// uidata.login.bg.children.node_2 = {classType="CCSprite",x="119",y="127",width="92",height="37",filePath="atten_tit.png"}

//end
