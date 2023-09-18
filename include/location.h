#ifndef LOCATION_H
#define LOCATION_H

#include <string>

class Location {
private:
    std::string city;

public:
    Location(std::string city);

    std::string getCity() const;
    void setCity(std::string city);
};

#endif
