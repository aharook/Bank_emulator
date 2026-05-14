#include "ClientManager.h"

ClientManager::ClientManager(const std::string& filePath) : saver(filePath) {
    loadAll();
}

ClientManager::~ClientManager() {
    saveAll();
}

void ClientManager::createClient(const std::string& name) {

        if(name.empty() ) { 
        throw std::invalid_argument("Name cannot be empty!");
    }
    auto newClient = std::make_shared<Client>(name);
    clients[newClient->getTaxId()] = newClient;
}

void ClientManager::deleteClient(const std::string& taxId) {
    if (taxId.empty()) {
        throw std::invalid_argument("Tax ID cannot be empty!");
    }
    clients.erase(taxId);
}

std::shared_ptr<Client> ClientManager::getClient(const std::string& taxId) {
    if (taxId.empty()) {
        throw std::invalid_argument("Tax ID cannot be empty!");
    }
    auto it = clients.find(taxId);
    if (it != clients.end()) {
        return it->second;
    }
    return nullptr;
}

bool ClientManager::clientExists(const std::string& taxId) const {
    return clients.find(taxId) != clients.end();
}

std::map<std::string, std::shared_ptr<Client>> ClientManager::getAllClients() const {
    return clients;
}

void ClientManager::loadAll() {
    const auto& allClients = saver.getAll();
    for (const auto& client : allClients) {
        clients[client->getTaxId()] = client;
    }
}

void ClientManager::saveAll() {
    for (const auto& pair : clients) {
        saver.save(pair.second);
    }
    saver.saveToFile();
}
