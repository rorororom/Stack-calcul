#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cpu.h"
#include "compiler.h"
#include "log_funcs.h"

int Compiler(struct Cpu* myCpu)
{
    FILE* inputFile = fopen("commands.txt", "r");
    if (inputFile == NULL) {
        perror("Не удается открыть файл");
        return 1;
    }

    myCpu->outputfile = fopen(myCpu->filename, "w");
    if (myCpu->outputfile == NULL) {
        return 1;
    }

    char command[256] = "";
    char arg_command[256] = "";
    int value = 0;

    myCpu -> codeArray = (char*)calloc(MAXSIZE, sizeof(char));
    int position = 0;

    if (fscanf(inputFile, "%s", command) != EOF && strcmp(command, "moss") != 0)
    {
        printf ("НЕ ТВОЙ ИСХОДНИК\n");
        return -1;
    }

    if (fscanf(inputFile, "%s", command) != EOF && strcmp(command, "VERSION2") != 0)
    {
        printf ("НЕ ТА ВЕРСИЯ\n");
        return -1;
    }


    while (fscanf(inputFile, "%s", command) != EOF)
    {
        int code = CommandToCode(command);

        if (code == PUSH && fscanf(inputFile, "%d", &value) != EOF)
        {
            myCpu -> codeArray[position++] = code;
            myCpu -> codeArray[position++] = value;
            fprintf(myCpu->outputfile, "%d  ", code);
            fprintf(myCpu->outputfile, "%d\n", value);
        }
        else if (code == PUSH_R && fscanf(inputFile, "%s", arg_command) != EOF)
        {
            int argCode = CommandToCode(arg_command);
            myCpu -> codeArray[position++] = code;
            myCpu -> codeArray[position++] = argCode;
            fprintf(myCpu->outputfile, "%d  ", code);
            fprintf(myCpu->outputfile, "%d\n", argCode);
        }
        else if (code == IN)
        {
            printf("Введите число\n");
            if (scanf("%d", &value))
                StackPush(&myCpu->myStack, value);
        }
        else if (code == POP && fscanf(inputFile, "%s", arg_command) != EOF)
        {
            int argCode = CommandToCode(arg_command);
            PopArg(myCpu, argCode);
        }
        else
        {
            myCpu -> codeArray[position++] = code;
            fprintf(myCpu->outputfile, "%d\n", code);
        }
    }

    fprintf(LOG_FILE, "МАССИВ КОМАНД\n");
    for(int i = 0; i < position; i++)
    {
        fprintf(LOG_FILE, "%d - %d\n", i, myCpu -> codeArray[i]);
    }

    BinaryRecordind (position, myCpu);

    fclose(myCpu->outputfile);

    myCpu->outputfile = fopen("machine_code.txt", "r");
    if (myCpu->outputfile == NULL) {
        return 1;
    }

    return position;
}

int CommandToCode(const char* command)
{
    if (strcmp (command, "push") == 0) return PUSH;
    if (strcmp (command, "sub")  == 0) return SUB;
    if (strcmp (command, "add")  == 0) return ADD;
    if (strcmp (command, "mul")  == 0) return MUL;
    if (strcmp (command, "div")  == 0) return DIV;
    if (strcmp (command, "sqrt") == 0) return SQRT;
    if (strcmp (command, "sin")  == 0) return SIN;
    if (strcmp (command, "cos")  == 0) return COS;
    if (strcmp (command, "out")  == 0) return OUT;
    if (strcmp (command, "hlt")  == 0) return HLT;
    if (strcmp (command, "push_r")  == 0) return PUSH_R;
    if (strcmp (command, "in")  == 0) return IN;
    if (strcmp (command, "pop")  == 0) return POP;
    if (strcmp (command, "rcx")  == 0) return RCX;
    if (strcmp (command, "rax")  == 0) return RAX;
    if (strcmp (command, "rbx")  == 0) return RBX;

    return 0;
}

void ReverseCompiler(FILE* inputFile, FILE* outputFile)
{
    int code, value;

    while (fscanf(inputFile, "%d", &code) != EOF) {
        switch (code) {
            case PUSH:
                if (fscanf(inputFile, "%d", &value) != EOF)
                {
                    fprintf(outputFile, "push  %d\n", value);
                }
                break;
            case ADD:
                fprintf(outputFile, "add\n");
                break;
            case SUB:
                fprintf(outputFile, "sub\n");
                break;
            case MUL:
                fprintf(outputFile, "mul\n");
                break;
            case DIV:
                fprintf(outputFile, "div\n");
                break;
            case SQRT:
                fprintf(outputFile, "sqwrt\n");
                break;
            case SIN:
                fprintf(outputFile, "sin\n");
                break;
            case COS:
                fprintf(outputFile, "cos\n");
                break;
            case OUT:
                fprintf(outputFile, "out\n");
                break;
            case HLT:
                fprintf(outputFile, "hlt\n");
                break;
            default:
                fprintf(outputFile, "unknown\n");
                break;
        }
    }
}

void CpuCtor (struct Cpu* myCpu, struct Stack* myStack)
{
    myCpu->myStack = *myStack;

    myCpu->rax = 0;
    myCpu->rbx = 0;
    myCpu->rcx = 0;
    myCpu->rdx = 0;

    myCpu->filename = "machine_code.txt";
    myCpu->outputfile = NULL;
}

void CpuDtor (struct Cpu* myCpu)
{
    StackDtor(&myCpu->myStack);

    myCpu->rax = 0;
    myCpu->rbx = 0;
    myCpu->rcx = 0;
    myCpu->rdx = 0;

    myCpu->filename = NULL;
    myCpu->outputfile = NULL;
}

int BinaryRecordind (int position, struct Cpu* myCpu)
{
    FILE* file = fopen("code2.bin", "wb");

    if (file == NULL) {
        perror("Не удается открыть файл");
        return 1;
    }
    size_t elements_written = fwrite(myCpu -> codeArray, sizeof(uint8_t), position, file);

    if (elements_written != position) {
        perror("Ошибка при записи в файл");
        fclose(file);
        return 1;
    }

    fclose(file);

    file = fopen("code2.bin", "rb");

    fprintf (LOG_FILE, "ИЗ ДВОИЧНОГО ФАЙЛА\n");
    for (int i = 0; i < position; i++)
    {
        fprintf(LOG_FILE, "%d - %08X\n", i, myCpu -> codeArray[i]);
    }

    fclose(file);

    return 0;
}
