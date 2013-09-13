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

    m_hBoxLayout = new QHBoxLayout();
    m_hBoxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    this->centralWidget()->setLayout(m_hBoxLayout);

    m_treeView = new QTreeView();
    m_treeView->setMinimumWidth(100);
    m_hBoxLayout->addWidget(m_treeView,2);

    QAbstractTreeModel* model = new QAbstractTreeModel(node);
    m_treeView->setModel(model);

    m_graphicsScene = new QGraphicsScene();
    m_graphicsView = new QGraphicsView();
    m_graphicsView->setMinimumWidth(200);
    m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //m_graphicsView->setBackgroundBrush(QBrush(QColor(Qt::black)));
    m_graphicsView->setScene(m_graphicsScene);
    m_hBoxLayout->addWidget(m_graphicsView,4);


    //m_graphicsScene->setSceneRect(0,0,200,200);
    //m_graphicsScene->setBackgroundBrush(QBrush(QColor(Qt::black)));
    m_graphicsScene->addRect(50,50,50,50,QPen(Qt::red));
    m_graphicsView->setFixedSize(200, 200);
    m_graphicsView->setSceneRect(0,0,200,200);

    //m_hBoxLayout->addWidget(m_browser,3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

