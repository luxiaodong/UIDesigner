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

    this->setSceneSize(300, 300);

    //m_hBoxLayout->addWidget(m_browser,3);
    this->test();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    QGraphicsRectItem* r1 = m_scene->addRect(-25,-25,50,50,QPen(Qt::red),QBrush(QColor(Qt::red)));
    QGraphicsRectItem* r2 = m_scene->addRect(-100,-100,200,200,QPen(Qt::green), QBrush(QColor(Qt::green)));
    QGraphicsRectItem* r3 = new QGraphicsRectItem(-25,-25,50,50, r2);

    r1->setData(1, "r1");
    //r1->setFlag(QGraphicsItem::ItemIsMovable, true);

    r2->setPos(125,125);
    r2->setData(1, "r2");
    //r2->setFlag(QGraphicsItem::ItemIsSelectable, true);
    r2->setFlag(QGraphicsItem::ItemIsMovable, true);

    r3->setPos(100,100);
    r3->setBrush(QBrush(QColor(Qt::blue)));
    r3->setData(1, "r3");
    r3->setFlag(QGraphicsItem::ItemIsMovable, true);
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


