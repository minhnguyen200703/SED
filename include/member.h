#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <vector>
#include "Motorbike.h"
#include "RentalRequest.h"
#include "Review.h"
#include "Account.h"


class Member : public Account {
public:
    // Constructors
    Member(std::string id, std::string username, std::string password, std::string fullName, std::string phoneNumber, std::string idType,
        std::string idNumber, std::string driverLicenseNumber, std::string expiryDate);

    Member(std::string id, std::string usernameReg, std::string password, std::string salt, std::string fullName, std::string phoneNumber, std::string idType,
        std::string idNumber, std::string driverLicenseNumber, std::string expiryDate, int creditPoints);

    // Member registration
    void registerMember();

    // List a motorbike for rent
    void listMotorbike();

    // Unlist a motorbike
    void unlistMotorbike();

    // Request to rent a motorbike
    void requestToRentMotorbike(Motorbike motorbike, TimePeriod period);

    // View rental requests
    void viewRequests();

    // Rate a rented motorbike
    void rateMotorbike(Motorbike motorbike, Review review);

    // Rate a renter (another member)
    void rateRenter(Member renter, Review review);

    // Top up credit points
    void topUpCreditPoints(int amount);

    // View member information
    void viewMemberInfo();

    // Getter functions
    std::string getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getSalt() const;
    std::string getFullName() const;
    std::string getPhoneNumber() const;
    std::string getIdType() const;
    std::string getIdNumber() const;
    std::string getDriverLicenseNumber() const;
    std::string getExpiryDate() const;
    Motorbike getMotorbikes() const;
    int getCreditPoints() const;
    double getRatingScores() const;
    std::vector<RentalRequest> getRentalRequests() const;

    // Setter functions
    void setId(const std::string& newId);
    void setUsername(const std::string& newUsername);
    void setPassword(const std::string& newPassword);
    void setSalt(const std::string& newSalt);
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

    // Function to write member data to a database file
    void writeToDatabase(const Member& account, const std::string& filename);

    // Get the role (type) of the member
    std::string getRole();

private:
    std::string id;
    std::string fullName;
    std::string phoneNumber;
    std::string idType;
    std::string idNumber;
    std::string driverLicenseNumber;
    std::string expiryDate;
    
    int creditPoints;
    double ratingScores;

    Motorbike motorbikes;
    std::vector<RentalRequest> rentalRequests;

};

#endif // MEMBER_H
