#ifndef RENTALREQUEST_H
#define RENTALREQUEST_H

#include "../include/member.h"
#include "../include/motorbike.h"
#include "../include/timeperiod.h"
#include "../include/review.h"

class Member;
class Motorbike;
class RentalRequest {
private:
    Member* requester; // Pointer to the member making the request
    Motorbike* motorbike; // Pointer to the motorbike being requested
    TimePeriod rentalPeriod;
    Review motorbikeReview;
    Review renterReview;
    std::string status;
    std::string id;

public:
    // Constructors
    RentalRequest(Member& requester, Motorbike* motorbike, const TimePeriod& rentalPeriod); // Create New
    RentalRequest(std::string id, Member requester, Motorbike* motorbike, 
                const TimePeriod rentalPeriod, Review motorbikeReview,
                Review renterReview, std::string status);
    RentalRequest();

    // Getter functions
    Member& getRequester() const;
    Motorbike& getMotorbike() const;
    TimePeriod getRentalPeriod() const;
    Review getMotorbikeReview() const;
    Review getRenterReview() const;
    std::string getStatus() const; // New getter for status
    std::string getId() const; // New getter for status

    // Setter functions
    void setMotorbikeReview(const Review& motorbikeReview);
    void setRenterReview(const Review& renterReview);
    void setStatus(const std::string& newStatus); // New setter for status
    void setId(const std::string& newId); // New setter for status

    bool hasRenterReview() const;
    void displayRequestDetails() const;
    std::string createAutoIncrementedId(std::string filename);

};

#endif
