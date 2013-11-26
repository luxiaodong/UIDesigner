#include "qccnode.h"
#include "qscene.h"
#include "qstoragedata.h"
#include <QImage>
#include <QPainter>

QCCNode* QCCNode::createCCNodeByType(QString type)
{
    QCCNode* node = 0;
    if(type == CLASS_TYPE_CCNODE)
    {
        node = new QCCNode();
    }
    else if(type == CLASS_TYPE_CCLAYER || type == CLASS_TYPE_ROOT)
    {
        node = new QCCLayer();
    }
    else if(type == CLASS_TYPE_CCLAYERCOLOR)
    {
        node = new QCCLayerColor();
    }
    else if(type == CLASS_TYPE_CCSPRITE)
    {
        QCCSprite* temp = new QCCSprite();
        node = temp;
    }
    else if(type == CLASS_TYPE_CCLABELTTF)
    {
        node = new QCCLabelTTF();
    }
    else if(type == CLASS_TYPE_CCCONTAINERLAYER)
    {
        node = new QCCContainerLayer();
    }
    else if(type == CLASS_TYPE_CCMENUITEM_IMAGE)
    {
        node = new QCCMenuItemImage();
    }

    Q_ASSERT(node != 0);
    static int count = 1;
    node->m_name = QString("node_%1").arg(count++);
    node->m_classType = type;
    return node;
}

QString QCCNode::resourceFullPath(QString relationPath)
{
    QSettings settings("UIDesigner");
    QString prefix = settings.value("resourceDir",QString("")).toString();
    QString fullPath = QString("%1/%2").arg(prefix, relationPath);
    return QDir::toNativeSeparators(fullPath);
}

QString QCCNode::luaVariableName()
{
    QString str = this->m_name;
    QCCNode* parent = this->m_parent;
    while(parent != 0)
    {
        str = QString("%1.children.%2").arg(parent->m_name, str);
        parent = parent->m_parent;
    }

    return str;
}

QCCNode::QCCNode()
{
    m_name = "undefined";
    m_classType = CLASS_TYPE_CCNODE;
    m_children.clear();
    m_parent = 0;
    m_graphicsItem = 0;

    m_isFixed = false;
    m_x = 0;
    m_y = 0;
    m_z = 0;
    m_tag = -1;
    m_width = 0;
    m_height = 0;
    m_rotation = 0;
    m_anchorX = 0.0f;
    m_anchorY = 0.0f;
    m_scaleX = 1.0f;
    m_scaleY = 1.0f;
    m_isVisible = true;
}

QCCNode::~QCCNode()
{
    foreach(QCCNode* node, m_children)
    {
        delete node;
    }
}

void QCCNode::importData(QMap<QString, QString>& map)
{
    m_isFixed = map.value("fixed", QString("0")).toInt();
    m_name = map.value("name", QString("undefined"));
    m_classType = map.value("classType", QString("%1").arg(CLASS_TYPE_CCNODE));
    m_x = map.value("x", QString("0")).toInt();
    m_y = map.value("y", QString("0")).toInt();
    m_z = map.value("z", QString("0")).toInt();
    m_tag = map.value("tag", QString("-1")).toInt();
    m_width = map.value("width", QString("0")).toInt();
    m_height = map.value("height", QString("0")).toInt();
    m_rotation = map.value("rotation", QString("0")).toInt();
    m_anchorX = map.value("anchorX", QString("0.5")).toFloat();
    m_anchorY = map.value("anchorY", QString("0.5")).toFloat();
    m_scaleX = map.value("scaleX", QString("1.0")).toFloat();
    m_scaleY = map.value("scaleY", QString("1.0")).toFloat();
    m_isVisible = map.value("isVisible", QString("1")).toInt();
}

QMap<QString, QString> QCCNode::exportData()
{
    QMap<QString, QString> map;
    map.insert("name", m_name);
    map.insert("classType", m_classType);
    map.insert("x", QString("%1").arg(m_x));
    map.insert("y", QString("%1").arg(m_y));
    map.insert("z", QString("%1").arg(m_z));
    map.insert("width", QString("%1").arg(m_width));
    map.insert("height", QString("%1").arg(m_height));
    map.insert("tag", QString("%1").arg(m_tag));

    if(m_isFixed == true)
    {
        map.insert("fixed","1");
    }

    if(m_rotation != 0)
    {
        map.insert("rotation", QString("%1").arg(m_rotation));
    }

//    map.insert("anchorX", QString("%1").arg(m_anchorX));
//    map.insert("anchorY", QString("%1").arg(m_anchorY));

    if(m_scaleX < 0.99 || m_scaleY > 1.01)
    {
        map.insert("scaleX", QString("%1").arg(m_scaleX));
    }

    if(m_scaleY < 0.99 || m_scaleY > 1.01)
    {
        map.insert("scaleY", QString("%1").arg(m_scaleY));
    }

    if(m_isVisible == false)
    {
        map.insert("isVisible", "0");
    }

    return map;
}

QGraphicsItem* QCCNode::createGraphicsItem()
{
    qDebug()<<"ccnode can't be draw to GraphicsItem";
    Q_ASSERT(0);
    return 0;
}

QCCLayer::QCCLayer()
{
    m_isTouchEnable = false;
    m_classType = CLASS_TYPE_CCLAYER;
}

void QCCLayer::importData(QMap<QString, QString>& map)
{
    QCCNode::importData(map);
    m_isTouchEnable = map.value("isTouchEnable", QString("0")).toInt();;
}

QMap<QString, QString> QCCLayer::exportData()
{
    QMap<QString, QString> map = QCCNode::exportData();
    if( m_isTouchEnable == true )
    {
        map.insert("isTouchEnable", "1");
    }

    return map;
}

QGraphicsItem* QCCLayer::createGraphicsItem()
{
    QGraphicsRectItem* item = new QGraphicsRectItem();
    item->setRect(0,0,m_width,m_height);
    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    m_graphicsItem = item;
    return item;
}

QCCLayerColor::QCCLayerColor()
{
    m_color = QColor(Qt::white);
    m_opacity = 0xff;
    m_classType = CLASS_TYPE_CCLAYERCOLOR;
}

void QCCLayerColor::importData(QMap<QString, QString>& map)
{
    QCCLayer::importData(map);
    int r = map.value("color_r", QString("255")).toInt();
    int g = map.value("color_g", QString("255")).toInt();
    int b = map.value("color_b", QString("255")).toInt();
    int a = map.value("alpha", QString("255")).toInt();
    m_color = QColor(r,g,b,a);
    m_opacity = map.value("opacity", QString("255")).toInt();
}

QMap<QString, QString> QCCLayerColor::exportData()
{
    QMap<QString, QString> map = QCCLayer::exportData();

    if( !(m_color.red() == 255 && m_color.green() == 255 && m_color.blue() == 255) )
    {
        map.insert("color_r", QString("%1").arg(m_color.red()));
        map.insert("color_g", QString("%1").arg(m_color.green()));
        map.insert("color_b", QString("%1").arg(m_color.blue()));
    }

    if(m_opacity != 255)
    {
        map.insert("opacity", QString("%1").arg(m_opacity));
    }

    return map;
}

QGraphicsItem* QCCLayerColor::createGraphicsItem()
{
    QGraphicsRectItem* item = new QGraphicsRectItem();
    item->setBrush( QBrush(QColor(m_color)) );
    item->setRect(0,0,m_width,m_height);
    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    item->setOpacity( m_opacity/255.0f );
    m_graphicsItem = item;
    return item;
}

QCCSprite::QCCSprite()
{
    m_filePath = "";
    m_classType = CLASS_TYPE_CCSPRITE;
}

void QCCSprite::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    m_filePath = map.value("filePath", QString(""));
}

QMap<QString, QString> QCCSprite::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();
    map.insert("filePath", m_filePath);
    return map;
}

QGraphicsItem* QCCSprite::createGraphicsItem()
{
    //qDebug()<<" sprite name -> "<<m_name;
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
    QPixmap pixmap;
    pixmap = QPixmap(resourceFullPath(m_filePath));
//        QSize s = pixmap.size();
//        QImage image = QImage(s.width(), s.height(), QImage::Format_RGB32);

//        for(int j = 0; j < s.height(); ++j)
//        {
//            for(int i = 0;i < s.width(); ++i)
//            {
//                if(i == 0 || i == s.width() -1 || j == 0 || j == s.height() - 1)
//                {
//                    image.setPixel(i,j,0xFFFFFF);
//                }
//                else if(i == 1 || i == s.width() -2 || j == 1 || j == s.height() - 2)
//                {
//                    image.setPixel(i,j,0xFFFFFF);
//                }
//                else if(i == 2 || i == s.width() -3 || j == 2 || j == s.height() - 3)
//                {
//                    image.setPixel(i,j,0xFF0000);
//                }
//                else if(i == 3 || i == s.width() -4 || j == 3 || j == s.height() - 4)
//                {
//                    image.setPixel(i,j,0xFF0000);
//                }
//                else
//                {
//                    image.setPixel(i,j,0x0);
//                }
//            }
//        }

//        pixmap = QPixmap::fromImage(image);

//  pixmap.fill(QColor(qrand()%255, qrand()%255, qrand()%255));
    item->setPixmap(pixmap);
    QSize s = pixmap.size();
    m_width = s.width();
    m_height = s.height();

    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);

    m_graphicsItem = item;
    return item;
}

QCCLabelTTF::QCCLabelTTF()
{
    m_text = "CCLabelTTF";
    m_font = QFont();
    m_font.setPointSize(20);
    m_classType = CLASS_TYPE_CCLABELTTF;
    m_horizontalTextAlignment = kCCHorizontalTextAlignmentCenter;
    m_verticalTextAlignment = kCCVerticalTextAlignmentCenter;
    m_dimensionWith = 0;
    m_dimensionHeight = 0;
}

void QCCLabelTTF::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    m_text = map.value("text", QString(""));
    //QString family = map.value("fontName", QString("")); //default font
    int pointSize = map.value("pointSize", QString("18")).toInt();
    m_font = QFont();
    m_font.setPointSize(pointSize);
}

QMap<QString, QString> QCCLabelTTF::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();
    map.insert("text", m_text);
    //map.insert("fontName", m_font.family());
    map.insert("pointSize", QString("%1").arg(m_font.pointSize()));
    return map;
}

QGraphicsItem* QCCLabelTTF::createGraphicsItem()
{
    QGraphicsTextItem* item = new QGraphicsTextItem();
    item->setFont(m_font);
    item->setHtml(m_text);
    item->setDefaultTextColor(QColor(m_color));

    QSizeF s = item->boundingRect().size();
    m_width = s.width();
    m_height = s.height();

    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    m_graphicsItem = item;
    return item;
}

QCCMenuItemImage::QCCMenuItemImage()
{
    m_classType = CLASS_TYPE_CCMENUITEM_IMAGE;
}

void QCCMenuItemImage::importData(QMap<QString, QString>& map)
{
    QCCSprite::importData(map);
    m_filePath = map.value("image_n", QString(""));
}

QMap<QString, QString> QCCMenuItemImage::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();
    map.insert("image_n", m_filePath);
    return map;
}

QCCContainerLayer::QCCContainerLayer()
{
    m_containerConfigFilePath = "";
}

void QCCContainerLayer::importData(QMap<QString, QString> &map)
{
    QCCLayer::importData(map);
    m_containerConfigFilePath = map.value("containerConfigFilePath", QString(""));
}

QMap<QString, QString> QCCContainerLayer::exportData()
{
    QMap<QString, QString> map = QCCLayer::exportData();
    map.insert("containerConfigFilePath", m_containerConfigFilePath);
    return map;
}

QGraphicsItem* QCCContainerLayer::createGraphicsItem()
{
    qDebug()<<m_containerConfigFilePath;
    QString fullPath = resourceFullPath(m_containerConfigFilePath);
    QStorageData storageData;
    QCCNode* root = storageData.readUIFile(fullPath);
    QScene scene;
    scene.setSceneRect(0,0,root->m_width, root->m_height);
    scene.createGraphicsItemByCCNode( root, 0);

    QImage image = QImage(root->m_width, root->m_height, QImage::Format_ARGB32);
    QPainter painter(&image);
    scene.render(&painter);
    //image.save(QString("%1.png").arg(fullPath), "png");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
    item->setPixmap( QPixmap::fromImage(image) );

    m_width = root->m_width;
    m_height = root->m_height;

    if(root->m_classType == CLASS_TYPE_CCSPRITE)
    {
        item->resetTransform();
        item->setTransform(QTransform().rotate(m_rotation), true);
        item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
        item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    }
    else if(root->m_classType == CLASS_TYPE_CCLAYER || root->m_classType == CLASS_TYPE_CCLAYERCOLOR)
    {
        item->setTransform(QTransform::fromTranslate(0, -m_height));
    }

    item->setFlag(QGraphicsItem::ItemIsMovable, true);
    m_graphicsItem = item;

    return item;
}
