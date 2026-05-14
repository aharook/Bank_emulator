#include <gtest/gtest.h>
#include <memory>
#include <cstdio>
#include "../src/core/Account.h"
#include "../src/core/Client.h"
#include "../src/core/Observer.h"
#include "../src/Aplication/AccountManager.h"
#include "../src/Aplication/ClientManager.h"

class TestObserver : public IObserver {
public:
    int updateCount = 0;
    TransactionType lastEventType;
    double lastAmount = 0.0;
    double lastBalance = 0.0;
    
    void update(const TransactionEvent& event) override {
        updateCount++;
        lastEventType = event.type;
        lastAmount = event.amount;
        lastBalance = event.newBalance;
    }
};

class MockTests : public ::testing::Test {
protected:
    void SetUp() override {
        remove("test_mock_clients.txt");
        remove("test_mock_accounts.txt");
        
        clientManager = std::make_unique<ClientManager>("test_mock_clients.txt");
        accountManager = std::make_unique<AccountManager>("test_mock_accounts.txt");
    }

    void TearDown() override {
        clientManager.reset();
        accountManager.reset();
        remove("test_mock_clients.txt");
        remove("test_mock_accounts.txt");
    }

    std::unique_ptr<ClientManager> clientManager;
    std::unique_ptr<AccountManager> accountManager;
};

TEST_F(MockTests, DepositNotifiesObserver) {
    Account acc("ACC001", 100.0);
    TestObserver observer;
    
    acc.attach(&observer);
    acc.deposit(50.0);
    
    EXPECT_EQ(observer.updateCount, 1);
    EXPECT_EQ(observer.lastEventType, TransactionType::DEPOSIT);
    EXPECT_DOUBLE_EQ(observer.lastAmount, 50.0);
}

TEST_F(MockTests, WithdrawalNotifiesObserver) {
    Account acc("ACC002", 100.0);
    TestObserver observer;
    
    acc.attach(&observer);
    acc.withdraw(30.0);
    
    EXPECT_EQ(observer.updateCount, 1);
    EXPECT_EQ(observer.lastEventType, TransactionType::WITHDRAWAL);
    EXPECT_DOUBLE_EQ(observer.lastAmount, 30.0);
}

TEST_F(MockTests, MultipleObserversNotified) {
    Account acc("ACC003", 100.0);
    TestObserver observer1;
    TestObserver observer2;
    
    acc.attach(&observer1);
    acc.attach(&observer2);
    acc.deposit(25.0);
    
    EXPECT_EQ(observer1.updateCount, 1);
    EXPECT_EQ(observer2.updateCount, 1);
}

TEST_F(MockTests, TransferUpdatesBalance) {
    Account acc1("ACC001", 1000.0);
    Account acc2("ACC002", 500.0);
    
    TestObserver observer1;
    TestObserver observer2;
    
    acc1.attach(&observer1);
    acc2.attach(&observer2);
    
    acc1.transfer(acc2, 200.0);
    
    EXPECT_DOUBLE_EQ(acc1.getBalance(), 800.0);
    EXPECT_DOUBLE_EQ(acc2.getBalance(), 700.0);
    EXPECT_GT(observer1.updateCount, 0);
    EXPECT_GT(observer2.updateCount, 0);
}

TEST_F(MockTests, AccountManagerCreatesAndStoresAccount) {
    accountManager->createAccount("MOCK_ACC", 300.0);
    auto account = accountManager->getAccount("MOCK_ACC");
    
    ASSERT_NE(account, nullptr);
    EXPECT_DOUBLE_EQ(account->getBalance(), 300.0);
}

TEST_F(MockTests, ClientManagerCreatesAndStoresClient) {
    clientManager->createClient("Mock Client");
    auto clients = clientManager->getAllClients();
    
    ASSERT_EQ(clients.size(), 1);
    EXPECT_EQ(clients.begin()->second->getName(), "Mock Client");
}

TEST_F(MockTests, AccountHistoryTracksTransactions) {
    Account acc("ACC004", 100.0);
    TestObserver observer;
    
    acc.attach(&observer);
    acc.deposit(50.0);
    acc.withdraw(25.0);
    acc.deposit(75.0);
    
    EXPECT_EQ(observer.updateCount, 3);
    auto history = acc.getHistory();
    EXPECT_EQ(history.size(), 3);
}

TEST_F(MockTests, FeeDeductionNotifiesObserver) {
    Account acc("ACC005", 1000.0);
    TestObserver observer;
    
    acc.attach(&observer);
    acc.deductFee(50.0);
    
    EXPECT_EQ(observer.updateCount, 1);
    EXPECT_EQ(observer.lastEventType, TransactionType::FEE_DEDUCTION);
}
TEST_F(MockTests, ClientNameUpdate) {
    clientManager->createClient("Original");
    auto clients = clientManager->getAllClients();
    auto client = clients.begin()->second;
    
    client->setName("Updated");
    EXPECT_EQ(client->getName(), "Updated");
}

TEST_F(MockTests, AccountExistenceVerification) {
    accountManager->createAccount("EXISTS", 100.0);
    
    EXPECT_TRUE(accountManager->accountExists("EXISTS"));
    EXPECT_FALSE(accountManager->accountExists("DOES_NOT_EXIST"));
}
