#include "lexical_analysis.h"

static token *LexicalAnalysis(compiler *Compiler, uptr *TokenCount)
{
    token *Result = 0;

    int Capacity = 1;
    *TokenCount = 0;

    if(!PlatformAllocateMemory(&Result, Capacity * sizeof(token)))
    {
        return Result;
    }

    for(char *c = Compiler->Source; *c != '\0';)
    {
        if(*TokenCount >= Capacity)
        {
            Capacity *= 2;

            if(!PlatformReallocateMemory(&Result, Capacity * sizeof(token), (Capacity / 2) * sizeof(token)))
            {
                return Result;
            }
        }

        while(StringIsSpace(*c))
        {
            c++;
        }

        if(*c == '\0')
        {
            break;
        }

        if(StringIsDigit(*c))
        {
            Result[*TokenCount].Type = TOKEN_NUMBER;
            
            while(StringIsDigit(*c))
            {
                Result[*TokenCount].Value = (Result[*TokenCount].Value * 10) + (*c - '0');
                c++;
            }

            (*TokenCount)++;
        }
        else if(StringIsLetter(*c))
        {
            Result[*TokenCount].Type = TOKEN_IDENTIFIER;
            
            for(uptr Index = 0; StringIsDigit(*c) || StringIsLetter(*c) || (*c == '_'); Index++)
            {
                Result[*TokenCount].Identifier[Index] = *c++;
            }

            (*TokenCount)++;
        }
        else if(*c == '+')
        {
            Result[(*TokenCount)++].Type = TOKEN_PLUS;
            c++;
        }
        else if(*c == '-')
        {
            Result[(*TokenCount)++].Type = TOKEN_MINUS;
            c++;
        }
        else if(*c == '*')
        {
            Result[(*TokenCount)++].Type = TOKEN_STAR;
            c++;
        }
        else if(*c == '/')
        {
            Result[(*TokenCount)++].Type = TOKEN_SLASH;
            c++;
        }
        else if(*c == '(')
        {
            Result[(*TokenCount)++].Type = TOKEN_LEFT_PARENTHESES;
            c++;
        }
        else if(*c == ')')
        {
            Result[(*TokenCount)++].Type = TOKEN_RIGHT_PARENTHESES;
            c++;
        }
        else
        {
            Log("Unknown token: %c\n", *c);
            return Result;
        }
    }

    return Result;
}