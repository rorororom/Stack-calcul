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
    HLT = -1
};

struct Cpu {
    struct Stack myStack;
    const char *filename;
    FILE *outputfile;
};

#define FORMAT_SPECIFIER(type) _Generic((type), \
    int: "%d", \
    float: "%f", \
    double: "%lf", \
    char*: "%s" \
)

int SravnenieV1 (char string[], struct Stack* myStack);
int PrintfStack (struct Stack* myStack);
int Compiler(struct Cpu* myCpu);
void Cpu(struct Cpu* myCpu);
int CheckStackSizeForOperation (struct Stack* myStack);
int CommandToCode(const char* command);
void ReverseCompiler(FILE* inputFile, FILE* outputFile);

