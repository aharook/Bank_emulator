#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>

class IObserver {
public:
    virtual ~IObserver() = default;

    virtual void update(std::string Message) = 0;
};

#endif