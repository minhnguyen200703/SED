// Motorbike.cpp
#include "Motorbike.h"
#include "Member.h" // Include the Member header to access member-related functionality

Motorbike::Motorbike(std::string model, std::string color, double engineSize, std::string transmissionMode,
                     int yearMade, std::string description, int minimumRenterRating, int consumingPoint)
    : model(model), color(color), engineSize(engineSize), transmissionMode(transmissionMode),
      yearMade(yearMade), description(description), availability(true), consumingPoint(consumingPoint), 
      rentalPeriod(0, 0), // Provide default TimePeriod values
      minimumRenterRating(minimumRenterRating), owner(nullptr) {
    // Initialize other Motorbike attributes or perform necessary setup
}

Motorbike::Motorbike() : model(""), color(""), engineSize(0.0), transmissionMode(""),
    yearMade(0), description(""), availability(true), consumingPoint(0),
    rentalPeriod(0, 0), minimumRenterRating(0), owner(nullptr) {
    // Initialize other Motorbike attributes or perform necessary setup
}



void Motorbike::rentMotorbike(Member& renter, TimePeriod period) {
    // Implement renting a motorbike
    // You may need to update availability, rental details, and owner information.
    
    // Check if the motorbike is available for the specified rental period
    if (!availability || !periodIsValid(period)) {
        // Handle unavailability or invalid rental period
        // You can return an error or take appropriate actions here.
        return;
    }

    // Update availability status and rental details
    setAvailability(false);
    setRentalDetails(period);

    // Set the renter as the owner during the rental period
    setOwner(&renter);
}

void Motorbike::viewMotorbikeDetails() const {
    // Implement viewing motorbike details
    // Display motorbike attributes such as model, color, engine size, and availability.
}

bool Motorbike::isAvailable() const {
    return availability;
}

void Motorbike::setAvailability(bool available) {
    availability = available;
}

bool Motorbike::periodIsValid(const TimePeriod& period) const {
    // Implement logic to check if the specified rental period is valid
    // You can check against your business rules and constraints.
    // Return true if the period is valid, otherwise return false.
}

void Motorbike::setRentalDetails(const TimePeriod& period) {
    // Implement setting the rental details for the motorbike
    // This can include start and end times of the rental period.
}

void Motorbike::setOwner(Member* newOwner) {
    owner = newOwner;
}

// You can add more methods or functionality to the Motorbike class as needed.
