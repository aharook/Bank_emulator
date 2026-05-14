#pragma once
#include <iostream>

class BankService;

class AccountUI {
private:
    BankService* bankService;

public:
    AccountUI(BankService* service);
    void run();
};
