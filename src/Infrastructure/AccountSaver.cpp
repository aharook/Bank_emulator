#include "AccountSaver.h"
#include "../core/Account.h"
#include <iostream>
#include <fstream>

void AccountSaver::save(const Account account) {
    auto it = std::find_if(cache.begin(), cache.end(),
        [&account](const Account& acc) {
            return acc.getAccountNumber() == account.getAccountNumber();
        });
    
    if (it != cache.end()) {
        cache.erase(it);
    }
    
    cache.push_back(account);
}

const std::vector<Account>& AccountSaver::getAll() const {
    return cache;
}

Account AccountSaver::findByNumber(const std::string& accountNumber) {
    auto it = std::find_if(cache.begin(), cache.end(),
        [&accountNumber](const Account& acc) {
            return acc.getAccountNumber() == accountNumber;
        });
    
    if (it != cache.end()) {
        return *it;
    }
    
    throw std::runtime_error("Account not found: " + accountNumber);
}

const Account AccountSaver::findByNumber(const std::string& accountNumber) const {
    auto it = std::find_if(cache.begin(), cache.end(),
        [&accountNumber](const Account& acc) {
            return acc.getAccountNumber() == accountNumber;
        });
    
    if (it != cache.end()) {
        return *it;
    }
    
    throw std::runtime_error("Account not found: " + accountNumber);
}

void AccountSaver::loadFromFile() {
    std::ifstream file(filePath_);
    
    if (!file.is_open()) {
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        size_t commaPos = line.find('|');
        if (commaPos == std::string::npos) continue;
        
        std::string accountNumber = line.substr(0, commaPos);
        double balance = std::stod(line.substr(commaPos + 1));
        
        Account acc(accountNumber, balance);
        cache.push_back(acc);
    }
    
    file.close();
}

void AccountSaver::saveToFile() {
    std::ofstream file(filePath_);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath_ << std::endl;
        return;
    }
    
    for (const Account& acc : cache) {
        file << acc.getAccountNumber() << "|" << acc.getBalance() << std::endl;
    }
    
    file.close();
}