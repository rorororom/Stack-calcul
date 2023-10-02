#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "log_funcs.h"
#include "stack.h"

int printf_Stack(struct Stack* myStack);
int sravnenie(char* string, struct Stack* myStack);

int main()
{
    OpenLogFile("LOGE", "w");

    Stack myStack;
    StackCtor(&myStack);

    int i = 0;

    while (1) // Бесконечный цикл
    {
        char string[20];
        scanf("%s", string);

        if (strcmp(string, "exit") == 0)
        {
            break;
        }

        sravnenie(string, &myStack);
    }

    StackDtor(&myStack);

    return 0;
}


