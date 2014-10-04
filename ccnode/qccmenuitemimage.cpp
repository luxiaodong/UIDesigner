#include "qccmenuitemimage.h"

QCCMenuItemImage::QCCMenuItemImage()
{
}

void QCCMenuItemImage::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    m_filePath = map.value("image_n", QString(""));
}

QMap<QString, QString> QCCMenuItemImage::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();
    map.insert("image_n", m_filePath);
    return map;
}

QGraphicsItem* QCCMenuItemImage::createGraphicsItem()
{
    return QCCSprite::createGraphicsItem();
}

void QCCMenuItemImage::updateGraphicsItem()
{
    return QCCSprite::updateGraphicsItem();
}
