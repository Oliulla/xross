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
            "  ls, dir        List directory contents\n"
            "  echo <text>    Output text\n"
            "  whoami         Show current user\n"
            "  cat <file>, type <file>      Display file contents\n"
            "  mkdir <name>    Create a new directory\n"
        );
        
    }
};

#endif // HELPCOMMAND_H
