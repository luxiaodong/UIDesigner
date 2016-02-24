#include "qccscale9sprite.h"


QCCScale9Sprite::QCCScale9Sprite()
{
    m_insetsRect = QRect(0,0,0,0);
    m_preferredSize = QSize(0,0);
}

void QCCScale9Sprite::importData(QMap<QString, QString>& map)
{
    QCCSprite::importData(map);
    int insets_x = map.value("insets_x","0").toInt();
    int insets_y = map.value("insets_y","0").toInt();
    int insets_w = map.value("insets_w","0").toInt();
    int insets_h = map.value("insets_h","0").toInt();
    m_insetsRect = QRect(insets_x, insets_y, insets_w, insets_h);

    int perferred_w = map.value("perferred_w","0").toInt();
    int perferred_h = map.value("perferred_h","0").toInt();
    m_preferredSize = QSize(perferred_w, perferred_h);
}

QMap<QString, QString> QCCScale9Sprite::exportData()
{
    QMap<QString, QString> map = QCCSprite::exportData();
    map.insert("insets_x", QString("%1").arg(m_insetsRect.x()));
    map.insert("insets_y", QString("%1").arg(m_insetsRect.y()));
    map.insert("insets_w", QString("%1").arg(m_insetsRect.width()));
    map.insert("insets_h", QString("%1").arg(m_insetsRect.height()));
    map.insert("perferred_w", QString("%1").arg(m_preferredSize.width()));
    map.insert("perferred_h", QString("%1").arg(m_preferredSize.height()));
    return map;
}

QGraphicsItem* QCCScale9Sprite::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCScale9Sprite::updateGraphicsItem()
{
    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
    QImage image = QImage(resourceFullPath(m_filePath));
    QSize s = image.size();

    int w1 = m_insetsRect.x();
    int h1 = m_insetsRect.y();
    int w2 = m_insetsRect.width();
    int h2 = m_insetsRect.height();
    int w3 = s.width() - w1 - w2;
    int h3 = s.height() - h1 - h2;

    QImage image_1 = image.copy(0,          0,      w1,     h1);
    QImage image_2 = image.copy(w1,         0,      w2,     h1);
    QImage image_3 = image.copy(w1 + w2,    0,      w3,     h1);
    QImage image_4 = image.copy(0,          h1,     w1,     h2);
    QImage image_5 = image.copy(w1,         h1,     w2,     h2);
    QImage image_6 = image.copy(w1 + w2,    h1,     w3,     h2);
    QImage image_7 = image.copy(0,      h1 + h2,    w1,     h3);
    QImage image_8 = image.copy(w1,     h1 + h2,    w2,     h3);
    QImage image_9 = image.copy(w1 + w2,h1 + h2,    w3,     h3);

    QImage imageOut = QImage(m_preferredSize.width(), m_preferredSize.height(), QImage::Format_ARGB32);
    imageOut.fill(0);
    QPainter painter(&imageOut);

    w2 = m_preferredSize.width() - w1 - w3;
    h2 = m_preferredSize.height() - h1 - h3;

    painter.drawImage( QRect(0,          0,      w1,     h1), image_1 );
    painter.drawImage( QRect(w1,         0,      w2,     h1), image_2 );
    painter.drawImage( QRect(w1 + w2,    0,      w3,     h1), image_3 );
    painter.drawImage( QRect(0,          h1,     w1,     h2), image_4 );
    painter.drawImage( QRect(w1,         h1,     w2,     h2), image_5 );
    painter.drawImage( QRect(w1 + w2,    h1,     w3,     h2), image_6 );
    painter.drawImage( QRect(0,      h1 + h2,    w1,     h3), image_7 );
    painter.drawImage( QRect(w1,     h1 + h2,    w2,     h3), image_8 );
    painter.drawImage( QRect(w1 + w2,h1 + h2,    w3,     h3), image_9 );

    item->setPixmap(QPixmap::fromImage(imageOut));
    m_width = m_preferredSize.width();
    m_height = m_preferredSize.height();

    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}
