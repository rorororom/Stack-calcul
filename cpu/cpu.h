#ifndef CPU_H
#define CPU_H

typedef int Elem_t;

#define FORMAT_SPECIFIER(type) _Generic((type), \
    int: "%d", \
    float: "%f", \
    double: "%lf", \
    char*: "%s" \
)


#define CPU_DUMP(source) CpuDump(source);

int CheckStackSizeForOperation (struct Stack* myStack);
Elem_t return_arg (struct Cpu* source, int code);
void ProcesscodeArray (struct Cpu* source, char* codeArray, int position);
void PopArg (struct Cpu* source, int code);

void ArifmeticCommand (struct Cpu* source, int code);

void CommandPrintout (int position, char* codeArray);
void PrintBinary (int position, char* codeArray);
int ValidationFile(FILE* file);
#endif
