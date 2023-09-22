#include "../include/rentalrequest.h"

// Constructors
RentalRequest::RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod)
    : requester(&requester), motorbike(&motorbike), rentalPeriod(rentalPeriod), status("Pending") {}


RentalRequest::RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod, Review& motorbikeReview, Review& renterReview, std::string status)
    : requester(&requester), motorbike(&motorbike), rentalPeriod(rentalPeriod), motorbikeReview(motorbikeReview), renterReview(renterReview), status(status) {}

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