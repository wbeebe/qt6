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