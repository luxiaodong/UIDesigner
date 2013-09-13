#ifndef QPROPERTYBROWSER_H
#define QPROPERTYBROWSER_H

#include "variantmanager.h"
#include "variantfactory.h"
#include "qttreepropertybrowser.h"

class QPropertyBrowser : public QtTreePropertyBrowser
{
public:
    QPropertyBrowser();

public:
    void test();

private:
    QtVariantPropertyManager*   m_manager;
    QtVariantEditorFactory *    m_factory;
};

#endif // QPROPERTYBROWSER_H
