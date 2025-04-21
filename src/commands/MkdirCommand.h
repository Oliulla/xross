// commands/MkdirCommand.h
#ifndef MKDIRCOMMAND_H
#define MKDIRCOMMAND_H

#include "ICommand.h"
#include <QDir>

class MkdirCommand : public ICommand {
public:
    QString name() const override {
        return "mkdir";
    }

    QString execute(const QStringList &args) override {
        if (args.isEmpty()) {
            return "Usage: mkdir <directory_name>";
        }

        QString dirName = args.first();
        QDir dir;
        if (dir.exists(dirName)) {
            return QString("Directory already exists: %1").arg(dirName);
        }

        if (dir.mkdir(dirName)) {
            return QString("Directory created: %1").arg(dirName);
        } else {
            return QString("Failed to create directory: %1").arg(dirName);
        }
    }
};

#endif // MKDIRCOMMAND_H
