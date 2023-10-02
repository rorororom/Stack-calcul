#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "calculator.h"

int sravnenie(char* string, struct Stack* myStack)
{
    int value = 0;
    int number1 = 0;
    int number2 = 0;
    if (strcmp(string, "push") == 0)
    {
        scanf("%d", &value);
        StackPush(myStack, value);

        while (getchar() != '\n');
    }
    else if (strcmp(string, "sub") == 0)
    {
        number1 = StackPop(myStack);
        number2 = StackPop(myStack);

        value = number1 - number2;

        StackPush(myStack, value);

        while (getchar() != '\n');
    }
    else if (strcmp(string, "out") == 0)
    {
        printf("%d\n", printf_Stack(myStack));
    }
    else if (strcmp(string, "div") == 0)
    {
        number1 = StackPop(myStack);
        number2 = StackPop(myStack);
        value = number1 / number2;

        StackPush(myStack, value);

        while (getchar() != '\n');
    }
    return 0;
}

int printf_Stack(struct Stack* myStack)
{
    if (myStack->size > 0)
        return myStack->data[myStack->size - 1];
    else
    {
        printf("Stack is empty\n");
        return -1;
    }
}
