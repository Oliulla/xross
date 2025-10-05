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

        registerCommand(new TreeCommand());
    }

    ~CommandManager() {
        qDeleteAll(commands);
    }

   QString handle(const QString &input) {
        QString normalizedInput = input.trimmed();
        if (normalizedInput.isEmpty()) return "";

        commandHistory.append(normalizedInput);

        QStringList tokens = normalizedInput.split(" ", Qt::SkipEmptyParts);
        if (tokens.isEmpty()) return "";

        QString commandName = tokens.takeFirst();

        // Check alias (case-insensitive)
        QString lowerCommand = commandName.toLower();
        if (aliases.contains(lowerCommand)) {
            commandName = aliases[lowerCommand];
        }

        // Try built-in command first
        if (commands.contains(commandName)) {
            return commands[commandName]->execute(tokens);
        }

        // Try executing as system command
        QProcess process;
        process.setProcessChannelMode(QProcess::MergedChannels); // Merge stdout & stderr
        process.start(commandName, tokens);
        
        if (!process.waitForStarted(2000)) {
            return QString("'%1' is not recognized as an internal or external command,\noperable program or batch file.").arg(commandName);
        }

        process.waitForFinished(-1);
        QString output = process.readAllStandardOutput();
        QString errorOutput = process.readAllStandardError();

        if (!errorOutput.isEmpty())
            return errorOutput;
        else if (!output.isEmpty())
            return output;
        else
            return QString("");
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
