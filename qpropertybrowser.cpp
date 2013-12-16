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

    //-- 2 level
    createPropertyPoint();
    createPropertySize();
    createPropertyAnchor();
    createPropertyScale();
    createPropertyTextAlignment();
    createPropertyDimensionSize();
    createPropertyInsetsRect();
    createPropertyPreferredSize();

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
}

void QPropertyBrowser::createPropertyFixed()
{
    m_fixed = m_manager->addProperty(QVariant::Bool, tr("fixed"));
    m_fixed->setValue(false);
}

//-- 1 level
void QPropertyBrowser::createPropertyX()
{
    m_x = m_manager->addProperty(QVariant::Int, "x");
    m_x->setAttribute("minimum",-9999);
    m_x->setAttribute("maximum",9999);
    m_x->setValue(0);
}

void QPropertyBrowser::createPropertyY()
{
    m_y = m_manager->addProperty(QVariant::Int, "y");
    m_y->setAttribute("minimum",-9999);
    m_y->setAttribute("maximum",9999);
    m_y->setValue(0);
}

void QPropertyBrowser::createPropertyZ()
{
    m_z = m_manager->addProperty(QVariant::Int, "z");
    m_z->setAttribute("minimum",-9999);
    m_z->setAttribute("maximum",9999);
    m_z->setValue(0);
}

void QPropertyBrowser::createPropertyTag()
{
    m_tag = m_manager->addProperty(QVariant::Int, "tag");
    m_tag->setAttribute("minimum",-1);
    m_tag->setAttribute("maximum",9999999);
    m_tag->setValue(-1);
}

void QPropertyBrowser::createPropertyWidth()
{
    m_width = m_manager->addProperty(QVariant::Int, "width");
    m_width->setAttribute("minimum",0);
    m_width->setAttribute("maximum",9999);
    m_width->setValue(0);
}

void QPropertyBrowser::createPropertyHeight()
{
    m_height = m_manager->addProperty(QVariant::Int, "height");
    m_height->setAttribute("minimum",0);
    m_height->setAttribute("maximum",9999);
    m_height->setValue(0);
}

void QPropertyBrowser::createPropertyAnchorX()
{
    m_anchorX = m_manager->addProperty(QVariant::Double, tr("anchorX"));
    m_anchorX->setAttribute("minimum", 0.0f);
    m_anchorX->setAttribute("maximum", 1.0f);
    m_anchorX->setAttribute("singleStep", 0.01f);
    m_anchorX->setValue(1.0f);
}

void QPropertyBrowser::createPropertyAnchorY()
{
    m_anchorY = m_manager->addProperty(QVariant::Double, tr("anchorX"));
    m_anchorY->setAttribute("minimum", 0.0f);
    m_anchorY->setAttribute("maximum", 1.0f);
    m_anchorY->setAttribute("singleStep", 0.01f);
    m_anchorY->setValue(1.0f);
}

void QPropertyBrowser::createPropertyScaleX()
{
    m_scaleX = m_manager->addProperty(QVariant::Double, tr("scaleX"));
    m_scaleX->setAttribute("minimum", -1000.0f);
    m_scaleX->setAttribute("maximum", 1000.0f);
    m_scaleX->setAttribute("singleStep", 0.01f);
    m_scaleX->setValue(1.0f);
}

void QPropertyBrowser::createPropertyScaleY()
{
    m_scaleY = m_manager->addProperty(QVariant::Double, tr("scaleY"));
    m_scaleY->setAttribute("minimum", -1000.0f);
    m_scaleY->setAttribute("maximum", 1000.0f);
    m_scaleY->setAttribute("singleStep", 0.01f);
    m_scaleY->setValue(1.0f);
}

void QPropertyBrowser::createPropertyRotation()
{
    m_rotation = m_manager->addProperty(QVariant::Int, "rotation");
    m_rotation->setAttribute("minimum",0);
    m_rotation->setAttribute("maximum",360);
    m_rotation->setValue(0);
}

void QPropertyBrowser::createPropertyVisible()
{
    m_visible = m_manager->addProperty(QVariant::Bool, tr("visible"));
    m_visible->setValue(true);
}

void QPropertyBrowser::createPropertyTouchEnable()
{
    m_touchEnable = m_manager->addProperty(QVariant::Bool, tr("touchEnable"));
    m_touchEnable->setValue(false);
}

void QPropertyBrowser::createPropertyColor()
{
    m_color = m_manager->addProperty(QVariant::Color, tr("color"));
    m_color->setValue(QColor(Qt::black));
}

void QPropertyBrowser::createPropertyOpacity()
{
    m_opacity = m_manager->addProperty(QVariant::Int, "opacity");
    m_opacity->setAttribute("minimum",0);
    m_opacity->setAttribute("maximum",255);
    m_opacity->setValue(255);
}

void QPropertyBrowser::createPropertyFilePath()
{
    m_filePath = m_manager->addProperty(VariantManager::filePathTypeId(), tr("image"));
    m_filePath->setValue("");
    m_filePath->setAttribute("filter", FILTER_IMAGES);
}

void QPropertyBrowser::createPropertyFont()
{
    m_font = m_manager->addProperty(QVariant::Font, tr("font"));
    m_font->setValue(QFont());
}

void QPropertyBrowser::createPropertyText()
{
    m_text = m_manager->addProperty(QVariant::String, tr("text"));
    m_text->setValue(QString());
}

void QPropertyBrowser::createPropertyHorizontalAlignment()
{
    m_horizontalAlignment = m_manager->addProperty(QtVariantPropertyManager::enumTypeId(), "Horizontal");
    QStringList list;
    list<<"Left"<<"Center"<<"Right";
    m_horizontalAlignment->setAttribute("enumNames", list);
    m_horizontalAlignment->setValue(1);
}

void QPropertyBrowser::createPropertyVerticalAlignment()
{
    m_verticalAlignment = m_manager->addProperty(QtVariantPropertyManager::enumTypeId(), "Vertical");
    QStringList list;
    list<<"Top"<<"Center"<<"Bottom";
    m_verticalAlignment->setAttribute("enumNames", list);
    m_verticalAlignment->setValue(1);
    m_verticalAlignment->setEnabled(false);
}

void QPropertyBrowser::createPropertyDimensionWith()
{
    m_dimensionWith = m_manager->addProperty(QVariant::Int, tr("width"));
    m_dimensionWith->setAttribute("minimum",0);
    m_dimensionWith->setAttribute("maximum",9999);
    m_dimensionWith->setValue(0);
}

void QPropertyBrowser::createPropertyDimensionHeight()
{
    m_dimensionHeight = m_manager->addProperty(QVariant::Int, tr("height"));
    m_dimensionHeight->setAttribute("minimum",0);
    m_dimensionHeight->setAttribute("maximum",9999);
    m_dimensionHeight->setValue(0);
    m_dimensionHeight->setEnabled(false);
}

void QPropertyBrowser::createPropertyContainerFilePath()
{
    m_containerLayerFilePath = m_manager->addProperty(VariantManager::filePathTypeId(), tr("filePath"));
    m_containerLayerFilePath->setValue("");
    m_containerLayerFilePath->setAttribute("filter", FILTER_CONFIG);
}

void QPropertyBrowser::createPropertyInsetsX()
{
    m_insetsX = m_manager->addProperty(QVariant::Int, tr("x"));
    m_insetsX->setAttribute("minimum",1);
    m_insetsX->setAttribute("maximum",9999);
    m_insetsX->setValue(1);
}

void QPropertyBrowser::createPropertyInsetsY()
{
    m_insetsY = m_manager->addProperty(QVariant::Int, tr("y"));
    m_insetsY->setAttribute("minimum",1);
    m_insetsY->setAttribute("maximum",9999);
    m_insetsY->setValue(1);
}

void QPropertyBrowser::createPropertyInsetsWidth()
{
    m_insetsWidth = m_manager->addProperty(QVariant::Int, tr("width"));
    m_insetsWidth->setAttribute("minimum",1);
    m_insetsWidth->setAttribute("maximum",9999);
    m_insetsWidth->setValue(1);
}

void QPropertyBrowser::createPropertyInsetsHeight()
{
    m_insetsHeight = m_manager->addProperty(QVariant::Int, tr("height"));
    m_insetsHeight->setAttribute("minimum",1);
    m_insetsHeight->setAttribute("maximum",9999);
    m_insetsHeight->setValue(1);
}

void QPropertyBrowser::createPropertyPreferedWidth()
{
    m_preferredWidth = m_manager->addProperty(QVariant::Int, tr("width"));
    m_preferredWidth->setAttribute("minimum",1);
    m_preferredWidth->setAttribute("maximum",9999);
    m_preferredWidth->setValue(1);
}

void QPropertyBrowser::createPropertyPreferedHeight()
{
    m_preferredHeight = m_manager->addProperty(QVariant::Int, tr("height"));
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
    m_progressTimerType->setEnabled(false);
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
    m_percentage = m_manager->addProperty(QVariant::Double, tr("height"));
    m_percentage->setAttribute("minimum", 0.0f);
    m_percentage->setAttribute("maximum", 1.0f);
    m_percentage->setAttribute("singleStep", 0.01f);
    m_percentage->setValue(1.0f);
}

void QPropertyBrowser::createPropertyAtlasElementWidth()
{
    m_atlasElementWidth = m_manager->addProperty(QVariant::Int, "width");
    m_atlasElementWidth->setAttribute("minimum",1);
    m_atlasElementWidth->setAttribute("maximum",9999);
    m_atlasElementWidth->setValue(10);
}

void QPropertyBrowser::createPropertyAtlasElementHeight()
{
    m_atlasElementHeight = m_manager->addProperty(QVariant::Int, "height");
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
    m_atlasText = m_manager->addProperty(QVariant::String, tr("text"));
    m_atlasText->setValue(QString());
}

//-- 2 level
void QPropertyBrowser::createPropertyPoint()
{
    m_point = m_manager->addProperty(QVariant::String, tr("position"));
    m_point->addSubProperty(m_x);
    m_point->addSubProperty(m_y);
    m_point->setValue(QString(""));
}

void QPropertyBrowser::createPropertySize()
{
    m_size = m_manager->addProperty(QVariant::String, tr("size"));
    m_size->addSubProperty(m_width);
    m_size->addSubProperty(m_height);
    m_size->setValue(QString(""));
    m_size->setEnabled(false);
}

void QPropertyBrowser::createPropertyAnchor()
{
    m_anchor = m_manager->addProperty(QVariant::String, tr("anchor"));
    m_anchor->addSubProperty(m_anchorX);
    m_anchor->addSubProperty(m_anchorY);
    m_anchor->setValue(QString(""));
}

void QPropertyBrowser::createPropertyScale()
{
    m_scale = m_manager->addProperty(QVariant::String, tr("scale"));
    m_scale->addSubProperty(m_scaleX);
    m_scale->addSubProperty(m_scaleY);
    m_scale->setValue(QString(""));
}

void QPropertyBrowser::createPropertyDimensionSize()
{
    m_dimensionSize = m_manager->addProperty(QVariant::String, tr("dimension"));
    m_dimensionSize->addSubProperty(m_dimensionWith);
    m_dimensionSize->addSubProperty(m_dimensionHeight);
    m_dimensionSize->setValue(QString(""));
}

void QPropertyBrowser::createPropertyTextAlignment()
{
    m_textAlignment = m_manager->addProperty(QVariant::String, tr("textAlignment"));
    m_textAlignment->addSubProperty(m_horizontalAlignment);
    m_textAlignment->addSubProperty(m_verticalAlignment);
    m_textAlignment->setValue(QString(""));
}

void QPropertyBrowser::createPropertyInsetsRect()
{
    m_insetsRect = m_manager->addProperty(QVariant::String, tr("insetsRect"));
    m_insetsRect->addSubProperty(m_insetsX);
    m_insetsRect->addSubProperty(m_insetsY);
    m_insetsRect->addSubProperty(m_insetsWidth);
    m_insetsRect->addSubProperty(m_insetsHeight);
    m_insetsRect->setValue(QString(""));
}

void QPropertyBrowser::createPropertyPreferredSize()
{
    m_preferredSize = m_manager->addProperty(QVariant::String, tr("preferredSize"));
    m_preferredSize->addSubProperty(m_preferredWidth);
    m_preferredSize->addSubProperty(m_preferredHeight);
    m_preferredSize->setValue(QString(""));
}

//-- 3 level
void QPropertyBrowser::createPropertyCCNode()
{
    m_ccNode = m_manager->addProperty(QVariant::String, tr("CCNode"));
    m_ccNode->addSubProperty(m_fixed);
    m_ccNode->addSubProperty(m_visible);
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
    m_ccLayer = m_manager->addProperty(QVariant::String, tr("CCLayer"));
    m_ccLayer->addSubProperty(m_touchEnable);
}

void QPropertyBrowser::createPropertyCCLayerColor()
{
    m_ccLayerColor = m_manager->addProperty(QVariant::String, tr("CCLayerColor"));
    m_ccLayerColor->addSubProperty(m_color);
    m_ccLayerColor->addSubProperty(m_opacity);
}

void QPropertyBrowser::createPropertyCCSprite()
{
    m_ccSprite = m_manager->addProperty(QVariant::String, tr("CCSprite"));
    m_ccSprite->addSubProperty(m_filePath);
}

void QPropertyBrowser::createPropertyCCLabelTTF()
{
    m_ccLabelTTF = m_manager->addProperty(QVariant::String, tr("CCLabelTTF"));
    m_ccLabelTTF->addSubProperty(m_text);
    m_ccLabelTTF->addSubProperty(m_font);
    m_ccLabelTTF->addSubProperty(m_dimensionSize);
    m_ccLabelTTF->addSubProperty(m_textAlignment);
}

void QPropertyBrowser::createPropertyCCContainerLayer()
{
    m_ccContainerLayer = m_manager->addProperty(QVariant::String, tr("ContainerLayer"));
    m_ccContainerLayer->addSubProperty(m_containerLayerFilePath);
}

void QPropertyBrowser::createPropertyCCScale9Sprite()
{
    m_ccScale9Sprite = m_manager->addProperty(QVariant::String, tr("CCScale9Sprite"));
    m_ccScale9Sprite->addSubProperty(m_insetsRect);
    m_ccScale9Sprite->addSubProperty(m_preferredSize);
}

void QPropertyBrowser::createPropertyCCProgressTimer()
{
    m_ccProgressTimer = m_manager->addProperty(QVariant::String, tr("CCProgressTimer"));
    m_ccProgressTimer->addSubProperty(m_progressTimerType);
    m_ccProgressTimer->addSubProperty(m_direction);
    m_ccProgressTimer->addSubProperty(m_percentage);
}

void QPropertyBrowser::createPropertyCCLabelAtlas()
{
    m_ccLabelAtlas = m_manager->addProperty(QVariant::String, tr("CCLabelAtlas"));
    m_ccLabelAtlas->addSubProperty(m_atlasText);
    m_ccLabelAtlas->addSubProperty(m_atlasElementWidth);
    m_ccLabelAtlas->addSubProperty(m_atlasElementHeight);
    m_ccLabelAtlas->addSubProperty(m_atlasStartChar);
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
    else if(classType == CLASS_TYPE_CCSPRITE || classType == CLASS_TYPE_CCMENUITEM_IMAGE)
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
    this->blockSignals(false);
}

void QPropertyBrowser::initPropertyCCNode(QCCNode* node)
{
    m_fixed->setValue(node->m_isFixed);
    m_visible->setValue(node->m_isVisible );
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
        float type = m_progressTimerType->value().toFloat();
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

void QPropertyBrowser::test()
{
    this->addProperty(m_ccNode);
    this->addProperty(m_ccLayer);
    this->addProperty(m_ccLayerColor);
    this->addProperty(m_ccSprite);
    this->addProperty(m_ccLabelTTF);
}
