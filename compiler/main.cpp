#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../common/log_funcs.h"

#include "compiler.h"

int main ()
{
    OpenLogFile ("LOGE.log", "w");

    FILE* inputFile = fopen ("../assets/commands.txt", "r");
    if (inputFile == NULL) {
        perror ("Не удается открыть файл\n");
        return 1;
    }

    printf ("adfg\n");

    FILE* outputfile = fopen ("../assets/machine_code.txt", "w");
    if (outputfile == NULL) {
        return 1;
    }

    char* codeArray = (char*)calloc (MAXSIZE, sizeof (char));
    int* codeRegister = (int*)calloc (MAX_SIZE_REG, sizeof (char));

    CheckingSignatureAndVersion (inputFile);

    int position = GenerateCodeFromInput (inputFile, codeArray, outputfile);

    CommandPrintout (position, codeArray);

    BinaryRecordind (position, codeArray);

    PrintBinary (position, codeArray);

    fclose (outputfile);

    outputfile = fopen ("../assets/machine_code.txt", "r");
    if (outputfile == NULL) {
        return 1;
    }

    return 0;
}