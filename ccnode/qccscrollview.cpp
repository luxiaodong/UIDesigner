#include "qccscrollview.h"
#include "qscene.h"
#include "qstoragedata.h"

QCCScrollView::QCCScrollView()
{
    m_containerConfigFilePath = "";
    m_direction = kCCScrollViewDirectionHorizontal;
    m_count = 1;
    m_offsetX = 0;
    m_offsetY = 0;
    m_spaceWidth = 0;
    m_spaceHeight = 0;
    m_contentWidth = 100;
    m_contentHeight = 100;
    m_isDynamicallyGenerated = false;
}

void QCCScrollView::importData(QMap<QString, QString>& map)
{
    QCCLayer::importData(map);
    m_containerConfigFilePath = map.value("filePath", QString(""));
    m_direction = map.value("direction","0").toInt();
    m_count = map.value("count","0").toInt();
    m_offsetX = map.value("offsetX","0").toInt();
    m_offsetY = map.value("offsetY","0").toInt();
    m_spaceWidth = map.value("spaceWidth","0").toInt();
    m_spaceHeight = map.value("spaceHeight","0").toInt();
    m_contentWidth = map.value("contentWidth","100").toInt();
    m_contentHeight = map.value("contentHeight","100").toInt();
    m_isDynamicallyGenerated = map.value("isDynamicallyGenerated","0").toInt();
}

QMap<QString, QString> QCCScrollView::exportData()
{
    QMap<QString, QString> map = QCCLayer::exportData();
    map.insert("filePath", m_containerConfigFilePath);
    map.insert("direction", QString("%1").arg(m_direction));
    map.insert("count", QString("%1").arg(m_count));
    map.insert("offsetX", QString("%1").arg(m_offsetX));
    map.insert("offsetY", QString("%1").arg(m_offsetY));
    map.insert("spaceWidth", QString("%1").arg(m_spaceWidth));
    map.insert("spaceHeight", QString("%1").arg(m_spaceHeight));
    map.insert("contentWidth", QString("%1").arg(m_contentWidth));
    map.insert("contentHeight", QString("%1").arg(m_contentHeight));
    map.insert("isDynamicallyGenerated", QString("%1").arg(m_isDynamicallyGenerated == true ? 1 : 0));
    return map;
}

QGraphicsItem* QCCScrollView::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCScrollView::updateGraphicsItem()
{
    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);

    QImage image = QImage(m_contentWidth, m_contentHeight, QImage::Format_ARGB32);
    image.fill(0);
    QPainter painter(&image);

    QString fullPath = resourceFullPath(m_containerConfigFilePath);
    QStorageData storageData;
    QCCNode* root = storageData.readUIFile(fullPath);

    if(m_isDynamicallyGenerated == true || root == 0)
    {
        painter.fillRect(0,0,m_contentWidth, m_contentHeight, QBrush(QColor(Qt::white)));
        item->setPixmap( QPixmap::fromImage(image) );
    }
    else
    {
        QRect srcRect(0,0,root->m_width, root->m_height);
        QScene scene;
        scene.setSceneRect(srcRect);
        scene.createGraphicsItemByCCNode(root, 0);

        int x = m_offsetX;
        int y = (m_contentHeight - root->m_height) - m_offsetY;

        if(m_direction == kCCScrollViewDirectionHorizontal)
        {
            for(int i = 0; i < m_count; ++i)
            {
                QRect targetRect(x + i*(root->m_width+m_spaceWidth), y, root->m_width, root->m_height);
                scene.render(&painter, targetRect, srcRect);
            }
        }
        else if(m_direction == kCCScrollViewDirectionVertical)
        {
            for(int i = 0; i < m_count; ++i)
            {
                QRect targetRect(x, y + i*(root->m_height+m_spaceHeight), root->m_width, root->m_height);
                scene.render(&painter, targetRect, srcRect);
            }
        }

        QImage copyImage = image.copy(0,0,m_contentWidth, m_contentHeight);
        item->setPixmap( QPixmap::fromImage(copyImage) );
    }

    m_width = m_contentWidth;
    m_height = m_contentHeight;
    item->resetTransform();
    item->setTransform(QTransform::fromTranslate(0, -m_height));
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}
