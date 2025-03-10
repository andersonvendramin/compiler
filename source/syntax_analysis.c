#include "syntax_analysis.h"
static ast *Expression(compiler *Compiler);

f64 EvaluateAST(ast *Node)
{
    f64 Result = 0.0;

    switch(Node->Type)
    {
        case AST_NUMBER:
        {
            return Node->Value;
        } break;

        case AST_ADD:
        {
            return EvaluateAST((ast *)Node->Left) + EvaluateAST((ast *)Node->Right);
        } break;

        case AST_SUBTRACT:
        {
            return EvaluateAST((ast *)Node->Left) - EvaluateAST((ast *)Node->Right);
        } break;

        case AST_MULTIPLY:
        {
            return EvaluateAST((ast *)Node->Left) * EvaluateAST((ast *)Node->Right);
        } break;

        case AST_DIVIDE:
        {
            return EvaluateAST((ast *)Node->Left) / EvaluateAST((ast *)Node->Right);
        } break;

        default:
        {
            Log("Invalid AST\n");
        } break;
    }

    return Result;
}

static ast_type TokenToASTType(token_type TokenType)
{
    ast_type Result = 0;

    switch(TokenType)
    {
        case TOKEN_NUMBER:
        {
            Result = AST_NUMBER;
        } break;

        case TOKEN_PLUS:
        {
            Result = AST_ADD;
        } break;

        case TOKEN_MINUS:
        {
            Result = AST_SUBTRACT;
        } break;

        case TOKEN_STAR:
        {
            Result = AST_MULTIPLY;
        } break;

        case TOKEN_SLASH:
        {
            Result = AST_DIVIDE;
        } break;

        default:
        {
            Result = AST_INVALID;
        }
    }

    return Result;
}

static ast *CreateAST(ast_type Type, f64 Value, ast *Left, ast *Right)
{
    ast *Result = 0;

    if(!PlatformAllocateMemory(&Result, sizeof(ast)))
    {
        return Result;
    }

    Result->Type = Type;
    Result->Value = Value;
    Result->Left = (struct ast *)Left;
    Result->Right = (struct ast *)Right;

    return Result;
}

static bool AdvanceToken(compiler *Compiler)
{
    bool Result = 0;

    if(Compiler->TokenIndex < Compiler->TokenCount)
    {
        Compiler->TokenIndex++;
        Result = 1;
    }
    else
    {
        Log("TokenIndex >= TokenCount\n");
        return Result;
    }

    return Result;
}

static ast *Factor(compiler *Compiler)
{
    ast *Result = 0;

    if(TokenToASTType(Compiler->Token[Compiler->TokenIndex].Type) == AST_NUMBER)
    {
        Result = CreateAST(AST_NUMBER, Compiler->Token[Compiler->TokenIndex].Value, 0, 0);
    }
    else if(Compiler->Token[Compiler->TokenIndex].Type == TOKEN_LEFT_PARENTHESES)
    {
        AdvanceToken(Compiler);
        Result = Expression(Compiler);
        
    }
    else
    {
        Log("Invalid syntax: ast type %d\n", TokenToASTType(Compiler->Token[Compiler->TokenIndex].Type));
        return Result;
    }

    AdvanceToken(Compiler);

    return Result;
}

static ast *Term(compiler *Compiler)
{
    ast *Result = Factor(Compiler);
    
    token *Token = &Compiler->Token[Compiler->TokenIndex];
    
    while((TokenToASTType(Compiler->Token[Compiler->TokenIndex].Type) == AST_MULTIPLY) || (TokenToASTType(Compiler->Token[Compiler->TokenIndex].Type) == AST_DIVIDE))
    {
        ast_type ASTType = TokenToASTType(Compiler->Token[Compiler->TokenIndex].Type);
        AdvanceToken(Compiler);
        ast *Right = Factor(Compiler);

        Result = CreateAST(ASTType, 0, Result, Right);
    }

    return Result;
}

static ast *Expression(compiler *Compiler)
{
    ast *Result = Term(Compiler);
    
    while((TokenToASTType(Compiler->Token[Compiler->TokenIndex].Type) == AST_ADD) || (TokenToASTType(Compiler->Token[Compiler->TokenIndex].Type) == AST_SUBTRACT))
    {
        ast_type ASTType = TokenToASTType(Compiler->Token[Compiler->TokenIndex].Type);
        AdvanceToken(Compiler);
        ast *Right = Term(Compiler);

        Result = CreateAST(ASTType, 0, Result, Right);
    }

    return Result;
}