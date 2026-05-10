#ifndef INTERESTSTRATEGY
#define INTERESTSTRATEGY

#include "Transaction.h"

class Strategy{
public:

virtual double calculate (double balance) = 0; 

virtual ~Strategy() = default;

};


class SavingsInterest: public Strategy {

public:
     double calculate(double balance)   override  {
        if (balance <= 0) return 0;
        
        return balance * 0.02; 
    }
};

class FixedDepositInterest: public Strategy {

public:
     double calculate(double balance) override {
        if (balance <= 0) return 0;
        
        return balance * 0.10;
    }
};

class PremiumInterest: public Strategy {

public:
    double calculate(double balance) override {
        if (balance <= 0) return 0;

        return 500.0 + (balance * 0.05); 
    }
};

class StrategyFactory {
public:
    static Strategy* createStrategy(TransactionType type);
};
#endif