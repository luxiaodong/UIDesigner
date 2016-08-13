#include "qccmenuitemimage.h"
#include <QSettings>
#include <QFile>

QCCMenuItemImage::QCCMenuItemImage()
{
}

void QCCMenuItemImage::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    m_filePath = map.value("filePath", QString(""));

    if(m_filePath.isEmpty() == true)
    {
        m_filePath = map.value("image_n", QString(""));
    }
}

QMap<QString, QString> QCCMenuItemImage::exportData()
{
    QMap<QString, QString> map = QCCLayerColor::exportData();

    QString image_n = m_filePath;
    QString image_p = m_filePath;
    QString image_d = m_filePath;

    image_p.replace("_n.png", "_p.png");
    image_d.replace("_n.png", "_d.png");

    QSettings settings("UIDesigner");
    QString resourceDir = settings.value("resourceDir",QString("")).toString();

    QString abs_image_p = QString("%1/%2").arg(resourceDir, image_p);
    QString abs_image_d = QString("%1/%2").arg(resourceDir, image_d);

    map.insert("image_n", image_n);

    if(QFile::exists(abs_image_p) == true)
    {
        map.insert("image_p", image_p);
    }

    if(QFile::exists(abs_image_d) == true)
    {
        map.insert("image_d", image_d);
    }

    return map;
}

QGraphicsItem* QCCMenuItemImage::createGraphicsItem()
{
    return QCCSprite::createGraphicsItem();
}

void QCCMenuItemImage::updateGraphicsItem()
{
    return QCCSprite::updateGraphicsItem();
}
