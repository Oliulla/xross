// commands/CommandManager.h
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "CommandHeaders.h"
#include <QMap>
#include <QStringList>

class CommandManager {
public:
    CommandManager() {
        registerCommand(new HelpCommand());
        registerCommand(new PwdCommand());
        registerCommand(new CdCommand());
        
        ClearCommand* clearCmd = new ClearCommand();
        registerCommand(clearCmd);
        commands["cls"] = clearCmd; 

        ListCommand* listCmd = new ListCommand();
        registerCommand(listCmd);
        commands["dir"] = listCmd; 

        registerCommand(new EchoCommand());
        registerCommand(new WhoamiCommand());

        CatCommand* catCmd = new CatCommand();
        registerCommand(catCmd);
        commands["type"] = catCmd; 

        registerCommand(new MkdirCommand());
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
