#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack.h"
#include "cpu.h"
#include "compiler.h"

void Cpu(struct Cpu* myCpu)
{
    int code = 0;
    int code_arg = 0;
    Elem_t value = 0;
    Elem_t number1 = 0, number2 = 0;

    while (fscanf(myCpu->outputfile, FORMAT_SPECIFIER(code), &code) != EOF)
    {
        switch (code)
        {
            case 1:
                if (fscanf(myCpu->outputfile, FORMAT_SPECIFIER(value), &value) != EOF)
                {
                    StackPush(&myCpu->myStack, value);
                }
                break;
            case 2:
                if (CheckStackSizeForOperation(&myCpu->myStack))
                {
                    number1 = StackPop(&myCpu->myStack);
                    number2 = StackPop(&myCpu->myStack);

                    value = number2 - number1;

                    StackPush(&myCpu->myStack, value);
                }
                break;
            case 3:
                if (CheckStackSizeForOperation(&myCpu->myStack))
                {
                    number1 = StackPop(&myCpu->myStack);
                    number2 = StackPop(&myCpu->myStack);

                    value = number2 + number1;

                    StackPush(&myCpu->myStack, value);
                }
                break;
            case 4:
                if (CheckStackSizeForOperation(&myCpu->myStack))
                {
                    number1 = StackPop(&myCpu->myStack);
                    number2 = StackPop(&myCpu->myStack);

                    value = number2 * number1;

                    StackPush(&myCpu->myStack, value);
                }
                break;
            case 5:
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
                break;
            case 6:
                if (CheckStackSizeForOperation(&myCpu->myStack))
                {
                    number1 = StackPop(&myCpu->myStack);

                    value = number1 * 0.5;

                    StackPush(&myCpu->myStack, value);
                }
                break;
            case 7:
                if (CheckStackSizeForOperation(&myCpu->myStack))
                {
                    number1 = StackPop(&myCpu->myStack);

                    value = sin(number1);

                    StackPush(&myCpu->myStack, value);
                }
                break;
            case 8:
                if (CheckStackSizeForOperation(&myCpu->myStack))
                {
                    number1 = StackPop(&myCpu->myStack);

                    value = cos(number1);

                    StackPush(&myCpu->myStack, value);
                }
                break;
            case 9:
                printf("answer = %d\n", StackPop(&myCpu->myStack));
                break;
            case 33:
                if (fscanf(myCpu->outputfile, FORMAT_SPECIFIER(code_arg), &code_arg) != EOF)
                {
                    StackPush(&myCpu->myStack, return_arg(myCpu, code_arg));
                }
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
    }
}

void pop_arg (struct Cpu* myCpu, int code)
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

