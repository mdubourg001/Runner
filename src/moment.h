#ifndef MOMENT_H
#define MOMENT_H

#include <iostream>
#include <chrono>

using namespace std;

class Moment
{
protected:
    int _hours;
    int _min;
    int _sec;
    int _milliseconds;
    int _microseconds;

public:
    Moment();
    Moment(int hours, int min, int sec, int milli, int micro);
    Moment(const Moment& t);

    int get_hours() const;
    int get_min() const;
    int get_sec() const;
    int get_milliseconds() const;
    int get_microseconds() const;

    double to_hours();
    double to_min();
    double to_sec();
    double to_milliseconds();
    double to_microseconds();

    string  toString() const;

    Moment operator+ (const Moment& t);
    Moment operator- (const Moment& t);
};

#endif // MOMENT_H
