#ifndef STACK_H
#define STACK_H


#include <stdlib.h>
#include <stdio.h>


#define STACK_BLOCK_SIZE 50
#define ERROR_MSG printf("[error]")



typedef struct Stack
{
    int* data;
    size_t size;
    size_t top;
} Stack;

//инициализация стека
Stack* InitStack();

//очистка памяти от стека
void FreeStack(Stack** stack);

//расширение буффера стека
void ResizeStack(Stack* stack);

void Push(Stack* stack, int value);

int Pop(Stack* stack);

int Peek(Stack* stack);

//вывод стека в stdout
void PrintStack(Stack* stack);


#endif // STACK_H
