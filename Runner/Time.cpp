#include "Time.h"

//====================================
//===========Constructors=============
//====================================

Time::Time()
{
    _t = time(0);
    _now = localtime(&_t);

    _hour = _now->tm_hour;
    _min = _now->tm_min;
    _sec = _now->tm_sec;
}

Time::Time(int h, int m, int s)
    : _hour {h}, _min {m}, _sec {s}
{
    _t = time(0);
    _now = localtime(&_t);
}

//===================================

//====================================
//===========Methods==================
//====================================

void Time::refresh()
{
    _hour = _now->tm_hour;
    _min = _now->tm_min;
    _sec = _now->tm_sec;
}

void Time::setHour(int h)
{ _hour = h; }

void Time::setMin(int m)
{ _min = m; }

void Time::setSec(int s)
{ _sec = s; }

int Time::getHour() const
{ return _hour; }

int Time::getMin() const
{ return _min; }

int Time::getSec() const
{ return _sec; }


std::string Time::toString()
{
    std::string str;
    str = std::to_string(_hour) + ":" + std::to_string(_min) + ":" + std::to_string(_sec);
    return str;
}

//====================================
//===========Operators================
//====================================

Time &Time::operator-(const Time &other)
{
    Time tmp;
    tmp._hour = (this->_hour - other._hour);
    tmp._min = (this->_min - other._min);
    tmp._sec = (this->_sec - other._sec);
    return tmp;
}

bool Time::operator!=(const Time &other)
{
    if(this->_hour == other._hour && this->_min == other._min && this->_sec == other._sec)
        return false;
    return true;
}

bool Time::operator==(const Time &other)
{
    if(this->_hour == other._hour && this->_min == other._min && this->_sec == other._sec)
        return true;
    return false;
}

bool Time::operator<=(const Time &other)
{
    if(this->_hour <= other._hour && this->_min <= other._min && this->_sec <= other._sec)
        return true;
    return false;
}

bool Time::operator>=(const Time &other)
{
    if(this->_hour >= other._hour && this->_min >= other._min && this->_sec >= other._sec)
        return true;
    return false;
}


