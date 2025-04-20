// commands/CommandManager.h
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "ICommand.h"
#include "HelpCommand.h"
#include "PwdCommand.h"
#include <QMap>
#include <QStringList>

class CommandManager {
public:
    CommandManager() {
        registerCommand(new HelpCommand());
        registerCommand(new PwdCommand());
        // registerCommand(new ClearCommand());
    }

    ~CommandManager() {
        qDeleteAll(commands);
    }

    QString handle(const QString &input) {
        QStringList tokens = input.split(" ", Qt::SkipEmptyParts);
        if (tokens.isEmpty()) return "";
    
        QString commandName = tokens.takeFirst(); // extract the command
        if (commands.contains(commandName)) {
            return commands[commandName]->execute(tokens); // now `tokens` is a QStringList
        } else {
            return QString("Unknown command: %1").arg(commandName);
        }
    }
    

private:
    QMap<QString, ICommand*> commands;

    void registerCommand(ICommand *cmd) {
        commands[cmd->name()] = cmd;
    }
};

#endif // COMMANDMANAGER_H
