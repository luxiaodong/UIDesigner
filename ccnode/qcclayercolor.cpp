#include "qcclayercolor.h"

QCCLayerColor::QCCLayerColor()
{
    m_color = QColor(Qt::white);
    m_opacity = 0xff;
    m_classType = CLASS_TYPE_CCLAYERCOLOR;
}

void QCCLayerColor::importData(QMap<QString, QString>& map)
{
    QCCLayer::importData(map);
    int r = map.value("color_r", QString("255")).toInt();
    int g = map.value("color_g", QString("255")).toInt();
    int b = map.value("color_b", QString("255")).toInt();
    int a = map.value("alpha", QString("255")).toInt();
    m_color = QColor(r,g,b,a);
    m_opacity = map.value("opacity", QString("255")).toInt();
}

QMap<QString, QString> QCCLayerColor::exportData()
{
    QMap<QString, QString> map = QCCLayer::exportData();

    if( !(m_color.red() == 255 && m_color.green() == 255 && m_color.blue() == 255) )
    {
        map.insert("color_r", QString("%1").arg(m_color.red()));
        map.insert("color_g", QString("%1").arg(m_color.green()));
        map.insert("color_b", QString("%1").arg(m_color.blue()));
    }

    if(m_opacity != 255)
    {
        map.insert("opacity", QString("%1").arg(m_opacity));
    }

    return map;
}

QGraphicsItem* QCCLayerColor::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsRectItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCLayerColor::updateGraphicsItem()
{
    QCCLayer::updateGraphicsItem();
    QGraphicsRectItem* item = dynamic_cast<QGraphicsRectItem*>(m_graphicsItem);
    item->setOpacity( m_opacity/255.0f );
    item->setBrush( QBrush(QColor(m_color)) );
}
