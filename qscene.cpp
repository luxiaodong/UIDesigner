#include "qscene.h"
#include <QGraphicsSceneMouseEvent>

QScene::QScene()
{
    m_selectItem = 0;
}

void QScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     QPointF pt = event->scenePos();
     QTransform trans;
     QGraphicsItem* item = this->itemAt(pt, trans);
     if(item != 0)
     {
         m_selectItem = item;
     }
     QGraphicsScene::mousePressEvent(event);
}

void QScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem* item = this->mouseGrabberItem();
    if (item != 0)
    {
        qDebug()<<"scene move "<<item->data(1).toString();
        qDebug()<<"scene move "<<item->x()<<item->y();
        int x = item->x();
        int y = item->y();
        emit changeItemPoint(x, y);
    }
    //emit currentItemPropertyChanged(item);
    QGraphicsScene::mouseMoveEvent(event);
}

void QScene::test()
{
    QGraphicsRectItem* r1 = this->addRect(-25,-25,50,50,QPen(Qt::red),QBrush(QColor(Qt::red)));
    QGraphicsRectItem* r2 = this->addRect(-100,-100,200,200,QPen(Qt::green), QBrush(QColor(Qt::green)));
    QGraphicsRectItem* r3 = new QGraphicsRectItem(-25,-25,50,50, r2);

    r1->setData(1, "r1");
    //r1->setFlag(QGraphicsItem::ItemIsMovable, true);

    r2->setPos(125,125);
    r2->setData(1, "r2");
    //r2->setFlag(QGraphicsItem::ItemIsSelectable, true);
    r2->setFlag(QGraphicsItem::ItemIsMovable, true);

    r3->setPos(100,100);
    r3->setBrush(QBrush(QColor(Qt::blue)));
    r3->setData(1, "r3");
    r3->setFlag(QGraphicsItem::ItemIsMovable, true);
}

void QScene::changedItemPoint(int x, int y)
{
    if(m_selectItem != 0)
    {
        m_selectItem->setPos(x, y);
    }
}

void QScene::changedItemZ(int z)
{
    if(m_selectItem != 0)
    {
        m_selectItem->setZValue(z);
    }
}

void QScene::changedItemSize(int width, int height)
{}

void QScene::changedItemAnchor(float anchorX, float anchorY)
{}

void QScene::changedItemScale(float scaleX, float scaleY)
{}

void QScene::changedItemRotation(int rotation)
{}

void QScene::changedItemVisible(bool visible)
{
    if(m_selectItem != 0)
    {
        m_selectItem->setVisible(visible);
    }
}

void QScene::changedItemTouchEnable(bool touchEnable)
{
    if(m_selectItem != 0)
    {
        m_selectItem->setVisible(visible);
    }
}

void QScene::changedItemColor(QColor& color)
{}

void QScene::changedItemOpacity(int opacity)
{}

void QScene::changedItemFilePath(QString& filePath)
{}

void QScene::changedItemFont(QFont& font)
{}

void QScene::changedItemText(QString& text)
{}

