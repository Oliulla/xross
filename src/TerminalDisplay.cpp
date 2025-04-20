// TerminalDisplay.cpp
#include "TerminalDisplay.h"

#include <QPainter>
#include <QTextCursor>
#include <QFontMetrics>
#include <QScrollBar>

TerminalDisplay::TerminalDisplay(QWidget *parent)
    : QPlainTextEdit(parent), m_cursorPos(0), m_cursorVisible(true)
{
    setReadOnly(false);
    setStyleSheet("background-color: black; color: white;");
    setFont(QFont("Courier", 10));
    setCursorWidth(0);
    setWordWrapMode(QTextOption::NoWrap);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_prompt = "";
    m_currentInput = "";

    m_cursorTimer.setInterval(500);
    connect(&m_cursorTimer, &QTimer::timeout, [this]() {
        m_cursorVisible = !m_cursorVisible;
        updateCursor();
    });
    m_cursorTimer.start();

    moveCursor(QTextCursor::End);
}

void TerminalDisplay::appendOutput(const QString &text)
{
    if (document()->blockCount() > 1000) {
        QTextCursor cursor(document());
        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::Down, QTextCursor::KeepAnchor, 200);
        cursor.removeSelectedText();
    }

    moveCursor(QTextCursor::End);
    insertPlainText(text + "\n");

    m_currentInput.clear();
    m_cursorPos = 0;
    ensureCursorVisible();
}

void TerminalDisplay::setPrompt(const QString &prompt)
{
    m_prompt = prompt;
    m_currentInput.clear();
    m_cursorPos = 0;

    moveCursor(QTextCursor::End);
    insertPlainText("\n" + m_prompt);

    updateCursor();
}


void TerminalDisplay::updateCursor()
{
    viewport()->update();
}

void TerminalDisplay::paintEvent(QPaintEvent *event)
{
    QPlainTextEdit::paintEvent(event);

    if (m_cursorVisible && hasFocus()) {
        QTextCursor cursor = textCursor();
        cursor.movePosition(QTextCursor::End);

        QRect curRect = cursorRect(cursor);
        QFontMetrics fm(font());
        curRect.setWidth(fm.horizontalAdvance(' '));

        QPainter painter(viewport());
        painter.fillRect(curRect, Qt::white);
    }
}

void TerminalDisplay::keyPressEvent(QKeyEvent *event)
{
    QString currentLine = m_prompt + m_currentInput;

    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        QString command = m_currentInput;
        appendOutput("\n"); // make new line before command
        m_currentInput.clear();
        m_cursorPos = 0;
        emit executeCommand(command);
        return;
    } else if (event->key() == Qt::Key_Backspace) {
        if (m_cursorPos > 0) {
            m_currentInput.remove(m_cursorPos - 1, 1);
            m_cursorPos--;
        }
    } else if (event->key() == Qt::Key_Left) {
        if (m_cursorPos > 0) {
            m_cursorPos--;
        }
    } else if (event->key() == Qt::Key_Right) {
        if (m_cursorPos < m_currentInput.length()) {
            m_cursorPos++;
        }
    } else if (!event->text().isEmpty()) {
        m_currentInput.insert(m_cursorPos, event->text());
        m_cursorPos += event->text().length();
    }

    QTextCursor cursor = textCursor();
    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.movePosition(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
    cursor.removeSelectedText();
    cursor.insertText(m_prompt + m_currentInput);

    cursor.movePosition(QTextCursor::StartOfLine);
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, m_prompt.length() + m_cursorPos);
    setTextCursor(cursor);

    updateCursor();
}

void TerminalDisplay::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    ensureCursorVisible();
}
