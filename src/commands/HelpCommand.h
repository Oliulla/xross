// commands/HelpCommand.h
#ifndef HELPCOMMAND_H
#define HELPCOMMAND_H

#include "ICommand.h"
#include <QStringList>

class HelpCommand : public ICommand {
    public:
        QString name() const override {
            return "help";
        }

    QString execute(const QStringList &args) override {
        Q_UNUSED(args);
        return QString(
            "Available commands:\n"
            "  help           Show this help message\n"
            "  pwd            Print current directory\n"
            "  cd <path>      Change directory\n"
            "  clear, cls     Clear the terminal output\n"
        );
    }
};

#endif // HELPCOMMAND_H
