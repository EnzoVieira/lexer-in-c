#include "./include/lexer.h"
#include "./include/token.h"

#include "./handlers/handleControllers.c"

int hasDigit(char instruction[])
{
    while (strlen(instruction))
    {
        // Retorna imediatamente se encontrar um dígito de 0 a 9
        if (isdigit(instruction[0]))
            return 1;

        instruction++;
    }

    return 0;
}

int isConversor(char instruction[])
{
    // Retorna imediatamente se encontrar conversor
    if (instruction[0] == 'f' || instruction[0] == 'i' || instruction[0] == 'c')
        return 1;

    return 0;
}

int isIOOperand(char instruction[])
{
    // Retorna imediatamente se encontrar conversor
    if (instruction[0] == 'l' || instruction[0] == 'p' || instruction[0] == 't')
        return 1;

    return 0;
}

char *parseInstruction(Token *token)
{
    if (token->firstChar == '"')
    {
        return "String";
    }
    else if (token->firstChar == '[')
    {
        return "Array";
    }
    else if (token->firstChar == '{')
    {
        return "Bloco";
    }
    else if (token->firstChar == ':')
    {
        return "Definição Variável";
    }
    else if (isupper(token->firstChar))
    {
        return "Variável";
    }
    else if (hasDigit(token->instruction))
    {
        printf("AQUI %s", token->instruction);
        int i = 0;
        while (strlen(token->instruction) - 1)
        {
            if (token->instruction[i] == '.')
                return "Double";

            i++;
        }

        return "Inteiro";
    }
    else if (isConversor(token->instruction))
    {
        return "Conversor";
    }
    else if (isIOOperand(token->instruction))
    {
        return "Operador I/O";
    }

    operatorsControllers(token);
    return "Operador";
}