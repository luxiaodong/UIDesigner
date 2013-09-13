#ifndef QCCNODE_H
#define QCCNODE_H

#include "qdefine.h"

//remeber set default value.
class QCCNode
{
public:
    QCCNode();

public:
    int m_x;
    int m_y;
    int m_z;
    int m_tag;
    bool m_visible;
};

class QCCLayer : public QCCNode
{
public:
    QCCLayer();

public:
    int m_width;
    int m_height;
    bool m_enable;
    float m_anchorX;
    float m_anchorY;
    float m_scaleX;
    float m_scaleY;
    float m_rotate;
};

class QCCLayerColor : public QCCLayer
{
public:
    QCCLayerColor();

public:
    QColor m_color;
};

class QCCSprite : public QCCLayerColor
{
public:
    QCCSprite();

public:
    QString m_filePath;
};

class QCCLabelTTF : public QCCLayerColor
{
public:
    QCCLabelTTF();

public:
    QFont m_font;
    QString m_text;
};

#endif // QCCNODE_H
