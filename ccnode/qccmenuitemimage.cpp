#include "qccmenuitemimage.h"
#include <QSettings>
#include <QFile>

QCCMenuItemImage::QCCMenuItemImage()
{
}

void QCCMenuItemImage::importData(QMap<QString, QString>& map)
{
    QCCLayerColor::importData(map);
    QString shortPath = map.value("filePath", QString(""));

    if(shortPath.isEmpty() == true)
    {
        shortPath = map.value("image_n", QString(""));
    }

    if(shortPath.contains("/"))
    {
        m_filePath = shortPath;
    }
    else
    {
        m_filePath = this->shortPathToLongPath(shortPath);
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

    //map.insert("image_n", image_n);

    QString shortPath = this->longPathToShortPath(image_n);
    map.insert("image_n", shortPath);

    if(QFile::exists(abs_image_p) == true)
    {
        shortPath = this->longPathToShortPath(image_p);
        map.insert("image_p", shortPath);
    }

    if(QFile::exists(abs_image_d) == true)
    {
        shortPath = this->longPathToShortPath(image_d);
        map.insert("image_d", shortPath);
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
