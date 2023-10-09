#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack.h"
#include "cpu.h"
#include "compiler.h"
#include "log_funcs.h"

void Cpu(struct Cpu* myCpu, int position)
{
    int code = 0;

    while (fscanf(myCpu->outputfile, FORMAT_SPECIFIER(code), &code) != EOF)
    {
        switch (code)
        {
            case 1:
                CasePush(myCpu);
                break;
            case 2:
                CaseSub(myCpu);
                break;
            case 3:
                CaseAdd(myCpu);
                break;
            case 4:
                CaseMul(myCpu);
                break;
            case 5:
                CaseDiv(myCpu);
                break;
            case 6:
                CaseSqrt(myCpu);
                break;
            case 7:
                CaseSin(myCpu);
                break;
            case 8:
                CaseCos(myCpu);
                break;
            case 9:
                printf("answer = %d\n", StackPop(&myCpu->myStack));
                break;
            case 33:
                CasePushR(myCpu);
                break;
            case -1:
                fclose(myCpu->outputfile);
                break;
            default:
                printf("Неизвестный код операции: %d\n", code);
                break;
        }
    }
}

Elem_t return_arg (struct Cpu* myCpu, int code)
{
    switch (code)
    {
        case 101:
            return myCpu->rax;
            break;
        case 102:
            return myCpu->rbx;
            break;
        case 103:
            return myCpu->rcx;
            break;
        case 104:
            return myCpu->rdx;
            break;
        default:
            printf("Неизвестный регистр: %d\n", code);
            break;
    }
}

void PopArg (struct Cpu* myCpu, int code)
{
    switch (code)
    {
        case 101:
            myCpu->rax = StackPop(&myCpu->myStack);
            break;
        case 102:
            myCpu->rbx = StackPop(&myCpu->myStack);
            break;
        case 103:
            myCpu->rcx = StackPop(&myCpu->myStack);
            break;
        case 104:
            break;
        default:
            printf("Неизвестный регистр: %d\n", code);
            break;
    }
}

int CheckStackSizeForOperation (struct Stack* myStack)
{
    if (GetSizeStack(myStack) < 2)
    {
        printf("Ошибка: недостаточно элементов в стеке для выполнения операции sum.\n");
        return 0;
    }
    return 1;
}

void CasePush (struct Cpu* myCpu)
{
    int value = 0;

    if (fscanf(myCpu->outputfile, FORMAT_SPECIFIER(value), &value) != EOF)
    {
        StackPush(&myCpu->myStack, value);
    }
}

void CaseSub (struct Cpu* myCpu)
{
    Elem_t number1 = 0, number2 = 0;
    int value = 0;

    if (CheckStackSizeForOperation(&myCpu->myStack))
    {
        number1 = StackPop(&myCpu->myStack);
        number2 = StackPop(&myCpu->myStack);

        value = number2 - number1;

        StackPush(&myCpu->myStack, value);
    }
}

void CaseAdd (struct Cpu* myCpu)
{
    Elem_t number1 = 0, number2 = 0;
    int value = 0;

    if (CheckStackSizeForOperation(&myCpu->myStack))
    {
        number1 = StackPop(&myCpu->myStack);
        number2 = StackPop(&myCpu->myStack);

        value = number2 + number1;

        StackPush(&myCpu->myStack, value);
    }
}

void CaseMul (struct Cpu* myCpu)
{
    Elem_t number1 = 0, number2 = 0;
    int value = 0;

    if (CheckStackSizeForOperation(&myCpu->myStack))
    {
        number1 = StackPop(&myCpu->myStack);
        number2 = StackPop(&myCpu->myStack);

        value = number2 * number1;

        StackPush(&myCpu->myStack, value);
    }
}

void CaseDiv (struct Cpu* myCpu)
{
    Elem_t number1 = 0, number2 = 0;
    int value = 0;

    if (CheckStackSizeForOperation(&myCpu->myStack))
    {
        number1 = StackPop(&myCpu->myStack);
        number2 = StackPop(&myCpu->myStack);

        if (number1 == 0)
        {
            printf("Ошибка: деление на ноль недопустимо.\n");
            StackPush(&myCpu->myStack, number2);
            StackPush(&myCpu->myStack, number1);
        }
        else
        {
            value = number2 / number1;
            StackPush(&myCpu->myStack, value);
        }
    }
}

void CaseSqrt (struct Cpu* myCpu)
{
    Elem_t number1 = 0;
    int value = 0;

    if (CheckStackSizeForOperation(&myCpu->myStack))
    {
        number1 = StackPop(&myCpu->myStack);

        value = number1 * 0.5;

        StackPush(&myCpu->myStack, value);
    }
}

void CaseSin (struct Cpu* myCpu)
{
    Elem_t number1 = 0;
    int value = 0;

    if (CheckStackSizeForOperation(&myCpu->myStack))
    {
        number1 = StackPop(&myCpu->myStack);

        value = sin(number1);

        StackPush(&myCpu->myStack, value);
    }
}

void CaseCos (struct Cpu* myCpu)
{
    Elem_t number1 = 0;
    int value = 0;

    if (CheckStackSizeForOperation(&myCpu->myStack))
    {
        number1 = StackPop(&myCpu->myStack);

        value = cos(number1);

        StackPush(&myCpu->myStack, value);
    }
}

void CasePushR (struct Cpu* myCpu)
{
    int code_arg = 0;

    if (fscanf(myCpu->outputfile, FORMAT_SPECIFIER(code_arg), &code_arg) != EOF)
    {
        StackPush(&myCpu->myStack, return_arg(myCpu, code_arg));
    }
}

void CpuDump (struct Cpu* myCpu)
{
    fprintf(LOG_FILE, "CPU Dump:\n");
    fprintf(LOG_FILE, "  RAX: %d\n", myCpu->rax);
    fprintf(LOG_FILE, "  RBX: %d\n", myCpu->rbx);
    fprintf(LOG_FILE, "  RCX: %d\n", myCpu->rcx);
    fprintf(LOG_FILE, "  RDX: %d\n", myCpu->rdx);
    fprintf(LOG_FILE, "  Filename: %s\n", myCpu->filename);
}

int CpuBinary (struct Cpu* myCpu, int position)
{
    int code = 0;

    FILE* file = fopen("code2.bin", "rb");
    char* codeArray = (char*)calloc(position, sizeof(char));

    fread(codeArray, position, sizeof(int), file);
    fprintf(LOG_FILE, "МАССИВ КОМАНД111\n");
    for(int i = 0; i < position; i++)
    {
        fprintf(LOG_FILE, "%d - %d\n", i, codeArray[i]);
    }

    int i = 0;
    int value = 0;
    int code_arg = 0;
    while (i < position)
    {
        code = codeArray[i];
        switch (code)
        {
            case 1:
                i+=1;
                value = codeArray[i];
                StackPush(&myCpu->myStack, value);
                i++;
                break;
            case 2:
                CaseSub(myCpu);
                i++;
                break;
            case 3:
                CaseAdd(myCpu);
                i++;
                break;
            case 4:
                CaseMul(myCpu);
                i++;
                break;
            case 5:
                CaseDiv(myCpu);
                i++;
                break;
            case 6:
                CaseSqrt(myCpu);
                i++;
                break;
            case 7:
                CaseSin(myCpu);
                i++;
                break;
            case 8:
                CaseCos(myCpu);
                i++;
                break;
            case 9:
                printf("answer = %d\n", StackPop(&myCpu->myStack));
                i++;
                break;
            case 33:
                i += 1;
                code_arg = codeArray[i];
                StackPush(&myCpu->myStack, return_arg(myCpu, code_arg));
                i++;
                break;
            case -1:
                fclose(myCpu->outputfile);
                i++;
                break;
            default:
                printf("Неизвестный код операции: %d\n", code);
                i++;
                break;
        }
    }
}
