#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include "../include/rentalrequest.h"
#include "../include/review.h"
#include "../include/account.h"
#include "../include/method.h"

class Method;
class Motorbike;
class RentalRequest;
class TimePeriod;
class Member : public Account {
public:
    // Constructors
    Member(std::string id, std::string username, std::string password, std::string fullName, std::string phoneNumber, std::string idType,
        std::string idNumber, std::string driverLicenseNumber, std::string expiryDate);

    Member(std::string id, std::string usernameReg, std::string password, std::string salt, std::string fullName, std::string phoneNumber, std::string idType,
        std::string idNumber, std::string driverLicenseNumber, std::string expiryDate, std::string city, int creditPoints, double ratingScores);

    Member ();
    

    // List a motorbike for rent
    void listMotorbike();

    // Unlist a motorbike
    void unlistMotorbike();

    // Request to rent a motorbike
    bool requestToRentMotorbike(Motorbike& motorbike, TimePeriod period);

    // View rental requests
    void viewRequests(std::string type);

    // View requests on status
    void viewRentalRequests(const std::string& type, const std::string& status);

    // Rate a rented motorbike
    void rateMotorbike(Motorbike motorbike, RentalRequest motorbikeRequest);

    // Rate a renter (another member)
    void rateRenter(Member renter, RentalRequest renterRequest);

    // Top up credit points
    void topUpCreditPoints();

    // View member information
    void viewMemberInfo();

    // Add Motorbike information
    void addMotorbike();

    // 
    void receiveRentalRequest(const RentalRequest& request);

    // 
    void editRatingScore();

    void viewUnscoredRequests(bool showRentedRequests);

    // Getter functions
    std::string getId() const;
    std::string getFullName() const;
    std::string getPhoneNumber() const;
    std::string getIdType() const;
    std::string getIdNumber() const;
    std::string getDriverLicenseNumber() const;
    std::string getExpiryDate() const;
    Motorbike* getMotorbikes() const;
    int getCreditPoints() const;
    double getRatingScores() const;
    std::vector<RentalRequest> getRentalRequests() const;
    std::vector<RentalRequest> getRentedRentalRequests() const;

    // Setter functions
    void setId(const std::string& newId);
    void setFullName(const std::string& newFullName);
    void setPhoneNumber(const std::string& newPhoneNumber);
    void setIdType(const std::string& newIdType);
    void setIdNumber(const std::string& newIdNumber);
    void setDriverLicenseNumber(const std::string& newDriverLicenseNumber);
    void setExpiryDate(const std::string& newExpiryDate);
    void setCreditPoints(int newCreditPoints);
    void setMotorbikes(Motorbike motorbike);
    void setRatingScores(double ratingScores);
    void setRentalRequests(const std::vector<RentalRequest>& newRentalRequests);
    void addRentalRequest(const RentalRequest& request);
    void setRentedRentalRequests(const std::vector<RentalRequest>& newRentedRentalRequests);
    void addRentedRentalRequest(const RentalRequest& rentedRentalRequests);
    void editMemberRatingScore();
    void acceptRequest(RentalRequest request);
    void RentRequestedMotorbike();
    void RateRenter();
    void addCreditPoints();
   // Get the role (type) of the member
    std::string getCity() const;
    void setCity(std::string city);

private:
    std::string id;
    std::string fullName;
    std::string phoneNumber;
    std::string idType;
    std::string idNumber;
    std::string driverLicenseNumber;
    std::string expiryDate;
    std::string city;
    
    int creditPoints;
    double ratingScores;

    Motorbike* motorbikes;
    std::vector<RentalRequest> rentalRequests; // chua incoming request, ngta thue cua minh, nguoi ta danh gia xe, minh la motorbike owner
    std::vector<RentalRequest> rentedRentalRequests; // chua request cua minh`, request history, minh thue cua ngta, ngta danh gia minh, minh la renter

};

#endif // MEMBER_H
