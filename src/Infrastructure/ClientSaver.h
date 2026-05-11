#ifndef CLIENTSAVER_H
#define CLIENTSAVER_H

#include "../core/Client.h"
#include <vector>
#include <memory>

class ClientSaver {
private:
    std::string filePath_;
    std::vector<std::shared_ptr<Client>> cache_;

public:
    explicit ClientSaver(const std::string& filePath);
    
    void save(std::shared_ptr<Client> client);
    const std::vector<std::shared_ptr<Client>>& getAll() const;
    
    void saveToFile();
    void loadFromFile();
};

#endif
