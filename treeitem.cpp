#include "treeitem.h"

TreeItem::TreeItem(const QString &name, TreeItem *parent)
    : m_name(name), m_parent(parent) {}

TreeItem::~TreeItem() {
    qDeleteAll(m_children);
}

void TreeItem::addChild(TreeItem *child) {
    m_children.append(child);
}

QVector<TreeItem *> TreeItem::children() const {
    return m_children;
}

QString TreeItem::name() const {
    return m_name;
}

TreeItem *TreeItem::parent() const {
    return m_parent;
}
