#include <sstream> // Include the <sstream> header
#include <fstream> // Include the necessary header
#include "../include/account.h"


#include "../include/admin.h" // You'll need to create Admin and Customer classes
#include "../include/member.h" // You'll need to create Admin and Customer classes
#include "../include/hashpassword.h" // You'll need to create Admin and Customer classes

Account::Account(std::string usernameReg, std::string password) {
    this->id = createAutoIncrementedId("./data/member.txt");
    this->username = usernameReg;
    this->salt = HashPassword::generateSalt(); // Implement HashPassword class
    this->password = password;
}

Account::Account(std::string id, std::string usernameReg, std::string password, std::string salt) {
    this->id = id;
    this->username = usernameReg;
    this->salt = salt;
    this->password = password;
}

Account::Account() {};



std::string Account::getId() const {
    return id;
}

std::string Account::getUsername() const {
    return username;
}

std::string Account::getSalt() const {
    return salt;
}

void Account::setSalt(std::string salt) {
    this->salt = salt;
}

bool Account::checkPassword(std::string password) const {
    std::string hashedPassword = HashPassword::get_SHA_256_SecurePassword(password, this->salt);
    return this->password == hashedPassword;
}

std::string Account::getPassword() const {
    return password;
}

std::string Account::createAutoIncrementedId(std::string filename) {
    int maxId = 0;
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string id;
                if (std::getline(iss, id, '|')) {
                    int accountId = std::stoi(id);
                    maxId = std::max(maxId, accountId);
                }
            }
            file.close();
        } else {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return 0;
        }

        // Generate the new account's ID
        int newId = maxId + 1;
        return std::to_string(newId);
}
