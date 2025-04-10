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
    // Constructor that takes an optional parent widget
    explicit MainWindow(QWidget *parent = nullptr);
    
    // Destructor
    ~MainWindow();

private slots:
    // Slot that is called when the Enter key is pressed in the input field
    void onEnterPressed();  // Only one declaration is needed

private:
    // Terminal-like output display for showing commands and results
    QTextEdit *output;
    
    // Input field where the user types commands (single-line input)
    QLineEdit *input;
    
    // Layout to arrange widgets vertically
    QVBoxLayout *layout;
    
    // Method to get the current username for the prompt display
    QString getCurrentUser();
    
    // Event filter to intercept and handle key events
    bool eventFilter(QObject* obj, QEvent* event);

    // Stores the current user for the prompt display (e.g., "oli")
    QString currentUser;
};

#endif // MAINWINDOW_H
