#include "qstoragedata.h"

QStorageData::QStorageData()
{
    m_root = 0;
}

void QStorageData::test()
{

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
