#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include "../include/hashpassword.h" // HashPassword class

class Account {
private:
    std::string id;
    std::string username;
    std::string password;
    std::string salt;

public:
    Account(std::string id, std::string usernameReg, std::string password);
    Account(std::string id, std::string usernameReg, std::string password, std::string salt);
    Account(std::string id, std::string usernameReg);
    Account();
    std::string getId() const;
    std::string getUsername() const;
    std::string getSalt() const;
    void setSalt(std::string salt);
    bool checkPassword(std::string password) const;
    std::string getPassword() const;
    Account* login(const std::string& fileName, const std::string& username, const std::string& password);
    // The 'virtual' keyword makes this function abstract, and it must be overridden in derived classes.
    
    virtual std::string getRole();
    virtual ~Account(); // Virtual destructor for polymorphism.
};

#endif
