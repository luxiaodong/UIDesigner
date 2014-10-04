#include "qstoragedata.h"
#include "qluadataparser.h"
#include "qxmldataparser.h"

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
    QString suffix = filePath.right(3);
    if(suffix == "xml")
    {
        parser = new QXmlDataParser();
    }
    else if(suffix == "lua")
    {
        parser = new QLuaDataParser();
    }
    else
    {
        m_lastError = QString("unknow file format");
        return 0;
    }

    m_root = parser->readUIFile(filePath);
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
    QString suffix = filePath.right(3);
    if(suffix == "xml")
    {
        parser = new QXmlDataParser();
    }
    else if(suffix == "lua")
    {
        parser = new QLuaDataParser();
    }
    else
    {
        m_lastError = QString("unknow file format");
        return false;
    }

    if( parser->writeUIFile(filePath, m_root) == false )
    {
        m_lastError = QString("parse file failed.");
        delete parser;
        return false;
    }

    delete parser;
    return true;
}
