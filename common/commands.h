DEF_CMD(PUSH,   1, 1, 0,
    {
        if((startCode & (1 << 5)) != 0)
        {
            i++;
            int code_arg = codeArray[i];
            StackPush(&myCpu->myStack, return_arg(myCpu, code_arg));
        }
        else
        {
            i++;
            value = codeArray[i];
            StackPush(&myCpu->myStack, value);
        }
    })
DEF_CMD(SUB,    2, 0, 0,
    {
        if (CheckStackSizeForOperation(&myCpu->myStack))
        {
            number1 = StackPop(&myCpu->myStack);
            number2 = StackPop(&myCpu->myStack);
            value = number2 - number1;
            StackPush(&myCpu->myStack, value);
        }
    })
DEF_CMD(ADD,    3, 0, 0,
    {
        if (CheckStackSizeForOperation(&myCpu->myStack))
        {
            number1 = StackPop(&myCpu->myStack);
            number2 = StackPop(&myCpu->myStack);
            value = number2 + number1;
            StackPush(&myCpu->myStack, value);
        }
    })
DEF_CMD(MUL,    4, 0, 0,
    {
        if (CheckStackSizeForOperation(&myCpu->myStack))
        {
            number1 = StackPop(&myCpu->myStack);
            number2 = StackPop(&myCpu->myStack);
            value = number2 * number1;
            StackPush(&myCpu->myStack, value);
        }
    })
DEF_CMD(DIV,    5, 0, 0,
    {
        if (CheckStackSizeForOperation(&myCpu->myStack))
        {
            number1 = StackPop(&myCpu->myStack);
            number2 = StackPop(&myCpu->myStack);

            if (number1 == 0)
            {
                printf("Ошибка: деление на ноль недопустимо.\n");
                StackPush(&myCpu->myStack, number2);
                StackPush(&myCpu->myStack, number1);
            }
            else
            {
                value = number2 / number1;
                StackPush(&myCpu->myStack, value);
            }
        }
    })
DEF_CMD(SQRT,   6, 0, 0,
    {
        if (CheckStackSizeForOperation(&myCpu->myStack))
        {
            number1 = StackPop(&myCpu->myStack);
            value = number1 * 0.5;
            StackPush(&myCpu->myStack, value);
        }
    })
DEF_CMD(SIN,    7, 0, 0,
    {
        if (CheckStackSizeForOperation(&myCpu->myStack))
        {
            number1 = StackPop(&myCpu->myStack);
            value = sin(number1);
             StackPush(&myCpu->myStack, value);
        }
    })
DEF_CMD(COS,    8, 0, 0,
    {
        if (CheckStackSizeForOperation(&myCpu->myStack))
        {
            number1 = StackPop(&myCpu->myStack);
            value = cos(number1);

            StackPush(&myCpu->myStack, value);
        }
    })
DEF_CMD(IN,     9, 0, 0,
    {
        printf("Введите число\n");
        scanf("%d", &value);
        StackPush(&myCpu->myStack, value);
    })
DEF_CMD(OUT,   10, 0, 0,
    {
        printf("answer = %d\n", StackPop(&myCpu->myStack));
    })
DEF_CMD(POP,   11, 0, 1,
    {
        i += 1;
        code_arg = codeArray[i];
        return_arg(myCpu, code_arg);
    })
DEF_CMD(MATAN, 12, 0, 0,
    {
        system ("say \" МНЕ НЕ НРАВИТСЯ МАТАН, КОМУ ОН ВООБЩЕ МОЖЕТ НРАВИТСЯ? ТОТ, КОМУ НРАВИТСЯ МАТАН - СТРАННЫЙ\" ");
    })
DEF_CMD(TG,    13, 0, 0,
    {
        value = sin(StackPop(&myCpu->myStack));
        StackPush(&myCpu->myStack, value);
    })
DEF_CMD(CTG,   14, 0, 0,
    {
        number1 = StackPop(&myCpu->myStack);
        value = cos(number1) /sin(number1);
        StackPush(&myCpu->myStack, value);
    })
DEF_CMD(POW,   15, 0, 0,
    {
        exponent = StackPop(&myCpu->myStack);
        base = StackPop(&myCpu->myStack);
        result = 1;
        for (int i = 0; i < exponent; i++)
        {
            result *= base;
        }
        StackPush(&myCpu->myStack, result);
    })
DEF_CMD(CAT,   18, 0, 0,
    {
        printf(" /\\_/\\  \n");
        printf("( o.o ) \n");
        printf(" > ^ <  \n");
        printf("  / | \\  \n");
        printf(" /  |  \\ \n");
        printf("  / \\   \n");
        printf(" /   \\  \n");
    })
DEF_CMD(SLEAP, 19, 0, 0,
    {
        system ("say \" ВОТ БЛИН, ПОРА СПАТЬ\" ");
    })
DEF_CMD(LOVE,  20, 0, 0,
    {
        system ("say \" Я ТЕБЯ ЛЮБЛЮ\" ");
    })
DEF_CMD(DOG,   21, 0, 0,
    {
        printf("   / \\__\n");
        printf("  (    @\\___\n");
        printf("  /         O\n");
        printf(" /   (_____/\n");
        printf(" /_____/   U\n");
    })
DEF_CMD(RAX,  101, 0, 0,
    {;})
DEF_CMD(RBX,  102, 0, 0,
    {;})
DEF_CMD(RCX,  103, 0, 0,
    {;})
DEF_CMD(HLT,   -1, 0, 0,
    {;})

