#ifndef COMPILER_H
#define COMPILER_H

#include "library/base.h"
#include "library/string.h"

typedef struct
{
    char Source[Kilobytes(64)];
    uptr SourceIndex;
} compiler;

#endif