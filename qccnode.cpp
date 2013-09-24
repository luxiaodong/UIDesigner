#include "qccnode.h"

QCCNode::QCCNode()
{
    m_name = "undefined";
    m_classType = CLASS_TYPE_CCNODE;
    m_children.clear();
    m_parent = 0;

    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_tag = -1;
    m_width = 0;
    m_height = 0;
    m_rotation = 0;
    m_anchorX = 0.0f;
    m_anchorY = 0.0f;
    m_scaleX = 1.0f;
    m_scaleY = 1.0f;
    m_isVisible = true;
}

QCCNode::~QCCNode()
{}

void QCCNode::importData(QMap<QString, QString>& map)
{
    m_name = map.value("name", QString("undefined"));
    m_classType = map.value("classType", QString("%1").arg(CLASS_TYPE_CCNODE));
    m_x = map.value("x", QString("0")).toInt();
    m_y = map.value("y", QString("0")).toInt();
    m_z = map.value("z", QString("0")).toInt();
    m_tag = map.value("tag", QString("-1")).toInt();
    m_width = map.value("width", QString("0")).toInt();
    m_height = map.value("height", QString("0")).toInt();
    m_rotation = map.value("rotation", QString("0")).toInt();
    m_anchorX = map.value("anchorX", QString("0.0")).toFloat();
    m_anchorY = map.value("anchorY", QString("0.0")).toFloat();
    m_scaleX = map.value("scaleX", QString("0.0")).toFloat();
    m_scaleY = map.value("scaleY", QString("0.0")).toFloat();
    m_isVisible = map.value("isVisible", QString("1")).toInt();
}

QMap<QString, QString> QCCNode::exportData()
{
    QMap<QString, QString> map;
    map.insert("x", QString("%1").arg(m_x));
    map.insert("y", QString("%1").arg(m_y));
    map.insert("z", QString("%1").arg(m_z));
    map.insert("tag", QString("%1").arg(m_tag));
    map.insert("width", QString("%1").arg(m_width));
    map.insert("height", QString("%1").arg(m_height));
    map.insert("rotation", QString("%1").arg(m_rotation));
    map.insert("anchorX", QString("%1").arg(m_anchorX));
    map.insert("anchorY", QString("%1").arg(m_anchorY));
    map.insert("scaleX", QString("%1").arg(m_scaleX));
    map.insert("scaleY", QString("%1").arg(m_scaleY));
    map.insert("isVisible", QString("%1").arg( (m_isVisible == true) ? 1 : 0 ));
    return map;
}

QCCLayer::QCCLayer()
{
    m_isTouchEnable = false;
}

void QCCLayer::importData(QMap<QString, QString>& map)
{
    QCCNode::importData(map);
    m_isTouchEnable = map.value("isTouchEnable", QString("0")).toInt();;
}

QMap<QString, QString> QCCLayer::exportData()
{
    QMap<QString, QString> map = QCCNode::exportData();
    map.insert("isTouchEnable", QString("%1").arg( (m_isTouchEnable == true) ? 1 : 0 ));
    return map;
}

QCCLayerColor::QCCLayerColor()
{
    m_color = QColor(Qt::white);
    m_opacity = 0xff;
}

void QCCLayerColor::importData(QMap<QString, QString>& map)
{
    QCCLayer::importData(map);
    int r = map.value("red", QString("255")).toInt();
    int g = map.value("green", QString("255")).toInt();
    int b = map.value("blue", QString("255")).toInt();
    int a = map.value("alpha", QString("255")).toInt();
    m_color = QColor(r,g,b,a);
    m_opacity = map.value("opacity", QString("255")).toInt();
}

QMap<QString, QString> QCCLayerColor::exportData()
{
    QMap<QString, QString> map = QCCLayer::exportData();
    map.insert("red", QString("%1").arg(m_color.red()));
    map.insert("green", QString("%1").arg(m_color.green()));
    map.insert("blue", QString("%1").arg(m_color.blue()));
    map.insert("alpha", QString("%1").arg(m_color.alpha()));
    map.insert("opacity", QString("%1").arg(m_opacity));
    return map;
}

QCCSprite::QCCSprite()
{
    m_filePath = "";
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

QCCLabelTTF::QCCLabelTTF()
{
    m_text = "";
    m_font = QFont();
}

void QCCLabelTTF::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    m_text = map.value("text", QString(""));
    QString family = map.value("family", QString("")); //default font
    int pointSize = map.value("pointSize", QString("18")).toInt();
    m_font = QFont(family,pointSize);
}

QMap<QString, QString> QCCLabelTTF::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();
    map.insert("text", m_text);
    map.insert("family", m_font.family());
    map.insert("pointSize", QString("%1").arg(m_font.pointSize()));
    return map;
}