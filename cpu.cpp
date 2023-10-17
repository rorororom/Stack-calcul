#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "creator_cpu.h"
#include "cpu.h"
#include "log_funcs.h"

#define DEF_CMD(name, num, has_arg_push, has_arg_pop, code)    \
    case CMD_##name:                                          \
        code                                                  \
        i++;                                                  \
        break;


int CpuBinary (struct Cpu* myCpu)
{
    int code = 0;
    FILE* file = fopen("code2.bin", "rb");

    int position = 0;
    if (fread(&position, sizeof(int), 1, file) != 1)
    {
        perror("!Ошибка при чтении из файла");
        fclose(file);
        return 1;
    }

    char* codeArray = (char*)calloc(position, sizeof(char));

    if (codeArray == NULL)
    {
        perror("Не удается выделить память");
        fclose(file);
        return 1;
    }

    printf("position = %d\n", position);

    if (fread(codeArray, sizeof(char), position, file) != position)
    {
        perror("Ошибка при чтении из файла");
        free(codeArray);
        fclose(file);
        return 1;
    }

    fclose(file);

    CommandPrintout (position, codeArray);

    ProcessCodeArray(myCpu, codeArray, position);

    return 0;
}

void ProcessCodeArray (struct Cpu* myCpu, char* codeArray, int position)
{
    int i = 0;
    int value = 0;
    int code_arg = 0;
    int startCode = 0;
    int code = 0;
    int number1 = 0;
    int number2 = 0;

    while (i < position)
    {
        startCode = codeArray[i];
        code = startCode & 31;

        int exponent = 0, base = 0, result = 0;

        if (startCode == -1)
        {
            fclose(myCpu->outputfile);
            break;
        }

        switch (code)
        {
            #include "commands.h"

            default:
                printf("Неизвестный код операции: %d\n", code);
                i++;
                break;
        }
        #undef DEF_CMD
    }
}

Elem_t return_arg (struct Cpu* myCpu, int code)
{
    switch (code)
    {
        case 101:
            return myCpu->codeRegister[1];
            break;
        case 102:
            return myCpu->codeRegister[2];
            break;
        case 103:
            return myCpu->codeRegister[3];
            break;
        case 104:
            return myCpu->codeRegister[4];
            break;
        default:
            printf("Неизвестный регистр: %d\n", code);
            break;
    }

    return 0;
}

void PopArg (struct Cpu* myCpu, int code)
{
    switch (code)
    {
        case 101:
            myCpu->codeRegister[1] = StackPop(&myCpu->myStack);
            break;
        case 102:
            myCpu->codeRegister[2] = StackPop(&myCpu->myStack);
            break;
        case 103:
            myCpu->codeRegister[3] = StackPop(&myCpu->myStack);
            break;
        case 104:
            break;
        default:
            printf("!!!!!Неизвестный регистр: %d\n", code);
            break;
    }
}

int CheckStackSizeForOperation (struct Stack* myStack)
{
    if (GetSizeStack(myStack) < 2)
    {
        printf("Ошибка: недостаточно элементов в стеке для выполнения операции.\n");
        return 0;
    }
    return 1;
}

void ArifmeticCommand (struct Cpu* myCpu, int code)
{
    Elem_t number1 = 0, number2 = 0;

    if (CheckStackSizeForOperation(&myCpu->myStack))
    {
        number1 = StackPop(&myCpu->myStack);
        number2 = StackPop(&myCpu->myStack);

    }
}

