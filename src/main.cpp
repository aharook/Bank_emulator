#include <iostream>
#include "Console/MainMenu.h"
#include "Aplication/BankService.h"

int main() {
    try {

        BankService bankService("Saves/accounts.txt", "Saves/clients.txt");
        
        bankService.getClientManager()->loadAll();
        bankService.getAccountManager()->loadAll();
        
        MainMenu mainMenu(&bankService);
        mainMenu.run();
        

        bankService.getClientManager()->saveAll();
        bankService.getAccountManager()->saveAll();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}