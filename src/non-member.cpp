// NonMember.cpp
#include "non-member.h"
#include "Member.h" // Include the Member header to access member registration functionality

NonMember::NonMember(std::string username) : username(username) {
    // Initialize other NonMember attributes or perform necessary setup
}

void NonMember::registerAsMember() {
    // Implement registration as a member
    // You may need to create a Member object with the provided username and perform registration steps.
}

void NonMember::viewMotorbikeDetails() {
    // Implement viewing motorbike details
    // Display motorbike information to non-members.
}

// You can add more methods or functionality to the NonMember class as needed.
