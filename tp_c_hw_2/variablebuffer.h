#ifndef VARIABLEBUFFER_H
#define VARIABLEBUFFER_H


#define VARIABLE_BUFFER_BLOCK_SIZE 50
#define ERROR_MSG printf("[error]")


//структура описвыающая буффер переменных
typedef struct VariablesBuffer
{
    int size;
    char** names;
    int* values;
} VariablesBuffer;

//расширение буффера переменных
void ExpandVariableBuffer(VariablesBuffer* buffer);

//добавление новой переменной
void AddVariable(VariablesBuffer* buffer, const char* name, int value);

//получение переменной по имени
int* GetVariableValue(VariablesBuffer* buffer, const char* name);

//вывод буффера переменных в stdout
void PrintVariablesBuffer(const VariablesBuffer* buffer);

//инициализация хранилища переменных
VariablesBuffer* InitVariablesBuffer();

//очисика памяти от хранилища
void FreeVariablesBuffer(VariablesBuffer** buffer);

#endif // VARIABLEBUFFER_H
