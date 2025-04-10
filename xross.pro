TEMPLATE = app
TARGET = xross

# Set build directory
DESTDIR = build
OBJECTS_DIR = build/objects
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

# Include the source directories
SOURCES += src/main.cpp

# Specify Qt modules
QT += core gui widgets

# Clean the build directory before building
CLEAN_DIRS += build

# Add header files (if any)
HEADERS += src/mainwindow.h

# Add other resources (if any)
# RESOURCES += src/resources.qrc
