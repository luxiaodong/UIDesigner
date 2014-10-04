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

    //是不是应该把xml那块移动这边, 绘画那一块已经在这边了

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

#endif // QCCNODE_H
