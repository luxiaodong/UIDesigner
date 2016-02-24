#include "qcccontainerlayer.h"
#include "qscene.h"
#include "qstoragedata.h"

QCCContainerLayer::QCCContainerLayer()
{
    m_containerConfigFilePath = "";
}

void QCCContainerLayer::importData(QMap<QString, QString> &map)
{
    QCCLayer::importData(map);
    m_containerConfigFilePath = map.value("filePath", QString(""));
}

QMap<QString, QString> QCCContainerLayer::exportData()
{
    QMap<QString, QString> map = QCCLayer::exportData();
    map.insert("filePath", m_containerConfigFilePath);
    return map;
}

QGraphicsItem* QCCContainerLayer::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCContainerLayer::updateGraphicsItem()
{
    QString fullPath = resourceFullPath(m_containerConfigFilePath);
    QStorageData storageData;
    QCCNode* root = storageData.readUIFile(fullPath);
    QScene scene;
    scene.setSceneRect(0,0,root->m_width, root->m_height);
    scene.createGraphicsItemByCCNode( root, 0);

    QImage image = QImage(root->m_width, root->m_height, QImage::Format_ARGB32);
    image.fill(0);
    QPainter painter(&image);
    //差了一个像素，不知道为什么
    scene.render(&painter, QRectF(1,1,root->m_width-1, root->m_height-1), QRectF(1,1,root->m_width-1, root->m_height-1) );
    //image.save(QString("%1.png").arg(fullPath), "png");

    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
    item->setPixmap( QPixmap::fromImage(image) );

    m_width = root->m_width;
    m_height = root->m_height;

    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}
