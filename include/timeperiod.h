#ifndef TIMEPERIOD_H
#define TIMEPERIOD_H

#include "../include/datetime.h" // Include the DateTime class

class TimePeriod {
private:
    DateTime startDate;
    DateTime endDate;

public:
    TimePeriod(const DateTime& start, const DateTime& end);
    TimePeriod();

    // Getter functions for start and end dates
    DateTime getStartDate() const;
    DateTime getEndDate() const;

    // Function to check if a given DateTime is within the time period
    bool contains(const TimePeriod& other) const;

    // Function to check if two time periods overlap
    bool overlapsWith(const TimePeriod& other) const;
    std::vector<TimePeriod> splitIfOverlaps(const TimePeriod& rentingPeriod) const;
    std::vector<TimePeriod> splitTimePeriodsContainingRentingPeriod(
        const std::vector<TimePeriod>& currentPeriods,
        const TimePeriod& rentingPeriod
    ) const;
    int getNumberOfDays() const;

};

#endif
