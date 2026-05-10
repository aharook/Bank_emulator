#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include <iostream>
#include <string>
#include "Observer.h"

class NotificationService : public IObserver {
private:
    std::string serviceName;

public:
    NotificationService(std::string name = "NotificationService")
        : serviceName(name) {
    }

    virtual ~NotificationService() = default;

    void update(std::string message) override {
        std::cout << "[" << serviceName << "] Notification: " << message << std::endl;
    }

    std::string getServiceName() const {
        return serviceName;
    }
};

#endif
