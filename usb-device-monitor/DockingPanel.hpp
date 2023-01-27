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
