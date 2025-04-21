# xross.pro
TEMPLATE = app
TARGET = xross

# Build dirs
DESTDIR = build
OBJECTS_DIR = build/objects
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui

# Sources
SOURCES += src/main.cpp \
           src/MainWindow.cpp \
           src/TerminalDisplay.cpp

HEADERS += src/MainWindow.h \
           src/TerminalDisplay.h \
           src/commands/ICommand.h \
           src/commands/HelpCommand.h \
           src/commands/PwdCommand.h \
           src/commands/CdCommand.h \
           src/commands/ClearCommand.h \
           src/commands/ListCommand.h \
           src/commands/EchoCommand.h \
           src/commands/WhoamiCommand.h \
           src/commands/CatCommand.h \
           src/commands/MkdirCommand.h \
           src/commands/RmCommand.h \
           src/commands/DateCommand.h \
           src/commands/ExitCommand.h \
           src/commands/HistoryCommand.h \
           src/commands/TreeCommand.h \
           src/commands/CommandManager.h

# Qt Modules
QT += core gui widgets network

CONFIG += c++11 warn_on release

# Clean build dir before building
CLEAN_DIRS += build

# Optimizations for release
win32:!debug {
    QMAKE_CXXFLAGS_RELEASE += -O2
    QMAKE_CFLAGS_RELEASE += -O2
}

unix:!debug {
    QMAKE_CXXFLAGS_RELEASE += -O2
    QMAKE_CFLAGS_RELEASE += -O2
}

