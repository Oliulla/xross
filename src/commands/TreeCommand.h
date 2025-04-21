#ifndef TREECOMMAND_H
#define TREECOMMAND_H

#include "ICommand.h"
#include <QDir>
#include <QString>
#include <QStringList>

class TreeCommand : public ICommand {
public:
    QString name() const override {
        return "tree";
    }

    QString execute(const QStringList &args) override {
        QString path = args.isEmpty() ? QDir::currentPath() : args.first();
        QDir dir(path);

        if (!dir.exists()) {
            return QString("Directory not found: %1").arg(path);
        }

        QString output;
        printTree(dir, "", output);
        return output;
    }

private:
    void printTree(const QDir &dir, const QString &prefix, QString &output) {
        QFileInfoList entries = dir.entryInfoList(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot, QDir::Name);

        for (int i = 0; i < entries.size(); ++i) {
            QFileInfo entry = entries[i];
            bool last = (i == entries.size() - 1);
            QString connector = last ? "└── " : "├── ";

            output += prefix + connector + entry.fileName() + "\n";

            if (entry.isDir()) {
                QString newPrefix = prefix + (last ? "    " : "│   ");
                printTree(QDir(entry.absoluteFilePath()), newPrefix, output);
            }
        }
    }
};

#endif // TREECOMMAND_H
