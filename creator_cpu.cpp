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

int CpuVerify (struct Cpu* myCpu)
{
    int cnt_errors = 0;
    if (myCpu->codeArray == NULL)
    {
        cnt_errors = cnt_errors | ERROR_CODE_ARRAY_BIT;
    }
    if (myCpu->outputfile == NULL)
    {
        cnt_errors = cnt_errors | ERROR_OUTPUTFILE_BIT;
    }
    if (myCpu->codeRegister == NULL)
    {
        cnt_errors = cnt_errors | ERROR_CODE_REGISTER_BIT;
    }
    if (myCpu->filename == NULL)
    {
        cnt_errors = cnt_errors | ERROR_FILENAME_BIT;
    }

    return cnt_errors;
}
