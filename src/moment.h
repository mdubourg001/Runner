#ifndef MOMENT_H
#define MOMENT_H

#include <iostream>
#include <chrono>

using namespace std;

class Moment
{
protected:
    unsigned int _hours;
    unsigned int _min;
    unsigned int _sec;
    unsigned int _milliseconds;
    unsigned int _microseconds;

public:
    Moment();
    Moment(int hours, int min, int sec, int milli, int micro);
    Moment(const Moment& t);

    unsigned int get_hours() const;
    unsigned int get_min() const;
    unsigned int get_sec() const;
    unsigned int get_milliseconds() const;
    unsigned int get_microseconds() const;

    double to_hours();
    double to_min();
    double to_sec();
    double to_milliseconds();
    double to_microseconds();

    Moment operator+ (const Moment& t);
    Moment operator- (const Moment& t);

    string  toString() const;
};

#endif // MOMENT_H
