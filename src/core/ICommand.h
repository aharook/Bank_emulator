#ifndef ICOMMAND_H
#define ICOMMAND_H

class ICommand {
    public:

    virtual ~ICommand() = default;

    virtual bool Execute() = 0;

    virtual void Undo() = 0;
};
#endif