#pragma once
#include <QGraphicsView>
#include <QString>
#include <QMap>
#include <QPoint>
class TreeItem;

class GraphTreeView : public QGraphicsView {
    Q_OBJECT
public:
    GraphTreeView(QWidget *parent = nullptr);
    void loadXml(const QString &path);

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawTree(TreeItem *root, int x = 0, int y = 0, int depth = 0);
    void clearScene();
    void computeSubtreeSizes(TreeItem* node, QMap<TreeItem*, int>& widths);
    void drawTreeRecursive(TreeItem* node, const QMap<TreeItem*, int>& widths,
                           QMap<TreeItem*, QPoint>& positions,
                           int x, int y, int hSpacing, int vSpacing);

    QGraphicsScene *scene;
};
