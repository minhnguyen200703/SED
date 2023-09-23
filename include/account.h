#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "../include/hashpassword.h" // HashPassword class

class HashPassword;

class Account {
private:
    std::string id;
    std::string username;
    std::string password;
    std::string salt;

public:
    Account(std::string usernameReg, std::string password);
    Account(std::string id, std::string usernameReg, std::string password, std::string salt);
    Account();
    std::string getId() const;
    std::string getUsername() const;
    std::string getSalt() const;
    void setSalt(std::string salt);
    bool checkPassword(std::string password) const;
    std::string getPassword() const;
    std::string createAutoIncrementedId(std::string filename);
    
};

#endif
