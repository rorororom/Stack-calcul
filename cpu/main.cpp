#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "creator_cpu.h"
#include "cpu.h"
#include "../common/log_funcs.h"
#include "../common/const.h"

int readIntFromFile(FILE* file, int* value, size_t size, size_t count);

int main ()
{
    OpenLogFile ("LOGE.log", "w");

    Stack myStack = {};
    StackCtor (&myStack);
    STACK_DUMP (&myStack);

    struct Cpu source = {};
    CpuCtor (&source, &myStack);
    CPU_DUMP (&source);

    int code = 0;
    FILE* file = fopen("../common/code2.bin", "rb");

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

    CommandPrintout (position, codeArray);

    fclose(file);
    CommandPrintout (position, codeArray);

    ProcesscodeArray(&source, codeArray, position);

    return 0;
}

int readIntFromFile(FILE* file, int* value, size_t size, size_t count)
{
    if (fread(value, size, count, file) != count)
    {
        perror("!Ошибка при чтении из файла");
        return 0;
    }
    return 1;
}
