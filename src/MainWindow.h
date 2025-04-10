#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class MainWindow : public QWidget
{
    Q_OBJECT  // This macro is essential for signals/slots

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *object, QEvent *event) override;

private slots:
    void onEnterPressed();  // Slot for handling Enter key press
};

#endif // MAINWINDOW_H
