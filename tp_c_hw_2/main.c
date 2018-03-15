#include "main.h"
#include "stack.h"
#include "variablebuffer.h"



//логика перемещения символов между стеками
void TransferOperator(int operator, int priority, Stack* expression, Stack* operators, Stack* priorities)
{
    if(priorities->top != 0)
        if(Peek(priorities) >= priority)
        {
            while(priorities->top != 0)
                if(Peek(priorities) >= priority)
                {
                    Push(expression, Pop(operators));
                    Pop(priorities);
                }
                else
                    break;
        }

    Push(operators, operator);
    Push(priorities, priority);
}

//перевод в постфксную запись
Stack* ToPostfixNotation(char* input)
{
    Stack* expression = InitStack();
    Stack* operators = InitStack();
    Stack* priorities = InitStack();
    int len;

    if(input == NULL)
        return NULL;
    else
        len = strlen(input);

    if(len == 0)
        Push(expression, 0);

    for(int i = 0; i < len; i++)
    {
        switch(input[i])
        {
        case('1'):
            Push(expression, 1);
            break;

        case('0'):
            Push(expression, 0);
            break;

        case('('):
            Push(operators, 40);
            Push(priorities, PRIORITY_BRACKET);
            break;

        case('&'):
            TransferOperator(38, PRIORITY_AND, expression, operators, priorities);
            break;

        case('|'):
            TransferOperator(124, PRIORITY_XOR, expression, operators, priorities);
            break;

        case('^'):
            TransferOperator(94, PRIORITY_XOR, expression, operators, priorities);
            break;

        case('!'):
            TransferOperator(33, PRIORITY_NOT, expression, operators, priorities);
            break;

        case(')'):
            while(1)
            {
                if((operators)->top != 0)
                {
                    if(Peek(operators) != 40)
                    {
                        int a = Pop(operators);
                        Push(expression, a);
                        Pop(priorities);
                    }
                    else
                        break;
                }
                else
                {
                    ERROR_MSG;
                    exit(0);
                }
            }
            Pop(operators);
            Pop(priorities);
            break;

        default:
            ERROR_MSG;
            exit(0);
            break;
        }
    }

    while((operators)->top != 0)
    {
        if(Peek(operators) == 40)
        {
            FreeStack(&expression);
            FreeStack(&priorities);
            FreeStack(&operators);

            ERROR_MSG;
            exit(0);
        }

        Push(expression, Pop(operators));
        Pop(priorities);
    }

    FreeStack(&priorities);
    FreeStack(&operators);

    return expression;
}

//расчет выражение
int CalcExpression(Stack* expression)
{
    Stack* stack = InitStack();
    int buf = 0;

    for(size_t i = 0; i < expression->top; i++)
    {
        switch(expression->data[i])
        {
        case 1:
            Push(stack, 1);
            break;

        case 0:
            Push(stack, 0);
            break;

        case '&':
            buf = Pop(stack);
            buf &= Pop(stack);
            Push(stack, buf);
            break;

        case '|':
            buf = Pop(stack);
            buf |= Pop(stack);
            Push(stack, buf);
            break;

        case '^':
            buf = Pop(stack);
            buf ^= Pop(stack);
            Push(stack, buf);
            break;

        case '!':
            buf = Pop(stack);
            Push(stack, !buf);
            break;

        default:
            break;
        }
    }

    buf = Pop(stack);
    if(stack->top != 0)
        buf = -1;

    FreeStack(&stack);
    return buf;
}



//очистка строки от пробелов
char* ClearSpaces(char* string)
{
    int spaces_num = 0;
    int n = strlen(string);

    for(int i = 0; i < n; i++)
        if(string[i] == ' ' || string[i] == '\n')
            spaces_num++;

    int new_string_size = n-spaces_num;
    if(new_string_size <= 0)
        return NULL;

    int new_string_position = 0;
    char* new_string = (char*) malloc(new_string_size);

    if(new_string == NULL)
        return NULL;

    for(int i = 0; i < n; i++)
        if(string[i] != ' ' && string[i] != '\n')
        {
            new_string[new_string_position] = string[i];
            new_string_position++;
        }

    return new_string;
}

//проверка объявления переменной на корректность
int CheckDeclaration(char *declaration)
{
    int n = strlen(declaration);
    int eq_counter = 0;
    int comma_counter = 0;

    for(int i = 0; i < n; i++)
    {
        if(declaration[i] == '=')
        {
            eq_counter++;
            if(eq_counter > 1)
                return 0;
        }

        if(declaration[i] == ';')
        {
            comma_counter++;
            if(comma_counter > 1)
                return 0;
        }
    }

    return 1;
}

//проверка имени переменной на доступность
int CheckNameAvailability(char* variable_name)
{
    int n = strlen(variable_name);

    for(int i = 0; i < n; i++)
        if(variable_name[i] < 97 || variable_name[i] > 122)
            return 0;

    if(strcmp(variable_name, "and") == 0)
        return 0;

    if(strcmp(variable_name, "or") == 0)
        return 0;

    if(strcmp(variable_name, "xor") == 0)
        return 0;

    if(strcmp(variable_name, "not") == 0)
        return 0;

    return 1;
}

//распарсиваем строку объявления переменной
int ParseVariableDeclaration(VariablesBuffer* var_buffer, char* declaration)
{
    char* command = NULL;
    char* variable = NULL;
    char* str_buffer = NULL;
    int variable_value;
    int var_size;

    //предварительный анализ
    if(!CheckDeclaration(declaration))
        return 0;

    //очистка от пробелов
    command = ClearSpaces(declaration);
    if(command == NULL)
        return 0;

    //считываем название переменной
    str_buffer = strtok(command, "=");
    if(str_buffer == NULL)
        return 0;

    //переписывам имя переменной
    var_size = strlen(str_buffer);
    variable = (char*) calloc(var_size+1, sizeof(char));

    if(variable == NULL)
    {
        free(command);
        return 0;
    }

    variable = strcpy(variable, str_buffer);
    if(variable == NULL)
    {
        free(command);
        return 0;
    }

    if(!CheckNameAvailability(variable))
    {
        free(command);
        free(variable);
        return 0;
    }

    //считываем значение переменной
    str_buffer = strtok(NULL, "=;");
    if(str_buffer == NULL)
    {
        free(command);
        free(variable);
        return 0;
    }

    //определяем значение переменной
    if(strcmp("True", str_buffer) == 0)
        variable_value = 1;
    else
        if(strcmp("False", str_buffer) == 0)
            variable_value = 0;
        else
        {
            free(command);
            free(variable);
            return 0;
        }

    AddVariable(var_buffer, variable, variable_value);
    free(command);
    free(variable);

    return 1;
}

//чтение строки произвольной строки
char* ReadString()
{
   const int block_size = 256;
   char* string_buffer = (char*) calloc(block_size, sizeof(char));

   if(string_buffer == NULL)
       return NULL;

   if(gets(string_buffer) == NULL)
       return NULL;

   return string_buffer;
}

//ввод данных пользователем
char* ReadInput(VariablesBuffer* var_buffer)
{
    char* string = NULL;

    while(1)
    {
        if(string != NULL)
            free(string);

        string = ReadString();
        if(string == NULL)
            return NULL;

        if(strchr(string, ';') != NULL)
        {
            if(!ParseVariableDeclaration(var_buffer, string))
            {
                free(string);
                return NULL;
            }
        }
        else
            break;
    }

    return string;
}

//ставит пробелы рядом со скобками, чтобы было удобно парсить
char* ExpandBrackets(char* string)
{
    int len = strlen(string);

    if(len == 0)
        return NULL;

    int size = 2 * len + 1;
    int counter = 0;
    char* buffer = malloc(size * sizeof(char));

    if(buffer == NULL)
        return NULL;

    buffer[counter] = string[counter];
    counter++;

    for(int i = 1; i < len; i++)
    {
        if(string[i] == '(' || string[i] == ')')
        {
            buffer[counter] = ' ';
            counter++;
            buffer[counter] = string[i];
            counter++;
            continue;
        }

        if(string[i-1] == '(' || string[i] == ')')
        {
            buffer[counter] = ' ';
            counter++;
            buffer[counter] = string[i];
            counter++;
            continue;
        }

        buffer[counter] = string[i];
        counter++;
    }

    buffer[counter] = '\0';
    counter++;

    return buffer;
}

//замена комманд и переменных на односимволные значения
char* ParseExpression(char* expression_src, VariablesBuffer* var_buffer)
{
    char* expression = ExpandBrackets(expression_src);
    char* sub_string = NULL;

    if(expression == NULL)
        return NULL;

    char* expression_parsed;
    int len = strlen(expression) + 1;
    int expression_parsed_pointer = 0;

    expression_parsed =  (char*) calloc(len, sizeof(char));
    if(expression == NULL)
    {
        free(expression);
        return NULL;
    }

    sub_string = strtok(expression, " \n");
    while(sub_string != NULL)
    {
        char tmp = 0;

        if(strcmp(sub_string, "(") == 0)
            tmp =  '(';

        else if (strcmp(sub_string, ")") == 0)
            tmp =  ')';

        else if (strcmp(sub_string, "not") == 0)
            tmp =  '!';

        else if (strcmp(sub_string, "and") == 0)
            tmp =  '&';

        else if(strcmp(sub_string, "or") == 0)
            tmp =  '|';

        else if(strcmp(sub_string, "xor") == 0)
            tmp =  '^';

        else if(strcmp(sub_string, "True") == 0)
            tmp =  '1';

        else if(strcmp(sub_string, "False") == 0)
            tmp =  '0';

        else
        {
            int* value_ptr = GetVariableValue(var_buffer, sub_string);
            if(value_ptr == NULL)
            {
                free(expression);
                free(expression_parsed);
                return NULL;
            }
            else if(*value_ptr)
                tmp =  '1';
            else
                tmp =  '0';
        }

        sub_string = strtok(NULL, " \n");
        expression_parsed[expression_parsed_pointer] = tmp;
        expression_parsed_pointer++;
    }

    free(expression);
    return expression_parsed;
}



int main()
{
    char* expression = NULL;
    char* expression_parsed = NULL;
    Stack* postfix_notation = NULL;
    VariablesBuffer* var_buffer = InitVariablesBuffer();

    if(var_buffer!= NULL)
    {
        expression = ReadInput(var_buffer);

        if(expression != NULL)
        {
            expression_parsed = ParseExpression(expression, var_buffer);

            if(expression_parsed != NULL)
            {
                postfix_notation = ToPostfixNotation(expression_parsed);

                if(postfix_notation != NULL)
                {
                    int result = CalcExpression(postfix_notation);

                    switch (result)
                    {
                    case 1:
                        printf("True");
                        break;
                    case 0:
                        printf("False");
                        break;
                    default:
                        ERROR_MSG;
                        break;
                    }

                    FreeStack(&postfix_notation);
                }
                else
                    //printf("[error in postfix notation]");
                    ERROR_MSG;

                free(expression_parsed);
            }
            else
                //printf("[error in expression parsing]");
                ERROR_MSG;

            free(expression);
        }
        else
            //printf("[error in expression reading]");
            ERROR_MSG;

        FreeVariablesBuffer(&var_buffer);
    }
    else
        //printf("[error variables buffer init]");
        ERROR_MSG;

    return 0;
}
