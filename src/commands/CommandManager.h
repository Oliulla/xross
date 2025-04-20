// commands/CommandManager.h
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "ICommand.h"
#include "HelpCommand.h"
#include "PwdCommand.h"
#include "CdCommand.h"
#include "ClearCommand.h"
#include "ListCommand.h"
#include <QMap>
#include <QStringList>

class CommandManager {
public:
    CommandManager() {
        registerCommand(new HelpCommand());
        registerCommand(new PwdCommand());
        registerCommand(new CdCommand());
        
        // Registering the clear command and its alias
        ClearCommand* clearCmd = new ClearCommand();
        registerCommand(clearCmd);
        // registerAlias("cls", clearCmd);
        commands["cls"] = clearCmd; // Alias

        // Registering the list command and its alias
        ListCommand* listCmd = new ListCommand();
        registerCommand(listCmd);
        // registerAlias("dir", clearCmd);
        commands["dir"] = listCmd; // Alias

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

    void registerAlias(const QString& alias, ICommand* cmd) {
        commands[alias] = cmd;
    }
};

#endif // COMMANDMANAGER_H
