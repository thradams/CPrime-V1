#pragma once
#pragma source

#include <stdlib.h>
#include <stdio.h>
#include "Ast.h"
#include "StrBuilder.h"
#include "Macro.h"
#include "Map.h"
#include "Options.h"


struct IntegerStack
{
    int * /*@auto*/ /*@[Size]*/ pData;
    int Size;
    int Capacity;
};


#define INTEGER_STACK_INIT {0,0,0}
typedef enum
{
    SearchNone,
    SearchAll,
    SearchDestroy,
    SearchInit,
    SearchDelete,
} Search;


typedef struct PrintCodeOptions
{
    struct Options Options;

    ///////////
    //controle interno
    struct IntegerStack Stack;// = 0;
    bool bInclude;// = true;
    int IdentationLevel;
    //

} PrintCodeOptions;

#define CODE_PRINT_OPTIONS_INIT {OPTIONS_INIT, INTEGER_STACK_INIT, true, 0}

void PrintCodeOptions_Destroy(PrintCodeOptions * options);

void TProgram_PrintCodeToFile(TProgram * pProgram,
                              struct Options * options,
                              const char * fileName,
                              const char * userpath);

void TProgram_PrintCodeToString(TProgram * pProgram,
                                struct Options * options,
                                StrBuilder * output);


void TTypeName_CodePrint(TProgram * program, PrintCodeOptions * options, TTypeName * p, StrBuilder * fp);


bool IsSuffix(const char * s, const char * suffix);
void TSpecifierQualifierList_CodePrint(TProgram * program,
                                       PrintCodeOptions * options,
                                       TSpecifierQualifierList * pDeclarationSpecifiers,

                                       StrBuilder * fp);


void TDeclarationSpecifiers_CodePrint(TProgram * program, PrintCodeOptions * options, TDeclarationSpecifiers * pDeclarationSpecifiers, StrBuilder * fp);

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

void InstanciateDestroy2(TProgram * program,
                         PrintCodeOptions * options,
                         TSpecifierQualifierList * pSpecifierQualifierList,//<-dupla para entender o tipo
                         TDeclarator * pDeclatator,                        //<-dupla para entender o tipo
                         TInitializer * pInitializer,
                         TParameterTypeList * pArgsOpt,
                         const char * pInitExpressionText, //(x->p->i = 0)    
                         const char * pszAutoPointerLenExpressionOpt, //expressao usada para definir o tamanho de um spaw de auto pointers
                                                                     //se passar null eh pq nao interessa
                         const Action action,
                         Search search,
                         bool * pbHasInitializers,
                         StrBuilder * fp);
