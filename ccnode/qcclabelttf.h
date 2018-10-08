#ifndef QCCLABELTTF_H
#define QCCLABELTTF_H

#include "qcclayercolor.h"

class QCCLabelTTF : public QCCLayerColor
{
public:
    QCCLabelTTF();

    virtual void importData(QMap<QString, QString>&);
    virtual QMap<QString, QString> exportData();
    virtual QGraphicsItem* createGraphicsItem();
    virtual void updateGraphicsItem();

private:
    bool loadLanguageFile();

public:  
    QFont m_font;
    QString m_text;
    int m_horizontalAlignment;
    int m_verticalAlignment;
    int m_dimensionWith;
    int m_dimensionHeight;
    bool m_isInLanguage;
    int m_strikeSize;
    QColor m_strikeColor;
};

#endif // QCCLABELTTF_H
