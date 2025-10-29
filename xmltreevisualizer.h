#ifndef XMLTREEVISUALIZER_H
#define XMLTREEVISUALIZER_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QXmlStreamReader>
#include <QTreeWidgetItem>

class QTreeWidget;
class QGraphicsView;
class QSplitter;

class XmlTreeVisualizer : public QMainWindow {
    Q_OBJECT

public:
    explicit XmlTreeVisualizer(QWidget *parent = nullptr);

private slots:
    void openXmlFile();

private:
    void setupUI();
    void parseAndVisualizeXml(const QString &filePath);
    void visualizeXmlElement(QXmlStreamReader &xml, QTreeWidgetItem *parentItem,
                           QGraphicsItem *parentGraphicsItem, int level, int &yPos);

    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QTreeWidget *treeWidget;
    QSplitter *splitter;
};

#endif // XMLTREEVISUALIZER_H
