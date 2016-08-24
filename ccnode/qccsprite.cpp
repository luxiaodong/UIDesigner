#include "qccsprite.h"

QCCSprite::QCCSprite()
{
    m_filePath = "";
    m_classType = CLASS_TYPE_CCSPRITE;
}

void QCCSprite::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    m_filePath = map.value("filePath", QString(""));
}

QMap<QString, QString> QCCSprite::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();
    map.insert("filePath", m_filePath);
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
/*
        QSize s = pixmap.size();
        QImage image = QImage(s.width(), s.height(), QImage::Format_RGB32);

        for(int j = 0; j < s.height(); ++j)
        {
            for(int i = 0;i < s.width(); ++i)
            {
                if(i == 0 || i == s.width() -1 || j == 0 || j == s.height() - 1)
                {
                    image.setPixel(i,j,0xFFFFFF);
                }
                else if(i == 1 || i == s.width() -2 || j == 1 || j == s.height() - 2)
                {
                    image.setPixel(i,j,0xFFFFFF);
                }
                else if(i == 2 || i == s.width() -3 || j == 2 || j == s.height() - 3)
                {
                    image.setPixel(i,j,0xFF0000);
                }
                else if(i == 3 || i == s.width() -4 || j == 3 || j == s.height() - 4)
                {
                    image.setPixel(i,j,0xFF0000);
                }
                else
                {
                    image.setPixel(i,j,0x0);
                }
            }
        }

        pixmap = QPixmap::fromImage(image);

    pixmap.fill(QColor(qrand()%255, qrand()%255, qrand()%255));
*/
    item->setPixmap(pixmap);
    QSize s = pixmap.size();
    m_width = s.width();
    m_height = s.height();
    item->setTransformOriginPoint(-m_width/2.0f, -m_height/2.0f);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2.0f, -m_height/2.0f), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}
