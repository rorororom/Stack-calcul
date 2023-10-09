const int MAXSIZE = 10000;

int Compiler(struct Cpu* myCpu);
int CommandToCode(const char* command);
void ReverseCompiler(FILE* inputFile, FILE* outputFile);
int CheckStackSizeForOperation (struct Stack* myStack);

void CpuCtor (struct Cpu* myCpu, struct Stack* myStack);
void CpuDtor (struct Cpu* myCpu);

int BinaryRecordind (int position, struct Cpu* myCpu);

