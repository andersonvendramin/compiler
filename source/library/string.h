#ifndef STRING_H
#define STRING_H

#include "base.h"

#ifdef _WIN32
    #ifdef STRING_IMPORT
        #define STRING_API __declspec(dllimport)
    #else
        #define STRING_API __declspec(dllexport)
    #endif
#else
    #error
#endif

STRING_API bool StringIsDigit(int Character);
STRING_API uptr StringLength(char *String);
STRING_API uptr StringCopyCharacter(char *Buffer, uptr BufferSize, int Character);
STRING_API uptr StringCopyString(char *Buffer, uptr BufferSize, char *String, uptr Length, uptr Precision);
STRING_API uptr StringCopySignedInteger32(char *Buffer, uptr BufferSize, s32 Value, int Base, char *Representation);
STRING_API uptr StringCopyUnsignedInteger32(char *Buffer, uptr BufferSize, u32 Value, int Base, char *Representation);
STRING_API uptr StringCopySignedInteger64(char *Buffer, uptr BufferSize, s64 Value, int Base, char *Representation);
STRING_API uptr StringCopyUnsignedInteger64(char *Buffer, uptr BufferSize, u64 Value, int Base, char *Representation);
STRING_API uptr StringCopyFloat64(char *Buffer, uptr BufferSize, f64 Value, int Precision);

#endif