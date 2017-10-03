#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "..\Parser\Ast.h"
#include "..\Base\StrBuilder.h"
#include "..\Parser\Macro.h"
#include "..\Base\Map.h"


typedef enum
{
	BuildTypeInit,
	BuildTypeDestroy,
	BuildTypeCreate,
	BuildTypeDelete,
	BuildTypeStaticInit,
} BuildType;


typedef struct Options
{
	bool bExpandMacros;
	bool bIncludeComments _defval(1);
	bool bDontPrintClueList;
	int IdentationLevel;
    bool bShrink;
} Options;

#define OPTIONS_INIT {false, true, false, 0, false}

void Options_Destroy(Options* options);

void TProgram_PrintCodeToFile(TProgram * pProgram,
	Options* options,
	const char * fileName,
	const char* userpath);



bool TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p, bool b, StrBuilder* fp);


bool IsSuffix(const char* s, const char* suffix);
bool TSpecifierQualifierList_CodePrint(TProgram* program,
	Options * options,
	TSpecifierQualifierList* pDeclarationSpecifiers,
	bool b,
	StrBuilder* fp);


bool TDeclarationSpecifiers_CodePrint(TProgram* program, Options * options, TDeclarationSpecifiers* pDeclarationSpecifiers, bool b, StrBuilder* fp);

typedef enum
{
    ActionDestroy,
    ActionDestroyContent,
    ActionDelete,
    ActionCreate,
    ActionInit,
    ActionInitContent,
    ActionStaticInit,
} Action;

void InstanciateDestroy2(TProgram* program,
    Options* options,
    TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
    TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
    const char* pInitExpressionText, //(x->p->i = 0)    
    const Action action,
    bool bCanApplyFunction,
    StrBuilder* fp);
