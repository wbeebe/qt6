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
#include <QGroupBox>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QGridLayout>
#include <QString>
#include <QCheckBox>
#include <QComboBox>
#include <QSettings>

#include "CentralWidget.hpp"

class DockingPanel : public QDockWidget {
    public:
    explicit DockingPanel(QMainWindow *parent, CentralWidget *cwidget);
    void saveDPState(QSettings &settings);
    void restoreDPState(QSettings &settings);

    private:
    QMainWindow *parent;
    CentralWidget *cwidget;
    QCheckBox
        *cb1,
        *cb2,
        *cb3,
        *cb4;
    QComboBox *comboBox;
};
