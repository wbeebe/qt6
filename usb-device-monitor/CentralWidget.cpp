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

#include <ctime>
#include <string>

#include "CentralWidget.hpp"
#include "devices.hpp"

CentralWidget::CentralWidget(QMainWindow *_parent) :
    QSplitter(parent),
    console(new QTextEdit),
    serialPort(new QSerialPort),
    table(new QTableWidget),
    logFile(nullptr),
    outputToTerminal(false),
    logToFile(false) {
        parent = _parent;
        setOrientation(Qt::Vertical);

        // Configure the console with which we will communicate with a given
        // USB device.
        //
        QPalette colors = palette();
        colors.setColor(QPalette::Base, Qt::black);
        colors.setColor(QPalette::Text, Qt::white);
        QFont font("Monospace", 12);
        font.setStyleStrategy(QFont::PreferAntialias);
        console->setPalette(colors);
        console->setFont(font);
        console->setCursorWidth(8);

        // Connect the console with the serial port so that any data that is
        // recieved by the serial port will be displayed on the console.
        //
        connect(
            serialPort, &QSerialPort::readyRead, this,
            &CentralWidget::readSerialData);

        // Find all the USB devices connected to our system. Put their data
        // in a spreadsheet-like table.
        //
        auto devices = getDevices();
        table->setRowCount(devices.size());
        QStringList headers = 
            {"Device", "Adapter Name", "Unique Identification"};
        table->setColumnCount(headers.size());
        table->setHorizontalHeaderLabels(headers);
        table->horizontalHeader()->setStretchLastSection(true);
        int row{0};

        // Populate the table with eacj USB device, one row/devices.
        //
        for (auto [device, values] : devices) {
            QString dev(device.c_str());
            QString v1(values[0].c_str());
            QString v2(values[1].c_str());
            table->setItem(row, 0, new QTableWidgetItem(dev));
            table->setItem(row, 1, new QTableWidgetItem(v1));
            table->setItem(row, 2, new QTableWidgetItem(v2));
            ++row;
        }

        table->resizeColumnsToContents();

        // Connect the table with the class function so that when a user
        // clicks on a port in the table, that port will be opened and
        // communicating with the console.
        //
        connect(
            table, &QTableWidget::itemClicked, this,
            &CentralWidget::openUSBPort);

        // Finish construction by putting the table at the top and the
        // console beneath it.
        //
        addWidget(table);
        addWidget(console);
        parent->statusBar()->showMessage("No port selected");
}

void CentralWidget::toggleTerminalOut(int state) {
    outputToTerminal = (state == Qt::Checked);
}

void CentralWidget::toggleLogConsole(int state) {
    logToFile = (state == Qt::Checked);

    if (not logToFile) {

        logName = "";
    }
}

/* This is connected to QSerialPort::readyRead.
 * The serial data is always read and displayed on the console (QTexEdit).
 * The function then checks to see if the data should be either written to
 * the console and/or the log file.
 * Note that the log file is always created and opened when a port is selected,
 * but will write to the log file if and only if logToFile is true.
 */
void CentralWidget::readSerialData() {
    char timeStamp[std::size("[yyyy/mm/dd hh:mm:ss] ")];
    QByteArray data = serialPort->readAll();
    console->insertPlainText(data);
    QScrollBar *scrollBar = console->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());

    if (outputToTerminal or logToFile) {
        std::string sdata(data.toStdString());
        const std::time_t now = std::time(nullptr);
        std::strftime(
            std::data(timeStamp), std::size(timeStamp),
            "[%Y/%m/%d %H:%M:%S] ", std::localtime(&now));

        if (outputToTerminal) {
            std::cout << timeStamp << sdata;
            if (sdata.length() == 0 or sdata.back() != '\n') {
                std::cout << "\n";
            }
        }

        if (logToFile and logFile != nullptr and logFile->isOpen()) {
            logFile->write(timeStamp);
            logFile->write(sdata.c_str());
            if (sdata.length() == 0 or sdata.back() != '\n') {
                logFile->write("\n");
            }
            logFile->flush();
        }
    }
}

/* This is connected to QTableWidget::itemClicked.
 * When any cell in the table is clicked this class function is called.
 * The function then checks to see if it was the correct cell, or cell
 * 0.
 * If it's cell 0, then the device name is used to open the serial port,
 * after any earlier port is closed.
 * Before the selected USB device is opened, a check is made to see if a
 * corresponding log file should be opened.
 * The status bar at the bottom is updated to show which port.
 */
void CentralWidget::openUSBPort(QTableWidgetItem *cell) {
    if (cell->column() == 0) {
        closeUSBPort();
        openLogFile(cell);
        QString portName = "/dev/" + cell->text();
        serialPort->setPortName(portName);
        serialPort->setBaudRate(QSerialPort::Baud115200);
        serialPort->setDataBits(QSerialPort::Data8);
        serialPort->setParity(QSerialPort::NoParity);
        serialPort->open(QIODevice::ReadOnly);
        serialPort->clear(QSerialPort::AllDirections);
        parent->statusBar()->showMessage(
            QString("Port: %1 ---- Logfile: %2").arg(portName).arg(logName));
    }
}

/* This is called from openUSBport. It will open a log file if the user has
 * checked a USB device in the table. The name of the log file incorporates
 * the device name and a time stamp using local time when it was created.
 */
void CentralWidget::openLogFile(QTableWidgetItem *cell) {
    if (logFile != nullptr) {
        logFile->close();
    }

    const std::time_t now = std::time(nullptr);
    char timeString[std::size("yyyymmdd_hhmmss")];
    std::strftime(
        std::data(timeString), std::size(timeString),
        "%Y%m%d_%H%M%S", std::localtime(&now));
    logName = QString("%1_%2.log").arg(cell->text()).arg(timeString);
    std::cout << logName.toStdString() << "\n";
    logFile = new QFile(logName);
    logFile->open(QIODevice::WriteOnly | QIODevice::Text);
    std::cout << 
        (logFile->isOpen() ? "logfile open\n" : "logfile failed to open\n");
}

void CentralWidget::closeUSBPort() {
    if (serialPort->isOpen()) {
        serialPort->clear();
        serialPort->close();
    }
}

void CentralWidget::saveCWState(QSettings &settings) {
    settings.setValue(CWIDGET_STATE, saveState());
}

void CentralWidget::restoreCWState(QSettings &settings) {
    if(settings.contains(CWIDGET_STATE)) {
        restoreState(settings.value(CWIDGET_STATE).toByteArray());
    }
}
