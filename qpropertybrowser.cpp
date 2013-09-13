#include "qpropertybrowser.h"

QPropertyBrowser::QPropertyBrowser()
{
    m_manager = new VariantManager();
    m_factory = new VariantFactory();
    this->setFactoryForManager(m_manager, m_factory);
}

void QPropertyBrowser::test()
{
    QtVariantProperty* m_visible = m_manager->addProperty(QVariant::Bool, tr("visible"));
    m_visible->setValue(true);
    this->addProperty(m_visible);

    QtVariantProperty* m_x = m_manager->addProperty(QVariant::Int, "x");
    m_x->setAttribute("minimum",0);
    m_x->setAttribute("maximum",1024);
    m_x->setValue(0);

    QtVariantProperty* m_y = m_manager->addProperty(QVariant::Int, "y");
    m_y->setAttribute("minimum",0);
    m_y->setAttribute("maximum",1024);
    m_y->setValue(0);

    QtVariantProperty* m_point = m_manager->addProperty(QVariant::String, tr("center point"));
    m_point->setValue(QString("(0,0)"));
    m_point->addSubProperty(m_x);
    m_point->addSubProperty(m_y);
    this->addProperty(m_point);
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
