#ifndef QCCNODE_H
#define QCCNODE_H

#include "qdefine.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QPoint>

//remeber set default value.
class QCCNode
{
public:
    static QCCNode* createCCNodeByType(QString type);
    static void createPathMap();
    static void traverseFiles(QString dir, QString dir2);
public:
    QCCNode();
    virtual ~QCCNode();

public:
    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem(); //尽量不要在这个函数里改变基础属性

public:
    QString resourceFullPath(QString relationPath);
    QString luaVariableName();
    QString longPathToShortPath(QString longPath);
    QString shortPathToLongPath(QString longPath);
    QPoint convertToNodePoint(int x, int y);
    QPoint convertToItemPoint(int x, int y);

private:
    QPoint dockOffset();

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
    bool m_isSkipCreate;
    bool m_isSkipInit;
    int m_dockHorizontal;
    int m_dockVertical;

public:
    QList<QCCNode*> m_children;
    QCCNode* m_parent;

public:
    QGraphicsItem* m_graphicsItem;
};

#endif // QCCNODE_H
