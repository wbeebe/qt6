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

#include "DockingPanel.hpp"

DockingPanel::DockingPanel(QMainWindow *_parent, CentralWidget *_cwidget) : QDockWidget(_parent) {
    parent = _parent;
    cwidget = _cwidget;
    setWindowTitle("Port Controls");
    setObjectName("Docking_Panel");
    setFeatures(QDockWidget::DockWidgetMovable);
    setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    QWidget *mainWidget = new QWidget(this);
    mainWidget->setObjectName("Main_Widget");
    QGridLayout *grid = new QGridLayout(mainWidget);
    grid->setObjectName("Main_Widget_Layout");
    mainWidget->setLayout(grid); 

    QGroupBox *checkboxSelection = new QGroupBox;
    checkboxSelection->setObjectName("Checkboxes");
    QVBoxLayout *cslayout = new QVBoxLayout(checkboxSelection);
    cslayout->setObjectName("Checkbox_Layout");
    cb1 = new QCheckBox("Echo to terminal", this);
    connect(cb1, &QCheckBox::stateChanged,
            cwidget, &CentralWidget::toggleTerminalOut);
    cslayout->addWidget(cb1, 0, Qt::AlignLeft);
    cb2 = new QCheckBox("Log to file", this);
    connect(cb2,&QCheckBox::stateChanged,
            cwidget, &CentralWidget::toggleLogConsole);
    cslayout->addWidget(cb2, 1, Qt::AlignLeft);
    //cb3 = new QCheckBox("Three", this);
    //cslayout->addWidget(cb3, 2, Qt::AlignLeft);
    //cb4 = new QCheckBox("Four", this);
    //cslayout->addWidget(cb4, 3, Qt::AlignLeft);
    checkboxSelection->setLayout(cslayout);
    grid->addWidget(checkboxSelection, 0, 0);
/*
    QGroupBox *groupBox = new QGroupBox("Dropdown", this);
    groupBox->setObjectName("Drowndown");
    QVBoxLayout *layout = new QVBoxLayout(groupBox);
    layout->setObjectName("ComboBox_Layout");
    comboBox = new QComboBox();
    comboBox->addItem("One");
    comboBox->addItem("Two");
    comboBox->addItem("Three");
    comboBox->addItem("Four");
    layout->addWidget(comboBox);
    groupBox->setLayout(layout);
    grid->addWidget(groupBox, 1, 0);
*/
    QWidget *filler = new QWidget(this);
    filler->setObjectName("Filler");
    QVBoxLayout *flayout = new QVBoxLayout(filler);
    flayout->addSpacerItem(
        new QSpacerItem(20, 800, QSizePolicy::Minimum,QSizePolicy::Expanding));
    flayout->setObjectName("Filler_Layout");
    filler->setLayout(flayout);
    grid->addWidget(filler, 1, 0);

    setWidget(mainWidget);
}

void DockingPanel::saveDPState(QSettings &settings) {
    settings.setValue("dock/cb1",cb1->isChecked());
    settings.setValue("dock/cb2",cb2->isChecked());
    //settings.setValue("dock/cb3",cb3->isChecked());
    //settings.setValue("dock/cb4",cb4->isChecked());
    //settings.setValue("dock/combo1", comboBox->currentIndex());
}

void DockingPanel::restoreDPState(QSettings &settings) {
    cb1->setChecked(settings.value("dock/cb1").toBool());
    cb2->setChecked(settings.value("dock/cb2").toBool());
    //cb3->setChecked(settings.value("dock/cb3").toBool());
    //cb4->setChecked(settings.value("dock/cb4").toBool());
    //comboBox->setCurrentIndex(settings.value("dock/combo1").toInt());
}
