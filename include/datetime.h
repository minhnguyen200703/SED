#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>

class DateTime {
private:
    int year;
    int month;
    int day;
 

public:
    DateTime(int year, int month, int day);
    DateTime();

    // Getter functions for individual date and time components
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    // Function to format the DateTime as a string
    std::string toString() const;

    // Overloaded comparison operators for DateTime objects
    bool operator==(const DateTime& other) const;
    bool operator!=(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;
    bool operator>(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;

    bool parseDateTime(const std::string& dateTimeStr);
    DateTime addOneDay();
    DateTime subtractOneDay();
};

#endif
