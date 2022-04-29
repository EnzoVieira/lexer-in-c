#ifndef TOKEN_h
#define TOKEN_h

typedef enum
{
    STRING,
    ARRAY,
    BLOCK,
    VAR_DEF,
    VAR,
    NUM,
    CONVERSOR,
    IO_OPERATOR,
    OPERATOR
} InstructionType;

typedef struct SToken
{
    char *instruction;
    char firstChar;
    InstructionType type;
} Token;

Token *createNewToken(char *instruction, char firstChar, InstructionType type);

#endif