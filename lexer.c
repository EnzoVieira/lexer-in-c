typedef struct SLexer
{
    char *contents;
} Lexer;

Lexer *createNewLexer(char *contents)
{
    Lexer *l = (Lexer *)calloc(1, sizeof(Lexer));

    l->contents = contents;

    return l;
}

// Avança o lexer em uma unidade
void advanceLexer(Lexer *l)
{
    l->contents++;
}

// Ignora todos os espaços vazios
void skipWhitespaces(Lexer *l)
{
    while (l->contents[0] == ' ')
    {
        advanceLexer(l);
    }
}

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

void getInstructionToken(char *instruction)
{
    Token *newToken = createNewToken(0, instruction);

    if (instruction[0] == '[')
    {
        printf("ARRAY %s\n", instruction);
        newToken->type = ARRAY;
    }
    else if (instruction[0] == '{')
    {
        newToken->type = BLOCK;
    }
    else if (hasDigit(instruction))
    {
        long unsigned i = 0;
        while (instruction[i] != '.' && strlen(instruction) > i)
        {
            i++;
        }

        if (instruction[i] == '\0')
        {
            newToken->type = INT;
        }
        else
        {
            newToken->type = DOUBLE;
        }
    }
    else
    {
        newToken->type = STRING;
    }

    printf("TOKEN (%d, %s)\n", newToken->type, newToken->instruction);
}

// Separa os elemtos do input
void getNextInstuctionToken(Lexer *l)
{
    char *instruction = calloc(1, sizeof(char));
    instruction[0] = '\0';

    // Ler um array
    if (l->contents[0] == '[')
    {
        int braces = 1, isFirst = 1;

        while (braces > 0 && strlen(l->contents) - 1)
        {
            char *tmp = calloc(2, sizeof(char));
            tmp[0] = l->contents[0];
            tmp[1] = '\0';

            instruction = realloc(instruction, (strlen(instruction) + strlen(tmp) + 1) * sizeof(char));

            strcat(instruction, tmp);

            if (l->contents[0] == '[')
            {
                braces += isFirst ? 0 : 1;
            }

            if (l->contents[0] == ']')
            {
                braces -= 1;
            }

            advanceLexer(l);

            isFirst = 0;
        }
    }

    // Ler uma string
    else if (l->contents[0] == '"')
    {
        advanceLexer(l);

        while (l->contents[0] != '"')
        {
            char *tmp = calloc(2, sizeof(char));
            tmp[0] = l->contents[0];
            tmp[1] = '\0';

            instruction = realloc(instruction, (strlen(instruction) + strlen(tmp) + 1) * sizeof(char));

            strcat(instruction, tmp);

            advanceLexer(l);
        }

        advanceLexer(l);
    }
    // Ler um bloco
    else if (l->contents[0] == '{')
    {
        int braces = 1, isFirst = 1;

        while (braces > 0 && strlen(l->contents) - 1)
        {
            if (l->contents[0] == '{' || l->contents[0] == '[')
            {
                braces += isFirst ? 0 : 1;
            }

            if (l->contents[0] == '}' || l->contents[0] == ']')
            {
                braces -= 1;
            }

            char *tmp = calloc(2, sizeof(char));
            tmp[0] = l->contents[0];
            tmp[1] = '\0';

            instruction = realloc(instruction, (strlen(instruction) + strlen(tmp) + 1) * sizeof(char));

            strcat(instruction, tmp);

            advanceLexer(l);

            isFirst = 0;
        }
    }
    // Ler qualquer outra coisa
    else
    {
        while (l->contents[0] != ' ' && strlen(l->contents) - 1)
        {
            char *tmp = calloc(2, sizeof(char));
            tmp[0] = l->contents[0];
            tmp[1] = '\0';

            instruction = realloc(instruction, (strlen(instruction) + strlen(tmp)) * sizeof(char));

            strcat(instruction, tmp);

            advanceLexer(l);
        }
    }

    getInstructionToken(instruction);
}
