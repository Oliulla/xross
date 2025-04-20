// TerminalDisplay.h
#ifndef TERMINALDISPLAY_H
#define TERMINALDISPLAY_H

#include <QPlainTextEdit>
#include <QTimer>
#include <QKeyEvent>

class TerminalDisplay : public QPlainTextEdit
{
    Q_OBJECT

public:
    explicit TerminalDisplay(QWidget *parent = nullptr);

    void appendOutput(const QString &text);
    void setPrompt(const QString &prompt);
    void updateCursor();

public slots:
    void clearTerminal();

signals:
    void executeCommand(const QString &command);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QString m_prompt;
    QString m_currentInput;
    int m_cursorPos;
    bool m_cursorVisible;
    QTimer m_cursorTimer;
};

#endif // TERMINALDISPLAY_H
