// commands/RmCommand.h
#ifndef RMCOMMAND_H
#define RMCOMMAND_H

#include "ICommand.h"
#include <QFileInfo>
#include <QDir>

class RmCommand : public ICommand {
public:
    QString name() const override {
        return "rm";
    }

    QString execute(const QStringList &args) override {
        if (args.isEmpty()) {
            return "Usage: rm <file-or-directory>";
        }

        QString path = args[0];
        QFileInfo info(path);

        if (!info.exists()) {
            return QString("No such file or directory: %1").arg(path);
        }

        if (info.isDir()) {
            QDir dir(path);
            if (dir.removeRecursively()) {
                return QString("Directory '%1' deleted successfully").arg(path);
            } else {
                return QString("Failed to delete directory: %1").arg(path);
            }
        } else {
            QFile file(path);
            if (file.remove()) {
                return QString("File '%1' deleted successfully").arg(path);
            } else {
                return QString("Failed to delete file: %1").arg(path);
            }
        }
    }
};

#endif // RMCOMMAND_H
