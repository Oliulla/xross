#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QString>
#include <QTimer>

class TerminalDisplay : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit TerminalDisplay(QWidget *parent = nullptr);
    void appendOutput(const QString &text);
    void setPrompt(const QString &prompt);
    void updateCursor();

signals:
    void executeCommand(const QString &command);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QString m_prompt;
    QString m_currentInput;
    int m_cursorPos;
    bool m_cursorVisible;
    QTimer m_cursorTimer;
};

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void executeCommand(const QString &command);

private:
    QString getCurrentUser();
    void updatePrompt();

    TerminalDisplay *output;
    QVBoxLayout *layout;
    QString currentUser;
    QString currentPrompt;
};

#endif // MAINWINDOW_H