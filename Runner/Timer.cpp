#include "Timer.h"


//====================================
//===========Constructors=============
//====================================

Timer::Timer() //par défaut
{
    _t = time(0);
    _now = localtime(&_t);
    _running = false;

    _begin.setHour(_now->tm_hour);
    _begin.setMin(_now->tm_min);
    _begin.setSec(_now->tm_sec);
}

Timer::Timer(int h, int m, int s) //paramétré
{
    _t = time(0);
    _now = localtime(&_t);
    _running = false; 

    m %= 60;
    m += s/60;
    h = h + (m/60);
    s %= 60;

    _limit.setSec(s);
    _limit.setMin(m);
    _limit.setHour(h);
}

//====================================
//===========Operators================
//====================================

Timer &Timer::operator=(const Timer &other)
{
    Timer tmp;
    tmp._begin = other._begin;
    tmp._end = other._end;
    tmp._value = other._value;
    tmp._limit = other._limit;
    tmp._running = false;
    return tmp;
}

//====================================
//===========Autres méthodes==========
//====================================

void Timer::start()
{
    _running = true;
    _begin.refresh();
}

void Timer::stop()
{
    _running = false;
    _end.refresh();
    _stopTable.push_back(_end);
}

void Timer::resume()
{
    if(!_running)
    {
        _running = true;
    }

    else
        std::cout << "Timer is already running!" << std::endl;
}

void Timer::reinitialise()
{
    Time null;
    this->_begin = null;
    this->_end = null;
    this->_limit = null;
    this->_value = null;
    this->_running = false;
    _stopTable.clear();
}

void Timer::setLimitAndRun(int h, int m, int s)
{
    m %= 60;
    m += s/60;
    h = h + (m/60);
    s %= 60;

    _limit.setSec(s);
    _limit.setMin(m);
    _limit.setHour(h);

    start();
}

void Timer::check()
{
    if(getValue() >= _limit)
    {
        stop();
        std::cout << "Fini!" << std::endl;
    }
}


bool Timer::isRunning() const
{
    if(_running)
        return true;
    return false;
}

Time Timer::getValue()
{
    _end.refresh();
    _value = _end - _begin;
    return _value;
}

Time Timer::getBegin() const
{
    return _begin;
}

Time Timer::getEnd() const
{
    return _end;
}

Time Timer::getLimit() const
{
    return _limit;
}

std::vector<Time> Timer::getTable() const
{
        return _stopTable;
}




