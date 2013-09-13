#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qabstracttreemodel.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVector<QVariant> data;
    data.append(QString("name"));
    data.append(QString(CLASS_TYPE_ROOT));

    QVector<QVariant> temp1;
    temp1.append(QString("xxx"));
    temp1.append(QString(CLASS_TYPE_CCLAYER));

    QTreeItem* node = new QTreeItem(data);

    node->insertChildren(0, 1, 2);
    node->insertChildren(0, 1, 2);
    node->child(0)->setData(0, QString("xxx"));
    node->child(0)->setData(1, QString(CLASS_TYPE_CCLAYER));
    node->child(1)->setData(0, QString("xxxx"));
    node->child(1)->setData(1, QString(CLASS_TYPE_CCLABELTTF));

    node->child(0)->insertChildren(0,1,2);
    node->child(0)->insertChildren(0,1,2);
    node->child(0)->child(0)->setData(0, QString("xxxxx"));
    node->child(0)->child(0)->setData(1, QString(CLASS_TYPE_CCLAYER));
    node->child(0)->child(1)->setData(0, QString("xxxxxxx"));
    node->child(0)->child(1)->setData(1, QString(CLASS_TYPE_CCSPRITE));

    QHBoxLayout* boxLayout = new QHBoxLayout();
    boxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    this->centralWidget()->setLayout(boxLayout);

    m_treeView = new QTreeView();
    QAbstractTreeModel* model = new QAbstractTreeModel(node);
    m_treeView->setModel(model);
    boxLayout->addWidget(m_treeView,2);

    m_scene = new QScene();
    m_scene->setBackgroundBrush(QBrush(QColor(Qt::black)));
    m_graphicsView = new QGraphicsView();
    m_graphicsView->setScene(m_scene);
    boxLayout->addWidget(m_graphicsView,4);

    m_browser = new QPropertyBrowser();
    boxLayout->addWidget(m_browser,3);

    //test
    this->setSceneSize(300, 300);
    this->test();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    m_scene->test();
    m_browser->test();
}

void MainWindow::setSceneSize(int width, int height)
{
    if(width > 1136)
    {
        m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        width = 1136;
    }
    else
    {
        m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    if(height > 1136)
    {
        m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        height = 1136;
    }
    else
    {
        m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    m_graphicsView->setFixedSize(width, height);
    m_scene->setSceneRect(0, 0, width, height);
}


