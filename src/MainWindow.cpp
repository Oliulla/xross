#include "MainWindow.h"
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QTextCursor>
#include <QPainter>
#include <QDir>          
#include <QHostInfo>     
#include <QResizeEvent>  
#include <cstdlib>

TerminalDisplay::TerminalDisplay(QWidget *parent) 
    : QPlainTextEdit(parent), m_cursorPos(0), m_cursorVisible(true)
{
    setReadOnly(false);
    setStyleSheet("background-color: black; color: white;");
    setFont(QFont("Courier", 10));
    setCursorWidth(0); // Hide default Qt cursor
    
    // Initialize with empty prompt
    m_prompt = "";
    m_currentInput = "";
    
    // Set up cursor blinking timer
    m_cursorTimer.setInterval(500);
    connect(&m_cursorTimer, &QTimer::timeout, [this]() {
        m_cursorVisible = !m_cursorVisible;
        updateCursor();
    });
    m_cursorTimer.start();
    
    // Ensure we start with the cursor at the end
    moveCursor(QTextCursor::End);

    // In TerminalDisplay constructor:
    setWordWrapMode(QTextOption::NoWrap);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void TerminalDisplay::appendOutput(const QString &text)
{
    // Limit the maximum block count to prevent memory issues
    if (document()->blockCount() > 1000) {
        QTextCursor cursor(document());
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor, 200);
        cursor.removeSelectedText();
    }
    
    moveCursor(QTextCursor::End);
    insertPlainText(text);
    m_currentInput.clear();
    m_cursorPos = 0;
    ensureCursorVisible();
}

void TerminalDisplay::setPrompt(const QString &prompt)
{
    m_prompt = prompt;
    
    // Get current input text
    QString currentText = toPlainText();
    
    // If we have existing text, find the last prompt
    if (!currentText.isEmpty()) {
        int lastPromptPos = currentText.lastIndexOf(m_prompt);
        if (lastPromptPos >= 0) {
            // Keep content before last prompt
            currentText = currentText.left(lastPromptPos);
        }
    }
    
    // Clear and set new prompt
    clear();
    insertPlainText(currentText + m_prompt);
    
    // Reset cursor position after prompt
    m_cursorPos = 0;
    m_currentInput.clear();
    
    // Move cursor to end
    moveCursor(QTextCursor::End);
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
     // Always ensure we're working with the current line
     QString currentLine = m_prompt + m_currentInput;
    
     // Handle key events
     if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
         QString command = m_currentInput;
         m_currentInput.clear();
         m_cursorPos = 0;
         emit executeCommand(command);
         return;
     } else if (event->key() == Qt::Key_Backspace) {
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
    
    // Update display
    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertText(m_prompt + m_currentInput);
    
    // Position cursor correctly
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 
                       m_prompt.length() + m_cursorPos);
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

    // Show initial prompt immediately
    updatePrompt();

    // In MainWindow constructor, after updatePrompt():
    output->setFocus();
    QTimer::singleShot(100, [this]() {
        output->updateCursor(); // Force initial cursor draw
    });
    
    // Set focus to the terminal so cursor is visible
    // output->setFocus();

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
    // Get current working directory for prompt
    QString currentDir = QDir::currentPath();
    currentDir.replace(QDir::homePath(), "~");
    
    currentPrompt = QString("%1@%2:%3$ ")
                  .arg(currentUser)
                  .arg(QHostInfo::localHostName())
                  .arg(currentDir);
    
    output->setPrompt(currentPrompt);
    
    // Force display update
    QTextCursor cursor = output->textCursor();
    cursor.movePosition(QTextCursor::End);
    output->setTextCursor(cursor);
    output->updateCursor();
}



void TerminalDisplay::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    ensureCursorVisible();
}


void MainWindow::executeCommand(const QString &command)
{
    // Process the command (simulated)
    QString result = QString("\nCommand '%1' executed").arg(command);
    
    // Display the result
    output->appendOutput(result + "\n");
    
    // Show new prompt
    updatePrompt();
}