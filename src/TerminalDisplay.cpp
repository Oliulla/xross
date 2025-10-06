// TerminalDisplay.cpp
#include "TerminalDisplay.h"

#include <QPainter>
#include <QTextCursor>
#include <QFontMetrics>
#include <QScrollBar>
#include <QFileInfo>
#include <QDir>
#include <QFileInfoList>
#include <QDebug>


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


QString TerminalDisplay::tryAutocomplete(const QString &input)
{
    // Split by space: last token might be a path or command
    QStringList parts = input.split(' ', Qt::SkipEmptyParts);
    QString prefix = parts.isEmpty() ? "" : parts.last();
    QString baseDir = ".";  // default to current directory

    QFileInfo fileInfo(prefix);
    if (fileInfo.path() != ".") {
        baseDir = fileInfo.path();
    }

    QString searchPrefix = fileInfo.fileName();
    QDir dir(baseDir);
    QFileInfoList entries = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst | QDir::Name);

    QStringList matches;
    for (const QFileInfo &info : entries) {
        if (info.fileName().startsWith(searchPrefix, Qt::CaseInsensitive)) {
            matches << info.fileName();
        }
    }

    // === CASE 1: no matches ===
    if (matches.isEmpty()) {
        m_lastMatches.clear();
        return input; // do nothing
    }

    // === CASE 2: single match → autocomplete ===
    if (matches.size() == 1) {
        QString completion = matches.first();
        QString fullPath = (fileInfo.path() == ".")
            ? completion
            : fileInfo.path() + "/" + completion;

        // Append trailing slash if directory
        if (QFileInfo(dir.absoluteFilePath(completion)).isDir())
            fullPath += "/";

        m_lastMatches.clear();
        m_lastInput.clear();
        parts.removeLast();
        parts << fullPath;
        return parts.join(' ');
    }

    // === CASE 3: multiple matches ===
    if (m_lastInput == input && !m_lastMatches.isEmpty()) {
        // Second Tab press → display matches
        int columns = 4;
        QString formatted;
        for (int i = 0; i < matches.size(); ++i) {
            formatted += matches[i].leftJustified(20);
            if ((i + 1) % columns == 0)
                formatted += "\n";
        }
        appendOutput(formatted.trimmed());

        m_lastMatches.clear();
        m_lastInput.clear();
        return input;
    } else {
        // First Tab press → store matches for next Tab
        m_lastMatches = matches;
        m_lastInput = input;
        return input;
    }
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

    // --- [ENTER] Execute command ---
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        QString command = m_currentInput.trimmed(); // ✅ trim whitespace
        appendOutput("\n"); 
        m_currentInput.clear();
        m_cursorPos = 0;
        emit executeCommand(command);
        return;
    } 

    // --- [BACKSPACE] Delete character ---
    else if (event->key() == Qt::Key_Backspace) {
        if (m_cursorPos > 0) {
            m_currentInput.remove(m_cursorPos - 1, 1);
            m_cursorPos--;
        }
    } 

    // --- [ARROWS] Move cursor ---
    else if (event->key() == Qt::Key_Left) {
        if (m_cursorPos > 0)
            m_cursorPos--;
    } 
    else if (event->key() == Qt::Key_Right) {
        if (m_cursorPos < m_currentInput.length())
            m_cursorPos++;
    } 

    // --- [TAB] Autocomplete ---
    else if (event->key() == Qt::Key_Tab) {
        QString completed = tryAutocomplete(m_currentInput);
        if (!completed.isEmpty() && completed != m_currentInput) {
            m_currentInput = completed;
            m_cursorPos = m_currentInput.length();
        }
        return; // ✅ prevents inserting a tab character
    } 

    // --- [OTHER TEXT INPUT] ---
    else if (!event->text().isEmpty()) {
        QChar ch = event->text().at(0);
        if (ch.category() != QChar::Other_Control) {
            m_currentInput.insert(m_cursorPos, event->text());
            m_cursorPos += event->text().length();
        }
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

void TerminalDisplay::clearTerminal() {
    this->clear();
}
