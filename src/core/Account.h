#ifndef ACCOUNT
#define ACCOUNT

#include <string>
#include <vector>
#include <algorithm>
#include "Transaction.h"
#include "Observer.h"
#include "TransactionEvent.h"
#include "InterestStrategy.h"

class Account {
private:
    std::string accountNumber;
    double balance;
    Strategy* strategy;
    std::vector<IObserver*> observers;
    std::vector<Transaction> history;

public:
    Account(std::string accNumber, double initialBalance = 0.0);

    ~Account();

    std::string getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    std::vector<Transaction> getHistory() const { return history; }

    void setInterestStrategy(Strategy* s) {
        strategy = s;
    }

    void applyInterest() {
        if (strategy != nullptr) {
            double interest = strategy->calculate(balance);
            balance += interest;
            Transaction trans("", interest, TransactionType::INTEREST_PAYMENT, std::chrono::system_clock::now());
            history.push_back(trans);
            
            TransactionEvent event(TransactionType::INTEREST_PAYMENT, interest, balance);
            notifyObservers(event);
        }
    }

    void attach(IObserver* observer) {
        if (observer != nullptr) {
            observers.push_back(observer);
        }
    }

    void notifyObservers(const TransactionEvent& event) {
        for (IObserver* observer : observers) {
            if (observer != nullptr) {
                observer->update(event);
            }
        }
    }

    bool deposit(double amount) {
        if (amount <= 0) return false;
        balance += amount;
        Transaction trans("", amount, TransactionType::DEPOSIT, std::chrono::system_clock::now());
        history.push_back(trans);
        
        TransactionEvent event(TransactionType::DEPOSIT, amount, balance);
        notifyObservers(event);
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        Transaction trans("", amount, TransactionType::WITHDRAWAL, std::chrono::system_clock::now());
        history.push_back(trans);
        
        TransactionEvent event(TransactionType::WITHDRAWAL, amount, balance);
        notifyObservers(event);
        return true;
    }

    bool transfer(Account& recipient, double amount) {
        if (!withdraw(amount)) return false;
        recipient.deposit(amount);
        Transaction trans("", amount, TransactionType::TRANSFER, std::chrono::system_clock::now());
        history.push_back(trans);
        
        TransactionEvent event(TransactionType::TRANSFER, amount, balance, 
                             "to account " + recipient.getAccountNumber());
        notifyObservers(event);
        return true;
    }

    void deductFee(double fee) {
        if (fee > 0 && balance >= fee) {
            balance -= fee;
            Transaction trans("", fee, TransactionType::FEE_DEDUCTION, std::chrono::system_clock::now());
            history.push_back(trans);
            
            TransactionEvent event(TransactionType::FEE_DEDUCTION, fee, balance);
            notifyObservers(event);
        }
    }
};

#endif