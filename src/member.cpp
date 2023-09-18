#include "Member.h"
#include "Motorbike.h"
#include "RentalRequest.h"
#include "Review.h"
#include <iostream>

// Constructor to initialize member attributes


Member::Member(std::string id, std::string username, std::string fullName, std::string phoneNumber, std::string idType,
       std::string idNumber, std::string driverLicenseNumber, std::string expiryDate)
    : Account(id, username), fullName(fullName), phoneNumber(phoneNumber), idType(idType),
      idNumber(idNumber), driverLicenseNumber(driverLicenseNumber), expiryDate(expiryDate), creditPoints(0) {
    // Initialize member-specific data members if needed
}

Member::Member(std::string id, std::string usernameReg, std::string password, std::string salt, std::string fullName, std::string phoneNumber, std::string idType,
       std::string idNumber, std::string driverLicenseNumber, std::string expiryDate)
    : Account(id, usernameReg, password, salt), fullName(fullName), phoneNumber(phoneNumber), idType(idType),
      idNumber(idNumber), driverLicenseNumber(driverLicenseNumber), expiryDate(expiryDate), creditPoints(0) {
    // Initialize member-specific data members if needed
}

// Member registration
void Member::registerMember() {
    // Implement member registration logic
    // You should prompt the user to enter necessary information and store it.
    std::cout << "Member registration completed." << std::endl;
}



// List a motorbike for rent
void Member::listMotorbike(Motorbike motorbike) {
    // Implement listing a motorbike for rent
    // Add the specified motorbike to the member's list of listed motorbikes.
}

// Unlist a motorbike
void Member::unlistMotorbike(Motorbike motorbike) {
    // Implement unlisting a motorbike
    // Remove the specified motorbike from the member's list of listed motorbikes.
}

// Request to rent a motorbike
void Member::requestToRentMotorbike(Motorbike motorbike, TimePeriod period) {
    // Implement requesting to rent a motorbike
    // Create a rental request and send it to the motorbike owner.
}

// View rental requests
void Member::viewRequests() {
    // Implement viewing rental requests
    // Display the list of rental requests for the member's listed motorbikes.
}

// Rate a rented motorbike
void Member::rateMotorbike(Motorbike motorbike, Review review) {
    // Implement rating a rented motorbike
    // Add the review to the motorbike's reviews.
}

// Rate a renter (another member)
void Member::rateRenter(Member renter, Review review) {
    // Implement rating a renter
    // Add the review to the renter's reviews.
}

// Top up credit points
void Member::topUpCreditPoints(int amount) {
    // Implement topping up credit points
    // Add the specified amount to the member's credit points balance.
    creditPoints += amount;
}

// View member information
void Member::viewMemberInfo() {
    // Implement viewing member information
    // Display the member's details, including username, full name, and credit points.
}

std::string Member::getRole() {
    return "Member";
}
