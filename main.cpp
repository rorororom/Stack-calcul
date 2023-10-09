#include <stdlib.h>
#include <string.h>

#include "log_funcs.h"
#include "stack.h"
#include "compiler.h"
#include "cpu.h"

int main()
{
    OpenLogFile ("LOGE", "w");

    Stack myStack = {};
    StackCtor (&myStack);
    STACK_DUMP (&myStack);

    struct Cpu myCpu = {};
    CpuCtor (&myCpu, &myStack);
    CPU_DUMP (&myCpu);

    int position = Compiler (&myCpu);
    STACK_DUMP (&myStack);
    CPU_DUMP (&myCpu);

    CpuBinary(&myCpu, position);
    STACK_DUMP (&myStack);
    CPU_DUMP (&myCpu);

    CpuDtor (&myCpu);
    return 0;
}

//-DWITH_CANARY_AND_HASHE




