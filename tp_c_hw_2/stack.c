#include "stack.h"



//инициализация стека
Stack* InitStack()
{
    Stack* stack = NULL;

    stack = (Stack*) malloc(sizeof(Stack));
    if(stack == NULL)
    {
        ERROR_MSG;
        exit(0);
    }

    stack->size = STACK_BLOCK_SIZE;
    stack->data = (int*) calloc(stack->size, sizeof(int));

    if(stack->data == NULL)
    {
        free(stack);
        ERROR_MSG;
        exit(0);
    }

    stack->top = 0;
    return stack;
}


//очистка памяти от стека
void FreeStack(Stack** stack)
{
    free((*stack)->data);
    free(*stack);
    *stack = NULL;
}


//расширение буффера стека
void ResizeStack(Stack* stack)
{
    stack->size += STACK_BLOCK_SIZE;
    stack->data = (int*) realloc(stack->data, stack->size * sizeof(int));
    if(stack->data == NULL)
    {
        ERROR_MSG;
        exit(0);
    }
}


void Push(Stack* stack, int value)
{
    if(stack->top >= stack->size)
        ResizeStack(stack);

    stack->data[stack->top] = value;
    stack->top++;
}


int Pop(Stack* stack)
{
    if(stack->top <= 0)
        ERROR_MSG;

    stack->top--;
    return stack->data[stack->top];
}


int Peek(Stack* stack)
{
    if(stack->top <= 0)
        ERROR_MSG;

    return stack->data[stack->top-1];
}


//вывод стека в stdout
void PrintStack(Stack* stack)
{
    if(stack != NULL)
    {
        printf("\nstack:\n");
        for(size_t i = 0; i < stack->top; i++)
            printf("%d ", stack->data[i]);
    }
}
