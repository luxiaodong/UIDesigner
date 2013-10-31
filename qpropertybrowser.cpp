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
    m_filePath->setAttribute("filter", "Images (*.png *.jpg)");
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

void QPropertyBrowser::initProperty(QCCNode* node)
{
    this->clear();
    QString classType = node->m_classType;
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
