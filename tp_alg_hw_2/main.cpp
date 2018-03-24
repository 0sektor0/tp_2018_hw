#include <iostream>
#include <math.h>
using namespace std;



void ReadData(int** array_a_ptr, int** array_b_ptr, int& size_a, int& size_b)
{
    cin >> size_a;
    cin >> size_b;

    *array_a_ptr = new int[size_a];
    *array_b_ptr = new int[size_b];

    int* array_a = *array_a_ptr;
    int* array_b = *array_b_ptr;

    for(int i = 0; i < size_a; i++)
    {   array_a[i] = 0;
        cin >> array_a[i];
    }

    for(int i = 0; i < size_b; i++)
    {
        array_b[i] = 0;
        cin >> array_b[i];
    }
}


int FindIndex(const int* array, const int& array_size, const int& key)
{
    int start = 0;
    int middle;
    int end = 2;

    while (true)
    {
        if(end >= array_size)
        {
            end = array_size-1;
            break;
        }

        if(array[start] >= key || array[end] >= key)
            break;

        start = end;
        end *= 2;
    }

    while(start <= end)
    {
        middle = (start + end)/2;

        if(array[middle] >= key)
        {
            if(middle == start)
                return middle;

            if(middle > 0)
            {
                if(array[middle-1] < key)
                    return middle;
                else
                    end = middle-1;
            }
        }
        else
        {
            if(array[middle] > key)
                end = middle-1;
            else
                start = middle+1;
        }
    }

    return array_size;
}


int main()
{
    int* key_array = NULL;
    int* sorted_array = NULL;
    int key_array_size = 0;
    int sorted_array_size = 0;

    ReadData(&sorted_array, &key_array, sorted_array_size, key_array_size);

    for(int i = 0; i < key_array_size; i++)
        cout << FindIndex(sorted_array, sorted_array_size, key_array[i]) << " ";

    delete [] key_array;
    delete [] sorted_array;

    return 0;
}






















