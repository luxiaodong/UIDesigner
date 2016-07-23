#ifndef QPROPERTYBROWSER_H
#define QPROPERTYBROWSER_H

#include "variantmanager.h"
#include "variantfactory.h"
#include "qttreepropertybrowser.h"

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

class QPropertyBrowser : public QtTreePropertyBrowser
{
    Q_OBJECT

public:
    QPropertyBrowser();

public:
    void test();
    void initProperty(QCCNode* node);

signals:
    void changePropertyFixed(bool fixed);
    void changePropertyPoint(int x, int y);
    void changePropertyZ(int z);
    void changePropertyTag(int tag);
    void changePropertySize(int width, int height);
    void changePropertyAnchor(float anchorX, float anchorY);
    void changePropertyScale(float scaleX, float scaleY);
    void changePropertyRotation(int rotation);
    void changePropertyVisible(bool visible);
    void changePropertySkipCreate(bool skip);
    void changePropertyTouchEnable(bool touchEnable);
    void changePropertyColor(QColor& color);
    void changePropertyOpacity(int opacity);
    void changePropertyFilePath(QString& filePath);
    void changePropertyFont(QFont& font);
    void changePropertyText(QString& text);
    void changePropertyAlignment(int horizontal, int vertical);
    void changePropertyTextDimension(int width, int height);
    void changePropertyCCContainerLayerFilePath(QString& filePath);
    void changePropertyInsetsRect(QRect);
    void changePropertyPreferedSize(QSize);
    void changePropertyProgressTimerType(int);
    void changePropertyDirection(int);
    void changePropertyPercentage(float);
    void changePropertyAtlasElementSize(int width, int height);
    void changePropertyAtlasStartChar(int);
    void changePropertyAtlasText(QString& text);
    void changePropertyScrollViewDirection(int);
    void changePropertyScrollViewCount(int);
    void changePropertyScrollViewOffset(int,int);
    void changePropertyScrollViewSpace(int,int);
    void changePropertyScrollViewContent(int,int);
    void changePropertyDynamicallyGenerated(bool);

public slots:
    void valueChanged(QtProperty*,QVariant);
    void changedPropertyPoint(int x, int y);
    void changedPropertySize(int w, int h);
    void changedPropertyTextDimension(int w, int h);

private:
    void initPropertyCCNode(QCCNode* node);
    void initPropertyCCLayer(QCCLayer* node);
    void initPropertyCCLayerColor(QCCLayerColor* node);
    void initPropertyCCSprite(QCCSprite* node);
    void initPropertyCCLabelTTF(QCCLabelTTF* node);
    void initPropertyCCContainerLayer(QCCContainerLayer *node);
    void initPropertyCCScale9Sprite(QCCScale9Sprite *node);
    void initPropertyCCProgressTimer(QCCProgressTimer *node);
    void initPropertyCCLabelAtlas(QCCLabelAtlas* node);
    void initPropertyCCScrollView(QCCScrollView* node);

private:
    void createProperty();

private:
//-- 1 level
    void createPropertyFixed();
    void createPropertyX();
    void createPropertyY();
    void createPropertyZ();
    void createPropertyTag();
    void createPropertyWidth();
    void createPropertyHeight();
    void createPropertyAnchorX();
    void createPropertyAnchorY();
    void createPropertyScaleX();
    void createPropertyScaleY();
    void createPropertyRotation();
    void createPropertyVisible();
    void createPropertySkipCreate();
    void createPropertyTouchEnable();
    void createPropertyColor();
    void createPropertyOpacity();
    void createPropertyFilePath();
    void createPropertyFont();
    void createPropertyText();
    void createPropertyHorizontalAlignment();
    void createPropertyVerticalAlignment();
    void createPropertyDimensionWith();
    void createPropertyDimensionHeight();
    void createPropertyContainerFilePath();
    void createPropertyInsetsX();
    void createPropertyInsetsY();
    void createPropertyInsetsWidth();
    void createPropertyInsetsHeight();
    void createPropertyPreferedWidth();
    void createPropertyPreferedHeight();
    void createPropertyProgressTimerType();
    void createPropertyDirection();
    void createPropertyPercentage();
    void createPropertyAtlasElementWidth();
    void createPropertyAtlasElementHeight();
    void createPropertyAtlasStartChar();
    void createPropertyAtlasText();
    void createPropertyScrollViewDirection();
    void createPropertyScrollViewCount();
    void createPropertyScrollViewOffsetX();
    void createPropertyScrollViewOffsetY();
    void createPropertyScrollViewSpaceWidth();
    void createPropertyScrollViewSpaceHeight();
    void createPropertyScrollViewContentWidth();
    void createPropertyScrollViewContentHeight();
    void createPropertyScrollViewIsDynamicallyGenerated();

//-- 2 level
    void createPropertyPoint();
    void createPropertySize();
    void createPropertyAnchor();
    void createPropertyScale();
    void createPropertyDimensionSize();
    void createPropertyTextAlignment();
    void createPropertyInsetsRect();
    void createPropertyPreferredSize();
    void createPropertyScrollViewOffset();
    void createPropertyScrollViewSpace();
    void createPropertyScrollViewContent();

//-- 3 level
    void createPropertyCCNode();
    void createPropertyCCLayer();
    void createPropertyCCLayerColor();
    void createPropertyCCSprite();
    void createPropertyCCLabelTTF();
    void createPropertyCCContainerLayer();
    void createPropertyCCScale9Sprite();
    void createPropertyCCProgressTimer();
    void createPropertyCCLabelAtlas();
    void createPropertyCCScrollView();

private:
//-- 1 level
    QtVariantProperty*  m_fixed;
    QtVariantProperty*  m_x;
    QtVariantProperty*  m_y;
    QtVariantProperty*  m_z;
    QtVariantProperty*  m_tag;
    QtVariantProperty*  m_width;
    QtVariantProperty*  m_height;
    QtVariantProperty*  m_anchorX;
    QtVariantProperty*  m_anchorY;
    QtVariantProperty*  m_scaleX;
    QtVariantProperty*  m_scaleY;
    QtVariantProperty*  m_rotation;
    QtVariantProperty*  m_visible;
    QtVariantProperty*  m_skipCreate;
    QtVariantProperty*  m_touchEnable;
    QtVariantProperty*  m_color;
    QtVariantProperty*  m_opacity;
    QtVariantProperty*  m_filePath;
    QtVariantProperty*  m_font;
    QtVariantProperty*  m_text;
    QtVariantProperty*  m_horizontalAlignment;
    QtVariantProperty*  m_verticalAlignment;
    QtVariantProperty*  m_dimensionWith;
    QtVariantProperty*  m_dimensionHeight;
    QtVariantProperty*  m_containerLayerFilePath;
    QtVariantProperty*  m_insetsX;
    QtVariantProperty*  m_insetsY;
    QtVariantProperty*  m_insetsWidth;
    QtVariantProperty*  m_insetsHeight;
    QtVariantProperty*  m_preferredWidth;
    QtVariantProperty*  m_preferredHeight;
    QtVariantProperty*  m_progressTimerType;
    QtVariantProperty*  m_direction;
    QtVariantProperty*  m_percentage;
    QtVariantProperty*  m_atlasElementWidth;
    QtVariantProperty*  m_atlasElementHeight;
    QtVariantProperty*  m_atlasStartChar;
    QtVariantProperty*  m_atlasText;
    QtVariantProperty*  m_scrollViewDirection;
    QtVariantProperty*  m_scrollViewCount;
    QtVariantProperty*  m_scrollViewOffsetX;
    QtVariantProperty*  m_scrollViewOffsetY;
    QtVariantProperty*  m_scrollViewSpaceWidth;
    QtVariantProperty*  m_scrollViewSpaceHeight;
    QtVariantProperty*  m_scrollViewContentWidth;
    QtVariantProperty*  m_scrollViewContentHeight;
    QtVariantProperty*  m_scrollViewIsDynamicallyGenerated;

//-- 2 level
    QtVariantProperty*  m_point;
    QtVariantProperty*  m_size;
    QtVariantProperty*  m_anchor;
    QtVariantProperty*  m_scale;
    QtVariantProperty*  m_dimensionSize;
    QtVariantProperty*  m_textAlignment;
    QtVariantProperty*  m_insetsRect;
    QtVariantProperty*  m_preferredSize;
    QtVariantProperty*  m_scrollViewOffset;
    QtVariantProperty*  m_scrollViewSpace;
    QtVariantProperty*  m_scrollViewContent;

//-- 3 level
    QtVariantProperty*  m_ccNode;
    QtVariantProperty*  m_ccLayer;
    QtVariantProperty*  m_ccLayerColor;
    QtVariantProperty*  m_ccSprite;
    QtVariantProperty*  m_ccLabelTTF;
    QtVariantProperty*  m_ccContainerLayer;
    QtVariantProperty*  m_ccScale9Sprite;
    QtVariantProperty*  m_ccProgressTimer;
    QtVariantProperty*  m_ccLabelAtlas;
    QtVariantProperty*  m_ccScrollView;

private:
    QtVariantPropertyManager*   m_manager;
    QtVariantEditorFactory *    m_factory;
};

#endif // QPROPERTYBROWSER_H
