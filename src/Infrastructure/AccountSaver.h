#include "../core/Account.h"
#include <stdexcept>

class AccountSaver {
    std::string filePath_;
    std::vector<Account> cache;
public:
    explicit AccountSaver(const std::string& filePath) : filePath_(filePath) {
        if (filePath.empty()) {
            throw std::invalid_argument("File path cannot be empty!");
        }
        loadFromFile();
    }

    ~AccountSaver() {
        saveToFile();
    }

    void save(const Account Account);
    const std::vector<Account>& getAll() const;
    Account findByNumber(const std::string& accountNumber);
    const Account findByNumber(const std::string& accountNumber) const;

    void saveToFile();
    void loadFromFile();
};