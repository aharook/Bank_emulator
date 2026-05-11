#include "ClientSaver.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

ClientSaver::ClientSaver(const std::string& filePath) : filePath_(filePath) {
    if (filePath.empty()) {
        throw std::invalid_argument("File path cannot be empty!");
    }
    loadFromFile();
}

void ClientSaver::save(std::shared_ptr<Client> client) {
    if (client == nullptr) {
        throw std::invalid_argument("Client cannot be null!");
    }
    
    auto it = std::find_if(cache_.begin(), cache_.end(),
        [&client](const std::shared_ptr<Client>& c) {
            return c->getTaxId() == client->getTaxId();
        });
    
    if (it != cache_.end()) {
        cache_.erase(it);
    }
    
    cache_.push_back(client);
}

const std::vector<std::shared_ptr<Client>>& ClientSaver::getAll() const {
    return cache_;
}

void ClientSaver::loadFromFile() {
    std::ifstream file(filePath_);
    
    if (!file.is_open()) {
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
    }
    
    file.close();
}

void ClientSaver::saveToFile() {
    std::ofstream file(filePath_);
    
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath_ << std::endl;
        return;
    }
    
    for (const auto& client : cache_) {
        file << client->getName() << "," << client->getTaxId() << std::endl;
    }
    
    file.close();
}
