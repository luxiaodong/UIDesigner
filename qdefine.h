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
#include <QFontMetrics>
#include <QProcess>

//1.add string manager
//2.add lua file browser.
//3.add pic use refrance count.
//4.support plist switch.

const char CLASS_TYPE_NONE[] = "";
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
const char CLASS_TYPE_CCUIBUTTON[] = "CCUIButton";

const char PROPERTY_TYPE_NAME[] = "name";
const char PROPERTY_TYPE_FIXED[] = "fixed";
const char PROPERTY_TYPE_X[] = "x";
const char PROPERTY_TYPE_Y[] = "y";
const char PROPERTY_TYPE_Z[] = "z";
const char PROPERTY_TYPE_TAG[] = "tag";
const char PROPERTY_TYPE_WIDTH[] = "width";
const char PROPERTY_TYPE_HEIGHT[] = "height";
const char PROPERTY_TYPE_ANCHORX[] = "anchorX";
const char PROPERTY_TYPE_ANCHORY[] = "anchorY";
const char PROPERTY_TYPE_SCALEX[] = "scaleX";
const char PROPERTY_TYPE_SCALEY[] = "scaleY";
const char PROPERTY_TYPE_ROTATION[] = "rotation";
const char PROPERTY_TYPE_VISIBLE[] = "visible";
const char PROPERTY_TYPE_SKIPCREATE[] = "skipCreate";
const char PROPERTY_TYPE_SKIPINIT[] = "skipInit";
const char PROPERTY_TYPE_TOUCHENABLE[] = "touchEnable";
const char PROPERTY_TYPE_COLOR[] = "color";
const char PROPERTY_TYPE_OPACITY[] = "opacity";
const char PROPERTY_TYPE_IMAGE[] = "image";
const char PROPERTY_TYPE_FONT[] = "font";
const char PROPERTY_TYPE_TEXT[] = "text";
const char PROPERTY_TYPE_TEXT_HORIZONTAL[] = "horizontal";
const char PROPERTY_TYPE_TEXT_VERTICAL[] = "vertical";
const char PROPERTY_TYPE_TEXT_ALIGNMENT_CENTER[] = "Center";
const char PROPERTY_TYPE_TEXT_ALIGNMENT_LEFT[] = "Left";
const char PROPERTY_TYPE_TEXT_ALIGNMENT_RIGHT[] = "Right";
const char PROPERTY_TYPE_TEXT_ALIGNMENT_TOP[] = "Top";
const char PROPERTY_TYPE_TEXT_ALIGNMENT_BOTTOM[] = "Bottom";
const char PROPERTY_TYPE_TEXT_STRIKE_SIZE[] = "strikeSize";
const char PROPERTY_TYPE_TEXT_STRIKE_COLOR[] = "strikeColor";
const char PROPERTY_TYPE_BAR_PERCENT[] = "percent";
const char PROPERTY_TYPE_CONTAINER_FILEPATH[] = "filePath";

const char PROPERTY_TYPE_POSITION[] = "position";
const char PROPERTY_TYPE_SIZE[] = "size";
const char PROPERTY_TYPE_ANCHOR[] = "anchor";
const char PROPERTY_TYPE_SCALE[] = "scale";
const char PROPERTY_TYPE_DIMENSION[] = "dimension";
const char PROPERTY_TYPE_TEXT_ALIGNMENT[] = "textAlignment";
const char PROPERTY_TYPE_TEXT_STRIKE[] = "textStrike";

const char PROPERTY_TYPE_INSETSRECT[] = "insetsRect";
const char PROPERTY_TYPE_PREFERREDSIZE[] = "preferredSize";
const char PROPERTY_TYPE_OFFSET[] = "offset";
const char PROPERTY_TYPE_SPACE[] = "space";
const char PROPERTY_TYPE_CONTENT[] = "content";

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
