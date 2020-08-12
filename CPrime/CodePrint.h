#pragma once
#pragma source

#include <stdlib.h>
#include <stdio.h>
#include "Ast.h"
#include "StrBuilder.h"
#include "Macro.h"

#include "Options.h"

# //BEGIN_EXPORT

struct IntegerStack
{
    int* /*@auto*/ /*@[Size]*/ pData;
    int Size;
    int Capacity;
};


#define INTEGER_STACK_INIT {0,0,0}
enum Search
{
    SearchNone,
    SearchAll,
    SearchDestroy,
    SearchInit,
    SearchDelete,
};


struct PrintCodeOptions
{
    struct Options Options;

    ///////////
    //controle interno
    struct IntegerStack Stack;// = 0;
    bool bInclude;// = true;
    int IdentationLevel;
    //

    struct StrBuilder sbPreDeclaration;

};

#define CODE_PRINT_OPTIONS_INIT {OPTIONS_INIT, INTEGER_STACK_INIT, true, 0, STRBUILDER_INIT}

void PrintCodeOptions_Destroy(struct PrintCodeOptions* options);

void SyntaxTree_PrintCodeToFile(struct SyntaxTree* pSyntaxTree,
                                struct Options* options,
                                const char* fileName,
                                const char* userpath);

void SyntaxTree_PrintCodeToString(struct SyntaxTree* pSyntaxTree,
                                  struct Options* options,
                                  struct StrBuilder* output);


void TTypeName_CodePrint(struct SyntaxTree* pSyntaxTree, struct PrintCodeOptions* options, struct TTypeName* p, struct StrBuilder* fp);



void TSpecifierQualifierList_CodePrint(struct SyntaxTree* pSyntaxTree,
                                       struct PrintCodeOptions* options,
                                       struct TSpecifierQualifierList* pDeclarationSpecifiers,

                                       struct StrBuilder* fp);


void TDeclarationSpecifiers_CodePrint(struct SyntaxTree* pSyntaxTree, struct PrintCodeOptions* options, struct TDeclarationSpecifiers* pDeclarationSpecifiers, struct StrBuilder* fp);

enum Action
{
    ActionDestroy,
    ActionDestroyContent,
    ActionDelete,
    ActionCreate,
    ActionInit,
    ActionInitContent,
    ActionStaticInit,
};

void InstanciateEspecialFunction(struct SyntaxTree* pSyntaxTree,
                         struct PrintCodeOptions* options,
                         struct TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
                         struct TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
                         struct TInitializer* pInitializer,
                         struct TParameterTypeList* pArgsOpt,
                         const char* pInitExpressionText, //(x->p->i = 0)    
                         const char* pszAutoPointerLenExpressionOpt, //expressao usada para definir o tamanho de um spaw de auto pointers
                                                                     //se passar null eh pq nao interessa
                         const enum Action action,
                         enum Search search,
                         bool* pbHasInitializers,
                         struct StrBuilder* fp);

# //END_EXPORT
