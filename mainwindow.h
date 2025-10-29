#pragma once
#include <QMainWindow>

class GraphTreeView;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void openXmlFile();

private:
    GraphTreeView *view;
};
