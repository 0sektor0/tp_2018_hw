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
        Merge(&arr[ms], size - ms, size-ms-1, Compare);

    //Merge all
    if(!(size && !(size & (size - 1))))
        Merge(arr, size, ms, Compare);
}




class LifePoint
{
public:
    static bool Compare(const LifePoint& x, const LifePoint& y);
    void SetDate(int day, int month, int year, bool bd);
    void SetDate(int day, int month, int year);
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


void LifePoint::SetDate(int day, int month, int year, bool bd)
{
    SetDate(day, month, year);
    birthday = bd;
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


LifePoint::~LifePoint()
{}




void PrintArr(const LifePoint* arr, const int& size)
{
    for (int i = 0; i < size; i++)
        cout << arr[i].date << " ";
    cout << endl;
}


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


long CalcAgeDiff(const LifePoint& x, const LifePoint& y)
{
    return x.date - y.date;
}


bool NormalizeAge(LifePoint& birth_point, LifePoint& death_point)
{
    int age = CalcAgeDiff(death_point, birth_point);

    //6480
    if(age < 18 * YEAR)
        return false;

    //28800
    if(age > 80 * YEAR)
    {
        death_point.date = birth_point.date;
        death_point.AddYears(80);
    }

    birth_point.AddYears(18);
    return true;
}


LifePoint* ReadInput(int& size)
{
    int counter = 0;
    size = 0;
    cin >> counter;

    LifePoint* arr = new LifePoint[counter * 2];

    for(int i = 0; i < counter; i++)
    {
        ReadDate(&arr[size], true);
        ReadDate(&arr[size+1], false);
        size += 2;
    }

    return arr;
}


LifePoint* Filter(const LifePoint* arr, const int& size, int& filtered_size)
{
    LifePoint* filtered_arr = new LifePoint[size];
    filtered_size = 0;

    for(int i = 0; i < size; i+=2)
    {
        filtered_arr[filtered_size] = LifePoint(arr[i]);
        filtered_arr[filtered_size+1] = LifePoint(arr[i+1]);

        if(NormalizeAge(filtered_arr[i], filtered_arr[i+1]))
            filtered_size += 2;
    }

    return filtered_arr;
}


int FindMaxContemporaryCount(LifePoint* arr, const int& size)
{
    int contemporary = 0;
    int contemporary_max = 0;

    if(size > 0)
    {
        //PrintArr(arr, size);
        MergeSort(arr, size, LifePoint::Compare);
        //PrintArr(arr, size);

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
    }

    return contemporary_max;
}




void Tests()
{
    LifePoint* arr = NULL;
    LifePoint* filtered_arr = NULL;
    int size = 0;
    int result;
    int correct_res;
    int filtered_size = 0;
    int tests_passed = 1;

    //умерли в день 18ти летия 2го
    size = 4;
    correct_res = 1;
    arr = new LifePoint[size];
    arr[0].SetDate(11, 12, 1900, true);
    arr[1].SetDate(1, 1, 2000, false);
    arr[2].SetDate(11, 12, 1962, true);
    arr[3].SetDate(11, 12, 1980, false);

    filtered_arr = Filter(arr, size, filtered_size);
    result = FindMaxContemporaryCount(filtered_arr, filtered_size);
    delete [] arr;
    delete [] filtered_arr;

    if(result == correct_res)
        tests_passed++;
    else
    {
        cout << "test: " << tests_passed<< " failed\n" << "expected: "<<correct_res<<"\ngot:" <<  result << endl;
        return;
    }

    //1 пересечение
    size = 4;
    correct_res = 2;
    arr = new LifePoint[size];
    arr[0].SetDate(11, 12, 1900, true);
    arr[1].SetDate(1, 1, 2000, false);
    arr[2].SetDate(10, 12, 1962, true);
    arr[3].SetDate(11, 12, 1980, false);

    filtered_arr = Filter(arr, size, filtered_size);
    result = FindMaxContemporaryCount(filtered_arr, filtered_size);
    delete [] arr;
    delete [] filtered_arr;

    if(result == correct_res)
        tests_passed++;
    else
    {
        cout << "test: " << tests_passed<< " failed\n" << "expected: "<<correct_res<<"\ngot:" <<  result << endl;
        return;
    }

    //смерть в 18
    size = 2;
    correct_res = 0;
    arr = new LifePoint[size];
    arr[0].SetDate(11, 12, 1962, true);
    arr[1].SetDate(11, 12, 1980, false);

    filtered_arr = Filter(arr, size, filtered_size);
    result = FindMaxContemporaryCount(filtered_arr, filtered_size);
    delete [] arr;
    delete [] filtered_arr;

    if(result == correct_res)
        tests_passed++;
    else
    {
        cout << "test: " << tests_passed<< " failed\n" << "expected: "<<correct_res<<"\ngot:" <<  result << endl;
        return;
    }

    // никогда не встречались
    size = 4;
    correct_res = 1;
    arr = new LifePoint[size];
    arr[0].SetDate(2, 3, 1500, true);
    arr[1].SetDate(3, 4, 1540, false);
    arr[2].SetDate(3, 5, 1541, true);
    arr[3].SetDate(4, 5, 1600, false);

    filtered_arr = Filter(arr, size, filtered_size);
    result = FindMaxContemporaryCount(filtered_arr, filtered_size);
    delete [] arr;
    delete [] filtered_arr;

    if(result == correct_res)
        tests_passed++;
    else
    {
        cout << "test: " << tests_passed<< " failed\n" << "expected: "<<correct_res<<"\ngot:" <<  result << endl;
        return;
    }

    //все умерли до 18
    size = 6;
    correct_res = 0;
    arr = new LifePoint[size];
    arr[0].SetDate(1, 5, 2000, true);
    arr[1].SetDate(3, 4, 2010, false);
    arr[2].SetDate(3, 8, 2001, true);
    arr[3].SetDate(11, 6, 2015, false);
    arr[4].SetDate(2, 7, 1995, true);
    arr[5].SetDate(13, 8, 2008, false);

    filtered_arr = Filter(arr, size, filtered_size);
    result = FindMaxContemporaryCount(filtered_arr, filtered_size);
    delete [] arr;
    delete [] filtered_arr;

    if(result == correct_res)
        tests_passed++;
    else
    {
        cout << "test: " << tests_passed<< " failed\n" << "expected: "<<correct_res<<"\ngot:" <<  result << endl;
        return;
    }

    // 2 пересечения, но в разное время
    size = 6;
    correct_res = 2;
    arr = new LifePoint[size];
    arr[0].SetDate(2, 8, 2020, true);
    arr[1].SetDate(3, 1, 2041, false);
    arr[2].SetDate(11, 12, 2010, true);
    arr[3].SetDate(6, 9, 2089, false);
    arr[4].SetDate(5, 7, 2050, true);
    arr[5].SetDate(5, 7, 2080, false);

    filtered_arr = Filter(arr, size, filtered_size);
    result = FindMaxContemporaryCount(filtered_arr, filtered_size);
    delete [] arr;
    delete [] filtered_arr;

    if(result == correct_res)
        tests_passed++;
    else
    {
        cout << "test: " << tests_passed<< " failed\n" << "expected: "<<correct_res<<"\ngot:" <<  result << endl;
        return;
    }

    cout << "OK\n";
}


int main()
{
    Tests();
    /*LifePoint* arr = NULL;
    LifePoint* filtered_arr = NULL;
    int size = 0;
    int filtered_size = 0;

    arr = ReadInput(size);
    //PrintArr(arr, size);
    filtered_arr = Filter(arr, size, filtered_size);
    //PrintArr(filtered_arr, filtered_size);
    cout << FindMaxContemporaryCount(filtered_arr, filtered_size);*/

    delete [] filtered_arr;
    delete [] arr;
    return 0;
}




























