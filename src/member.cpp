#include "Member.h"
#include "Motorbike.h"
#include "RentalRequest.h"
#include "Review.h"
#include "hashPassword.h"
#include "method.h"
#include "datetime.h"
#include "timeperiod.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <limits> // Include the <limits> header



// Constructor to initialize member attributes
Member::Member(std::string id, std::string username, std::string password, std::string fullName, std::string phoneNumber, std::string idType,
               std::string idNumber, std::string driverLicenseNumber, std::string expiryDate)
    : Account(id, username, password), fullName(fullName), phoneNumber(phoneNumber), idType(idType),
      idNumber(idNumber), driverLicenseNumber(driverLicenseNumber), expiryDate(expiryDate), creditPoints(20),
      ratingScores(0), motorbikes()
{
    // Initialize member-specific data members if needed
    // rentalRequests vector is already defined as a member variable, no need to define it again here.
}

// for existed member
Member::Member(std::string id, std::string usernameReg, std::string password, std::string salt, std::string fullName, std::string phoneNumber, std::string idType,
               std::string idNumber, std::string driverLicenseNumber, std::string expiryDate, int creditPoints)
    : Account(id, usernameReg, password, salt), fullName(fullName), phoneNumber(phoneNumber), idType(idType),
      idNumber(idNumber), driverLicenseNumber(driverLicenseNumber), expiryDate(expiryDate), creditPoints(creditPoints)
{
    // Initialize member-specific data members if needed
}

Member::Member () {};

// Member registration
static void registerMember(std::vector<Member>& members) {
    // Implement member registration logic
    // You should prompt the user to enter necessary information and store it securely.
    std::string id, username, password, fullName, phoneNumber, idType, idNumber, driverLicenseNumber, expiryDate;

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
    members.push_back(newMember);

    std::cout << "Member registration completed." << std::endl;
}

// List a motorbike for rent
void Member::addMotorbike()
{
    std::string model, color, engineSizeVal, transmissionMode, description, yearMadeVal, minimumRenterRatingVal, consumingPointVal;
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
    // std::cout << "Enter minimum renter rating: ";
    // std::cin >> minimumRenterRatingVal;
    std::cout << "Enter consuming point: ";
    std::cin >> consumingPointVal;

    double engineSize = Method::validateDouble(engineSizeVal);
    int yearMade = Method::validateNumber(yearMadeVal);
    int consumingPoint = Method::validateNumber(consumingPointVal);

    Motorbike motorbike(model, color, engineSize, transmissionMode, yearMade,
                        description, consumingPoint, this);
    this->setMotorbikes(motorbike);
    std::cout << "Motorbike added!" << std::endl;
}

void Member::listMotorbike()
{
    Motorbike motorbike = this->getMotorbikes();
    std::string minimumRenterRatingVal;

    if (motorbike.isAvailable())
    {
        std::cout << "This motorbike is already listed!" << std::endl;
    }
    else
    {
        motorbike.setAvailability(true);
        std::cout << "Enter minimum renter rating (enter 0 if you don't want to set rating):" << std::endl;
        std::cin >> minimumRenterRatingVal;
        int minimumRenterRating = Method::validateNumber(minimumRenterRatingVal);

        motorbike.setMinimumRenterRating(minimumRenterRating);

        DateTime startDate, endDate;
        bool validPeriod = false;

        while (!validPeriod)
        {
            std::cout << "Enter start date (YYYY-MM-DD): ";
            std::string startDateTimeStr;
            std::cin.ignore(); // Consume newline character
            std::getline(std::cin, startDateTimeStr);

            std::cout << "Enter end date (YYYY-MM-DD): ";
            std::string endDateTimeStr;
            std::getline(std::cin, endDateTimeStr);

            // Create instances of DateTime
            DateTime startDateTime = DateTime(); // You might need to pass date/time components here
            DateTime endDateTime = DateTime();   // You might need to pass date/time components here

            // Call non-static member functions on the DateTime instances
            if (startDateTime.parseDateTime(startDateTimeStr) && endDateTime.parseDateTime(endDateTimeStr))
            {
                // Check if the period is valid
                if (startDateTime <= endDateTime)
                {
                    validPeriod = true;
                    startDate = startDateTime;
                    endDate = endDateTime;
                }
                else
                {
                    std::cout << "Invalid date/time period. End date should be later than or equal to start date. Please try again." << std::endl;
                }
            }
            else
            {
                std::cout << "Invalid date/time format. Please enter dates in the format YYYY-MM-DD." << std::endl;
            }
        }

        // Rest of your code

        // Create a TimePeriod object from the start and end dates
        TimePeriod period(startDate, endDate);

        // Set the rental period for the motorbike
        motorbike.setRentalDetails(period);

        std::cout << "Motorbike listed successfully!" << std::endl;
    }
}

// Unlist a motorbike
void Member::unlistMotorbike()
{
    Motorbike motorbike = this->getMotorbikes();
    motorbike.setAvailability(false);
    motorbike.removeAvailablePeriods();
    std::cout << "Motorbike unlisted!" << std::endl;
    
}

// Request to rent a motorbike
bool Member::requestToRentMotorbike(Motorbike& motorbike, TimePeriod period) {
    // Check if the motorbike is available for the specified rental period
    if (!motorbike.isAvailable() || !motorbike.periodIsValid(period)) {
        std::cout << "Motorbike is not available for the specified rental period or the period is invalid." << std::endl;
        return false;
    }

    if (this->getRatingScores() <= motorbike.getMinimumRenterRating()) {
        std::cout << "You do not have enough rating to rent this motorbike!" << std::endl;
        return false;
    }

    // Create a rental request
    RentalRequest request(*this, motorbike, period);

    // Send the rental request to the motorbike owner
    motorbike.getOwner()->receiveRentalRequest(request);

    // Add the rental request to the member's list of rental requests
    rentedRentalRequests.push_back(request);

    std::cout << "Rental request sent to the motorbike owner." << std::endl;
    return true;
}

void Member::receiveRentalRequest(const RentalRequest& request) {

    // Check if the request is valid, e.g., it's for a motorbike owned by this member
    if (request.getMotorbike().getOwner() == this) {      
        
        // Add the request to the list of received requests
        rentalRequests.push_back(request);

        // Provide feedback or confirmation to the requester
        std::cout << "Rental request received and added to the owner request list." << std::endl;
        
    } else {
        // Handle the case where the request is not for a motorbike owned by this member
        std::cout << "This rental request is not for one of his/her motorbikes." << std::endl;
    }

}



// View rental requests (1 or 2)
void Member::viewRequests(std::string type) {
    std::cout << "Rental Requests:" << std::endl;
    int index = 1; // Initialize an index counter

    if (type == "1") {
        // Print all rental requests
        for (const RentalRequest& request : rentalRequests) {
            Member member = request.getRequester();
            TimePeriod period = request.getRentalPeriod();
            std::cout << "Index: " << index << std::endl; // Print the index
            std::cout << "Requester ID: " << member.getId() << std::endl;
            std::cout << "Requester Name: " << member.getFullName() << std::endl;
            std::cout << "Start Date: " << period.getStartDate().toString() << std::endl;
            std::cout << "End Date: " << period.getEndDate().toString() << std::endl;
            std::cout << "Status: " << request.getStatus() << std::endl;
            std::cout << "----------------------" << std::endl;
        index++;
        }
    } else if (type == "2") {
        // Print only rented rental requests
        for (const RentalRequest& request : rentedRentalRequests) {
            if (request.getStatus() == "Rented") {
                Member member = request.getRequester();
                TimePeriod period = request.getRentalPeriod();
                std::cout << "Index: " << index << std::endl; // Print the index
                std::cout << "Requester ID: " << member.getId() << std::endl;
                std::cout << "Requester Name: " << member.getFullName() << std::endl;
                std::cout << "Start Date: " << period.getStartDate().toString() << std::endl;
                std::cout << "End Date: " << period.getEndDate().toString() << std::endl;
                std::cout << "Status: " << request.getStatus() << std::endl;
                std::cout << "----------------------" << std::endl;
            index++;
            }
        }
    } else {
        std::cout << "Invalid request type. Please specify '1' to view all requests or '2' to view rented requests." << std::endl;
    }
}


void Member::viewRentalRequests(const std::string& type, const std::string& status) {
    int index = 1; // Initialize an index counter
    
    if (type == "1") {
        std::cout << "All Rental Requests:" << std::endl;
        // Loop through all rental requests
        for (const RentalRequest& request : rentalRequests) {
            if (request.getStatus() == status) {
                Member member = request.getRequester();
                TimePeriod period = request.getRentalPeriod();
                std::cout << "Index: " << index << std::endl; // Print the index
                std::cout << "Requester ID: " << member.getId() << std::endl;
                std::cout << "Requester Name: " << member.getFullName() << std::endl;
                std::cout << "Start Date: " << period.getStartDate().toString() << std::endl;
                std::cout << "End Date: " << period.getEndDate().toString() << std::endl;
                std::cout << "----------------------" << std::endl;
            index++;
            }
        }
    } else if (type == "2") {
        std::cout << "Rented Rental Requests:" << std::endl;
        // Loop through rented rental requests
        for (const RentalRequest& request : rentedRentalRequests) {
            if (request.getStatus() == "Rented" && request.getStatus() == status) {
                Member member = request.getRequester();
                TimePeriod period = request.getRentalPeriod();
                std::cout << "Index: " << index << std::endl; // Print the index
                std::cout << "Requester ID: " << member.getId() << std::endl;
                std::cout << "Requester Name: " << member.getFullName() << std::endl;
                std::cout << "Start Date: " << period.getStartDate().toString() << std::endl;
                std::cout << "End Date: " << period.getEndDate().toString() << std::endl;
                std::cout << "----------------------" << std::endl;
            index++;
            }
        }
    } else {
        std::cout << "Invalid request type. Please specify '1' to view all requests or '2' to view rented requests." << std::endl;
    }
}



// Rate a rented motorbike, user rent another motorbike
void Member::rateMotorbike(Motorbike motorbike, RentalRequest motorbikeRequest)
{
    // Prompt the user to input a review score (1 to 10)
    int score;
    std::cout << "Enter a rating score for the motorbike (1 to 10): ";
    std::cin >> score;

    // Check if the score is within the valid range
    if (score < 1 || score > 10) {
        std::cout << "Invalid rating score. Please enter a score between 1 and 10." << std::endl;
        return;
    }

    // Consume the newline character
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Prompt the user to input a review comment
    std::string comment;
    std::cout << "Enter a comment for the motorbike: ";
    std::getline(std::cin, comment);

    motorbikeRequest.getMotorbikeReview().setComment(comment);
    motorbikeRequest.getMotorbikeReview().setScore(score);
    motorbike.editMotorbikeRatingScore(rentedRentalRequests);
    motorbike.getOwner()->addRentedRentalRequest(motorbikeRequest);
    this->addRentalRequest(motorbikeRequest);

    std::cout << "You have successfully rated the motorbike." << std::endl;
}

void Member::editMemberRatingScore() {
    int totalScore = 0;
    int numberOfReviews = 0;

    // Loop through the rentedRentalRequests
    for (const RentalRequest& request : rentalRequests) {
        if (request.getStatus() == "Rented") {
            // Get the renterReview from each rented rental request
            Review renterReview = request.getRenterReview();
            
            // Check if a review exists for this request
            if (renterReview.getScore() > 0) {
                // Sum up the scores and count the number of reviews
                totalScore += renterReview.getScore();
                numberOfReviews++;
            }
        }
    }

    if (numberOfReviews > 0) {
        // Calculate the average score
        double averageScore = static_cast<double>(totalScore) / numberOfReviews;
        
        // Update the member's rating score
        ratingScores = averageScore;

        std::cout << "Member's rating score has been updated to: " << averageScore << std::endl;
    } else {
        std::cout << "No renter reviews found to calculate the rating score." << std::endl;
    }
}






// Rate a renter (another member)
void Member::rateRenter(Member renter, RentalRequest renterRequest) {
    // Check if the renter exists and is not the same as the current member
    if (&renter == this) {
        std::cout << "You cannot rate yourself." << std::endl;
        return;
    }

    int score;
    std::cout << "Enter a rating score for the renter (1 to 10): ";
    std::cin >> score;

    // Check if the score is within the valid range
    if (score < 1 || score > 10) {
        std::cout << "Invalid rating score. Please enter a score between 1 and 10." << std::endl;
        return;
    }

    // Consume the newline character
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Prompt the user to input a review comment
    std::string comment;
    std::cout << "Enter a comment for the renter: ";
    std::getline(std::cin, comment);


    
    renterRequest.getRenterReview().setComment(comment);
    renterRequest.getRenterReview().setScore(score);
    editMemberRatingScore();

    std::cout << "You have successfully rated the renter." << std::endl;
}


// Top up credit points
void Member::topUpCreditPoints() {
    int amount;
    std::cout << "Enter the amount to top up your credit points: ";
    std::cin >> amount;

    // Check if the input is a positive amount
    if (amount <= 0) {
        std::cout << "Invalid amount. Please enter a positive number to top up your credit points." << std::endl;
        return;
    }

    // Add the specified amount to the member's credit points balance
    creditPoints += amount;

    std::cout << "Your credit points have been topped up. Your new balance is: " << creditPoints << " points." << std::endl;
}

void Member::viewUnscoredRequests(bool showRentedRequests) {
    std::string requestType = showRentedRequests ? "Rented Rental Requests" : "Rental Requests"; // if true: rented; false, renter
    std::cout << "Unscored " << requestType << ":" << std::endl;

    // Loop through either rentalRequests or rentedRentalRequests based on showRentedRequests
    const std::vector<RentalRequest>& requests = showRentedRequests ? rentedRentalRequests : rentalRequests;

    int index = 1; // Initialize an index counter

    for (const RentalRequest& request : requests) {
        // Check if the request has not been scored
        if (!request.hasRenterReview()) {
            Member requester = request.getRequester();
            TimePeriod period = request.getRentalPeriod();
            
            std::cout << "Index: " << index << std::endl; // Print the index
            std::cout << "Requester ID: " << requester.getId() << std::endl;
            std::cout << "Requester Name: " << requester.getFullName() << std::endl;
            std::cout << "Start Date: " << period.getStartDate().toString() << std::endl;
            std::cout << "End Date: " << period.getEndDate().toString() << std::endl;
            std::cout << "Status: " << request.getStatus() << std::endl;
            std::cout << "----------------------" << std::endl;

            index++; // Increment the index counter
        }
    }
}




// View member information
void Member::viewMemberInfo()
{
    std::cout << "Member Information:" << std::endl;
    std::cout << "Username: " << getUsername() << std::endl;
    std::cout << "Full Name: " << getFullName() << std::endl;
    std::cout << "Phone Number: " << getPhoneNumber() << std::endl;
    std::cout << "ID Type: " << getIdType() << std::endl;
    std::cout << "ID Number: " << getIdNumber() << std::endl;
    std::cout << "Driver's License Number: " << getDriverLicenseNumber() << std::endl;
    std::cout << "Expiry Date: " << getExpiryDate() << std::endl;
    std::cout << "Credit Points: " << getCreditPoints() << std::endl;
    std::cout << "Rating Scores: " << getRatingScores() << std::endl;

    // You can add more member details here if needed

    std::cout << "----------------------" << std::endl;
}


std::string Member::getRole()
{
    return "Member";
}

std::string Member::getId() const
{
    return id;
}

std::string Member::getFullName() const
{
    return fullName;
}

std::string Member::getPhoneNumber() const
{
    return phoneNumber;
}

std::string Member::getIdType() const
{
    return idType;
}

std::string Member::getIdNumber() const
{
    return idNumber;
}

std::string Member::getDriverLicenseNumber() const
{
    return driverLicenseNumber;
}

std::string Member::getExpiryDate() const
{
    return expiryDate;
}

int Member::getCreditPoints() const
{
    return creditPoints;
}

Motorbike Member::getMotorbikes() const
{
    return motorbikes;
}

double Member::getRatingScores() const
{
    return ratingScores;
}

std::vector<RentalRequest> Member::getRentalRequests() const
{
    return rentalRequests;
}

std::vector<RentalRequest> Member::getRentedRentalRequests() const
{
    return rentedRentalRequests;
}

int Member::getCreditPoints() const
{
    return creditPoints;
}




// Setter functions
void Member::setId(const std::string &newId)
{
    id = newId;
}

void Member::setFullName(const std::string &newFullName)
{
    fullName = newFullName;
}

void Member::setPhoneNumber(const std::string &newPhoneNumber)
{
    phoneNumber = newPhoneNumber;
}

void Member::setIdType(const std::string &newIdType)
{
    idType = newIdType;
}

void Member::setIdNumber(const std::string &newIdNumber)
{
    idNumber = newIdNumber;
}

void Member::setDriverLicenseNumber(const std::string &newDriverLicenseNumber)
{
    driverLicenseNumber = newDriverLicenseNumber;
}

void Member::setExpiryDate(const std::string &newExpiryDate)
{
    expiryDate = newExpiryDate;
}

void Member::setCreditPoints(int newCreditPoints)
{
    creditPoints = newCreditPoints;
}

void Member::setCreditPoints(int newCreditPoints)
{
    creditPoints = newCreditPoints;
}

void Member::setMotorbikes(Motorbike newMotorbike)
{
    motorbikes = newMotorbike;
    std::cout << "Motorbike added!" << std::endl;
}

void Member::setRatingScores(double newRatingScores)
{
    ratingScores = newRatingScores;
}

void Member::setRentalRequests(const std::vector<RentalRequest> &newRentalRequests)
{
    rentalRequests = newRentalRequests;
}

void Member::setRentedRentalRequests(const std::vector<RentalRequest> &newRentedRentalRequests)
{
    rentedRentalRequests = newRentedRentalRequests;
}

void Member::addRentalRequest(const RentalRequest &request)
{
    rentalRequests.push_back(request);
}

void Member::addRentedRentalRequest(const RentalRequest &rentRequest)
{
    rentedRentalRequests.push_back(rentRequest);
}

std::string Member::getCity() {
    return city;
};


void Member::setCity(std::string city) {
    this->city = city;
};
