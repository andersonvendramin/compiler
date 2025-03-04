#include "base.h"

#ifdef WINDOWS_OS
    #include <windows.h>
#else
    #error
#endif

#define POINTER_SIZE sizeof(void *)
#define VAGet(argument, type) *(type *)VAGetArgument(argument)
#define Log(format, ...)

typedef u8* va_args;

static uptr StringLength(char *String)
{
    uptr Result = 0;

    while(*String++ != '\0')
    {
        Result++;
    }

    return Result;
}

static uptr CopyCharacter(char *Buffer, uptr BufferSize, int Character)
{
    uptr Result = 0;

    if(BufferSize < (2 * sizeof(char)))
    {
        Log("BufferSize is %llu\n");
        return Result;
    }

    Buffer[0] = (char)Character;
    Buffer[1] = '\0';

    return 1;
}

static uptr CopyString(char *Buffer, uptr BufferSize, char *String, uptr Length)
{
    uptr Result = 0;

    uptr MaxLength = StringLength(String);

    if(Length > MaxLength)
    {
        Log("String %s has length %llu greater than max length %llu\n", String, Length, MaxLength);
        return Result;
    }

    for(uptr Index = 0; Index < Length; Index++)
    {
        Result += CopyCharacter(Buffer + Index, BufferSize - Index, String[Index]);
    }

    return Result;
}

static uptr CopySignedInteger32(char *Buffer, uptr BufferSize, s32 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = CopyCharacter(Buffer, BufferSize, '0');
        return Result;
    }

    bool IsNegative = Value < 0;

    if(IsNegative)
    {
        Value = -Value;
    }

    char WorkBuffer[32] = {0};
    int WorkBufferIndex = ArrayCount(WorkBuffer) - 2;

    for(; Value; Value /= Base)
    {
        WorkBuffer[WorkBufferIndex--] = Representation[Value % Base];
    }

    if(IsNegative)
    {
        WorkBuffer[WorkBufferIndex] = '-';
    }
    else
    {
        WorkBufferIndex++;
    }

    Result = CopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, StringLength(WorkBuffer + WorkBufferIndex));
    return Result;
}

static uptr CopyUnsignedInteger32(char *Buffer, uptr BufferSize, u32 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = CopyCharacter(Buffer, BufferSize, '0');
        return Result;
    }

    char WorkBuffer[32] = {0};
    int WorkBufferIndex = ArrayCount(WorkBuffer) - 2;

    for(; Value; Value /= Base)
    {
        WorkBuffer[WorkBufferIndex--] = Representation[Value % Base];
    }
    
    WorkBufferIndex++;

    Result = CopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, StringLength(WorkBuffer + WorkBufferIndex));
    return Result;
}

static uptr CopySignedInteger64(char *Buffer, uptr BufferSize, s64 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = CopyCharacter(Buffer, BufferSize, '0');
        return Result;
    }

    bool IsNegative = Value < 0;

    if(IsNegative)
    {
        Value = -Value;
    }

    char WorkBuffer[64] = {0};
    int WorkBufferIndex = ArrayCount(WorkBuffer) - 2;

    for(; Value; Value /= Base)
    {
        WorkBuffer[WorkBufferIndex--] = Representation[Value % Base];
    }

    if(IsNegative)
    {
        WorkBuffer[WorkBufferIndex] = '-';
    }
    else
    {
        WorkBufferIndex++;
    }

    Result = CopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, StringLength(WorkBuffer + WorkBufferIndex));
    return Result;
}

static uptr CopyUnsignedInteger64(char *Buffer, uptr BufferSize, u64 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = CopyCharacter(Buffer, BufferSize, '0');
        return Result;
    }

    char WorkBuffer[64] = {0};
    int WorkBufferIndex = ArrayCount(WorkBuffer) - 2;

    for(; Value; Value /= Base)
    {
        WorkBuffer[WorkBufferIndex--] = Representation[Value % Base];
    }
    
    WorkBufferIndex++;

    Result = CopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, StringLength(WorkBuffer + WorkBufferIndex));
    return Result;
}

static uptr CopyFloat64(char *Buffer, uptr BufferSize, f64 Value, int Precision)
{
    uptr Result = 0;

    char *Decimal = "0123456789";
    int IntegerPart = (int)Value;
    Result = CopySignedInteger32(Buffer, BufferSize, IntegerPart, 10, Decimal);
    Result += CopyCharacter(Buffer + Result, BufferSize - Result, '.');

    if(Value < 0)
    {
        Value = -Value;
        IntegerPart = -IntegerPart;
    }

    Value -= IntegerPart;

    for(int Index = 0; Index < Precision; Index++)
    {
        Value *= 10;
        IntegerPart = (int)Value;
        Result += CopySignedInteger32(Buffer + Result, BufferSize - Result, IntegerPart, 10, Decimal);
        Value -= IntegerPart;
    }

    return Result;
}

static va_args VABegin(void *Format)
{
    va_args Result = (va_args)Format + POINTER_SIZE;
    return Result;
}

static va_args VAEnd()
{
    va_args Result = 0;
    return Result;
}

static void *VAGetArgument(va_args *Argument)
{
    void *Result = *Argument;

    *Argument += POINTER_SIZE;

    return Result;
}

BASE_API uptr BaseWriteConsole(void *Buffer, uptr BufferSize)
{
    uptr Result = 0;
    
    HANDLE OutputConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(!OutputConsoleHandle || (OutputConsoleHandle == INVALID_HANDLE_VALUE))
    {
        Log("GetStdHandle() failed: 0x%X\n", GetLastError());
        return Result;
    }

    DWORD CharactersWritten = 0;
    WriteConsoleA(OutputConsoleHandle, Buffer, (DWORD)BufferSize, &CharactersWritten, 0);

    if(CharactersWritten != BufferSize)
    {
        Log("Characters written %u is different from buffer size %llu\n", CharactersWritten, BufferSize);
        return Result;
    }

    Result = BufferSize;
    return Result;
}

BASE_API uptr BasePrint(char *Format, ...)
{
    uptr Result = 0;

    uptr BufferSize = 1024;
    char Buffer[1024] = {0};
    va_args Argument = VABegin(&Format);
    char *Octal = "01234567";
    char *Decimal = "0123456789";
    char *HexadecimalLowercase = "0123456789abcdef";
    char *HexadecimalUppercase = "0123456789ABCDEF";

    for(char *c = Format; *c != '\0';)
    {
        if(*c != '%')
        {
            Result += CopyCharacter(Buffer + Result, BufferSize - Result, *c);
            c++;
            continue;
        }

        if(*++c == '%')
        {
            Result += CopyCharacter(Buffer + Result, BufferSize - Result, *c);
            c++;
        }
        else if(*c == 'c')
        {
            int Value = VAGet(&Argument, int);
            Result += CopyCharacter(Buffer + Result, BufferSize - Result, Value);
            c++;
        }
        else if((*c == 'd') || (*c == 'i'))
        {
            s32 Value = VAGet(&Argument, s32);
            Result += CopySignedInteger32(Buffer + Result, BufferSize - Result, Value, 10, Decimal);
            c++;
        }
        else if(*c == 'f')
        {
            f64 Value = VAGet(&Argument, f64);
            Result += CopyFloat64(Buffer + Result, BufferSize - Result, Value, 6);
            c++;
        }
        else if((c[0] == 'l') && (c[1] == 'l') && ((c[2] == 'd') || (c[2] == 'i')))
        {
            s64 Value = VAGet(&Argument, s64);
            Result += CopySignedInteger64(Buffer + Result, BufferSize - Result, Value, 10, Decimal);
            c += 3;
        }
        else if((c[0] == 'l') && (c[1] == 'l') && (c[2] == 'u'))
        {
            u64 Value = VAGet(&Argument, u64);
            Result += CopyUnsignedInteger64(Buffer + Result, BufferSize - Result, Value, 10, Decimal);
            c += 3;
        }
        else if(*c == 'o')
        {
            u32 Value = VAGet(&Argument, u32);
            Result += CopyUnsignedInteger32(Buffer + Result, BufferSize - Result, Value, 8, Octal);
            c++;
        }
        else if(*c == 'p')
        {
            void *Value = VAGet(&Argument, void *);
            Result += CopyUnsignedInteger64(Buffer + Result, BufferSize - Result, (u64)Value, 16, HexadecimalLowercase);
            c++;
        }
        else if(*c == 's')
        {
            char *Value = VAGet(&Argument, char *);
            Result += CopyString(Buffer + Result, BufferSize - Result, Value, StringLength(Value));
            c++;
        }
        else if(*c == 'u')
        {
            u32 Value = VAGet(&Argument, u32);
            Result += CopyUnsignedInteger32(Buffer + Result, BufferSize - Result, Value, 10, Decimal);
            c++;
        }
        else if((*c == 'x') || (*c == 'X'))
        {
            u32 Value = VAGet(&Argument, u32);
            
            if(*c == 'x')
            {
                Result += CopyUnsignedInteger32(Buffer + Result, BufferSize - Result, Value, 16, HexadecimalLowercase);
            }
            else
            {
                Result += CopyUnsignedInteger32(Buffer + Result, BufferSize - Result, Value, 16, HexadecimalUppercase);
            }

            c++;
        }
        else
        {
            Log("Invalid format specifier: %c\n");
            break;
        }
    }

    Argument = VAEnd();

    BaseWriteConsole(Buffer, StringLength(Buffer));

    return Result;
}