#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QString>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onEnterPressed();

private:
    QTextEdit *output;  // Terminal-like output display
    QLineEdit *input;   // Text input for commands
    QVBoxLayout *layout;
};

#endif // MAINWINDOW_H
