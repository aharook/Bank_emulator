#include "BankService.h"
#include <stdexcept>

BankService::BankService(const std::string& accountsPath, const std::string& clientsPath) {
    if (accountsPath.empty()) {
        throw std::invalid_argument("Accounts file path cannot be empty!");
    }
    if (clientsPath.empty()) {
        throw std::invalid_argument("Clients file path cannot be empty!");
    }
    
    accountManager = std::make_unique<AccountManager>(accountsPath);
    clientManager = std::make_unique<ClientManager>(clientsPath);
    transactionManager = std::make_unique<TransactionManager>();
}

BankService::~BankService() = default;

AccountManager* BankService::getAccountManager() {
    return accountManager.get();
}

ClientManager* BankService::getClientManager() {
    return clientManager.get();
}

TransactionManager* BankService::getTransactionManager() {
    return transactionManager.get();
}
