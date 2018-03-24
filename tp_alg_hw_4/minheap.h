#ifndef MINHEAP_H
#define MINHEAP_H

#include <iostream>
#include <string.h>
#include <assert.h>
#include <cmath>
using namespace std;

template <typename T>
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
    int SiftDown(int node_index);
    int SiftUp(int node_index);
    void ExpandBuffer();
    void Heapify();

    const int buffer_block_size = 10;
    int buffer_size;
    int heap_size;
    T* buffer;
};

#endif // MINHEAP_H
