#include "TimePeriod.h"

TimePeriod::TimePeriod(int startHour, int endHour)
    : startHour(startHour), endHour(endHour) {
    // Initialize other TimePeriod attributes or perform necessary setup
}

int TimePeriod::getStartHour() const {
    return startHour;
}

int TimePeriod::getEndHour() const {
    return endHour;
}

bool TimePeriod::overlapsWith(const TimePeriod& other) const {
    // Check if this time period overlaps with the provided 'other' time period
    // Return true if there is an overlap, otherwise return false.
    return (startHour < other.getEndHour() && endHour > other.getStartHour());
}
