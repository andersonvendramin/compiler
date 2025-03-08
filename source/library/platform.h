#ifndef PLATFORM_H
#define PLATFORM_H

#include "base.h"

#ifdef _WIN32
    #ifdef PLATFORM_IMPORT
        #define PLATFORM_API __declspec(dllimport)
    #else
        #define PLATFORM_API __declspec(dllexport)
    #endif
#else
    #error
#endif

PLATFORM_API bool PlatformAllocateMemory(void **Memory, uptr Size);
PLATFORM_API bool PlatformFreeMemory(void **Memory);
PLATFORM_API bool PlatformGetFileSize(char *FileName, uptr *Size);
PLATFORM_API bool PlatformReadFile(char *FileName, void *Buffer, u32 BufferSize);
PLATFORM_API bool PlatformWriteFile(char *FileName, void *Buffer, u32 BufferSize);
PLATFORM_API bool PlatformReallocateMemory(void **Memory, uptr NewSize, uptr OldSize);

#endif