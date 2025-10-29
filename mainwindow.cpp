#include "mainwindow.h"
#include "graphtreeview.h"
#include <QMenuBar>
#include <QFileDialog>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    resize(1000, 800);
    auto *widget = new QWidget(this);
    auto *layout = new QVBoxLayout(widget);

    view = new GraphTreeView(this);
    layout->addWidget(view);

    widget->setLayout(layout);
    setCentralWidget(widget);

    auto *fileMenu = menuBar()->addMenu("File");
    auto *openAction = fileMenu->addAction("Open XML...");
    connect(openAction, &QAction::triggered, this, &MainWindow::openXmlFile);
}

void MainWindow::openXmlFile() {
    QString path = QFileDialog::getOpenFileName(this, "Open XML File", QString(), "XML Files (*.xml)");
    if (!path.isEmpty()) {
        view->loadXml(path);
    }
}
