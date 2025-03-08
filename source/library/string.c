#include "../library/string.h"

STRING_API bool StringIsDigit(int Character)
{
    bool Result = 0;

    char c = (char)Character;

    if((c >= '0') && (c <= '9'))
    {
        Result = 1;
    }

    return Result;
}

STRING_API uptr StringLength(char *String)
{
    uptr Result = 0;

    while(*String++ != '\0')
    {
        Result++;
    }

    return Result;
}

STRING_API uptr StringCopyCharacter(char *Buffer, uptr BufferSize, int Character)
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

STRING_API uptr StringCopyString(char *Buffer, uptr BufferSize, char *String, uptr Length, uptr Precision)
{
    uptr Result = 0;

    uptr MaxLength = StringLength(String);

    if(Length > MaxLength)
    {
        Log("String %s has length of %llu greater than max length of %llu\n", String, Length, MaxLength);
        return Result;
    }

    if(!Precision)
    {
        Precision = Length;
    }
    else if(Precision > MaxLength)
    {
        Log("String %s has precision length of %llu greater than max length of %llu\n", String, Precision, MaxLength);
        return Result;
    }

    for(uptr Index = 0; Index < Precision; Index++)
    {
        Result += StringCopyCharacter(Buffer + Index, BufferSize - Index, String[Index]);
    }

    return Result;
}

STRING_API uptr StringCopySignedInteger32(char *Buffer, uptr BufferSize, s32 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = StringCopyCharacter(Buffer, BufferSize, '0');
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

    Result = StringCopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, StringLength(WorkBuffer + WorkBufferIndex), 0);
    return Result;
}

STRING_API uptr StringCopyUnsignedInteger32(char *Buffer, uptr BufferSize, u32 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = StringCopyCharacter(Buffer, BufferSize, '0');
        return Result;
    }

    char WorkBuffer[32] = {0};
    int WorkBufferIndex = ArrayCount(WorkBuffer) - 2;

    for(; Value; Value /= Base)
    {
        WorkBuffer[WorkBufferIndex--] = Representation[Value % Base];
    }
    
    WorkBufferIndex++;

    Result = StringCopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, StringLength(WorkBuffer + WorkBufferIndex), 0);
    return Result;
}

STRING_API uptr StringCopySignedInteger64(char *Buffer, uptr BufferSize, s64 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = StringCopyCharacter(Buffer, BufferSize, '0');
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

    Result = StringCopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, StringLength(WorkBuffer + WorkBufferIndex), 0);
    return Result;
}

STRING_API uptr StringCopyUnsignedInteger64(char *Buffer, uptr BufferSize, u64 Value, int Base, char *Representation)
{
    uptr Result = 0;

    if(!Value)
    {
        Result = StringCopyCharacter(Buffer, BufferSize, '0');
        return Result;
    }

    char WorkBuffer[64] = {0};
    int WorkBufferIndex = ArrayCount(WorkBuffer) - 2;

    for(; Value; Value /= Base)
    {
        WorkBuffer[WorkBufferIndex--] = Representation[Value % Base];
    }
    
    WorkBufferIndex++;

    Result = StringCopyString(Buffer, BufferSize, WorkBuffer + WorkBufferIndex, StringLength(WorkBuffer + WorkBufferIndex), 0);
    return Result;
}

STRING_API uptr StringCopyFloat64(char *Buffer, uptr BufferSize, f64 Value, int Precision)
{
    uptr Result = 0;

    char *Decimal = "0123456789";
    int IntegerPart = (int)Value;
    Result = StringCopySignedInteger32(Buffer, BufferSize, IntegerPart, 10, Decimal);
    Result += StringCopyCharacter(Buffer + Result, BufferSize - Result, '.');

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
        Result += StringCopySignedInteger32(Buffer + Result, BufferSize - Result, IntegerPart, 10, Decimal);
        Value -= IntegerPart;
    }

    return Result;
}

STRING_API bool StringIsSpace(int Character)
{
    bool Result = 0;

    char c = (char)Character;

    if((c == ' ') || (c == '\f') || (c == '\n') || (c == '\r') || (c == '\t') || (c == '\v'))
    {
        Result = 1;
    }

    return Result;
}

STRING_API bool StringIsLetter(int Character)
{
    bool Result = 0;

    char c = (char)Character;

    if(((c >= 'A') && (c <= 'Z')) || ((c >= 'a') && (c <= 'z')))
    {
        Result = 1;
    }

    return Result;
}