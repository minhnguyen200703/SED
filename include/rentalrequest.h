#ifndef RENTALREQUEST_H
#define RENTALREQUEST_H

#include "Member.h"
#include "Motorbike.h"
#include "TimePeriod.h"
#include "Review.h"

class RentalRequest {
private:
    Member* requester; // Pointer to the member making the request
    Motorbike* motorbike; // Pointer to the motorbike being requested
    TimePeriod rentalPeriod;
    Review motorbikeReview;
    Review renterReview;
    std::string status;

public:
    // Constructors
    RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod);
    RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod, Review& motorbikeReview);
    RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod, Review& motorbikeReview, Review& renterReview);

    // Getter functions
    Member& getRequester() const;
    Motorbike& getMotorbike() const;
    TimePeriod getRentalPeriod() const;
    Review getMotorbikeReview() const;
    Review getRenterReview() const;
    std::string getStatus() const; // New getter for status

    // Setter functions
    void setMotorbikeReview(const Review& motorbikeReview);
    void setRenterReview(const Review& renterReview);
    void setStatus(const std::string& newStatus); // New setter for status

    bool RentalRequest::hasRenterReview() const;
};

#endif
