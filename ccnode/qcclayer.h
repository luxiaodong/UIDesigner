#ifndef QCCLAYER_H
#define QCCLAYER_H

#include "qccnode.h"

class QCCLayer : public QCCNode
{
public:
    QCCLayer();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();

public:
    bool m_isTouchEnable;
};

#endif // QCCLAYER_H
