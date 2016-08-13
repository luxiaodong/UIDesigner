#include "qpropertybrowser.h"
#include "qstoragedata.h"

QPropertyBrowser::QPropertyBrowser()
{
    m_manager = new VariantManager();
    m_factory = new VariantFactory();
    this->setFactoryForManager(m_manager, m_factory);
    this->createProperty();
    connect(m_manager, SIGNAL(valueChanged(QtProperty*,QVariant)), this, SLOT(valueChanged(QtProperty*,QVariant)));
}

void QPropertyBrowser::createProperty()
{
    //-- 1 level
    createPropertyFixed();
    createPropertyX();
    createPropertyY();
    createPropertyZ();
    createPropertyTag();
    createPropertyWidth();
    createPropertyHeight();
    createPropertyAnchorX();
    createPropertyAnchorY();
    createPropertyScaleX();
    createPropertyScaleY();
    createPropertyRotation();
    createPropertyVisible();
    createPropertySkipCreate();
    createPropertySkipInit();
    createPropertyTouchEnable();
    createPropertyColor();
    createPropertyOpacity();
    createPropertyFilePath();
    createPropertyFont();
    createPropertyText();
    createPropertyHorizontalAlignment();
    createPropertyVerticalAlignment();
    createPropertyDimensionWith();
    createPropertyDimensionHeight();
    createPropertyTextStrikeSize();
    createPropertyTextStrikeColor();
    createPropertyContainerFilePath();
    createPropertyInsetsX();
    createPropertyInsetsY();
    createPropertyInsetsWidth();
    createPropertyInsetsHeight();
    createPropertyPreferedWidth();
    createPropertyPreferedHeight();
    createPropertyProgressTimerType();
    createPropertyDirection();
    createPropertyPercentage();
    createPropertyAtlasElementWidth();
    createPropertyAtlasElementHeight();
    createPropertyAtlasStartChar();
    createPropertyAtlasText();
    createPropertyScrollViewDirection();
    createPropertyScrollViewCount();
    createPropertyScrollViewOffsetX();
    createPropertyScrollViewOffsetY();
    createPropertyScrollViewSpaceWidth();
    createPropertyScrollViewSpaceHeight();
    createPropertyScrollViewContentWidth();
    createPropertyScrollViewContentHeight();
    createPropertyScrollViewIsDynamicallyGenerated();

    //-- 2 level
    createPropertyPoint();
    createPropertySize();
    createPropertyAnchor();
    createPropertyScale();
    createPropertyTextAlignment();
    createPropertyDimensionSize();
    createPropertyTextStrike();
    createPropertyInsetsRect();
    createPropertyPreferredSize();
    createPropertyScrollViewOffset();
    createPropertyScrollViewSpace();
    createPropertyScrollViewContent();

    //-- 3 level
    createPropertyCCNode();
    createPropertyCCLayer();
    createPropertyCCLayerColor();
    createPropertyCCSprite();
    createPropertyCCLabelTTF();
    createPropertyCCContainerLayer();
    createPropertyCCScale9Sprite();
    createPropertyCCProgressTimer();
    createPropertyCCLabelAtlas();
    createPropertyCCScrollView();
}

void QPropertyBrowser::createPropertyFixed()
{
    m_fixed = m_manager->addProperty(QVariant::Bool, PROPERTY_TYPE_FIXED);
    m_fixed->setValue(false);
}

//-- 1 level
void QPropertyBrowser::createPropertyX()
{
    m_x = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_X);
    m_x->setAttribute("minimum",-9999);
    m_x->setAttribute("maximum",9999);
    m_x->setValue(0);
}

void QPropertyBrowser::createPropertyY()
{
    m_y = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_Y);
    m_y->setAttribute("minimum",-9999);
    m_y->setAttribute("maximum",9999);
    m_y->setValue(0);
}

void QPropertyBrowser::createPropertyZ()
{
    m_z = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_Z);
    m_z->setAttribute("minimum",-9999);
    m_z->setAttribute("maximum",9999);
    m_z->setValue(0);
}

void QPropertyBrowser::createPropertyTag()
{
    m_tag = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_TAG);
    m_tag->setAttribute("minimum",-1);
    m_tag->setAttribute("maximum",9999999);
    m_tag->setValue(-1);
}

void QPropertyBrowser::createPropertyWidth()
{
    m_width = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_WIDTH);
    m_width->setAttribute("minimum",0);
    m_width->setAttribute("maximum",9999);
    m_width->setValue(0);
}

void QPropertyBrowser::createPropertyHeight()
{
    m_height = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_HEIGHT);
    m_height->setAttribute("minimum",0);
    m_height->setAttribute("maximum",9999);
    m_height->setValue(0);
}

void QPropertyBrowser::createPropertyAnchorX()
{
    m_anchorX = m_manager->addProperty(QVariant::Double, PROPERTY_TYPE_ANCHORX);
    m_anchorX->setAttribute("minimum", 0.0f);
    m_anchorX->setAttribute("maximum", 1.0f);
    m_anchorX->setAttribute("singleStep", 0.01f);
    m_anchorX->setValue(1.0f);
}

void QPropertyBrowser::createPropertyAnchorY()
{
    m_anchorY = m_manager->addProperty(QVariant::Double, PROPERTY_TYPE_ANCHORY);
    m_anchorY->setAttribute("minimum", 0.0f);
    m_anchorY->setAttribute("maximum", 1.0f);
    m_anchorY->setAttribute("singleStep", 0.01f);
    m_anchorY->setValue(1.0f);
}

void QPropertyBrowser::createPropertyScaleX()
{
    m_scaleX = m_manager->addProperty(QVariant::Double, PROPERTY_TYPE_SCALEX);
    m_scaleX->setAttribute("minimum", -1000.0f);
    m_scaleX->setAttribute("maximum", 1000.0f);
    m_scaleX->setAttribute("singleStep", 0.01f);
    m_scaleX->setValue(1.0f);
}

void QPropertyBrowser::createPropertyScaleY()
{
    m_scaleY = m_manager->addProperty(QVariant::Double, PROPERTY_TYPE_SCALEY);
    m_scaleY->setAttribute("minimum", -1000.0f);
    m_scaleY->setAttribute("maximum", 1000.0f);
    m_scaleY->setAttribute("singleStep", 0.01f);
    m_scaleY->setValue(1.0f);
}

void QPropertyBrowser::createPropertyRotation()
{
    m_rotation = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_ROTATION);
    m_rotation->setAttribute("minimum",0);
    m_rotation->setAttribute("maximum",360);
    m_rotation->setValue(0);
}

void QPropertyBrowser::createPropertyVisible()
{
    m_visible = m_manager->addProperty(QVariant::Bool, PROPERTY_TYPE_VISIBLE);
    m_visible->setValue(true);
}

void QPropertyBrowser::createPropertySkipCreate()
{
    m_skipCreate = m_manager->addProperty(QVariant::Bool, PROPERTY_TYPE_SKIPCREATE);
    m_skipCreate->setValue(false);
}

void QPropertyBrowser::createPropertySkipInit()
{
    m_skipInit = m_manager->addProperty(QVariant::Bool, PROPERTY_TYPE_SKIPINIT);
    m_skipInit->setValue(false);
}

void QPropertyBrowser::createPropertyTouchEnable()
{
    m_touchEnable = m_manager->addProperty(QVariant::Bool, PROPERTY_TYPE_TOUCHENABLE);
    m_touchEnable->setValue(false);
}

void QPropertyBrowser::createPropertyColor()
{
    m_color = m_manager->addProperty(QVariant::Color, PROPERTY_TYPE_COLOR);
    m_color->setValue(QColor(Qt::black));
}

void QPropertyBrowser::createPropertyOpacity()
{
    m_opacity = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_OPACITY);
    m_opacity->setAttribute("minimum",0);
    m_opacity->setAttribute("maximum",255);
    m_opacity->setValue(255);
}

void QPropertyBrowser::createPropertyFilePath()
{
    m_filePath = m_manager->addProperty(VariantManager::filePathTypeId(), PROPERTY_TYPE_IMAGE);
    m_filePath->setValue("");
    m_filePath->setAttribute("filter", FILTER_IMAGES);
}

void QPropertyBrowser::createPropertyFont()
{
    m_font = m_manager->addProperty(QVariant::Font, PROPERTY_TYPE_FONT);
    m_font->setValue(QFont());
}

void QPropertyBrowser::createPropertyText()
{
    m_text = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_TEXT);
    m_text->setValue(QString());
}

void QPropertyBrowser::createPropertyHorizontalAlignment()
{
    m_horizontalAlignment = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_OPACITY);
    QStringList list;
    list<<"Left"<<"Center"<<"Right";
    m_horizontalAlignment->setAttribute("enumNames", list);
    m_horizontalAlignment->setValue(1);
}

void QPropertyBrowser::createPropertyVerticalAlignment()
{
    m_verticalAlignment = m_manager->addProperty(QtVariantPropertyManager::enumTypeId(), PROPERTY_TYPE_TEXT_VERTICAL);
    QStringList list;
    list<<"Top"<<"Center"<<"Bottom";
    m_verticalAlignment->setAttribute("enumNames", list);
    m_verticalAlignment->setValue(1);
}

void QPropertyBrowser::createPropertyTextStrikeSize()
{
    m_textStrikeSize = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_TEXT_STRIKE_SIZE);
    m_textStrikeSize->setAttribute("minimum",0);
    m_textStrikeSize->setAttribute("maximum",9);
    m_horizontalAlignment->setValue(0);
}

void QPropertyBrowser::createPropertyTextStrikeColor()
{
    m_textStrikeColor = m_manager->addProperty(QVariant::Color, PROPERTY_TYPE_COLOR);
    m_textStrikeColor->setValue(QColor(Qt::black));
}

void QPropertyBrowser::createPropertyDimensionWith()
{
    m_dimensionWith = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_WIDTH );
    m_dimensionWith->setAttribute("minimum",0);
    m_dimensionWith->setAttribute("maximum",9999);
    m_dimensionWith->setValue(0);
}

void QPropertyBrowser::createPropertyDimensionHeight()
{
    m_dimensionHeight = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_HEIGHT );
    m_dimensionHeight->setAttribute("minimum",0);
    m_dimensionHeight->setAttribute("maximum",9999);
    m_dimensionHeight->setValue(0);
    //m_dimensionHeight->setEnabled(false);
}

void QPropertyBrowser::createPropertyContainerFilePath()
{
    m_containerLayerFilePath = m_manager->addProperty(VariantManager::filePathTypeId(), PROPERTY_TYPE_CONTAINER_FILEPATH);
    m_containerLayerFilePath->setValue("");
    m_containerLayerFilePath->setAttribute("filter", FILTER_CONFIG);
}

void QPropertyBrowser::createPropertyInsetsX()
{
    m_insetsX = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_X);
    m_insetsX->setAttribute("minimum",1);
    m_insetsX->setAttribute("maximum",9999);
    m_insetsX->setValue(1);
}

void QPropertyBrowser::createPropertyInsetsY()
{
    m_insetsY = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_Y);
    m_insetsY->setAttribute("minimum",1);
    m_insetsY->setAttribute("maximum",9999);
    m_insetsY->setValue(1);
}

void QPropertyBrowser::createPropertyInsetsWidth()
{
    m_insetsWidth = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_WIDTH);
    m_insetsWidth->setAttribute("minimum",1);
    m_insetsWidth->setAttribute("maximum",9999);
    m_insetsWidth->setValue(1);
}

void QPropertyBrowser::createPropertyInsetsHeight()
{
    m_insetsHeight = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_HEIGHT);
    m_insetsHeight->setAttribute("minimum",1);
    m_insetsHeight->setAttribute("maximum",9999);
    m_insetsHeight->setValue(1);
}

void QPropertyBrowser::createPropertyPreferedWidth()
{
    m_preferredWidth = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_WIDTH);
    m_preferredWidth->setAttribute("minimum",1);
    m_preferredWidth->setAttribute("maximum",9999);
    m_preferredWidth->setValue(1);
}

void QPropertyBrowser::createPropertyPreferedHeight()
{
    m_preferredHeight = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_HEIGHT);
    m_preferredHeight->setAttribute("minimum",1);
    m_preferredHeight->setAttribute("maximum",9999);
    m_preferredHeight->setValue(1);
}

void QPropertyBrowser::createPropertyProgressTimerType()
{
    m_progressTimerType = m_manager->addProperty(QtVariantPropertyManager::enumTypeId(), "progressType");
    QStringList list;
    list<<"Radial"<<"Bar";
    m_progressTimerType->setAttribute("enumNames", list);
    m_progressTimerType->setValue(1);
    //m_progressTimerType->setEnabled(false);
}

void QPropertyBrowser::createPropertyDirection()
{
    m_direction = m_manager->addProperty(QtVariantPropertyManager::enumTypeId(), "direction");
    QStringList list;
    list<<"LeftToRight"<<"RightToLeft"<<"BottomToTop"<<"TopToBottom";
    m_direction->setAttribute("enumNames", list);
    m_direction->setValue(0);
}

void QPropertyBrowser::createPropertyPercentage()
{
    m_percentage = m_manager->addProperty(QVariant::Double, PROPERTY_TYPE_BAR_PERCENT);
    m_percentage->setAttribute("minimum", 0.0f);
    m_percentage->setAttribute("maximum", 1.0f);
    m_percentage->setAttribute("singleStep", 0.01f);
    m_percentage->setValue(1.0f);
}

void QPropertyBrowser::createPropertyAtlasElementWidth()
{
    m_atlasElementWidth = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_WIDTH);
    m_atlasElementWidth->setAttribute("minimum",1);
    m_atlasElementWidth->setAttribute("maximum",9999);
    m_atlasElementWidth->setValue(10);
}

void QPropertyBrowser::createPropertyAtlasElementHeight()
{
    m_atlasElementHeight = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_HEIGHT);
    m_atlasElementHeight->setAttribute("minimum",1);
    m_atlasElementHeight->setAttribute("maximum",9999);
    m_atlasElementHeight->setValue(10);
}

void QPropertyBrowser::createPropertyAtlasStartChar()
{
    m_atlasStartChar = m_manager->addProperty(QVariant::Int, "startChar");
    m_atlasStartChar->setAttribute("minimum",1);
    m_atlasStartChar->setAttribute("maximum",255);
    m_atlasStartChar->setValue(0x30);
}

void QPropertyBrowser::createPropertyAtlasText()
{
    m_atlasText = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_TEXT);
    m_atlasText->setValue(QString());
}

void QPropertyBrowser::createPropertyScrollViewDirection()
{
    m_scrollViewDirection = m_manager->addProperty(QtVariantPropertyManager::enumTypeId(), "direction");
    QStringList list;
    list<<"Horizontal"<<"Vertical";
    m_scrollViewDirection->setAttribute("enumNames", list);
    m_scrollViewDirection->setValue(0);
}

void QPropertyBrowser::createPropertyScrollViewCount()
{
    m_scrollViewCount = m_manager->addProperty(QVariant::Int, "count");
    m_scrollViewCount->setAttribute("minimum",1);
    m_scrollViewCount->setAttribute("maximum",99);
    m_scrollViewCount->setValue(3);
}

void QPropertyBrowser::createPropertyScrollViewOffsetX()
{
    m_scrollViewOffsetX = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_X);
    m_scrollViewOffsetX->setAttribute("minimum",0);
    m_scrollViewOffsetX->setAttribute("maximum",999);
    m_scrollViewOffsetX->setValue(0);
}

void QPropertyBrowser::createPropertyScrollViewOffsetY()
{
    m_scrollViewOffsetY = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_Y);
    m_scrollViewOffsetY->setAttribute("minimum",0);
    m_scrollViewOffsetY->setAttribute("maximum",999);
    m_scrollViewOffsetY->setValue(0);
}

void QPropertyBrowser::createPropertyScrollViewSpaceWidth()
{
    m_scrollViewSpaceWidth = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_WIDTH);
    m_scrollViewSpaceWidth->setAttribute("minimum",0);
    m_scrollViewSpaceWidth->setAttribute("maximum",999);
    m_scrollViewSpaceWidth->setValue(0);
}

void QPropertyBrowser::createPropertyScrollViewSpaceHeight()
{
    m_scrollViewSpaceHeight = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_HEIGHT);
    m_scrollViewSpaceHeight->setAttribute("minimum",0);
    m_scrollViewSpaceHeight->setAttribute("maximum",999);
    m_scrollViewSpaceHeight->setValue(0);
}

void QPropertyBrowser::createPropertyScrollViewContentWidth()
{
    m_scrollViewContentWidth = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_WIDTH);
    m_scrollViewContentWidth->setAttribute("minimum",0);
    m_scrollViewContentWidth->setAttribute("maximum",999);
    m_scrollViewContentWidth->setValue(0);
}

void QPropertyBrowser::createPropertyScrollViewContentHeight()
{
    m_scrollViewContentHeight = m_manager->addProperty(QVariant::Int, PROPERTY_TYPE_HEIGHT);
    m_scrollViewContentHeight->setAttribute("minimum",0);
    m_scrollViewContentHeight->setAttribute("maximum",999);
    m_scrollViewContentHeight->setValue(0);
}

void QPropertyBrowser::createPropertyScrollViewIsDynamicallyGenerated()
{
    m_scrollViewIsDynamicallyGenerated = m_manager->addProperty(QVariant::Bool, tr("dynamicallyGenerated"));
    m_scrollViewIsDynamicallyGenerated->setValue(false);
}

//-- 2 level
void QPropertyBrowser::createPropertyPoint()
{
    m_point = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_POSITION);
    m_point->addSubProperty(m_x);
    m_point->addSubProperty(m_y);
    m_point->setValue(QString(""));
}

void QPropertyBrowser::createPropertySize()
{
    m_size = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_SIZE);
    m_size->addSubProperty(m_width);
    m_size->addSubProperty(m_height);
    m_size->setValue(QString(""));
    m_size->setEnabled(false);
}

void QPropertyBrowser::createPropertyAnchor()
{
    m_anchor = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_ANCHOR);
    m_anchor->addSubProperty(m_anchorX);
    m_anchor->addSubProperty(m_anchorY);
    m_anchor->setValue(QString(""));
}

void QPropertyBrowser::createPropertyScale()
{
    m_scale = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_SCALE);
    m_scale->addSubProperty(m_scaleX);
    m_scale->addSubProperty(m_scaleY);
    m_scale->setValue(QString(""));
}

void QPropertyBrowser::createPropertyDimensionSize()
{
    m_dimensionSize = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_DIMENSION);
    m_dimensionSize->addSubProperty(m_dimensionWith);
    m_dimensionSize->addSubProperty(m_dimensionHeight);
    m_dimensionSize->setValue(QString(""));
}

void QPropertyBrowser::createPropertyTextAlignment()
{
    m_textAlignment = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_TEXT_ALIGNMENT);
    m_textAlignment->addSubProperty(m_horizontalAlignment);
    m_textAlignment->addSubProperty(m_verticalAlignment);
    m_textAlignment->setValue(QString(""));
}

void QPropertyBrowser::createPropertyTextStrike()
{
    m_textStrike = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_TEXT_STRIKE);
    m_textStrike->addSubProperty(m_textStrikeColor);
    m_textStrike->addSubProperty(m_textStrikeSize);
    m_textStrike->setValue(QString(""));
}

void QPropertyBrowser::createPropertyInsetsRect()
{
    m_insetsRect = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_INSETSRECT);
    m_insetsRect->addSubProperty(m_insetsX);
    m_insetsRect->addSubProperty(m_insetsY);
    m_insetsRect->addSubProperty(m_insetsWidth);
    m_insetsRect->addSubProperty(m_insetsHeight);
    m_insetsRect->setValue(QString(""));
}

void QPropertyBrowser::createPropertyPreferredSize()
{
    m_preferredSize = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_PREFERREDSIZE);
    m_preferredSize->addSubProperty(m_preferredWidth);
    m_preferredSize->addSubProperty(m_preferredHeight);
    m_preferredSize->setValue(QString(""));
}

void QPropertyBrowser::createPropertyScrollViewOffset()
{
    m_scrollViewOffset = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_OFFSET);
    m_scrollViewOffset->addSubProperty(m_scrollViewOffsetX);
    m_scrollViewOffset->addSubProperty(m_scrollViewOffsetY);
    m_scrollViewOffset->setValue(QString(""));
}

void QPropertyBrowser::createPropertyScrollViewSpace()
{
    m_scrollViewSpace = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_SPACE);
    m_scrollViewSpace->addSubProperty(m_scrollViewSpaceWidth);
    m_scrollViewSpace->addSubProperty(m_scrollViewSpaceHeight);
    m_scrollViewSpace->setValue(QString(""));
}

void QPropertyBrowser::createPropertyScrollViewContent()
{
    m_scrollViewContent = m_manager->addProperty(QVariant::String, PROPERTY_TYPE_CONTENT);
    m_scrollViewContent->addSubProperty(m_scrollViewContentWidth);
    m_scrollViewContent->addSubProperty(m_scrollViewContentHeight);
    m_scrollViewContent->setValue(QString(""));
}

//-- 3 level
void QPropertyBrowser::createPropertyCCNode()
{
    m_ccNode = m_manager->addProperty(QVariant::String, tr(CLASS_TYPE_CCNODE));
    m_ccNode->addSubProperty(m_fixed);
    m_ccNode->addSubProperty(m_visible);
    m_ccNode->addSubProperty(m_skipCreate);
    m_ccNode->addSubProperty(m_skipInit);
    m_ccNode->addSubProperty(m_z);
    m_ccNode->addSubProperty(m_tag);
    m_ccNode->addSubProperty(m_point);
    m_ccNode->addSubProperty(m_size);
    //m_ccNode->addSubProperty(m_anchor);
    m_ccNode->addSubProperty(m_scale);
    m_ccNode->addSubProperty(m_rotation);
}

void QPropertyBrowser::createPropertyCCLayer()
{
    m_ccLayer = m_manager->addProperty(QVariant::String, tr(CLASS_TYPE_CCLAYER));
    m_ccLayer->addSubProperty(m_touchEnable);
}

void QPropertyBrowser::createPropertyCCLayerColor()
{
    m_ccLayerColor = m_manager->addProperty(QVariant::String, tr(CLASS_TYPE_CCLAYERCOLOR));
    m_ccLayerColor->addSubProperty(m_color);
    m_ccLayerColor->addSubProperty(m_opacity);
}

void QPropertyBrowser::createPropertyCCSprite()
{
    m_ccSprite = m_manager->addProperty(QVariant::String, tr(CLASS_TYPE_CCSPRITE));
    m_ccSprite->addSubProperty(m_filePath);
}

void QPropertyBrowser::createPropertyCCLabelTTF()
{
    m_ccLabelTTF = m_manager->addProperty(QVariant::String, tr(CLASS_TYPE_CCLABELTTF));
    m_ccLabelTTF->addSubProperty(m_text);
    m_ccLabelTTF->addSubProperty(m_font);
    m_ccLabelTTF->addSubProperty(m_dimensionSize);
    m_ccLabelTTF->addSubProperty(m_textAlignment);
    m_ccLabelTTF->addSubProperty(m_textStrike);
}

void QPropertyBrowser::createPropertyCCContainerLayer()
{
    m_ccContainerLayer = m_manager->addProperty(QVariant::String, tr(CLASS_TYPE_CCCONTAINERLAYER));
    m_ccContainerLayer->addSubProperty(m_containerLayerFilePath);
}

void QPropertyBrowser::createPropertyCCScale9Sprite()
{
    m_ccScale9Sprite = m_manager->addProperty(QVariant::String, tr(CLASS_TYPE_CCSCALE9SPRITE));
    m_ccScale9Sprite->addSubProperty(m_insetsRect);
    m_ccScale9Sprite->addSubProperty(m_preferredSize);
}

void QPropertyBrowser::createPropertyCCProgressTimer()
{
    m_ccProgressTimer = m_manager->addProperty(QVariant::String, tr(CLASS_TYPE_CCPROGRESSTIMER));
    m_ccProgressTimer->addSubProperty(m_progressTimerType);
    m_ccProgressTimer->addSubProperty(m_direction);
    m_ccProgressTimer->addSubProperty(m_percentage);
}

void QPropertyBrowser::createPropertyCCLabelAtlas()
{
    m_ccLabelAtlas = m_manager->addProperty(QVariant::String, tr(CLASS_TYPE_CCLABELATLAS));
    m_ccLabelAtlas->addSubProperty(m_atlasText);
    m_ccLabelAtlas->addSubProperty(m_atlasElementWidth);
    m_ccLabelAtlas->addSubProperty(m_atlasElementHeight);
    m_ccLabelAtlas->addSubProperty(m_atlasStartChar);
}

void QPropertyBrowser::createPropertyCCScrollView()
{
    m_ccScrollView = m_manager->addProperty(QVariant::String, tr(CLASS_TYPE_CCSCROLLVIEW));
    m_ccScrollView->addSubProperty(m_scrollViewIsDynamicallyGenerated);
    m_ccScrollView->addSubProperty(m_containerLayerFilePath);
    m_ccScrollView->addSubProperty(m_scrollViewDirection);
    m_ccScrollView->addSubProperty(m_scrollViewCount);
    m_ccScrollView->addSubProperty(m_scrollViewContent);
    m_ccScrollView->addSubProperty(m_scrollViewOffset);
    m_ccScrollView->addSubProperty(m_scrollViewSpace);
}

void QPropertyBrowser::initProperty(QCCNode* node)
{
    this->clear();
    this->blockSignals(true);
    QString classType = node->m_classType;
    if (classType == CLASS_TYPE_CCNODE)
    {
        this->initPropertyCCNode(node);
    }
    else if(classType == CLASS_TYPE_CCLAYER)
    {
        this->initPropertyCCLayer(dynamic_cast<QCCLayer*>(node));
    }
    else if(classType == CLASS_TYPE_CCLAYERCOLOR)
    {
        this->initPropertyCCLayerColor(dynamic_cast<QCCLayerColor*>(node));
    }
    else if(classType == CLASS_TYPE_CCSPRITE
            || classType == CLASS_TYPE_CCMENUITEM_IMAGE
            || classType == CLASS_TYPE_CCUIBUTTON)
    {
        this->initPropertyCCSprite( dynamic_cast<QCCSprite*>(node));
    }
    else if(classType == CLASS_TYPE_CCSCALE9SPRITE )
    {
        this->initPropertyCCScale9Sprite( dynamic_cast<QCCScale9Sprite*>(node));
    }
    else if(classType == CLASS_TYPE_CCLABELTTF)
    {
        this->initPropertyCCLabelTTF( dynamic_cast<QCCLabelTTF*>(node));
    }
    else if(classType == CLASS_TYPE_CCCONTAINERLAYER)
    {
        this->initPropertyCCContainerLayer( dynamic_cast<QCCContainerLayer*>(node));
    }
    else if(classType == CLASS_TYPE_CCPROGRESSTIMER)
    {
        this->initPropertyCCProgressTimer( dynamic_cast<QCCProgressTimer*>(node));
    }
    else if(classType == CLASS_TYPE_CCLABELATLAS)
    {
        this->initPropertyCCLabelAtlas( dynamic_cast<QCCLabelAtlas*>(node) );
    }
    else if(classType == CLASS_TYPE_CCSCROLLVIEW)
    {
        this->initPropertyCCScrollView( dynamic_cast<QCCScrollView*>(node) );
    }
    this->blockSignals(false);
}

void QPropertyBrowser::initPropertyCCNode(QCCNode* node)
{
    m_fixed->setValue(node->m_isFixed);
    m_visible->setValue(node->m_isVisible);
    m_skipCreate->setValue(node->m_isSkipCreate);
    m_skipInit->setValue(node->m_isSkipInit);
    m_z->setValue(node->m_z);
    m_tag->setValue(node->m_tag);
    m_x->setValue(node->m_x);
    m_y->setValue(node->m_y);
    m_width->setValue(node->m_width);
    m_height->setValue(node->m_height);
    m_anchorX->setValue(node->m_anchorX);
    m_anchorY->setValue(node->m_anchorY);
    m_scaleX->setValue(node->m_scaleX);
    m_scaleY->setValue(node->m_scaleY);
    m_rotation->setValue(node->m_rotation);
    this->addProperty(m_ccNode);
}

void QPropertyBrowser::initPropertyCCLayer(QCCLayer* node)
{
    this->initPropertyCCNode(node);
    m_touchEnable->setValue(node->m_isTouchEnable);
    this->addProperty(m_ccLayer);
}

void QPropertyBrowser::initPropertyCCLayerColor(QCCLayerColor* node)
{
    this->initPropertyCCLayer(node);
    m_color->setValue(node->m_color);
    m_opacity->setValue(node->m_opacity);
    this->addProperty(m_ccLayerColor);
}

void QPropertyBrowser::initPropertyCCSprite(QCCSprite* node)
{
    this->initPropertyCCLayer(node);
    m_filePath->setValue( node->resourceFullPath(node->m_filePath) );
    this->addProperty(m_ccSprite);
}

void QPropertyBrowser::initPropertyCCLabelTTF(QCCLabelTTF* node)
{
    this->initPropertyCCLayerColor(node);
    m_text->setValue(node->m_text);
    m_font->setValue(node->m_font);
    m_dimensionWith->setValue(node->m_dimensionWith);
    m_dimensionHeight->setValue(node->m_dimensionHeight);
    m_horizontalAlignment->setValue(node->m_horizontalAlignment);
    m_verticalAlignment->setValue(node->m_verticalAlignment);
    m_textStrikeSize->setValue(node->m_strikeSize);
    m_textStrikeColor->setValue(node->m_strikeColor);
    this->addProperty(m_ccLabelTTF);
}

void QPropertyBrowser::initPropertyCCContainerLayer(QCCContainerLayer* node)
{
    this->initPropertyCCNode(node);
    m_containerLayerFilePath->setValue(node->resourceFullPath(node->m_containerConfigFilePath));
    this->addProperty(m_ccContainerLayer);
}

void QPropertyBrowser::initPropertyCCScale9Sprite(QCCScale9Sprite *node)
{
    this->initPropertyCCSprite(node);
    m_insetsX->setValue(node->m_insetsRect.x());
    m_insetsY->setValue(node->m_insetsRect.y());
    m_insetsWidth->setValue(node->m_insetsRect.width());
    m_insetsHeight->setValue(node->m_insetsRect.height());
    m_preferredWidth->setValue(node->m_preferredSize.width());
    m_preferredHeight->setValue(node->m_preferredSize.height());
    this->addProperty(m_ccScale9Sprite);
}

void QPropertyBrowser::initPropertyCCProgressTimer(QCCProgressTimer *node)
{
    this->initPropertyCCSprite(node);
    m_progressTimerType->setValue(node->m_percentage);
    m_direction->setValue(node->m_direction);
    m_percentage->setValue(node->m_percentage);
    this->addProperty(m_ccProgressTimer);
}

void QPropertyBrowser::initPropertyCCLabelAtlas(QCCLabelAtlas* node)
{
    this->initPropertyCCSprite(node);
    m_atlasElementWidth->setValue(node->m_elementWidth);
    m_atlasElementHeight->setValue(node->m_elementHeight);
    m_atlasStartChar->setValue(node->m_startChar);
    m_atlasText->setValue(node->m_text);
    this->addProperty(m_ccLabelAtlas);
}

void QPropertyBrowser::initPropertyCCScrollView(QCCScrollView* node)
{
    this->initPropertyCCNode(node);
    m_scrollViewIsDynamicallyGenerated->setValue(node->m_isDynamicallyGenerated);
    m_containerLayerFilePath->setValue(node->m_containerConfigFilePath);
    m_scrollViewCount->setValue(node->m_count);
    m_scrollViewContentWidth->setValue(node->m_contentWidth);
    m_scrollViewContentHeight->setValue(node->m_contentHeight);
    m_scrollViewOffsetX->setValue(node->m_offsetX);
    m_scrollViewOffsetY->setValue(node->m_offsetY);
    m_scrollViewSpaceWidth->setValue(node->m_spaceWidth);
    m_scrollViewSpaceHeight->setValue(node->m_spaceHeight);
    this->addProperty(m_ccScrollView);
}

//slot
void QPropertyBrowser::valueChanged(QtProperty* property, QVariant )
{
    if(property == m_fixed)
    {
        int isFixed = m_fixed->value().toBool();
        emit changePropertyFixed(isFixed);
    }
    else if(property == m_x || property == m_y)
    {
        int x = m_x->value().toInt();
        int y = m_y->value().toInt();
        emit changePropertyPoint(x, y);
    }
    else if(property == m_z)
    {
        int z = m_z->value().toInt();
        emit changePropertyZ(z);
    }
    else if(property == m_tag)
    {
        int tag = m_tag->value().toInt();
        emit changePropertyTag(tag);
    }
    else if(property == m_width || property == m_height)
    {
        int width = m_width->value().toInt();
        int height = m_height->value().toInt();
        emit changePropertySize(width, height);
    }
    else if(property == m_anchorX || property == m_anchorY)
    {
        float anchorX = m_anchorX->value().toFloat();
        float anchorY = m_anchorY->value().toFloat();
        emit changePropertyAnchor(anchorX, anchorY);
    }
    else if(property == m_scaleX || property == m_scaleY)
    {
        float scaleX = m_scaleX->value().toFloat();
        float scaleY = m_scaleY->value().toFloat();
        emit changePropertyScale(scaleX, scaleY);
    }
    else if(property == m_rotation)
    {
        int rotation = m_rotation->value().toInt();
        emit changePropertyRotation(rotation);
    }
    else if(property == m_visible)
    {
        bool visible = m_visible->value().toBool();
        emit changePropertyVisible(visible);
    }
    else if(property == m_skipCreate)
    {
        bool skipCreate = m_skipCreate->value().toBool();
        emit changePropertySkipCreate(skipCreate);
    }
    else if(property == m_skipInit)
    {
        bool skipInit = m_skipInit->value().toBool();
        emit changePropertySkipInit(skipInit);
    }
    else if(property == m_touchEnable)
    {
        bool touchEnable = m_touchEnable->value().toBool();
        emit changePropertyTouchEnable(touchEnable);
    }
    else if(property == m_color)
    {
        QColor color = m_color->value().value<QColor>();
        emit changePropertyColor(color);
    }
    else if(property == m_opacity)
    {
        int opacity = m_opacity->value().toInt();
        emit changePropertyOpacity(opacity);
    }
    else if(property == m_filePath)
    {
        QString filePath = m_filePath->value().toString();
        emit changePropertyFilePath(filePath);
    }
    else if(property == m_font)
    {
        QFont font = m_font->value().value<QFont>();
        emit changePropertyFont(font);
    }
    else if(property == m_text)
    {
        QString text = m_text->value().toString();
        emit changePropertyText(text);
    }
    else if(property == m_horizontalAlignment || property == m_verticalAlignment)
    {
        int horizontal = m_horizontalAlignment->value().toInt();
        int vertical = m_verticalAlignment->value().toInt();
        emit changePropertyAlignment(horizontal, vertical);
    }
    else if(property == m_dimensionWith || property == m_dimensionHeight)
    {
        int width = m_dimensionWith->value().toInt();
        int height = m_dimensionHeight->value().toInt();
        emit changePropertyTextDimension(width, height);
    }
    else if(property == m_textStrikeSize || property == m_textStrikeColor)
    {
        int size = m_textStrikeSize->value().toInt();
        QColor color = m_textStrikeColor->value().value<QColor>();
        emit changePropertyTextStrike(size, color);
    }
    else if(property == m_containerLayerFilePath)
    {
        QString filePath = m_containerLayerFilePath->value().toString();
        emit changePropertyCCContainerLayerFilePath(filePath);
    }
    else if(property == m_insetsX || property == m_insetsY || property == m_insetsWidth || property == m_insetsHeight)
    {
        int x = m_insetsX->value().toInt();
        int y = m_insetsY->value().toInt();
        int w = m_insetsWidth->value().toInt();
        int h = m_insetsHeight->value().toInt();
        emit changePropertyInsetsRect(QRect(x,y,w,h));
    }
    else if(property == m_preferredWidth || property == m_preferredHeight)
    {
        int w = m_preferredWidth->value().toInt();
        int h = m_preferredHeight->value().toInt();
        emit changePropertyPreferedSize(QSize(w,h));
    }
    else if(property == m_progressTimerType)
    {
        int type = m_progressTimerType->value().toInt();

        if(type == 0) //list<<"Radial"<<"Bar";
        {
            QStringList list;
            list<<"clockwise"<<"anticlockwise";
            m_direction->setAttribute("enumNames", list);
            m_direction->setValue(0);
        }
        else if(type == 1)
        {
            QStringList list;
            list<<"LeftToRight"<<"RightToLeft"<<"BottomToTop"<<"TopToBottom";
            m_direction->setAttribute("enumNames", list);
            m_direction->setValue(0);
        }

        emit changePropertyProgressTimerType( type );
    }
    else if(property == m_direction)
    {
        int direction = m_direction->value().toInt();
        emit changePropertyDirection( direction );
    }
    else if(property == m_percentage)
    {
        float percentage = m_percentage->value().toFloat();
        emit changePropertyPercentage( percentage );
    }
    else if(property == m_atlasElementWidth || property == m_atlasElementHeight)
    {
        int width = m_atlasElementWidth->value().toInt();
        int height = m_atlasElementHeight->value().toInt();
        emit changePropertyAtlasElementSize(width, height);
    }
    else if(property == m_atlasStartChar)
    {
        int startChar = m_atlasStartChar->value().toInt();
        emit changePropertyAtlasStartChar(startChar);
    }
    else if(property == m_atlasText)
    {
        QString text = m_atlasText->value().toString();
        emit changePropertyAtlasText(text);
    }
    else if(property == m_scrollViewCount)
    {
        int count = m_scrollViewCount->value().toInt();
        emit changePropertyScrollViewCount(count);
    }
    else if(property == m_scrollViewDirection)
    {
        int direction = m_scrollViewDirection->value().toInt();
        emit changePropertyScrollViewDirection(direction);
    }
    else if(property == m_scrollViewOffsetX || property == m_scrollViewOffsetY)
    {
        int x = m_scrollViewOffsetX->value().toInt();
        int y = m_scrollViewOffsetY->value().toInt();
        emit changePropertyScrollViewOffset(x,y);
    }
    else if(property == m_scrollViewSpaceWidth || property == m_scrollViewSpaceHeight)
    {
        int width = m_scrollViewSpaceWidth->value().toInt();
        int height = m_scrollViewSpaceHeight->value().toInt();
        emit changePropertyScrollViewSpace(width, height);
    }
    else if(property == m_scrollViewContentWidth || property == m_scrollViewContentHeight)
    {
        int width = m_scrollViewContentWidth->value().toInt();
        int height = m_scrollViewContentHeight->value().toInt();
        emit changePropertyScrollViewContent(width, height);
    }
    else if(property == m_scrollViewIsDynamicallyGenerated)
    {
        int isDynamically = m_scrollViewIsDynamicallyGenerated->value().toBool();
        emit changePropertyDynamicallyGenerated(isDynamically);
    }
}

void QPropertyBrowser::changedPropertyPoint(int x, int y)
{
    this->blockSignals(true);
    m_x->setValue(x);
    m_y->setValue(y);
    this->blockSignals(false);
}

void QPropertyBrowser::changedPropertySize(int width, int height)
{
    this->blockSignals(true);
    m_width->setValue(width);
    m_height->setValue(height);
    this->blockSignals(false);
}

void QPropertyBrowser::changedPropertyTextDimension(int w, int h)
{
    this->blockSignals(true);
    m_dimensionWith->setValue(w);
    m_dimensionHeight->setValue(h);
    this->blockSignals(false);
}

void QPropertyBrowser::test()
{
    this->addProperty(m_ccNode);
    this->addProperty(m_ccLayer);
    this->addProperty(m_ccLayerColor);
    this->addProperty(m_ccSprite);
    this->addProperty(m_ccLabelTTF);
}
