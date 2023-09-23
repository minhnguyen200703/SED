#include <fstream>
#include <iostream>
#include <vector>
#include <limits>
#include "../include/member.h"
#include "../include/motorbike.h"
#include "../include/rentalrequest.h"
#include "../include/review.h"
#include "../include/hashpassword.h"
#include "../include/method.h"
#include "../include/datetime.h"
#include "../include/timeperiod.h"
#include "../include/account.h"

// Constructor to initialize member attributes
Member::Member(std::string username, std::string password, std::string fullName, std::string phoneNumber,
               std::string idType, std::string idNumber, std::string driverLicenseNumber, std::string expiryDate, std::string city)
    : Account(username, password), fullName(fullName), phoneNumber(phoneNumber), idType(idType),
      idNumber(idNumber), driverLicenseNumber(driverLicenseNumber), expiryDate(expiryDate), creditPoints(20),
      ratingScores(0), motorbike(), rentalRequests(), rentedRentalRequests(), city(city)
{
}

// for existed member
Member::Member(std::string id, std::string usernameReg, std::string hashedPassword, std::string salt,
               std::string fullName, std::string phoneNumber, std::string idType, std::string idNumber,
               std::string driverLicenseNumber, std::string expiryDate, std::string city, int creditPoints, double ratingScores)
    : Account(id, usernameReg, hashedPassword, salt), fullName(fullName), phoneNumber(phoneNumber), idType(idType),
      idNumber(idNumber), driverLicenseNumber(driverLicenseNumber), expiryDate(expiryDate), creditPoints(creditPoints),
      city(city), motorbike(), rentalRequests(), rentedRentalRequests(), ratingScores(ratingScores)
{
    // Initialize member-specific data members if needed
}

Member::Member(){};

// List a motorbike for rent
void Member::addMotorbike()
{
    std::string model, color, engineSizeVal, transmissionMode, description, yearMadeVal, minimumRenterRatingVal;
    std::cout << "Enter Model Name: " << std::endl;
    std::cin.ignore();
    std::getline(std::cin, model);
    std::cout << "Enter color: " << std::endl;
    std::getline(std::cin, color);
    std::cout << "Enter Transmission Mode: " << std::endl;
    std::getline(std::cin, transmissionMode);
    std::cout << "Enter Description:: " << std::endl;
    std::getline(std::cin, description);
    std::cout << "Enter Engine size: " << std::endl;
    std::getline(std::cin, engineSizeVal);
    std::cout << "Enter Year made: " << std::endl;
    std::getline(std::cin, yearMadeVal);

    int engineSize = Method::validateNumber(engineSizeVal);
    int yearMade = Method::validateNumber(yearMadeVal);

    // Create a new Motorbike object using dynamic allocation (new)
    Motorbike *newMotorbike = new Motorbike(
        model, color, engineSize, transmissionMode, yearMade, description, this);

    // Set the member variable to point to the newly allocated Motorbike object
    this->motorbike = newMotorbike;
}

// List a motorbike
void Member::listMotorbike()
{
    std::string minimumRenterRatingVal;
    std::string consumingPointsVal;

    Motorbike *memberMotorbike = this->getMotorbike();

    if (memberMotorbike->getAvailability())
    {
        std::cout << "This motorbike is already listed!" << std::endl;
    }
    else
    {
        std::cout << "Listing motorbike:" << std::endl;

        std::cout << "Enter consuming points:" << std::endl;
        std::cin >> consumingPointsVal;
        int consumingPoints = Method::validateNumber(consumingPointsVal);

        // Set the consuming points for the member's motorbike
        memberMotorbike->setConsumingPoint(consumingPoints);

        std::cout << "Enter minimum renter rating (enter 0 if you don't want to set rating):" << std::endl;
        std::cin >> minimumRenterRatingVal;
        int minimumRenterRating = Method::validateNumber(minimumRenterRatingVal);

        // Set the minimum renter rating for the member's motorbike
        memberMotorbike->setMinimumRenterRating(minimumRenterRating);

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

        // Set the rental period for the member's motorbike
        memberMotorbike->setRentalDetails(period);

        // Set the motorbike as available
        memberMotorbike->setAvailability(true);

        // Find and replace the existing member's motorbike in the motorbikes vector

        std::cout << "Motorbike listed successfully!" << std::endl;
    }
}

// Unlist a motorbike
// Unlist a motorbike
void Member::unlistMotorbike()
{
    Motorbike *memberMotorbike = this->getMotorbike();

    // Set the availability of the member's motorbike to false
    memberMotorbike->setAvailability(false);

    // Find and replace the existing member's motorbike in the motorbikes vector

    std::cout << "Motorbike unlisted!" << std::endl;
}

// Request to rent a motorbike
bool Member::requestToRentMotorbike(Motorbike *motorbike, TimePeriod period)
{
    // Check if the motorbike is available for the specified rental period
    if (!motorbike->isAvailable() || !motorbike->periodIsValid(period))
    {
        std::cout << "Motorbike is not available for the specified rental period or the period is invalid." << std::endl;
        return false;
    }

    // Create a rental request
    RentalRequest request(*this, motorbike, period);

    //  the rental request to the motorbike owner
    motorbike->getOwner()->receiveRentalRequest(request);

    // Add the rental request to the member's list of rental requests
    rentedRentalRequests.push_back(request);

    std::cout << "Rental request sent to the motorbike owner." << std::endl;
    return true;
}

void Member::receiveRentalRequest(const RentalRequest &request)
{

    // Check if the request is valid, e.g., it's for a motorbike owned by this member
    if (request.getMotorbike().getOwner() == this)
    {

        // Add the request to the list of received requests
        rentalRequests.push_back(request);

        // Provide feedback or confirmation to the requester
        std::cout << "Rental request received and added to the owner request list." << std::endl;
    }
    else
    {
        // Handle the case where the request is not for a motorbike owned by this member
        std::cout << "This rental request is not for one of his/her motorbike." << std::endl;
    }
}

// View rental requests (1 or 2)
void Member::viewRequests(std::string type)
{
    int index = 1; // Initialize an index counter

    if (type == "1")
    {
        if (rentalRequests.empty())
        {
            std::cout << "No rental requests found." << std::endl;
            return;
        }
        else
        {
            std::cout << "Rental Requests:" << std::endl;

            // Print all rental requests
            for (const RentalRequest &request : rentalRequests)
            {
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
    }
    else if (type == "2")
    {
        if (rentalRequests.empty())
        {
            std::cout << "No rental requests found." << std::endl;
            return;
        }
        else
        {
            std::cout << "Rented rental Requests:" << std::endl;
            // Print only rented rental requests
            for (const RentalRequest &request : rentedRentalRequests)
            {
                if (request.getStatus() == "Rented")
                {
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
        }
    }
    else
    {
        std::cout << "Invalid request type. Please specify '1' to view all requests or '2' to view rented requests." << std::endl;
    }
}

void Member::viewRentalRequests(const std::string &type, const std::string &status)
{
    int index = 1; // Initialize an index counter
    if (type == "1")
    {
        if (rentalRequests.empty())
        {
            std::cout << "No " << status << " rental requests found." << std::endl;
            return;
        }
        else
        {

            std::cout << "All Rental Requests:" << std::endl;
            // Loop through all rental requests
            for (const RentalRequest &request : rentalRequests)
            {
                if (request.getStatus() == status)
                {
                    Member member = request.getRequester();
                    TimePeriod period = request.getRentalPeriod();
                    std::cout << "Index: " << index << std::endl; // Print the index
                    std::cout << "Requester ID: " << member.getId() << std::endl;
                    std::cout << "Requester Name: " << member.getFullName() << std::endl;
                    std::cout << "Start Date: " << period.getStartDate().toString() << std::endl;
                    std::cout << "End Date: " << period.getEndDate().toString() << std::endl;
                    std::cout << "----------------------" << std::endl;
                }
                index++;
            }
        }
    }
    else if (type == "2")
    {
        if (rentalRequests.empty())
        {
            std::cout << "No " << status << " rental requests found." << std::endl;
            return;
        }
        else
        {

            std::cout << "Rented Rental Requests:" << std::endl;
            // Loop through rented rental requests
            for (const RentalRequest &request : rentedRentalRequests)
            {
                if (request.getStatus() == "Rented" && request.getStatus() == status)
                {
                    Member member = request.getRequester();
                    TimePeriod period = request.getRentalPeriod();
                    std::cout << "Index: " << index << std::endl; // Print the index
                    std::cout << "Requester ID: " << member.getId() << std::endl;
                    std::cout << "Requester Name: " << member.getFullName() << std::endl;
                    std::cout << "Start Date: " << period.getStartDate().toString() << std::endl;
                    std::cout << "End Date: " << period.getEndDate().toString() << std::endl;
                    std::cout << "----------------------" << std::endl;
                }
                index++;
            }
        }
    }
    else
    {
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
    if (score < 1 || score > 10)
    {
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
    motorbike.editMotorbikeRatingScore();
    motorbike.getOwner()->addRentedRentalRequest(motorbikeRequest);
    this->addRentalRequest(motorbikeRequest);

    std::cout << "You have successfully rated the motorbike." << std::endl;
}

void Member::editMemberRatingScore()
{
    int totalScore = 0;
    int numberOfReviews = 0;

    // Loop through the rentedRentalRequests
    for (const RentalRequest &request : rentalRequests)
    {
        if (request.getStatus() == "Rented")
        {
            // Get the renterReview from each rented rental request
            Review renterReview = request.getRenterReview();

            // Check if a review exists for this request
            if (renterReview.getScore() > 0)
            {
                // Sum up the scores and count the number of reviews
                totalScore += renterReview.getScore();
                numberOfReviews++;
            }
        }
    }

    if (numberOfReviews > 0)
    {
        // Calculate the average score
        double averageScore = static_cast<double>(totalScore) / numberOfReviews;

        // Update the member's rating score
        ratingScores = averageScore;

        std::cout << "Member's rating score has been updated to: " << averageScore << std::endl;
    }
    else
    {
        std::cout << "No renter reviews found to calculate the rating score." << std::endl;
    }
}

// Top up credit points
void Member::topUpCreditPoints()
{
    int amount;
    std::cout << "Enter the amount to top up your credit points: ";
    std::cin >> amount;

    // Check if the input is a positive amount
    if (amount <= 0)
    {
        std::cout << "Invalid amount. Please enter a positive number to top up your credit points." << std::endl;
        return;
    }

    // Add the specified amount to the member's credit points balance
    creditPoints += amount;

    std::cout << "Your credit points have been topped up. Your new balance is: " << creditPoints << " points." << std::endl;
}

void Member::viewUnscoredRequests(bool showRentedRequests)
{
    std::string requestType = showRentedRequests ? "Rented Rental Requests" : "Rental Requests"; // if true: rented; false, renter
    std::cout << "Unscored " << requestType << ":" << std::endl;

    // Loop through either rentalRequests or rentedRentalRequests based on showRentedRequests
    const std::vector<RentalRequest> &requests = showRentedRequests ? rentedRentalRequests : rentalRequests;

    int index = 1; // Initialize an index counter

    for (const RentalRequest &request : requests)
    {
        // Check if the request has not been scored
        if (!request.hasRenterReview())
        {
            Member requester = request.getRequester();
            TimePeriod period = request.getRentalPeriod();

            std::cout << "Index: " << index << std::endl; // Print the index
            std::cout << "Requester ID: " << requester.getId() << std::endl;
            std::cout << "Requester Name: " << requester.getFullName() << std::endl;
            std::cout << "Start Date: " << period.getStartDate().toString() << std::endl;
            std::cout << "End Date: " << period.getEndDate().toString() << std::endl;
            std::cout << "Status: " << request.getStatus() << std::endl;
            std::cout << "----------------------" << std::endl;
        }
        index++; // Increment the index counter
    }
}

// View member information
void Member::viewMemberInfo()
{
    std::cout << "Member Information:" << std::endl;
    std::cout << "Username: " << Account::getUsername() << std::endl;
    std::cout << "Full Name: " << getFullName() << std::endl;
    std::cout << "Phone Number: " << getPhoneNumber() << std::endl;
    std::cout << "ID Type: " << getIdType() << std::endl;
    std::cout << "ID Number: " << getIdNumber() << std::endl;
    std::cout << "Driver's License Number: " << getDriverLicenseNumber() << std::endl;
    std::cout << "Expiry Date: " << getExpiryDate() << std::endl;
    std::cout << "City: " << getCity() << std::endl;
    std::cout << "Credit Points: " << getCreditPoints() << std::endl;
    std::cout << "Rating Scores: " << getRatingScores() << std::endl;

    // You can add more member details here if needed

    if (getMotorbike())
    {

        Motorbike *mtb = this->getMotorbike();
        std::cout << std::endl
                  << "Motorbike details:" << std::endl;
        std::cout << mtb->getMotorbikeDetails() << std::endl;
    }
    else
    {
        std::cout << " None" << std::endl;
    }

    std::cout << "----------------------" << std::endl;
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

Motorbike *Member::getMotorbike() const
{
    return motorbike;
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

void Member::setMotorbike(Motorbike &newMotorbike)
{
    Motorbike *motorbikePtr = new Motorbike(newMotorbike);

    motorbike = motorbikePtr;

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

std::string Member::getCity() const
{
    return city;
};

void Member::setCity(std::string city)
{
    this->city = city;
};

void Member::changeRequestStatusById(std::string requestId, const std::string &newStatus)
{

    for (RentalRequest &request : this->getRentedRentalRequests())
    {
        if (request.getId() == requestId)
        {
            // Found the request with the given ID, update its status
            request.setStatus(newStatus);
            return; // Exit the function after updating the status
        }
    }
}

std::vector<RentalRequest> Member::acceptRequest(RentalRequest *currentRequest)
{
    std::vector<RentalRequest> newRentalRequests;

    // Loop through the rental requests of the member
    for (RentalRequest &request : rentalRequests)
    {
        // Check if the current request's time period overlaps with the other request's time period
        if (currentRequest->getId() == request.getId())
        {
            request.setStatus("Accepted");
            request.getRequester().changeRequestStatusById(currentRequest->getId(), "Accepted");
            newRentalRequests.push_back(request);
        }
        else if (currentRequest->getRentalPeriod().overlapsWith(request.getRentalPeriod()))
        {
            // If there is an overlap and the requests are not the same, set the other request's status to denied
            request.setStatus("Denied");
            request.getRequester().changeRequestStatusById(currentRequest->getId(), "Denied");

            newRentalRequests.push_back(request); // Add the denied request to the vector
        }
        else
        {
            newRentalRequests.push_back(request); // Add the denied request to the vector
        }

        // After checking all requests, set the current request's status to accepted
    }
    return newRentalRequests; // Return the vector of denied requests
}

// In the Member class
void Member::RentRequestedMotorbike()
{
    // Step 1: List the rental requests with status "Accepted"
    int index = 1;
    std::cout << "List of Accepted request:" << std::endl;

    this->viewRentalRequests("1", "Accepted");

    // Step 2: Ask the member to choose a rental request by index
    std::cout << "Enter the index of the rental request for the rented motorbike you want to rate: ";
    int selectedIndex;
    std::cin >> selectedIndex;

    // Check if the selected index is valid
    if (selectedIndex >= 1 && (selectedIndex - 1) <= rentedRentalRequests.size())
    {
        // Step 3: Prompt the member to rate the rented motorbike
        RentalRequest &selectedRequest = rentedRentalRequests[selectedIndex - 1];

        if (selectedRequest.getStatus() != "Accepted")
        {
            std::cout << "Invalid selection. Please choose an accepted rental request." << std::endl;
            return;
        }

        std::cout << "Rate the rented motorbike from 1 to 10 (10 being the best): ";
        int rating;
        std::cin >> rating;

        // Validate the rating (1-10 range)
        if (rating < 1 || rating > 10)
        {
            std::cout << "Invalid rating. Please enter a rating between 1 and 10." << std::endl;
            return;
        }

        std::cin.ignore(); // Clear newline from the input buffer

        std::cout << "Enter a comment for your rating: ";
        std::string comment;
        std::getline(std::cin, comment);

        // Step 4: Set the rating and comment for the rented motorbike
        selectedRequest.setMotorbikeReview(Review(rating, comment));

        std::cout << "Thank you for rating the rented motorbike!" << std::endl;
    }
    else
    {
        std::cout << "Invalid selection. Please enter a valid index." << std::endl;
    }
}

// In the Member class
void Member::RateRenter()
{
    // Create a vector to store the indices of rental requests that can be rated
    std::vector<int> unratedRentalIndices;

    // Step 1: Loop through rentalRequests and find "Rented" status requests without renter reviews
    int index = 1;
    for (size_t i = 0; i < rentalRequests.size(); ++i)
    {
        if (rentalRequests[i].getStatus() == "Rented" && !rentalRequests[i].hasRenterReview())
        {
            unratedRentalIndices.push_back(i);
            std::cout << index << ". ";
            rentalRequests[i].displayRequestDetails(); // Implement this function in RentalRequest class
        }
        ++index;
    }

    // Step 2: Check if there are unrated rental requests
    if (unratedRentalIndices.empty())
    {
        std::cout << "No renters need to be rated at the moment." << std::endl;
        return;
    }

    // Step 3: Prompt the member to select a rental request by index
    std::cout << "Enter the index of the rental request you want to rate: ";
    int selectedIndex;
    std::cin >> selectedIndex;

    // Check if the selected index is valid
    if (selectedIndex >= 1 && selectedIndex <= static_cast<int>(unratedRentalIndices.size()))
    {
        // Get the index of the selected rental request in the overall rentalRequests vector
        int selectedRentalIndex = unratedRentalIndices[selectedIndex - 1];

        // Step 4: Prompt the member to rate the renter
        std::cout << "Rate the renter from 1 to 10 (10 being the best): ";
        int rating;
        std::cin >> rating;

        // Validate the rating (1-10 range)
        if (rating < 1 || rating > 10)
        {
            std::cout << "Invalid rating. Please enter a rating between 1 and 10." << std::endl;
            return;
        }

        std::cin.ignore(); // Clear newline from the input buffer

        std::cout << "Enter a comment for your rating: ";
        std::string comment;
        std::getline(std::cin, comment);

        // Step 5: Set the renter review for the selected rental request
        rentalRequests[selectedRentalIndex].setRenterReview(Review(rating, comment));

        std::cout << "Thank you for rating the renter!" << std::endl;
    }
    else
    {
        std::cout << "Invalid selection. Please enter a valid index." << std::endl;
    }
}

// Add credit points to the member's account
void Member::addCreditPoints()
{
    int amountToAdd;
    std::cout << "Enter the amount to add to your credit points: ";
    std::cin >> amountToAdd;

    if (amountToAdd <= 0)
    {
        std::cout << "Invalid amount. Please enter a positive number to add credit points." << std::endl;
        return;
    }

    // Add the specified amount to the member's credit points balance
    creditPoints += amountToAdd;

    std::cout << "Your credit points have been added. Your new balance is: " << creditPoints << " points." << std::endl;
};
