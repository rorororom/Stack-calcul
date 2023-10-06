int Compiler(struct Cpu* myCpu);
int CommandToCode(const char* command);
void ReverseCompiler(FILE* inputFile, FILE* outputFile);
int CheckStackSizeForOperation (struct Stack* myStack);
void CpuCtor (struct Cpu* myCpu, struct Stack* myStack);
