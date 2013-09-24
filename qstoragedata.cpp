#include "qstoragedata.h"

QStorageData::QStorageData()
{
    m_root = 0;
    m_lastError = "";
}

void QStorageData::test()
{
    QStringList list;
}

QString QStorageData::resourceDir()
{
    QSettings settings("UIDesigner");
    return settings.value("resourceDir",QString("")).toString();
}

void QStorageData::setResourceDir(QString& dir)
{
    QSettings settings("UIDesigner");
    settings.setValue("resourceDir", dir);
}

QCCNode* QStorageData::readUIFile(QString filePath)
{
    if(filePath.isEmpty() == true)
    {
        m_lastError = QString("an empty filePath");
        return 0;
    }

    QDataParser* parser = 0;
    int dataFormat = 0;
    QString suffix = filePath.right(3);
    if(suffix == "xml")
    {
        parser = new QXmlDataParser();
        dataFormat = DATA_FORMAT_XML;
    }
    else if(suffix == "lua")
    {
        parser = new QLuaDataParser();
        dataFormat = DATA_FORMAT_LUA;
    }
    else
    {
        m_lastError = QString("unknow file format");
        return 0;
    }

    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly) == false)
    {
        m_lastError = QString("open file failed");
        return 0;
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    QString str = stream.readAll();
    file.close();

    m_root = parser->parse(str);
    delete parser;

    if(m_root == 0)
    {
        m_lastError = QString("parse file failed.");
    }

    return m_root;
}

bool QStorageData::writeUIFile(QString filePath)
{
    if(filePath.isEmpty() == true)
    {
        m_lastError = QString("an empty filePath");
        return false;
    }

    QDataParser* parser = 0;
    int dataFormat = 0;
    QString suffix = filePath.right(3);
    if(suffix == "xml")
    {
        parser = new QXmlDataParser();
        dataFormat = DATA_FORMAT_XML;
    }
    else if(suffix == "lua")
    {
        parser = new QLuaDataParser();
        dataFormat = DATA_FORMAT_LUA;
    }
    else
    {
        m_lastError = QString("unknow file format");
        return false;
    }

    QString str = parser->parse(m_root);
    delete parser;

    if(str == "")
    {
        m_lastError = QString("parse file failed.");
        return false;
    }

    QFile file(filePath);
    if(file.open(QIODevice::WriteOnly) == false)
    {
        m_lastError = QString("open file failed");
        return 0;
    }

    str.replace(">",">\n");

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    stream<<str;
    file.close();

    return true;
}
