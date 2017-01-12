#include "qccnode.h"
#include "qcclayer.h"
#include "qcclayercolor.h"
#include "qccsprite.h"
#include "qccprogresstimer.h"
#include "qccscale9sprite.h"
#include "qcccontainerlayer.h"
#include "qccmenuitemimage.h"
#include "qcclabelatlas.h"
#include "qcclabelttf.h"
#include "qccscrollview.h"
#include "qccuibutton.h"

#include <QImage>
#include <QPainter>

static QMap<QString, QString> g_pathMap; //路径映射，短路径到长路径
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
    else if(type == CLASS_TYPE_CCSCROLLVIEW)
    {
        node = new QCCScrollView();
    }
    else if(type == CLASS_TYPE_CCUIBUTTON)
    {
        node = new QCCUiButton();
    }

    Q_ASSERT(node != 0);
    static int count = 1;
    node->m_name = QString("node_%1").arg(count);
    node->m_z = count++;
    node->m_classType = type;
    return node;
}

void QCCNode::createPathMap()
{
    g_pathMap.clear();
    QSettings settings("UIDesigner");
    QString prefix = settings.value("resourceDir",QString("")).toString();
    QString resDir = QString("%1/").arg(prefix);
    QCCNode::traverseFiles(prefix, resDir);
}

void QCCNode::traverseFiles(QString filePath, QString relationPath)
{
    QDir dir(filePath);
    dir.setFilter(QDir::Dirs);
    dir.setSorting(QDir::Name);

    QFileInfoList fileInfoList = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);

    if(fileInfoList.isEmpty() == false)
    {
        foreach(QFileInfo fileInfo, fileInfoList)
        {
            if(fileInfo.isDir())
            {
                QCCNode::traverseFiles(fileInfo.absoluteFilePath(), relationPath);
            }
            else if(fileInfo.isFile())
            {
                QString absFilePath = fileInfo.absoluteFilePath();
                QString shortPath = absFilePath.split("/").last();

                if(absFilePath.contains("/res/pic/") || absFilePath.contains("/res/text/") )
                {
                    QString test = g_pathMap.value(shortPath, "");
                    if (test.isEmpty() == true)
                    {
                        g_pathMap.insert(shortPath, absFilePath.remove(relationPath));
                    }
                    else
                    {
                        qDebug()<<absFilePath.remove(relationPath);
                        qDebug()<<test;
                    }
                }
            }
        }
    }
}

QString QCCNode::longPathToShortPath(QString longPath)
{
    QStringList list = longPath.split("/");
    return list.last();
}

QString QCCNode::shortPathToLongPath(QString shortPath)
{
    QString path = g_pathMap.value(shortPath, "");
    return path;
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
    m_tag = 0;
    m_width = 0;
    m_height = 0;
    m_rotation = 0;
    m_anchorX = 0.0f;
    m_anchorY = 0.0f;
    m_scaleX = 1.0f;
    m_scaleY = 1.0f;
    m_isVisible = true;
    m_isSkipCreate = false;
    m_isSkipInit = false;
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
    m_name = map.value("name", QString(CLASS_TYPE_NONE));
    m_classType = map.value("classType", QString("%1").arg(CLASS_TYPE_NONE));
    m_x = map.value("x", QString("0")).toInt();
    m_y = map.value("y", QString("0")).toInt();
    m_z = map.value("z", QString("0")).toInt();
    m_tag = map.value("tag", QString("0")).toInt();
    m_width = map.value("width", QString("0")).toInt();
    m_height = map.value("height", QString("0")).toInt();
    m_rotation = map.value("rotation", QString("0")).toInt();
    m_anchorX = map.value("anchorX", QString("0.5")).toFloat();
    m_anchorY = map.value("anchorY", QString("0.5")).toFloat();
    m_scaleX = map.value("scaleX", QString("1.0")).toFloat();
    m_scaleY = map.value("scaleY", QString("1.0")).toFloat();
    m_isVisible = map.value("visible", QString("1")).toInt();
    m_isSkipCreate = map.value("skipCreate", QString("0")).toInt();
    m_isSkipInit = map.value("skipInit", QString("0")).toInt();
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

    if(m_tag != 0)
    {
        map.insert("tag", QString("%1").arg(m_tag));
    }

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

    if(m_scaleX < 0.99 || m_scaleX > 1.01)
    {
        map.insert("scaleX", QString("%1").arg(m_scaleX));
    }

    if(m_scaleY < 0.99 || m_scaleY > 1.01)
    {
        map.insert("scaleY", QString("%1").arg(m_scaleY));
    }

    if(m_isVisible == false)
    {
        map.insert("visible", "0");
    }

    if(m_isSkipCreate == true)
    {
        map.insert("skipCreate", "1");
    }

    if(m_isSkipInit == true)
    {
        map.insert("skipInit", "1");
    }

    return map;
}

QGraphicsItem* QCCNode::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsRectItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCNode::updateGraphicsItem()
{
    QGraphicsRectItem* item = dynamic_cast<QGraphicsRectItem*>(m_graphicsItem);
    item->setRect(0,0,1,1);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    //item->setTransform(QTransform::fromTranslate(0, -m_height), true);
    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
    item->setBrush( QBrush(Qt::NoBrush) );
}

