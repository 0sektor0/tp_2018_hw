#include <iostream>
#include <string.h>
#include <assert.h>
#include <cmath>
using namespace std;



template <class T>
class MinHeap
{
 public:
    MinHeap(const T* arr, const int& size);
    void Add(const T&);
    void PrintHeap();
    const T& Peek();
    int Size();
    T GetMin();
    ~MinHeap();
    MinHeap();


 private:
    int GetChildIndex(int parent_index, bool left);
    int GetParentIndex(int child_index);
    void SiftDown(int node_index);
    void SiftUp(int node_index);
    void ExpandBuffer();

    const int buffer_block_size = 10;
    int buffer_size;
    int heap_size;
    T* buffer;
};


template <class T>
MinHeap<T>::MinHeap(const T* arr, const int& size) : heap_size(size), buffer_size(buffer_block_size)
{
    if (heap_size > buffer_size)
        buffer_size += heap_size;

    buffer = new T[buffer_size];

    memcpy(buffer, arr, heap_size * sizeof(T));

    for(int i = heap_size/2 - 1; i >= 0; i--)
        SiftDown(i);
}


template <class T>
MinHeap<T>::MinHeap() : heap_size(0), buffer_size(buffer_block_size)
{
    buffer = new T[buffer_block_size];
}


template <class T>
MinHeap<T>::~MinHeap()
{
    delete [] buffer;
}


template <class T>
void MinHeap<T>::ExpandBuffer()
{
    int new_buffer_size = buffer_size + buffer_block_size;
    T* new_buffer = new T[new_buffer_size];

    memcpy(new_buffer, buffer, heap_size * sizeof(T));

    delete [] buffer;
    buffer = new_buffer;
    buffer_size = new_buffer_size;
}


template <class T>
int MinHeap<T>::Size()
{
    return heap_size;
}


template <class T>
int MinHeap<T>::GetParentIndex(int child_index)
{
    assert(child_index < heap_size || child_index >= 0);

    if(child_index == 0)
        return child_index;
    else
        return (child_index -1)/2;
}


template <class T>
int MinHeap<T>::GetChildIndex(int parent_index, bool left)
{
    assert(parent_index >= 0);
    int child_index;

    if (left)
        child_index = 2 * parent_index + 1;
    else
        child_index = 2 * parent_index + 2;

    if(child_index < heap_size)
        return child_index;
    else
        return parent_index;
}


template <class T>
void MinHeap<T>::SiftUp(int node_index)
{
    int parent_index = -1;

    while(node_index > 0)
    {
        //проверка на выход за пределы идет в методе получения родителя
        parent_index = GetParentIndex(node_index);

        if(parent_index != node_index)
        {
            if(buffer[parent_index] > buffer[node_index])
            {
                swap(buffer[parent_index], buffer[node_index]);
                node_index = parent_index;
            }
            else
                break;
        }
        else
            break;
    }
}


template <class T>
void MinHeap<T>::SiftDown(int node_index)
{
    while(true)
    {
        //проверка на выход за пределы идет в методах получения потомков
        int min_child = GetChildIndex(node_index, 1);
        int max_child = GetChildIndex(node_index, 0);

        //определение минимального потомка
        if(buffer[min_child] > buffer[max_child])
            min_child = max_child;

        if(buffer[min_child] < buffer[node_index])
        {
            swap(buffer[min_child], buffer[node_index]);
            node_index = min_child;
        }
        else
            break;
    }
}


template <class T>
void MinHeap<T>::PrintHeap()
{
    int level_counter = 0;
    int brake_point = 0;

    cout << "Heap:" << endl;
    for(int i = 0; i < heap_size; i++)
    {
        cout << buffer[i] << " ";

        if(i == brake_point)
        {
            cout << endl;
            level_counter++;
            brake_point += pow(2, level_counter);
        }
    }
    cout << endl;
}


template <class T>
void MinHeap<T>::Add(const T& value)
{
    if(heap_size == buffer_size)
        ExpandBuffer();

    int new_node_index = heap_size;
    buffer[heap_size] = value;
    heap_size++;

    SiftUp(new_node_index);
}


template <class T>
const T& MinHeap<T>::Peek()
{
    assert(heap_size > 0);
    return buffer[0];
}


template <class T>
T MinHeap<T>::GetMin()
{
    assert(heap_size > 0);
    int min = buffer[0];

    heap_size--;
    swap(buffer[0], buffer[heap_size]);

    bool sorting = true;
    int index = 0;

    SiftDown(index);
    return min;
}



void ReadInput(MinHeap<int>& heap)
{
    int count = 0;
    cin >> count;
    assert(count > 0);

    for(int  i = 0; i < count; i++)
    {
        int data;
        cin >> data;
        heap.Add(data);
    }
}


int QuickSum(MinHeap<int>& heap)
{
    int res = 0;

    if (heap.Size()==1)
        return heap.GetMin();

    while(heap.Size()>1)
    {
        int f_elem = heap.GetMin();
        int s_elem = heap.GetMin();

        int sum = f_elem + s_elem;
        res += sum;
        heap.Add(sum);
    }

    return res;
}



int main()
{
    /*int size = 10;
    int* arr = new int[size] {4, 5, 6, 1, 0 ,2 ,4 ,5 ,6, 3};
    MinHeap<int> heap_1 = MinHeap<int>(arr, size);
    heap_1.PrintHeap();*/

    MinHeap<int> heap = MinHeap<int>();

    ReadInput(heap);
    cout << QuickSum(heap);

    return 0;
}
























