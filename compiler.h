#define ADD_CODE_VALUE(arr, pos, code, value, file)     \
    do {                                                \
        (arr)[(pos)++] = (code);                        \
        (arr)[ (pos)++] = (value);                       \
        fprintf ( (file), "%d  %d\n", (code), (value));   \
    } while (0)


int Compiler ();
int CommandToCode (const char* command);
void ReverseCompiler (FILE* inputFile, FILE* outputFile);
int CheckStackSizeForOperation (struct Stack* myStack);
int GenerateCodeFromInput (FILE* inputFile, char* codeArray, FILE* outputfile);

void CheckingSignatureAndVersion (FILE* inputFile);

int BinaryRecordind (int position, char* codeArray);

