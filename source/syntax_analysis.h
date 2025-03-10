#ifndef SYNTAX_ANALYSIS_H
#define SYNTAX_ANALYSIS_H

#include "library/base.h"
#include "library/platform.h"

typedef enum
{
    AST_INVALID,
    AST_NUMBER,
    AST_ADD,
    AST_SUBTRACT,
    AST_MULTIPLY,
    AST_DIVIDE,
} ast_type;

typedef struct
{
    ast_type Type;
    f64 Value;
    struct ast *Left;
    struct ast *Right;
} ast;

#endif