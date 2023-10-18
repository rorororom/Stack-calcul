#ifndef COMPILER_H
#define COMPILER_H

#define ADD_CODE_VALUE(arr, pos, code, value, file)     \
    do {                                                \
        (arr)[(pos)++] = (code);                        \
        (arr)[ (pos)++] = (value);                       \
        fprintf ( (file), "%d  %d\n", (code), (value));   \
    } while (0)

#define MAXSIZE 100
#define MAX_SIZE_REG 10

int Compiler ();
int CommandToCodeArg (const char* command);
void ReverseCompiler (FILE* inputFile, FILE* outputFile);
int CheckStackSizeForOperation (struct Stack* myStack);
int GenerateCodeFromInput (FILE* inputFile, char* codeArray, FILE* outputfile);

void CheckingSignatureAndVersion (FILE* inputFile);
void CommandPrintout (int position, char* codeArray);
void PrintBinary (int position, char* codeArray);

int BinaryRecordind (int position, char* codeArray);

#endif
