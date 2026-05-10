#ifndef TRANSACTION
#define TRANSACTION 

#include <string>
#include <vector>
#include <chrono>

enum class TransactionType{
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER,
    INTEREST_PAYMENT,   
    FEE_DEDUCTION
};

class Transaction{

private:

    std::string Id;
    double Amount;
    TransactionType Type;
    std::chrono::system_clock::time_point Timestamp;
    
    std::string generateId(std::chrono::system_clock::time_point Timestamp) {
    std::hash<long long> hasher;
    auto duration = Timestamp.time_since_epoch();
    auto count = duration.count();
    return std::to_string(hasher(count));
}

public:
    Transaction(std::string Id, double Amount, TransactionType Type, std::chrono::system_clock::time_point Timestamp)
    : Id(generateId( Timestamp)), Amount(Amount), Type(Type), Timestamp(Timestamp){}

    std::chrono::system_clock::time_point getTimestamp() const { return Timestamp;}

    double getAmount(){return Amount;}
    std::string getId(){return Id;}
    TransactionType getType(){return Type;}

};

#endif