#ifndef TRANSACTION_EVENT_H
#define TRANSACTION_EVENT_H

#include "Transaction.h"
#include <string>

struct TransactionEvent {
    TransactionType type;
    double amount;
    double newBalance;
    std::string details;  

    TransactionEvent(TransactionType t, double amt, double balance, const std::string& det = "")
        : type(t), amount(amt), newBalance(balance), details(det) {}
};

#endif
