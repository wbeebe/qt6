cmake_minimum_required (VERSION 3.25.0)
#
# Build requirements
#
include_directories( /usr/include/x86_64-linux-gnu/qt6/
                     /usr/include/x86_64-linux-gnu/qt6/QtCore/
                     /usr/include/x86_64-linux-gnu/qt6/QtGui/
                     /usr/include/x86_64-linux-gnu/qt6/QtWidgets/
                     /usr/include/x86_64-linux-gnu/qt6/QtSerialPort )
link_libraries( Qt6Core Qt6Widgets Qt6Gui Qt6SerialPort )
add_compile_options( -fPIC -std=c++20 )
#
# Project specific
#
project (usb-device-monitor)
add_executable (udm
                main.cpp
                MainWindow.cpp
                CentralWidget.cpp
                AddWindowFileMenu.cpp
                DockingPanel.cpp
                devices.cpp)