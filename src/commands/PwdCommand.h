// commands/PwdCommand.h
#ifndef PWDCOMMAND_H
#define PWDCOMMAND_H

#include "ICommand.h"
#include <QDir>
#include <QStringList>

class PwdCommand : public ICommand {
public:
    QString name() const override {
        return "pwd";
    }

    QString execute(const QStringList &args) override {
        Q_UNUSED(args);
        return QDir::currentPath();
    }
};

#endif // PWDCOMMAND_H
