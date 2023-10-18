#ifndef CREATOR_CPU
#define CREATOR_CPU

#include "../cpu/stack.h"
#include <stdio.h>

#define CPU_VERIFY(myCpu) {         \
    if (CpuVerify (myCpu) > 0) {    \
        CPU_DUMP (myCpu);           \
    }                               \
}

#define DEF_CMD(name, num, ...)     \
        CMD_##name = num,

enum Commands
{
    #include "../common/commands.h"
};

#undef DEF_CMD


enum CpuErrors {
    ERROR_FILENAME_BIT        = 1,
    ERROR_OUTPUTFILE_BIT      = 1 << 2,
    ERROR_CODE_ARRAY_BIT      = 1 << 3,
    ERROR_CODE_REGISTER_BIT   = 1 << 4,
};

struct Cpu {
    struct Stack myStack;
    const char* filename;
    FILE* outputfile;
    char* codeArray;
    int* codeRegister;
};

void CpuCtor (struct Cpu* myCpu, struct Stack* myStack);
void CpuDtor (struct Cpu* myCpu);
void CpuDump (struct Cpu* myCpu);

int CpuVerify (struct Cpu* myCpu);

#endif
