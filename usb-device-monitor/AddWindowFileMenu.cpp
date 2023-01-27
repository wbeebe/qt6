#include <QApplication>
#include "MainWindow.hpp"

void MainWindow::createFileMenu() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    newAction = new QAction(tr("&New"), this);
    fileMenu->addAction(newAction);
    openAction = new QAction(tr("&Open"), this);
    fileMenu->addAction(openAction);
    saveAction = new QAction(tr("&Save"), this);
    fileMenu->addAction(saveAction);
    saveAsAction = new QAction(tr("Save as"), this);
    fileMenu->addAction(saveAsAction);
    fileMenu->addSeparator();
    aboutAction = new QAction(tr("&About Qt"), this);
    connect(aboutAction, &QAction::triggered, qApp, &QApplication::aboutQt);
    fileMenu->addAction(aboutAction);
    fileMenu->addSeparator();
    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(exitAction);
}
