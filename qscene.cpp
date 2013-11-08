#include "qscene.h"
#include <QGraphicsSceneMouseEvent>

QScene::QScene()
{
    m_selectItem = 0;
    //m_boundingRect = new QGraphicsRectItem();
    //m_boundingRect->setPen(QPen(QColor(Qt::red)));
}

void QScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
     QPointF pt = event->scenePos();
     //QTransform trans;
     QList<QGraphicsItem*> items = this->items(pt);
     if(items.size() > 0)
     {
         QGraphicsItem* item = items.at(0);
         m_selectItem = item;
         emit changeItemSelect(item);
     }
     QGraphicsScene::mousePressEvent(event);
}

void QScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    emit showMessage( QString("%1,%2").arg( event->scenePos().x() ).arg( this->height() - event->scenePos().y()) );
    QGraphicsItem* item = this->mouseGrabberItem();
    if (item != 0 && item == m_selectItem)
    {
        //qDebug()<<"scene move "<<item->data(1).toString();
        //qDebug()<<"scene move "<<item->x()<<item->y();
        int x = item->x();
        int y = item->y();

        QGraphicsItem* parentItem = item->parentItem();
        if(parentItem != 0)
        {
            y = parentItem->boundingRect().size().height() - 1 - y;
        }
        else
        {
            y = this->height() - 1 - y;
        }

        emit changeItemPoint(x, y);
    }
    //emit currentItemPropertyChanged(item);
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
    item->setZValue(node->m_z);

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

//        qDebug()<<height;
//        qDebug()<<height - y;
        m_selectItem->setPos(x, height - 1 - y);
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
        m_selectItem->setVisible(touchEnable);
    }
}

void QScene::changedItemColor(QColor& color)
{}

void QScene::changedItemOpacity(int opacity)
{}

void QScene::changedItemFilePath(QString& filePath)
{
    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_selectItem);
    QPixmap pixmap(filePath);
    item->setPixmap(pixmap);

    //要做些相应调整,对于放大缩小等东西
    QSize s = pixmap.size();
    QTransform t = QTransform::fromTranslate(-s.width()/2, -s.height()/2);
    item->setTransform(t);
}

void QScene::changedItemFont(QFont& font)
{}

void QScene::changedItemText(QString& text)
{}

