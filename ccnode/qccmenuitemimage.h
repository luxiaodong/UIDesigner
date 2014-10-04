#ifndef QCCMENUITEMIMAGE_H
#define QCCMENUITEMIMAGE_H

#include "qccsprite.h"

class QCCMenuItemImage : public QCCSprite
{
public:
    QCCMenuItemImage();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();
};



#endif // QCCMENUITEMIMAGE_H
