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
#include <QSplitter>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QListView>
#include <QTableView>
#include <QUrl>
#include <QMimeData>

//1.add string manager
//2.add lua fire browser.
//3.add pic use refrance count.
//4.support plist switch.


const char CLASS_TYPE_CCNODE[] = "CCNode";
const char CLASS_TYPE_CCLAYER[] = "CCLayer";
const char CLASS_TYPE_CCLAYERCOLOR[] = "CCLayerColor";
const char CLASS_TYPE_CCSPRITE[] = "CCSprite";
const char CLASS_TYPE_CCSCALE9SPRITE[] = "CCScale9Sprite";
const char CLASS_TYPE_CCLABELTTF[] = "CCLabelTTF";
const char CLASS_TYPE_CCLABELATLAS[] = "CCLabelAtlas";
const char CLASS_TYPE_CCPROGRESSTIMER[] = "CCProgressTimer";
const char CLASS_TYPE_CCMENUITEM_IMAGE[] = "CCMenuItemImage";
const char CLASS_TYPE_CCCONTAINERLAYER[] = "CCContainerLayer";
const char CLASS_TYPE_CCSCROLLVIEW[] = "CCScrollView";

const char FILTER_IMAGES[] = "Images (*.png *.jpg)";
const char FILTER_CONFIG[] = "Config (*.lua)";

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

typedef enum {
    kCCScrollViewDirectionNone = -1,
    kCCScrollViewDirectionHorizontal = 0,
    kCCScrollViewDirectionVertical,
    kCCScrollViewDirectionBoth
} CCScrollViewDirection;

#endif // QDEFINE_H
