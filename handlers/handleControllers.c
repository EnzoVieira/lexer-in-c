#include "../include/token.h"

int mathControllers(Token *token)
{
    int was_used = 1;

    if (token->firstChar == '+')
    {
        printf("sum(stk);");
    }
    else if (token->firstChar == '-')
    {
        printf("sub(stk);");
    }
    else if (token->firstChar == '*')
    {
        printf("mult(stk);");
    }
    else if (token->firstChar == '/')
    {
        printf("divide(stk);");
    }
    else if (token->firstChar == ')')
    {
        printf("inc(stk);");
    }
    else if (token->firstChar == '(')
    {
        printf("dec(stk);");
    }
    else if (token->firstChar == '%')
    {
        printf("mod(stk);");
    }
    else if (token->firstChar == '#')
    {
        printf("expo(stk);");
    }
    else
        was_used = 0;

    return was_used;
}

void logicControllers(Token *token)
{
    if (strcmp(token->instruction, "e>") == 0)
    {
        printf("eMoreThen(stk);");
    }
}

void operatorsControllers(Token *token)
{
    if (!mathControllers(token))
    {
        logicControllers(token);
    }

    printf("\n");
}