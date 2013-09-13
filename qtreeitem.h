#ifndef QTREEITEM_H
#define QTREEITEM_H

#include "qccnode.h"

class QTreeItem
{
public:
    QTreeItem(const QVector<QVariant> &data, QTreeItem *parent = 0);
    ~QTreeItem();

    QTreeItem *parent();
    QTreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count = 1, int columns = 2);
    bool removeChildren(int position, int count = 1);
    bool insertColumns(int position, int columns);
    bool removeColumns(int position, int columns);
    int childIndex() const;
    bool setData(int column, const QVariant &value);

public:
    QList<QTreeItem*> m_children;
    QVector<QVariant> m_data; //name & type
    QTreeItem* m_parent;
    QCCNode* m_node;

private:
    QCCNode* createCCNodeByType(QString type);
};

#endif // QTREEITEM_H
