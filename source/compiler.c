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

    u8 *buffer = Source;
    buffer[FileSize] = '\0';

    StringCopyString(SourceName, SourceNameSize, FileName, StringLength(FileName), 0);

    return 1;
}

static void LexicalAnalysis()
{
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

    LexicalAnalysis();
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