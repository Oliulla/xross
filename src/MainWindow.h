// MainWindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QString>
#include <QTimer>

#include "TerminalDisplay.h"
#include "commands/CommandManager.h"


class MainWindow : public QWidget {
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
        CommandManager *commandManager; // ✅ Add this line
};

#endif // MAINWINDOW_H