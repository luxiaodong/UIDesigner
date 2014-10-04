#ifndef QCCCONTAINERLAYER_H
#define QCCCONTAINERLAYER_H

#include "qcclayer.h"

class QCCContainerLayer : public QCCLayer
{
public:
    QCCContainerLayer();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();

public:
    QString m_containerConfigFilePath;
};

#endif // QCCCONTAINERLAYER_H
