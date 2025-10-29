#include "xmltreeparser.h"
#include "treeitem.h"
#include <QDomDocument>
#include <QFile>
#include <QDebug>

static TreeItem* parseElement(const QDomElement &element, TreeItem *parent = nullptr) {
    TreeItem *item = new TreeItem(element.tagName(), parent);
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.isElement()) {
            item->addChild(parseElement(child.toElement(), item));
        }
        child = child.nextSibling();
    }
    return item;
}

TreeItem *XmlTreeParser::parseFile(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file" << filePath;
        return nullptr;
    }
    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        qWarning() << "Failed to parse XML content";
        return nullptr;
    }
    file.close();
    return parseElement(doc.documentElement());
}
