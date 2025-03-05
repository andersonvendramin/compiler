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

static void ReadSourceCode(void *Buffer, uptr BufferSize)
{

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

    ReadSourceCode(Argument[1], StringLength(Argument[1]));
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