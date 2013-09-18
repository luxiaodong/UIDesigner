#ifndef QSCENE_H
#define QSCENE_H

#include "qdefine.h"

class QScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QScene();

public:
    void test();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:
    void changeItemPoint(int x, int y);

private:
    QGraphicsItem* m_selectItem;
};

#endif // QSCENE_H
