#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include "Motorbike.h"
#include "RentalRequest.h"
#include "Review.h"
#include "Account.h"


class Member : public Account {
private:
    std::string fullName;
    std::string phoneNumber;
    std::string idType;  // Citizen ID or Passport
    std::string idNumber;
    std::string driverLicenseNumber;
    std::string expiryDate;
    int creditPoints;

    std::vector<Motorbike> motorbikes;
    std::vector<RentalRequest> rentalRequests;
    std::vector<Review> reviews;

public:
    
    Member(std::string id, std::string username, std::string fullName, std::string phoneNumber, std::string idType,
       std::string idNumber, std::string driverLicenseNumber, std::string expiryDate); // for using
    Member(std::string id, std::string username, std::string password, std::string salt, std::string fullName, std::string phoneNumber, std::string idType,
       std::string idNumber, std::string driverLicenseNumber, std::string expiryDate); // for registering


    void registerMember();
    void listMotorbike(Motorbike motorbike);
    void unlistMotorbike(Motorbike motorbike);
    void requestToRentMotorbike(Motorbike motorbike, TimePeriod period);
    void viewRequests();
    void rateMotorbike(Motorbike motorbike, Review review);
    void rateRenter(Member renter, Review review);
    void topUpCreditPoints(int amount);
    void viewMemberInfo();
    std::string getRole() override;

};

#endif
