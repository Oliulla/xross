#include "MainWindow.h"
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QTextCursor>
#include <QPainter>
#include <cstdlib>

TerminalDisplay::TerminalDisplay(QWidget *parent) 
    : QPlainTextEdit(parent), m_cursorPos(0), m_cursorVisible(true)
{
    setReadOnly(false);
    setStyleSheet("background-color: black; color: white;");
    setFont(QFont("Courier", 10));
    
    // Set up cursor blinking timer
    m_cursorTimer.setInterval(500); // 500ms blink interval
    connect(&m_cursorTimer, &QTimer::timeout, [this]() {
        m_cursorVisible = !m_cursorVisible;
        updateCursor();
    });
    m_cursorTimer.start();
}

void TerminalDisplay::appendOutput(const QString &text)
{
    moveCursor(QTextCursor::End);
    insertPlainText(text);
    m_currentInput.clear();
    m_cursorPos = 0;
}

void TerminalDisplay::setPrompt(const QString &prompt)
{
    m_prompt = prompt;  // Fixed the typo here (was promopt)
    updateCursor();
}

void TerminalDisplay::updateCursor()
{
    // Force repaint to show/hide cursor
    viewport()->update();
}

void TerminalDisplay::paintEvent(QPaintEvent *event)
{
    QPlainTextEdit::paintEvent(event);
    
    // Draw the cursor if it's visible and we're at the input line
    if (m_cursorVisible && hasFocus()) {
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::End);
        
        // Calculate cursor position
        QString fullLine = m_prompt + m_currentInput;
        QFontMetrics fm(font());
        int cursorX = fm.horizontalAdvance(fullLine.left(m_cursorPos + m_prompt.length()));
        
        // Get the line rectangle
        QRect curRect = cursorRect(cursor);
        curRect.setLeft(curRect.left() + cursorX - fm.horizontalAdvance(fullLine.left(m_cursorPos)));
        curRect.setWidth(fm.horizontalAdvance(' '));
        
        // Draw the cursor
        QPainter painter(viewport());
        painter.fillRect(curRect, Qt::white);
    }
}

void TerminalDisplay::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        QString command = m_currentInput;
        m_currentInput.clear();
        m_cursorPos = 0;
        emit executeCommand(command);
        return;
    }
    else if (event->key() == Qt::Key_Backspace) {
        if (m_cursorPos > 0) {
            m_currentInput.remove(m_cursorPos - 1, 1);
            m_cursorPos--;
        }
    }
    else if (event->key() == Qt::Key_Left) {
        if (m_cursorPos > 0) {
            m_cursorPos--;
        }
    }
    else if (event->key() == Qt::Key_Right) {
        if (m_cursorPos < m_currentInput.length()) {
            m_cursorPos++;
        }
    }
    else if (!event->text().isEmpty()) {
        m_currentInput.insert(m_cursorPos, event->text());
        m_cursorPos += event->text().length();
    }
    
    // Update the display
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.select(QTextCursor::LineUnderCursor);
    cursor.removeSelectedText();
    cursor.insertText(m_prompt + m_currentInput);
    cursor.movePosition(QTextCursor::End);
    setTextCursor(cursor);
    
    updateCursor();
}

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

    connect(output, &TerminalDisplay::executeCommand, this, &MainWindow::executeCommand);
}

MainWindow::~MainWindow()
{
}

QString MainWindow::getCurrentUser()
{
    const char *username = std::getenv("USER");
    return username ? QString(username) : "root";
}

void MainWindow::updatePrompt()
{
    currentPrompt = QString("%1:~$ ").arg(currentUser);
    output->setPrompt(currentPrompt);
    output->appendOutput(""); // Shows the prompt
}

void MainWindow::executeCommand(const QString &command)
{
    // Process the command (simulated)
    QString result = QString("Command '%1' executed").arg(command);
    
    // Display the result
    output->appendOutput(result + "\n");
    
    // Show new prompt
    updatePrompt();
}