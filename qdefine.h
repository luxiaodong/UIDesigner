#ifndef QDEFINE_H
#define QDEFINE_H

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
#include <QGraphicsTextItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QRegExp>
#include <QTextStream>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QXmlStreamAttributes>
#include <QTextBlockFormat>
#include <QTextCursor>
#include <QActionGroup>
#include <QCloseEvent>

//1.add string manager
//2.add lua fire browser.
//3.add pic use refrance count.
//4.support plist switch.

#define CLASS_TYPE_CCNODE       "CCNode"
#define CLASS_TYPE_CCLAYER      "CCLayer"
#define CLASS_TYPE_CCLAYERCOLOR "CCLayerColor"
#define CLASS_TYPE_CCSPRITE     "CCSprite"
#define CLASS_TYPE_CCSCALE9SPRITE "CCScale9Sprite"
#define CLASS_TYPE_CCLABELTTF   "CCLabelTTF"
#define CLASS_TYPE_CCPROGRESSTIMER  "CCProgressTimer"
#define CLASS_TYPE_CCMENUITEM_IMAGE "CCMenuItemImage"
#define CLASS_TYPE_CCCONTAINERLAYER  "CCContainerLayer"

#define FILTER_IMAGES "Images (*.png *.jpg)"
#define FILTER_CONFIG "Config (*.lua)"

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

typedef enum {
    /// Radial Counter-Clockwise
    kCCProgressTimerTypeRadial,
    kCCProgressTimerTypeBar
} CCProgressTimerType;

#endif // QDEFINE_H
