#include "MainWindow.h"
#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    // Constructor implementation
    setWindowTitle("Xross");
    resize(400, 300);
}

MainWindow::~MainWindow() {
    // Destructor implementation
}

void MainWindow::onEnterPressed() {
    // Handle the enter key press here
    qDebug() << "Enter key pressed";
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    // Custom event filtering for key press
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Return) {
            onEnterPressed();
            return true;
        }
    }
    return QWidget::eventFilter(object, event);
}
