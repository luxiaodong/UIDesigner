#include "qcclabelatlas.h"

QCCLabelAtlas::QCCLabelAtlas()
{
    m_text = "0123456789";
    m_elementWidth = 0;
    m_elementHeight = 0;
    m_startChar = '0';
}

void QCCLabelAtlas::importData(QMap<QString, QString>& map)
{
    QCCSprite::importData(map);
    m_elementWidth = map.value("elementWidth", QString("0")).toInt();
    m_elementHeight = map.value("elementHeight", QString("0")).toInt();
    m_startChar = map.value("startChar", QString("0x30")).toInt();
    m_text = map.value("text", QString(""));
}

QMap<QString, QString> QCCLabelAtlas::exportData()
{
    QMap<QString, QString> map = QCCSprite::exportData();
    map.insert("elementWidth", QString("%1").arg(m_elementWidth));
    map.insert("elementHeight", QString("%1").arg(m_elementHeight));
    map.insert("startChar", QString("%1").arg(m_startChar));
    map.insert("text", m_text);
    return map;
}

QGraphicsItem* QCCLabelAtlas::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCLabelAtlas::updateGraphicsItem()
{
    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
    QImage image = QImage(resourceFullPath(m_filePath));
    QSize s = image.size();

    int charCount = m_text.count();
    if(charCount > 0)
    {
        QImage imageOut = QImage(m_elementWidth*charCount, m_elementHeight, QImage::Format_ARGB32);
        imageOut.fill(0);
        QPainter painter(&imageOut);
        int m_elementCountPerWidth = s.width()/m_elementWidth;
        int m_elementCountPerHeight = s.height()/m_elementHeight;

        for(int i = 0; i < charCount; ++i)
        {
            char c = m_text.at(i).toLatin1();
            int index = c - m_startChar;
            if(index < 0 || index >= m_elementCountPerWidth*m_elementCountPerHeight)
            {
                index = 0;
            }

            int rowIndex = index/m_elementCountPerWidth;
            int colIndex = index%m_elementCountPerWidth;

            QRect r = QRect(colIndex*m_elementWidth, rowIndex*m_elementCountPerHeight, m_elementWidth, m_elementHeight);
            QImage imageCopy = image.copy(r);
            painter.drawImage( QRect(i*m_elementWidth,0,m_elementWidth,m_elementHeight), imageCopy );
        }

        item->setPixmap(QPixmap::fromImage(imageOut));
    }

    m_width = m_elementWidth*charCount;
    m_height = m_elementHeight;

    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);

    m_width = s.width();
    m_height = s.height();
}
