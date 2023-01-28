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

#include <QCoreApplication>
#include <QGuiApplication>
#include <QScreen>
#include <QSize>
#include <QStatusBar>

#include "MainWindow.hpp"

MainWindow::MainWindow() {
    QCoreApplication::setOrganizationName(SCOPE_NAME);
    QCoreApplication::setApplicationName(APP_NAME);

    setWindowTitle(APP_NAME);
    cwidget = new CentralWidget(this);
    setCentralWidget(cwidget);
    dockingPanel = new DockingPanel(this, cwidget);
    addDockWidget(Qt::LeftDockWidgetArea, dockingPanel);
    createFileMenu();
    //statusBar()->showMessage("Statusbar Placeholder");

    QSettings settings(
        QCoreApplication::organizationName(),
        QCoreApplication::applicationName());

    if (settings.contains(APP_GEOMETRY) and 
        settings.contains(APP_STATE)) {
        restoreGeometry(settings.value(APP_GEOMETRY).toByteArray());
        restoreState(settings.value(APP_STATE).toByteArray());
        cwidget->restoreCWState(settings);
        dockingPanel->restoreDPState(settings);
        return;
    }

    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QSize screenSize = primaryScreen->availableSize();
    auto screenWidth  = screenSize.width();
    auto screenHeight = screenSize.height();
    auto upperLeftX  = (screenWidth - INITIAL_WIDTH)/2;
    auto upperLeftY = (screenHeight - INITIAL_HEIGHT)/2;
    setGeometry(upperLeftX, upperLeftY, INITIAL_WIDTH, INITIAL_HEIGHT);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QSettings settings(
        QCoreApplication::organizationName(),
        QCoreApplication::applicationName());
    settings.setValue(APP_GEOMETRY, saveGeometry());
    settings.setValue(APP_STATE, saveState());
    cwidget->saveCWState(settings);
    dockingPanel->saveDPState(settings);
    QMainWindow::closeEvent(event);
}