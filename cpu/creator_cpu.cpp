#include <stdlib.h>
#include <assert.h>

#include "creator_cpu.h"
#include "log_funcs.h"

void CpuCtor(struct Cpu* myCpu, struct Stack* myStack) {
    assert(myCpu != NULL);
    assert(myStack != NULL);

    myCpu->myStack = *myStack;

    myCpu->codeArray = (char*)calloc(MAXSIZE, sizeof(char));
    myCpu->codeRegister = (int*)calloc(MAX_SIZE_REG, sizeof(int));

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


void CpuDump (struct Cpu* myCpu)
{
    fprintf(LOG_FILE, "CPU Dump:\n");

    for (int i = 1; i < 2; i++)
    {
        fprintf (LOG_FILE, "%d = %d\n", i, myCpu->codeRegister[i]);
    }

    fprintf(LOG_FILE, "     Filename: %s\n", myCpu->filename);
}
