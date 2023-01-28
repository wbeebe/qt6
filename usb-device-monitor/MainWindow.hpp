/*
 * Copyright (c) 2023 William H. Beebe, Jr.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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