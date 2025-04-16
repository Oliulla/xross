TEMPLATE = app
TARGET = xross

# Set build directory
DESTDIR = build
OBJECTS_DIR = build/objects
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

# Input files
SOURCES += src/main.cpp \
           src/MainWindow.cpp

HEADERS += src/MainWindow.h

# Specify Qt modules (no duplicates needed)
QT += core gui widgets
QT += core gui widgets network

# Compiler flags
CONFIG += c++11
CONFIG += warn_on
CONFIG += release

# Clean the build directory before building
CLEAN_DIRS += build

# Additional settings for release builds
win32:!debug {
    QMAKE_CXXFLAGS_RELEASE += -O2
    QMAKE_CFLAGS_RELEASE += -O2
}

unix:!debug {
    QMAKE_CXXFLAGS_RELEASE += -O2
    QMAKE_CFLAGS_RELEASE += -O2
}