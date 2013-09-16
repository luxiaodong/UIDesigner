#include "qccnode.h"

QCCNode::QCCNode()
{
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

QCCLayer::QCCLayer()
{
    m_isTouchEnable = true;
}

QCCLayerColor::QCCLayerColor()
{
    m_color = QColor(Qt::black);
    m_opacity = 0xff;
}

QCCSprite::QCCSprite()
{
    m_filePath = "";
}

QCCLabelTTF::QCCLabelTTF()
{
    m_text = "";
    m_font = QFont();
}
