#include <gtest/gtest.h>
#include <memory>
#include <cstdio>
#include "../src/Aplication/BankService.h"
#include "../src/Aplication/AccountManager.h"
#include "../src/Aplication/ClientManager.h"

class EndToEndTest : public ::testing::Test {
protected:
    void SetUp() override {
        remove("test_e2e_accounts.txt");
        remove("test_e2e_clients.txt");
        
        bankService = std::make_unique<BankService>("test_e2e_accounts.txt", "test_e2e_clients.txt");
        bankService->getClientManager()->loadAll();
        bankService->getAccountManager()->loadAll();
    }

    void TearDown() override {
        bankService->getClientManager()->saveAll();
        bankService->getAccountManager()->saveAll();
        bankService.reset();
        remove("test_e2e_accounts.txt");
        remove("test_e2e_clients.txt");
    }

    std::unique_ptr<BankService> bankService;
};

TEST_F(EndToEndTest, CompleteClientCreation) {
    bankService->getClientManager()->createClient("Alice Wonder");
    auto clients = bankService->getClientManager()->getAllClients();
    EXPECT_EQ(clients.size(), 1);
    EXPECT_EQ(clients.begin()->second->getName(), "Alice Wonder");
}

TEST_F(EndToEndTest, CompleteAccountCreation) {
    bankService->getAccountManager()->createAccount("ACC001", 500.0);
    auto account = bankService->getAccountManager()->getAccount("ACC001");
    EXPECT_NE(account, nullptr);
    EXPECT_DOUBLE_EQ(account->getBalance(), 500.0);
}

TEST_F(EndToEndTest, MultipleClientsCreation) {
    bankService->getClientManager()->createClient("Client 1");
    bankService->getClientManager()->createClient("Client 2");
    bankService->getClientManager()->createClient("Client 3");
    
    auto clients = bankService->getClientManager()->getAllClients();
    EXPECT_EQ(clients.size(), 3);
}

TEST_F(EndToEndTest, MultipleAccountsWithTransactions) {
    bankService->getAccountManager()->createAccount("ACC001", 1000.0);
    bankService->getAccountManager()->createAccount("ACC002", 500.0);
    
    auto acc1 = bankService->getAccountManager()->getAccount("ACC001");
    auto acc2 = bankService->getAccountManager()->getAccount("ACC002");
    
    acc1->transfer(*acc2, 200.0);
    
    EXPECT_DOUBLE_EQ(acc1->getBalance(), 800.0);
    EXPECT_DOUBLE_EQ(acc2->getBalance(), 700.0);
}

TEST_F(EndToEndTest, ClientEditWorkflow) {
    bankService->getClientManager()->createClient("Original Name");
    auto clients = bankService->getClientManager()->getAllClients();
    auto client = clients.begin()->second;
    
    client->setName("Updated Name");
    EXPECT_EQ(client->getName(), "Updated Name");
}

TEST_F(EndToEndTest, AccountAndClientDeletion) {
    bankService->getClientManager()->createClient("Client to Delete");
    bankService->getAccountManager()->createAccount("ACC_DELETE", 100.0);
    
    auto clients = bankService->getClientManager()->getAllClients();
    std::string taxId = clients.begin()->first;
    
    bankService->getClientManager()->deleteClient(taxId);
    bankService->getAccountManager()->deleteAccount("ACC_DELETE");
    
    EXPECT_EQ(bankService->getClientManager()->getAllClients().size(), 0);
    EXPECT_EQ(bankService->getAccountManager()->getAllAccounts().size(), 0);
}

TEST_F(EndToEndTest, ComplexTransactionSequence) {
    bankService->getAccountManager()->createAccount("ACC1", 1000.0);
    auto acc = bankService->getAccountManager()->getAccount("ACC1");
    
    acc->deposit(500.0);
    acc->withdraw(200.0);
    acc->deposit(100.0);
    
    EXPECT_DOUBLE_EQ(acc->getBalance(), 1400.0);
    EXPECT_EQ(acc->getHistory().size(), 3);
}

TEST_F(EndToEndTest, VerifyAccountExistence) {
    bankService->getAccountManager()->createAccount("VERIFY_ACC", 250.0);
    
    EXPECT_TRUE(bankService->getAccountManager()->accountExists("VERIFY_ACC"));
    EXPECT_FALSE(bankService->getAccountManager()->accountExists("NONEXISTENT"));
}

TEST_F(EndToEndTest, VerifyClientExistence) {
    bankService->getClientManager()->createClient("Test Client");
    auto clients = bankService->getClientManager()->getAllClients();
    std::string taxId = clients.begin()->first;
    
    EXPECT_TRUE(bankService->getClientManager()->clientExists(taxId));
    EXPECT_FALSE(bankService->getClientManager()->clientExists("FAKE_TAX_ID"));
}

TEST_F(EndToEndTest, GetAllAccountsAndClients) {
    bankService->getAccountManager()->createAccount("ACC1", 100.0);
    bankService->getAccountManager()->createAccount("ACC2", 200.0);
    bankService->getClientManager()->createClient("Client 1");
    bankService->getClientManager()->createClient("Client 2");
    
    auto accounts = bankService->getAccountManager()->getAllAccounts();
    auto clients = bankService->getClientManager()->getAllClients();
    
    EXPECT_EQ(accounts.size(), 2);
    EXPECT_EQ(clients.size(), 2);
}
