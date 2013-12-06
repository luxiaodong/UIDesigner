#ifndef QCCNODE_H
#define QCCNODE_H

#include "qdefine.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

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
    virtual void updateGraphicsItem();

public:
    QString resourceFullPath(QString relationPath);
    QString luaVariableName();

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
    virtual void updateGraphicsItem();

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
    virtual void updateGraphicsItem();

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
    virtual void updateGraphicsItem();

public:
    QString m_filePath;
};

class QCCScale9Sprite : public QCCSprite
{
public:
    QCCScale9Sprite();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();

public:
    QRect m_insetsRect;
    QSize m_preferredSize;
};

class QCCLabelTTF : public QCCLayerColor
{
public:
    QCCLabelTTF();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();

public:
    QFont m_font;
    QString m_text;
    int m_horizontalAlignment;
    int m_verticalAlignment;
    int m_dimensionWith;
    int m_dimensionHeight;
};

class QCCMenuItemImage : public QCCSprite
{
public:
    QCCMenuItemImage();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();
};

class QCCContainerLayer : public QCCLayer
{
public:
    QCCContainerLayer();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();

public:
    QString m_containerConfigFilePath;
};

#endif // QCCNODE_H
