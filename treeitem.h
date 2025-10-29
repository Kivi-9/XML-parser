#pragma once
#include <QString>
#include <QVector>

class TreeItem {
public:
    TreeItem(const QString &name, TreeItem *parent = nullptr);
    ~TreeItem();

    void addChild(TreeItem *child);
    QVector<TreeItem *> children() const;
    QString name() const;
    TreeItem *parent() const;

private:
    QString m_name;
    QVector<TreeItem *> m_children;
    TreeItem *m_parent;
};
