#ifndef COMPILER_H
#define COMPILER_H

#include "library/base.h"
#include "library/string.h"
#include "library/platform.h"

typedef struct
{
    char SourceName[100];
    char Source[Kilobytes(64)];
    uptr SourceIndex;
} compiler;

#endif