#include "MainMenu.h"
#include "ClientUI.h"
#include "AccountUI.h"
#include "TransactionUI.h"
#include "../Aplication/BankService.h"

MainMenu::MainMenu(BankService* service) : bankService(service) {}

void MainMenu::run() {
    bool inMenu = true;

    while (inMenu) {
        std::cout << "\n===== BANK EMULATOR - MAIN MENU =====" << std::endl;
        std::cout << "1. Client Management" << std::endl;
        std::cout << "2. Account Management" << std::endl;
        std::cout << "3. Transactions" << std::endl;
        std::cout << "4. About" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Choose option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                ClientUI clientUI(bankService);
                clientUI.run();
                break;
            }
            case 2: {
                AccountUI accountUI(bankService);
                accountUI.run();
                break;
            }
            case 3: {
                TransactionUI transactionUI(bankService);
                transactionUI.run();
                break;
            }
            case 4:
                std::cout << "\n===== ABOUT =====" << std::endl;
                std::cout << "Bank Emulator v1.0" << std::endl;
                std::cout << "A simple console-based banking system." << std::endl;
                std::cout << "\nFeatures:" << std::endl;
                std::cout << "  - Client Management" << std::endl;
                std::cout << "  - Account Management" << std::endl;
                std::cout << "  - Transaction Processing" << std::endl;
                break;
            case 0:
                std::cout << "\nThank you for using Bank Emulator. Goodbye!" << std::endl;
                inMenu = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}
