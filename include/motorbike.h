#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include <string>
#include "TimePeriod.h"
#include "Member.h" // Include the Member class header

class Motorbike {
private:
    std::string model;
    std::string color;
    double engineSize;
    std::string transmissionMode;
    int yearMade;
    std::string description;
    bool availability;
    std::vector<TimePeriod> availablePeriods; // Added rental period attribute
    int minimumRenterRating;
    int consumingPoint;
    double ratingScores;


    Member* owner; // Pointer to the owner of the motorbike

public:
    // Constructor for creating a Motorbike instance
    Motorbike(std::string model, std::string color, double engineSize, std::string transmissionMode,
              int yearMade, std::string description, int consumingPoint, Member* member);
    Motorbike();

    // Rent the motorbike to a member for a specified time period
    void rentMotorbike(Member& renter, TimePeriod period);

    // View details of the motorbike
    void viewMotorbikeDetails(int index) const;

    // View details of the motorbike with reviews
    void viewMotorbikeDetailsWithReview(int index) const;

    // Check if the motorbike is available for rent
    bool isAvailable() const;

    // Set the availability status of the motorbike
    void setAvailability(bool available);

    // Check if the specified rental period is valid
    bool periodIsValid(const TimePeriod& period) const;

    // Set the rental details for the motorbike
    void setRentalDetails(const TimePeriod& period);


    void removeAvailablePeriods();

    void editMotorbikeRatingScore(std::vector<RentalRequest> rentalRequests);

    std::string getLocation() const;
    
    // Getter functions
    std::string getModel() const;
    std::string getColor() const;
    double getEngineSize() const;
    std::string getTransmissionMode() const;
    int getYearMade() const;
    std::string getDescription() const;
    bool getAvailability() const;
    int getMinimumRenterRating() const;
    int getConsumingPoint() const;
    double getRatingScores() const;
    Member* getOwner() const;
    std::vector<TimePeriod> getAvailablePeriods() const;

    // Setter functions
    void setModel(const std::string& newModel);
    void setColor(const std::string& newColor);
    void setEngineSize(double newSize);
    void setTransmissionMode(const std::string& newMode);
    void setYearMade(int newYear);
    void setDescription(const std::string& newDescription);
    void setMinimumRenterRating(int newRating);
    void setConsumingPoint(int newConsumingPoint);
    void setRatingScores(double newRatingScores);
    void setOwner(Member* newOwner);
    void setAvailablePeriods(std::vector<TimePeriod> rentalPeriods);
};

#endif
