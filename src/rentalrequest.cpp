// RentalRequest.cpp
#include "RentalRequest.h"
#include "review.h"


RentalRequest::RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod)
    : requester(&requester), motorbike(&motorbike), rentalPeriod(rentalPeriod) {
    // Initialize other RentalRequest attributes or perform necessary setup
}

RentalRequest::RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod, Review& motorbikeReview)
    : requester(&requester), motorbike(&motorbike), rentalPeriod(rentalPeriod), motorbikeReview(motorbikeReview) {
    // Initialize other RentalRequest attributes or perform necessary setup
}

RentalRequest::RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod, Review& motorbikeReview, Review& renterReview)
    : requester(&requester), motorbike(&motorbike), rentalPeriod(rentalPeriod), motorbikeReview(motorbikeReview), renterReview(renterReview) {
    // Initialize other RentalRequest attributes or perform necessary setup
}

Member& RentalRequest::getRequester() const {
    return *requester;
}

Motorbike& RentalRequest::getMotorbike() const {
    return *motorbike;
}

TimePeriod RentalRequest::getRentalPeriod() const {
    return rentalPeriod;
}

// You can add more methods or functionality to the RentalRequest class as needed.
