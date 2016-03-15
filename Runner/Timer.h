#ifndef TIMER_H
#define TIMER_H
#include <ctime>
#include <iostream>
#include <vector>
#include "Time.h"



class Timer
{
private:
    time_t _t;
    struct tm* _now;

    Time _begin;
    Time _end;
    Time _value;
    Time _limit;
    std::vector<Time> _stopTable;
    bool _running;

public:
    Timer();
    Timer(int h, int m, int s);

    void start();
    void stop();
    void resume();
    void reinitialise();
    void setLimitAndRun(int h, int m, int s);
    void check();
    bool isRunning() const;
    Time getValue();
    Time getBegin() const;
    Time getEnd() const;
    Time getLimit() const;
    std::vector<Time> getTable() const;
    Timer &operator=(const Timer &other);
};

#endif // TIMER_H
