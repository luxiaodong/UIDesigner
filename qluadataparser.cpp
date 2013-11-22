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

    for(int i = 0; i < list.size(); ++i)
    {
        QString single = list.at(i);
        QMap<QString,QString> map = this->parseLine(single);

        if(map.size() > 1) //only have name.
        {
            QString classType = map.value("classType");

            QCCNode* node = 0;
            if(classType == CLASS_TYPE_CCLAYER)
            {
                node = QCCNode::createCCNodeByType(CLASS_TYPE_CCLAYER);
                //this->parseCCLayer((QCCLayer*)node, attr);
            }
            else if(classType == CLASS_TYPE_CCLAYERCOLOR)
            {
                node = QCCNode::createCCNodeByType(CLASS_TYPE_CCLAYERCOLOR);
                //this->parseCCLayerColor((QCCLayerColor*)node, attr);
            }
            else if(classType == CLASS_TYPE_CCSPRITE)
            {
                node = QCCNode::createCCNodeByType(CLASS_TYPE_CCSPRITE);
                //this->parseCCSprite((QCCSprite*)node, attr);
            }
            else if(classType == CLASS_TYPE_CCLABELTTF)
            {
                node = QCCNode::createCCNodeByType(CLASS_TYPE_CCLABELTTF);
                //this->parseCCLabelTTF((QCCLabelTTF*)node, attr);
            }
            else if(classType == CLASS_TYPE_CCMENUITEM_IMAGE)
            {
                node = QCCNode::createCCNodeByType(CLASS_TYPE_CCMENUITEM_IMAGE);
                //this->parseCCMenuItemImage((QCCMenuItemImage*)node, attr);
            }
            else if(classType == CLASS_TYPE_CCCONTAINERLAYER)
            {
                node = QCCNode::createCCNodeByType(CLASS_TYPE_CCCONTAINERLAYER);
                //this->parseCCContainerLayer((QCCContainerLayer*)node, attr);
            }

            Q_ASSERT(node != 0);
            if(root == 0)
            {
                root = node;
                parent = node;
            }
            else
            {
                //find parent.
                QCCNode* parent = root;


                parent->m_children.append(node);
                node->m_parent = parent;
                parent = node;
            }
        }
    }

    return root;
}

QMap<QString,QString> QLuaDataParser::parseLine(QString& line)
{
    QMap<QString,QString> map;

    QRegExp r(QString("[{\" \"=,\"}]"));
    QStringList list = line.split(r,QString::SkipEmptyParts);
    Q_ASSERT(list.size()%2 == 1);
    map.insert(QString("name"), list.at(0));
    for(int i=1; i < list.size(); i+=2)
    {
        QString key = list.at(i);
        QString value = list.at(i+1);
        map.insert(key, value);
    }

    return map;
}

QCCNode* QLuaDataParser::findParentNode(QString name, QCCNode* root)
{
    QStringList list = name.split(".");
}


QString QLuaDataParser::parse(QCCNode* root)
{}

//uidata = uidata or {};

//if uidata.login == nil then

// uidata.login ={};
// uidata.login.bg ={classType="CCSprite",x="149",y="101",z="1",width="298",height="204",filePath="set_dt_list_on.png"}
// uidata.login.bg.children = {};
// uidata.login.bg.children.node_2 = {classType="CCSprite",x="119",y="127",width="92",height="37",filePath="atten_tit.png"}

//end
