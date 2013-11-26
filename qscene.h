#ifndef QSCENE_H
#define QSCENE_H

#include "qdefine.h"
#include "qccnode.h"

#define GRAPHICS_ITEM_NAME_TAG  1
#define GRAPHICS_ITEM_CLASS_TAG  2

//少了一个切换select的item
class QScene : public QGraphicsScene
{
    Q_OBJECT
public:
    QScene();

public:
    void test();
    void createGraphicsItemByCCNode(QCCNode* node, QGraphicsItem* parentItem);
    void changeSimpleTextItemBounding();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:
    void showMessage(QString msg);
    void changeItemSelect(QGraphicsItem* item);
    void changeItemPoint(int x, int y);

public slots:
    void changedItemSelect(QCCNode* node);

//应该机制改掉, 改成传CCNode. 然后qccnode那边分解创建和初始化,然后这边直接调用初始化更新
    void changedItemFixed(bool);
    void changedItemPoint(int x, int y);
    void changedItemZ(int z);
    void changedItemSize(int width, int height);
    void changedItemAnchor(float anchorX, float anchorY);
    void changedItemScaleAndRotation(float scaleX, float scaleY, int rotation);
    void changedItemVisible(bool visible);
    void changedItemTouchEnable(bool touchEnable);
    void changedItemColor(QColor&, QString&);
    void changedItemOpacity(int opacity);
    void changedItemFilePath(QString& filePath);
    void changedItemFont(QFont& font);
    void changedItemText(QString& text);

private:
    QGraphicsItem* m_selectItem;
    QGraphicsRectItem* m_boundingRect;
};

#endif // QSCENE_H
