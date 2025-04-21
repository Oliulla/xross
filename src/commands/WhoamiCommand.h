// commands/WhoamiCommand.h
#ifndef WHOAMICOMMAND_H
#define WHOAMICOMMAND_H

#include "ICommand.h"
#include <QProcess>
#include <QSysInfo>

class WhoamiCommand : public ICommand {
public:
    QString name() const override {
        return "whoami";
    }

    QString execute(const QStringList &args) override {
        Q_UNUSED(args);

        // Cross-platform support: try common env vars
        QString username = qEnvironmentVariable("USERNAME"); // Windows
        if (username.isEmpty()) {
            username = qEnvironmentVariable("USER"); // Unix-like
        }

        if (!username.isEmpty()) {
            return username;
        } else {
            return "Unable to determine user.";
        }
    }
};

#endif // WHOAMICOMMAND_H
