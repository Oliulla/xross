// commands/CatCommand.h
#ifndef CATCOMMAND_H
#define CATCOMMAND_H

#include "ICommand.h"
#include <QFile>
#include <QTextStream>

class CatCommand : public ICommand {
public:
    QString name() const override {
        return "cat";
    }

    QString execute(const QStringList &args) override {
        if (args.isEmpty()) {
            return "Usage: cat <filename>";
        }

        QString filePath = args.first();
        QFile file(filePath);

        if (!file.exists()) {
            return QString("File not found: %1").arg(filePath);
        }

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return QString("Failed to open file: %1").arg(filePath);
        }

        QTextStream in(&file);
        return in.readAll();
    }
};

#endif // CATCOMMAND_H
