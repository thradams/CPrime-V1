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
    bool bIncludeComments;
} Options;

#define OPTIONS_INIT {false, true}
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

void BuildDestroy(TProgram* program,
                  TSpecifierQualifierList* pSpecifierQualifierList,
                  TDeclarator* pDeclarator,
                  TInitializer* pInitializer,
                  const char* pVariableName,
                  bool bVariableNameIsPointer,
                  BuildType buildType,
                  StrBuilder* fp);
