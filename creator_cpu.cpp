#include <stdlib.h>

#include "creator_cpu.h"
#include "log_funcs.h"

void CpuCtor (struct Cpu* myCpu, struct Stack* myStack)
{
    myCpu->myStack = *myStack;

    myCpu -> codeArray = (char*)calloc (MAXSIZE, sizeof (char));
    myCpu -> codeRegister = (int*)calloc (MAX_SIZE_REG, sizeof (char));

    myCpu->filename = "machine_code.txt";
    myCpu->outputfile = NULL;
}

void CpuDtor (struct Cpu* myCpu)
{
    StackDtor (&myCpu->myStack);

    myCpu->filename = NULL;
    myCpu->outputfile = NULL;

    free (myCpu->codeArray);
    myCpu->codeArray = NULL;

    free (myCpu->codeRegister);
    myCpu->codeRegister = NULL;
}

void CommandPrintout (int position, char* codeArray)
{
    fprintf (LOG_FILE, "МАССИВ КОМАНД\n");
    for (int i = 0; i < position; i++)
    {
        fprintf (LOG_FILE, "%d - %d\n", i, codeArray[i]);
    }
}

void PrintBinary (int position, char* codeArray)
{
    for (int i = 0; i < position; i++)
    {
        fprintf(LOG_FILE, "Address: %p, Value: %08X\n", (void*)&codeArray[i], (unsigned int)codeArray[i]);
    }
}
