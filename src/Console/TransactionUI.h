#pragma once
#include <iostream>

class BankService;

class TransactionUI {
private:
    BankService* bankService;

public:
    TransactionUI(BankService* service);
    void run();
};
