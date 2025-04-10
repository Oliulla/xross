#include "MainWindow.h"
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    output(new QTextEdit(this)),
    input(new QLineEdit(this)),
    layout(new QVBoxLayout(this))
{
    // Set the window properties
    setWindowTitle("Xross Terminal");
    setFixedSize(600, 400);

    // Make the output read-only (simulate terminal output)
    output->setReadOnly(true);
    output->setStyleSheet("background-color: black; color: white;");

    // Set up the input area
    input->setStyleSheet("background-color: black; color: white;");
    input->setPlaceholderText("Enter your command...");
    
    // Set the layout
    layout->addWidget(output);
    layout->addWidget(input);

    // Display the initial prompt in the output
    output->append("oli@oli:~$");

    // Connect the Enter key press to the slot
    connect(input, &QLineEdit::returnPressed, this, &MainWindow::onEnterPressed);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onEnterPressed()
{
    // Get the command from input field
    QString command = input->text();

    // Add the entered command to the output
    output->append("oli@oli:~$ " + command);

    // Simulate the command execution (for now, just show it)
    output->append("Executed: " + command);

    // Clear the input field for the next command
    input->clear();
}
