#include "AccountManager.h"
#include <stdexcept>

AccountManager::AccountManager(const std::string& filePath) : saver(filePath) {
    loadAll();
}

AccountManager::~AccountManager() {
    saveAll();
}

void AccountManager::createAccount(const std::string& number, double balance) {
    if(number.empty() ) { 
        throw std::invalid_argument("Number cannot be empty!");
    }

    if(balance < 0 ) { 
        throw std::invalid_argument(" balance cannot be negative");
    }

    if (accounts.find(number) == accounts.end()) {
        auto account = std::make_shared<Account>(number, balance);
        if (globalObserver != nullptr) {
            account->attach(globalObserver);
        }
        accounts[number] = account;
    }

}

void AccountManager::deleteAccount(const std::string& number) {
    if (number.empty()) {
        throw std::invalid_argument("Account number cannot be empty!");
    }
    accounts.erase(number);
}

std::shared_ptr<Account> AccountManager::getAccount(const std::string& number) {
    if (number.empty()) {
        throw std::invalid_argument("Account number cannot be empty!");
    }
    auto it = accounts.find(number);
    if (it != accounts.end()) {
        return it->second;
    }
    return nullptr;
}

bool AccountManager::accountExists(const std::string& number) const {
    return accounts.find(number) != accounts.end();
}

std::map<std::string, std::shared_ptr<Account>> AccountManager::getAllAccounts() const {
    return accounts;
}

void AccountManager::loadAll() {
    const auto& allAccounts = saver.getAll();
    for (const auto& account : allAccounts) {
        accounts[account.getAccountNumber()] = std::make_shared<Account>(account);
    }
}

void AccountManager::saveAll() {
    for (const auto& pair : accounts) {
        saver.save(*pair.second);
    }
    saver.saveToFile();
}

void AccountManager::attachGlobalObserver(IObserver* observer) {
    globalObserver = observer;
    for (auto& pair : accounts) {
        pair.second->attach(observer);
    }
}
