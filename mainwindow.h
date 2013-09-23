#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

signals:
    //view;
    //scene;
    void changeItemSelect(QStringList& list);

    //property;
    void changePropertyPoint(int x, int y);

public slots:
    //view slot;
    void viewActivated(const QModelIndex& index);
    void viewClicked(const QModelIndex& index);
    void viewDoubleClicked(const QModelIndex& index);
    void viewEntered(const QModelIndex& index);
    void viewPressed(const QModelIndex & index);

    //model slot;
    void dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight, const QVector<int> & roles);

    //scene slot;
    void changedItemPoint(int x, int y);

    //property slot;
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

private slots:
    void on_actionResource_triggered();

private:
    QTreeView*          m_treeView;
    QGraphicsView*      m_graphicsView;
    QAbstractTreeModel* m_model;
    QScene*             m_scene;
    QPropertyBrowser*   m_browser;
    QStorageData*       m_storageData;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
