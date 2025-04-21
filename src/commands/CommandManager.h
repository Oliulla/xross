// commands/CommandManager.h
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "CommandHeaders.h"
#include <QMap>
#include <QStringList>

class CommandManager {
public:
    CommandManager() {
        // Core commands
        registerCommand(new HelpCommand());
        registerCommand(new PwdCommand());
        registerCommand(new CdCommand());

        // Clear / CLS
        ClearCommand* clearCmd = new ClearCommand();
        registerCommand(clearCmd);
        registerAlias("cls", clearCmd);

        // LS / DIR
        ListCommand* listCmd = new ListCommand();
        registerCommand(listCmd);
        registerAlias("dir", listCmd);

        // Echo
        registerCommand(new EchoCommand());

        // Whoami
        registerCommand(new WhoamiCommand());

        // Cat / Type
        CatCommand* catCmd = new CatCommand();
        registerCommand(catCmd);
        registerAlias("type", catCmd);

        // Mkdir
        registerCommand(new MkdirCommand());

        // RM / DEL / RMDIR
        RmCommand* rmCmd = new RmCommand();
        registerCommand(rmCmd);
        registerAlias("del", rmCmd);
        registerAlias("rmdir", rmCmd);

        // Date / Get-Date / etc.
        DateCommand* dateCmd = new DateCommand();
        registerCommand(dateCmd);
        registerAlias("get-date", dateCmd);
        registerAlias("date /t", dateCmd);
        registerAlias("time /t", dateCmd);
    }

    ~CommandManager() {
        qDeleteAll(commands);
    }

    QString handle(const QString &input) {
        QString trimmed = input.trimmed();
        if (trimmed.isEmpty()) return "";

        QStringList tokens = trimmed.split(" ", Qt::SkipEmptyParts);
        if (tokens.isEmpty()) return "";

        QString commandName = tokens.takeFirst().toLower();

        if (commands.contains(commandName)) {
            return commands[commandName]->execute(tokens);
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
        commands[alias.toLower()] = cmd;
    }
};

#endif // COMMANDMANAGER_H
