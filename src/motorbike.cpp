// Motorbike.cpp
#include "../include/motorbike.h"
#include "../include/member.h" 
using namespace std;

// for creating new motorbike
Motorbike::Motorbike(std::string model, std::string color, double engineSize, std::string transmissionMode,
                     int yearMade, std::string description, Member* member)
    : model(model), color(color), engineSize(engineSize), transmissionMode(transmissionMode),
      yearMade(yearMade), description(description), availability(false), consumingPoint(), 
      availablePeriods(), minimumRenterRating(), owner(member), ratingScores() {
    
}

// for existed motorbike with availability false
    
Motorbike::Motorbike(std::string model, std::string color, double engineSize, std::string transmissionMode,
    int yearMade, std::string description, Member* member, double ratingScores)
    : model(model), color(color), engineSize(engineSize), transmissionMode(transmissionMode),
      yearMade(yearMade), description(description), availability(false), consumingPoint(), 
      availablePeriods(), minimumRenterRating(), owner(member), ratingScores(ratingScores) {
    
}

            // for existed motorbike with availability true
Motorbike::Motorbike(std::string model, std::string color, double engineSize, std::string transmissionMode,
    int yearMade, std::string description, int consumingPoint, std::vector<TimePeriod> availablePeriod, int minimumRenterRating,
    Member* member, double ratingScores)
    : model(model), color(color), engineSize(engineSize), transmissionMode(transmissionMode),
      yearMade(yearMade), description(description), availability(true), consumingPoint(consumingPoint), 
      availablePeriods(availablePeriod), minimumRenterRating(minimumRenterRating), owner(member), ratingScores(ratingScores) {
    
}
    



Motorbike::Motorbike() {
    
}


void Motorbike::viewMotorbikeDetails(int index) const {
    std::cout << "Index: " << index << std::endl;
    std::cout << "Motorbike Details:" << std::endl;
    std::cout << "Model: " << Motorbike::getModel() << std::endl;
    std::cout << "Color: " << getColor() << std::endl;
    std::cout << "Engine Size: " << getEngineSize() << " cc" << std::endl;
    std::cout << "Transmission Mode: " << getTransmissionMode() << std::endl;
    std::cout << "Year Made: " << getYearMade() << std::endl;
    std::cout << "Description: " << getDescription() << std::endl;
    std::cout << "Availability: " << (isAvailable() ? "Available" : "Not Available") << std::endl;
    std::cout << "Minimum Renter Rating: " << getMinimumRenterRating() << std::endl;
    std::cout << "Consuming Point: " << getConsumingPoint() << std::endl;
    std::cout << "Owner: " << getOwner()->getFullName() << std::endl;
    std::cout << "Rating Scores: " << getRatingScores() << std::endl;
    std::cout << "----------------------" << std::endl;
}

void Motorbike::viewMotorbikeDetailsWithReview(int index) const {
    viewMotorbikeDetails(index); // Display basic motorbike details first
    std::vector<Review> mtbReviews;
    for (const RentalRequest& request : owner->getRentalRequests()) {
           mtbReviews.push_back( request.getMotorbikeReview());
        }
    // Check if the motorbike has any reviews
    if (mtbReviews.empty()) {
        std::cout << "No reviews available for this motorbike." << std::endl;
    } else {
        std::cout << "Motorbike Reviews:" << std::endl;
        
        // Loop through and display all reviews for the motorbike
        for (const Review& review : mtbReviews) {
            std::cout << "Review Score: " << review.getScore() << std::endl;
            std::cout << "Review Comment: " << review.getComment() << std::endl;
            std::cout << "----------------------" << std::endl;
        }
    }
}

bool Motorbike::isAvailable() const {
    return availability;
}

void Motorbike::setAvailability(bool available) {
    availability = available;
}

bool Motorbike::periodIsValid(const TimePeriod& period) const {
    // Check if the specified rental period is valid based on business rules
    // For example, you can check if the period falls within any of the available periods
    for (const TimePeriod& availablePeriod : availablePeriods) {
        if (availablePeriod.contains(period)) {
            // The specified period is within an available period, so it's valid
            return true;
        }
    }
    
    // If no available period contains the specified period, it's not valid
    return false;
}

std::string Motorbike::getLocation() const {
    return owner->getCity();
}


void Motorbike::editMotorbikeRatingScore() {
    int totalScore = 0;
    int numberOfReviews = 0;

    // Loop through the rentedRentalRequests
    for (const RentalRequest& request : owner->getRentedRentalRequests()) {
        if (request.getStatus() == "Rented") {
            // Get the renterReview from each rented rental request
            Review renterReview = request.getRenterReview();
            
            // Check if a review exists for this request
            if (renterReview.getScore() > 0) {
                // Sum up the scores and count the number of reviews
                totalScore += renterReview.getScore();
                numberOfReviews++;
            }
        }
    }

    if (numberOfReviews > 0) {
        // Calculate the average score
        double averageScore = static_cast<double>(totalScore) / numberOfReviews;
        
        // Update the member's rating score
        ratingScores = averageScore;

        std::cout << "Motorbike's rating score has been updated to: " << averageScore << std::endl;
    } else {
        std::cout << "No renter reviews found to calculate the rating score." << std::endl;
    }
}

void Motorbike::setRentalDetails(const TimePeriod& period) {
    // Check if the rentalPeriods vector is empty
    if (availablePeriods.empty()) {
        availablePeriods.push_back(period); // If empty, just add the period
    } else {
        TimePeriod timePeriod;

        // Use the splitTimePeriodsContainingRentingPeriod function
        std::vector<TimePeriod> updatedPeriods = timePeriod.splitTimePeriodsContainingRentingPeriod(availablePeriods, period);

        // Replace the rentalPeriods vector with the updated vector
        availablePeriods = updatedPeriods;
    }
}

void Motorbike::removeAvailablePeriods() {
    availablePeriods.clear(); // Clear the rental periods vector to remove all periods
}



void Motorbike::setOwner(Member* newOwner) {
    owner = newOwner;
}

// Getter functions

std::string Motorbike::getModel() const {
    return model;
}

std::string Motorbike::getColor() const {
    return color;
}

double Motorbike::getEngineSize() const {
    return engineSize;
}

std::string Motorbike::getTransmissionMode() const {
    return transmissionMode;
}

int Motorbike::getYearMade() const {
    return yearMade;
}

std::string Motorbike::getDescription() const {
    return description;
}

bool Motorbike::getAvailability() const {
    return availability;
}

int Motorbike::getMinimumRenterRating() const {
    return minimumRenterRating;
}

int Motorbike::getConsumingPoint() const {
    return consumingPoint;
}

double Motorbike::getRatingScores() const {
    return ratingScores;
}

Member* Motorbike::getOwner() const {
    return owner;
}

std::vector<TimePeriod> Motorbike::getAvailablePeriods() const {
    return availablePeriods;
}

// Setter functions

void Motorbike::setModel(const std::string& newModel) {
    model = newModel;
}

void Motorbike::setColor(const std::string& newColor) {
    color = newColor;
}

void Motorbike::setEngineSize(double newSize) {
    engineSize = newSize;
}

void Motorbike::setTransmissionMode(const std::string& newMode) {
    transmissionMode = newMode;
}

void Motorbike::setYearMade(int newYear) {
    yearMade = newYear;
}

void Motorbike::setDescription(const std::string& newDescription) {
    description = newDescription;
}

void Motorbike::setMinimumRenterRating(int newRating) {
    minimumRenterRating = newRating;
}

void Motorbike::setConsumingPoint(int newConsumingPoint) {
    consumingPoint = newConsumingPoint;
}

void Motorbike::setRatingScores(double newRatingScores) {
    ratingScores = newRatingScores;
}

void Motorbike::setAvailablePeriods(std::vector<TimePeriod> newRentalPeriods) {
    availablePeriods = newRentalPeriods;
};

std::string Motorbike::getMotorbikeDetails() const {
    std::string details = "Model: " + this->Motorbike::getModel() + "\n";
    details += "Color: " + getColor() + "\n";
    details += "Engine Size: " + std::to_string(getEngineSize()) + " cc\n";
    details += "Transmission Mode: " + getTransmissionMode() + "\n";
    details += "Year Made: " + std::to_string(getYearMade()) + "\n";
    details += "Description: " + getDescription() + "\n";
    
    details += "Availability: " + (isAvailable() ? std::string("Available") : std::string("Not Available")) + "\n";
    details += "Minimum Renter Rating: " + std::to_string(getMinimumRenterRating()) + "\n";
    details += "Consuming Point: " + std::to_string(getConsumingPoint()) + "\n";
    details += "Owner: " + getOwner()->getFullName() + "\n";
    details += "Rating Scores: " + std::to_string(getRatingScores()) + "\n";

    return details;
}










