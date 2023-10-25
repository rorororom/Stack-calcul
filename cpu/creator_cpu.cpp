#include <stdlib.h>
#include <assert.h>

#include "creator_cpu.h"
#include "../common/log_funcs.h"
#include "../common/const.h"

void CpuCtor(struct Cpu* source, struct Stack* myStack) {
    assert(source != NULL);
    assert(myStack != NULL);

    source->myStack = *myStack;

    source->codeArray = (char*)calloc(MAXSIZE, sizeof(char));
    source->codeRegister = (int*)calloc(MAX_SIZE_REG, sizeof(int));

    source->filename = "../assets/code2.txt";
    source->outputfile = NULL;
}


void CpuDtor (struct Cpu* source)
{
    StackDtor (&source->myStack);

    source->filename = NULL;
    source->outputfile = NULL;

    free (source->codeArray);
    source->codeArray = NULL;

    free (source->codeRegister);
    source->codeRegister = NULL;
}

int CpuVerify (struct Cpu* source)
{
    int cnt_errors = 0;
    if (source->codeArray == NULL)
    {
        cnt_errors = cnt_errors | ERROR_CODE_ARRAY_BIT;
    }
    if (source->outputfile == NULL)
    {
        cnt_errors = cnt_errors | ERROR_OUTPUTFILE_BIT;
    }
    if (source->codeRegister == NULL)
    {
        cnt_errors = cnt_errors | ERROR_CODE_REGISTER_BIT;
    }
    if (source->filename == NULL)
    {
        cnt_errors = cnt_errors | ERROR_FILENAME_BIT;
    }

    return cnt_errors;
}


void CpuDump (struct Cpu* source)
{
    fprintf(LOG_FILE, "CPU Dump:\n");

    fprintf(LOG_FILE, "     Filename: %s\n", source->filename);
}
