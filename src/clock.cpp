#include "clock.h"

Clock::Clock()
    :_timelapse {0}
    , _limit {0}
    ,_running {false}
    , _has_ticked {false}
{

}


/*!
 * \brief Clock::get_time
 * \return la valeur courante de la clock (_check - _start)
 */
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

/*!
 * \brief Clock::start
 * start la clock
 */
void Clock::start()
{
    _start = chrono::system_clock::now();
    _running = true;
}

/*!
 * \brief Clock::stop
 * stop la clock
 */
void Clock::stop()
{
    _running = false;
}

/*!
 * \brief Clock::reset
 * _start = _check mais ne stoppe pas la clock
 */
void Clock::reset()
{
    _start = _check;
    _timelapse = 0;
    _has_ticked = false;
}

/*!
 * \brief Clock::set_alarm
 * \param m
 * la clock tickera dans m milliseconds
 */
void Clock::set_alarm(Moment m)
{
    _limit = m.to_microseconds();
}

/*!
 * \brief Clock::update
 * met a jour la valeur de _check et le temps depuis le start du timer
 */
void Clock::update()
{
    if(is_running())
    {
        _check = chrono::system_clock::now();
        _timelapse = chrono::duration_cast<chrono::microseconds>
                (_check - _start).count();
    }
}

/*!
 * \brief Clock::check_time
 * check si la clock a attends sa limite
 */
void Clock::check_time()
{
    if(_timelapse >= _limit)
        _has_ticked = true;
}

