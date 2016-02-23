#ifndef QEXPORTCODE_H
#define QEXPORTCODE_H

#include <QString>
#include <QStringList>

class QExportCode
{
public:
    QExportCode();

public:
    void parseFile(QString filePath);
    QString createLayerString();
    QString registerScriptTapHandler();
    QString handlerScriptTapHandler();
    QString resourceDir();

private:
    QString m_uiFileName;
    QString m_className;

    QStringList m_menuList;
};

#endif // QEXPORTCODE_H
