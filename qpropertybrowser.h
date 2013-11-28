#ifndef QPROPERTYBROWSER_H
#define QPROPERTYBROWSER_H

#include "variantmanager.h"
#include "variantfactory.h"
#include "qttreepropertybrowser.h"
#include "qccnode.h"

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
    void changePropertyTouchEnable(bool touchEnable);
    void changePropertyColor(QColor& color);
    void changePropertyOpacity(int opacity);
    void changePropertyFilePath(QString& filePath);
    void changePropertyFont(QFont& font);
    void changePropertyText(QString& text);
    void changePropertyAlignment(int horizontal, int vertical);
    void changePropertyTextDimension(int width, int height);
    void changePropertyCCContainerLayerFilePath(QString& filePath);

public slots:
    void valueChanged(QtProperty*,QVariant);
    void changedPropertyPoint(int x, int y);
    void changedPropertySize(int width, int height);

private:
    void initPropertyCCNode(QCCNode* node);
    void initPropertyCCLayer(QCCLayer* node);
    void initPropertyCCLayerColor(QCCLayerColor* node);
    void initPropertyCCSprite(QCCSprite* node);
    void initPropertyCCLabelTTF(QCCLabelTTF* node);
    void initPropertyCCContainerLayer(QCCContainerLayer *node);

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

//-- 2 level
    void createPropertyPoint();
    void createPropertySize();
    void createPropertyAnchor();
    void createPropertyScale();
    void createPropertyDimensionSize();
    void createPropertyTextAlignment();

//-- 3 level
    void createPropertyCCNode();
    void createPropertyCCLayer();
    void createPropertyCCLayerColor();
    void createPropertyCCSprite();
    void createPropertyCCLabelTTF();
    void createPropertyCCContainerLayer();

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

//-- 2 level
    QtVariantProperty*  m_point;
    QtVariantProperty*  m_size;
    QtVariantProperty*  m_anchor;
    QtVariantProperty*  m_scale;
    QtVariantProperty*  m_dimensionSize;
    QtVariantProperty*  m_textAlignment;

//-- 3 level
    QtVariantProperty*  m_ccNode;
    QtVariantProperty*  m_ccLayer;
    QtVariantProperty*  m_ccLayerColor;
    QtVariantProperty*  m_ccSprite;
    QtVariantProperty*  m_ccLabelTTF;
    QtVariantProperty*  m_ccContainerLayer;

private:
    QtVariantPropertyManager*   m_manager;
    QtVariantEditorFactory *    m_factory;
};

#endif // QPROPERTYBROWSER_H
