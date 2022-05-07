typedef enum
{
    INT,      // 0
    DOUBLE,   // 1
    OPERATOR, // 2
    ARRAY,    // 3
    STRING,   // 4
    BLOCK     // 5
} TYPE;

typedef struct SToken
{
    char *instruction;
    TYPE type;
} Token;

typedef struct STokenSequence
{
    Token *tokenSequence;
} TokenSequence;

Token *createNewToken(TYPE type, char *instruction)
{
    Token *t = (Token *)calloc(1, sizeof(Token));

    t->instruction = instruction;
    t->type = type;

    return t;
}

TokenSequence *createNewTokenSequence()
{
    TokenSequence *ts = (TokenSequence *)calloc(1, sizeof(TokenSequence));

    ts->tokenSequence = (Token *)calloc(1, sizeof(Token));

    return ts;
}