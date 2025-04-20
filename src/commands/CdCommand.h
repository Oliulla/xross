// commands/CdCommand.h
#ifndef CDCOMMAND_H
#define CDCOMMAND_H

#include "ICommand.h"
#include <QDir>
#include <QStringList>

class CdCommand : public ICommand {
public:
    QString name() const override {
        return "cd";
    }

    QString execute(const QStringList &args) override {
        if (args.isEmpty()) {
            return "Usage: cd <path>";
        }

        QString path = args.join(" ");
        QDir dir;
        if (dir.cd(path)) {
            QDir::setCurrent(dir.absolutePath());  // changes the working dir globally
            return "";
        } else {
            return QString("cd: no such file or directory: %1").arg(path);
        }
    }
};

#endif // CDCOMMAND_H
