#ifndef QCCPROGRESSTIMER_H
#define QCCPROGRESSTIMER_H

#include "qccsprite.h"

class QCCProgressTimer : public QCCSprite
{
public:
    QCCProgressTimer();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();

public:
    int m_progressTimerType;
    int m_direction;//0.从左到右 1.从右到左 2.从下到上 3.从上到下
    float m_percentage;
};



#endif // QCCPROGRESSTIMER_H
