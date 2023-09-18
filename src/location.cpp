// Location.cpp
#include "Location.h"

Location::Location(std::string city) : city(city) {
    // Initialize other Location attributes or perform necessary setup
}

std::string Location::getCity() const {
    return city;
}

void Location::setCity(std::string city) {
    this->city = city;
}

// You can add more methods or functionality to the Location class as needed.
