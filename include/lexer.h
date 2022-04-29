#ifndef LEXER_h
#define LEXER_h

typedef struct SLexer
{
    char *contents;
    char firstChar;
    char *currentInstruction;
} Lexer;

Lexer *createNewLexer(char *contents);
void avanceLexer(Lexer *lexer);
void nextInstruction(Lexer *lexer);
char *getInstruction(Lexer *lexer);
void handleLexer(Lexer *input);

#endif