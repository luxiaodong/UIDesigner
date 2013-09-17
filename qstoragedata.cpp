#include "qstoragedata.h"

QStorageData::QStorageData()
{
}

QString QStorageData::resourceDir()
{
    QSettings settings("UIDesigner");
    return settings.value("resourceDir").toString();
}

void QStorageData::setResourceDir(QString& dir)
{
    QSettings settings("UIDesigner");
    settings.setValue("resourceDir", dir);
}
