#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qabstracttreemodel.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QActionGroup* group = new QActionGroup(this);
    group->addAction(ui->actionRatio25);
    group->addAction(ui->actionRatio50);
    group->addAction(ui->actionRatio75);
    group->addAction(ui->actionRatio100);
    group->addAction(ui->actionRatio150);
    group->addAction(ui->actionRatio200);
    connect(group, SIGNAL(triggered(QAction*)), this, SLOT(on_actionRatio(QAction*)));
    m_viewRatio = 100;

    QHBoxLayout* boxLayout = new QHBoxLayout();
    boxLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
    this->centralWidget()->setLayout(boxLayout);

    m_treeView = new QTreeView();
    boxLayout->addWidget(m_treeView,2);

    m_scene = new QScene();
    m_scene->setBackgroundBrush(QBrush(QColor(Qt::black)));
    m_graphicsView = new QGraphicsView();
    m_graphicsView->setScene(m_scene);
    boxLayout->addWidget(m_graphicsView,3);

    m_browser = new QPropertyBrowser();
    boxLayout->addWidget(m_browser,2);

    m_storageData = new QStorageData();

    this->connectSignalAndSlot();

    m_model = 0;
    m_currentOpenFile.clear();
    m_copyBuffer.clear();

    //test
//    this->setSceneSize(9, 9);
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

//    this->replaceRootNode(root);

//    m_scene->test();
//    m_browser->test();
}

void MainWindow::replaceRootNode(QCCNode* node)
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
    m_scene->reset();
    this->setSceneSize(node->m_width, node->m_height);
    m_scene->createGraphicsItemByCCNode(node, 0);

    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex,const QVector<int>)), this, SLOT(dataChanged(const QModelIndex&,const QModelIndex&,const QVector<int>&)));

    //默认选中第一个
    m_treeView->setCurrentIndex( m_model->index(0,0) );
    this->viewClicked( m_model->index(0,0) );
//    m_treeView->setCurrentIndex( m_model->index(0,0) );
//    m_browser->initProperty(node);
}

void MainWindow::syncNodeAfterCreate(QModelIndex index, QCCNode* node)
{
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

QCCNode* MainWindow::currentSelectNode()
{
    QModelIndex index = m_treeView->selectionModel()->currentIndex();
    if(index != QModelIndex())
    {
        QTreeItem* treeItem = m_model->itemAt(index);
        QCCNode* node = treeItem->m_node;
        return node;
    }

    return 0;
}

void MainWindow::setSceneSize(int width, int height)
{
    m_graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //need +2, is a bug ?
    m_graphicsView->setFixedSize(width*m_viewRatio/100.0f, height*m_viewRatio/100.0f);
    m_graphicsView->setTransform(QTransform::fromScale(m_viewRatio/100.0f, m_viewRatio/100.0f), false);
    m_scene->setSceneRect(0, 0, width, height);
}

bool MainWindow::isCCSpriteCanBeCreate(QString filePath)
{
    if(filePath.isEmpty() == true)
    {
        return false;
    }

    QPixmap pixmap(filePath);
    if(pixmap.isNull() == true)
    {
        this->statusBar()->showMessage(QString("%1 not a picture.").arg(filePath));
        return false;
    }

    if(filePath.contains(m_storageData->resourceDir()) == false)
    {
        this->statusBar()->showMessage(QString("%1 out of Resource.").arg(filePath));
        return false;
    }

    return true;
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

    connect(this, SIGNAL(changeItemPoint(int,int)), m_scene, SLOT(changedItemPoint(int,int)));
    connect(this, SIGNAL(changeItemSelect(QCCNode*)), m_scene,SLOT(changedItemSelect(QCCNode*)));

    //property emit and window slot
    connect(m_browser, SIGNAL(changePropertyFixed(bool)), this, SLOT(changedPropertyFixed(bool)));
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

    connect(m_browser, SIGNAL(changePropertyAlignment(int, int)), this, SLOT(changedPropertyAlignment(int, int)));
    connect(m_browser, SIGNAL(changePropertyTextDimension(int, int)), this, SLOT(changedPropertyTextDimension(int, int)));

    connect(m_browser, SIGNAL(changePropertyCCContainerLayerFilePath(QString&)), this, SLOT(changedPropertyCCContainerLayerFilePath(QString&)));


    connect(this, SIGNAL(changePropertyPoint(int,int)), m_browser, SLOT(changedPropertyPoint(int,int)));
    connect(this, SIGNAL(changePropertySize(int,int)), m_browser, SLOT(changedPropertySize(int,int)));
}

//model slot;
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

            this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
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
        emit changeItemSelect(treeItem->m_node);
    }
}

void MainWindow::changedItemPoint(int x, int y)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_x = x;
        node->m_y = y;
        emit changePropertyPoint(x, y);
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

//property slot;
void MainWindow::changedPropertyFixed(bool fixed)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_isFixed = fixed;
        node->updateGraphicsItem();
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyPoint(int x, int y)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_x = x;
        node->m_y = y;
        emit changeItemPoint(x, y);
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyZ(int z)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_z = z;
        node->updateGraphicsItem();
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyTag(int tag)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_tag = tag;
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertySize(int width, int height)
{}

void MainWindow::changedPropertyAnchor(float anchorX, float anchorY)
{}

void MainWindow::changedPropertyScale(float scaleX, float scaleY)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_scaleX = scaleX;
        node->m_scaleY = scaleY;
        node->updateGraphicsItem();
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyRotation(int rotation)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_rotation = rotation;
        node->updateGraphicsItem();
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyVisible(bool visible)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_isVisible = visible;
        node->updateGraphicsItem();
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyTouchEnable(bool touchEnable)
{}

void MainWindow::changedPropertyColor(QColor& color)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCLayerColor* temp = dynamic_cast<QCCLayerColor*>(node);
        temp->m_color = color;
        temp->updateGraphicsItem();
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyOpacity(int opacity)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCLayerColor* temp = dynamic_cast<QCCLayerColor*>(node);
        temp->m_opacity = opacity;
        temp->updateGraphicsItem();
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyFilePath(QString& filePath)
{
    //check if a image.
    QPixmap pixmap(filePath);
    if(pixmap.isNull() == true)
    {
        //QMessageBox::warning(this,QString("warning"), QString("picture is null. %1").arg(filePath));
        this->statusBar()->showMessage( QString("picture is null. %1").arg(filePath) );
        return ;
    }
    else
    {
        this->statusBar()->showMessage(QString());
    }

    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCSprite* sprite = dynamic_cast<QCCSprite*>(node);
        QString relationFilePath = filePath;
        relationFilePath.remove( QString("%1/").arg(m_storageData->resourceDir()) );
        sprite->m_filePath = relationFilePath;
        sprite->updateGraphicsItem();
        emit changeItemSelect(node);
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyFont(QFont& font)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCLabelTTF* temp = dynamic_cast<QCCLabelTTF*>(node);
        temp->m_font = font;
        temp->updateGraphicsItem();
        emit changeItemSelect(node);
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyText(QString& text)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCLabelTTF* temp = dynamic_cast<QCCLabelTTF*>(node);
        temp->m_text = text;
        temp->updateGraphicsItem();
        emit changeItemSelect(node);
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyAlignment(int horizontal, int vertical)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCLabelTTF* temp = dynamic_cast<QCCLabelTTF*>(node);
        temp->m_horizontalAlignment = horizontal;
        temp->m_verticalAlignment = vertical;
        temp->updateGraphicsItem();
        emit changeItemSelect(node);
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyTextDimension(int width, int height)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCLabelTTF* temp = dynamic_cast<QCCLabelTTF*>(node);
        temp->m_dimensionWith = width;
        temp->m_dimensionHeight = height;
        temp->updateGraphicsItem();
        emit changeItemSelect(node);
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::changedPropertyCCContainerLayerFilePath(QString& filePath)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCContainerLayer* temp = dynamic_cast<QCCContainerLayer*>(node);

        //check if a container.
        QStorageData data;
        QCCNode* root = data.readUIFile(filePath);
        if(root != 0)
        {
            delete root;
            QString relationFilePath = filePath;
            relationFilePath.remove( QString("%1/").arg(m_storageData->resourceDir()) );
            temp->m_containerConfigFilePath = relationFilePath;
            temp->updateGraphicsItem();
            emit changeItemSelect(node);
            this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
        }
    }
}

void MainWindow::on_actionResource_triggered()
{
    QString oldDir = m_storageData->resourceDir();
    QString newDir = QFileDialog::getExistingDirectory(this, QString("Open Directory"), oldDir);
    m_storageData->setResourceDir(newDir);
}

void MainWindow::on_actionNew_triggered()
{
    QString openFile = QFileDialog::getSaveFileName(this, QString("New File"), m_storageData->resourceDir());
    if(openFile.isEmpty())
    {
        return ;
    }

    QSelectSizeDialog dialog;
    if(dialog.exec() == QDialog::Accepted)
    {
        if(dialog.m_rootClassType == CLASS_TYPE_CCSPRITE)
        {
            QString filePath = QFileDialog::getOpenFileName(this, QString("Open File"), m_storageData->resourceDir(),FILTER_IMAGES);
            if(this->isCCSpriteCanBeCreate(filePath) == false)
            {
                return;
            }

            QCCNode* node = QCCNode::createCCNodeByType(CLASS_TYPE_CCSPRITE);
            QCCSprite* sprite = dynamic_cast<QCCSprite*>(node);
            QImage image(filePath);
            sprite->m_filePath = filePath.remove(QString("%1/").arg(m_storageData->resourceDir()));
            QSize s = image.size();
            node->m_width = s.width();
            node->m_height = s.height();
            node->m_x = s.width()/2;
            node->m_y = s.height()/2;
            m_storageData->m_root = node;
            m_currentOpenFile = openFile;
            this->replaceRootNode(node);
            this->setWindowTitle(m_currentOpenFile);
        }
        else if(dialog.m_rootClassType == CLASS_TYPE_CCLAYER || dialog.m_rootClassType == CLASS_TYPE_CCLAYERCOLOR)
        {
            QCCNode* node = QCCNode::createCCNodeByType( dialog.m_rootClassType );
            node->m_width = dialog.m_width;
            node->m_height = dialog.m_height;
            node->m_x = 0;
            node->m_y = 0;
            m_storageData->m_root = node;
            m_currentOpenFile = openFile;
            this->replaceRootNode(node);
            this->setWindowTitle(m_currentOpenFile);
        }
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString oldDir = m_storageData->resourceDir();
    QString filePath = QFileDialog::getOpenFileName(this, QString("Open Directory"), oldDir, FILTER_CONFIG);
    QCCNode* node = m_storageData->readUIFile(filePath);
    if(node != 0)
    {
        m_currentOpenFile = filePath;
        this->replaceRootNode(node);
        this->setWindowTitle(m_currentOpenFile);
    }
    else
    {
        this->statusBar()->showMessage(QString("open file failed.  %1").arg(filePath));
    }
}

void MainWindow::on_actionSave_triggered()
{
    m_storageData->writeUIFile(m_currentOpenFile);
    this->setWindowTitle(m_currentOpenFile);
}

void MainWindow::on_actionSave_As_triggered()
{
    this->on_actionSave_triggered();
    this->setWindowTitle(m_currentOpenFile);

    QString filePath = QFileDialog::getSaveFileName(this, QString("Save As"), m_currentOpenFile, FILTER_CONFIG);
    if(filePath.isEmpty())
    {
        return ;
    }

    m_currentOpenFile = filePath;
    this->on_actionSave_triggered();
    this->setWindowTitle(m_currentOpenFile);
}

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
        QString oldName = node->m_name;
        node->importData(m_copyBuffer);
        QString newName = node->m_name;
        if(newName.contains("node") == false)
        {
            if(newName.contains("_") == true)
            {
                int index = newName.indexOf("_");
                QString last = newName.right(newName.size() - (index + 1));
                bool ok;
                int value = last.toInt(&ok);
                if(ok == true)
                {
                    newName = QString("%1_%2").arg(newName.left(index), value+1);
                }
            }

            node->m_name = newName;
        }
        else
        {
            node->m_name = oldName;
        }

        //sync
        this->syncNodeAfterCreate(index, node);

        this->statusBar()->showMessage("Parse ok");
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
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
            this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
        }
    }
}

void MainWindow::on_actionCCSprite_triggered()
{
    QModelIndex index = m_treeView->currentIndex();
    if(index.isValid() == true)
    {
        QString filePath = QFileDialog::getOpenFileName(this, QString("Open File"), m_storageData->resourceDir(), FILTER_IMAGES);
        if(this->isCCSpriteCanBeCreate(filePath) == false)
        {
            return;
        }

        //create
        QCCNode* node = QCCNode::createCCNodeByType(CLASS_TYPE_CCSPRITE);
        QCCSprite* sprite = dynamic_cast<QCCSprite*>(node);
        sprite->m_filePath = filePath.remove(QString("%1/").arg(m_storageData->resourceDir()));
        //sync
        this->syncNodeAfterCreate(index, node);
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::on_actionCCLabelTTF_triggered()
{
    QModelIndex index = m_treeView->currentIndex();
    if(index.isValid() == true)
    {
        //create
        QCCNode* node = QCCNode::createCCNodeByType(CLASS_TYPE_CCLABELTTF);
        //sync
        this->syncNodeAfterCreate(index, node);
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::on_actionCCMenu_triggered()
{
    QModelIndex index = m_treeView->currentIndex();
    if(index.isValid() == true)
    {
        QString filePath = QFileDialog::getOpenFileName(this, QString("Open File"), m_storageData->resourceDir(), FILTER_IMAGES);
        if(this->isCCSpriteCanBeCreate(filePath) == false)
        {
            return;
        }

        //create
        QCCNode* node = QCCNode::createCCNodeByType(CLASS_TYPE_CCMENUITEM_IMAGE);
        QCCSprite* sprite = dynamic_cast<QCCSprite*>(node);
        sprite->m_filePath = filePath.remove(QString("%1/").arg(m_storageData->resourceDir()));
        //sync
        this->syncNodeAfterCreate(index, node);
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::on_actionCContainer_triggered()
{
    QModelIndex index = m_treeView->currentIndex();
    if(index.isValid() == true)
    {
        QString filePath = QFileDialog::getOpenFileName(this, QString("Open File"), m_storageData->resourceDir(), FILTER_CONFIG);

        //create
        QCCNode* node = QCCNode::createCCNodeByType(CLASS_TYPE_CCCONTAINERLAYER);
        QCCContainerLayer* layer = dynamic_cast<QCCContainerLayer*>(node);
        layer->m_containerConfigFilePath = filePath.remove(QString("%1/").arg(m_storageData->resourceDir()));
        //sync
        this->syncNodeAfterCreate(index, node);
        this->setWindowTitle(QString("%1*").arg(m_currentOpenFile));
    }
}

void MainWindow::on_actionRatio(QAction* action)
{
    QString str = action->text();
    m_viewRatio = str.remove("%").toInt();

    if(m_currentOpenFile.isEmpty() == false)
    {
        int width = m_scene->width();
        int height = m_scene->height();
        this->setSceneSize(width, height);
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QString title = this->windowTitle();
    if(title.right(1) == "*")
    {
        QMessageBox msgBox;
        msgBox.setText("The document has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        if(ret == QMessageBox::Save)
        {
            this->on_actionSave_triggered();
        }
        else if(ret == QMessageBox::Cancel)
        {
            event->ignore();
            return ;
        }
    }

    QMainWindow::closeEvent(event);
}
