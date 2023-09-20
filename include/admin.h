#ifndef ADMIN_H
#define ADMIN_H

#include "Account.h"

class Admin : public Account {
public:
    Admin(std::string id, std::string username, std::string password);

    void viewMemberInfo();
    void viewMotorbikeInfo();

    ~Admin() override; // Override the virtual destructor in the derived class.
    std::string getRole() override;
};

#endif
