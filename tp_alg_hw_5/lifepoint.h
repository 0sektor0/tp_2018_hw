#ifndef LIFEPOINT_H
#define LIFEPOINT_H


class LifePoint
{
public:
    //void SetDate(int& day, int& month, int& year, bool& birthday);
    void SetDate(int day, int month, int year, bool birthday);
    static bool Compare(LifePoint& x, LifePoint& y);
    void AddYears(int years);
    bool& Birthday();
    long& Date();
    LifePoint();
    ~LifePoint();


private:
    long _date;
    bool _birthday;
};


#endif // LIFEPOINT_H
