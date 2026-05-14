#include "AccountUI.h"
#include "../Aplication/BankService.h"
#include "../Aplication/AccountManager.h"
#include "../core/Account.h"

AccountUI::AccountUI(BankService* service) : bankService(service) {}

void AccountUI::run() {
    bool inMenu = true;

    while (inMenu) {
        std::cout << "\n===== ACCOUNT MANAGEMENT =====" << std::endl;
        std::cout << "1. Create New Account" << std::endl;
        std::cout << "2. View All Accounts" << std::endl;
        std::cout << "3. View Account Details" << std::endl;
        std::cout << "4. Close Account" << std::endl;
        std::cout << "0. Back" << std::endl;
        std::cout << "Choose option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::cout << "\n--- Create New Account ---" << std::endl;
                std::cout << "Enter account number: ";
                std::string accNumber;
                std::getline(std::cin, accNumber);
                
                std::cout << "Enter initial balance: ";
                double balance;
                std::cin >> balance;
                
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Error: Invalid balance amount. Please enter a valid number." << std::endl;
                } else {
                    std::cin.ignore();
                    try {
                        bankService->getAccountManager()->createAccount(accNumber, balance);
                        std::cout << "Account created successfully!" << std::endl;
                    }
                    catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                    }
                }
                break;
            }
            case 2: {
                std::cout << "\n--- View All Accounts ---" << std::endl;
                auto allAccounts = bankService->getAccountManager()->getAllAccounts();
                
                if (allAccounts.empty()) {
                    std::cout << "No accounts found." << std::endl;
                } else {
                    std::cout << "\nTotal Accounts: " << allAccounts.size() << std::endl;
                    std::cout << std::string(60, '-') << std::endl;
                    
                    for (const auto& pair : allAccounts) {
                        auto account = pair.second;
                        std::cout << "Account Number: " << account->getAccountNumber() << std::endl;
                        std::cout << "Balance: $" << account->getBalance() << std::endl;
                        std::cout << "Transactions: " << account->getHistory().size() << std::endl;
                        std::cout << std::string(60, '-') << std::endl;
                    }
                }
                break;
            }
            case 3: {
                std::cout << "\n--- View Account Details ---" << std::endl;
                std::cout << "Enter account number: ";
                std::string accNumber;
                std::getline(std::cin, accNumber);
                
                auto account = bankService->getAccountManager()->getAccount(accNumber);
                if (account) {
                    std::cout << "\nAccount Number: " << account->getAccountNumber() << std::endl;
                    std::cout << "Balance: $" << account->getBalance() << std::endl;
                    
                    auto history = account->getHistory();
                    if (!history.empty()) {
                        std::cout << "\nTransaction History:" << std::endl;
                        std::cout << "  (See transaction details in Transactions menu)" << std::endl;
                    }
                } else {
                    std::cout << "Account not found!" << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "\n--- Close Account ---" << std::endl;
                std::cout << "Enter account number: ";
                std::string accNumber;
                std::getline(std::cin, accNumber);
                
                if (bankService->getAccountManager()->accountExists(accNumber)) {
                    bankService->getAccountManager()->deleteAccount(accNumber);
                    std::cout << "Account closed successfully!" << std::endl;
                } else {
                    std::cout << "Account not found!" << std::endl;
                }
                break;
            }
            case 0:
                std::cout << "Returning to main menu..." << std::endl;
                inMenu = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}
