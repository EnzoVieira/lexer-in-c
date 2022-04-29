#include "./include/lexer.h"

#include "./token.c"

Lexer *createNewLexer(char *contents)
{
    Lexer *newLexer = calloc(1, sizeof(Lexer));

    newLexer->contents = contents;
    newLexer->firstChar = contents[0];

    return newLexer;
}

void avanceLexer(Lexer *lexer)
{
    lexer->contents += 1;
}

// Avança até a próxima instrução no input
void nextInstruction(Lexer *lexer)
{
    if (lexer->contents[0] != '\0' && strlen(lexer->contents) - 1)
    {
        lexer->contents += 1;

        // Ignora todos os espaços vazios
        while (lexer->contents[0] == ' ')
        {
            lexer->contents += 1;
        }
    }
}

char *getInstruction(Lexer *lexer)
{
    char *instruction = calloc(1, sizeof(char));
    instruction[0] = '\0';

    if (lexer->contents[0] != '\0' && lexer->contents[0] != 10)
    {
        lexer->firstChar = lexer->contents[0];

        // Ler uma string
        if (lexer->contents[0] == '"')
        {
            avanceLexer(lexer);

            while (lexer->contents[0] != '"' && strlen(lexer->contents) - 1)
            {
                char *tmp = calloc(2, sizeof(char));
                tmp[0] = lexer->contents[0];
                tmp[1] = '\0';

                instruction = realloc(instruction, (strlen(instruction) + strlen(tmp) + 1) * sizeof(char));

                strcat(instruction, tmp);

                avanceLexer(lexer);
            }
        }

        // Ler um array
        else if (lexer->contents[0] == '[')
        {
            int braces = 1, isFirst = 1;

            // avanceLexer(lexer);

            // while (lexer->contents[0] != ']' && strlen(lexer->contents) - 1)
            while (braces > 0 && strlen(lexer->contents) - 1)
            {
                char *tmp = calloc(2, sizeof(char));
                tmp[0] = lexer->contents[0];
                tmp[1] = '\0';

                instruction = realloc(instruction, (strlen(instruction) + strlen(tmp) + 1) * sizeof(char));

                strcat(instruction, tmp);

                if (lexer->contents[0] == '[')
                {
                    braces += isFirst ? 0 : 1;
                }

                if (lexer->contents[0] == ']')
                {
                    braces -= 1;
                }

                avanceLexer(lexer);

                isFirst = 0;
            }
        }

        // Ler um bloco
        else if (lexer->contents[0] == '{')
        {
            int braces = 1, isFirst = 1;

            // while (lexer->contents[0] != '}' && strlen(lexer->contents) - 1)
            while (braces > 0 && strlen(lexer->contents) - 1)
            {
                if (lexer->contents[0] == '{' || lexer->contents[0] == '[')
                {
                    braces += isFirst ? 0 : 1;
                }

                if (lexer->contents[0] == '}' || lexer->contents[0] == ']')
                {
                    braces -= 1;
                }

                char *tmp = calloc(2, sizeof(char));
                tmp[0] = lexer->contents[0];
                tmp[1] = '\0';

                instruction = realloc(instruction, (strlen(instruction) + strlen(tmp) + 1) * sizeof(char));

                strcat(instruction, tmp);

                avanceLexer(lexer);

                isFirst = 0;
            }
        }

        // Outra coisa qualquer
        else
        {
            while (lexer->contents[0] != ' ' && strlen(lexer->contents) - 1)
            {
                char *tmp = calloc(2, sizeof(char));
                tmp[0] = lexer->contents[0];
                tmp[1] = '\0';

                instruction = realloc(instruction, (strlen(instruction) + strlen(tmp) + 1) * sizeof(char));

                strcat(instruction, tmp);

                avanceLexer(lexer);
            }
        }
    }

    lexer->currentInstruction = instruction;
    return instruction;
}

void handleLexer(Lexer *input)
{
    while (strlen(input->contents) - 1)
    {
        Token *token = createNewToken(getInstruction(input), input->firstChar, ARRAY);

        printf("INSTRUCTION ( %s, %s )\n", token->instruction, parseInstruction(token));

        nextInstruction(input);
    }
}