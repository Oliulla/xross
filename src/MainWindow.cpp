// MainWindow.cpp
#include "MainWindow.h"
#include "TerminalDisplay.h"

#include <QDir>
#include <QHostInfo>
#include <QTimer>
#include "commands/CommandManager.h" 

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    output(new TerminalDisplay(this)),
    layout(new QVBoxLayout(this)),
    currentUser(getCurrentUser())
{
    setWindowTitle("Xross Terminal");
    setFixedSize(600, 400);

    layout->addWidget(output);
    setLayout(layout);

    updatePrompt();

    output->setFocus();
    QTimer::singleShot(100, [this]() {
        output->updateCursor();
    });

    commandManager = new CommandManager();
    connect(output, &TerminalDisplay::executeCommand, this, &MainWindow::executeCommand);
}

MainWindow::~MainWindow() {}

QString MainWindow::getCurrentUser()
{
    const char *username = std::getenv("USER");
    return username ? QString(username) : "root";
}

void MainWindow::updatePrompt()
{
    QString currentDir = QDir::currentPath().replace(QDir::homePath(), "~");
    currentPrompt = QString("%1@%2:%3$ ")
                  .arg(currentUser)
                  .arg(QHostInfo::localHostName())
                  .arg(currentDir);

    output->setPrompt(currentPrompt);

    QTextCursor cursor = output->textCursor();
    cursor.movePosition(QTextCursor::End);
    output->setTextCursor(cursor);
    output->updateCursor();
}


void MainWindow::executeCommand(const QString &command) {
    QString outputText = commandManager->handle(command);

    if (outputText == "__clear__") {
        output->clearTerminal();
    } else {
        output->appendOutput(outputText);
    }

    updatePrompt();
}
