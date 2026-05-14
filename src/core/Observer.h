#ifndef OBSERVER_H
#define OBSERVER_H

#include "TransactionEvent.h"

class IObserver {
public:
    virtual ~IObserver() = default;

    virtual void update(const TransactionEvent& event) = 0;
};

#endif