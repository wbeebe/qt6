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
#include <QStatusBar>
#include <QSplitter>
#include <QWidget>
#include <QString>
#include <QStringList>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QSettings>
#include <QPalette>
#include <QSerialPort>
#include <QByteArray>
#include <QScrollBar>
#include <QFont>
#include <QFile>

class CentralWidget : public QSplitter {
    public:
    const QString CWIDGET_STATE{"cwidget/state"};

    explicit CentralWidget(QMainWindow *parent);
    void saveCWState(QSettings &settings);
    void restoreCWState(QSettings &settings);

    public slots:
    void toggleTerminalOut(int);
    void toggleLogConsole(int);

    private:
    QMainWindow *parent;
    QTextEdit *console;
    QSerialPort *serialPort;
    QTableWidget *table;
    bool outputToTerminal,
         logToFile;
    QFile *logFile;
    QString logName;

    void closeUSBPort();
    void openLogFile(QTableWidgetItem *);

    private slots:
    void readSerialData();
    void openUSBPort(QTableWidgetItem *);
};