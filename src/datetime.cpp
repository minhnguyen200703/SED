#include "../include/datetime.h"
#include <iomanip>
#include <sstream>

// Constructor
DateTime::DateTime(int year, int month, int day)
    : year(year), month(month), day(day) {}

DateTime::DateTime() {};

// Getter functions for individual date and time components
int DateTime::getYear() const {
    return year;
}

int DateTime::getMonth() const {
    return month;
}

int DateTime::getDay() const {
    return day;
}


// Function to format the DateTime as a string
std::string DateTime::toString() const {
    std::ostringstream oss;
    oss << std::setfill('0');
    oss << std::setw(4) << year << '-' << std::setw(2) << month << '-' << std::setw(2) << day;
    return oss.str();
}

// Overloaded comparison operators for DateTime objects
bool DateTime::operator==(const DateTime& other) const {
    return (year == other.year && month == other.month && day == other.day );
}

bool DateTime::operator!=(const DateTime& other) const {
    return !(*this == other);
}

bool DateTime::operator<(const DateTime& other) const {
    if (year < other.year) {
        return true;
    } else if (year == other.year) {
        if (month < other.month) {
            return true;
        } else if (month == other.month) {
            if (day < other.day) {
                return true;
            } else if (day == other.day) {
                
            }
        }
    }

    // If none of the conditions above are met, return false
    return false;
}


bool DateTime::operator<=(const DateTime& other) const {
    return (*this < other) || (*this == other);
}

bool DateTime::operator>(const DateTime& other) const {
    return !(*this <= other);
}

bool DateTime::operator>=(const DateTime& other) const {
    return !(*this < other);
}

// Static function to parse a date string in "YYYY-MM-DD" format and create a DateTime object
bool DateTime::parseDateTime(const std::string& dateTimeStr) {
    int year, month, day;
    char delimiter;

    std::istringstream iss(dateTimeStr);
    iss >> year >> delimiter >> month >> delimiter >> day;

    // You may want to add error handling here to check if parsing was successful.

    // If parsing was successful, update the DateTime object's date components.
    if (!iss.fail()) {
        this->year = year;
        this->month = month;
        this->day = day;
        return true;
    } else {
        return false;
    }
}


// Function to add one day to the DateTime object
DateTime DateTime::addOneDay() {
    // Check if it's the last day of the year
    if (month == 12 && day == 31) {
        year++;
        month = 1;
        day = 1;
    }
    // Check if it's the last day of the month
    else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10) && day == 31) {
        month++;
        day = 1;
    }
    else if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 30) {
        month++;
        day = 1;
    }
    // Check if it's the last day of February (considering leap years)
    else if (month == 2) {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            // Leap year
            if (day == 29) {
                month++;
                day = 1;
            } else {
                day++;
            }
        } else {
            // Not a leap year
            if (day == 28) {
                month++;
                day = 1;
            } else {
                day++;
            }
        }
    }
    // Any other day
    else {
        day++;
    }
    return DateTime(year, month, day);
}

// Function to subtract one day from the DateTime object
DateTime DateTime::subtractOneDay() {
    // Check if it's the first day of the year
    if (month == 1 && day == 1) {
        year--;
        month = 12;
        day = 31;
    }
    // Check if it's the first day of the month
    else if (day == 1) {
        // Check if it's March (considering leap years)
        if (month == 3) {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                // Leap year
                day = 29;
            } else {
                // Not a leap year
                day = 28;
            }
        }
        // Check if it's the first day of any other month
        else if (month == 1 || month == 2 || month == 4 || month == 6 || month == 8 || month == 9 || month == 11) {
            month--;
            day = 31;
        } else {
            month--;
            day = 30;
        }
    }
    // Any other day
    else {
        day--;
    }
    return DateTime(year, month, day);
}

