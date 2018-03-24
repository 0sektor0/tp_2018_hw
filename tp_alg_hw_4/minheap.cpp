#include "minheap.h"


template <typename T>
MinHeap<T>::MinHeap(const T* arr, const int& size) : heap_size(size), buffer_size(buffer_block_size)
{
    if (heap_size > buffer_size)
        buffer_size += heap_size;

    buffer = new T[buffer_size];
    assert(buffer);

    memcpy(buffer, arr, heap_size * sizeof(T));
    assert(buffer);

    Heapify();
}


template <typename T>
MinHeap<T>::MinHeap() : heap_size(0), buffer_size(buffer_block_size)
{
    buffer = new T[buffer_block_size];
    assert(buffer);
}


template <typename T>
MinHeap<T>::~MinHeap()
{
    delete [] buffer;
}


template <typename T>
void MinHeap<T>::ExpandBuffer()
{
    int new_buffer_size = buffer_size + buffer_block_size;
    T* new_buffer = new T[new_buffer_size];
    assert(new_buffer);

    memcpy(new_buffer, buffer, heap_size * sizeof(T));
    assert(new_buffer);

    delete [] buffer;
    buffer = new_buffer;
    buffer_size = new_buffer_size;
}


template <typename T>
int MinHeap<T>::Size()
{
    return heap_size;
}


template <typename T>
int MinHeap<T>::GetParentIndex(int child_index)
{
    assert(child_index < heap_size);
    assert(child_index >= 0);

    if(child_index == 0)
        return child_index;
    else
        return (child_index -1)/2;
}


template <typename T>
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


template <typename T>
int MinHeap<T>::SiftUp(int node_index)
{
    //проверка на выход за пределы идет в методе получения родителя
    int parent_index = GetParentIndex(node_index);

    if(parent_index != node_index)
        if(buffer[parent_index] > buffer[node_index])
        {
            swap(buffer[parent_index], buffer[node_index]);
            return parent_index;
        }

    return node_index;
}


template <typename T>
int MinHeap<T>::SiftDown(int node_index)
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
        return min_child;
    }

    return node_index;
}


template <typename T>
void MinHeap<T>::Heapify()
{
    bool changed = true;

    while(changed)
    {
        changed = false;
        for(int i = heap_size-1; i >= 0; i--)
            changed |= i != SiftUp(i);
    }
}


template <typename T>
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


template <typename T>
void MinHeap<T>::Add(const T& value)
{
    if(heap_size == buffer_size)
        ExpandBuffer();

    int new_node_index = heap_size;
    buffer[heap_size] = value;
    heap_size++;

    bool sorting = true;
    while(sorting)
    {
        int sorted_index = SiftUp(new_node_index);
        sorting = false;
        sorting = sorted_index != new_node_index;
        new_node_index = sorted_index;
    }
}


template <typename T>
const T& MinHeap<T>::Peek()
{
    assert(heap_size > 0);
    return buffer[0];
}


template <typename T>
T MinHeap<T>::GetMin()
{
    assert(heap_size > 0);
    int min = buffer[0];

    heap_size--;
    swap(buffer[0], buffer[heap_size]);

    bool sorting = true;
    int index = 0;
    while (sorting)
    {
        int sorted_index = SiftDown(index);
        sorting = sorted_index != index;
        index = sorted_index;
    }

    return min;
}
