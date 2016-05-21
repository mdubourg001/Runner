#include "clock.h"

Clock::Clock()
    :_timelapse {0}
    , _limit {0}
    ,_running {false}
    , _has_ticked {false}
{

}


Moment Clock::get_time() const
{
    int temp = _timelapse;
    int hours = temp / 3600000000;
    temp %= 3600000000;
    int min = temp / 60000000;
    temp %= 60000000;
    int sec = temp / 1000000;
    temp %= 1000000;
    int milliseconds = temp / 1000;
    temp %= 1000;
    int microseconds = temp;
    Moment m(hours, min, sec, milliseconds, microseconds);
    return m;
}

bool Clock::is_running() const
{
    return _running;
}

bool Clock::has_ticked() const
{
    return _has_ticked;
}

void Clock::start()
{
    _start = chrono::system_clock::now();
    _running = true;
}

void Clock::stop()
{
    _running = false;
}

void Clock::reset()
{
    _start = _check;
    _timelapse = 0;
    _has_ticked = false;
}

void Clock::set_alarm(Moment m)
{
    _limit = m.to_microseconds();
}

void Clock::update()
{
    if(is_running())
    {
        _check = chrono::system_clock::now();
        _timelapse = chrono::duration_cast<chrono::microseconds>
                (_check - _start).count();
    }
}

void Clock::check_time()
{
    if(_timelapse >= _limit)
        _has_ticked = true;
}

