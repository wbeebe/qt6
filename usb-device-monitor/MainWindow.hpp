#pragma once

#include <QMainWindow>
#include <QMenuBar>
#include <QSettings>
#include <QString>

#include "CentralWidget.hpp"
#include "DockingPanel.hpp"

class MainWindow : public QMainWindow {
    public:
    const QString SCOPE_NAME{"Qt6BasedSoftware"};
    const QString APP_NAME{"USBDeviceMonitor"};
    const QString APP_GEOMETRY{"app/geometry"};
    const QString APP_STATE{"app/state"};
    const int INITIAL_WIDTH{900};
    const int INITIAL_HEIGHT{600};

    MainWindow();

    private:
    CentralWidget *cwidget;
    DockingPanel *dockingPanel;

    void createFileMenu();
    QMenu *fileMenu;
    QAction
        *newAction,
        *openAction,
        *saveAction,
        *saveAsAction,
        *aboutAction,
        *exitAction;

    void closeEvent(QCloseEvent*);
};