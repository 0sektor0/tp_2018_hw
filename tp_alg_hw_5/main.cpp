#include <iostream>
#include <assert.h>
#include <string.h>
using namespace std;

#define YEAR 360
#define MONTH 30




template <class T>
void Merge(T* arr, int size, int middle, bool (*Compare)(const T&, const T&))
{
    assert(arr && size > 0);

    int ptr_r = middle;
    int ptr_l = 0;

    T* buff = new T[size];
    int ptr_b = 0;

    while(ptr_l < middle && ptr_r < size)
    {
        if(Compare(arr[ptr_l], arr[ptr_r]))
        {
            buff[ptr_b] = arr[ptr_l];
            ptr_l++;
        }
        else
        {
            buff[ptr_b] = arr[ptr_r];
            ptr_r++;
        }

        ptr_b++;
    }

    while(ptr_l < middle)
    {
        buff[ptr_b] = arr[ptr_l];
        ptr_l++;
        ptr_b++;
    }

    while(ptr_r < size)
    {
        buff[ptr_b] = arr[ptr_r];
        ptr_r++;
        ptr_b++;
    }

    memcpy(arr, buff, size * sizeof(T));
    delete [] buff;
}


template <class T>
void MergeSort(T* arr, int size, bool (*Compare)(const T&, const T&))
{
    assert(arr && size);
    int ms = 2; //merge window size

    if(size == 1)
        return;

    for(ms = 2; ms <= size; ms*=2)
        for(int offset= 0; offset+ms <= size; offset+=ms)
            Merge(&arr[offset], ms, ms/2, Compare);

    ms /= 2;

    //add lonely element to array
    if(size & 1)
    {
        if(size == 3)
        {
            Merge(arr, 3, 2, Compare);
        }
        else
            MergeSort(&arr[ms], size - ms, Compare);

        Merge(arr, size, ms, Compare);
        return;
    }

    //Merge all
    if(!(size && !(size & (size - 1))))
    {
        MergeSort(&arr[ms], size - ms, Compare);
        Merge(arr, size, ms, Compare);
    }
}


bool Comparei(const int& x1, const int& x2)
{
    return x1 < x2;
}




class LifePoint
{
public:
    void SetDate(int day, int month, int year);
    static bool Compare(const LifePoint& x, const LifePoint& y);
    static long CalcAgeDiff(const LifePoint& x, const LifePoint& y);
    void AddYears(int years);
    void AddDays(int days);
    LifePoint();
    ~LifePoint();

    bool birthday;
    long date;
};


LifePoint::LifePoint() : date(0), birthday(0)
{}


void LifePoint::SetDate(int day, int month, int year)
{
    date = 0;
    date += day;
    date += month * MONTH;
    date += year * YEAR;
}


void LifePoint::AddYears(int years)
{
    date += years * YEAR;
}


void LifePoint::AddDays(int days)
{
    date += days;
}


bool LifePoint::Compare(const LifePoint& x, const LifePoint& y)
{
    if(x.date == y.date && x.birthday != y.birthday)
    {
        return !x.birthday;
    }
    else
        return x.date < y.date;
}


long LifePoint::CalcAgeDiff(const LifePoint& x, const LifePoint& y)
{
    return x.date - y.date;
}


LifePoint::~LifePoint()
{}




void ReadDate(LifePoint* date, bool bd)
{
    int day;
    int mon;
    int year;

    cin >> day;
    cin >> mon;
    cin >> year;

    date->SetDate(day, mon, year);
    date->birthday = bd;
}


LifePoint* ReadInput(int& size)
{
    int counter = 0;
    cin >> counter;

    LifePoint* arr = new LifePoint[counter * 2];

    for(int i = 0; i < counter; i++)
    {
        ReadDate(&arr[size], true);
        ReadDate(&arr[size+1], false);

        int age = LifePoint::CalcAgeDiff(arr[size+1], arr[size]);

        //6480
        if(age < 18 * YEAR)
            continue;

        //28800
        if(age > 80 * YEAR)
        {
            arr[size+1].date = arr[size].date;
            arr[size+1].AddYears(80);
        }

        arr[size].AddYears(18);
        size += 2;
    }

    return arr;
}


int MaxContemporaryCount(LifePoint* arr, const int& size)
{
    int contemporary = 0;
    int contemporary_max = 0;

    for(int i = 0; i < size; i++)
    {
        if(arr[i].birthday)
            contemporary++;
        else
        {
            if(contemporary > contemporary_max)
                contemporary_max = contemporary;

            contemporary--;
        }
    }

    return contemporary_max;
}




int main()
{
    LifePoint* arr = NULL;
    int size = 0;

    arr = ReadInput(size);

    if(size > 0)
    {
        MergeSort(arr, size, LifePoint::Compare);
        cout << MaxContemporaryCount(arr, size);
    }
    else
        cout << 0;

    delete [] arr;
    return 0;
}






























