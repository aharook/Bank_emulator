#pragma once
#include <iostream>
#include "NotificationService.h"
#include <memory>

class BankService;

class MainMenu {
private:
    BankService* bankService;
    std::unique_ptr<NotificationService> notificationService;

public:
    MainMenu(BankService* service);
    void run();
};
