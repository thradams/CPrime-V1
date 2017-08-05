
#pragma once

#include "..\Base\Map.h"
#include "..\Base\StrBuilder.h"
#include "Ast.h"
#include "Scanner.h"

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
  
  //TDeclarations Templates;
  //TDeclarations TemplatesInstances;
} Parser;

Result Parser_InitFile(Parser *parser, const char *fileName);

Result Parser_InitString(Parser *parser, const char *name, const char *text);

void Parser_Destroy(Parser *parser);

bool Parser_HasError(Parser *pParser);

const char *GetCompletationMessage(Parser *parser);

bool GetAST(const char *filename, const char *configFileName,

            TProgram *pProgram);

void ConstantExpression(Parser *ctx, TExpression **ppExpression);
Tokens Parser_MatchToken(Parser *parser, Tokens tk, TScannerItemList *listOpt);

Tokens Parser_LookAheadToken(Parser *parser);
