#include <iostream>
#include <assert.h>
#include <string.h>
using namespace std;


#define BUFFER_BLOCk_SIZE 1000



class Dequeue
{
  public:
    Dequeue();
    ~Dequeue();
    void PushFront(int a);
    void PushBack(int a);
    int PopFront();
    int PopBack();
    void RowPrint();
    void Print();


  private:
    void ExpandBuffer();
    void MoveLeft(int& ptr);
    void MoveRight(int& ptr);

    int buffer_size;
    int* buffer;
    int head;
    int tail;
};

Dequeue::Dequeue() : head(0), tail(0), buffer_size(BUFFER_BLOCk_SIZE)
{
    buffer = new int[buffer_size];
    assert(buffer);
}

Dequeue::~Dequeue()
{
    delete [] buffer;
}

void Dequeue::MoveLeft(int& ptr)
{
    if(ptr == 0)
        ptr = buffer_size-1;
    else
        ptr--;
}

void Dequeue::MoveRight(int& ptr)
{
    if(ptr == buffer_size-1)
        ptr = 0;
    else
        ptr++;
}

void Dequeue::PushFront(int a)
{
    buffer[head] = a;
    MoveRight(head);

    if(head == tail)
        ExpandBuffer();
}

void Dequeue::PushBack(int a)
{
    MoveLeft(tail);
    buffer[tail] = a;

    if(head == tail)
        ExpandBuffer();
}

int Dequeue::PopBack()
{
   if(tail == head)
       return -1;

   int res = buffer[tail];
   MoveRight(tail);

   return res;
}

int Dequeue::PopFront()
{
    if(tail == head)
        return -1;

    MoveLeft(head);
    int res = buffer[head];

    return res;
}

void Dequeue::ExpandBuffer()
{
    int expanded_buffer_size = buffer_size + BUFFER_BLOCk_SIZE;
    int* expanded_buffer = new int[expanded_buffer_size];
    assert(expanded_buffer);

    int cp_count = buffer_size - tail;
    memcpy(expanded_buffer, &buffer[tail], cp_count * sizeof(int));
    assert(expanded_buffer);

    memcpy(&expanded_buffer[cp_count], buffer, tail * sizeof(int));
    assert(expanded_buffer);

    tail = 0;
    head = buffer_size;

    delete [] buffer;
    buffer = expanded_buffer;
    buffer_size = expanded_buffer_size;
}

void Dequeue::RowPrint()
{
    cout << "dequeue: ";

    for(int i = 0; i < buffer_size; i++)
        cout << buffer[i] << " ";
    /*for(int i = tail+1; i <= head; i++ )
    {
        if(i == buffer_size)
            i = 0;

        cout << buffer[i] << " ";
    }*/

    cout << endl;
}



int ProcessCommands(Dequeue* dequeue)
{
    int command_count;
    int command;
    int param;

    cin >> command_count;
    for(int i = 0; i < command_count; i++)
    {
        cin >> command;
        cin >> param;

        switch (command)
        {
        case 1:
            dequeue->PushFront(param);
            break;

        case 2:
            if(param != dequeue->PopFront())
                return 0;
            break;

        case 3:
            dequeue->PushBack(param);
            break;

        case 4:
            if(param != dequeue->PopBack())
                return 0;
            break;

        default:
            break;
        }
    }

    return 1;
}


int main()
{
    Dequeue* dequeue = new Dequeue();

    if(ProcessCommands(dequeue))
        cout << "YES";
    else
        cout << "NO";

    delete(dequeue);
    return 0;
}























