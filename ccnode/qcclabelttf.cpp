#include "qcclabelttf.h"

static QMap<QString, QString> g_languages;

QCCLabelTTF::QCCLabelTTF()
{
    m_text = "CCLabelTTF";
    m_font = QFont();
    m_font.setPointSize(20);
    m_classType = CLASS_TYPE_CCLABELTTF;
    m_horizontalAlignment = kCCHorizontalTextAlignmentCenter;
    m_verticalAlignment = kCCVerticalTextAlignmentCenter;
    m_dimensionWith = 0;
    m_dimensionHeight = 0;
    m_isInLanguage = false;
    m_strikeSize = 0;
    m_strikeColor = QColor(Qt::black);
    m_anchorX = 0.5f;
    m_anchorY = 0.5f;
}

void QCCLabelTTF::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    m_text = map.value("text", QString(""));
    //QString family = map.value("fontName", QString("")); //default font
    int pointSize = map.value("pointSize", QString("20")).toInt();
    m_font = QFont();
    m_font.setPointSize(pointSize);

    m_dimensionWith = map.value("dimensionWith", "0").toInt();
    if(m_dimensionWith > 0)
    {
        m_dimensionHeight = map.value("dimensionHeight", "0").toInt();
        m_horizontalAlignment = map.value("horizontalAlignment").toInt();
        m_verticalAlignment = map.value("verticalAlignment").toInt();
    }

    m_isInLanguage = map.value("isInlanguage","0").toInt();
    m_strikeSize = map.value("strikeSize",0).toInt();

    int r = map.value("strikeColor_r", QString("0")).toInt();
    int g = map.value("strikeColor_g", QString("0")).toInt();
    int b = map.value("strikeColor_b", QString("0")).toInt();
    m_strikeColor = QColor(r,g,b,255);
}

QMap<QString, QString> QCCLabelTTF::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();
    map.insert("text", m_text);
    //map.insert("fontName", m_font.family());
    map.insert("pointSize", QString("%1").arg(m_font.pointSize()));

    if(m_dimensionWith > 0)
    {
        map.insert("dimensionWith", QString("%1").arg(m_dimensionWith));
        map.insert("dimensionHeight", QString("%1").arg(m_dimensionHeight));
        map.insert("horizontalAlignment",QString("%1").arg(m_horizontalAlignment));
        map.insert("verticalAlignment",QString("%1").arg(m_verticalAlignment));
    }

    if(m_isInLanguage == true)
    {
        map.insert("isInlanguage", QString('1'));
    }

    if (m_strikeSize > 0)
    {
        map.insert("strikeSize", QString("%1").arg(m_strikeSize));

        if( m_strikeColor != QColor(Qt::black) )
        {
            map.insert("strikeColor_r", QString("%1").arg(m_strikeColor.red()));
            map.insert("strikeColor_g", QString("%1").arg(m_strikeColor.green()));
            map.insert("strikeColor_b", QString("%1").arg(m_strikeColor.blue()));
        }
    }

    return map;
}

QGraphicsItem* QCCLabelTTF::createGraphicsItem()
{
    m_graphicsItem = new QGraphicsPixmapItem();
    this->updateGraphicsItem();
    return m_graphicsItem;
}

void QCCLabelTTF::updateGraphicsItem()
{
    if(m_text.isEmpty() == true)
    {
        return ;
    }

    static bool isLanguageLoaded = false;
    if (isLanguageLoaded == false)
    {
        isLanguageLoaded = this->loadLanguageFile();
    }

    QString displayText = m_text;
    if( g_languages.count() > 0 )
    {
        displayText = g_languages.value(m_text, m_text);
    }

    if(displayText == m_text)
    {
        this->m_isInLanguage = false;
    }
    else
    {
        this->m_isInLanguage = true;
    }

    if(m_dimensionWith != 0 && m_dimensionHeight !=0 )
    {
        m_width = m_dimensionWith;
        m_height = m_dimensionHeight;
    }
    else
    {
        //QFontMetrics
        QFontMetrics metrics(m_font);
        m_width = metrics.width(displayText);
        m_height = metrics.height();
    }

    QImage image = QImage(m_width, m_height, QImage::Format_RGBA8888);
    image.fill(0);
    QPainter painter(&image);

    painter.setPen(QColor(m_color));
    painter.setFont(m_font);

    int horzArray[3] = {Qt::AlignLeft,Qt::AlignHCenter,Qt::AlignRight};
    int vertArray[3] = {Qt::AlignTop,Qt::AlignVCenter,Qt::AlignBottom};
    Qt::AlignmentFlag flag = (Qt::AlignmentFlag)(horzArray[m_horizontalAlignment] | vertArray[m_verticalAlignment]);
    QTextOption option = QTextOption(flag);
    option.setFlags( QTextOption::AddSpaceForLineAndParagraphSeparators | QTextOption::ShowLineAndParagraphSeparators);
    option.setWrapMode(QTextOption::WordWrap);
    painter.drawText(QRect(0,0,m_width,m_height), displayText, option);

    QGraphicsPixmapItem* item = dynamic_cast<QGraphicsPixmapItem*>(m_graphicsItem);
    item->setPixmap(QPixmap::fromImage(image));

    //item->setTransformOriginPoint(-m_width/2, -m_height/2);
    item->resetTransform();
    item->setTransform(QTransform().rotate(m_rotation), true);
    item->setTransform(QTransform::fromScale(m_scaleX,m_scaleY), true);
    item->setTransform(QTransform::fromTranslate(m_width*(0 - m_anchorX), m_height*(m_anchorY - 1.0)), true);

    item->setZValue(m_z);
    item->setVisible(m_isVisible);
    item->setFlag(QGraphicsItem::ItemIsMovable, !m_isFixed);
}

bool QCCLabelTTF::loadLanguageFile()
{
    QSettings settings("UIDesigner");
    QString fileDir = settings.value("resourceDir",QString("")).toString();

    QString filePath = QString("%1/language.lua").arg(fileDir);
    QFile file(filePath);
    if( file.open(QIODevice::ReadOnly) == false)
    {
        return false;
    }

    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    bool isRealLanguageFile = false;
    while( stream.atEnd() == false )
    {
        QString line = stream.readLine().trimmed();
        if(line.contains("language") == true && line.contains("=") )
        {
            isRealLanguageFile = true;
            g_languages.clear();
        }

        if(isRealLanguageFile == true)
        {
            if(line.count('[') == 1  && line.count(']') == 1 && line.count('=') == 1 && line.count('"') == 4 && line.contains(',') )
            {
                int index1 = line.indexOf('"');
                int index2 = line.indexOf('"', index1 + 1);
                int index3 = line.indexOf('=', index2 + 1);
                int index4 = line.indexOf('"', index3 + 1);
                int index5 = line.indexOf('"', index4 + 1);

                if( (index1 != -1) && (index2 != -1) && (index4 != -1) && (index5 != -1))
                {
                    QString key = line.mid(index1 + 1, index2 - index1 - 1);
                    QString value = line.mid(index4 + 1, index5 - index4 - 1);
                    g_languages.insert(key, value);
                }
            }
        }
    }

    file.close();
    return true;
}
