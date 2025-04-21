// commands/DateCommand.h
#ifndef DATECOMMAND_H
#define DATECOMMAND_H

#include "ICommand.h"
#include <QDateTime>

class DateCommand : public ICommand {
public:
    QString name() const override {
        return "date";
    }

    QString execute(const QStringList &args) override {
        Q_UNUSED(args);
        QDateTime now = QDateTime::currentDateTime();
        return now.toString("dddd, dd MMMM yyyy - hh:mm:ss ap");
    }
};

#endif // DATECOMMAND_H
