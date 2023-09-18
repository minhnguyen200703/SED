#ifndef NONMEMBER_H
#define NONMEMBER_H

#include <string>

class NonMember {
private:
    std::string username; // Non-members can choose a username for registration

public:
    NonMember(std::string username);

    void registerAsMember();
    void viewMotorbikeDetails();
};

#endif
