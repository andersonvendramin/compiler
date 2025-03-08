// @TODO: Fix char '.' when calling Print 
// @TODO: Fix '.' on CopyFloat64()
//@TODO: Unity test compiler

#include "compiler.h"

static int PrintUsage()
{
    Print("Usage: compiler.exe source_file.txt\n");
    return 0;
}

static void ReportCompilerErrors()
{
}

static bool InitializeCompiler()
{
    bool Result = 0;

    return 1;
}

static bool FinalizeCompiler()
{
    bool Result = 0;

    return 1;
}

static bool ReadSourceCode(char *FileName, char *SourceName, uptr SourceNameSize, void *Source)
{
    bool Result = 0;

    uptr FileSize = 0;

    if(!PlatformGetFileSize(FileName, &FileSize))
    {
        return Result;
    }

    if(FileSize > MAX_U32)
    {
        Log("File size is greater than %u\n", MAX_U32);
        return Result;
    }

    if(!PlatformReadFile(FileName, Source, (u32)FileSize))
    {
        return Result;
    }

    u8 *Buffer = Source;
    Buffer[FileSize] = '\0';
    uptr FileNameLength = StringLength(FileName);

    if(StringCopyString(SourceName, SourceNameSize, FileName, FileNameLength, 0) != FileNameLength)
    {
        *SourceName = '\0';
        *Buffer = '\0';
        return Result;
    }

    return 1;
}

static void SyntaxAnalysis()
{
}

static bool SemanticAnalysis()
{
    bool Result = 0;

    return 1;
}

static void GenerateIntermediateCode()
{
}

static void OptimazeCode()
{
}

static void GenerateMachineCode()
{
}

static bool OutputExecutable()
{
    bool Result = 0;

    return 1;
}

int main(int ArgumentCount, char **Argument)
{
    int Result = 1;

    if(ArgumentCount != 2)
    {
        return PrintUsage();
    }

    if(!InitializeCompiler())
    {
        return Result;
    }

    compiler Compiler = {0};

    if(!ReadSourceCode(Argument[1], Compiler.SourceName, sizeof(Compiler.SourceName), Compiler.Source))
    {
        return Result;
    }

    uptr TokenCount = 0;
    token *Token = LexicalAnalysis(&Compiler, &TokenCount);
    char *TokenString[] = 
    {
        "TOKEN_NUMBER",
        "TOKEN_IDENTIFIER",
        "TOKEN_PLUS",
        "TOKEN_MINUS",
        "TOKEN_STAR",
        "TOKEN_SLASH",
        "TOKEN_LEFT_PARENTHESES",
        "TOKEN_RIGHT_PARENTHESES",
    };    

    for(uptr Index = 0; Index < TokenCount; Index++)
    {
        Print("Token_Type = %s\n", TokenString[Token[Index].Type]);

        if(Token[Index].Type == TOKEN_NUMBER)
        {
            Print("Token_Value = %.1f\n", Token[Index].Value);
        }
        else if(Token[Index].Type == TOKEN_IDENTIFIER)
        {
            Print("Token_Identifier = %s\n", Token[Index].Identifier);
        }

        Print("\n");
    }

    SyntaxAnalysis();
    
    bool IsSemanticsValid = SemanticAnalysis();

    if(IsSemanticsValid)
    {
        GenerateIntermediateCode();
        OptimazeCode();
        GenerateMachineCode();

        if(!OutputExecutable())
        {
            return Result;
        }
    }
    else
    {
        ReportCompilerErrors();
        return Result;
    }

    
    return 0;
}