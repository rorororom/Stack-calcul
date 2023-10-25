#ifndef CREATOR_CPU
#define CREATOR_CPU

#include "../cpu/stack.h"
#include "../common/const.h"
#include <stdio.h>

#define CPU_VERIFY(source) {         \
    if (CpuVerify (source) > 0) {    \
        CPU_DUMP (source);           \
    }                               \
}

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

void CpuCtor (struct Cpu* source, struct Stack* myStack);
void CpuDtor (struct Cpu* source);
void CpuDump (struct Cpu* source);

int CpuVerify (struct Cpu* source);

#endif
