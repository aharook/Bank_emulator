#ifndef CLIENT
#define CLIENT

#include <string>
#include <vector>
#include "Account.h"

class Client {
private:
std::string Name;
std::string TaxId;
std::vector<Account> Accounts;

std::string generateTaxId(std::string Name) {
    std::hash<std::string> hasher;
    return std::to_string(hasher(Name));
}

public:

Client (std::string Name, std::vector<Account> Accounts = {}) : Name(Name), TaxId(generateTaxId(Name)), Accounts(Accounts) {};

std::string getName(){return Name;}
std::string getTaxId(){return TaxId;}
std::vector<Account> getAccount(){return Accounts;}

void AddAccount(Account account){
    Accounts.push_back(account);
}
};

#endif