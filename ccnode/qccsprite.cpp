#include "qccsprite.h"

QCCSprite::QCCSprite()
{
    m_filePath = "";
    m_classType = CLASS_TYPE_CCSPRITE;
    m_anchorX = 0.5f;
    m_anchorY = 0.5f;
}

void QCCSprite::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    QString shortPath = map.value("filePath", QString(""));
    if (shortPath.contains("/"))
    {
        m_filePath = shortPath;
    }
    else
    {
        m_filePath = this->shortPathToLongPath(shortPath);
    }
}

QMap<QString, QString> QCCSprite::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();
    QString shortPath = this->longPathToShortPath(m_filePath);
    map.insert("filePath", shortPath);
    return map;
}

QGraphicsItem* QCCSprite::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCSprite::updateGraphicsItem()
{
    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
    QPixmap pixmap;
    pixmap = QPixmap(resourceFullPath(m_filePath));
    item->setPixmap(pixmap);
    QSize s = pixmap.size();
    m_width = s.width();
    m_height = s.height();
    item->setTransformOriginPoint(-m_width/2.0f, -m_height/2.0f);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(m_width*(0 - m_anchorX), m_height*(m_anchorY - 1.0)), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}
