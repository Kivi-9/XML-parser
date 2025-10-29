#pragma once
#include <QString>
class TreeItem;

class XmlTreeParser {
public:
    static TreeItem *parseFile(const QString &filePath);
};
