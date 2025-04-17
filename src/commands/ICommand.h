#ifndef ICOMMAND_H
#define ICOMMAND_H

#include <QString>

class ICommand {
    public:
        virtual ~ICommand() = default;
        virtual QString name() const = 0;
        virtual QString execute(const QStringList &args) = 0;
};

#endif // ICOMMAND_H
