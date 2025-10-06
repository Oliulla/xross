#include "TerminalInput.h"

TerminalInput::TerminalInput(QWidget *parent)
    : QLineEdit(parent) {}

void TerminalInput::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Tab) {
        emit tabPressed(this->text());
        return; // prevent focus change
    }
    QLineEdit::keyPressEvent(event);
}
