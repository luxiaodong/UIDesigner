#include "qtreeitem.h"

QTreeItem::QTreeItem(const QVector<QVariant> &data, QTreeItem *parent)
{
    m_parent = parent;
    m_data = data;
}

QTreeItem::~QTreeItem()
{
    qDeleteAll(m_children);
}

QTreeItem *QTreeItem::child(int number)
{
    return m_children.value(number);
}

int QTreeItem::childCount() const
{
    return m_children.count();
}

int QTreeItem::childIndex() const
{
    if (m_parent)
    {
        return m_parent->m_children.indexOf(const_cast<QTreeItem*>(this));
    }

    return 0;
}

int QTreeItem::columnCount() const
{
    return m_data.count();
}

QVariant QTreeItem::data(int column) const
{
    return m_data.value(column);
}

bool QTreeItem::insertChildren(int position, int count, int columns)
{
    if (position < 0 || position > m_children.size())
    {
        return false;
    }

    for (int row = 0; row < count; ++row)
    {
        QVector<QVariant> data(columns);
        QTreeItem *item = new QTreeItem(data, this);
        m_children.insert(position, item);
    }

    return true;
}

bool QTreeItem::insertColumns(int position, int columns)
{
    if (position < 0 || position > m_data.size())
    {
        return false;
    }

    for (int column = 0; column < columns; ++column)
    {
        m_data.insert(position, QVariant());
    }

    foreach (QTreeItem *child, m_children)
    {
        child->insertColumns(position, columns);
    }

    return true;
}

QTreeItem *QTreeItem::parent()
{
    return m_parent;
}

bool QTreeItem::removeChildren(int position, int count)
{
    if (position < 0 || position + count > m_children.size())
    {
        return false;
    }

    for (int row = 0; row < count; ++row)
    {
        delete m_children.takeAt(position);
    }

    return true;
}

bool QTreeItem::removeColumns(int position, int columns)
{
    if (position < 0 || position + columns > m_data.size())
    {
        return false;
    }

    for (int column = 0; column < columns; ++column)
    {
        m_data.remove(position);
    }

    foreach (QTreeItem *child, m_children)
    {
        child->removeColumns(position, columns);
    }

    return true;
}

bool QTreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= m_data.size())
    {
        return false;
    }

    m_data[column] = value;
    return true;
}

