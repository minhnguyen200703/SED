#ifndef TIMEPERIOD_H
#define TIMEPERIOD_H

class TimePeriod {
private:
    int startHour;
    int endHour;

public:
    TimePeriod(int startHour, int endHour);

    int getStartHour() const;
    int getEndHour() const;
    bool overlapsWith(const TimePeriod& other) const;
};

#endif
