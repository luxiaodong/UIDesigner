#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qabstracttreemodel.h"
#include <QDebug>

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

    m_storageData = new QStorageData();

    this->connectSignalAndSlot();

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

void MainWindow::connectSignalAndSlot()
{
    //model emit and window slot;
    connect(m_treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(viewClicked(const QModelIndex&)));

    //scene emit and window slot;
    connect(m_scene, SIGNAL(changeItemPoint(int,int)),this,SLOT(changedItemPoint(int,int)));

    //property emit and window slot
    connect(m_browser, SIGNAL(changePropertyPoint(int,int)), this, SLOT(changedPropertyPoint(int,int)));
    connect(m_browser, SIGNAL(changePropertyZ(int)), this, SLOT(changedPropertyZ(int)));
    connect(m_browser, SIGNAL(changePropertyTag(int)), this, SLOT(changedPropertyTag(int)));
    connect(m_browser, SIGNAL(changePropertySize(int,int)), this, SLOT(changedPropertySize(int,int)));
    connect(m_browser, SIGNAL(changePropertyAnchor(float,float)), this, SLOT(changedPropertyAnchor(float,float)));
    connect(m_browser, SIGNAL(changePropertyScale(float,float)), this, SLOT(changedPropertyScale(float,float)));
    connect(m_browser, SIGNAL(changePropertyRotation(int)), this, SLOT(changedPropertyRotation(int)));
    connect(m_browser, SIGNAL(changePropertyVisible(bool)), this, SLOT(changedPropertyVisible(bool)));
    connect(m_browser, SIGNAL(changePropertyTouchEnable(bool)), this, SLOT(changedPropertyTouchEnable(bool)));
    connect(m_browser, SIGNAL(changePropertyColor(QColor&)), this, SLOT(changedPropertyColor(QColor&)));
    connect(m_browser, SIGNAL(changePropertyOpacity(int)), this, SLOT(changedPropertyOpacity(int)));
    connect(m_browser, SIGNAL(changePropertyFilePath(QString&)), this, SLOT(changedPropertyFilePath(QString&)));
    connect(m_browser, SIGNAL(changePropertyFont(QFont&)), this, SLOT(changedPropertyFont(QFont&)));
    connect(m_browser, SIGNAL(changePropertyText(QString&)), this, SLOT(changedPropertyText(QString&)));

    connect(this, SIGNAL(changePropertyPoint(int,int)), m_browser, SLOT(changedPropertyPoint(int,int)));
}

//model slot;
void MainWindow::viewClicked(const QModelIndex& index)
{
    if (index.column() == 0)
    {
        QStringList path;
        QModelIndex parent = current.parent();
    }

    //要考虑parent.
    qDebug()<<index.data().toString();
    qDebug()<<index.column()<<index.row();
}

//scene slot;
void MainWindow::changedItemPoint(int x, int y)
{
    qDebug()<<"item "<<x<<y;
    //save x,y
    //emit to item for change
    emit changePropertyPoint(x, y);
}

//property slot;
void MainWindow::changedPropertyPoint(int x, int y)
{
    qDebug()<<"property "<<x<<y;
    //save x,y;
    //emit to item for change
}

void MainWindow::changedPropertyZ(int z)
{}

void MainWindow::changedPropertyTag(int tag)
{}

void MainWindow::changedPropertySize(int width, int height)
{}

void MainWindow::changedPropertyAnchor(float anchorX, float anchorY)
{}

void MainWindow::changedPropertyScale(float scaleX, float scaleY)
{}

void MainWindow::changedPropertyRotation(int rotation)
{}

void MainWindow::changedPropertyVisible(bool visible)
{}

void MainWindow::changedPropertyTouchEnable(bool touchEnable)
{}

void MainWindow::changedPropertyColor(QColor& color)
{}

void MainWindow::changedPropertyOpacity(int opacity)
{}

void MainWindow::changedPropertyFilePath(QString& filePath)
{}

void MainWindow::changedPropertyFont(QFont& font)
{}

void MainWindow::changedPropertyText(QString& text)
{}

