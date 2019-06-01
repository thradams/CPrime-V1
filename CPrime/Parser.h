
#pragma once
#pragma source

#include "Map.h"
#include "StrBuilder.h"
#include "Ast.h"
#include "Scanner.h"
#include "CodePrint.h"


struct ParserOptions
{
    bool bNoImplicitTag;
};

struct Parser
{
    // indica presenca de erro no parser
    bool bError;

    // mensagem de erro
    struct StrBuilder ErrorMessage;

    // scanner ja pré-processado
    struct Scanner Scanner;

    struct TScannerItemList ClueList;

    struct SymbolMap GlobalScope;
    struct SymbolMap* pCurrentScope;

    int IncludeLevel;
    bool bPreprocessorEvalFlag;

    struct ParserOptions ParserOptions;
};

bool Parser_InitFile(struct Parser* parser, const char* fileName);

bool Parser_InitString(struct Parser* parser, const char* name, const char* Text);

void Parser_Destroy(struct Parser* parser);

bool Parser_HasError(struct Parser* pParser);

const char* GetCompletationMessage(struct Parser* parser);

bool GetAST(const char* filename, const char* configFileName,
            struct Options* options,
            struct SyntaxTree* pProgram);

void ConstantExpression(struct Parser* ctx, struct TExpression** ppExpression);
enum Tokens Parser_MatchToken(struct Parser* parser, enum Tokens tk, struct TScannerItemList* listOpt);

enum Tokens Parser_LookAheadToken(struct Parser* parser);

bool GetASTFromString(const char* sourceCode,
                      struct Options* options,
                      struct SyntaxTree* pProgram);
