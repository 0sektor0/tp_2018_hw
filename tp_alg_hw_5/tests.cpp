#include <iostream>
#include <assert.h>
#include <string.h>
#include "tests.h"
using namespace std;




bool CompareArrays(const int* arr1, const int& size1, const int* arr2, const int& size2)
{
    if(size1 != size2)
        return false;

    for(int i = 0; i < size1; i++)
        if(arr1[i] != arr2[i])
            return false;

    return true;
}


int Compare(const void* x1, const void* x2)
{
    return ( *(int*)x1 - *(int*)x2 );
}


int* RandArray(int& size)
{
    size = 10 + rand() % ((50 + 1) - 10);
    int* arr = new int[size];

    for(int i = 0; i < size; i++)
        arr[i] = -100 + rand() % ((100 + 1) + 100);

    return arr;
}
