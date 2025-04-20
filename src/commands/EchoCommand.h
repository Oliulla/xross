// commands/EchoCommand.h
#ifndef ECHOCOMMAND_H
#define ECHOCOMMAND_H

#include "ICommand.h"
#include <QStringList>

class EchoCommand : public ICommand {
public:
    QString name() const override {
        return "echo";
    }

    QString execute(const QStringList &args) override {
        return args.join(" ");
    }
};

#endif // ECHOCOMMAND_H
