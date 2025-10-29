#include "graphtreeview.h"
#include "xmltreeparser.h"
#include "treeitem.h"
#include <QGraphicsTextItem>
#include <QGraphicsLineItem>
#include <QDebug>
#include <QResizeEvent>

GraphTreeView::GraphTreeView(QWidget *parent)
    : QGraphicsView(parent), scene(new QGraphicsScene(this)) {
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setTransformationAnchor(AnchorUnderMouse);
}

void GraphTreeView::clearScene() {
    scene->clear();
}

void GraphTreeView::loadXml(const QString &path) {
    clearScene();
    TreeItem *root = XmlTreeParser::parseFile(path);
    if (root) {
        drawTree(root);
        scene->setSceneRect(scene->itemsBoundingRect());
        fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }
    delete root;
}

void GraphTreeView::drawTree(TreeItem *root, int, int, int) {
    QMap<TreeItem*, int> widths;
    computeSubtreeSizes(root, widths);

    QMap<TreeItem*, QPoint> positions;
    drawTreeRecursive(root, widths, positions, 0, 0, 120, 100);
    QMap<TreeItem*, QGraphicsTextItem*> graphics;
    for (auto it = positions.begin(); it != positions.end(); ++it) {
        TreeItem *node = it.key();
        QPoint pos = it.value();
        auto *item = scene->addText(node->name());
        item->setPos(pos);
        graphics[node] = item;
    }

    for (auto it = positions.begin(); it != positions.end(); ++it) {
        TreeItem *node = it.key();
        for (TreeItem *child : node->children()) {
            QPoint p1 = graphics[node]->boundingRect().center().toPoint() + graphics[node]->pos().toPoint();
            QPoint p2 = graphics[child]->boundingRect().center().toPoint() + graphics[child]->pos().toPoint();
            scene->addLine(p1.x(), p1.y(), p2.x(), p2.y());
        }
    }
}

void GraphTreeView::computeSubtreeSizes(TreeItem* node, QMap<TreeItem*, int>& widths) {
    if (!node) return;
    if (node->children().isEmpty()) {
        widths[node] = 1;
        return;
    }
    int total = 0;
    for (TreeItem* child : node->children()) {
        computeSubtreeSizes(child, widths);
        total += widths[child];
    }
    widths[node] = std::max(total, 1);
}

void GraphTreeView::drawTreeRecursive(TreeItem* node, const QMap<TreeItem*, int>& widths,
                                      QMap<TreeItem*, QPoint>& positions,
                                      int x, int y, int hSpacing, int vSpacing) {
    int width = widths.value(node, 1);
    int startX = x - (width * hSpacing) / 2;
    int offsetX = 0;

    positions[node] = QPoint(x, y);

    for (TreeItem *child : node->children()) {
        int childWidth = widths.value(child, 1);
        int childX = startX + offsetX + (childWidth * hSpacing) / 2;
        int childY = y + vSpacing;
        drawTreeRecursive(child, widths, positions, childX, childY, hSpacing, vSpacing);
        offsetX += childWidth * hSpacing;
    }
}

void GraphTreeView::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}
