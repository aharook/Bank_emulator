#ifndef BANKSERVICE_H
#define BANKSERVICE_H

#include "AccountManager.h"
#include "ClientManager.h"
#include "TransactionManager.h"
#include <memory>

class BankService {
private:
    std::unique_ptr<AccountManager> accountManager;
    std::unique_ptr<ClientManager> clientManager;
    std::unique_ptr<TransactionManager> transactionManager;

public:
    BankService(const std::string& accountsPath, const std::string& clientsPath);
    ~BankService();
    
    AccountManager* getAccountManager();
    ClientManager* getClientManager();
    TransactionManager* getTransactionManager();
};

#endif
