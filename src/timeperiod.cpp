#include "../include/timeperiod.h"
#include <iostream>
#include <vector>


TimePeriod::TimePeriod(const DateTime& start, const DateTime& end)
    : startDate(start), endDate(end) {}

TimePeriod::TimePeriod() {};


DateTime TimePeriod::getStartDate() const {
    return startDate;
}

DateTime TimePeriod::getEndDate() const {
    return endDate;
}

bool TimePeriod::contains(const TimePeriod& other) const {
    // Check if 'other' starts after the beginning of this time period
    bool startsAfterBegin = (other.getStartDate() >= getStartDate() && other.getStartDate() <= getEndDate());

    // Check if 'other' ends before the end of this time period
    bool endsBeforeEnd = (other.getEndDate() >= getStartDate() && other.getEndDate() <= getEndDate());

    // 'other' is contained within this time period if both conditions are true
    return startsAfterBegin && endsBeforeEnd;
}


bool TimePeriod::overlapsWith(const TimePeriod& other) const {
    // Check if two time periods overlap
    return (startDate <= other.getEndDate()) && (endDate >= other.getStartDate());
}

std::vector<TimePeriod> TimePeriod::splitIfOverlaps(const TimePeriod& rentingPeriod) const {
    std::vector<TimePeriod> splits;

    // Check if the rentingPeriod overlaps with the current TimePeriod
    if (rentingPeriod.getEndDate() < startDate || rentingPeriod.getStartDate() > endDate) {
        // No overlap, return the current TimePeriod
        splits.push_back(*this);
    } else if (rentingPeriod.getStartDate() <= startDate && rentingPeriod.getEndDate() >= endDate) {
        // RentingPeriod completely covers the current TimePeriod, return an empty vector
    } else if (rentingPeriod.getStartDate() == startDate) {
        // RentingPeriod starts at the same time as the current TimePeriod
        splits.push_back(TimePeriod(rentingPeriod.getEndDate().addOneDay(), endDate));
    } else if (rentingPeriod.getEndDate() == endDate) {
        // RentingPeriod ends at the same time as the current TimePeriod
        splits.push_back(TimePeriod(startDate, rentingPeriod.getStartDate().subtractOneDay()));
    } else {
        // Overlap, split into two TimePeriods
        splits.push_back(TimePeriod(startDate, rentingPeriod.getStartDate().subtractOneDay()));
        splits.push_back(TimePeriod(rentingPeriod.getEndDate().addOneDay(), endDate));
    }

    return splits;
}


std::vector<TimePeriod> TimePeriod::splitTimePeriodsContainingRentingPeriod(
    const std::vector<TimePeriod>& currentPeriods,
    const TimePeriod& rentingPeriod
) const {
    std::vector<TimePeriod> result;

    for (const TimePeriod& current : currentPeriods) {
        // Check if the current time period contains the renting period
        if (current.contains(rentingPeriod)) {
            // Split the current time period based on the renting period
            std::vector<TimePeriod> splits = current.splitIfOverlaps(rentingPeriod);

            // Add the splits to the result
            result.insert(result.end(), splits.begin(), splits.end());
        } else {
            // No overlap, add the current time period as is
            result.push_back(current);
        }
    }

    return result;
}

int TimePeriod::getNumberOfDays() const {
    // Calculate the number of days between the start and end dates

    // If the start date is the same as the end date, return 1 day
    if (startDate == endDate) {
        return 1;
    }

    // Calculate the number of days between start and end dates
    int days = 0;

    // Initialize a temporary DateTime object to the start date
    DateTime currentDate = startDate;

    // Keep adding one day at a time until we reach the end date
    while (currentDate != endDate) {
        // Increment the day and update currentDate
        currentDate = currentDate.addOneDay();

        // Increment the count of days
        days++;
    }

    // Add 1 to include the end date in the count
    days++;

    return days;
}


