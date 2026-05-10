#include "Account.h"

Account::Account(std::string accNumber, double initialBalance)
    : accountNumber(accNumber), balance(initialBalance), strategy(nullptr) {
}

Account::~Account() {
    observers.clear();
    history.clear();
}
