#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "Ast.h"
#include "StrBuilder.h"
#include "Macro.h"
#include "Map.h"



typedef enum 
{
    SearchNone,
    SearchAll,
    SearchDestroy,
    SearchInit,
    SearchDelete,
} Search;

typedef struct Options
{
    ///////////
    //controle interno
    bool bInclude;// = true;
    int IncludeLevel;// = 0;
    ////////////
	bool bExpandMacros;
	bool bIncludeComments _defval(1);
    
    //Usado para converter para string 
    //exemplo unsigned   /*algo*/ int   
    //tem que imprimir so 'unsigned int'
    bool bPrintRepresentation;

	int IdentationLevel;
    bool bHideDefaultImplementation;
} Options;

#define OPTIONS_INIT {true, 0,  false, true, false, 0, false}

void Options_Destroy(Options* options);

void TProgram_PrintCodeToFile(TProgram * pProgram,
	Options* options,
	const char * fileName,
	const char* userpath);

void TProgram_PrintCodeToString(TProgram* pProgram,
  Options* options,
  StrBuilder* output);


void TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p,  StrBuilder* fp);


bool IsSuffix(const char* s, const char* suffix);
void TSpecifierQualifierList_CodePrint(TProgram* program,
	Options * options,
	TSpecifierQualifierList* pDeclarationSpecifiers,

	StrBuilder* fp);


void TDeclarationSpecifiers_CodePrint(TProgram* program, Options * options, TDeclarationSpecifiers* pDeclarationSpecifiers,  StrBuilder* fp);

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
    TInitializer* pInitializer,
	  TParameterTypeList* pArgsOpt,
    const char* pInitExpressionText, //(x->p->i = 0)    
    const char* pszAutoPointerLenExpressionOpt, //expressao usada para definir o tamanho de um spaw de auto pointers
                                                //se passar null eh pq nao interessa
    const Action action,
    Search search,
    bool *pbHasInitializers,
    StrBuilder* fp);
