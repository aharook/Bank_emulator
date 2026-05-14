#pragma once
#include <iostream>

class BankService;

class ClientUI {
private:
    BankService* bankService;

public:
    ClientUI(BankService* service);
    void run();
};
