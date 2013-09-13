#ifndef QSCENE_H
#define QSCENE_H

#include "qdefine.h"

class QScene : public QGraphicsScene
{
public:
    QScene();

public:
    void test();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QSCENE_H
