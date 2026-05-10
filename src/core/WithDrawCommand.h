#ifndef WITHDRAW_COMMAND_H
#define WITHDRAW_COMMAND_H

#include "ICommand.h"
#include "Account.h"

class WithDrawCommand: public ICommand {

    Account& account;  
    double amount;    
    bool isExecuted;

public:

    WithDrawCommand(Account& account, double amount,bool isExecuted) : account(account), amount(amount), isExecuted(false) {}

    bool Execute() override {
        isExecuted = account.withdraw(amount);
        return isExecuted;
    }

    void Undo() override {
        if (isExecuted) {
            account.deposit(amount);
            isExecuted = false;
        }
    }
};
#endif