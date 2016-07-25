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
    m_isInLanguage = false;
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

    m_isInLanguage = map.value("isInlanguage","0").toInt();
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

    if(m_isInLanguage == true)
    {
        map.insert("isInlanguage", QString('1'));
    }

    return map;
}

QGraphicsItem* QCCLabelTTF::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCLabelTTF::updateGraphicsItem()
{
    if(m_text.isEmpty() == true)
    {
        return ;
    }

    if(m_dimensionWith != 0 && m_dimensionHeight !=0 )
    {
        m_width = m_dimensionWith;
        m_height = m_dimensionHeight;
    }
    else
    {
        //QFontMetrics
        QFontMetrics metrics(m_font);
        m_width = metrics.width(m_text);
        m_height = metrics.height();
    }

    QImage image = QImage(m_width, m_height, QImage::Format_RGBA8888);
    image.fill(0);
    QPainter painter(&image);

    painter.setPen(QColor(m_color));
    painter.setFont(m_font);

    int horzArray[3] = {Qt::AlignLeft,Qt::AlignHCenter,Qt::AlignRight};
    int vertArray[3] = {Qt::AlignTop,Qt::AlignVCenter,Qt::AlignBottom};
    Qt::AlignmentFlag flag = (Qt::AlignmentFlag)(horzArray[m_horizontalAlignment] | vertArray[m_verticalAlignment]);
    QTextOption option = QTextOption(flag);
    option.setFlags( QTextOption::AddSpaceForLineAndParagraphSeparators | QTextOption::ShowLineAndParagraphSeparators);
    option.setWrapMode(QTextOption::WordWrap);
    painter.drawText(QRect(0,0,m_width,m_height), m_text, option);

    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
    item->setPixmap(QPixmap::fromImage(image));

    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}
