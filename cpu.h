#include "stack.h"

typedef int Elem_t;

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
    PUSH_R = 33,
    RAX = 101,
    RBX = 102,
    RCX = 103,
    RDX = 104,

};

struct Cpu {
    struct Stack myStack;
    const char *filename;
    FILE *outputfile;
    int rax;
    int rbx;
    int rcx;
    int rdx;
};

#define FORMAT_SPECIFIER(type) _Generic((type), \
    int: "%d", \
    float: "%f", \
    double: "%lf", \
    char*: "%s" \
)

void Cpu(struct Cpu* myCpu);
int CheckStackSizeForOperation (struct Stack* myStack);
int call_arg (struct Cpu* myCpu, char arg_rAx[]);
void pop_arg (struct Cpu* myCpu, int code);
Elem_t return_arg (struct Cpu* myCpu, int code);
