#ifndef EXITCOMMAND_H
#define EXITCOMMAND_H

#include "ICommand.h"
#include <QCoreApplication>

class ExitCommand : public ICommand {
public:
    QString name() const override {
        return "exit";
    }

    QString execute(const QStringList &args) override {
        Q_UNUSED(args);
        QCoreApplication::quit();  // Exits the application
        return "Exiting Xross terminal...";
    }
};

#endif // EXITCOMMAND_H
