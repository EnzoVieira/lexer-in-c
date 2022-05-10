#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "token.c"
#include "lexer.c"
#include "parser.c"

int main()
{
    char *str = calloc(1000, sizeof(char));

    if (!fgets(str, 1000, stdin))
    {
        return 1;
    }

    Lexer *lexer = createNewLexer(str);

    // Ler input
    while (strlen(lexer->contents) - 1)
    {
        // Gera um novo token para cada elemento no input
        Token *token = getNextInstuctionToken(lexer);
        printToken(token);

        parserParse(token, lexer);

        // Ignora todos os whitespaces entre os elementos do input
        skipWhitespaces(lexer);
    }

    return 0;
}