#ifndef QCCNODE_H
#define QCCNODE_H

#include "qdefine.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>

//remeber set default value.
class QCCNode
{
public:
    static QCCNode* createCCNodeByType(QString type);
public:
    QCCNode();
    virtual ~QCCNode();

public:
    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();

public:
    QString resourceFullPath(QString relationPath);

public:
    QString m_name;
    QString m_classType;
    bool m_isFixed;
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

public:
    QGraphicsItem* m_graphicsItem;
};

class QCCLayer : public QCCNode
{
public:
    QCCLayer();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();

public:
    bool m_isTouchEnable;
};

class QCCLayerColor : public QCCLayer
{
public:
    QCCLayerColor();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();

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
    virtual QGraphicsItem* createGraphicsItem();

public:
    QString m_filePath;
};

class QCCLabelTTF : public QCCLayerColor
{
public:
    QCCLabelTTF();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();

public:
    QFont m_font;
    QString m_text;
    int m_horizontalTextAlignment;
    int m_verticalTextAlignment;
    int m_dimensionWith;
    int m_dimensionHeight;
};

class QCCMenuItemImage : public QCCSprite
{
public:
    QCCMenuItemImage();
};

class QCCContainerLayer : public QCCLayer
{
public:
    QCCContainerLayer();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();

public:
    QString m_containerConfigFilePath;
};

#endif // QCCNODE_H
