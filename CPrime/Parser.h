
#pragma once
#pragma source

#include "Map.h"
#include "StrBuilder.h"
#include "Ast.h"
#include "Scanner.h"
#include "CodePrint.h"

#define SYMBOL_BUCKETS_SIZE 1000

typedef struct {
  // indica presenca de erro no parser
  bool bError;

  // mensagem de erro
  StrBuilder ErrorMessage;

  // scanner ja pré-processado
  Scanner Scanner;

  TScannerItemList ClueList;

  SymbolMap GlobalScope;
  SymbolMap* pCurrentScope;
  
  int IncludeLevel;
  bool bPreprocessorEvalFlag;
} Parser;

bool Parser_InitFile(Parser *parser, const char *fileName);

bool Parser_InitString(Parser *parser, const char *name, const char *Text);

void Parser_Destroy(Parser *parser);

bool Parser_HasError(Parser *pParser);

const char *GetCompletationMessage(Parser *parser);

bool GetAST(const char *filename, const char *configFileName,
            Options* options,
            TProgram *pProgram);

void ConstantExpression(Parser *ctx, TExpression **ppExpression);
Tokens Parser_MatchToken(Parser *parser, Tokens tk, TScannerItemList *listOpt);

Tokens Parser_LookAheadToken(Parser *parser);

bool GetASTFromString(const char*  sourceCode,
  TProgram* pProgram);
