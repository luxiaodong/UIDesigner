#include "qabstracttreemodel.h"

QAbstractTreeModel::QAbstractTreeModel(QObject *parent): QAbstractItemModel(parent)
{
}

void QAbstractTreeModel::setRoot(QTreeItem* root)
{
    m_root = root;
}

int QAbstractTreeModel::columnCount(const QModelIndex & /* parent */) const
{
    return m_root->columnCount();
}

QVariant QAbstractTreeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole)
    {
        return QVariant();
    }

    QTreeItem *item = this->itemAt(index);
    return item->data(index.column());
}

Qt::ItemFlags QAbstractTreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.column() == 1)
    {
        return 0;
    }

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QTreeItem *QAbstractTreeModel::itemAt(const QModelIndex &index) const
{
    if (index.isValid())
    {
        QTreeItem *item = static_cast<QTreeItem*>(index.internalPointer());
        if (item)
        {
            return item;
        }
    }
    return m_root;
}

QVariant QAbstractTreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return m_root->data(section);
    }

    return QVariant();
}

QModelIndex QAbstractTreeModel::index(int row, int column, const QModelIndex &parent) const
{
    if (parent.isValid() && parent.column() != 0)
    {
        return QModelIndex();
    }

    QTreeItem *parentItem = this->itemAt(parent);
    QTreeItem *childItem = parentItem->child(row);
    if (childItem)
    {
        return createIndex(row, column, childItem);
    }

    return QModelIndex();
}

bool QAbstractTreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
    bool success = m_root->insertColumns(position, columns);
    endInsertColumns();
    return success;
}

bool QAbstractTreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    QTreeItem *parentItem = this->itemAt(parent);
    beginInsertRows(parent, position, position + rows - 1);
    bool success = parentItem->insertChildren(position, rows, m_root->columnCount());
    endInsertRows();
    return success;
}

QModelIndex QAbstractTreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
    {
        return QModelIndex();
    }

    QTreeItem *childItem = this->itemAt(index);
    QTreeItem *parentItem = childItem->parent();

    if (parentItem == m_root)
    {
        return QModelIndex();
    }

    return createIndex(parentItem->childIndex(), 0, parentItem);
}

bool QAbstractTreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
    beginRemoveColumns(parent, position, position + columns - 1);
    bool success = m_root->removeColumns(position, columns);
    endRemoveColumns();

    if (m_root->columnCount() == 0)
    {
        removeRows(0, rowCount());
    }

    return success;
}

bool QAbstractTreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    QTreeItem *parentItem = this->itemAt(parent);
    beginRemoveRows(parent, position, position + rows - 1);
    bool success = parentItem->removeChildren(position, rows);
    endRemoveRows();
    return success;
}

int QAbstractTreeModel::rowCount(const QModelIndex &parent) const
{
    QTreeItem *parentItem = this->itemAt(parent);
    return parentItem->childCount();
}

bool QAbstractTreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole)
    {
        return false;
    }

    QTreeItem *item = this->itemAt(index);
    bool result = item->setData(index.column(), value);
    if (result)
    {
        emit dataChanged(index, index);
    }

    return result;
}

bool QAbstractTreeModel::setHeaderData(int section, Qt::Orientation orientation,
                              const QVariant &value, int role)
{
    if (role != Qt::EditRole || orientation != Qt::Horizontal)
    {
        return false;
    }

    bool result = m_root->setData(section, value);
    if (result)
    {
        emit headerDataChanged(orientation, section, section);
    }

    return result;
}

void QAbstractTreeModel::createTreeItemByCCNode(QCCNode* node, QModelIndex parentIndex)
{
    int itemCount = this->rowCount( parentIndex );
    this->insertRows(itemCount,1,parentIndex);
    QModelIndex nameIndex = this->index(itemCount, 0 , parentIndex);
    this->setData(nameIndex, node->m_name);
    QModelIndex classIndex = this->index(itemCount, 1 , parentIndex);
    this->setData(classIndex, node->m_classType);
    this->itemAt(nameIndex)->m_node = node;

    //-R
    foreach (QCCNode* son, node->m_children)
    {
        //why nameIndex, relation with QModelIndex and colum
        this->createTreeItemByCCNode(son, nameIndex);
    }
}
