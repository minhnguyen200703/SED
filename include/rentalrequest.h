#ifndef RENTALREQUEST_H
#define RENTALREQUEST_H

#include "../include/member.h"
#include "../include/motorbike.h"
#include "../include/timeperiod.h"
#include "../include/review.h"

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
    RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod); // Create New
    RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod);
    RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod, Review& motorbikeReview, Review& renterReview, std::string status);

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

    bool hasRenterReview() const;
    void displayRequestDetails() const;
};

#endif
