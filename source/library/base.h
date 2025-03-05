#ifndef BASE_H
#define BASE_H

#ifdef _WIN32
    #define WINDOWS_OS
    
    #ifdef BASE_IMPORT
        #define BASE_API __declspec(dllimport)
    #else
        #define BASE_API __declspec(dllexport)
    #endif
#else
    #error
#endif

#ifdef _DEBUG
    #define Assert(expression) do { if(!(expression)) { *(int *)0 = 0; } } while(0)
#else
    #define Assert(expression)
#endif

#define ArrayCount(array) (sizeof(array) / sizeof((array)[0]))
#define Kilobytes(value) ((value) * 1024LL)
#define Megabytes(value) (Kilobytes(value) * 1024LL)
#define Gigabytes(value) (Megabytes(value) * 1024LL)
#define Terabytes(value) (Gigabytes(value) * 1024LL)

typedef char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;
typedef long long s64;
typedef unsigned long long u64;
typedef float f32;
typedef double f64;
typedef s32 sint;
typedef u32 uint;
typedef uint bool;
typedef s64 sptr;
typedef u64 uptr;

BASE_API uptr BasePrint(char *Format, ...);
BASE_API uptr BaseWriteConsole(void *Buffer, uptr BufferSize);

#define Print BasePrint
#define Log Print
#endif
