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
