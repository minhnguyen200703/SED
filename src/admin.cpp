#include "Admin.h"
#include "Member.h"
#include "Motorbike.h"

Admin::Admin(std::string username, std::string password)
    : Account("", username, password) {
    // Initialize other admin attributes or perform necessary setup
}

// bool Admin::login(const std::string& fileName, const std::string& username, const std::string& password) {
//     // Implement admin login logic
//     // Check if the provided username and password match the admin's credentials.
//     // Return true if login is successful, otherwise return false.
//     return (username == getUsername() && checkPassword(password));
// }

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
