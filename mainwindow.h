#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qabstracttreemodel.h"
#include "qscene.h"

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
    void setSceneSize(int width, int height);

signals:
    //model;
    //scene;
    //property;

public slots:
    //model slot;
    //scene slot;
    //property slot;

private:
    QTreeView*          m_treeView;
    QGraphicsView*      m_graphicsView;
    QScene*             m_scene;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
