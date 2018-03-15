#include "variablebuffer.h"



//расширение буффера переменных
void ExpandVariableBuffer(VariablesBuffer* buffer)
{
    buffer->size += VARIABLE_BUFFER_BLOCK_SIZE;

    buffer->names = (char**) realloc(buffer->names, buffer->size * sizeof(char*));
    if(buffer->names == NULL)
    {
        ERROR_MSG;
        exit(0);
    }

    buffer->values = (int*) realloc(buffer->values, buffer->size * sizeof(int));
    if(buffer->values == NULL)
    {
        ERROR_MSG;
        exit(0);
    }
}


//добавление новой переменной
void AddVariable(VariablesBuffer* buffer, const char* name, int value)
{
    if(name == NULL)
    {
        ERROR_MSG;
        exit(0);
    }

    for(int i = 0;; i++)
    {
        if(buffer->names[i] == NULL)
        {
            int len = strlen(name);

            buffer->names[i] = (char*) calloc(len+1, sizeof(char));
            if(buffer->names[i] == NULL)
            {
                ERROR_MSG;
                exit(0);
            }

            buffer->names[i] = strcpy(buffer->names[i], name);
            if(buffer->names[i] == NULL)
            {
                ERROR_MSG;
                exit(0);
            }

            buffer->values[i] = value;
            return;
        }

        if(strcmp(buffer->names[i], name) == 0)
        {
            buffer->values[i] = value;
            return;
        }

        if(i == buffer->size-1)
            ExpandVariableBuffer(buffer);
    }
}


//получение переменной по имени
int* GetVariableValue(VariablesBuffer* buffer, const char* name)
{
    for(int i = 0; i < buffer->size; i++)
        if(buffer->names[i] != NULL)
        {
            if(strcmp(buffer->names[i], name) == 0)
                return &buffer->values[i];
        }
        else
            return NULL;

    return NULL;
}


//вывод буффера переменных в stdout
void PrintVariablesBuffer(const VariablesBuffer* buffer)
{
    printf("variables:\n");

    for(int i = 0; i < buffer->size; i++)
        if(buffer->names[i] != NULL)
            printf("%s : %d\n", buffer->names[i], buffer->values[i]);
}


//инициализация хранилища переменных
VariablesBuffer* InitVariablesBuffer()
{
    VariablesBuffer* buffer = calloc(1, sizeof(VariablesBuffer));
    if(buffer == NULL)
    {
        ERROR_MSG;
        exit(0);
    }

    buffer->size = VARIABLE_BUFFER_BLOCK_SIZE;

    buffer->names = (char**) calloc(buffer->size, sizeof(char*));
    if(buffer->names == NULL)
    {
        ERROR_MSG;
        exit(0);
    }

    buffer->values = (int*) calloc(buffer->size, sizeof(int));
    if(buffer->values == NULL)
    {
        ERROR_MSG;
        exit(0);
    }

    AddVariable(buffer, "True", 1);
    AddVariable(buffer, "False", 0);

    return buffer;
}


//очисика памяти от хранилища
void FreeVariablesBuffer(VariablesBuffer** buffer)
{
    if((*buffer)->names != NULL)
    {
        for(int i = 0; i < (*buffer)->size; i++)
            if((*buffer)->names[i] != NULL)
                free((*buffer)->names[i]);

        free((*buffer)->names);
    }

    if((*buffer)->values != NULL)
        free((*buffer)->values);

    free(*buffer);
    *buffer = NULL;
}

