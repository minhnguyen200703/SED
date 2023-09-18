#include "Account.h"
#include "Admin.h" // You'll need to create Admin and Customer classes
#include "member.h" // You'll need to create Admin and Customer classes

Account::Account(std::string id, std::string usernameReg, std::string password) {
    this->id = id;
    this->username = usernameReg;
    this->salt = HashPassword::getSalt(); // Implement HashPassword class
    this->password = HashPassword::get_SHA_256_SecurePassword(password, this->salt);
}

Account::Account(std::string id, std::string usernameReg, std::string password, std::string salt) {
    this->id = id;
    this->username = usernameReg;
    this->salt = salt;
    this->password = HashPassword::get_SHA_256_SecurePassword(password, this->salt);
}

Account::Account(std::string id, std::string usernameReg) {
    this->id = id;
    this->username = usernameReg;
}

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

bool Account::login(const std::string& fileName, const std::string& username, const std::string& password) {
    Account* account = nullptr;

    // Check if admin
    // Implement this part to read and compare admin credentials

    // Check if user
    // Implement this part to read and compare user credentials

    return account;
}
