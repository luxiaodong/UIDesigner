#include "qexportcode.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "qstoragedata.h"

QExportCode::QExportCode()
{

}

void QExportCode::parseFile(QString filePath)
{
    QString className = filePath.split("/").last();
    m_uiFileName = className.remove(".lua");
    m_className = QString("G%1%2Layer").arg( className.left(1).toUpper() ).arg(className.right(className.size() - 1) );

    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly) == false)
    {
        return ;
    }

    m_menuList.clear();
    QTextStream stream(&file);
    while( stream.atEnd() == false )
    {
        QString line = stream.readLine().trimmed();
        if( line.contains(QString("uidata.")) && line.contains(QString("CCMenuItem")) )
        {
            m_menuList.append( line.split(QString(" ")).first() );
        }
    }

    file.close();

    QString dir = this->resourceDir();
    QString outFile = QString("%1/src/ui/layer/%2.lua").arg( dir.left( dir.length() - 4 ), m_className );
    file.setFileName(outFile);
    if(file.open(QIODevice::WriteOnly) == false)
    {
        return ;
    }

    QTextStream outStream(&file);
    outStream<<createLayerString();
    file.close();
}

QString QExportCode::createLayerString()
{
    QString str;
    str += QString("local GAbstractLayer = require(\"ui.GAbstractLayer\");\n");
    str += QString("local %1 = class(\"%1\", GAbstractLayer)\n").arg(m_className);
    str += QString("\n");

    str += QString("function %1:ctor()\n").arg(m_className);
    str += QString("    GAbstractLayer.ctor(self)\n");
    str += QString("    self:loadUiFile(\"ui.%1\")\n").arg(m_uiFileName);
    str += QString("end\n");
    str += QString("\n");

    str += QString("function %1:init()\n").arg(m_className);
    str += this->registerScriptTapHandler();
    //str += QString("--listen btn click event\n");
    str += QString("end\n");
    str += QString("\n");

    str += QString("function %1:onEnter()\n").arg(m_className);
    str += QString("end\n");
    str += QString("\n");

    str += QString("function %1:onExit()\n").arg(m_className);
    str += QString("end\n");
    str += QString("\n");

//    str += QString("function %1:update()\n").arg(m_className);
//    str += QString("end\n");
//    str += QString("\n");

    str += this->handlerScriptTapHandler();

    str += QString("return %1\n").arg(m_className);
    return str;
}

QString QExportCode::registerScriptTapHandler()
{
    QString str;
    foreach (QString single, m_menuList)
    {
        QString name = single.replace(QString("uidata."), QString("self.ui."));
        QString funcName = single.split(".").last();
        str += QString("    %1:registerScriptTapHandler( handler(self, self.click_%2) )\n").arg(name).arg(funcName);
    }
    return str;
}

QString QExportCode::handlerScriptTapHandler()
{
    QString str;
    foreach (QString single, m_menuList)
    {
        QString funcName = single.split(".").last();
        str += QString("function %1:click_%2()\n").arg(m_className, funcName);
        str += QString("end\n");
        str += QString("\n");
    }
    return str;
}

QString QExportCode::resourceDir()
{
    QStorageData data;
    return data.resourceDir();
}
