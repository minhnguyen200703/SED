#ifndef MOTORBIKE_H
#define MOTORBIKE_H

#include <string>
#include "TimePeriod.h"

class Member; // Forward declaration of the Member class

class Motorbike {
private:
    std::string model;
    std::string color;
    double engineSize;
    std::string transmissionMode;
    int yearMade;
    std::string description;
    bool availability;
    TimePeriod rentalPeriod; // Added rental period attribute
    int minimumRenterRating;
    int consumingPoint;
    double ratingScores;

    std::vector<Review> reviews;


    Member* owner; // Pointer to the owner of the motorbike

public:
    // Constructor for creating a Motorbike instance
    Motorbike(std::string model, std::string color, double engineSize, std::string transmissionMode,
              int yearMade, std::string description, int minimumRenterRating, int consumingPoint);
    Motorbike();
    // Rent the motorbike to a member for a specified time period
    void rentMotorbike(Member& renter, TimePeriod period);

    // View details of the motorbike
    void viewMotorbikeDetails() const;

    // Check if the motorbike is available for rent
    bool isAvailable() const;

    // Set the availability status of the motorbike
    void setAvailability(bool available);

    // Check if the specified rental period is valid
    bool periodIsValid(const TimePeriod& period) const;

    // Set the rental details for the motorbike
    void setRentalDetails(const TimePeriod& period);

    // Set the owner of the motorbike
    void setOwner(Member* newOwner);
    void setTimePeriod();
};

#endif
