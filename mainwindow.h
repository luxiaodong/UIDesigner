#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qabstracttreemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    //model;
    //scene;
    //property;

public slots:
    //model slot;
    //scene slot;
    //property slot;


private:
    QHBoxLayout*        m_hBoxLayout;
    QTreeView*          m_treeView;
    QGraphicsView*      m_graphicsView;
    QGraphicsScene*     m_graphicsScene;

    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
