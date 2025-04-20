// commands/ClearCommand.h
#ifndef CLEARCOMMAND_H
#define CLEARCOMMAND_H

#include "ICommand.h"
#include <QStringList>

class ClearCommand : public ICommand {
public:
    QString name() const override {
        return "clear";
    }

    QString execute(const QStringList &args) override {
        Q_UNUSED(args);
        return QString("__CLEAR__");
    }
};

#endif // CLEARCOMMAND_H