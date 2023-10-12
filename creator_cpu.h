#ifndef CREATOR_CPU
#define CREATOR_CPU

#include "stack.h"
#include <stdio.h>

#define MAXSIZE 100
#define MAX_SIZE_REG 10

#define CPU_VERIFY(myCpu) {         \
    if (CpuVerify (myCpu) > 0) {    \
        CPU_DUMP (myCpu);           \
    }                               \
}

enum {
    PUSH = 1,
    SUB, //2
    ADD, //3
    MUL, //4
    DIV, //5
    SQRT,//6
    SIN, //7
    COS, //8
    OUT, //9
    IN, //10
    POP, //11
    HLT = -1,
    RAX = 101,
    RBX = 102,
    RCX = 103,
    RDX = 104,
};

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

void CommandPrintout (int position, char* codeArray);
void PrintBinary (int position, char* codeArray);
int CpuVerify (struct Cpu* myCpu);

#endif
