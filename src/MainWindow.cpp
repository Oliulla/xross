#include "MainWindow.h"
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QTextCursor>
#include <cstdlib>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    output(new QTextEdit(this)),
    layout(new QVBoxLayout(this)),
    currentUser(getCurrentUser())  // Initialize currentUser with the current system user
{
    // Set the window properties
    setWindowTitle("Xross Terminal");
    setFixedSize(600, 400);

    // Make the output read-only (simulate terminal output)
    output->setReadOnly(true);  // Should be read-only to simulate terminal output
    output->setStyleSheet("background-color: black; color: white;");
    output->setFont(QFont("Courier", 10));

    // Set the layout
    layout->addWidget(output);
    
    // Display the initial prompt in the output (dynamically based on the user)
    output->append(currentUser + ":~$ ");
    
    // Set the cursor to the end of the prompt, so user can start typing after the prompt
    QTextCursor cursor = output->textCursor();
    cursor.movePosition(QTextCursor::End);
    output->setTextCursor(cursor);

    // Connect keyPressEvent to capture user input (typing commands)
    output->installEventFilter(this);  // Capture key events from output (e.g., Enter)
}

MainWindow::~MainWindow()
{
}

QString MainWindow::getCurrentUser()
{
    // Get the current username from the system environment variable
    const char *username = std::getenv("USER");
    if (username) {
        return QString(username);
    } else {
        return "root";  // Default to root if no user found
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == output && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        
        if (keyEvent->key() == Qt::Key_Return) {
            // Capture the last command entered (just the text in the current input line)
            QString command = output->toPlainText().split("\n").last();  // Get the last line entered (command)
            
            // Append the command to the output
            output->append(currentUser + ":~$ " + command);  // Show the prompt with the command
            output->append("Executed: " + command);  // Simulate command execution output
            
            // Set the cursor back to the end of the prompt for the next command
            QTextCursor cursor = output->textCursor();
            cursor.movePosition(QTextCursor::End);
            output->setTextCursor(cursor);
            
            // Clear the input field after pressing enter
            output->clear();
        } else {
            // Let the user type normally (handle other keys)
            event->ignore();
        }
        return true;  // We handled the event, no further processing needed
    }
    return QWidget::eventFilter(obj, event);  // Default event handling from QWidget
}


void MainWindow::onEnterPressed()
{
    // Capture the command entered by the user
    QString command = output->toPlainText().split("\n").last();  // Get the last line entered (command)

    // Append the command to the output (simulating execution)
    output->append(currentUser + ":~$ " + command);  // Show the prompt with the command
    output->append("Executed: " + command);  // Simulate command execution output

    // Set the cursor back to the end of the prompt for the next command
    QTextCursor cursor = output->textCursor();
    
    // Move cursor to the end of the document (right after the prompt)
    cursor.movePosition(QTextCursor::End);
    output->setTextCursor(cursor);
    
    // Optionally, clear the input field after pressing enter (if you want the prompt to be ready for the next input)
    output->clear();
}
