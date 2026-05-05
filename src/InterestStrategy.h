#ifndef INTERESTSTRATEGY
#define INTERESTSTRATEGY


class InterestStrategy{
public:

virtual double calculate (double balance) = 0; 

virtual ~InterestStrategy() = default;

};


class SavingsInterest: public InterestStrategy {

public:
     double calculate(double balance)   override  {
        if (balance <= 0) return 0;
        
        return balance * 0.02; 
    }
};

class FixedDepositInterest: public InterestStrategy {

public:
     double calculate(double balance) override {
        if (balance <= 0) return 0;
        
        return balance * 0.10;
    }
};

class PremiumInterest: public InterestStrategy {

public:
    double calculate(double balance) override {
        if (balance <= 0) return 0;

        return 500.0 + (balance * 0.05); 
    }
};
#endif