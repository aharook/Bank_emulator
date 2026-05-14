#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <iostream>
#include <string>
#include "../core/Observer.h"
#include "../core/TransactionEvent.h"

class NotificationService : public IObserver {
private:
    std::string serviceName;

    std::string formatEvent(const TransactionEvent& event) const {
        std::string typeStr;
        switch (event.type) {
            case TransactionType::DEPOSIT:
                typeStr = "Deposit";
                break;
            case TransactionType::WITHDRAWAL:
                typeStr = "Withdrawal";
                break;
            case TransactionType::TRANSFER:
                typeStr = "Transfer";
                break;
            case TransactionType::INTEREST_PAYMENT:
                typeStr = "Interest Payment";
                break;
            case TransactionType::FEE_DEDUCTION:
                typeStr = "Fee Deduction";
                break;
            default:
                typeStr = "Unknown";
        }

        std::string message = typeStr + ": " + std::to_string(event.amount) + " | New balance: " + std::to_string(event.newBalance);
        
        if (!event.details.empty()) {
            message += " | " + event.details;
        }
        
        return message;
    }

public:
    NotificationService(std::string name = "NotificationService")
        : serviceName(name) {
    }

    virtual ~NotificationService() = default;

    void update(const TransactionEvent& event) override {
        std::cout << "[" << serviceName << "] " << formatEvent(event) << std::endl;
    }

    std::string getServiceName() const {
        return serviceName;
    }
};

#endif
