#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qselectsizedialog.h"
#include "qabstracttreemodel.h"
#include "qscene.h"
#include "qpropertybrowser.h"
#include "qstoragedata.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void test();

private:
    void setSceneSize(int width, int height);
    void connectSignalAndSlot();

private:
    void replaceRootNode(QCCNode* root);
    void syncNodeAfterCreate(QModelIndex index, QCCNode* node);
    QModelIndex searchIndex(QModelIndex parentIndex,QGraphicsItem* item);
    QCCNode* currentSelectNode();

private:
    bool isCCSpriteCanBeCreate(QString filePath);

signals:
    //view;
    //scene;
    void changeItemSelect(QCCNode* node);
    void changeItemPoint(int x, int y);

    //property;
    void changePropertyPoint(int x, int y);
    void changePropertySize(int width, int height);

public slots:
    //view slot;
    void viewClicked(const QModelIndex& index);

    //model slot;
    void dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight, const QVector<int> & roles);

    //scene slot;
    void changedItemSelect(QGraphicsItem* item);
    void changedItemPoint(int x, int y);

    //property slot;
    void changedPropertyFixed(bool fixed);
    void changedPropertyPoint(int x, int y);
    void changedPropertyZ(int z);
    void changedPropertyTag(int tag);
    void changedPropertySize(int width, int height);
    void changedPropertyAnchor(float anchorX, float anchorY);
    void changedPropertyScale(float scaleX, float scaleY);
    void changedPropertyRotation(int rotation);
    void changedPropertyVisible(bool visible);
    void changedPropertyTouchEnable(bool touchEnable);
    void changedPropertyColor(QColor& color);
    void changedPropertyOpacity(int opacity);
    void changedPropertyFilePath(QString& filePath);
    void changedPropertyFont(QFont& font);
    void changedPropertyText(QString& text);
    void changedPropertyAlignment(int horizontal, int vertical);
    void changedPropertyTextDimension(int width, int height);
    void changedPropertyCCContainerLayerFilePath(QString& filePath);

private slots:
    void on_actionRatio(QAction*);
    void on_actionResource_triggered();
    void on_actionNew_triggered();
    void on_actionOpen_File_triggered();
    void on_actionSave_triggered();
    void on_actionSave_As_triggered();
    void on_actionCopy_triggered();
    void on_actionParse_triggered();
    void on_actionDel_triggered();
    void on_actionCCSprite_triggered();
    void on_actionCCLabelTTF_triggered();
    void on_actionCCMenu_triggered();
    void on_actionCContainer_triggered();

protected:
    virtual void closeEvent(QCloseEvent *event);

private:
    QTreeView*          m_treeView;
    QGraphicsView*      m_graphicsView;
    QAbstractTreeModel* m_model;
    QScene*             m_scene;
    QPropertyBrowser*   m_browser;
    QStorageData*       m_storageData;

private:
    QString             m_currentOpenFile;
    QString             m_lastBrowserFile;
    QMap<QString, QString> m_copyBuffer;
    int                 m_viewRatio;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
