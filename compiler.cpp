#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "creator_cpu.h"
#include "compiler.h"
#include "log_funcs.h"

int Compiler ()
{
    FILE* inputFile = fopen ("commands.txt", "r");
    if (inputFile == NULL) {
        perror ("Не удается открыть файл");
        return 1;
    }

    FILE* outputfile = fopen ("machine_code.txt", "w");
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

    outputfile = fopen ("machine_code.txt", "r");
    if (outputfile == NULL) {
        return 1;
    }

    return 0;
}

int GenerateCodeFromInput (FILE* inputFile, char* codeArray, FILE* outputfile)
{
    char command[256] = "";
    char arg_command[256] = "";
    int value = 0;

    int position = 0;
    int argCode = 0;

    while (fscanf (inputFile, "%s", command) != EOF)
    {
        int code = CommandToCode (command);

        if (code == PUSH)
        {
            if (fscanf(inputFile, "%d", &value) == 1)
            {
                fprintf (outputfile, "%d %d\n", ((1 << 4) | PUSH), value);
                codeArray[position++] = (1 << 4) | PUSH;
                codeArray[position++] = value;
            }
            else if (fscanf(inputFile, "%s", arg_command) == 1)
            {
                argCode = CommandToCode (arg_command);

                fprintf (outputfile, "%d %d\n", ((1 << 5) | PUSH), argCode);
                codeArray[position++] = (1 << 5) | PUSH;
                codeArray[position++] = argCode;
            }
        }
        else if (code == IN)
        {
            codeArray[position++] = code;
            fprintf (outputfile, "%d\n", code);
        }
        else if (code == POP && fscanf (inputFile, "%s", arg_command) != EOF)
        {
            argCode = CommandToCode (arg_command);
            ADD_CODE_VALUE (codeArray, position, code, argCode, outputfile);
        }
        else
        {
            codeArray[position++] = code;
            fprintf (outputfile, "%d\n", code);
        }
    }

    return position;
}

int CommandToCode (const char* command)
{
    if (strcmp (command, "push")    == 0) return PUSH;
    if (strcmp (command, "sub")     == 0) return SUB;
    if (strcmp (command, "add")     == 0) return ADD;
    if (strcmp (command, "mul")     == 0) return MUL;
    if (strcmp (command, "div")     == 0) return DIV;
    if (strcmp (command, "sqrt")    == 0) return SQRT;
    if (strcmp (command, "sin")     == 0) return SIN;
    if (strcmp (command, "cos")     == 0) return COS;
    if (strcmp (command, "out")     == 0) return OUT;
    if (strcmp (command, "hlt")     == 0) return HLT;
    if (strcmp (command, "in")      == 0) return IN;
    if (strcmp (command, "pop")     == 0) return POP;
    if (strcmp (command, "rcx")     == 0) return RCX;
    if (strcmp (command, "rax")     == 0) return RAX;
    if (strcmp (command, "rbx")     == 0) return RBX;

    return 0;
}

void ReverseCompiler (FILE* inputFile, FILE* outputFile)
{
    int code, value;

    while (fscanf (inputFile, "%d", &code) != EOF) {
        switch (code) {
            case PUSH:
                if (fscanf (inputFile, "%d", &value) != EOF)
                {
                    fprintf (outputFile, "push  %d\n", value);
                }
                break;
            case ADD:
                fprintf (outputFile, "add\n");
                break;
            case SUB:
                fprintf (outputFile, "sub\n");
                break;
            case MUL:
                fprintf (outputFile, "mul\n");
                break;
            case DIV:
                fprintf (outputFile, "div\n");
                break;
            case SQRT:
                fprintf (outputFile, "sqwrt\n");
                break;
            case SIN:
                fprintf (outputFile, "sin\n");
                break;
            case COS:
                fprintf (outputFile, "cos\n");
                break;
            case OUT:
                fprintf (outputFile, "out\n");
                break;
            case HLT:
                fprintf (outputFile, "hlt\n");
                break;
            default:
                fprintf (outputFile, "unknown\n");
                break;
        }
    }
}

int BinaryRecordind (int position, char* codeArray)
{
    FILE* file = fopen ("code2.bin", "wb");

    if (file == NULL) {
        perror ("Не удается открыть файл");
        return 1;
    }

    size_t elements_written1 = fwrite (&position, sizeof (int), 1, file);
    if (elements_written1 != 1)
    {
        perror ("Ошибка при записи в файл");
        fclose (file);
        return 1;
    }

    size_t elements_written = fwrite (codeArray, sizeof (uint8_t), position, file);

    if (elements_written != position) {
        perror ("Ошибка при записи в файл");
        fclose (file);
        return 1;
    }

    fclose (file);

    file = fopen ("code2.bin", "rb");

    fprintf (LOG_FILE, "ИЗ ДВОИЧНОГО ФАЙЛА\n");
    for (int i = 0; i < position; i++)
    {
        fprintf (LOG_FILE, "%d - %08X\n", i, codeArray[i]);
    }

    fclose (file);

    return 0;
}

void CheckingSignatureAndVersion (FILE* inputFile)
{
    char command[256] = "";

    if (fscanf (inputFile, "%s", command) != EOF && strcmp (command, "moss") != 0)
    {
        printf ("НЕ ТВОЙ ИСХОДНИК\n");
        exit (1);
    }

    if (fscanf (inputFile, "%s", command) != EOF && strcmp (command, "VERSION2") != 0)
    {
        printf ("НЕ ТА ВЕРСИЯ\n");
        exit (1);
    }
}

