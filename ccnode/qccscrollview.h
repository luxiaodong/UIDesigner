#ifndef QCCSCROLLVIEW_H
#define QCCSCROLLVIEW_H

#include "qcclayer.h"

class QCCScrollView : public QCCLayer
{
public:
    QCCScrollView();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();

public:
    QString m_containerConfigFilePath;
    int m_direction;//0.左右 1.上下. 2.Both
    int m_count;//
    int m_offsetX;
    int m_offsetY;
    int m_spaceWidth;
    int m_spaceHeight;
    int m_contentWidth;
    int m_contentHeight;
    bool m_isDynamicallyGenerated;
};

#endif // QCCSCROLLVIEW_H
