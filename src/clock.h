#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <chrono>
#include <math.h>

#include "moment.h"

using namespace std;

class Clock
{
protected:
    chrono::time_point<chrono::system_clock> _start, _check;
    double _timelapse; //temps entre _start et maintenant
    double _limit;
    bool _running;
    bool  _has_ticked;

public:
    Clock();

    Moment get_time() const;
    bool is_running() const;
    bool has_ticked() const;

    void start();
    void stop();
    void reset(); //n'arrete pas la clock
    void set_alarm(Moment m);
    void update();
    void check_time();
};

#endif // CLOCK_H
