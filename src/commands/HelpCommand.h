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
            "  whoami         Show current username\n"
            "  cat <file>     Display file content\n"
            "  mkdir <dir>    Create directory\n"
            "  rm <file/dir>  Delete file or directory\n"
            "  rmdir, del     Aliases for rm\n"
            "  date           Show current date and time (aliases: Get-Date, date /T, time /T)\n"

        );
        
        
    }
};

#endif // HELPCOMMAND_H
