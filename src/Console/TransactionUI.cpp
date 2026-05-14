#include "TransactionUI.h"
#include "../Aplication/BankService.h"
#include "../Aplication/AccountManager.h"
#include "../core/Account.h"

TransactionUI::TransactionUI(BankService* service) : bankService(service) {}

void TransactionUI::run() {
    bool inMenu = true;

    while (inMenu) {
        std::cout << "\n===== TRANSACTIONS =====" << std::endl;
        std::cout << "1. Deposit Money" << std::endl;
        std::cout << "2. Withdraw Money" << std::endl;
        std::cout << "3. Transfer Money" << std::endl;
        std::cout << "4. View Transaction History" << std::endl;
        std::cout << "0. Back" << std::endl;
        std::cout << "Choose option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::cout << "\n--- Deposit Money ---" << std::endl;
                std::cout << "Enter account number: ";
                std::string accNumber;
                std::getline(std::cin, accNumber);
                
                auto account = bankService->getAccountManager()->getAccount(accNumber);
                if (account) {
                    std::cout << "Enter deposit amount: $";
                    double amount;
                    std::cin >> amount;
                    
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Error: Invalid amount. Please enter a valid number." << std::endl;
                    } else {
                        std::cin.ignore();
                        if (account->deposit(amount)) {
                            std::cout << "Deposit successful! New balance: $" << account->getBalance() << std::endl;
                        } else {
                            std::cout << "Deposit failed! Invalid amount." << std::endl;
                        }
                    }
                } else {
                    std::cout << "Account not found!" << std::endl;
                }
                break;
            }
            case 2: {
                std::cout << "\n--- Withdraw Money ---" << std::endl;
                std::cout << "Enter account number: ";
                std::string accNumber;
                std::getline(std::cin, accNumber);
                
                auto account = bankService->getAccountManager()->getAccount(accNumber);
                if (account) {
                    std::cout << "Enter withdrawal amount: $";
                    double amount;
                    std::cin >> amount;
                    
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Error: Invalid amount. Please enter a valid number." << std::endl;
                    } else {
                        std::cin.ignore();
                        if (account->withdraw(amount)) {
                            std::cout << "Withdrawal successful! New balance: $" << account->getBalance() << std::endl;
                        } else {
                            std::cout << "Withdrawal failed! Insufficient funds or invalid amount." << std::endl;
                        }
                    }
                } else {
                    std::cout << "Account not found!" << std::endl;
                }
                break;
            }
            case 3: {
                std::cout << "\n--- Transfer Money ---" << std::endl;
                std::cout << "Enter source account number: ";
                std::string sourceAccNumber;
                std::getline(std::cin, sourceAccNumber);
                
                std::cout << "Enter destination account number: ";
                std::string destAccNumber;
                std::getline(std::cin, destAccNumber);
                
                auto sourceAccount = bankService->getAccountManager()->getAccount(sourceAccNumber);
                auto destAccount = bankService->getAccountManager()->getAccount(destAccNumber);
                
                if (sourceAccount && destAccount) {
                    std::cout << "Enter transfer amount: $";
                    double amount;
                    std::cin >> amount;
                    
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(10000, '\n');
                        std::cout << "Error: Invalid amount. Please enter a valid number." << std::endl;
                    } else {
                        std::cin.ignore();
                        if (sourceAccount->transfer(*destAccount, amount)) {
                            std::cout << "Transfer successful!" << std::endl;
                            std::cout << "Source account balance: $" << sourceAccount->getBalance() << std::endl;
                            std::cout << "Destination account balance: $" << destAccount->getBalance() << std::endl;
                        } else {
                            std::cout << "Transfer failed! Insufficient funds or invalid amount." << std::endl;
                        }
                    }
                } else {
                    std::cout << "One or both accounts not found!" << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "\n--- View Transaction History ---" << std::endl;
                std::cout << "Enter account number: ";
                std::string accNumber;
                std::getline(std::cin, accNumber);
                
                auto account = bankService->getAccountManager()->getAccount(accNumber);
                if (account) {
                    auto history = account->getHistory();
                    if (history.empty()) {
                        std::cout << "No transactions found." << std::endl;
                    } else {
                        std::cout << "Transaction History for account " << accNumber << ":" << std::endl;
                        std::cout << "  Total transactions: " << history.size() << std::endl;
                    }
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
