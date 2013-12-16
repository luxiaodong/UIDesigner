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
    else if(type == CLASS_TYPE_CCLAYER)
    {
        node = new QCCLayer();
    }
    else if(type == CLASS_TYPE_CCLAYERCOLOR)
    {
        node = new QCCLayerColor();
    }
    else if(type == CLASS_TYPE_CCSPRITE)
    {
        node = new QCCSprite();
    }
    else if(type == CLASS_TYPE_CCSCALE9SPRITE)
    {
        node = new QCCScale9Sprite();
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
    else if(type == CLASS_TYPE_CCPROGRESSTIMER)
    {
        node = new QCCProgressTimer();
    }
    else if(type == CLASS_TYPE_CCLABELATLAS)
    {
        node = new QCCLabelAtlas();
    }

    Q_ASSERT(node != 0);
    static int count = 1;
    node->m_name = QString("node_%1").arg(count);
    node->m_z = count++;
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
    qDebug()<<"ccnode can't be create to GraphicsItem";
    Q_ASSERT(0);
    return 0;
}

void QCCNode::updateGraphicsItem()
{
    qDebug()<<"ccnode can't be update to GraphicsItem";
    Q_ASSERT(0);
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
    m_graphicsItem = new QGraphicsRectItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCLayer::updateGraphicsItem()
{
    QGraphicsRectItem* item = dynamic_cast<QGraphicsRectItem*>(m_graphicsItem);
    item->setRect(0,0,m_width,m_height);
    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(0, -m_height), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
    item->setBrush( QBrush(Qt::NoBrush) );
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
    m_graphicsItem = new QGraphicsRectItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCLayerColor::updateGraphicsItem()
{
    QCCLayer::updateGraphicsItem();
    QGraphicsRectItem* item = dynamic_cast<QGraphicsRectItem*>(m_graphicsItem);
    item->setOpacity( m_opacity/255.0f );
    item->setBrush( QBrush(QColor(m_color)) );
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
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCSprite::updateGraphicsItem()
{
    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
    QPixmap pixmap;
    pixmap = QPixmap(resourceFullPath(m_filePath));
/*
        QSize s = pixmap.size();
        QImage image = QImage(s.width(), s.height(), QImage::Format_RGB32);

        for(int j = 0; j < s.height(); ++j)
        {
            for(int i = 0;i < s.width(); ++i)
            {
                if(i == 0 || i == s.width() -1 || j == 0 || j == s.height() - 1)
                {
                    image.setPixel(i,j,0xFFFFFF);
                }
                else if(i == 1 || i == s.width() -2 || j == 1 || j == s.height() - 2)
                {
                    image.setPixel(i,j,0xFFFFFF);
                }
                else if(i == 2 || i == s.width() -3 || j == 2 || j == s.height() - 3)
                {
                    image.setPixel(i,j,0xFF0000);
                }
                else if(i == 3 || i == s.width() -4 || j == 3 || j == s.height() - 4)
                {
                    image.setPixel(i,j,0xFF0000);
                }
                else
                {
                    image.setPixel(i,j,0x0);
                }
            }
        }

        pixmap = QPixmap::fromImage(image);

    pixmap.fill(QColor(qrand()%255, qrand()%255, qrand()%255));
*/
    item->setPixmap(pixmap);
    QSize s = pixmap.size();
    m_width = s.width();
    m_height = s.height();
    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}


QCCScale9Sprite::QCCScale9Sprite()
{
    m_insetsRect = QRect(0,0,0,0);
    m_preferredSize = QSize(0,0);
}

void QCCScale9Sprite::importData(QMap<QString, QString>& map)
{
    QCCSprite::importData(map);
    int insets_x = map.value("insets_x","0").toInt();
    int insets_y = map.value("insets_y","0").toInt();
    int insets_w = map.value("insets_w","0").toInt();
    int insets_h = map.value("insets_h","0").toInt();
    m_insetsRect = QRect(insets_x, insets_y, insets_w, insets_h);

    int perferred_w = map.value("perferred_w","0").toInt();
    int perferred_h = map.value("perferred_h","0").toInt();
    m_preferredSize = QSize(perferred_w, perferred_h);
}

QMap<QString, QString> QCCScale9Sprite::exportData()
{
    QMap<QString, QString> map = QCCSprite::exportData();
    map.insert("insets_x", QString("%1").arg(m_insetsRect.x()));
    map.insert("insets_y", QString("%1").arg(m_insetsRect.y()));
    map.insert("insets_w", QString("%1").arg(m_insetsRect.width()));
    map.insert("insets_h", QString("%1").arg(m_insetsRect.height()));
    map.insert("perferred_w", QString("%1").arg(m_preferredSize.width()));
    map.insert("perferred_h", QString("%1").arg(m_preferredSize.height()));
    return map;
}

QGraphicsItem* QCCScale9Sprite::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCScale9Sprite::updateGraphicsItem()
{
    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
    QImage image = QImage(resourceFullPath(m_filePath));
    QSize s = image.size();

    int w1 = m_insetsRect.x();
    int h1 = m_insetsRect.y();
    int w2 = m_insetsRect.width();
    int h2 = m_insetsRect.height();
    int w3 = s.width() - w1 - w2;
    int h3 = s.height() - h1 - h2;

    QImage image_1 = image.copy(0,          0,      w1,     h1);
    QImage image_2 = image.copy(w1,         0,      w2,     h1);
    QImage image_3 = image.copy(w1 + w2,    0,      w3,     h1);
    QImage image_4 = image.copy(0,          h1,     w1,     h2);
    QImage image_5 = image.copy(w1,         h1,     w2,     h2);
    QImage image_6 = image.copy(w1 + w2,    h1,     w3,     h2);
    QImage image_7 = image.copy(0,      h1 + h2,    w1,     h3);
    QImage image_8 = image.copy(w1,     h1 + h2,    w2,     h3);
    QImage image_9 = image.copy(w1 + w2,h1 + h2,    w3,     h3);

    QImage imageOut = QImage(m_preferredSize.width(), m_preferredSize.height(), QImage::Format_ARGB32);
    imageOut.fill(0);
    QPainter painter(&imageOut);

    w2 = m_preferredSize.width() - w1 - w3;
    h2 = m_preferredSize.height() - h1 - h3;

    painter.drawImage( QRect(0,          0,      w1,     h1), image_1 );
    painter.drawImage( QRect(w1,         0,      w2,     h1), image_2 );
    painter.drawImage( QRect(w1 + w2,    0,      w3,     h1), image_3 );
    painter.drawImage( QRect(0,          h1,     w1,     h2), image_4 );
    painter.drawImage( QRect(w1,         h1,     w2,     h2), image_5 );
    painter.drawImage( QRect(w1 + w2,    h1,     w3,     h2), image_6 );
    painter.drawImage( QRect(0,      h1 + h2,    w1,     h3), image_7 );
    painter.drawImage( QRect(w1,     h1 + h2,    w2,     h3), image_8 );
    painter.drawImage( QRect(w1 + w2,h1 + h2,    w3,     h3), image_9 );

    item->setPixmap(QPixmap::fromImage(imageOut));

    m_width = m_preferredSize.width();
    m_height = m_preferredSize.height();

    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}

QCCLabelTTF::QCCLabelTTF()
{
    m_text = "CCLabelTTF";
    m_font = QFont();
    m_font.setPointSize(20);
    m_classType = CLASS_TYPE_CCLABELTTF;
    m_horizontalAlignment = kCCHorizontalTextAlignmentCenter;
    m_verticalAlignment = kCCVerticalTextAlignmentCenter;
    m_dimensionWith = 0;
    m_dimensionHeight = 0;
}

void QCCLabelTTF::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    m_text = map.value("text", QString(""));
    //QString family = map.value("fontName", QString("")); //default font
    int pointSize = map.value("pointSize", QString("20")).toInt();
    m_font = QFont();
    m_font.setPointSize(pointSize);

    m_dimensionWith = map.value("dimensionWith", "0").toInt();
    if(m_dimensionWith > 0)
    {
        m_dimensionHeight = map.value("dimensionHeight", "0").toInt();
        m_horizontalAlignment = map.value("horizontalAlignment").toInt();
        m_verticalAlignment = map.value("verticalAlignment").toInt();
    }
}

QMap<QString, QString> QCCLabelTTF::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();
    map.insert("text", m_text);
    //map.insert("fontName", m_font.family());
    map.insert("pointSize", QString("%1").arg(m_font.pointSize()));

    if(m_dimensionWith > 0)
    {
        map.insert("dimensionWith", QString("%1").arg(m_dimensionWith));
        map.insert("dimensionHeight", QString("%1").arg(m_dimensionHeight));
        map.insert("horizontalAlignment",QString("%1").arg(m_horizontalAlignment));
        map.insert("verticalAlignment",QString("%1").arg(m_verticalAlignment));
    }

    return map;
}

QGraphicsItem* QCCLabelTTF::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsTextItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCLabelTTF::updateGraphicsItem()
{
    QGraphicsTextItem* item = dynamic_cast<QGraphicsTextItem*>(m_graphicsItem);
    item->setFont(m_font);
    item->setHtml(m_text);
    item->setDefaultTextColor(QColor(m_color));

    item->setTextWidth(-1);
    QSizeF s = item->boundingRect().size();
    m_width = s.width();
    m_height = s.height();

    int width = m_width;
    if(m_dimensionWith > 0)
    {
        width = m_dimensionWith;
        m_dimensionHeight = m_height;
    }

    item->setTransformOriginPoint(-width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-width/2, -m_height/2), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);

    if(m_dimensionWith != 0)
    {
        item->setTextWidth(m_dimensionWith);
        QTextBlockFormat format;
        int alignArray[3] = {Qt::AlignLeft,Qt::AlignCenter,Qt::AlignRight};
        format.setAlignment((Qt::AlignmentFlag)(alignArray[m_horizontalAlignment]));
        QTextCursor cursor = item->textCursor();
        cursor.select(QTextCursor::Document);
        cursor.mergeBlockFormat(format);
        cursor.clearSelection();
        item->setTextCursor(cursor);
    }
    else
    {
        item->setTextWidth(-1);
    }
}


QCCLabelAtlas::QCCLabelAtlas()
{
    m_text = "0123456789";
    m_elementWidth = 0;
    m_elementHeight = 0;
    m_startChar = '0';
}

void QCCLabelAtlas::importData(QMap<QString, QString>& map)
{
    QCCSprite::importData(map);
    m_elementWidth = map.value("elementWidth", QString("0")).toInt();
    m_elementHeight = map.value("elementHeight", QString("0")).toInt();
    m_startChar = map.value("startChar", QString("0x30")).toInt();
    m_text = map.value("text", QString(""));
}

QMap<QString, QString> QCCLabelAtlas::exportData()
{
    QMap<QString, QString> map = QCCSprite::exportData();
    map.insert("elementWidth", QString("%1").arg(m_elementWidth));
    map.insert("elementHeight", QString("%1").arg(m_elementHeight));
    map.insert("startChar", QString("%1").arg(m_startChar));
    map.insert("text", m_text);
    return map;
}

QGraphicsItem* QCCLabelAtlas::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCLabelAtlas::updateGraphicsItem()
{

    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
    QImage image = QImage(resourceFullPath(m_filePath));
    QSize s = image.size();

    int charCount = m_text.count();
    if(charCount > 0)
    {
        QImage imageOut = QImage(m_elementWidth*charCount, m_elementHeight, QImage::Format_ARGB32);
        imageOut.fill(0);
        QPainter painter(&imageOut);
        int m_elementCountPerWidth = s.width()/m_elementWidth;
        int m_elementCountPerHeight = s.height()/m_elementHeight;

        for(int i = 0; i < charCount; ++i)
        {
            char c = m_text.at(i).toLatin1();
            int index = c - m_startChar;
            if(index < 0 || index >= m_elementCountPerWidth*m_elementCountPerHeight)
            {
                index = 0;
            }

            int rowIndex = index/m_elementCountPerWidth;
            int colIndex = index%m_elementCountPerWidth;

            QRect r = QRect(colIndex*m_elementWidth, rowIndex*m_elementCountPerHeight, m_elementWidth, m_elementHeight);
            QImage imageCopy = image.copy(r);
            painter.drawImage( QRect(i*m_elementWidth,0,m_elementWidth,m_elementHeight), imageCopy );
        }

        item->setPixmap(QPixmap::fromImage(imageOut));
    }

    m_width = m_elementWidth*charCount;
    m_height = m_elementHeight;

    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);

    m_width = s.width();
    m_height = s.height();
}


QCCMenuItemImage::QCCMenuItemImage()
{
}

void QCCMenuItemImage::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    m_filePath = map.value("image_n", QString(""));
}

QMap<QString, QString> QCCMenuItemImage::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();
    map.insert("image_n", m_filePath);
    return map;
}

QGraphicsItem* QCCMenuItemImage::createGraphicsItem()
{
    return QCCSprite::createGraphicsItem();
}

void QCCMenuItemImage::updateGraphicsItem()
{
    return QCCSprite::updateGraphicsItem();
}

QCCProgressTimer::QCCProgressTimer()
{
    m_progressTimerType = kCCProgressTimerTypeBar;
    m_direction = 0;//0.从左到右 1.从右到左 2.从下到上 3.从上到下
    m_percentage = 1.0;
}

void QCCProgressTimer::importData(QMap<QString, QString>& map)
{
    QCCSprite::importData(map);
    m_progressTimerType = map.value("progressTimerType","1").toInt();
    m_direction = map.value("direction","0").toInt();
    m_percentage = map.value("percentage","0.5").toFloat();
}

QMap<QString, QString> QCCProgressTimer::exportData()
{
    QMap<QString, QString> map = QCCSprite::exportData();
    map.insert("progressTimerType", QString("%1").arg(m_progressTimerType));
    map.insert("direction", QString("%1").arg(m_direction));
    map.insert("percentage", QString("%1").arg(m_percentage));
    return map;
}

QGraphicsItem* QCCProgressTimer::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCProgressTimer::updateGraphicsItem()
{
    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
    QImage image = QImage(resourceFullPath(m_filePath));
    QSize s = image.size();

    if (m_progressTimerType == kCCProgressTimerTypeRadial)
    {}
    else if(m_progressTimerType == kCCProgressTimerTypeBar)
    {
        QRect r;
        if(m_direction == 0)
        {
            r = QRect(0, 0, s.width()*m_percentage, s.height());
        }
        else if(m_direction == 1)
        {
            r = QRect(s.width()*(1 - m_percentage), 0, s.width()*m_percentage, s.height());
        }
        else if(m_direction == 2)
        {
            r = QRect(0, s.height()*(1 - m_percentage), s.width(), s.height()*m_percentage);
        }
        else if(m_direction == 3)
        {
            r = QRect(0, 0, s.width(), s.height()*m_percentage);
        }

        QImage image_1 = image.copy( r );
        QImage imageOut = QImage(s.width(), s.height(), QImage::Format_ARGB32);
        imageOut.fill(0);
        QPainter painter(&imageOut);
        painter.drawImage( r, image_1 );
        item->setPixmap(QPixmap::fromImage(imageOut));
    }

    m_width = s.width();
    m_height = s.height();

    item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(-m_width/2, -m_height/2), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
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
    scene.render(&painter);
    //image.save(QString("%1.png").arg(fullPath), "png");

    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
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

    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}
