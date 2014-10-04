#include "qcclayer.h"
#include "qscene.h"
#include "qstoragedata.h"
#include <QImage>
#include <QPainter>

QCCLayer::QCCLayer()
{
    m_isTouchEnable = false;
    m_classType = CLASS_TYPE_CCLAYER;
}

void QCCLayer::importData(QMap<QString, QString>& map)
{
    QCCNode::importData(map);
    m_isTouchEnable = map.value("isTouchEnable", QString("0")).toInt();;
}

QMap<QString, QString> QCCLayer::exportData()
{
    QMap<QString, QString> map = QCCNode::exportData();
    if( m_isTouchEnable == true )
    {
        map.insert("isTouchEnable", "1");
    }

    return map;
}

QGraphicsItem* QCCLayer::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsRectItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCLayer::updateGraphicsItem()
{
    QGraphicsRectItem* item = dynamic_cast<QGraphicsRectItem*>(m_graphicsItem);
    item->setRect(0,0,m_width,m_height);
    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(0, -m_height), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
    item->setBrush( QBrush(Qt::NoBrush) );
}
