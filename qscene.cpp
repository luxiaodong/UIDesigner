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
    item->setVisible(node->m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !node->m_isFixed);

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

void QScene::changedItemFixed(bool fixed)
{
    if(m_selectItem != 0)
    {
        m_selectItem->setFlag(QGraphicsItem::ItemIsMovable, !fixed);
    }
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

void QScene::changedItemScaleAndRotation(float scaleX, float scaleY, int rotation)
{
    if(m_selectItem != 0)
    {
        //必须是sprite才可以设置
        //
        QRectF r = m_selectItem->boundingRect();
        m_selectItem->setTransformOriginPoint(-r.width()/2, -r.height()/2);

        m_selectItem->resetTransform();
        m_selectItem->setTransform(QTransform().rotate(rotation), true);
        m_selectItem->setTransform(QTransform::fromScale(scaleX,scaleY), true);
        m_selectItem->setTransform(QTransform::fromTranslate(-r.width()/2, -r.height()/2), true);
    }
}

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

void QScene::changedItemColor(QColor& color, QString& classType)
{
    if(m_selectItem != 0)
    {
        if(classType == CLASS_TYPE_CCLAYERCOLOR)
        {
            QGraphicsRectItem* item = dynamic_cast<QGraphicsRectItem*>(m_selectItem);
            item->setBrush(QBrush(QColor(color)));
        }
        else if(classType == CLASS_TYPE_CCLABELTTF)
        {
            QGraphicsSimpleTextItem* item = dynamic_cast<QGraphicsSimpleTextItem*>(m_selectItem);
            item->setBrush(QBrush(QColor(color)));
        }
    }
}

void QScene::changedItemOpacity(int opacity)
{
    if(m_selectItem != 0)
    {
        m_selectItem->setOpacity(opacity/255.0f);
    }
}

void QScene::changedItemFilePath(QString& filePath)
{
    if(m_selectItem != 0)
    {
        QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_selectItem);
        QTransform t = item->transform();
        QPixmap pixmap(filePath);
        item->setPixmap(pixmap);
        QSize r = pixmap.size();
        m_selectItem->setTransformOriginPoint(-r.width()/2, -r.height()/2);
        m_selectItem->resetTransform();
        m_selectItem->setTransform(t, true);
    }
}

void QScene::changedItemFont(QFont& font)
{
    if(m_selectItem != 0)
    {
        QGraphicsSimpleTextItem* item = dynamic_cast<QGraphicsSimpleTextItem*>(m_selectItem);
        item->setFont(font);
    }
}

void QScene::changedItemText(QString& text)
{
    if(m_selectItem != 0)
    {
        QGraphicsSimpleTextItem* item = dynamic_cast<QGraphicsSimpleTextItem*>(m_selectItem);
        item->setText(text);
    }
}

