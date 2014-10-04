#ifndef QCCLAYERCOLOR_H
#define QCCLAYERCOLOR_H

#include "qcclayer.h"

class QCCLayerColor : public QCCLayer
{
public:
    QCCLayerColor();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();

public:
    QColor m_color;
    int m_opacity;
};


#endif // QCCLAYERCOLOR_H
