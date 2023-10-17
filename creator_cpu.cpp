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


void CpuDump (struct Cpu* myCpu)
{
    fprintf(LOG_FILE, "CPU Dump:\n");

    for (int i = 1; i < 2; i++)
    {
        fprintf (LOG_FILE, "%d = %d\n", i, myCpu->codeRegister[i]);
    }

    fprintf(LOG_FILE, "     Filename: %s\n", myCpu->filename);
}




// void Cpu(struct Cpu* myCpu)
// {
//     int code = 0;
//
//     while (fscanf(myCpu->outputfile, FORMAT_SPECIFIER(code), &code) != EOF)
//     {
//         switch (code)
//         {
//             case 1:
//                 CasePush(myCpu);
//                 break;
//             case 2:
//                 CaseSub(myCpu);
//                 break;
//             case 3:
//                 CaseAdd(myCpu);
//                 break;
//             case 4:
//                 CaseMul(myCpu);
//                 break;
//             case 5:
//                 CaseDiv(myCpu);
//                 break;
//             case 6:
//                 CaseSqrt(myCpu);
//                 break;
//             case 7:
//                 CaseSin(myCpu);
//                 break;
//             case 8:
//                 CaseCos(myCpu);
//                 break;
//             case 9:
//                 printf("answer = %d\n", StackPop(&myCpu->myStack));
//                 break;
//             case 33:
//                 CasePushR(myCpu);
//                 break;
//             case -1:
//                 fclose(myCpu->outputfile);
//                 break;
//             default:
//                 printf("Неизвестный код операции: %d\n", code);
//                 break;
//         }
//     }
// }
