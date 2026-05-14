#include <gtest/gtest.h>
#include <memory>
#include <cstdio>
#include "../src/core/Account.h"
#include "../src/core/Client.h"
#include "../src/Aplication/AccountManager.h"
#include "../src/Aplication/ClientManager.h"

class ErrorHandlingTest : public ::testing::Test {
protected:
    void SetUp() override {
        remove("test_error_clients.txt");
        remove("test_error_accounts.txt");
        
        clientManager = std::make_unique<ClientManager>("test_error_clients.txt");
        accountManager = std::make_unique<AccountManager>("test_error_accounts.txt");
    }

    void TearDown() override {
        clientManager.reset();
        accountManager.reset();
        remove("test_error_clients.txt");
        remove("test_error_accounts.txt");
    }

    std::unique_ptr<ClientManager> clientManager;
    std::unique_ptr<AccountManager> accountManager;
};

TEST_F(ErrorHandlingTest, EmptyAccountNumberThrows) {
    EXPECT_THROW(accountManager->createAccount("", 100.0), std::invalid_argument);
}

TEST_F(ErrorHandlingTest, NegativeBalanceThrows) {
    EXPECT_THROW(accountManager->createAccount("ACC001", -100.0), std::invalid_argument);
}

TEST_F(ErrorHandlingTest, EmptyClientNameThrows) {
    EXPECT_THROW(clientManager->createClient(""), std::invalid_argument);
}

TEST_F(ErrorHandlingTest, DeleteNonExistentAccount) {
    EXPECT_NO_THROW(accountManager->deleteAccount("NONEXISTENT"));
}

TEST_F(ErrorHandlingTest, DeleteNonExistentClient) {
    EXPECT_NO_THROW(clientManager->deleteClient("NONEXISTENT_TAX_ID"));
}

TEST_F(ErrorHandlingTest, GetNonExistentAccount) {
    auto account = accountManager->getAccount("NONEXISTENT");
    EXPECT_EQ(account, nullptr);
}

TEST_F(ErrorHandlingTest, GetNonExistentClient) {
    auto client = clientManager->getClient("NONEXISTENT_TAX_ID");
    EXPECT_EQ(client, nullptr);
}

TEST_F(ErrorHandlingTest, WithdrawMoreThanBalance) {
    Account acc("ACC001", 100.0);
    bool result = acc.withdraw(200.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}

TEST_F(ErrorHandlingTest, TransferInsufficientFunds) {
    Account acc1("ACC001", 50.0);
    Account acc2("ACC002", 100.0);
    bool result = acc1.transfer(acc2, 100.0);
    EXPECT_FALSE(result);
    EXPECT_DOUBLE_EQ(acc1.getBalance(), 50.0);
    EXPECT_DOUBLE_EQ(acc2.getBalance(), 100.0);
}

TEST_F(ErrorHandlingTest, ZeroAmountOperations) {
    Account acc("ACC001", 100.0);
    EXPECT_FALSE(acc.deposit(0.0));
    EXPECT_FALSE(acc.withdraw(0.0));
    EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}
