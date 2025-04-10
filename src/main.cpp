#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}
// Compare this snippet from src/MainWindow.cpp:
// #include "MainWindow.h"
// #include <QPushButton>
// #include <QVBoxLayout>
// #include <QKeyEvent>