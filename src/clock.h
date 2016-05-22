#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>

#include "moment.h"

using namespace std;

class Clock
{
protected:
    chrono::time_point<chrono::system_clock> _begin, _start, _check; //begin représente le premier lancement de la clock
    double _timelapse; //temps entre _start et maintenant
    double _limit;
    bool _running;
    bool  _has_ticked;
    vector<chrono::time_point<chrono::system_clock>> _ticks;

public:
    Clock();

    Moment get_time_since_begin() const;
    Moment get_time_since_tick() const;
    vector<Moment> get_ticks() const;
    bool is_running() const;
    bool has_ticked() const;

    void start();
    void stop();
    void reset(); //n'arrete pas la clock
    void set_alarm(Moment m);
    void update();
    void check_time();

    static Moment get_time_between(chrono::time_point<chrono::system_clock> earlier
                            , chrono::time_point<chrono::system_clock> later);
    static Moment get_time_since(chrono::time_point<chrono::system_clock> time_point);
};

#endif // CLOCK_H
