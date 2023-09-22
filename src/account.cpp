#include "../include/account.h"

#include "../include/admin.h" // You'll need to create Admin and Customer classes
#include "../include/member.h" // You'll need to create Admin and Customer classes
#include "../include/hashpassword.h" // You'll need to create Admin and Customer classes

Account::Account(std::string id, std::string usernameReg, std::string password) {
    this->id = id;
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


