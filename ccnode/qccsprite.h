#ifndef QCCSPRITE_H
#define QCCSPRITE_H

#include "qcclayercolor.h"

//三张图片,命名必须是 xxxx_n.png  xxxx_h.png  xxxx_d.png
class QCCSprite : public QCCLayerColor
{
public:
    QCCSprite();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();

public:
    QString m_filePath;
};

#endif // QCCSPRITE_H
