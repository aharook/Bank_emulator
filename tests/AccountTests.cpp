#include <gtest/gtest.h>
#include "../src/core/Account.h"
#include "../src/core/Observer.h"
#include "../src/core/InterestStrategy.h"

class MockObserver : public IObserver {
public:
    std::vector<std::string> messages;
    
    void update(std::string message) override {
        messages.push_back(message);
    }
    
    int getMessageCount() const {
        return messages.size();
    }
    
    std::string getLastMessage() const {
        if (messages.empty()) return "";
        return messages.back();
    }
};

class MockStrategy : public Strategy {
private:
    double rate;
    
public:
    MockStrategy(double r) : rate(r) {}
    
    double calculate(double balance) override {
        return balance * rate;
    }
};

class AccountDepositTests : public ::testing::Test {
protected:
    Account account{"ACC001", 1000.0};
    MockObserver observer;
    
    void SetUp() override {
        account.attach(&observer);
    }
};

TEST_F(AccountDepositTests, ValidDepositIncreasesBalance) {
    double initialBalance = account.getBalance();
    EXPECT_TRUE(account.deposit(500.0));
    EXPECT_EQ(account.getBalance(), initialBalance + 500.0);
}

TEST_F(AccountDepositTests, NegativeDepositFails) {
    double initialBalance = account.getBalance();
    EXPECT_FALSE(account.deposit(-100.0));
    EXPECT_EQ(account.getBalance(), initialBalance);
}

TEST_F(AccountDepositTests, DepositCreatesTransaction) {
    EXPECT_EQ(account.getHistory().size(), 0);
    account.deposit(100.0);
    EXPECT_EQ(account.getHistory().size(), 1);
}

class AccountWithdrawTests : public ::testing::Test {
protected:
    Account account{"ACC002", 1000.0};
    MockObserver observer;
    
    void SetUp() override {
        account.attach(&observer);
    }
};

TEST_F(AccountWithdrawTests, ValidWithdrawDecreasesBalance) {
    double initialBalance = account.getBalance();
    EXPECT_TRUE(account.withdraw(300.0));
    EXPECT_EQ(account.getBalance(), initialBalance - 300.0);
}

TEST_F(AccountWithdrawTests, WithdrawMoreThanBalanceFails) {
    double initialBalance = account.getBalance();
    EXPECT_FALSE(account.withdraw(1500.0));
    EXPECT_EQ(account.getBalance(), initialBalance);
}

TEST_F(AccountWithdrawTests, WithdrawCreatesTransaction) {
    EXPECT_EQ(account.getHistory().size(), 0);
    account.withdraw(50.0);
    EXPECT_EQ(account.getHistory().size(), 1);
}

class AccountTransferTests : public ::testing::Test {
protected:
    Account sender{"ACC003", 1000.0};
    Account recipient{"ACC004", 500.0};
    MockObserver senderObserver;
    MockObserver recipientObserver;
    
    void SetUp() override {
        sender.attach(&senderObserver);
        recipient.attach(&recipientObserver);
    }
};

TEST_F(AccountTransferTests, ValidTransferReducesSenderBalance) {
    double initialBalance = sender.getBalance();
    sender.transfer(recipient, 200.0);
    EXPECT_EQ(sender.getBalance(), initialBalance - 200.0);
}

TEST_F(AccountTransferTests, ValidTransferIncreasesRecipientBalance) {
    double initialBalance = recipient.getBalance();
    sender.transfer(recipient, 200.0);
    EXPECT_EQ(recipient.getBalance(), initialBalance + 200.0);
}

TEST_F(AccountTransferTests, TransferMoreThanBalanceFails) {
    double senderBalance = sender.getBalance();
    double recipientBalance = recipient.getBalance();
    
    EXPECT_FALSE(sender.transfer(recipient, 1500.0));
    EXPECT_EQ(sender.getBalance(), senderBalance);
    EXPECT_EQ(recipient.getBalance(), recipientBalance);
}

class AccountFeeTests : public ::testing::Test {
protected:
    Account account{"ACC005", 1000.0};
    MockObserver observer;
    
    void SetUp() override {
        account.attach(&observer);
    }
};

TEST_F(AccountFeeTests, ValidFeeDecreasesBalance) {
    double initialBalance = account.getBalance();
    account.deductFee(50.0);
    EXPECT_EQ(account.getBalance(), initialBalance - 50.0);
}

TEST_F(AccountFeeTests, FeeMoreThanBalanceIgnored) {
    double initialBalance = account.getBalance();
    account.deductFee(1500.0);
    EXPECT_EQ(account.getBalance(), initialBalance);
}

TEST_F(AccountFeeTests, FeeCreatesTransaction) {
    EXPECT_EQ(account.getHistory().size(), 0);
    account.deductFee(10.0);
    EXPECT_EQ(account.getHistory().size(), 1);
}

class AccountInterestTests : public ::testing::Test {
protected:
    Account account{"ACC006", 1000.0};
    MockObserver observer;
    MockStrategy strategy{0.05}; 
    
    void SetUp() override {
        account.attach(&observer);
        account.setInterestStrategy(&strategy);
    }
};

TEST_F(AccountInterestTests, InterestWithStrategyIncreasesBalance) {
    double initialBalance = account.getBalance();
    account.applyInterest();
    EXPECT_EQ(account.getBalance(), initialBalance + (initialBalance * 0.05));
}

TEST_F(AccountInterestTests, InterestWithoutStrategyDoesNothing) {
    Account acc2{"ACC007", 1000.0};
    acc2.attach(&observer);
    double initialBalance = acc2.getBalance();
    
    acc2.applyInterest(); 
    EXPECT_EQ(acc2.getBalance(), initialBalance);
}

class AccountObserverTests : public ::testing::Test {
protected:
    Account account{"ACC008", 1000.0};
    MockObserver observer1, observer2;
};

TEST_F(AccountObserverTests, MultipleObserversGetNotified) {
    account.attach(&observer1);
    account.attach(&observer2);
    
    account.deposit(100.0);
    EXPECT_GT(observer1.getMessageCount(), 0);
    EXPECT_GT(observer2.getMessageCount(), 0);
}

class AccountComplexTests : public ::testing::Test {
protected:
    Account account1{"ACC011", 5000.0};
    Account account2{"ACC012", 3000.0};
    
    void SetUp() override {
    }
};

TEST_F(AccountComplexTests, SequenceOfOperations) {

    EXPECT_EQ(account1.getBalance(), 5000.0);

    account1.deposit(1000.0);
    EXPECT_EQ(account1.getBalance(), 6000.0);

    account1.withdraw(500.0);
    EXPECT_EQ(account1.getBalance(), 5500.0);

    account1.deductFee(100.0);
    EXPECT_EQ(account1.getBalance(), 5400.0);

    account1.transfer(account2, 1000.0);
    EXPECT_EQ(account1.getBalance(), 4400.0);
    EXPECT_EQ(account2.getBalance(), 4000.0);
    
    EXPECT_EQ(account1.getHistory().size(), 5);
}

TEST_F(AccountComplexTests, MultipleTransfersWithFees) {
    account1.transfer(account2, 500.0);
    EXPECT_EQ(account1.getBalance(), 4500.0);
    EXPECT_EQ(account2.getBalance(), 3500.0);
    
    account1.deductFee(50.0);
    EXPECT_EQ(account1.getBalance(), 4450.0);
    
    account2.transfer(account1, 200.0);
    EXPECT_EQ(account2.getBalance(), 3300.0);
    EXPECT_EQ(account1.getBalance(), 4650.0);
}
