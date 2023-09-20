#include "Member.h"
#include "Motorbike.h"
#include "RentalRequest.h"
#include "Review.h"
#include "hashPassword.h"
#include "method.h"
#include <fstream>
#include <iostream>



// Constructor to initialize member attributes
Member::Member(std::string id, std::string username, std::string password, std::string fullName, std::string phoneNumber, std::string idType,
   std::string idNumber, std::string driverLicenseNumber, std::string expiryDate)
    : Account(id, username, password), fullName(fullName), phoneNumber(phoneNumber), idType(idType),
      idNumber(idNumber), driverLicenseNumber(driverLicenseNumber), expiryDate(expiryDate), creditPoints(20), 
      ratingScores(0), motorbikes() {
    // Initialize member-specific data members if needed
    // rentalRequests vector is already defined as a member variable, no need to define it again here.
}



// for existed member
Member::Member(std::string id, std::string usernameReg, std::string password, std::string salt, std::string fullName, std::string phoneNumber, std::string idType,
       std::string idNumber, std::string driverLicenseNumber, std::string expiryDate, int creditPoints)
    : Account(id, usernameReg, password, salt), fullName(fullName), phoneNumber(phoneNumber), idType(idType),
      idNumber(idNumber), driverLicenseNumber(driverLicenseNumber), expiryDate(expiryDate), creditPoints(creditPoints) {
    // Initialize member-specific data members if needed
}

// Member registration
void Member::registerMember() {
    // Implement member registration logic
    // You should prompt the user to enter necessary informastion and store it securely.
    std::string id, username, password, salt, fullName, phoneNumber, idType, idNumber, driverLicenseNumber, expiryDate;

    // Prompt the user to enter registration details
    std::cout << "Enter Member ID: ";
    std::cin >> id;
    std::cout << "Enter Username: ";
    std::cin >> username;
    std::cout << "Enter Password: ";
    std::cin >> password; // You can use a password validation function here.
    
    std::cout << "Enter Full Name: ";
    std::cin.ignore(); 
    std::getline(std::cin, fullName);
    std::cout << "Enter Phone Number: ";
    std::cin >> phoneNumber;
    std::cout << "Enter ID Type: ";
    std::cin >> idType;
    std::cout << "Enter ID Number: ";
    std::cin >> idNumber;
    std::cout << "Enter Driver License Number: ";
    std::cin >> driverLicenseNumber;
    std::cout << "Enter Expiry Date: ";
    std::cin >> expiryDate;

    // Create a Member object with the provided information
    Member newMember(id, username, password, fullName, phoneNumber, idType, idNumber, driverLicenseNumber, expiryDate);

    // Store the member data or perform any necessary operations

    std::cout << "Member registration completed." << std::endl;
}


// List a motorbike for rent
void Member::listMotorbike() {
    std::string model, color, engineSizeVal, transmissionMode, description, yearMadeVal, minimumRenterRatingVal, consumingPointVal;
    std::string startDate, endDate;
    std::cout << "Enter Model Name: ";
    std::cin.ignore(); // Consume newline character
    std::getline(std::cin, model);
    std::cout << "Enter color: ";
    std::cin >> color;
    std::cout << "Enter Transmission Mode: ";
    std::cin >> transmissionMode;
    std::cout << "Enter Description:: ";
    std::cin.ignore(); 
    std::getline(std::cin, description);
    std::cout << "Enter engine size: ";
    std::cin >> engineSizeVal;
    std::cout << "Enter year made: ";
    std::cin >> yearMadeVal;
    std::cout << "Enter minimum renter rating: ";
    std::cin >> minimumRenterRatingVal;
    std::cout << "Enter consuming point: ";
    std::cin >> consumingPointVal;
    std::cout << "Enter start date: ";
    std::cin >> startDate;

    std::cout << "Enter end date: ";
    std::cin >> endDate;
    double engineSize = Method::validateDouble(engineSizeVal);
    int yearMade = Method::validateNumber(yearMadeVal);
    int minimumRenterRating = Method::validateNumber(minimumRenterRatingVal);
    int consumingPoint = Method::validateNumber(consumingPointVal);

    Motorbike motorbike(model, color, engineSize, transmissionMode, yearMade,
                            description, minimumRenterRating, consumingPoint);
    


}

// Unlist a motorbike
void Member::unlistMotorbike() {
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


void Member::writeToDatabase(const Member& account, const std::string& filename) {
    std::ofstream outputFile(filename, std::ios::app); // Open the file in append mode

    if (outputFile.is_open()) {
        outputFile << account.getId() << "|" << account.getUsername() << "|" << account.getPassword() << "|" << account.getFullName() << "|" << account.getPhoneNumber() << "|" << account.getIdType() << "|" << account.getIdNumber() << "|" << account.getDriverLicenseNumber() << "|" << account.getExpiryDate() << "|" << account.getSalt() << "\n";
        outputFile.close(); // Close the file
    } else {
        std::cerr << "Error writing to database file." << std::endl;
    }
}

std::string Member::getRole() {
    return "Member";
}

std::string Member::getId() const {
    return id;
}


std::string Member::getFullName() const {
    return fullName;
}

std::string Member::getPhoneNumber() const {
    return phoneNumber;
}

std::string Member::getIdType() const {
    return idType;
}

std::string Member::getIdNumber() const {
    return idNumber;
}

std::string Member::getDriverLicenseNumber() const {
    return driverLicenseNumber;
}

std::string Member::getExpiryDate() const {
    return expiryDate;
}

int Member::getCreditPoints() const {
    return creditPoints;
}

Motorbike Member::getMotorbikes() const {
        return motorbikes;
    }

double Member::getRatingScores() const {
    return ratingScores;
}

std::vector<RentalRequest> Member::getRentalRequests() const {
        return rentalRequests;
    }

// Setter functions
void Member::setId(const std::string& newId) {
    id = newId;
}

void Member::setFullName(const std::string& newFullName) {
    fullName = newFullName;
}

void Member::setPhoneNumber(const std::string& newPhoneNumber) {
    phoneNumber = newPhoneNumber;
}

void Member::setIdType(const std::string& newIdType) {
    idType = newIdType;
}

void Member::setIdNumber(const std::string& newIdNumber) {
    idNumber = newIdNumber;
}

void Member::setDriverLicenseNumber(const std::string& newDriverLicenseNumber) {
    driverLicenseNumber = newDriverLicenseNumber;
}

void Member::setExpiryDate(const std::string& newExpiryDate) {
    expiryDate = newExpiryDate;
}

void Member::setCreditPoints(int newCreditPoints) {
    creditPoints = newCreditPoints;
}

void Member::setCreditPoints(int newCreditPoints) {
        creditPoints = newCreditPoints;
    }

void Member::setMotorbikes(Motorbike newMotorbike) {
    motorbikes = newMotorbike;
}

void Member::setRatingScores(double newRatingScores) {
    ratingScores = newRatingScores;
}

void Member::setRentalRequests(const std::vector<RentalRequest>& newRentalRequests) {
    rentalRequests = newRentalRequests;
}

void addRentalRequest(const RentalRequest& request) {
    rentalRequests.push_back(request);
}