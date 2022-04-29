#include "./include/token.h"

Token *createNewToken(char *instruction, char firstChar, InstructionType type)
{
    Token *newToken = calloc(1, sizeof(Token));

    newToken->instruction = instruction;
    newToken->firstChar = firstChar;
    newToken->type = type;

    return newToken;
}