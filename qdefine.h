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

#define CLASS_TYPE_ROOT     "class"

#define CLASS_TYPE_CCNODE       "CCNode"
#define CLASS_TYPE_CCLAYER      "CCLayer"
#define CLASS_TYPE_CCLAYERCOLOR "CCLayerColor"
#define CLASS_TYPE_CCSPRITE     "CCSprite"
#define CLASS_TYPE_CCLABELTTF   "CCLabelTTF"

#endif // QDEFINE_H
