#pragma once
#include <iostream>

class BankService;

class MainMenu {
private:
    BankService* bankService;

public:
    MainMenu(BankService* service);
    void run();
};
