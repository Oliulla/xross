// commands/ListCommand.h
#ifndef LISTCOMMAND_H
#define LISTCOMMAND_H

#include "ICommand.h"
#include <QDir>
#include <QStringList>

class ListCommand : public ICommand {
public:
    QString name() const override {
        return "ls"; // We'll register both "ls" and "dir"
    }

    QString execute(const QStringList &args) override {
        Q_UNUSED(args);
        QDir dir(QDir::currentPath());
        QStringList entries = dir.entryList(QDir::NoDotAndDotDot | QDir::AllEntries);
        
        if (entries.isEmpty()) {
            return "[Empty Directory]";
        }

        QString output;
        for (const QString &entry : entries) {
            output += entry + "\n";
        }
        return output.trimmed();
    }
};

#endif // LISTCOMMAND_H
