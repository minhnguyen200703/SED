#include "../include/admin.h"
#include "../include/member.h"
#include "../include/motorbike.h"

Admin::Admin(std::string id, std::string username, std::string password)
    : Account(id, username, password) {
    // Initialize other admin attributes or perform necessary setup
}

 Admin::Admin() {
        // Initialization code if needed
    }



void Admin::viewMemberInfo() {
    // Implement viewing member information
    // Display details of all members, possibly by iterating through the member list.
}

void Admin::viewMotorbikeInfo() {
    // Implement viewing motorbike information
    // Display details of all motorbikes, possibly by iterating through the motorbike list.
}

std::string getRole() {
    return "admin";
};


Admin::~Admin() {
    // Any necessary cleanup specific to Admin objects can be performed here
}
