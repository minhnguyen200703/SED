#ifndef RENTALREQUEST_H
#define RENTALREQUEST_H

#include "Member.h"
#include "Motorbike.h"
#include "TimePeriod.h"

class RentalRequest {
private:
    Member* requester; // Pointer to the member making the request
    Motorbike* motorbike; // Pointer to the motorbike being requested
    TimePeriod rentalPeriod;

public:
    RentalRequest(Member& requester, Motorbike& motorbike, const TimePeriod& rentalPeriod);

    Member& getRequester() const;
    Motorbike& getMotorbike() const;
    TimePeriod getRentalPeriod() const;
};

#endif
