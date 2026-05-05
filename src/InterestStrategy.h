#ifndef INTERESTSTRATEGY
#define INTERESTSTRATEGY


class InterestStrategy{
public:

virtual double calculate (double balance) = 0; 

virtual ~InterestStrategy() = default;

};

#endif