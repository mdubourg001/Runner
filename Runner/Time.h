#ifndef TIME_H
#define TIME_H
#include <ctime>
#include <iostream>


class Time
{
private:
    time_t _t;
    struct tm* _now;

    int _hour;
    int _min;
    int _sec;

public:
    Time();
    Time(int h, int m, int s);

    Time &operator-(const Time &other);
    bool operator!=(const Time &other);
    bool operator==(const Time &other);
    bool operator>=(const Time &other);
    bool operator<=(const Time &other);

    void refresh();
    void setSec(int s);
    void setMin(int m);
    void setHour(int h);
    int getHour() const;
    int getMin() const;
    int getSec() const;
    std::string toString();
};

#endif // TIME_H
