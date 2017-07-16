
#pragma once

#include "Scanner.h"
#include "..\Base\StrBuilder.h"
#include "Ast.h"
#include "Scanner.h"
#include "..\Base\Map.h"

#define SYMBOL_BUCKETS_SIZE 1000


typedef struct
{
  //indica presenca de erro no parser
  bool bError;

  //mensagem de erro
  StrBuilder ErrorMessage;

  //scanner ja pré-processado
  Scanner Scanner;

  //struct, union, or enum;
  //typedef estao no mesmo mapa mas da p achar
  //a diferenca se preciso
  DeclarationsMap  Symbols;

  Map EnumMap;

  TScannerItemList ClueList;
  TDeclarations Templates;
  TDeclarations TemplatesInstances;
} Parser;

Result Parser_InitFile(Parser* parser, const char* fileName);

Result Parser_InitString(Parser* parser,
                         const char* name,
                         const char* text);

void Parser_Destroy(Parser* parser);

bool Parser_HasError(Parser * pParser);


const char* GetCompletationMessage(Parser* parser);


bool GetAST(const char * filename,
            const char * configFileName,
            
            TProgram* pProgram);


//Tokens Parser_MatchToken(Parser* parser, Tokens tk);
void ConstantExpression(Parser* ctx, TExpression** ppExpression);
Tokens Parser_MatchToken(Parser* parser,
    Tokens tk,
    TScannerItemList* listOpt);

Tokens Parser_LookAheadToken(Parser* parser);
