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
        registerAlias("cls", clearCmd);

        ListCommand* listCmd = new ListCommand();
        registerCommand(listCmd);
        registerAlias("dir", listCmd);

        registerCommand(new EchoCommand());

        registerCommand(new WhoamiCommand());

        CatCommand* catCmd = new CatCommand();
        registerCommand(catCmd);
        registerAlias("type", catCmd);

        registerCommand(new MkdirCommand());

        RmCommand* rmCmd = new RmCommand();
        registerCommand(rmCmd);
        registerAlias("del", rmCmd);
        registerAlias("rmdir", rmCmd);

        DateCommand* dateCmd = new DateCommand();
        registerCommand(dateCmd);
        registerAlias("get-date", dateCmd);
        registerAlias("date /t", dateCmd);
        // registerAlias("time /t", dateCmd);

        registerCommand(new ExitCommand());
        registerCommand(new HistoryCommand(&commandHistory));
    }

    ~CommandManager() {
        qDeleteAll(commands);
    }

    QString handle(const QString &input) {
        QString normalizedInput = input.trimmed();
        if (normalizedInput.isEmpty()) return "";
    
        commandHistory.append(normalizedInput);
    
        QString lowered = normalizedInput.toLower();
        if (aliases.contains(lowered)) {
            lowered = aliases[lowered];
        }
    
        QStringList tokens = lowered.split(" ", Qt::SkipEmptyParts);
        if (tokens.isEmpty()) return "";
    
        QString commandName = tokens.takeFirst();
        if (commands.contains(commandName)) {
            return commands[commandName]->execute(tokens);
        } else {
            return QString("Unknown command: %1").arg(commandName);
        }
    }
    
    

private:
    QMap<QString, ICommand*> commands;
    QMap<QString, QString> aliases;
    QStringList commandHistory;

    void registerCommand(ICommand *cmd) {
        commands[cmd->name()] = cmd;
    }

    void registerAlias(const QString& alias, ICommand* cmd) {
        commands[alias.toLower()] = cmd;
    }
};

#endif // COMMANDMANAGER_H
