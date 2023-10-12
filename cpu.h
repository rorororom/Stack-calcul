#ifndef CPU_H
#define CPU_H

typedef int Elem_t;

#define FORMAT_SPECIFIER(type) _Generic((type), \
    int: "%d", \
    float: "%f", \
    double: "%lf", \
    char*: "%s" \
)

#define CPU_DUMP(myCpu) CpuDump(myCpu);

void CpuDump (struct Cpu* myCpu);

void Cpu(struct Cpu* myCpu);
int CpuBinary (struct Cpu* myCpu);
int CheckStackSizeForOperation (struct Stack* myStack);
int call_arg (struct Cpu* myCpu, char arg_rAx[]);
void PopArg (struct Cpu* myCpu, int code);
Elem_t return_arg (struct Cpu* myCpu, int code);
void ProcessCodeArray (struct Cpu* myCpu, char* codeArray, int position);

void CasePush (struct Cpu* myCpu);
void CaseSub (struct Cpu* myCpu);
void CaseAdd (struct Cpu* myCpu);
void CaseMul (struct Cpu* myCpu);
void CaseDiv (struct Cpu* myCpu);
void CaseSqrt (struct Cpu* myCpu);
void CaseSin (struct Cpu* myCpu);
void CaseCos (struct Cpu* myCpu);
void CasePushR (struct Cpu* myCpu);

#endif 
