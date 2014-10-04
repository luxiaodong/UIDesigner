#ifndef QCCSCALE9SPRITE_H
#define QCCSCALE9SPRITE_H

#include "qccsprite.h"

class QCCScale9Sprite : public QCCSprite
{
public:
    QCCScale9Sprite();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();

public:
    QRect m_insetsRect;
    QSize m_preferredSize;
};

#endif // QCCSCALE9SPRITE_H
