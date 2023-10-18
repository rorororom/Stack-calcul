#ifndef CPU_H
#define CPU_H

typedef int Elem_t;

#define FORMAT_SPECIFIER(type) _Generic((type), \
    int: "%d", \
    float: "%f", \
    double: "%lf", \
    char*: "%s" \
)

#define PROCESS_OPERATION(code)                                     \
    if (CheckStackSizeForOperation(&myCpu->myStack)) {              \
        number1 = StackPop(&myCpu->myStack);                        \
        number2 = StackPop(&myCpu->myStack);                        \
    }                                                               \
    switch (code) {                                                 \
        case SUB:                                                   \
            StackPush(&myCpu->myStack, number1 - number2);          \
            break;                                                 \
        case ADD:                                                   \
            StackPush(&myCpu->myStack, number1 + number2);          \
            break;                                                 \
        case MUL:                                                   \
            StackPush(&myCpu->myStack, number1 * number2);          \
            break;                                                 \
        case DIV:                                                   \
            if (number1 == 0) {                                     \
                printf("Ошибка: деление на ноль недопустимо.\n");  \
                StackPush(&myCpu->myStack, number2);                \
                StackPush(&myCpu->myStack, number1);                \
            } else {                                              \
                StackPush(&myCpu->myStack, number2 / number1);      \
            }                                                     \
            break;                                                 \
    }


#define CPU_DUMP(myCpu) CpuDump(myCpu);

int CheckStackSizeForOperation (struct Stack* myStack);
Elem_t return_arg (struct Cpu* myCpu, int code);
void ProcessCodeArray (struct Cpu* myCpu, char* codeArray, int position);

void ArifmeticCommand (struct Cpu* myCpu, int code);
#endif
