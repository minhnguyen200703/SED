#ifndef RENTALREQUEST_H
#define RENTALREQUEST_H

#include "Member.h"
#include "Motorbike.h"
#include "TimePeriod.h"
#include "review.h"

class RentalRequest {
private:
    Member* requester; // Pointer to the member making the request
    Motorbike* motorbike; // Pointer to the motorbike being requested
    TimePeriod rentalPeriod;
    Review motorbikeReview;
    Review renterReview;

public:
    RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod);
    RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod, Review& motorbikeReview);
    RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod, Review& motorbikeReview, Review& renterReview);

    Member& getRequester() const;
    Motorbike& getMotorbike() const;
    TimePeriod getRentalPeriod() const;
    void setRenterReview(Review renterReview);
};

#endif
