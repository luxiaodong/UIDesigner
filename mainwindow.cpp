#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qabstracttreemodel.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),m_model(0)
{
    ui->setupUi(this);

    QHBoxLayout* boxLayout = new QHBoxLayout();
    boxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    this->centralWidget()->setLayout(boxLayout);

    m_treeView = new QTreeView();
    boxLayout->addWidget(m_treeView,20);

    m_scene = new QScene();
    m_scene->setBackgroundBrush(QBrush(QColor(Qt::black)));
    m_graphicsView = new QGraphicsView();
    m_graphicsView->setScene(m_scene);
    boxLayout->addWidget(m_graphicsView,20);

    m_browser = new QPropertyBrowser();
    boxLayout->addWidget(m_browser,3);

    m_storageData = new QStorageData();

    this->connectSignalAndSlot();

    m_currentOpenFile.clear();
    m_copyBuffer.clear();

    //test
//    this->setSceneSize(300, 300);
//    this->test();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test()
{
    QCCNode* root = new QCCNode();
    QCCNode* node1 = new QCCNode();
    QCCNode* node11 = new QCCNode();
    QCCNode* node12 = new QCCNode();
    QCCNode* node2 = new QCCNode();

    root->m_name = "name_1";
    root->m_classType = "class_1";
    node1->m_name = "1";
    node11->m_name = "11";
    node12->m_name = "12";
    node2->m_name = "2";

    node1->m_classType = CLASS_TYPE_CCSPRITE;
    node11->m_classType = CLASS_TYPE_CCSPRITE;
    node12->m_classType = CLASS_TYPE_CCSPRITE;
    node2->m_classType = CLASS_TYPE_CCSPRITE;

    root->m_children.append(node1);
    root->m_children.append(node2);

    node1->m_children.append(node11);
    node1->m_children.append(node12);

    this->replaceTreeModel(root);

    m_scene->test();
    m_browser->test();
}

void MainWindow::replaceTreeModel(QCCNode* node)
{
    if(m_model != 0)
    {
        delete m_model;
    }

    QVector<QVariant> data;
    data.append(QString("name"));
    data.append(QString(CLASS_TYPE_ROOT));
    QTreeItem* item = new QTreeItem(data);
    //item->m_node = node; //first is cclayer, not displayed. can be 0.

    m_model = new QAbstractTreeModel();
    m_model->setRoot(item);
    m_treeView->setModel(m_model);

    //not clear the root relation between, ccnode, cctreeitem.
    m_model->createTreeItemByCCNode(node, QModelIndex());

    //must set scene size first.
    this->setSceneSize(node->m_parent->m_width, node->m_parent->m_height);
    m_scene->createGraphicsItemByCCNode(node, 0);

    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,const QVector<int>)), this, SLOT(dataChanged(const QModelIndex&,const QModelIndex&,const QVector<int>&)));

    //默认选中第一个
    m_treeView->setCurrentIndex( m_model->index(0,0) );
}

QModelIndex MainWindow::searchIndex(QModelIndex parentIndex, QGraphicsItem* item)
{
    QTreeItem* items = m_model->itemAt(parentIndex);
    for(int i=0; i < items->m_children.size(); ++i)
    {
        QTreeItem* treeItem = items->m_children.at(i);
        if(treeItem->m_node != 0)
        {
            QModelIndex currentIndex = m_model->index(i, 0, parentIndex);

            if(treeItem->m_node->m_graphicsItem == item)
            {
                return currentIndex;
            }

            if( treeItem->m_children.size() > 0 )
            {
                QModelIndex subIndex = this->searchIndex(currentIndex, item);
                if(subIndex != QModelIndex())
                {
                    return subIndex;
                }
            }
        }
    }

    return QModelIndex();
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
    //view emit and window slot;
    //connect(m_treeView, SIGNAL(activated(QModelIndex)), this, SLOT(viewActivated(const QModelIndex&)));
    connect(m_treeView, SIGNAL(clicked(QModelIndex)), this, SLOT(viewClicked(const QModelIndex&)));
    //connect(m_treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(viewDoubleClicked(const QModelIndex&)));
    //connect(m_treeView, SIGNAL(entered(QModelIndex)), this, SLOT(viewEntered(const QModelIndex&)));
    //connect(m_treeView, SIGNAL(pressed(QModelIndex)), this, SLOT(viewPressed(const QModelIndex&)));


    //scene emit and window slot;
    connect(m_scene, SIGNAL(showMessage(QString)), this->statusBar(), SLOT(showMessage(QString)));
    connect(m_scene, SIGNAL(changeItemSelect(QGraphicsItem*)), this, SLOT(changedItemSelect(QGraphicsItem*)));
    connect(m_scene, SIGNAL(changeItemPoint(int,int)),this,SLOT(changedItemPoint(int,int)));

    connect(this, SIGNAL(changeItemSelect(QCCNode*)), m_scene,SLOT(changedItemSelect(QCCNode*)));


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
void MainWindow::viewActivated(const QModelIndex& index)
{
    qDebug()<<"viewActivated "<<index.data().toString();
}

void MainWindow::viewDoubleClicked(const QModelIndex& index)
{
    qDebug()<<"viewDoubleClicked "<<index.data().toString();
}

void MainWindow::viewEntered(const QModelIndex& index)
{
    qDebug()<<"viewEntered "<<index.data().toString();
}

void MainWindow::viewPressed(const QModelIndex & index)
{
    qDebug()<<"viewPressed "<<index.data().toString();
}

void MainWindow::viewClicked(const QModelIndex& index)
{
    if (index.column() == 0)
    {
        QTreeItem* item = m_model->itemAt(index);
        emit changeItemSelect(item->m_node);
        m_browser->initProperty(item->m_node);
    }
}

//model slot
void MainWindow::dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight, const QVector<int> & roles)
{
    if(topLeft == bottomRight)
    {
        if(topLeft.column() == 0)
        {
            int rowCount = m_model->rowCount(topLeft.parent());
            bool isConflict = false;
            for(int i =0; i < rowCount; ++i)
            {
                QModelIndex index = m_model->index(i,0,topLeft.parent());
                if(index != topLeft)
                {
                    if(index.data().toString() == topLeft.data().toString())
                    {
                        isConflict = true;
                        break;
                    }
                }
            }

            //名字有冲突
            if(isConflict == true)
            {
                //QMessageBox::warning(this,"warning",QString("the same name\n%1").arg(topLeft.data().toString()));
                return ;
            }

            QTreeItem* treeItem = m_model->itemAt(topLeft);
            treeItem->m_node->m_name = topLeft.data().toString();
            //先该底层的数据,再改上层的东西
        }
    }
}

//scene slot;
void MainWindow::changedItemSelect(QGraphicsItem* item)
{
    QModelIndex index = this->searchIndex(QModelIndex(), item);
    if(index != QModelIndex())
    {
        m_treeView->setCurrentIndex(index);
        QTreeItem* treeItem = m_model->itemAt(index);
        m_browser->initProperty(treeItem->m_node);
    }

    //属性更新
    //iter for search item.
    //ma fan le.
}

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

void MainWindow::on_actionResource_triggered()
{
    QString oldDir = m_storageData->resourceDir();
    QString newDir = QFileDialog::getExistingDirectory(this, QString("Open Directory"), oldDir);
    m_storageData->setResourceDir(newDir);
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString oldDir = m_storageData->resourceDir();
    QString filePath = QFileDialog::getOpenFileName(this, QString("Open Directory"), oldDir);
    QCCNode* node = m_storageData->readUIFile(filePath);
    if(node != 0)
    {
        m_currentOpenFile = filePath;
        this->replaceTreeModel(node->m_children.at(0));
    }
}

void MainWindow::on_actionSave_triggered()
{
    m_storageData->writeUIFile(m_currentOpenFile);
}

//这里要api细分,独立创建,树更新,设置数据,选择等操作, copy的时候应该 copy整个树
//创建和删除核心的程序,应该只有一个.保证树的正确和内部内存的正确
//代码需要重构了
void MainWindow::on_actionCCSprite_triggered()
{
    QModelIndex index = m_treeView->currentIndex();
    if(index.isValid() == true)
    {
        //create
        QCCNode* node = QCCNode::createCCNodeByType(CLASS_TYPE_CCSPRITE);
        //sync
        QCCNode* parentNode = m_model->itemAt(index)->m_node;
        parentNode->m_children.append(node);
        node->m_parent = parentNode;

        disconnect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,const QVector<int>)), this, SLOT(dataChanged(const QModelIndex&,const QModelIndex&,const QVector<int>&)));

        //add to treeItem
        m_model->createTreeItemByCCNode(node, index);
        m_scene->createGraphicsItemByCCNode(node, parentNode->m_graphicsItem);

        connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,const QVector<int>)), this, SLOT(dataChanged(const QModelIndex&,const QModelIndex&,const QVector<int>&)));

        //更换当前选择
        this->viewClicked( m_model->index( m_model->rowCount(index) - 1 , 0, index) );

        //qDebug()<<index.data();
    }
}

//is need copy all children, en, copy all children can process at save doc.
void MainWindow::on_actionCopy_triggered()
{
    QModelIndex index = m_treeView->currentIndex();
    if(index.isValid() == true)
    {
        QTreeItem* item = m_model->itemAt(index);
        m_copyBuffer = item->m_node->exportData();
        this->statusBar()->showMessage("copy ok");
    }
}

void MainWindow::on_actionParse_triggered()
{
    QModelIndex index = m_treeView->currentIndex();
    if(index.isValid() == true)
    {
        if(m_copyBuffer.isEmpty() == true)
        {
            return ;
        }

        QString classType = m_copyBuffer.value("classType", QString(""));
        Q_ASSERT(classType.isEmpty() == false);

        //create and sync
        QCCNode* node = QCCNode::createCCNodeByType(classType);
        node->importData(m_copyBuffer);

        QCCNode* parentNode = m_model->itemAt(index)->m_node;
        parentNode->m_children.append(node);
        node->m_parent = parentNode;

        //add to treeItem
        m_model->createTreeItemByCCNode(node, index);
        m_scene->createGraphicsItemByCCNode(node, parentNode->m_graphicsItem);

        //is need 更换当前选择
        //this->viewClicked( m_model->index( m_model->rowCount(index) - 1 , 0, index) );

        this->statusBar()->showMessage("Parse ok");
    }
}

void MainWindow::on_actionDel_triggered()
{
    QModelIndex index = m_treeView->currentIndex();
    if(index.isValid() == true)
    {
        if( QMessageBox::question(this,"delete",QString("remove this and all children")) ==  QMessageBox::Yes)
        {
            int rowIndex = index.row();
            QCCNode* node = m_model->itemAt(index)->m_node;

            //1. remove from model.
            m_model->removeRows(rowIndex, 1, index.parent());

            //2. remove from scene.
            m_scene->removeItem(node->m_graphicsItem);

            //3. remove from data.
            if(node->m_parent != 0)
            {
                node->m_parent->m_children.removeAt(rowIndex);
            }

            delete node;
        }
    }
}
