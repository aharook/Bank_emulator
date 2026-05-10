#ifndef ACCOUNT
#define ACCOUNT

#include <string>
#include <vector>
#include <algorithm>
#include "Transaction.h"
#include "Observer.h"
#include "NotificationService.h"
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
            notify("Interest applied: +" + std::to_string(interest));
        }
    }

    void attach(IObserver* observer) {
        if (observer != nullptr) {
            observers.push_back(observer);
        }
    }

    void notify(std::string message) {
        for (IObserver* observer : observers) {
            if (observer != nullptr) {
                observer->update(message);
            }
        }
    }

    bool deposit(double amount) {
        if (amount <= 0) return false;
        balance += amount;
        Transaction trans("", amount, TransactionType::DEPOSIT, std::chrono::system_clock::now());
        history.push_back(trans);
        notify("Deposit: +" + std::to_string(amount) + " New balance: " + std::to_string(balance));
        return true;
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) return false;
        balance -= amount;
        Transaction trans("", amount, TransactionType::WITHDRAWAL, std::chrono::system_clock::now());
        history.push_back(trans);
        notify("Withdrawal: -" + std::to_string(amount) + " New balance: " + std::to_string(balance));
        return true;
    }

    bool transfer(Account& recipient, double amount) {
        if (!withdraw(amount)) return false;
        recipient.deposit(amount);
        Transaction trans("", amount, TransactionType::TRANSFER, std::chrono::system_clock::now());
        history.push_back(trans);
        notify("Transfer: -" + std::to_string(amount) + " to account " + recipient.getAccountNumber());
        return true;
    }

    void deductFee(double fee) {
        if (fee > 0 && balance >= fee) {
            balance -= fee;
            Transaction trans("", fee, TransactionType::FEE_DEDUCTION, std::chrono::system_clock::now());
            history.push_back(trans);
            notify("Fee deducted: -" + std::to_string(fee));
        }
    }
};

#endif