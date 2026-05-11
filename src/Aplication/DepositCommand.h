#ifndef DEPOSITECOMMAND_H
#define DEPOSITECOMMAND_H

#include "ICommand.h"
#include "Account.h"
#include <stdexcept>

class DepositCommand: public ICommand {

    Account& account;  
    double amount;    
    bool isExecuted;

public:

    DepositCommand(Account& account, double amount, bool isExecuted) 
        : account(account), amount(amount), isExecuted(false) {
        if (amount <= 0) {
            throw std::invalid_argument("Deposit amount must be positive!");
        }
    }

    bool Execute() override {
        isExecuted = account.deposit(amount);
        return isExecuted;
    }

    void Undo() override {
        if (isExecuted) {
            account.withdraw(amount);
            isExecuted = false;
        }
    }
};
#endif