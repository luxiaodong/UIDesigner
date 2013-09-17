#include "qpropertybrowser.h"

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

    //-- 2 level
    createPropertyPoint();
    createPropertySize();
    createPropertyAnchor();
    createPropertyScale();

    //-- 3 level
    createPropertyCCNode();
    createPropertyCCLayer();
    createPropertyCCLayerColor();
    createPropertyCCSprite();
    createPropertyCCLabelTTF();
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
    m_visible->setValue(false);
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
    m_filePath->setAttribute("filter", "Image files (*.png)");
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

//-- 3 level
void QPropertyBrowser::createPropertyCCNode()
{
    m_ccNode = m_manager->addProperty(QVariant::String, tr("CCNode"));
    m_ccNode->addSubProperty(m_visible);
    m_ccNode->addSubProperty(m_z);
    m_ccNode->addSubProperty(m_tag);
    m_ccNode->addSubProperty(m_point);
    m_ccNode->addSubProperty(m_size);
    m_ccNode->addSubProperty(m_anchor);
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
}

void QPropertyBrowser::initProperty(QString& classType, QCCNode* node)
{
    this->clear();
    if (classType == CLASS_TYPE_CCNODE)
    {
        this->initPropertyCCNode(node);
    }
    else if(classType == CLASS_TYPE_CCLAYER)
    {
        this->initPropertyCCLayer((QCCLayer*)(node));
    }
    else if(classType == CLASS_TYPE_CCLAYERCOLOR)
    {
        this->initPropertyCCLayerColor((QCCLayerColor*)(node));
    }
    else if(classType == CLASS_TYPE_CCSPRITE)
    {
        this->initPropertyCCSprite((QCCSprite*)(node));
    }
    else if(classType == CLASS_TYPE_CCLABELTTF)
    {
        this->initPropertyCCLabelTTF((QCCLabelTTF*)(node));
    }
}

void QPropertyBrowser::initPropertyCCNode(QCCNode* node)
{
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
    this->initPropertyCCLayerColor(node);
    m_filePath->setValue(node->m_filePath);
    this->addProperty(m_ccSprite);
}

void QPropertyBrowser::initPropertyCCLabelTTF(QCCLabelTTF* node)
{
    this->initPropertyCCLayerColor(node);
    m_text->setValue(node->m_text);
    m_font->setValue(node->m_font);
    this->addProperty(m_ccLabelTTF);
}

//slot
void QPropertyBrowser::valueChanged(QtProperty* property, QVariant )
{
    if(property == m_x || property == m_y)
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
}

void QPropertyBrowser::changedPropertyPoint(int x, int y)
{
    m_x->setValue(x);
    m_y->setValue(y);
}

void QPropertyBrowser::test()
{
    this->addProperty(m_ccNode);\
    this->addProperty(m_ccLayer);
    this->addProperty(m_ccLayerColor);
    this->addProperty(m_ccSprite);
    this->addProperty(m_ccLabelTTF);
}

/*
    QtVariantPropertyManager *variantManager = new VariantManager();
    QtVariantEditorFactory *variantFactory = new VariantFactory();
    m_browser = new QtTreePropertyBrowser();
    m_browser->setFactoryForManager(variantManager, variantFactory);

//name
    m_name = variantManager->addProperty(QVariant::String, tr("name"));
    m_name->setValue(tr("none"));
    m_browser->addProperty(m_name);

//visible
    m_visible = variantManager->addProperty(QVariant::Bool, tr("visible"));
    m_visible->setValue(true);
    m_browser->addProperty(m_visible);

//enable
    m_enable = variantManager->addProperty(QVariant::Bool, tr("enable"));
    m_enable->setValue(true);
    m_browser->addProperty(m_enable);

//z
    m_z = variantManager->addProperty(QVariant::Int, "z");
    m_z->setAttribute("minimum",0);
    m_z->setAttribute("maximum",1024);
    m_z->setValue(0);
    m_browser->addProperty(m_z);

//point
    m_x = variantManager->addProperty(QVariant::Int, "x");
    m_x->setAttribute("minimum",0);
    m_x->setAttribute("maximum",1024);
    m_x->setValue(0);

    m_y = variantManager->addProperty(QVariant::Int, "y");
    m_y->setAttribute("minimum",0);
    m_y->setAttribute("maximum",1024);
    m_y->setValue(0);

    m_point = variantManager->addProperty(QVariant::String, tr("center point"));
    m_point->setValue(QString("(0,0)"));
    m_point->addSubProperty(m_x);
    m_point->addSubProperty(m_y);
    m_browser->addProperty(m_point);

//scale
    m_keepRatio = variantManager->addProperty(QVariant::Bool, tr("keepRatio"));
    m_keepRatio->setValue(true);

    m_ratio = variantManager->addProperty(QVariant::Double, tr("ratio"));
    m_ratio->setAttribute("minimum", 0.0f);
    m_ratio->setAttribute("maximum", 1024.0f);
    m_ratio->setAttribute("singleStep", 0.01f);
    m_ratio->setValue(1.0f);

    m_width = variantManager->addProperty(QVariant::Int, tr("width"));
    m_width->setAttribute("minimum",0);
    m_width->setAttribute("maximum",1024);
    m_width->setValue(0);
    m_width->setEnabled(false);

    m_height = variantManager->addProperty(QVariant::Int, tr("height"));
    m_height->setAttribute("minimum",0);
    m_height->setAttribute("maximum",1024);
    m_height->setValue(0);
    m_height->setEnabled(false);

    m_scale = variantManager->addProperty(QVariant::String, tr("scale"));
    m_scale->setValue(QString("(1.00,1.00)"));
    m_scale->addSubProperty(m_keepRatio);
    m_scale->addSubProperty(m_ratio);
    m_scale->addSubProperty(m_width);
    m_scale->addSubProperty(m_height);
    m_browser->addProperty(m_scale);

//opacity
    m_opacity = variantManager->addProperty(QVariant::Double, tr("opacity"));
    m_opacity->setAttribute("minimum", 0.0f);
    m_opacity->setAttribute("maximum", 1.0f);
    m_opacity->setAttribute("singleStep", 0.01f);
    m_opacity->setValue(1.0f);
    m_browser->addProperty(m_opacity);

//rotate
    m_rotate = variantManager->addProperty(QVariant::Int, tr("rotate"));
    m_rotate->setAttribute("minimum", 0);
    m_rotate->setAttribute("maximum", 360);
    m_rotate->setValue(0);
    m_browser->addProperty(m_rotate);

//menuItem
    m_menuImage = variantManager->addProperty(VariantManager::filePathTypeId(), tr("image"));
    m_menuImage->setValue("");
    m_menuImage->setAttribute("filter", "Image files (*.png)");

    m_single = variantManager->addProperty(QVariant::Bool, tr("single"));
    m_single->setValue(false);

    m_light = variantManager->addProperty(QVariant::Bool, tr("light"));
    m_light->setValue(false);

    m_menuItem = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), tr("menuItem"));
    m_menuItem->addSubProperty(m_menuImage);
    m_menuItem->addSubProperty(m_single);
    m_menuItem->addSubProperty(m_light);
    m_browser->addProperty(m_menuItem);

//sprite
    m_spriteImage = variantManager->addProperty(VariantManager::filePathTypeId(), tr("image"));
    m_spriteImage->setValue("");
    m_spriteImage->setAttribute("filter", "Image files (*.png)");

    m_sprite = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), tr("sprite"));
    m_sprite->addSubProperty(m_spriteImage);
    m_browser->addProperty(m_sprite);

//label
    m_text = variantManager->addProperty(QVariant::String, tr("text"));
    m_edit = variantManager->addProperty(QVariant::Bool, tr("edit"));
    m_edit->setValue(false);
    m_click = variantManager->addProperty(QVariant::Bool, tr("click"));
    m_click->setValue(false);
    m_font = variantManager->addProperty(QVariant::Font, tr("font"));
    m_font->setValue(m_defaultFont);
    m_color = variantManager->addProperty(QVariant::Color, tr("color"));
    m_color->setValue(QColor(Qt::white));
    m_label = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), tr("label"));
    m_label->addSubProperty(m_text);
    m_label->addSubProperty(m_edit);
    m_label->addSubProperty(m_click);
    m_label->addSubProperty(m_font);
    m_label->addSubProperty(m_color);
    m_browser->addProperty(m_label);

//bar
    m_barBgImage = variantManager->addProperty(VariantManager::filePathTypeId(), tr("bgImage"));
    m_barBgImage->setValue("");
    m_barBgImage->setAttribute("filter", "Image files (*.png)");

    m_barBarImage = variantManager->addProperty(VariantManager::filePathTypeId(), tr("barImage"));
    m_barBarImage->setValue("");
    m_barBarImage->setAttribute("filter", "Image files (*.png)");

    m_bar = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), tr("bar"));
    m_bar->addSubProperty(m_barBgImage);
    m_bar->addSubProperty(m_barBarImage);
    m_browser->addProperty(m_bar);

//list
    m_listWidth = variantManager->addProperty(QVariant::Int, tr("width"));
    m_listWidth->setAttribute("minimum", 1);
    m_listWidth->setAttribute("maximum", 1024);
    m_listWidth->setValue(50);

    m_listHeight = variantManager->addProperty(QVariant::Int, tr("height"));
    m_listHeight->setAttribute("minimum", 1);
    m_listHeight->setAttribute("maximum", 1024);
    m_listHeight->setValue(50);

    m_list = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), tr("list"));
    m_list->addSubProperty(m_listWidth);
    m_list->addSubProperty(m_listHeight);
    m_browser->addProperty(m_list);

 //table
    m_tableWidth = variantManager->addProperty(QVariant::Int, tr("width"));
    m_tableWidth->setAttribute("minimum", 1);
    m_tableWidth->setAttribute("maximum", 1024);
    m_tableWidth->setValue(50);

    m_tableHeight = variantManager->addProperty(QVariant::Int, tr("height"));
    m_tableHeight->setAttribute("minimum", 1);
    m_tableHeight->setAttribute("maximum", 1024);
    m_tableHeight->setValue(50);

    m_tableRow = variantManager->addProperty(QVariant::Int, tr("Row"));
    m_tableRow->setAttribute("minimum", 1);
    m_tableRow->setAttribute("maximum", 10);
    m_tableRow->setValue(1);

    m_tableColumn = variantManager->addProperty(QVariant::Int, tr("Column"));
    m_tableColumn->setAttribute("minimum", 1);
    m_tableColumn->setAttribute("maximum", 10);
    m_tableColumn->setValue(1);

    m_tableOffsetX = variantManager->addProperty(QVariant::Int, tr("OffsetX"));
    m_tableOffsetX->setAttribute("minimum", 0);
    m_tableOffsetX->setAttribute("maximum", 1024);
    m_tableOffsetX->setValue(1);

    m_tableOffsetY = variantManager->addProperty(QVariant::Int, tr("OffsetY"));
    m_tableOffsetY->setAttribute("minimum", 0);
    m_tableOffsetY->setAttribute("maximum", 1024);
    m_tableOffsetY->setValue(1);

    m_tableSpanWidth = variantManager->addProperty(QVariant::Int, tr("SpanWidth"));
    m_tableSpanWidth->setAttribute("minimum", 0);
    m_tableSpanWidth->setAttribute("maximum", 1024);
    m_tableSpanWidth->setValue(1);

    m_tableSpanHeight = variantManager->addProperty(QVariant::Int, tr("SpanHeight"));
    m_tableSpanHeight->setAttribute("minimum", 0);
    m_tableSpanHeight->setAttribute("maximum", 1024);
    m_tableSpanHeight->setValue(1);

    m_table = variantManager->addProperty(QtVariantPropertyManager::groupTypeId(), tr("table"));
    m_table->addSubProperty(m_tableWidth);
    m_table->addSubProperty(m_tableHeight);
    m_table->addSubProperty(m_tableRow);
    m_table->addSubProperty(m_tableColumn);
    m_table->addSubProperty(m_tableOffsetX);
    m_table->addSubProperty(m_tableOffsetY);
    m_table->addSubProperty(m_tableSpanWidth);
    m_table->addSubProperty(m_tableSpanHeight);
    m_browser->addProperty(m_table);

    connect(variantManager, SIGNAL(valueChanged(QtProperty*,QVariant)), this, SLOT(valueChanged(QtProperty*,QVariant)));


 */
