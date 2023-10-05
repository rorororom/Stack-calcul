#include <stdlib.h>
#include <string.h>

#include "log_funcs.h"
#include "stack.h"
#include "cpu.h"

int main()
{
    OpenLogFile ("LOGE", "w");

    Stack myStack = {};

    StackCtor (&myStack);
    STACK_DUMP (&myStack);

    struct Cpu myCpu = {
        myStack,
        NULL,
        NULL
    };

    Compiler (&myCpu);
//     char input[256];
//
//     while (true) {
//         scanf("%s", input);
//
//         if (strcmp(input, "exit") == 0) {
//             printf ("%d\n", StackPop(&myStack));
//             break;
//         }
//         else
//         {
//             // for (int i = myStack.size - 1; i >= 0; i--) {
//             //     printf("%d\n", myStack.data[i]);
//             // }
//
//             sravnenie_v1(input, &myStack);
//         }
//     }

    StackDtor(&myStack);

    return 0;
}

//-DWITH_CANARY_AND_HASHE




