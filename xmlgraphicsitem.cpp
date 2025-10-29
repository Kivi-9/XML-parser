#include "xmlgraphicsitem.h"
#include <QPen>
#include <QBrush>

XmlElementItem::XmlElementItem(const QString &text, QGraphicsItem *parent)
    : QGraphicsItem(parent) {
    textItem = new QGraphicsTextItem(text, this);
    QRectF textRect = textItem->boundingRect();
    rectItem = new QGraphicsRectItem(textRect.adjusted(-5, -5, 5, 5), this);
    rectItem->setBrush(Qt::lightGray);
    textItem->setPos(-textRect.width()/2, -textRect.height()/2);
    rectItem->setPos(-textRect.width()/2, -textRect.height()/2);
}

QRectF XmlElementItem::boundingRect() const {
    return rectItem->boundingRect();
}

void XmlElementItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Drawing is handled by child items
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void XmlElementItem::connectTo(QGraphicsItem *parentItem) {
    QLineF line(parentItem->boundingRect().right(),
               parentItem->boundingRect().center().y(),
               boundingRect().left(),
               boundingRect().center().y());

    QGraphicsLineItem *connector = new QGraphicsLineItem(line, this);
    connector->setPen(QPen(Qt::black, 1, Qt::DashLine));
    connector->setZValue(-1);
}

XmlTextItem::XmlTextItem(const QString &text, QGraphicsItem *parent)
    : QGraphicsItem(parent) {
    textItem = new QGraphicsTextItem(text, this);
    QRectF textRect = textItem->boundingRect();
    ellipseItem = new QGraphicsEllipseItem(textRect.adjusted(-5, -5, 5, 5), this);
    ellipseItem->setBrush(Qt::white);
    textItem->setPos(-textRect.width()/2, -textRect.height()/2);
    ellipseItem->setPos(-textRect.width()/2, -textRect.height()/2);
}

QRectF XmlTextItem::boundingRect() const {
    return ellipseItem->boundingRect();
}

void XmlTextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    // Drawing is handled by child items
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void XmlTextItem::positionRelativeTo(QGraphicsItem *parentItem) {
    qreal x = parentItem->pos().x() + parentItem->boundingRect().width() + 20;
    qreal y = parentItem->pos().y() + parentItem->boundingRect().height()/2 - boundingRect().height()/2;
    setPos(x, y);
}

void XmlTextItem::connectTo(QGraphicsItem *parentItem) {
    QLineF line(parentItem->boundingRect().right() + parentItem->pos().x() - this->pos().x(),
               parentItem->boundingRect().center().y() + parentItem->pos().y() - this->pos().y(),
               boundingRect().left(),
               boundingRect().center().y());

    QGraphicsLineItem *connector = new QGraphicsLineItem(line, this);
    connector->setPen(QPen(Qt::gray));
    connector->setZValue(-1);
}
