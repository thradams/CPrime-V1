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

void BuildInitializationForTypedef(TProgram* program,
	Options * options,
	const char* typedefName,
	StrBuilder* strBuilder);

bool TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p, bool b, StrBuilder* fp);

void InstanciateSpecialFunctions(TProgram* program,
	Options * options,
	TSpecifierQualifierList* pSpecifierQualifierList,
	TDeclarator* pDeclarator,
	TInitializer* pInitializer,
	const char* pVariableName,
	bool bVariableNameIsPointer,
	BuildType buildType,
	StrBuilder* fp);

bool IsSuffix(const char* s, const char* suffix);
bool TSpecifierQualifierList_CodePrint(TProgram* program,
	Options * options,
	TSpecifierQualifierList* pDeclarationSpecifiers,
	bool b,
	StrBuilder* fp);


bool TDeclarationSpecifiers_CodePrint(TProgram* program, Options * options, TDeclarationSpecifiers* pDeclarationSpecifiers, bool b, StrBuilder* fp);

void InstanciateInit(TProgram* program,
    Options* options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    TDeclarator* pDeclatator,
    TInitializer* pInitializer,
    const char* pVariableName,
    bool bInitPointerContent,
    StrBuilder* fp);
