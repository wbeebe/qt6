# Qt 6
## What Is This?
This is my area for developing graphical tools to support my IoT development. These tools are developed with Qt 6.2 LTS and C++ on Linux Mint 21.1 (and later).

---

## General Requirements to Build
0. A Debian/Ubuntu based Linux operating system. As noted I use Linux Mint 21.1.
1. `cmake` - I use the latest (or near latest) version available from the CMake website at https://cmake.org/download. I download the prebuilt binary and run it locally in my home area. 
2. `g++` - Version 11 or higher. You need to support the C++20 standard. This version of g++ is part of the GCC tool chain, found in every contemporary Linux distribution such as Linux Mint 21.1.
3. QT 6.2 LTS - Make sure the following libraries are installed (this is for Linux Mint 21.1)
    - `qt6-base-dev`
    - `libqt6serialport6` (to support QSerial, not installed with qt6-base-dev)
    - `libqt6serialport6-dev` (to support QSerial, not installed with qt6-base-dev)

---

## How to Build
Details for how to build and run each application is in the README in each folder.
