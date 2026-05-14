#include "ClientUI.h"
#include "../Aplication/BankService.h"
#include "../Aplication/ClientManager.h"
#include "../core/Client.h"

ClientUI::ClientUI(BankService* service) : bankService(service) {}

void ClientUI::run() {
    bool inMenu = true;

    while (inMenu) {
        std::cout << "\n===== CLIENT MANAGEMENT =====" << std::endl;
        std::cout << "1. Add New Client" << std::endl;
        std::cout << "2. View All Clients" << std::endl;
        std::cout << "3. Edit Client" << std::endl;
        std::cout << "4. Delete Client" << std::endl;
        std::cout << "0. Back" << std::endl;
        std::cout << "Choose option: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::cout << "\n--- Add New Client ---" << std::endl;
                std::cout << "Enter client name: ";
                std::string name;
                std::getline(std::cin, name);
                
                try {
                    bankService->getClientManager()->createClient(name);
                    std::cout << "Client created successfully!" << std::endl;
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
                break;
            }
            case 2: {
                std::cout << "\n--- View All Clients ---" << std::endl;
                auto allClients = bankService->getClientManager()->getAllClients();
                
                if (allClients.empty()) {
                    std::cout << "No clients found." << std::endl;
                } else {
                    std::cout << "\nTotal Clients: " << allClients.size() << std::endl;
                    std::cout << std::string(60, '-') << std::endl;
                    
                    for (const auto& pair : allClients) {
                        auto client = pair.second;
                        std::cout << "Name: " << client->getName() << std::endl;
                        std::cout << "Tax ID: " << client->getTaxId() << std::endl;
                        std::cout << "Accounts: " << client->getAccount().size() << std::endl;
                        std::cout << std::string(60, '-') << std::endl;
                    }
                }
                break;
            }
            case 3: {
                std::cout << "\n--- Edit Client ---" << std::endl;
                std::cout << "Enter client Tax ID: ";
                std::string taxId;
                std::getline(std::cin, taxId);
                
                auto client = bankService->getClientManager()->getClient(taxId);
                if (client) {
                    std::cout << "\nCurrent Name: " << client->getName() << std::endl;
                    std::cout << "Enter new name: ";
                    std::string newName;
                    std::getline(std::cin, newName);
                    
                    client->setName(newName);
                    std::cout << "Client updated successfully!" << std::endl;
                } else {
                    std::cout << "Client not found!" << std::endl;
                }
                break;
            }
            case 4: {
                std::cout << "\n--- Delete Client ---" << std::endl;
                std::cout << "Enter client Tax ID: ";
                std::string taxId;
                std::getline(std::cin, taxId);
                
                if (bankService->getClientManager()->clientExists(taxId)) {
                    bankService->getClientManager()->deleteClient(taxId);
                    std::cout << "Client deleted successfully!" << std::endl;
                } else {
                    std::cout << "Client not found!" << std::endl;
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
