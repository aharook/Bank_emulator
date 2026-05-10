#ifndef DEPOSITECOMMAND_H
#define DEPOSITECOMMAND_H

#include "ICommand.h"
#include "Account.h"

class DepositCommand: public ICommand {

    Account& account;  
    double amount;    
    bool isExecuted;

public:

    DepositCommand(Account& account, double amount,bool isExecuted) : account(account), amount(amount), isExecuted(false) {}

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