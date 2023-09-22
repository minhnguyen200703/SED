#ifndef ADMIN_H
#define ADMIN_H

#include "../include/account.h"

class Admin : public Account {
public:
    Admin(std::string id, std::string username, std::string password);
    Admin();

 
};

#endif
