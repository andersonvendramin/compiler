#ifndef COMPILER_H
#define COMPILER_H

#include "library/base.h"
#include "library/string.h"
#include "library/platform.h"

#include "lexical_analysis.h"

typedef struct
{
    char SourceName[100];
    char Source[Kilobytes(64)];
    uptr SourceIndex;
    token *Token;
    uptr TokenCount;
    uptr TokenIndex;
} compiler;

#include "lexical_analysis.c"
#include "syntax_analysis.c"

#endif