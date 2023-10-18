#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main ()
{
    Stack myStack = {};
    StackCtor (&myStack);
    STACK_DUMP (&myStack);

    struct Cpu myCpu = {};
    CpuCtor (&myCpu, &myStack);
    CPU_DUMP (&myCpu);

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
