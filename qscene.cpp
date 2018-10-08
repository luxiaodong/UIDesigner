#include "qscene.h"
#include <QGraphicsSceneMouseEvent>

QScene::QScene()
{
}

void QScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     QPointF pt = event->scenePos();
     //QTransform trans;
     QList<QGraphicsItem*> items = this->items(pt);
     if(items.size() > 0)
     {
         QGraphicsItem* item = items.at(0);

         if(m_boundingRect == item)
         {
             if(items.size() > 1)
             {
                 item = items.at(1);
             }
         }

         emit changeItemSelect(item);
     }
     QGraphicsScene::mousePressEvent(event);
}

void QScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pt = event->scenePos();
    emit changeMouseMove(pt.x(), this->height() - pt.y());
    QGraphicsScene::mouseMoveEvent(event);
}

void QScene::test()
{
    QGraphicsRectItem* r1 = this->addRect(-3,-3,6,6,QPen(Qt::red),QBrush(QColor(Qt::red)));
    QGraphicsRectItem* r2 = this->addRect(-6,-6,12,12,QPen(Qt::green), QBrush(QColor(Qt::green)));
    QGraphicsRectItem* r3 = new QGraphicsRectItem(0,0,3,3, r2);
    QGraphicsRectItem* r4 = new QGraphicsRectItem(-25,-25,50,50, r2);

    QTransform t1;
    QTransform t2 = t1.translate(-25, -25);
    r3->setTransform( t2 );

    qDebug()<<"r1 "<<r1->pos();
    qDebug()<<"r2 "<<r2->pos();
    qDebug()<<"r3 "<<r3->pos();
    qDebug()<<"r4 "<<r4->pos();

    r1->setData(GRAPHICS_ITEM_NAME_TAG, "1");
    //r1->setFlag(QGraphicsItem::ItemIsMovable, true);

    //r2->setPos(125,125);
    r2->setData(GRAPHICS_ITEM_NAME_TAG, "0");
    //r2->setFlag(QGraphicsItem::ItemIsSelectable, true);
    r2->setFlag(QGraphicsItem::ItemIsMovable, true);

    //r3->setPos(100,100);
    r3->setBrush(QBrush(QColor(Qt::blue)));
    r3->setData(GRAPHICS_ITEM_NAME_TAG, "00");
    r3->setFlag(QGraphicsItem::ItemIsMovable, true);

    //r4->setPos(50,50);
    r4->setBrush(QBrush(QColor(Qt::yellow)));
    r4->setData(GRAPHICS_ITEM_NAME_TAG, "01");
    r4->setFlag(QGraphicsItem::ItemIsMovable, true);

    qDebug()<<"r1 "<<r1->pos();
    qDebug()<<"r2 "<<r2->pos();
    qDebug()<<"r3 "<<r3->pos();
    qDebug()<<"r4 "<<r4->pos();
    qDebug()<<"r1 "<<r1->transform();
    qDebug()<<"r2 "<<r2->transform();
    qDebug()<<"r3 "<<r3->transform();
    qDebug()<<"r4 "<<r4->transform();
}

void QScene::reset()
{
    this->clear();
    m_selectItem = 0;
    m_boundingRect = new QGraphicsRectItem();
    m_boundingRect->setPen(QPen(QColor(Qt::red)));
    m_boundingRect->setZValue(10000000);
    m_boundingRect->setVisible(false);
    this->addItem(m_boundingRect);

//    QGraphicsLineItem* line;
//    line = new QGraphicsLineItem(QLine(0,0,200,200));
//    line->setPen(QPen(QColor(Qt::red)));
//    this->addItem(line);
//    line = new QGraphicsLineItem(QLine(0,200,200,0));
//    line->setPen(QPen(QColor(Qt::red)));
//    this->addItem(line);
//    line = new QGraphicsLineItem(QLine(100,0,100,200));
//    line->setPen(QPen(QColor(Qt::red)));
//    this->addItem(line);
//    line = new QGraphicsLineItem(QLine(0,100,200,100));
//    line->setPen(QPen(QColor(Qt::red)));
//    this->addItem(line);
}

void QScene::createGraphicsItemByCCNode(QCCNode* node, QGraphicsItem* parentItem)
{
    QGraphicsItem* item = node->createGraphicsItem();
    int height = node->m_height;
    if(parentItem == 0)
    {
        this->addItem(item);
    }
    else
    {
        item->setParentItem(parentItem);
        height = node->m_parent->m_height;
    }

    item->setPos(node->m_x, height - node->m_y);

    foreach(QCCNode* son, node->m_children)
    {
        this->createGraphicsItemByCCNode(son, item);
    }
}

void QScene::changedItemSelect(QCCNode* node)
{
    //add 红色边框
    QGraphicsItem* item = node->m_graphicsItem;
    m_selectItem = item;

    QRectF r = m_selectItem->boundingRect();
    m_boundingRect->setRect( m_selectItem->mapToScene(r).boundingRect()  );
    m_boundingRect->setVisible(true);
}

void QScene::changedItemPoint(int x, int y)
{
    if(m_selectItem != 0)
    {
        int height = this->height();
        if(m_selectItem->parentItem() != 0)
        {
            height = m_selectItem->parentItem()->boundingRect().height();
        }

        m_selectItem->setPos(x, height - y);
        QRectF r = m_selectItem->boundingRect();
        m_boundingRect->setRect( m_selectItem->mapToScene(r).boundingRect()  );
        m_boundingRect->setVisible(true);
    }
}
