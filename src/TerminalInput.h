#ifndef TERMINALINPUT_H
#define TERMINALINPUT_H

#include <QLineEdit>
#include <QKeyEvent>

class TerminalInput : public QLineEdit {
    Q_OBJECT

public:
    explicit TerminalInput(QWidget *parent = nullptr);

signals:
    void tabPressed(const QString &currentText);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif 
