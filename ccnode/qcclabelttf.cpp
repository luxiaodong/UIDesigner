#include "qcclabelttf.h"


QCCLabelTTF::QCCLabelTTF()
{
    m_text = "CCLabelTTF";
    m_font = QFont();
    m_font.setPointSize(20);
    m_classType = CLASS_TYPE_CCLABELTTF;
    m_horizontalAlignment = kCCHorizontalTextAlignmentCenter;
    m_verticalAlignment = kCCVerticalTextAlignmentCenter;
    m_dimensionWith = 0;
    m_dimensionHeight = 0;
}

void QCCLabelTTF::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    m_text = map.value("text", QString(""));
    //QString family = map.value("fontName", QString("")); //default font
    int pointSize = map.value("pointSize", QString("20")).toInt();
    m_font = QFont();
    m_font.setPointSize(pointSize);

    m_dimensionWith = map.value("dimensionWith", "0").toInt();
    if(m_dimensionWith > 0)
    {
        m_dimensionHeight = map.value("dimensionHeight", "0").toInt();
        m_horizontalAlignment = map.value("horizontalAlignment").toInt();
        m_verticalAlignment = map.value("verticalAlignment").toInt();
    }
}

QMap<QString, QString> QCCLabelTTF::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();
    map.insert("text", m_text);
    //map.insert("fontName", m_font.family());
    map.insert("pointSize", QString("%1").arg(m_font.pointSize()));

    if(m_dimensionWith > 0)
    {
        map.insert("dimensionWith", QString("%1").arg(m_dimensionWith));
        map.insert("dimensionHeight", QString("%1").arg(m_dimensionHeight));
        map.insert("horizontalAlignment",QString("%1").arg(m_horizontalAlignment));
        map.insert("verticalAlignment",QString("%1").arg(m_verticalAlignment));
    }

    return map;
}

QGraphicsItem* QCCLabelTTF::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsTextItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCLabelTTF::updateGraphicsItem()
{
    QGraphicsTextItem* item = dynamic_cast<QGraphicsTextItem*>(m_graphicsItem);
    item->setFont(m_font);
    item->setHtml(m_text);
    item->setDefaultTextColor(QColor(m_color));

    if(m_dimensionWith == 0)
    {
        item->setTextWidth(-1);
        QSizeF s = item->boundingRect().size();
        m_width = s.width();
        m_height = s.height();
        m_dimensionWith = 0;
        m_dimensionHeight = 0;
    }
    else
    {
        item->setTextWidth(m_dimensionWith);
        m_width = m_dimensionWith;
        m_height = m_dimensionHeight;

        QTextBlockFormat format;
        int horzArray[3] = {Qt::AlignLeft,Qt::AlignHCenter,Qt::AlignRight};
        int vertArray[3] = {Qt::AlignTop,Qt::AlignVCenter,Qt::AlignBottom};
        format.setAlignment((Qt::AlignmentFlag)(horzArray[m_horizontalAlignment] | vertArray[m_verticalAlignment] ));
        QTextCursor cursor = item->textCursor();
        cursor.select(QTextCursor::Document);
        cursor.mergeBlockFormat(format);
        cursor.clearSelection();
        item->setTextCursor(cursor);
    }

    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}
