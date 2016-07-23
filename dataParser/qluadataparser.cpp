#include "qluadataparser.h"
#include <QDebug>

QCCNode* QLuaDataParser::readUIFile(QString filePath)
{
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly) == false)
    {
        return 0;
    }

    QString fileName = filePath.split("/").last();
    fileName.remove(".lua");
    QString rootStr = QString("uidata");

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QStringList list;
    QString prefix = QString("%1.").arg(rootStr);

    while(stream.atEnd() == false)
    {
        QString line = stream.readLine().trimmed();
        if( line.left(2) != QString("--") &&  line.contains(prefix) )
        {
            list.append(line.remove(prefix));
        }
    }

    file.close();
    return this->parse(list);
}

bool QLuaDataParser::writeUIFile(QString filePath, QCCNode* root)
{
    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly) == false)
    {
        return false;
    }

    QString fileName = filePath.split("/").last();
    fileName.remove(".lua");
    QString rootStr = QString("uidata");

    QString str("\n");
    str += QString("local %1 = {}\n").arg(rootStr);
    m_lines.clear();
    this->parse(root);

    foreach(QString single, m_lines)
    {
        str += QString("%1.%2\n").arg(rootStr, single);
    }

    str += QString("\n");
    str += QString("return %1;\n").arg(rootStr);

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream<<str;
    file.close();
    return true;
}

QCCNode* QLuaDataParser::parse(QStringList& list)
{
    QCCNode* root = 0;

    for(int i = 0; i < list.size(); ++i)
    {
        QString single = list.at(i);
        QMap<QString,QString> map = this->parseLine(single);
        QString nameList = map.value("name");

        if(map.size() > 1) //only have name.
        {
            QString classType = map.value("classType");
            QCCNode* node = QCCNode::createCCNodeByType(classType);
            QString lastName = nameList.split(".").last();
            map.insert("name", lastName);
            node->importData(map);
            Q_ASSERT(node != 0);
            if(root == 0)
            {
                root = node;
            }
            else
            {
                //find parent.
                QCCNode* parent = this->findParentNode(nameList, root);
                Q_ASSERT(parent != 0);
                parent->m_children.append(node);
                node->m_parent = parent;
            }
        }
    }

    return root;
}

QMap<QString,QString> QLuaDataParser::parseLine(QString& line)
{
    QMap<QString,QString> map;
    QRegExp r(QString("[{\" \"=,;\"}]"));
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

QCCNode* QLuaDataParser::findParentNode(QString namelist, QCCNode* root)
{
    QStringList list = namelist.remove("children").split(".");
    QCCNode* parent = root;
    for(int i = 1; i < list.size() - 1; ++i)
    {
        for(int j = 0; j < parent->m_children.size(); ++j)
        {
            QCCNode* son = parent->m_children.at(j);
            if(son->m_name == list.at(i))
            {
                parent = son;
            }
        }
    }

    return parent;
}

void QLuaDataParser::parse(QCCNode* node)
{
    QMap<QString,QString> map = node->exportData();
    map.insert("name", node->luaVariableName());
    m_lines.append( this->parseSingleNode(map) );

    if(node->m_children.size() > 0)
    {
        //add a children
        m_lines.append(QString("%1.children = {};").arg(node->luaVariableName()));

        foreach(QCCNode* son, node->m_children)
        {
            this->parse(son);
        }
    }
}

QString QLuaDataParser::parseSingleNode(QMap<QString,QString>& map)
{
    QString name = map.value("name");
    QString classType = map.value("classType");
    QString x = map.value("x");
    QString y = map.value("y");
    QString z = map.value("z");
    QString width = map.value("width");
    QString height = map.value("height");

    map.remove("name");
    map.remove("classType");
    map.remove("x");
    map.remove("y");
    map.remove("z");
    map.remove("width");
    map.remove("height");

    QString str = QString("%1 = {").arg(name);
    str += QString("classType=\"%1\"").arg(classType);
    str += QString(",x=\"%1\"").arg(x);
    str += QString(",y=\"%1\"").arg(y);
    str += QString(",z=\"%1\"").arg(z);
    str += QString(",width=\"%1\"").arg(width);
    str += QString(",height=\"%1\"").arg(height);

    QMap<QString, QString>::const_iterator i = map.constBegin();
    while (i != map.constEnd())
    {
        if(i.value().isEmpty() == false)
        {
            str += QString(",%1=\"%2\"").arg(i.key(), i.value());
        }

        ++i;
    }

    str += QString("};");
    return str;
}

//uidata = uidata or {};

//if uidata.login == nil then

// uidata.login ={};
// uidata.login.bg = {classType="CCSprite",x="149",y="101",z="1",width="298",height="204",filePath="set_dt_list_on.png"}
// uidata.login.bg.children = {};
// uidata.login.bg.children.node_2 = {classType="CCSprite",x="119",y="127",width="92",height="37",filePath="atten_tit.png"}

//end
