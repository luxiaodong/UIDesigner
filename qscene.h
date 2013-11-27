#ifndef QSCENE_H
#define QSCENE_H

#include "qdefine.h"
#include "qccnode.h"

#define GRAPHICS_ITEM_NAME_TAG  1
#define GRAPHICS_ITEM_CLASS_TAG  2

//少了一个切换select的item
class QScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QScene();

public:
    void test();
    void reset();
    void createGraphicsItemByCCNode(QCCNode* node, QGraphicsItem* parentItem);
    void changeSimpleTextItemBounding();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:
    void showMessage(QString msg);
    void changeItemSelect(QGraphicsItem* item);
    void changeItemPoint(int x, int y);

public slots:
    void changedItemSelect(QCCNode* node);
    void changedItemPoint(int x, int y);

private:
    QGraphicsItem* m_selectItem;
    QGraphicsRectItem* m_boundingRect;
};

#endif // QSCENE_H
