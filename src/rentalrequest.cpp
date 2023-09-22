#include "RentalRequest.h"

// Constructors
RentalRequest::RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod)
    : requester(&requester), motorbike(&motorbike), rentalPeriod(rentalPeriod), status("Pending") {}

RentalRequest::RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod, Review& motorbikeReview)
    : requester(&requester), motorbike(&motorbike), rentalPeriod(rentalPeriod), motorbikeReview(motorbikeReview), status("Pending") {}

RentalRequest::RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod, Review& motorbikeReview, Review& renterReview)
    : requester(&requester), motorbike(&motorbike), rentalPeriod(rentalPeriod), motorbikeReview(motorbikeReview), renterReview(renterReview), status("Pending") {}

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