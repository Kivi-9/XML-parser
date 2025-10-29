#ifndef XMLGRAPHICSITEM_H
#define XMLGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>

class XmlElementItem : public QGraphicsItem {
public:
    XmlElementItem(const QString &text, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void connectTo(QGraphicsItem *parentItem);

private:
    QGraphicsTextItem *textItem;
    QGraphicsRectItem *rectItem;
};

class XmlTextItem : public QGraphicsItem {
public:
    XmlTextItem(const QString &text, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void positionRelativeTo(QGraphicsItem *parentItem);
    void connectTo(QGraphicsItem *parentItem);

private:
    QGraphicsTextItem *textItem;
    QGraphicsEllipseItem *ellipseItem;
};

#endif // XMLGRAPHICSITEM_H
