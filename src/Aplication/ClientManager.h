#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include "../core/Client.h"
#include "../Infrastructure/ClientSaver.h"
#include <map>
#include <memory>

class ClientManager {
private:
    std::map<std::string, std::shared_ptr<Client>> clients;
    ClientSaver saver;

public:
    ClientManager(const std::string& filePath);
    ~ClientManager();

    void createClient(const std::string& name);
    void deleteClient(const std::string& taxId);
    std::shared_ptr<Client> getClient(const std::string& taxId);
    bool clientExists(const std::string& taxId) const;
    std::map<std::string, std::shared_ptr<Client>> getAllClients() const;
    
    void loadAll();
    void saveAll();
};

#endif
