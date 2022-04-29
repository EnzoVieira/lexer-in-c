#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "./parser.c"
#include "./lexer.c"

int main()
{
    char *input = calloc(1000, sizeof(char));

    if (!fgets(input, 1000, stdin))
    {
        return 1;
    }

    handleLexer(createNewLexer(input));

    return 0;
}