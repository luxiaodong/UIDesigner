#include "qccprogresstimer.h"

QCCProgressTimer::QCCProgressTimer()
{
    m_progressTimerType = kCCProgressTimerTypeBar;
    m_direction = 0;//0.从左到右 1.从右到左 2.从下到上 3.从上到下
    m_percentage = 1.0;
}

void QCCProgressTimer::importData(QMap<QString, QString>& map)
{
    QCCSprite::importData(map);
    m_progressTimerType = map.value("progressTimerType","1").toInt();
    m_direction = map.value("direction","0").toInt();
    m_percentage = map.value("percentage","0.5").toFloat();
}

QMap<QString, QString> QCCProgressTimer::exportData()
{
    QMap<QString, QString> map = QCCSprite::exportData();
    map.insert("progressTimerType", QString("%1").arg(m_progressTimerType));
    map.insert("direction", QString("%1").arg(m_direction));
    map.insert("percentage", QString("%1").arg(m_percentage));
    return map;
}

QGraphicsItem* QCCProgressTimer::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCProgressTimer::updateGraphicsItem()
{
    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
    QImage image = QImage(resourceFullPath(m_filePath));
    QSize s = image.size();

    if (m_progressTimerType == kCCProgressTimerTypeRadial)
    {
        if(m_direction == 0)//顺时针
        {
            //float angle = m_percentage*360;
        }
        else if(m_direction == 1) //逆时针
        {}
    }
    else if(m_progressTimerType == kCCProgressTimerTypeBar)
    {
        QRect r;
        if(m_direction == 0)
        {
            r = QRect(0, 0, s.width()*m_percentage, s.height());
        }
        else if(m_direction == 1)
        {
            r = QRect(s.width()*(1 - m_percentage), 0, s.width()*m_percentage, s.height());
        }
        else if(m_direction == 2)
        {
            r = QRect(0, s.height()*(1 - m_percentage), s.width(), s.height()*m_percentage);
        }
        else if(m_direction == 3)
        {
            r = QRect(0, 0, s.width(), s.height()*m_percentage);
        }

        QImage image_1 = image.copy( r );
        QImage imageOut = QImage(s.width(), s.height(), QImage::Format_ARGB32);
        imageOut.fill(0);
        QPainter painter(&imageOut);
        painter.drawImage( r, image_1 );
        item->setPixmap(QPixmap::fromImage(imageOut));
    }

    m_width = s.width();
    m_height = s.height();

    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}
