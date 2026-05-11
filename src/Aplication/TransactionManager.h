#ifndef TRANSACTION_MANAGER_H
#define TRANSACTION_MANAGER_H

#include <stack>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "../core/ICommand.h"

class TransactionManager {
private:
    std::stack<std::shared_ptr<ICommand>> commandHistory;

public:
    void executeCommand(std::shared_ptr<ICommand> command) {
        if (!command) {
            throw std::invalid_argument("Command cannot be null!");
        }
        if (command->Execute()) {
            commandHistory.push(command);
        } else {
            std::cout << "Transaction has been canceled " << std::endl;
        }
    }

    void undoLast() {
        if (!commandHistory.empty()) {
            auto lastCommand = commandHistory.top();
            lastCommand->Undo();
            commandHistory.pop();
            std::cout << "Last transaction has been canceled." << std::endl;
        } else {
            std::cout << "Has no transaction to cancel" << std::endl;
        }
    }
};

#endif
