#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stack.h"
#include "cpu.h"

int SravnenieV1(char string[], struct Stack* myStack)
{
    int value = 0;
    int number1 = 0;
    int number2 = 0;

    if (strcmp(string, "push") == 0)
    {
        scanf(FORMAT_SPECIFIER(value), &value);
        StackPush(myStack, value);
    }
    else if (strcmp(string, "add") == 0)
    {
        if (myStack->size < 2)
        {
            printf("Ошибка: недостаточно элементов в стеке для выполнения операции sum.\n");
        }
        else
        {
            number1 = StackPop(myStack);
            number2 = StackPop(myStack);

            value = number2 + number1;

            StackPush(myStack, value);
        }
    }
    else if (strcmp(string, "sub") == 0)
    {
        if (myStack->size < 2)
        {
            printf("Ошибка: недостаточно элементов в стеке для выполнения операции sub.\n");
        }
        else
        {
            number1 = StackPop(myStack);
            number2 = StackPop(myStack);

            value = number2 - number1;

            StackPush(myStack, value);
        }
    }
    else if (strcmp(string, "mul") == 0)
    {
        if (myStack->size < 2)
        {
            printf("Ошибка: недостаточно элементов в стеке для выполнения операции sum.\n");
        }
        else
        {
            number1 = StackPop(myStack);
            number2 = StackPop(myStack);

            value = number2 * number1;

            StackPush(myStack, value);
        }
    }
    else if (strcmp(string, "sqrt") == 0)
    {
        if (myStack->size < 2)
        {
            printf("Ошибка: недостаточно элементов в стеке для выполнения операции sum.\n");
        }
        else
        {
            number1 = StackPop(myStack);

            value = number1 * 0.5;

            StackPush(myStack, value);
        }
    }
    else if (strcmp(string, "sin") == 0)
    {
        if (myStack->size < 2)
        {
            printf("Ошибка: недостаточно элементов в стеке для выполнения операции sum.\n");
        }
        else
        {
            number1 = StackPop(myStack);

            value = sin(number1);

            StackPush(myStack, value);
        }
    }
    else if (strcmp(string, "cos") == 0)
    {
        if (myStack->size < 2)
        {
            printf("Ошибка: недостаточно элементов в стеке для выполнения операции sum.\n");
        }
        else
        {
            number1 = StackPop(myStack);

            value = cos(number1);

            StackPush(myStack, value);
        }
    }
    else if (strcmp(string, "out") == 0)
    {
        printf("%d ", StackPop(myStack));
        printf("\n");

        getchar();
    }
    else if (strcmp(string, "div") == 0)
    {
        if (myStack->size < 2)
        {
            printf("Ошибка: недостаточно элементов в стеке для выполнения операции div.\n");
        }
        else
        {
            number1 = StackPop(myStack);
            number2 = StackPop(myStack);

            if (number1 == 0)
            {
                printf("Ошибка: деление на ноль недопустимо.\n");
                StackPush(myStack, number2);
                StackPush(myStack, number1);
            }
            else
            {
                value = number2 / number1;
                StackPush(myStack, value);
            }
        }

    }

    return 0;
}


int PrintfStack(struct Stack* myStack)
{
    if (myStack->size > 0)
        return myStack->data[myStack->size - 1];
    else
    {
        printf("Stack is empty\n");
        return -1;
    }
}

int Compiler(struct Cpu* myCpu)
{
    FILE* inputFile = fopen("commands.txt", "r");
    if (inputFile == NULL) {
        perror("Не удается открыть файл");
        return 1;
    }

    myCpu->outputfile = fopen("machine_code.txt", "w");
    if (myCpu->outputfile == NULL) {
        return 1;
    }

    char command[256] = "";
    int value = 0;

    while (fscanf(inputFile, "%s", command) != EOF)
    {
        int code = CommandToCode(command);
        if (code == PUSH && fscanf(inputFile, "%d", &value) != EOF)
        {
            fprintf(myCpu->outputfile, "%d  ", code);
            fprintf(myCpu->outputfile, "%d\n", value);
        }
        else
        {
            fprintf(myCpu->outputfile, "%d\n", code);
        }
    }

    fclose(myCpu->outputfile);

    myCpu->outputfile = fopen("modified_commands.txt", "r");
    if (myCpu->outputfile == NULL) {
        return 1;
    }

    Cpu(myCpu);

    return 0;
}


void Cpu(struct Cpu* myCpu)
{
    int code;
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
            case -1:
                fclose(myCpu->outputfile);
                break;
            default:
                printf("Неизвестный код операции: %d\n", code);
                break;
        }
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

int CommandToCode(const char* command)
{
    if (strcmp (command, "push") == 0) return PUSH;
    if (strcmp (command, "sub")  == 0) return SUB;
    if (strcmp (command, "add")  == 0) return ADD;
    if (strcmp (command, "mul")  == 0) return MUL;
    if (strcmp (command, "div")  == 0) return DIV;
    if (strcmp (command, "sqrt") == 0) return SQRT;
    if (strcmp (command, "sin")  == 0) return SIN;
    if (strcmp (command, "cos")  == 0) return COS;
    if (strcmp (command, "out")  == 0) return OUT;
    if (strcmp (command, "hlt")  == 0) return HLT;

    return 0;
}

void ReverseCompiler(FILE* inputFile, FILE* outputFile)
{
    int code, value;

    while (fscanf(inputFile, "%d", &code) != EOF) {
        switch (code) {
            case PUSH:
                if (fscanf(inputFile, "%d", &value) != EOF)
                {
                    fprintf(outputFile, "push  %d\n", value);
                }
                break;
            case ADD:
                fprintf(outputFile, "add\n");
                break;
            case SUB:
                fprintf(outputFile, "sub\n");
                break;
            case MUL:
                fprintf(outputFile, "mul\n");
                break;
            case DIV:
                fprintf(outputFile, "div\n");
                break;
            case SQRT:
                fprintf(outputFile, "sqwrt\n");
                break;
            case SIN:
                fprintf(outputFile, "sin\n");
                break;
            case COS:
                fprintf(outputFile, "cos\n");
                break;
            case OUT:
                fprintf(outputFile, "out\n");
                break;
            case HLT:
                fprintf(outputFile, "hlt\n");
                break;
            default:
                fprintf(outputFile, "unknown\n");
                break;
        }
    }
}

