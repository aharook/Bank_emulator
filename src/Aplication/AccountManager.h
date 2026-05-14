#ifndef ACCOUNTMANAGER_H
#define ACCOUNTMANAGER_H

#include "../core/Account.h"
#include "../core/Observer.h"
#include "../Infrastructure/AccountSaver.h"
#include <map>
#include <memory>

class AccountManager {
private:
    std::map<std::string, std::shared_ptr<Account>> accounts;
    AccountSaver saver;
    IObserver* globalObserver = nullptr;

public:
    AccountManager(const std::string& filePath);
    ~AccountManager();

    void createAccount(const std::string& number, double balance);
    void deleteAccount(const std::string& number);
    std::shared_ptr<Account> getAccount(const std::string& number);
    bool accountExists(const std::string& number) const;
    std::map<std::string, std::shared_ptr<Account>> getAllAccounts() const;
    
    void loadAll();
    void saveAll();
    void attachGlobalObserver(IObserver* observer);
};

#endif