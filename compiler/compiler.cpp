#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../common/log_funcs.h"
#include "../cpu/creator_cpu.h"

#include "compiler.h"

#define DEF_CMD(name, code, has_arg_push, has_arg_pop, ...)                      \
    if (strcmp(command, #name) == 0) {                                      \
        cmd = code;                                                         \
        if (has_arg_push) {                                                 \
            if(fscanf(inputFile, "%d", &value) == 1) {                      \
                argCode = value;                                            \
                fprintf(outputfile, "%d %d\n", code, argCode);              \
                codeArray[position++] = code;                               \
                codeArray[position++] = argCode;                            \
            } else if(fscanf(inputFile, "%s", arg_command) == 1) {          \
                argCode = CommandToCodeArg(arg_command);                    \
                fprintf(outputfile, "%d %d\n", ((1 << 5) | code), argCode); \
                codeArray[position++] = ((1 << 5) | code);                  \
                codeArray[position++] = argCode;                            \
            }                                                               \
        } else if (has_arg_pop) {                                           \
            if (fscanf(inputFile, "%s", arg_command) != EOF) {              \
                argCode = CommandToCodeArg(arg_command);                    \
                fprintf(outputfile, "%d %d\n", code, argCode);              \
                codeArray[position++] = code;                               \
                codeArray[position++] = argCode;                            \
            }                                                               \
        } else {                                                            \
            codeArray[position++] = code;                                   \
            fprintf(outputfile, "%d\n", code);                              \
        }                                                                   \
    }

int GenerateCodeFromInput (FILE* inputFile, char* codeArray, FILE* outputfile)
{
    char command[256] = "";
    char arg_command[256] = "";
    int value = 0;

    int position = 0;
    int argCode = 0;
    int cmd = 0;

    while (fscanf(inputFile, "%s", command) != EOF)
    {
        #include "../common/commands.h"
    }
    #undef DEF_CMD

    return position;
}


void ReverseCompiler (FILE* inputFile, FILE* outputFile)
{
    int code, value;

    while (fscanf (inputFile, "%d", &code) != EOF) {
        switch (code) {
            case CMD_PUSH:
                if (fscanf (inputFile, "%d", &value) != EOF)
                {
                    fprintf (outputFile, "push  %d\n", value);
                }
                break;
            case CMD_ADD:
                fprintf (outputFile, "add\n");
                break;
            case CMD_SUB:
                fprintf (outputFile, "sub\n");
                break;
            case CMD_MUL:
                fprintf (outputFile, "mul\n");
                break;
            case CMD_DIV:
                fprintf (outputFile, "div\n");
                break;
            case CMD_SQRT:
                fprintf (outputFile, "sqwrt\n");
                break;
            case CMD_SIN:
                fprintf (outputFile, "sin\n");
                break;
            case CMD_COS:
                fprintf (outputFile, "cos\n");
                break;
            case CMD_OUT:
                fprintf (outputFile, "out\n");
                break;
            case CMD_HLT:
                fprintf (outputFile, "hlt\n");
                break;
            default:
                fprintf (outputFile, "unknown\n");
                break;
        }
    }
}

int CommandToCodeArg (const char* command)
{
    if (strcmp (command, "RCX")     == 0) return CMD_RCX;
    if (strcmp (command, "RAX")     == 0) return CMD_RAX;
    if (strcmp (command, "RBX")     == 0) return CMD_RBX;

    return 0;
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

    file = fopen ("../assets/code2.bin", "rb");

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

void CommandPrintout (int position, char* codeArray)
{
    fprintf (LOG_FILE, "МАССИВ КОМАНД\n");
    for (int i = 0; i < position; i++)
    {
        fprintf (LOG_FILE, "%d - %d\n", i, codeArray[i]);
    }
}

void PrintBinary (int position, char* codeArray)
{
    for (int i = 0; i < position; i++)
    {
        fprintf(LOG_FILE, "Address: %p, Value: %08X\n", (void*)&codeArray[i], (unsigned int)codeArray[i]);
    }
}

