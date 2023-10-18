#include <stdlib.h>
#include <string.h>

#include "log_funcs.h"
#include "stack.h"
#include "compiler.h"
#include "cpu/cpu.h"
#include "creator_cpu.h"

int main ()
{
    OpenLogFile ("LOGE.log", "w");

    Stack myStack = {};
    StackCtor (&myStack);
    STACK_DUMP (&myStack);

    Compiler ();
    STACK_DUMP (&myStack);
    CPU_DUMP (&myCpu);

    CpuDtor (&myCpu);
    return 0;
}

//-DWITH_CANARY_AND_HASHE




