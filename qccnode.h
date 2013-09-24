#ifndef QCCNODE_H
#define QCCNODE_H

#include "qdefine.h"

//remeber set default value.
//treeView 改变的时候,目前无法获得以前的名字,导致在scene里无法找到原来的,这里需要重新考虑数据组织结构
class QCCNode
{
public:
    QCCNode();
    ~QCCNode();

public:
    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();

public:
    QString m_name;
    QString m_classType;
    int m_x;
    int m_y;
    int m_z;
    int m_tag;
    int m_width;
    int m_height;
    int m_rotation;
    float m_anchorX;
    float m_anchorY;
    float m_scaleX;
    float m_scaleY;
    bool m_isVisible;

public:
    QList<QCCNode*> m_children;
    QCCNode* m_parent;
};

class QCCLayer : public QCCNode
{
public:
    QCCLayer();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();

public:
    bool m_isTouchEnable;
};

class QCCLayerColor : public QCCLayer
{
public:
    QCCLayerColor();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();

public:
    QColor m_color;
    int m_opacity;
};

class QCCSprite : public QCCLayerColor
{
public:
    QCCSprite();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();

public:
    QString m_filePath;
};

class QCCLabelTTF : public QCCLayerColor
{
public:
    QCCLabelTTF();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();

public:
    QFont m_font;
    QString m_text;
};

#endif // QCCNODE_H