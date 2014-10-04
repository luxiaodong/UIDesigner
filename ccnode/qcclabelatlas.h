#ifndef QCCLABELATLAS_H
#define QCCLABELATLAS_H

#include "qccsprite.h"

class QCCLabelAtlas : public QCCSprite
{
public:
    QCCLabelAtlas();
public:
    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();
public:
    QString m_text;
    int m_elementWidth;
    int m_elementHeight;
    int m_startChar;
};

#endif // QCCLABELATLAS_H
