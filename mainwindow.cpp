#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qabstracttreemodel.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
    m_scene->clear();
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

    //need +2, is a bug ?
    m_graphicsView->setFixedSize(width, height);
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

    connect(this, SIGNAL(changeItemSelect(QCCNode*)), m_scene,SLOT(changedItemSelect(QCCNode*)));
    connect(this, SIGNAL(changeItemFixed(bool)), m_scene, SLOT(changedItemFixed(bool)));
    connect(this, SIGNAL(changeItemPoint(int, int)), m_scene,SLOT(changedItemPoint(int, int)));
    connect(this, SIGNAL(changeItemZ(int)), m_scene, SLOT(changedItemZ(int)));
    connect(this, SIGNAL(changeItemScaleAndRotation(float,float,int)), m_scene, SLOT(changedItemScaleAndRotation(float,float,int)));
    connect(this, SIGNAL(changeItemColor(QColor&, QString&)), m_scene, SLOT(changedItemColor(QColor&, QString&)));
    connect(this, SIGNAL(changeItemOpacity(int)), m_scene, SLOT(changedItemOpacity(int)));
    connect(this, SIGNAL(changeItemVisible(bool)), m_scene, SLOT(changedItemVisible(bool)));
    connect(this, SIGNAL(changeItemFilePath(QString&)), m_scene,SLOT(changedItemFilePath(QString&)));
    connect(this, SIGNAL(changeItemFont(QFont&)), m_scene,SLOT(changedItemFont(QFont&)));
    connect(this, SIGNAL(changeItemText(QString&)), m_scene,SLOT(changedItemText(QString&)));

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

    connect(m_browser, SIGNAL(changePropertyTextAlignment(int, int)), this, SLOT(changedPropertyTextAlignment(int, int)));
    connect(m_browser, SIGNAL(changePropertyTextDimension(int, int)), this, SLOT(changedPropertyTextDimension(int, int)));

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
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_x = x;
        node->m_y = y;
        emit changePropertyPoint(x, y);
    }
}

//property slot;
void MainWindow::changedPropertyFixed(bool fixed)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_isFixed = fixed;
        emit changeItemFixed(fixed);
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
    }
}

void MainWindow::changedPropertyZ(int z)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_z = z;
        emit changeItemZ(z);
    }
}

void MainWindow::changedPropertyTag(int tag)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_tag = tag;
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
        emit changeItemScaleAndRotation(scaleX, scaleY, node->m_rotation);
    }
}

void MainWindow::changedPropertyRotation(int rotation)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_rotation = rotation;
        emit changeItemScaleAndRotation(node->m_scaleX, node->m_scaleY, rotation);
    }
}

void MainWindow::changedPropertyVisible(bool visible)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        node->m_isVisible = visible;
        emit changeItemVisible(visible);
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
        emit changeItemColor(color, node->m_classType);
    }
}

void MainWindow::changedPropertyOpacity(int opacity)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCLayerColor* temp = dynamic_cast<QCCLayerColor*>(node);
        temp->m_opacity = opacity;
        emit changeItemOpacity(opacity);
    }
}

void MainWindow::changedPropertyFilePath(QString& filePath)
{
    //check if a image.
    QPixmap pixmap(filePath);
    if(pixmap.isNull() == true)
    {
        QMessageBox::warning(this,QString("warning"), QString("picture is null. %1").arg(filePath));
        return ;
    }

    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCSprite* sprite = dynamic_cast<QCCSprite*>(node);
        QString relationFilePath = filePath;
        relationFilePath.remove( QString("%1/").arg(m_storageData->resourceDir()) );
        sprite->m_filePath = relationFilePath;
        QSize s = pixmap.size();
        sprite->m_width = s.width();
        sprite->m_height = s.height(); //send message to property width & height.
        emit changeItemFilePath(filePath);
    }
}

void MainWindow::changedPropertyFont(QFont& font)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCLabelTTF* temp = dynamic_cast<QCCLabelTTF*>(node);
        temp->m_font = font;
        emit changeItemFont(font);
    }
}

void MainWindow::changedPropertyText(QString& text)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCLabelTTF* temp = dynamic_cast<QCCLabelTTF*>(node);
        temp->m_text = text;
        emit changeItemText(text);
    }
}

void MainWindow::changedPropertyTextAlignment(int horizontal, int vertical)
{
    QCCNode* node = this->currentSelectNode();
    if(node != 0)
    {
        QCCLabelTTF* temp = dynamic_cast<QCCLabelTTF*>(node);
        temp->m_horizontalTextAlignment = horizontal;
        temp->m_verticalTextAlignment = vertical;
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
            QString filePath = QFileDialog::getOpenFileName(this, QString("Open File"), m_storageData->resourceDir());
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
        }
        else if(dialog.m_rootClassType == CLASS_TYPE_CCLAYER || dialog.m_rootClassType == CLASS_TYPE_CCLAYERCOLOR)
        {
            QCCNode* node = QCCNode::createCCNodeByType( dialog.m_rootClassType );
            node->m_width = dialog.m_width;
            node->m_height = dialog.m_height;
            node->m_x = node->m_width/2;
            node->m_y = node->m_height/2;
            m_storageData->m_root = node;
            m_currentOpenFile = openFile;
            this->replaceRootNode(node);
        }
    }
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString oldDir = m_storageData->resourceDir();
    QString filePath = QFileDialog::getOpenFileName(this, QString("Open Directory"), oldDir);
    QCCNode* node = m_storageData->readUIFile(filePath);
    if(node != 0)
    {
        m_currentOpenFile = filePath;
        this->replaceRootNode(node);
    }
}

void MainWindow::on_actionSave_triggered()
{
    m_storageData->writeUIFile(m_currentOpenFile);
}

void MainWindow::on_actionSave_As_triggered()
{
    QString filePath = QFileDialog::getSaveFileName(this, QString("Save As"), m_currentOpenFile);
    if(filePath.isEmpty())
    {
        return ;
    }

    QString tempFile = m_currentOpenFile;
    m_currentOpenFile = filePath;
    this->on_actionSave_triggered();
    m_currentOpenFile = tempFile;
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
        node->importData(m_copyBuffer);

        //sync
        this->syncNodeAfterCreate(index, node);

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

void MainWindow::on_actionCCSprite_triggered()
{
    QModelIndex index = m_treeView->currentIndex();
    if(index.isValid() == true)
    {
        QString filePath = QFileDialog::getOpenFileName(this, QString("Open File"), m_storageData->resourceDir());
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
    }
}

void MainWindow::on_actionCCMenu_triggered()
{
    QModelIndex index = m_treeView->currentIndex();
    if(index.isValid() == true)
    {
        QString filePath = QFileDialog::getOpenFileName(this, QString("Open File"), m_storageData->resourceDir());
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
    }
}
