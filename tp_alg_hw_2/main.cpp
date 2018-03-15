#include <iostream>
using namespace std;


void ReadData(int** array_a_ptr, int** array_b_ptr, int& size_a, int& size_b);
int FindIndex(int* array, int array_size, int num);



int main()
{
    int* input_array;
    int* sorted_array;
    int input_array_size;
    int sorted_array_size;

    ReadData(&sorted_array, &input_array, sorted_array_size, input_array_size);

    for(int i = 0; i < input_array_size; i++)
        cout << FindIndex(sorted_array, sorted_array_size, input_array[i]) << " ";


    delete(input_array);
    delete(sorted_array);

    return 0;
}


void ReadData(int** array_a_ptr, int** array_b_ptr, int& size_a, int& size_b)
{
    cin >> size_a;
    cin >> size_b;
dd file to ignore
    *array_a_ptr = new int[size_a];
    *array_b_ptr = new int[size_b];

    int* array_a = *array_a_ptr;
    int* array_b = *array_b_ptr;

    for(int i = 0; i < size_a; i++)
        cin >> array_a[i];

    for(int i = 0; i < size_b; i++)
        cin >> array_b[i];
}


int FindIndex(int* array, int array_size, int key)
{
    int start = 0;
    int middle = -1;
    int end = array_size-1;

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








