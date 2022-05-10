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
    // Array de instruções
    Token *tokenSequence;
    // Capacidade de alocação em memória
    int size;
    // Quantidade de instruções já alocadas
    int instructionsQuantity;
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
    ts->size = 1;
    ts->instructionsQuantity = 0;

    return ts;
}

void reallocMemory(TokenSequence *ts)
{
    void *temp = realloc(ts->tokenSequence, ((ts->size * 2) * sizeof(Token)));

    if (temp == 0)
    {
        printf("Falha ao realocar a memória.\n");
    }
    else
    {
        ts->tokenSequence = temp;
    }

    ts->size *= 2;
}

void pushInstruction(Token *t, TokenSequence *ts)
{
    if (ts->instructionsQuantity == ts->size - 1)
    {
        reallocMemory(ts);
    }

    ts->tokenSequence[ts->instructionsQuantity] = *t;
    ts->instructionsQuantity++;
}