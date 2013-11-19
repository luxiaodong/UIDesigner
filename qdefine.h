#ifndef QDEFINE_H
#define QDEFINE_H

//主要设计思想是
//创建一个当前选择的记录项 select_item;
//tree scene property 互相独立
//mainWindow掌管tree scene property, 当作桥梁
//tree --> select_item
//scene --> select_item
//property --> select_item
//select_item --> tree scene property
//data --> tree
//data --> scene
//先制定存储的数据格式标准，实现底层的数据导入导出
//再支持treeView的选中，增加，删除，拷贝等操作
//再将treeView的操作消息影响到scene
//scene接受到后作出改变，再反过来影响treeView
//add a GraphicsItem that can load xml as child.
//最后实现property的控制
//color may be use colorIndex.

#include <QList>
#include <QVector>
#include <QMap>
#include <QString>
#include <QVariant>
#include <QString>
#include <QColor>
#include <QBrush>
#include <QFont>
#include <QAbstractItemModel>
#include <QStringList>
#include <QVariant>
#include <QDebug>
#include <QHBoxLayout>
#include <QTreeView>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QSettings>
#include <QGraphicsPixmapItem>
#include <QGraphicsSimpleTextItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QXmlStreamAttributes>

#define CLASS_TYPE_ROOT     "class"

#define CLASS_TYPE_CCNODE       "CCNode"
#define CLASS_TYPE_CCLAYER      "CCLayer"
#define CLASS_TYPE_CCLAYERCOLOR "CCLayerColor"
#define CLASS_TYPE_CCSPRITE     "CCSprite"
#define CLASS_TYPE_CCLABELTTF   "CCLabelTTF"
#define CLASS_TYPE_CCCONTAINERLAYER  "CCContainerLayer"


typedef enum
{
    kCCVerticalTextAlignmentTop,
    kCCVerticalTextAlignmentCenter,
    kCCVerticalTextAlignmentBottom
} CCVerticalTextAlignment;

typedef enum
{
    kCCHorizontalTextAlignmentLeft,
    kCCHorizontalTextAlignmentCenter,
    kCCHorizontalTextAlignmentRight
} CCHorizontalTextAlignment;

#endif // QDEFINE_H
