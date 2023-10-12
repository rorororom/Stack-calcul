int SravnenieV1 (char string[], struct Stack* myStack)
{
    int value = 0;
    int number1 = 0;
    int number2 = 0;

    if (strcmp (string, "push") == 0)
    {
        scanf (FORMAT_SPECIFIER (value), &value);
        StackPush (myStack, value);
    }
    else if (strcmp (string, "add") == 0)
    {
        if (myStack->size < 2)
        {
            printf ("Ошибка: недостаточно элементов в стеке для выполнения операции sum.\n");
        }
        else
        {
            number1 = StackPop (myStack);
            number2 = StackPop (myStack);

            value = number2 + number1;

            StackPush (myStack, value);
        }
    }
    else if (strcmp (string, "sub") == 0)
    {
        if (myStack->size < 2)
        {
            printf ("Ошибка: недостаточно элементов в стеке для выполнения операции sub.\n");
        }
        else
        {
            number1 = StackPop (myStack);
            number2 = StackPop (myStack);

            value = number2 - number1;

            StackPush (myStack, value);
        }
    }
    else if (strcmp (string, "mul") == 0)
    {
        if (myStack->size < 2)
        {
            printf ("Ошибка: недостаточно элементов в стеке для выполнения операции sum.\n");
        }
        else
        {
            number1 = StackPop (myStack);
            number2 = StackPop (myStack);

            value = number2 * number1;

            StackPush (myStack, value);
        }
    }
    else if (strcmp (string, "sqrt") == 0)
    {
        if (myStack->size < 2)
        {
            printf ("Ошибка: недостаточно элементов в стеке для выполнения операции sum.\n");
        }
        else
        {
            number1 = StackPop (myStack);

            value = number1 * 0.5;

            StackPush (myStack, value);
        }
    }
    else if (strcmp (string, "sin") == 0)
    {
        if (myStack->size < 2)
        {
            printf ("Ошибка: недостаточно элементов в стеке для выполнения операции sum.\n");
        }
        else
        {
            number1 = StackPop (myStack);

            value = sin (number1);

            StackPush (myStack, value);
        }
    }
    else if (strcmp (string, "cos") == 0)
    {
        if (myStack->size < 2)
        {
            printf ("Ошибка: недостаточно элементов в стеке для выполнения операции sum.\n");
        }
        else
        {
            number1 = StackPop (myStack);

            value = cos (number1);

            StackPush (myStack, value);
        }
    }
    else if (strcmp (string, "out") == 0)
    {
        printf ("%d ", StackPop (myStack));
        printf ("\n");

        getchar ();
    }
    else if (strcmp (string, "div") == 0)
    {
        if (myStack->size < 2)
        {
            printf ("Ошибка: недостаточно элементов в стеке для выполнения операции div.\n");
        }
        else
        {
            number1 = StackPop (myStack);
            number2 = StackPop (myStack);

            if (number1 == 0)
            {
                printf ("Ошибка: деление на ноль недопустимо.\n");
                StackPush (myStack, number2);
                StackPush (myStack, number1);
            }
            else
            {
                value = number2 / number1;
                StackPush (myStack, value);
            }
        }

    }

    return 0;
}


// int PrintfStack (struct Stack* myStack)
// {
//     if (myStack->size > 0)
//         return myStack->data[myStack->size - 1];
//     else
//     {
//         printf ("Stack is empty\n");
//         return -1;
//     }
// }

// in
// pop rax
// in
// pop rbx
// in
// pop rcx
// push_r rbx
// push_r rbx
// mul
// push 4
// push_r rax
// push_r rcx
// mul
// mul
// sub
// out
// hlt

