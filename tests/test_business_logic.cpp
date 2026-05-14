#include <gtest/gtest.h>
#include <memory>
#include <cstdio>
#include "../src/core/Account.h"
#include "../src/core/Client.h"
#include "../src/Aplication/AccountManager.h"
#include "../src/Aplication/ClientManager.h"

class BusinessLogicTest : public ::testing::Test {
protected:
    void SetUp() override {
        remove("test_clients.txt");
        remove("test_accounts.txt");
        
        {clientManager = std::make_unique<ClientManager>("test_clients.txt");
        accountManager = std::make_unique<AccountManager>("test_accounts.txt");}

    }

    void TearDown() override {
        clientManager.reset();
        accountManager.reset();
        remove("test_clients.txt");
        remove("test_accounts.txt");
    }

    std::unique_ptr<ClientManager> clientManager;
    std::unique_ptr<AccountManager> accountManager;
};

TEST_F(BusinessLogicTest, AccountDeposit) {
    Account acc("ACC001", 100.0);
    bool result = acc.deposit(50.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 150.0);
}

TEST_F(BusinessLogicTest, AccountWithdrawal) {
    Account acc("ACC002", 100.0);
    bool result = acc.withdraw(30.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 70.0);
}

TEST_F(BusinessLogicTest, AccountTransfer) {
    Account acc1("ACC001", 100.0);
    Account acc2("ACC002", 50.0);
    bool result = acc1.transfer(acc2, 40.0);
    EXPECT_TRUE(result);
    EXPECT_DOUBLE_EQ(acc1.getBalance(), 60.0);
    EXPECT_DOUBLE_EQ(acc2.getBalance(), 90.0);
}

TEST_F(BusinessLogicTest, InsufficientFundsWithdrawal) {
    Account acc("ACC003", 50.0);
    bool result = acc.withdraw(100.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 50.0);
}

TEST_F(BusinessLogicTest, CreateClient) {
    EXPECT_NO_THROW(clientManager->createClient("John Doe"));
    EXPECT_EQ(clientManager->getAllClients().size(), 1);
}

TEST_F(BusinessLogicTest, CreateAccount) {
    EXPECT_NO_THROW(accountManager->createAccount("ACC001", 100.0));
    EXPECT_TRUE(accountManager->accountExists("ACC001"));
    auto acc = accountManager->getAccount("ACC001");
    EXPECT_NE(acc, nullptr);
    EXPECT_DOUBLE_EQ(acc->getBalance(), 100.0);
}

TEST_F(BusinessLogicTest, GetClient) {
    clientManager->createClient("Jane Smith");
    auto clients = clientManager->getAllClients();
    EXPECT_EQ(clients.size(), 1);
    auto client = clients.begin()->second;
    EXPECT_EQ(client->getName(), "Jane Smith");
}

TEST_F(BusinessLogicTest, DeleteClient) {
    clientManager->createClient("Bob Johnson");
    auto clients = clientManager->getAllClients();
    std::string taxId = clients.begin()->first;
    
    clientManager->deleteClient(taxId);
    EXPECT_FALSE(clientManager->clientExists(taxId));
}

TEST_F(BusinessLogicTest, TransactionHistory) {
    Account acc("ACC004", 100.0);
    acc.deposit(50.0);
    acc.withdraw(25.0);
    
    auto history = acc.getHistory();
    EXPECT_EQ(history.size(), 2);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 125.0);
}

TEST_F(BusinessLogicTest, NegativeDeposit) {
    Account acc("ACC005", 100.0);
    bool result = acc.deposit(-50.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}
