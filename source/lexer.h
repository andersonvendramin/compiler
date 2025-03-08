#ifndef LEXER_H
#define LEXER_H

#include "library/base.h"
#include "library/platform.h"

typedef enum
{
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_LEFT_PARENTHESES,
    TOKEN_RIGHT_PARENTHESES,
} token_type;

typedef struct
{
    token_type Type;
    f64 Value;
    char Identifier[100];
} token;

#endif