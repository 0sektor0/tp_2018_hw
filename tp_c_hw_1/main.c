#include <stdio.h>
#include <stdlib.h>


#define STD_ERROR_MSG printf("[error]")



int ReadData(int* size, int** array);
int FindMaxSubArray(int* size, int* array, int** subarray);
void DisplayResult(int* size, int* array);


int main()
{
    int size;
    int* array = NULL;
    int* subarray = NULL;

    if(!ReadData(&size, &array))
    {
        STD_ERROR_MSG;
        if(array)
            free(array);
        return 0;
    }

    size = FindMaxSubArray(&size, array, &subarray);
    DisplayResult(&size, subarray);

    free(array);
    return 0;
}


int ReadData(int* size, int** array)
{
    if(!scanf("%d", size))
        return 0;

    if(*size <= 0)
        return 0;

    if(!(*array = (int*) malloc(*size * sizeof(int))))
        return 0;

    int i = 0;
    int* array_pointer = *array;
    while(i < *size)
        if(!scanf("%d", &array_pointer[i++]))
            return 0;

    return 1;
}


int FindMaxSubArray(int* size, int* array, int** subarray)
{
    int current_size = 1;
    int max_size = 1;

    for(int i = 1; i < *size; i++)
    {
        if(array[i-1] + 1 == array[i])
            current_size++;
        else
        {
            if(current_size > max_size)
            {
                max_size = current_size;
                *subarray = &array[i - max_size];
            }
            current_size = 1;
        }
    }

    if(current_size > max_size)
    {
        max_size = current_size;
        *subarray = &array[*size - max_size];
    }

    if(max_size == 1)
        return 0;

    return max_size;
}


void DisplayResult(int* size, int* array)
{
    printf("%d\r\n", *size);

    for(int j = 0; j < *size; j++)
        printf("%d ", array[j]);
}
