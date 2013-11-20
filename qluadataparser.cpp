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
    foreach(QString single, list)
    {
        //解析单个行
        qDebug()<<single;
    }

    return 0;
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
