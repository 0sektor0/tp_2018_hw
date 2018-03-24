#include "lifepoint.h"


LifePoint::LifePoint() : _date(0), _birthday(0)
{}


/*void LifePoint::SetDate(int& day, int& month, int& year, bool& birthday)
{
    _date = 0;
    _date += day;
    _date += month * 30;
    _date += year * 30 * 365;
    _birthday = birthday;
}*/


void LifePoint::SetDate(int day, int month, int year, bool birthday)
{
    _date = 0;
    _date += day;
    _date += month * 30;
    _date += year * 30 * 365;
    _birthday = birthday;
}


void LifePoint::AddYears(int years)
{
    _date += years * 30 * 365;
}


bool LifePoint::Compare(LifePoint& x, LifePoint& y)
{
    return x.Date() < y.Date();
}


long& LifePoint::Date()
{
    return _date;
}


bool& LifePoint::Birthday()
{
    return _birthday;
}


LifePoint::~LifePoint()
{}
