void printToken(Token *token)
{
    // Apenas para teste
    char *enumNames[] = {"INT", "DOUBLE", "OPERATOR", "ARRAY", "STRING", "BLOCK"};

    printf("TOKEN (%s, %s)", enumNames[token->type], token->instruction);
}

void printTokenSequence(TokenSequence *tokenSequence)
{
    int i = 0;
    for (i = 0; i < tokenSequence->instructionsQuantity; i++)
    {
        Token *t = &tokenSequence->tokenSequence[i];
        printToken(t);
        printf("\n");
    }
}

void parserParserBlock(Token *token)
{
    Lexer *lexer = createNewLexer(token->instruction);
    TokenSequence *ts = createNewTokenSequence();

    advanceLexer(lexer);

    int braces = 1;
    while (braces > 0 && strlen(lexer->contents) - 1)
    {
        Token *t = getNextInstuctionToken(lexer);

        pushInstruction(t, ts);

        if (lexer->contents[0] == '{')
        {
            braces += 1;
        }

        if (lexer->contents[0] == '}')
        {
            braces -= 1;
        }

        advanceLexer(lexer);
    }

    printTokenSequence(ts);
}

void parserParse(Token *token, Lexer *lexer)
{
    if (token->type == INT)
    {
        printf(" - Adiciona inteiro no array\n");
    }
    else if (token->type == DOUBLE)
    {
        printf(" - Adiciona double no array\n");
    }
    else if (token->type == OPERATOR)
    {
        printf(" - Executa operador\n");
    }
    else if (token->type == ARRAY)
    {
        printf(" - Adiciona array na stack\n");
    }
    else if (token->type == STRING)
    {
        printf(" - Adiciona string na stack\n");
    }
    else if (token->type == BLOCK)
    {
        // Cria uma sequencia de instruções (TOKENS) e adiciona-os na stack
        printf(" - Adiciona Lambda Function na stack\n");
        parserParserBlock(token);
    }
}