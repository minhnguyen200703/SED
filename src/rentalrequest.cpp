#include "../include/rentalrequest.h"
#include <fstream> // Include the necessary header
#include <sstream> // Include the <sstream> header


// Constructors
RentalRequest::RentalRequest(Member& requester, Motorbike* motorbike, const TimePeriod& rentalPeriod)
    : id(createAutoIncrementedId("./data/RentalRequest.txt")), requester(&requester), motorbike(motorbike), rentalPeriod(rentalPeriod), status("Pending") {}


RentalRequest::RentalRequest(std::string id, Member requester, Motorbike* motorbike, const TimePeriod rentalPeriod, Review motorbikeReview, Review renterReview, std::string status)
    : id(id), requester(&requester), motorbike(motorbike), rentalPeriod(rentalPeriod), motorbikeReview(motorbikeReview), renterReview(renterReview), status(status) {}

    RentalRequest::RentalRequest() {};

// Getter functions
Member& RentalRequest::getRequester() const {
    return *requester;
}

Motorbike& RentalRequest::getMotorbike() const {
    return *motorbike;
}

TimePeriod RentalRequest::getRentalPeriod() const {
    return rentalPeriod;
}

Review RentalRequest::getMotorbikeReview() const {
    return motorbikeReview;
}

Review RentalRequest::getRenterReview() const {
    return renterReview;
}

std::string RentalRequest::getStatus() const {
    return status;
}
std::string RentalRequest::getId() const {
    return id;
}; // New getter for status

void RentalRequest::setId(const std::string& newId) {
    this->id = newId;
}; // New setter for status


// Setter functions
void RentalRequest::setMotorbikeReview(const Review& motorbikeReview) {
    this->motorbikeReview = motorbikeReview;
}

void RentalRequest::setRenterReview(const Review& renterReview) {
    this->renterReview = renterReview;
}

void RentalRequest::setStatus(const std::string& newStatus) {
    status = newStatus;
}

bool RentalRequest::hasRenterReview() const {
    // Check if the renterReview attribute has been set
    return renterReview.getScore() > 0; // You can modify this condition based on your Review class implementation
}

void RentalRequest::displayRequestDetails() const
{
    // Display the details of the rental request
    std::cout << "Rental Request Details:" << std::endl;
    std::cout << "Requester: " << requester->getFullName() << std::endl;
    std::cout << "Motorbike: " << motorbike->getMotorbikeDetails() << std::endl;
    std::cout << "Rental Period: " << rentalPeriod.getStartDate().toString() << " to " << rentalPeriod.getEndDate().toString() << std::endl;
    std::cout << "Status: " << status << std::endl;

    // Check if there is a motorbike review
    if (motorbikeReview.getScore() > 0)
    {
        std::cout << "Motorbike Review:" << std::endl;
        std::cout << "Rating: " << motorbikeReview.getScore() << "/10" << std::endl;
        std::cout << "Comments: " << motorbikeReview.getComment() << std::endl;
    }

    // Check if there is a renter review
    if (hasRenterReview())
    {
        std::cout << "Renter Review:" << std::endl;
        std::cout << "Rating: " << renterReview.getScore() << "/10" << std::endl;
        std::cout << "Comments: " << renterReview.getComment() << std::endl;
    }
    else
    {
        std::cout << "No renter review available." << std::endl;
    }
}

std::string RentalRequest::createAutoIncrementedId(std::string filename) {
    int maxId = 0;
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string id;
                if (std::getline(iss, id, '|')) {
                    int accountId = std::stoi(id);
                    maxId = std::max(maxId, accountId);
                }
            }
            file.close();
        } else {
            std::cerr << "Failed to open file: " << filename << std::endl;
            return 0;
        }

        // Generate the new account's ID
        int newId = maxId + 1;
        return std::to_string(newId);
}