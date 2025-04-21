#ifndef HISTORYCOMMAND_H
#define HISTORYCOMMAND_H

#include "ICommand.h"
#include "CommandManager.h"

class HistoryCommand : public ICommand {
public:
    HistoryCommand(QStringList *historyRef) : history(historyRef) {}

    QString name() const override {
        return "history";
    }

    QString execute(const QStringList &args) override {
        Q_UNUSED(args);
        QString result;
        for (int i = 0; i < history->size(); ++i) {
            result += QString("%1  %2\n").arg(i + 1).arg(history->at(i));
        }
        return result.isEmpty() ? "No history available." : result;
    }

private:
    QStringList *history;
};

#endif // HISTORYCOMMAND_H
