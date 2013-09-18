#ifndef QSCENE_H
#define QSCENE_H

#include "qdefine.h"

//少了一个切换select的item
class QScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QScene();

public:
    void test();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:
    void changeItemPoint(int x, int y);

public slots:
    void changedItemPoint(int x, int y);
    void changedItemZ(int z);
    void changedItemSize(int width, int height);
    void changedItemAnchor(float anchorX, float anchorY);
    void changedItemScale(float scaleX, float scaleY);
    void changedItemRotation(int rotation);
    void changedItemVisible(bool visible);
    void changedItemTouchEnable(bool touchEnable);
    void changedItemColor(QColor& color);
    void changedItemOpacity(int opacity);
    void changedItemFilePath(QString& filePath);
    void changedItemFont(QFont& font);
    void changedItemText(QString& text);

private:
    QGraphicsItem* m_selectItem;
};

#endif // QSCENE_H
