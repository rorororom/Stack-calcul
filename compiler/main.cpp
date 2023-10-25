#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../common/log_funcs.h"
#include "../common/const.h"

#include "read_file_in_buffer.h"
#include "compiler.h"

int main ()
{
    OpenLogFile ("LOGE.log", "w");

    struct Compiler source = {
        "../assets/commands.txt",
        NULL,
        NULL,
        NULL,
        0,
        0,
        NULL,
        0,
        NULL,
        0
    };

    MainFuncReadFile(&source);

    PrintTextArray(&source);

    FILE* outputfile = fopen ("../assets/machine_code.txt", "w");
    if (ValidationFile(outputfile) != 0)
    {
        return 1;
    }

    int* codeRegister = (int*)calloc (MAX_SIZE_REG, sizeof (char));

    GenerateCodeFromInput (&source, outputfile);

    CommandPrintout (&source);

    BinaryRecordind (&source);

    fclose (outputfile);

    DestroyCompiler(&source);
    return 0;
}





















// void ReverseCompiler (FILE* inputFile, FILE* outputFile)
// {
//     int code, value;
//
//     while (fscanf (inputFile, "%d", &code) != EOF) {
//         switch (code) {
//             case CMD_PUSH:
//                 if (fscanf (inputFile, "%d", &value) != EOF)
//                 {
//                     fprintf (outputFile, "push  %d\n", value);
//                 }
//                 break;
//             case CMD_ADD:
//                 fprintf (outputFile, "add\n");
//                 break;
//             case CMD_SUB:
//                 fprintf (outputFile, "sub\n");
//                 break;
//             case CMD_MUL:
//                 fprintf (outputFile, "mul\n");
//                 break;
//             case CMD_DIV:
//                 fprintf (outputFile, "div\n");
//                 break;
//             case CMD_SQRT:
//                 fprintf (outputFile, "sqwrt\n");
//                 break;
//             case CMD_SIN:
//                 fprintf (outputFile, "sin\n");
//                 break;
//             case CMD_COS:
//                 fprintf (outputFile, "cos\n");
//                 break;
//             case CMD_OUT:
//                 fprintf (outputFile, "out\n");
//                 break;
//             case CMD_HLT:
//                 fprintf (outputFile, "hlt\n");
//                 break;
//             default:
//                 fprintf (outputFile, "unknown\n");
//                 break;
//         }
//     }
// }

