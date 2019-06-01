
#include "CodePrint.h"
#include "Ast.h"
#include "Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Path.h"


void IntegerStack_Init(struct IntegerStack* pItems) /*@default*/
{
    pItems->pData = NULL;
    pItems->Size = 0;
    pItems->Capacity = 0;
}

void IntegerStack_PushBack(struct IntegerStack* pItems, int i) /*@default*/
{
    if (pItems->Size + 1 > pItems->Capacity)
    {
        int n = pItems->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        int* pnew = pItems->pData;
        pnew = (int*)Realloc(pnew, n * sizeof(int));
        if (pnew)
        {
            pItems->pData = pnew;
            pItems->Capacity = n;
        }
    }
    pItems->pData[pItems->Size] = i;
    pItems->Size++;
}

void IntegerStack_Pop(struct IntegerStack* pItems)
{
    if (pItems->Size > 0)
        pItems->Size--;
    //else
      //assert(false);
}



void IntegerStack_Destroy(struct IntegerStack* pItems) /*@default*/
{
    Free((void*)pItems->pData);
}

static int global_lambda_counter = 0;
static const char* GetReallocStr(struct SyntaxTree* program);

void PrintCodeOptions_Destroy(struct PrintCodeOptions* options) /*@default*/
{
    Options_Destroy(&options->Options);
    IntegerStack_Destroy(&options->Stack);
    StrBuilder_Destroy(&options->sbPreDeclaration);
}


void TSpecifierQualifierList_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TSpecifierQualifierList* pDeclarationSpecifiers, struct StrBuilder* fp);

void TTypeName_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TTypeName* p, struct StrBuilder* fp);

static void TInitializer_CodePrint(struct SyntaxTree* program,
                                   struct PrintCodeOptions* options,
                                   struct TDeclarator* pDeclarator,
                                   struct TDeclarationSpecifiers* pDeclarationSpecifiers,
                                   struct TInitializer* pTInitializer,

                                   struct StrBuilder* fp);

static void TInitializerList_CodePrint(struct SyntaxTree* program,
                                       struct PrintCodeOptions* options,
                                       struct TDeclarationSpecifiers* pDeclarationSpecifiers,
                                       struct TDeclarator* pDeclarator,
                                       struct TInitializerList* p,

                                       struct StrBuilder* fp);


static void TInitializerListItem_CodePrint(struct SyntaxTree* program,
                                           struct PrintCodeOptions* options,
                                           struct TDeclarator* pDeclarator,
                                           struct TDeclarationSpecifiers* pDeclarationSpecifiers,
                                           struct TInitializerListItem* p,

                                           struct StrBuilder* fp);


static void TTypeQualifierList_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TTypeQualifierList* p, struct StrBuilder* fp);

static void TAnyDeclaration_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TAnyDeclaration* pDeclaration, struct StrBuilder* fp);

static void TAnyStructDeclaration_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TAnyStructDeclaration* p, struct StrBuilder* fp);
static void TTypeQualifier_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TTypeQualifier* p, struct StrBuilder* fp);
static void TDeclaration_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TDeclaration* p, struct StrBuilder* fp);
static void TExpression_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TExpression* p, const char* name, struct StrBuilder* fp);
static void TStatement_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TStatement* p, struct StrBuilder* fp);
static void TBlockItem_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TBlockItem* p, struct StrBuilder* fp);

static void TPointer_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TPointer* pPointer, struct StrBuilder* fp);
static void TParameter_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TParameter* p, struct StrBuilder* fp);

void Output_Append(struct StrBuilder* p,
                   struct PrintCodeOptions* options,
                   const char* source)
{
    if (options->bInclude)
    {
        if (options->Stack.Size == 0 ||
            options->Stack.pData[options->Stack.Size - 1] == 1)
        {
            StrBuilder_Append(p, source);
        }
    }
    else
    {
        //nao eh p include
    }
}

static void TNodeClueList_CodePrint(struct PrintCodeOptions* options, struct TScannerItemList* list,
                                    struct StrBuilder* fp)
{
    if (options->Options.bCannonical)
    {
        // no modo cannonical quem coloca os espacos
        //eh a funcao especializada
        //para que o tipo seja somente ele 
        return;
    };

    ForEachListItem(struct ScannerItem, pNodeClue, list)
    {
        switch (pNodeClue->token)
        {
            case TK_PRE_INCLUDE:
            {
                bool bIncludeFile = true;

                if (options->Stack.Size > 0 &&
                    options->Stack.pData[options->Stack.Size - 1] == 0)
                {
                    bIncludeFile = false;
                }
                else
                {
                    if (options->Options.bAmalgamate)
                    {
                        if (strstr(pNodeClue->lexeme.c_str, "<") != NULL)
                        {
                            bIncludeFile = false;
                        }
                    }
                    else
                    {
                        bIncludeFile = false;
                    }
                }


                if (bIncludeFile)
                {
                    IntegerStack_PushBack(&options->Stack, bIncludeFile);
                }
                else
                {
                    Output_Append(fp, options, pNodeClue->lexeme.c_str);
                    Output_Append(fp, options, "\n");
                    IntegerStack_PushBack(&options->Stack, bIncludeFile);
                }

            }
            break;

            case TK_FILE_EOF:
                IntegerStack_Pop(&options->Stack);
                //options->IncludeLevel--;
                ////assert(IncludeLevel > 0);
                //bInclude = true;
                if (options->Options.bAmalgamate)
                {
                    Output_Append(fp, options, "\n");
                }

                break;
            case TK_PRE_DEFINE:
                //TODO gerar macros como init
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
                Output_Append(fp, options, "\n");
                break;

            case TK_PRE_PRAGMA:
                if (options->Options.bAmalgamate)
                {
                    //pragma once nao eh p incluir
                }
                else
                {
                    Output_Append(fp, options, pNodeClue->lexeme.c_str);
                    Output_Append(fp, options, "\n");
                }

                break;
            case TK_PRE_UNDEF:

            case TK_PRE_IF:
            case TK_PRE_ENDIF:
            case TK_PRE_ELSE:
            case TK_PRE_IFDEF:
            case TK_PRE_IFNDEF:
            case TK_PRE_ELIF:
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
                Output_Append(fp, options, "\n");
                break;

            case TK_OPEN_COMMENT:
            case TK_CLOSE_COMMENT:
                //Output_Append(fp, options, pNodeClue->lexeme.c_str);
                break;

            case TK_COMMENT:
                if (options->Options.bIncludeComments)
                {
                    Output_Append(fp, options, pNodeClue->lexeme.c_str);
                }
                else
                {
                    Output_Append(fp, options, " ");
                }

                break;

            case TK_LINE_COMMENT:
                if (options->Options.bIncludeComments)
                {
                    Output_Append(fp, options, pNodeClue->lexeme.c_str);
                }
                else
                {

                }
                break;

            case TK_BREAKLINE:
                Output_Append(fp, options, "\n");

                break;

            case TK_MACRO_CALL:
                if (options->Options.bExpandMacros)
                {

                }
                else
                {
                    Output_Append(fp, options, pNodeClue->lexeme.c_str);
                    options->bInclude = false;
                }
                break;


            case TK_MACRO_EOF:
                if (options->Options.bExpandMacros)
                {

                }
                else
                {
                    options->bInclude = true;
                }


                break;

            case TK_SPACES:
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
                break;

                //case NodeClueTypeNone:      
            default:
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
                break;
        }
    }

}

static void TCompoundStatement_CodePrint(struct SyntaxTree* program,
                                         struct PrintCodeOptions* options,
                                         struct TCompoundStatement* p,

                                         struct StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "{");

    for (int j = 0; j < p->BlockItemList.Size; j++)
    {
        struct TBlockItem* pBlockItem = p->BlockItemList.pItems[j];
        TBlockItem_CodePrint(program, options, pBlockItem, fp);
    }

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "}");

}


static void TLabeledStatement_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TLabeledStatement* p, struct StrBuilder* fp)
{


    if (p->token == TK_CASE)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "case");
        if (p->pExpression)
        {
            TExpression_CodePrint(program, options, p->pExpression, "", fp);
        }
        else
        {
            //assert(false);
        }
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, ":");

        TStatement_CodePrint(program, options, p->pStatementOpt, fp);
    }
    else if (p->token == TK_DEFAULT)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "default");
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, ":");
        TStatement_CodePrint(program, options, p->pStatementOpt, fp);
    }
    else if (p->token == TK_IDENTIFIER)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, p->Identifier);

        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, ":");

        TStatement_CodePrint(program, options, p->pStatementOpt, fp);
    }



}

static void TForStatement_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TForStatement* p, struct StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "for");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "(");

    if (p->pInitDeclarationOpt)
    {
        TAnyDeclaration_CodePrint(program, options, p->pInitDeclarationOpt, fp);
        if (p->pExpression2)
        {
            TExpression_CodePrint(program, options, p->pExpression2, "expr2", fp);
        }
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, options, ";");
        TExpression_CodePrint(program, options, p->pExpression3, "expr3", fp);
    }
    else
    {
        TExpression_CodePrint(program, options, p->pExpression1, "expr1", fp);
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, options, ";");
        TExpression_CodePrint(program, options, p->pExpression2, "expr2", fp);
        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, options, ";");
        TExpression_CodePrint(program, options, p->pExpression3, "expr3", fp);
    }

    TNodeClueList_CodePrint(options, &p->ClueList4, fp);
    Output_Append(fp, options, ")");

    TStatement_CodePrint(program, options, p->pStatement, fp);


}


static void TWhileStatement_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TWhileStatement* p, struct StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "while");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "(");
    TExpression_CodePrint(program, options, p->pExpression, "expr", fp);
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, ")");
    TStatement_CodePrint(program, options, p->pStatement, fp);

}



static void TDoStatement_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TDoStatement* p, struct StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "do");

    TStatement_CodePrint(program, options, p->pStatement, fp);

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "while");
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, "(");
    TExpression_CodePrint(program, options, p->pExpression, "expr", fp);
    TNodeClueList_CodePrint(options, &p->ClueList3, fp);
    Output_Append(fp, options, ")");
    TNodeClueList_CodePrint(options, &p->ClueList4, fp);
    Output_Append(fp, options, ";");


}


static void TExpressionStatement_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TExpressionStatement* p, struct StrBuilder* fp)
{
    TExpression_CodePrint(program, options, p->pExpression, "", fp);

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, ";");


}


static void TJumpStatement_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TJumpStatement* p, struct StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    switch (p->token)
    {
        case TK_GOTO:
            Output_Append(fp, options, "goto");
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, options, p->Identifier);
            break;
        case  TK_CONTINUE:
            Output_Append(fp, options, "continue");
            break;
        case TK_BREAK:
            Output_Append(fp, options, "break");
            break;
        case TK_RETURN:
            Output_Append(fp, options, "return");
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            TExpression_CodePrint(program, options, p->pExpression, "", fp);
            break;

        default:
            //assert(false);
            break;
    }


    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, ";");


}

static void TAsmStatement_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TAsmStatement* p, struct StrBuilder* fp)
{
    Output_Append(fp, options, "\"type\":\"asm-statement\"");

}

static void TSwitchStatement_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TSwitchStatement* p, struct StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "switch");

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "(");

    TExpression_CodePrint(program, options, p->pConditionExpression, "expr", fp);

    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, ")");

    TStatement_CodePrint(program, options, p->pExpression, fp);

}


static void TIfStatement_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TIfStatement* p, struct StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "if");

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "(");


    TExpression_CodePrint(program, options, p->pConditionExpression, "expr", fp);

    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, ")");

    if (p->pStatement->Type != TCompoundStatement_ID)
        Output_Append(fp, options, "");

    if (p->pStatement)
    {
        TStatement_CodePrint(program, options, p->pStatement, fp);
    }

    if (p->pElseStatement)
    {
        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, options, "else");
        TStatement_CodePrint(program, options, p->pElseStatement, fp);
    }


}

static void TStatement_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TStatement* p, struct StrBuilder* fp)
{
    if (p == NULL)
    {
        return;
    }

    switch (p->Type)
    {
        case TExpressionStatement_ID:
            TExpressionStatement_CodePrint(program, options, (struct TExpressionStatement*)p, fp);
            break;

        case TSwitchStatement_ID:
            TSwitchStatement_CodePrint(program, options, (struct TSwitchStatement*)p, fp);
            break;

        case TLabeledStatement_ID:
            TLabeledStatement_CodePrint(program, options, (struct TLabeledStatement*)p, fp);
            break;

        case TForStatement_ID:
            TForStatement_CodePrint(program, options, (struct TForStatement*)p, fp);
            break;

        case TJumpStatement_ID:
            TJumpStatement_CodePrint(program, options, (struct TJumpStatement*)p, fp);
            break;

        case TAsmStatement_ID:
            TAsmStatement_CodePrint(program, options, (struct TAsmStatement*)p, fp);
            break;

        case TCompoundStatement_ID:
            TCompoundStatement_CodePrint(program, options, (struct TCompoundStatement*)p, fp);
            break;

        case TIfStatement_ID:
            TIfStatement_CodePrint(program, options, (struct TIfStatement*)p, fp);
            break;

        case TDoStatement_ID:
            TDoStatement_CodePrint(program, options, (struct TDoStatement*)p, fp);
            break;

        default:
            //assert(false);
            break;
    }


}

static void TBlockItem_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TBlockItem* p, struct StrBuilder* fp)
{
    if (p == NULL)
    {
        //assert(false);
        return;
    }


    switch (p->Type)
    {
        case TEofDeclaration_ID:
            break;

        case TStaticAssertDeclaration_ID:
            break;

        case TSwitchStatement_ID:

            TSwitchStatement_CodePrint(program, options, (struct TSwitchStatement*)p, fp);

            break;

        case TJumpStatement_ID:

            TJumpStatement_CodePrint(program, options, (struct TJumpStatement*)p, fp);

            break;

        case TForStatement_ID:

            TForStatement_CodePrint(program, options, (struct TForStatement*)p, fp);

            break;

        case TIfStatement_ID:

            TIfStatement_CodePrint(program, options, (struct TIfStatement*)p, fp);

            break;

        case TWhileStatement_ID:

            TWhileStatement_CodePrint(program, options, (struct TWhileStatement*)p, fp);

            break;

        case TDoStatement_ID:

            TDoStatement_CodePrint(program, options, (struct TDoStatement*)p, fp);

            break;

        case TDeclaration_ID:
            TDeclaration_CodePrint(program, options, (struct TDeclaration*)p, fp);
            //Output_Append(fp, options,  "\n");
            break;

        case TLabeledStatement_ID:

            TLabeledStatement_CodePrint(program, options, (struct TLabeledStatement*)p, fp);

            break;

        case TCompoundStatement_ID:
            TCompoundStatement_CodePrint(program, options, (struct TCompoundStatement*)p, fp);
            break;

        case TExpressionStatement_ID:

            TExpressionStatement_CodePrint(program, options, (struct TExpressionStatement*)p, fp);

            break;


        case TAsmStatement_ID:

            TAsmStatement_CodePrint(program, options, (struct TAsmStatement*)p, fp);

            break;

        default:
            //assert(false);
            break;
    }


}



bool GetType(const char* source,
             struct StrBuilder* strBuilderType)
{

    while (*source &&
           *source != '_')
    {
        StrBuilder_AppendChar(strBuilderType, *source);
        source++;
    }


    return *source == '_';
}


bool GetTypeAndFunction(const char* source,
                        struct StrBuilder* strBuilderType,
                        struct StrBuilder* strBuilderFunc)
{

    while (*source &&
           *source != '_')
    {
        StrBuilder_AppendChar(strBuilderType, *source);
        source++;
    }

    while (*source)
    {
        StrBuilder_AppendChar(strBuilderFunc, *source);
        source++;
    }

    return *source == '_';
}

static void TParameterTypeList_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TParameterTypeList* p, struct StrBuilder* fp);


static void TPrimaryExpressionLambda_CodePrint(struct SyntaxTree* program,
                                               struct PrintCodeOptions* options,
                                               struct TPrimaryExpressionLambda* p,
                                               struct StrBuilder* fp)
{

    //Output_Append(fp, options, "l1");
    //Output_Append
    StrBuilder_AppendFmt(fp, "_lambda_%d", global_lambda_counter);

    struct StrBuilder sb = STRBUILDER_INIT;

    if (p->pParameterTypeListOpt)
    {
        //TNodeClueList_CodePrint(options, &p->ClueList2, &sb);


        Output_Append(&sb, options, "\n");
        StrBuilder_AppendFmt(&sb, "static void _lambda_%d(", global_lambda_counter);
        //Output_Append(&sb, options, "static void func_l1(");

        TParameterTypeList_CodePrint(program, options, p->pParameterTypeListOpt, &sb);

        //TNodeClueList_CodePrint(options, &p->ClueList3, &sb);
        Output_Append(&sb, options, ")");

    }
    global_lambda_counter++;
    TCompoundStatement_CodePrint(program, options, p->pCompoundStatement, &sb);

    Output_Append(&options->sbPreDeclaration, options, "\n");

    StrBuilder_Append(&options->sbPreDeclaration, sb.c_str);




    StrBuilder_Destroy(&sb);

#if NORMAL 
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "[");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "]");

    if (p->pParameterTypeListOpt)
    {
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, options, "(");

        TParameterTypeList_CodePrint(program, options, p->pParameterTypeListOpt, fp);

        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, options, ")");

    }

    TCompoundStatement_CodePrint(program, options, p->pCompoundStatement, fp);
#endif

}

static void TPostfixExpressionCore_CodePrint(struct SyntaxTree* program,
                                             struct PrintCodeOptions* options,
                                             struct TPostfixExpressionCore* p,

                                             struct StrBuilder* fp)
{


    bool bIsPointer = false;

    if (p->pExpressionLeft)
    {
        TExpression_CodePrint(program, options, p->pExpressionLeft, "l", fp);
    }


    {
        if (p->pTypeName)
        {
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);
            Output_Append(fp, options, "(");
            TTypeName_CodePrint(program, options, p->pTypeName, fp);
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, options, ")");

            //pSpecifierQualifierList = &p->pTypeName->SpecifierQualifierList;
            bIsPointer = TPointerList_IsPointer(&p->pTypeName->Declarator.PointerList);

            //falta imprimeir typename
            //TTypeName_Print*
            TInitializerList_CodePrint(program,
                                       options,
                                       (struct TDeclarationSpecifiers*) & p->pTypeName->SpecifierQualifierList,
                                       NULL,
                                       &p->InitializerList,

                                       fp);
        }

    }

    switch (p->token)
    {
        case TK_FULL_STOP:
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);
            Output_Append(fp, options, ".");
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, options, p->Identifier);

            break;
        case TK_ARROW:
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);
            Output_Append(fp, options, "->");
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, options, p->Identifier);

            break;

        case TK_LEFT_SQUARE_BRACKET:
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);
            Output_Append(fp, options, "[");
            TExpression_CodePrint(program, options, p->pExpressionRight, "r", fp);
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, options, "]");
            break;

        case TK_LEFT_PARENTHESIS:
            //Do lado esquerdo vem o nome da funcao p->pExpressionLeft
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);
            Output_Append(fp, options, "(");
            TExpression_CodePrint(program, options, p->pExpressionRight, "r", fp);
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, options, ")");
            break;

        case TK_PLUSPLUS:
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);
            Output_Append(fp, options, "++");

            break;
        case TK_MINUSMINUS:
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);
            Output_Append(fp, options, "--");

            break;


        default:
            //assert(false);
            break;
    }



    if (p->pNext)
    {
        TPostfixExpressionCore_CodePrint(program, options, p->pNext, fp);
    }



}

static void TExpression_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TExpression* p,
                                  const char* name,

                                  struct StrBuilder* fp)
{
    if (p == NULL)
    {
        ////assert(false);
        return;
    }



    switch (p->Type)
    {
        case TBinaryExpression_ID:
        {
            struct TBinaryExpression* pBinaryExpression = (struct TBinaryExpression*)p;

            TExpression_CodePrint(program, options, pBinaryExpression->pExpressionLeft, "l-expr", fp);

            TNodeClueList_CodePrint(options, &pBinaryExpression->ClueList0, fp);
            Output_Append(fp, options, TokenToString(pBinaryExpression->token));

            TExpression_CodePrint(program, options, ((struct TBinaryExpression*)p)->pExpressionRight, "r-expr", fp);
        }
        break;

        case TTernaryExpression_ID:
        {
            struct TTernaryExpression* pTernaryExpression =
                (struct TTernaryExpression*)p;


            TExpression_CodePrint(program, options, pTernaryExpression->pExpressionLeft, "l-expr", fp);

            TNodeClueList_CodePrint(options, &pTernaryExpression->ClueList0, fp);
            Output_Append(fp, options, "?");

            TExpression_CodePrint(program, options, pTernaryExpression->pExpressionMiddle, "m-expr", fp);

            TNodeClueList_CodePrint(options, &pTernaryExpression->ClueList1, fp);
            Output_Append(fp, options, ":");

            TExpression_CodePrint(program, options, pTernaryExpression->pExpressionRight, "r-expr", fp);
        }
        break;

        case TPrimaryExpressionLiteral_ID:
        {
            struct TPrimaryExpressionLiteral* pPrimaryExpressionLiteral
                = (struct TPrimaryExpressionLiteral*)p;

            ForEachListItem(struct TPrimaryExpressionLiteralItem, pItem, &pPrimaryExpressionLiteral->List)
            {
                TNodeClueList_CodePrint(options, &pItem->ClueList0, fp);
                Output_Append(fp, options, pItem->lexeme);
            }
        }
        break;

        case TPrimaryExpressionValue_ID:
        {
            struct TPrimaryExpressionValue* pPrimaryExpressionValue =
                (struct TPrimaryExpressionValue*)p;

            if (pPrimaryExpressionValue->pExpressionOpt != NULL)
            {
                TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList0, fp);
                Output_Append(fp, options, "(");
                TExpression_CodePrint(program, options, pPrimaryExpressionValue->pExpressionOpt, "expr", fp);

                TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList1, fp);
                Output_Append(fp, options, ")");
            }
            else
            {
                TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList0, fp);
                Output_Append(fp, options, pPrimaryExpressionValue->lexeme);
            }
        }
        ///true;

        break;

        case TPrimaryExpressionLambda_ID:
        {
            struct TPrimaryExpressionLambda* pPostfixExpressionCore =
                (struct TPrimaryExpressionLambda*)p;
            TPrimaryExpressionLambda_CodePrint(program, options, pPostfixExpressionCore, fp);
        }
        break;

        case TPostfixExpressionCore_ID:
        {
            struct TPostfixExpressionCore* pPostfixExpressionCore =
                (struct TPostfixExpressionCore*)p;
            TPostfixExpressionCore_CodePrint(program, options, pPostfixExpressionCore, fp);
        }
        break;

        case TUnaryExpressionOperator_ID:
        {
            struct TUnaryExpressionOperator* pTUnaryExpressionOperator =
                (struct TUnaryExpressionOperator*)p;

            TNodeClueList_CodePrint(options, &pTUnaryExpressionOperator->ClueList0, fp);

            if (pTUnaryExpressionOperator->token == TK_SIZEOF)
            {
                if (pTUnaryExpressionOperator->TypeName.SpecifierQualifierList.Size > 0)
                {
                    Output_Append(fp, options, "sizeof");
                    TNodeClueList_CodePrint(options, &pTUnaryExpressionOperator->ClueList1, fp);

                    Output_Append(fp, options, "(");
                    TTypeName_CodePrint(program, options, &pTUnaryExpressionOperator->TypeName, fp);

                    TNodeClueList_CodePrint(options, &pTUnaryExpressionOperator->ClueList2, fp);
                    Output_Append(fp, options, ")");
                }
                else
                {
                    Output_Append(fp, options, "sizeof");
                    TExpression_CodePrint(program, options, pTUnaryExpressionOperator->pExpressionRight, "expr", fp);
                    Output_Append(fp, options, "");
                }
            }
            else
            {
                Output_Append(fp, options, TokenToString(((struct TBinaryExpression*)p)->token));
                TExpression_CodePrint(program, options, pTUnaryExpressionOperator->pExpressionRight, "expr", fp);
            }
        }
        break;

        case TCastExpressionType_ID:
        {
            struct TCastExpressionType* pCastExpressionType =
                (struct TCastExpressionType*)p;
            TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList0, fp);
            Output_Append(fp, options, "(");

            TTypeName_CodePrint(program, options, &pCastExpressionType->TypeName, fp);


            TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList1, fp);
            Output_Append(fp, options, ")");

            TExpression_CodePrint(program, options, pCastExpressionType->pExpression, "expr", fp);
        }
        break;

        default:

            //assert(false);
            break;
    }



}



static   void TEnumerator_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TEnumerator* pTEnumerator, struct StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &pTEnumerator->ClueList0, fp);
    Output_Append(fp, options, pTEnumerator->Name);

    if (pTEnumerator->pConstantExpression)
    {
        TNodeClueList_CodePrint(options, &pTEnumerator->ClueList1, fp);
        Output_Append(fp, options, "=");

        TExpression_CodePrint(program, options, pTEnumerator->pConstantExpression, "expr", fp);


    }
    else
    {
        //vou criar uma expressionp enum?
    }

    if (pTEnumerator->bHasComma)
    {
        TNodeClueList_CodePrint(options, &pTEnumerator->ClueList2, fp);
        Output_Append(fp, options, ",");
    }


}

static void TEnumSpecifier_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TEnumSpecifier* p, struct StrBuilder* fp)
{
    //true;

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "enum");

    if (options->Options.bCannonical)
    {
        Output_Append(fp, options, " ");
    }

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, p->Tag);

    TNodeClueList_CodePrint(options, &p->ClueList2, fp);

    if (p->EnumeratorList.pHead != NULL)
    {
        Output_Append(fp, options, "{");

        ForEachListItem(struct TEnumerator, pTEnumerator, &p->EnumeratorList)
        {
            TEnumerator_CodePrint(program, options, pTEnumerator, fp);
        }

        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, options, "}");
    }


}

static void TUnionSetItem_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TUnionSetItem* p, struct StrBuilder* fp)
{
    if (p->Token == TK_STRUCT)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "struct");
    }
    else if (p->Token == TK_UNION)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "union");
    }

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, p->Name);

    if (p->TokenFollow == TK_VERTICAL_LINE)
    {
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, options, "|");
    }
}

static void TUnionSet_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TUnionSet* p, struct StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    if (options->Options.Target == CompilerTarget_Annotated)
    {
        Output_Append(fp, options, "/*@");
    }

    Output_Append(fp, options, "<");

    struct TUnionSetItem* pCurrent = p->pHead;
    while (pCurrent)
    {
        TUnionSetItem_CodePrint(program, options, pCurrent, fp);
        pCurrent = pCurrent->pNext;
    }

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, ">");

    if (options->Options.Target == CompilerTarget_Annotated)
    {
        Output_Append(fp, options, "*/");
    }

}

static void TStructUnionSpecifier_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TStructUnionSpecifier* p, struct StrBuilder* fp)
{
    if (options->Options.bCannonical)
    {
    }
    else
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    }

    //true;

    if (p->StructDeclarationList.Size > 0)
    {
        if (p->Token == TK_STRUCT)
        {
            Output_Append(fp, options, "struct");
        }
        else if (p->Token == TK_UNION)
        {
            Output_Append(fp, options, "union");
        }

        if (options->Options.bCannonical)
        {
            Output_Append(fp, options, " ");
        }

        if (p->UnionSet.pHead != NULL)
        {
            TUnionSet_CodePrint(program, options, &p->UnionSet, fp);
        }

        //TNodeClueList_CodePrint(options, &p->ClueList1, fp);

    }
    else
    {
        if (p->Token == TK_STRUCT)
        {
            Output_Append(fp, options, "struct");
        }
        else if (p->Token == TK_UNION)
        {
            Output_Append(fp, options, "union");
        }

        if (options->Options.bCannonical)
        {
            Output_Append(fp, options, " ");
        }

        if (p->UnionSet.pHead != NULL)
        {
            TUnionSet_CodePrint(program, options, &p->UnionSet, fp);
        }
    }

    if (options->Options.bCannonical)
    {
    }
    else
    {
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    }

    Output_Append(fp, options, p->Tag);


    if (p->StructDeclarationList.Size > 0)
    {
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);

        Output_Append(fp, options, "{");

        for (int i = 0; i < p->StructDeclarationList.Size; i++)
        {
            struct TAnyStructDeclaration* pStructDeclaration = p->StructDeclarationList.pItems[i];
            TAnyStructDeclaration_CodePrint(program, options, pStructDeclaration, fp);
        }

        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, options, "}");
    }

}

static void TSingleTypeSpecifier_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TSingleTypeSpecifier* p, struct StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    //true;

    /*if (p->Token2 == TK_STRUCT)
    {
      if (options->Target == CompilerTarget_Annotated)
      {
        //acrescenta
        Output_Append(fp, options, "struct ");
      }
      Output_Append(fp, options, p->TypedefName);
    }
    else if (p->Token2 == TK_UNION)
    {
      if (options->Target == CompilerTarget_Annotated)
      {
        //acrescenta
        Output_Append(fp, options, "union ");
      }
      Output_Append(fp, options, p->TypedefName);

    }
    else if (p->Token2 == TK_ENUM)
    {
      if (options->Target == CompilerTarget_Annotated)
      {
        //acrescenta
        Output_Append(fp, options, "enum ");
      }
      Output_Append(fp, options, p->TypedefName);

    }
    else
    */
    if (p->Token2 == TK_IDENTIFIER)
    {
        Output_Append(fp, options, p->TypedefName);
    }
    else
    {
        Output_Append(fp, options,
                      TokenToString(p->Token2));
    }



}

static void TDesignator_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TDesignator* p, struct StrBuilder* fp)
{
    //    if (b)
    //      Output_Append(fp, options,  ",");


    //
    if (p->Name)
    {
        //.identifier
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, ".");
        Output_Append(fp, options, p->Name);
        Output_Append(fp, options, "=");
        TExpression_CodePrint(program, options, p->pExpression, "index", fp);
    }
    else
    {
        //[constant-expression]
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        TExpression_CodePrint(program, options, p->pExpression, "index", fp);
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    }



}

#define List_HasOneItem(pList) \
 ((pList)->pHead != NULL && (pList)->pHead == (pList)->pTail)

#define List_Back(pList) \
  ((pList)->pTail)

static void TInitializerList_CodePrint(struct SyntaxTree* program,
                                       struct PrintCodeOptions* options,
                                       struct TDeclarationSpecifiers* pDeclarationSpecifiers, //<- usadao para construir {}
                                       struct TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
                                       struct TInitializerList* p,

                                       struct StrBuilder* fp)
{
    if (List_HasOneItem(p) &&
        List_Back(p)->pInitializer == NULL/* &&
                  pSpecifierQualifierList != NULL*/)
    {
        if (options->Options.Target == CompilerTarget_Annotated)
        {
            //Output_Append(fp, options, COMMENT_KEYWORD_DEFAULT);
        }
        //a partir de {} e um tipo consegue gerar o final  
        struct StrBuilder sb = STRBUILDER_INIT;
        bool bHasInitializers = false;
        InstanciateDestroy2(program,
                            options,
                            (struct TSpecifierQualifierList*)(pDeclarationSpecifiers),
                            pDeclatator,                        //<-dupla para entender o tipo
                            NULL,
                            NULL,/*args*/
                            "",
                            NULL /*not used*/,
                            ActionStaticInit,
                            SearchNone,
                            &bHasInitializers,
                            &sb);
        if (bHasInitializers)
        {
            Output_Append(fp, options, sb.c_str);
        }
        else
        {
            Output_Append(fp, options, "{0}");
        }

        StrBuilder_Destroy(&sb);
    }
    else
    {

        ForEachListItem(struct TInitializerListItem, pItem, p)
        {
            if (!List_IsFirstItem(p, pItem))
                Output_Append(fp, options, ",");

            TInitializerListItem_CodePrint(program,
                                           options,
                                           pDeclatator,
                                           pDeclarationSpecifiers,
                                           pItem,
                                           fp);
        }

    }
}

static void TInitializerListType_CodePrint(struct SyntaxTree* program,
                                           struct PrintCodeOptions* options,
                                           struct TDeclarator* pDeclarator,
                                           struct TDeclarationSpecifiers* pDeclarationSpecifiers,
                                           struct TInitializerListType* p,
                                           struct StrBuilder* fp)
{

    /*
    default { ... }
    {}
    */
    if (p->bDefault || p->InitializerList.pHead == NULL)
    {
        //TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        struct TInitializer* pInitializer = NULL;
        //p->InitializerList.pHead ?
        //p->InitializerList.pHead->pInitializer : NULL;


        if (options->Options.Target == CompilerTarget_CXX)
        {
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, options, "{");

            TNodeClueList_CodePrint(options, &p->ClueList2, fp);
            Output_Append(fp, options, "}");
        }
        else  if (options->Options.Target == CompilerTarget_Annotated)
        {
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);

            if (options->Options.Target == CompilerTarget_Annotated)
            {
                Output_Append(fp, options, "/*@");
            }


            Output_Append(fp, options, "default");


            if (options->Options.Target == CompilerTarget_Annotated)
            {
                Output_Append(fp, options, "*/");
            }

            TNodeClueList_CodePrint(options, &p->ClueList1, fp);

            if (p->InitializerList.pHead)
                TNodeClueList_CodePrint(options, &p->InitializerList.pHead->ClueList, fp);

            struct StrBuilder sb = STRBUILDER_INIT;
            bool bHasInitializers = false;
            InstanciateDestroy2(program,
                                options,
                                (struct TSpecifierQualifierList*)(pDeclarationSpecifiers),
                                pDeclarator,                        //<-dupla para entender o tipo
                                pInitializer,
                                NULL,/*args*/
                                "",
                                NULL /*not used*/,
                                ActionStaticInit,
                                SearchNone,
                                &bHasInitializers,
                                &sb);

            if (bHasInitializers)
            {
                Output_Append(fp, options, sb.c_str);
            }
            else
            {
                Output_Append(fp, options, "{0}");
            }

            StrBuilder_Destroy(&sb);
        }

    }
    else
    {
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, "{");

        TInitializerList_CodePrint(program,
                                   options,
                                   pDeclarationSpecifiers,
                                   pDeclarator,
                                   &p->InitializerList,

                                   fp);

        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, options, "}");
    }


}


static void TInitializer_CodePrint(struct SyntaxTree* program,
                                   struct PrintCodeOptions* options,
                                   struct TDeclarator* pDeclarator,
                                   struct TDeclarationSpecifiers* pDeclarationSpecifiers,
                                   struct TInitializer* pTInitializer,

                                   struct StrBuilder* fp)
{
    if (pTInitializer == NULL)
    {
        return;
    }
    if (pTInitializer->Type == TInitializerListType_ID)
    {
        TInitializerListType_CodePrint(program,
                                       options,
                                       pDeclarator,
                                       pDeclarationSpecifiers,
                                       (struct TInitializerListType*)pTInitializer, fp);
    }
    else
    {
        TExpression_CodePrint(program, options, (struct TExpression*)pTInitializer, "", fp);
    }


}



static void TPointerList_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TPointerList* p, struct StrBuilder* fp)
{
    ForEachListItem(struct TPointer, pItem, p)
    {
        TPointer_CodePrint(program, options, pItem, fp);
    }
}

static void TParameterList_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TParameterList* p, struct StrBuilder* fp)
{



    ForEachListItem(struct TParameter, pItem, p)
    {
        //if (!List_IsFirstItem(p, pItem))
        //{
        //  TNodeClueList_CodePrint(options, &pItem->ClueList, fp);
        //            Output_Append(fp, options,  ",");
        //}
        //TParameterDeclaration * pItem = p->pItems[i];
        TParameter_CodePrint(program, options, pItem, fp);
    }



}

static void TParameterTypeList_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TParameterTypeList* p, struct StrBuilder* fp)
{
    //Output_Append(fp, options,  "(");
    TParameterList_CodePrint(program, options, &p->ParameterList, fp);

    if (p->bVariadicArgs)
    {
        //TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        //Output_Append(fp, options,  ",");

        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, "...");
    }
    //Output_Append(fp, options,  ")");

}
static void TDeclarator_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TDeclarator* p, bool bPrintName, struct StrBuilder* fp);

static void TDirectDeclarator_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TDirectDeclarator* pDirectDeclarator,

                                        bool bPrintName,
                                        struct StrBuilder* fp)
{
    if (pDirectDeclarator == NULL)
    {
        return;
    }
    //fprintf(fp, "{");


    if (pDirectDeclarator->Identifier)
    {
        //identifier
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList0, fp);
        if (bPrintName)
        {
            Output_Append(fp, options, pDirectDeclarator->Identifier);
        }
        //true;
    }
    else  if (pDirectDeclarator->pDeclarator)
    {
        //( declarator )
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList0, fp);
        Output_Append(fp, options, "(");

        TDeclarator_CodePrint(program, options, pDirectDeclarator->pDeclarator, bPrintName, fp);

        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList1, fp);
        Output_Append(fp, options, ")");
    }

    if (pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeArray)
    {
        /*
        direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
        direct-declarator [ static type-qualifier-listopt assignment-expression ]
        direct-declarator [ type-qualifier-list static assignment-expression ]
        */
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList2, fp);
        Output_Append(fp, options, "[");
        if (pDirectDeclarator->pExpression)
        {
            TExpression_CodePrint(program, options, pDirectDeclarator->pExpression, "assignment-expression", fp);
        }
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList3, fp);
        Output_Append(fp, options, "]");
    }


    if (pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
    {
        //( parameter-type-list )
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList2, fp);
        Output_Append(fp, options, "(");
        TParameterTypeList_CodePrint(program, options, &pDirectDeclarator->Parameters, fp);
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList3, fp);
        Output_Append(fp, options, ")");
    }

    if (pDirectDeclarator->pDirectDeclarator)
    {
        //fprintf(fp, "\"direct-declarator\":");
        TDirectDeclarator_CodePrint(program, options, pDirectDeclarator->pDirectDeclarator, bPrintName, fp);
    }


    //fprintf(fp, "}");

}

static void TDeclarator_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TDeclarator* p, bool bPrintName, struct StrBuilder* fp)
{
    TPointerList_CodePrint(program, options, &p->PointerList, fp);
    TDirectDeclarator_CodePrint(program, options, p->pDirectDeclarator, bPrintName, fp);

}

//void TInitDeclarator_CodePrint(struct SyntaxTree* program, 
//struct PrintCodeOptions * options, 
//TI/nitDeclarator* p,    
//struct StrBuilder* fp);



void TStructDeclarator_CodePrint(struct SyntaxTree* program,
                                 struct PrintCodeOptions* options,
                                 struct TSpecifierQualifierList* pSpecifierQualifierList,
                                 TStructDeclarator* p,
                                 struct StrBuilder* fp)
{

    TDeclarator_CodePrint(program, options, p->pDeclarator, true/*bPrintName*/, fp);
    if (p->pInitializer)
    {
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "/*@");
        }

        Output_Append(fp, options, "=");

        struct PrintCodeOptions options2 = *options;
        options2.Options.bExpandMacros = true;
        options2.Options.bIncludeComments = false;


        TInitializer_CodePrint(program,
                               &options2,
                               p->pDeclarator,
                               (struct TDeclarationSpecifiers*)pSpecifierQualifierList,
                               p->pInitializer,
                               fp);

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "*/");
        }

    }

}

static void TStructDeclaratorList_CodePrint(struct SyntaxTree* program,
                                            struct PrintCodeOptions* options,
                                            struct TSpecifierQualifierList* pSpecifierQualifierList,
                                            struct TStructDeclaratorList* p,
                                            struct StrBuilder* fp)
{




    ForEachListItem(struct TInitDeclarator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
        {
            TNodeClueList_CodePrint(options, &pItem->ClueList0, fp);
            Output_Append(fp, options, ",");
        }
        TStructDeclarator_CodePrint(program, options, pSpecifierQualifierList, pItem, fp);
    }



}

static void TStructDeclaration_CodePrint(struct SyntaxTree* program,
                                         struct PrintCodeOptions* options,
                                         struct TStructDeclaration* p,
                                         struct StrBuilder* fp)
{
    TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, fp);
    TStructDeclaratorList_CodePrint(program,
                                    options,
                                    &p->SpecifierQualifierList,
                                    &p->DeclaratorList, fp);


    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, ";");


}

static void TAnyStructDeclaration_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TAnyStructDeclaration* p, struct StrBuilder* fp)
{
    switch (p->Type)
    {
        case TStructDeclaration_ID:
            TStructDeclaration_CodePrint(program, options, (struct TStructDeclaration*)p, fp);
            break;

        default:
            //assert(false);
            break;
    }


}

static void StorageSpecifier_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TStorageSpecifier* p, struct StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, TokenToString(p->Token));
}

static void TFunctionSpecifier_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TFunctionSpecifier* p, struct StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, TokenToString(p->Token));
}


static void TTypeQualifier_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TTypeQualifier* p, struct StrBuilder* fp)
{
    //TODO nao pode colocr isso se veio de comentario

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    if (p->Token == TK_AUTO)
    {
        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "/*@");
        }

        Output_Append(fp, options, "auto");

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "*/");
        }
    }
    else if (p->Token == TK_LEFT_SQUARE_BRACKET)
    {
        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "/*@");
        }
        //TODO espacos
        Output_Append(fp, options, "[");
        Output_Append(fp, options, p->SizeIdentifier);
        Output_Append(fp, options, "]");

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "*/");
        }

    }
    else
    {

        Output_Append(fp, options, TokenToString(p->Token));
    }

#ifdef LANGUAGE_EXTENSIONS
    if (p->Token == TK_SIZEOF)
    {
        //tODO ja esta nos comentarios
        //Output_Append(fp, options, "(");
        //Output_Append(fp, options, p->SizeIdentifier);
        //Output_Append(fp, options, ")");

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            //Output_Append(fp, options, "@*/");
        }
    }
#endif
}

static void TTypeQualifierList_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TTypeQualifierList* p, struct StrBuilder* fp)
{
    for (int i = 0; i < p->Size; i++)
    {
        struct TTypeQualifier* pItem = p->Data[i];
        TTypeQualifier_CodePrint(program, options, pItem, fp);
    }

}
static void TPointer_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TPointer* pPointer, struct StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &pPointer->ClueList0, fp);
    Output_Append(fp, options, "*");
    TTypeQualifierList_CodePrint(program, options, &pPointer->Qualifier, fp);
}

void TSpecifierQualifierList_CodePrint(struct SyntaxTree* program,
                                       struct PrintCodeOptions* options,
                                       struct TSpecifierQualifierList* pDeclarationSpecifiers,
                                       struct StrBuilder* fp)
{
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        if (i > 0 && options->Options.bCannonical)
        {
            //gerar espaco entre eles para nao grudar no modo cannonico
            Output_Append(fp, options, " ");
        }

        struct TSpecifierQualifier* pItem = pDeclarationSpecifiers->pData[i];
        switch (pItem->Type)
        {

            case TSingleTypeSpecifier_ID:
                TSingleTypeSpecifier_CodePrint(program, options, (struct TSingleTypeSpecifier*)pItem, fp);
            break;

            case TStorageSpecifier_ID:
                StorageSpecifier_CodePrint(program, options, (struct TStorageSpecifier*)pItem, fp);
            break;
            case TTypeQualifier_ID:
                TTypeQualifier_CodePrint(program, options, (struct TTypeQualifier*)pItem, fp);
            break;
            case TFunctionSpecifier_ID:
                TFunctionSpecifier_CodePrint(program, options, (struct TFunctionSpecifier*)pItem, fp);
            break;
            //case TAlignmentSpecifier_ID: 
            ///TAlignmentSpecifier_CodePrint(program, options, (struct TAlignmentSpecifier*)pItem,  fp);
            //break;

            case TStructUnionSpecifier_ID:
                TStructUnionSpecifier_CodePrint(program, options, (struct TStructUnionSpecifier*)pItem, fp);
            break;

            case TEnumSpecifier_ID:
                TEnumSpecifier_CodePrint(program, options, (struct TEnumSpecifier*)pItem, fp);
            break;

            default:
                //assert(false);
                break;
        }
    }


}

void TDeclarationSpecifiers_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TDeclarationSpecifiers* pDeclarationSpecifiers, struct StrBuilder* fp)
{

    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        struct TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];

        switch (pItem->Type)
        {

            case TSingleTypeSpecifier_ID:
                TSingleTypeSpecifier_CodePrint(program, options, (struct TSingleTypeSpecifier*)pItem, fp);
            break;

            case TStructUnionSpecifier_ID:
                TStructUnionSpecifier_CodePrint(program, options, (struct TStructUnionSpecifier*)pItem, fp);
            break;

            case TEnumSpecifier_ID:
                TEnumSpecifier_CodePrint(program, options, (struct TEnumSpecifier*)pItem, fp);
            break;

            case TStorageSpecifier_ID:
                StorageSpecifier_CodePrint(program, options, (struct TStorageSpecifier*)pItem, fp);
            break;
            case TTypeQualifier_ID:
                TTypeQualifier_CodePrint(program, options, (struct TTypeQualifier*)pItem, fp);
            break;
            case TFunctionSpecifier_ID:
                TFunctionSpecifier_CodePrint(program, options, (struct TFunctionSpecifier*)pItem, fp);
            break;

            //case TAlignmentSpecifier_ID: 
            ///TAlignmentSpecifier_CodePrint(program, options, (struct TAlignmentSpecifier*)pItem,  fp);
            //break;

            default:
                //assert(false);
                break;
        }
    }





}

void TInitDeclarator_CodePrint(struct SyntaxTree* program,
                               struct PrintCodeOptions* options,
                               struct TDeclarator* pDeclarator,
                               struct TDeclarationSpecifiers* pDeclarationSpecifiers,
                               struct TInitDeclarator* p,
                               struct StrBuilder* fp)
{
    TDeclarator_CodePrint(program, options, p->pDeclarator, true/*bPrintName*/, fp);

    if (p->pInitializer)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "=");
        TInitializer_CodePrint(program,
                               options,
                               pDeclarator,
                               pDeclarationSpecifiers,
                               p->pInitializer,

                               fp);
    }

}



void TInitDeclaratorList_CodePrint(struct SyntaxTree* program,
                                   struct PrintCodeOptions* options,

                                   struct TDeclarationSpecifiers* pDeclarationSpecifiers,
                                   struct TInitDeclaratorList* p,

                                   struct StrBuilder* fp)
{

    //fprintf(fp, "[");
    ForEachListItem(struct TInitDeclarator, pInitDeclarator, p)
    {
        if (!List_IsFirstItem(p, pInitDeclarator))
            Output_Append(fp, options, ",");


        TInitDeclarator_CodePrint(program,
                                  options,
                                  pInitDeclarator->pDeclarator,
                                  pDeclarationSpecifiers,
                                  pInitDeclarator,
                                  fp);
    }

    //  fprintf(fp, "]");

}



struct TStructUnionSpecifier* GetStructSpecifier(struct SyntaxTree* program, struct TDeclarationSpecifiers* specifiers);


static bool FindListStructPattern(struct SyntaxTree* program,
                                  struct TParameter* pParameter,
                                  bool* pbItemIsPointer,
                                  bool* pbItemIsAutoPointer,
                                  struct StrBuilder* itemTypeName,
                                  struct StrBuilder* arrayName)
{
    //Esta funcao analisa a struct e ve se ela eh compativel com o tipo vector.
    //ter size, capacity e um vector de items

    bool bHasHead = false;
    bool bHasTail = false;

    //O primeiro parametro tem que ser struct or typedef para struct
    struct TStructUnionSpecifier* pStructUnionSpecifier =
        GetStructSpecifier(program, &pParameter->Specifiers);
    if (pStructUnionSpecifier)
    {
        //Vou analisar a "digital" da struct
        //ok tem a definicao completa da struct
        for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
        {
            struct TAnyStructDeclaration* pAnyStructDeclaration =
                pStructUnionSpecifier->StructDeclarationList.pItems[i];

            struct TStructDeclaration* pStructDeclaration =
                TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
            if (pStructDeclaration)
            {
                TStructDeclarator* pStructDeclarator =
                    pStructDeclaration->DeclaratorList.pHead;

                while (pStructDeclarator)
                {
                    const char* structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);


                    bool bIsPointer1 =
                        TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 1);

                    bool bIsPointer2 =
                        TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 2);
                    if (bIsPointer1)

                    {
                        if (strcmp(structDeclaratorName, "pHead") == 0)
                        {
                            bHasHead = true;
                        }
                        if (strcmp(structDeclaratorName, "pTail") == 0)
                        {
                            bHasTail = true;
                        }
                    }

                    pStructDeclarator = (pStructDeclarator)->pNext;
                }
            }
        }
    }

    return bHasHead && bHasTail;
}

static bool FindVectorStructPattern(struct SyntaxTree* program,
                                    struct TParameter* pParameter,
                                    bool* pbItemIsPointer,
                                    bool* pbItemIsAutoPointer,
                                    struct StrBuilder* itemTypeName,
                                    struct StrBuilder* arrayName)
{
    //Esta funcao analisa a struct e ve se ela eh compativel com o tipo vector.
    //ter size, capacity e um vector de items
    bool bHasVector = false;
    bool bHasSize = false;
    bool bHasCapacity = false;

    //O primeiro parametro tem que ser struct or typedef para struct
    struct TStructUnionSpecifier* pStructUnionSpecifier =
        GetStructSpecifier(program, &pParameter->Specifiers);
    if (pStructUnionSpecifier)
    {
        //Vou analisar a "digital" da struct
        //ok tem a definicao completa da struct
        for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
        {
            struct TAnyStructDeclaration* pAnyStructDeclaration =
                pStructUnionSpecifier->StructDeclarationList.pItems[i];

            struct TStructDeclaration* pStructDeclaration =
                TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
            if (pStructDeclaration)
            {
                TStructDeclarator* pStructDeclarator =
                    pStructDeclaration->DeclaratorList.pHead;

                while (pStructDeclarator)
                {
                    const char* structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);


                    bool bIsPointer1 =
                        TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 1);

                    bool bIsPointer2 =
                        TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 2);

                    if (bIsPointer1 || bIsPointer2)
                    {
                        bHasVector = true;
                        StrBuilder_Set(arrayName, structDeclaratorName);

                        //se eh um array de ponteiros 
                        bool bItemIsPointer =
                            TPointerList_IsPointer(&pStructDeclarator->pDeclarator->PointerList);

                        *pbItemIsPointer = bIsPointer2;

                        //se eh um array de ponteiros  donos
                        bool bItemIsAutoPointer =
                            TPointerList_IsAutoPointer(&pStructDeclarator->pDeclarator->PointerList);

                        *pbItemIsAutoPointer = bItemIsPointer;

                        //este eh array
                        //vamos ver o tipo do item e se ele eh auto
                        //pStructDeclaration->SpecifierQualifierList
                        // struct StrBuilder itemTypeStr = STRBUILDER_INIT;
                        struct TTypeName* pTypeName = NULL;
                        struct PrintCodeOptions  options = CODE_PRINT_OPTIONS_INIT;
                        options.Options.bCannonical = true;
                        TSpecifierQualifierList_CodePrint(program, &options, &pStructDeclaration->SpecifierQualifierList, itemTypeName);
                        //StrBuilder_Destroy(&itemTypeStr);
                    }
                    else  if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
                    {
                        if (strcmp(structDeclaratorName, "Size") == 0)
                        {
                            bHasSize = true;
                        }
                        else if (strcmp(structDeclaratorName, "Capacity") == 0)
                        {
                            bHasCapacity = true;
                        }
                    }

                    pStructDeclarator = (pStructDeclarator)->pNext;
                }
            }
        }
    }

    return bHasSize && bHasCapacity&& bHasVector;
}


struct TemplateVar
{
    const char* Name;
    const char* Value;
};

const char* FindValue(const char* name, int namesize, struct TemplateVar* args, int argssize)
{
    for (int i = 0; i < argssize; i++)
    {
        if (namesize == strlen(args[i].Name) &&
            strncmp(name, args[i].Name, namesize) == 0)
        {
            return args[i].Value;
        }
    }
    return "?";
}

void StrBuilder_Template(struct StrBuilder* p,
                         const char* tmpt,
                         struct TemplateVar* vars,
                         int size,
                         int identationLevel)
{


    const char* pch = tmpt;

    //Move tudo para o lado de acordo com a identacao
    for (int i = 0; i < identationLevel * 4; i++)
    {
        StrBuilder_AppendChar(p, ' ');
    }

    //agora nove de acordo com os espacos
    while (*pch == ' ')
    {
        for (int j = 0; j < 4; j++)
        {
            StrBuilder_AppendChar(p, ' ');
        }

        pch++;
    }

    while (*pch)
    {
        if (*pch == '$')
        {

            pch++;
            const char* name = pch;
            int namesize = 0;
            if (*pch &&
                (*pch >= 'a' && *pch <= 'z') ||
                (*pch >= 'A' && *pch <= 'Z') ||
                (*pch >= '_'))
            {
                pch++;
                namesize++;

                while (*pch &&
                    (*pch >= 'a' && *pch <= 'z') ||
                       (*pch >= 'A' && *pch <= 'Z') ||
                       (*pch >= '0' && *pch <= '9') ||
                       (*pch >= '_')) //$X_X
                {
                    pch++;
                    namesize++;
                }
            }

            const char* val =
                FindValue(name, namesize, vars, size);
            StrBuilder_Append(p, val);
        }
        else
        {
            //Este \b eh usado para juntar identificador
            //$part1_part2
            //$part1\b_part2
            //

            if (*pch == '\n')
            {
                StrBuilder_AppendChar(p, *pch);
                pch++;


                if (*pch != '\0') //se for o ultimo nao move
                {//Move tudo para o lado de acordo com a identacao
                    for (int i = 0; i < identationLevel * 4; i++)
                    {
                        StrBuilder_AppendChar(p, ' ');
                    }

                    //agora nove de acordo com os espacos
                    while (*pch == ' ')
                    {
                        for (int j = 0; j < 4; j++)
                        {
                            StrBuilder_AppendChar(p, ' ');
                        }
                        pch++;
                    }
                }
            }
            else
            {
                if (*pch != '\b')
                {
                    StrBuilder_AppendChar(p, *pch);
                }
                pch++;
            }
        }
    }
}

void GetPrefixSuffix(const char* psz, struct StrBuilder* prefix, struct StrBuilder* suffix)
{
    while (*psz && *psz != '_')
    {
        StrBuilder_AppendChar(prefix, *psz);
        psz++;
    }

    if (*psz == '_')
        psz++;

    while (*psz)
    {
        StrBuilder_AppendChar(suffix, *psz);
        psz++;
    }
}

static int FindRuntimeID(struct SyntaxTree* program,
                         const char* structOrTypeName,
                         struct StrBuilder* idname)
{
    ////////////
    struct TDeclaration* pFinalDecl =
        SyntaxTree_GetFinalTypeDeclaration(program, structOrTypeName);
    int typeInt = 0;
    struct TStructUnionSpecifier* pStructUnionSpecifier = NULL;
    if (pFinalDecl)
    {
        typeInt = 1; //typefef
        if (pFinalDecl->Specifiers.Size > 1)
        {
            pStructUnionSpecifier =
                TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
            if (pStructUnionSpecifier->Tag)
            {
                //procura a mais completa
                pStructUnionSpecifier =
                    SymbolMap_FindCompleteStructUnionSpecifier(&program->GlobalScope, pStructUnionSpecifier->Tag);
            }
        }
    }
    else
    {
        typeInt = 2; //struct
        pStructUnionSpecifier =
            SymbolMap_FindCompleteStructUnionSpecifier(&program->GlobalScope, structOrTypeName);
    }
    //////////////

    if (pStructUnionSpecifier &&
        pStructUnionSpecifier->UnionSet.pHead != NULL)
    {
        if (pStructUnionSpecifier->StructDeclarationList.Size > 0)
        {
            struct TStructDeclaration* pStructDeclaration =
                TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[0]);
            if (pStructDeclaration)
            {
                TStructDeclarator* pStructDeclarator =
                    pStructDeclaration->DeclaratorList.pHead;

                //o primeiro item tem que ser o ID
                if (pStructDeclarator)
                {
                    const char* structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);
                    //if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
                    {
                        StrBuilder_Set(idname, structDeclaratorName);
                    }
                }
            }
        }
    }
    return typeInt;
}


static int FindIDValue(struct SyntaxTree* program,
                       const char* structOrTypeName,
                       struct StrBuilder* idname)
{
    ////////////
    struct TDeclaration* pFinalDecl =
        SyntaxTree_GetFinalTypeDeclaration(program, structOrTypeName);
    int typeInt = 0;
    struct TStructUnionSpecifier* pStructUnionSpecifier = NULL;
    if (pFinalDecl)
    {
        typeInt = 1; //typefef
        if (pFinalDecl->Specifiers.Size > 1)
        {
            pStructUnionSpecifier =
                TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
            if (pStructUnionSpecifier->Tag)
            {
                //procura a mais completa
                pStructUnionSpecifier =
                    SymbolMap_FindCompleteStructUnionSpecifier(&program->GlobalScope, pStructUnionSpecifier->Tag);
            }
        }
    }
    else
    {
        typeInt = 2; //struct
        pStructUnionSpecifier =
            SymbolMap_FindCompleteStructUnionSpecifier(&program->GlobalScope, structOrTypeName);
    }
    //////////////

    if (pStructUnionSpecifier)
    {
        if (pStructUnionSpecifier->StructDeclarationList.Size > 0)
        {
            struct TStructDeclaration* pStructDeclaration =
                TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[0]);
            if (pStructDeclaration)
            {
                TStructDeclarator* pStructDeclarator =
                    pStructDeclaration->DeclaratorList.pHead;

                //o primeiro item tem que ser o ID
                if (pStructDeclarator)
                {
                    const char* structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);
                    //if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
                    {
                        struct PrintCodeOptions options2 = CODE_PRINT_OPTIONS_INIT;
                        TInitializer_CodePrint(program, &options2, pStructDeclarator->pDeclarator,
                            (struct TDeclarationSpecifiers*) & pStructDeclaration->SpecifierQualifierList,
                                               pStructDeclarator->pInitializer, idname);

                        //StrBuilder_Set(idname, structDeclaratorName);
                    }
                }
            }
        }
    }
    return typeInt;
}


void FindUnionSetOf(struct SyntaxTree* program,
                    const char* structOrTypeName,
                    struct Map2* map)
{
    struct TDeclaration* pFinalDecl =
        SyntaxTree_GetFinalTypeDeclaration(program, structOrTypeName);
    int typeInt = 0;
    struct TStructUnionSpecifier* pStructUnionSpecifier = NULL;
    if (pFinalDecl)
    {
        typeInt = 1; //typefef
        if (pFinalDecl->Specifiers.Size > 1)
        {
            pStructUnionSpecifier =
                TDeclarationSpecifier_As_TStructUnionSpecifier(pFinalDecl->Specifiers.pData[1]);
            if (pStructUnionSpecifier->Tag)
            {
                //procura a mais completa
                pStructUnionSpecifier =
                    SymbolMap_FindCompleteStructUnionSpecifier(&program->GlobalScope, pStructUnionSpecifier->Tag);
            }
        }
    }
    else
    {
        typeInt = 2; //struct
        pStructUnionSpecifier =
            SymbolMap_FindCompleteStructUnionSpecifier(&program->GlobalScope, structOrTypeName);
    }

    if (pStructUnionSpecifier &&
        pStructUnionSpecifier->UnionSet.pHead != NULL)
    {
        struct TUnionSetItem* pCurrent =
            pStructUnionSpecifier->UnionSet.pHead;
        while (pCurrent)
        {
            FindUnionSetOf(program, pCurrent->Name, map);
            pCurrent = pCurrent->pNext;
        }
    }
    else
    {
        void* pp;
        Map2_SetAt(map, structOrTypeName, (void*)typeInt, &pp);
    }
}

void UnionTypeDefault(struct SyntaxTree* program,
                      struct PrintCodeOptions* options,
                      const char* structName,
                      struct TParameterTypeList* pArgsOpt, //parametros
                      const char* parameterName,
                      const char* functionSuffix,
                      struct StrBuilder* fp);
static const char* GetNullStr(struct SyntaxTree* program);



static void DefaultFunctionDefinition_CodePrint(struct SyntaxTree* program,
                                                struct PrintCodeOptions* options,
                                                struct TDeclaration* p,
                                                struct StrBuilder* fp)
{

    //Retorno da funcao
    struct TDeclarationSpecifiers* pSpecifiers =
        &p->Specifiers;

    const char* funcName =
        TDeclarator_GetName(p->InitDeclaratorList.pHead->pDeclarator);

    struct StrBuilder functionPrefix = STRBUILDER_INIT;
    struct StrBuilder functionSuffix = STRBUILDER_INIT;

    GetPrefixSuffix(funcName, &functionPrefix, &functionSuffix);

    //parametros


    struct TParameterTypeList* pArgs =
        TDeclaration_GetFunctionArguments(p);

    struct TParameter* pFirstParameter =
        TParameterTypeList_GetParameterByIndex(pArgs, 0);


    const char* functionTagName = TDeclaration_FindFunctionTagName(p, &program->GlobalScope);


    struct TParameter* pSecondParameter =
        TParameterTypeList_GetParameterByIndex(pArgs, 1);


    if (functionTagName && strcmp(functionTagName, "create") == 0)
    {
        options->IdentationLevel++;

        InstanciateDestroy2(program,
                            options,
                            (struct TSpecifierQualifierList*)(pSpecifiers),
                            p->InitDeclaratorList.pHead->pDeclarator,
                            NULL,
                            pArgs,
                            "p",
                            NULL /*not used*/,
                            ActionCreate,
                            SearchInit,
                            NULL,
                            fp);
        options->IdentationLevel--;
    }
    else if (functionTagName && strcmp(functionTagName, "init") == 0 && pFirstParameter != NULL)
    {
        options->IdentationLevel++;
        InstanciateDestroy2(program,
                            options,
                            (struct TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
                            &pFirstParameter->Declarator,
                            NULL,
                            pArgs,/*args fazer inicializacao conforme parametro*/
                            TParameter_GetName(pFirstParameter),
                            NULL /*not used*/,
                            ActionInitContent,
                            SearchNone,
                            NULL,
                            fp);
        options->IdentationLevel--;
    }
    else if (functionTagName && strcmp(functionTagName, "destroy") == 0 && pFirstParameter != NULL)
    {

        options->IdentationLevel++;
        InstanciateDestroy2(program,
                            options,
                            (struct TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
                            &pFirstParameter->Declarator,
                            NULL,
                            NULL,/*args*/
                            TParameter_GetName(pFirstParameter),
                            NULL /*not used*/,
                            ActionDestroyContent,
                            SearchNone,
                            NULL,
                            fp);
        options->IdentationLevel--;
    }
    else if (functionTagName && strcmp(functionTagName, "delete") == 0 && pFirstParameter != NULL)
    {

        options->IdentationLevel++;
        InstanciateDestroy2(program,
                            options,
                            (struct TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
                            &pFirstParameter->Declarator,
                            NULL,
                            NULL,/*args*/
                            TParameter_GetName(pFirstParameter),
                            NULL /*not used*/,
                            ActionDelete,
                            SearchDestroy,
                            NULL,
                            fp);
        options->IdentationLevel--;
    }
    else
    {
        //Agora entre no auto tag.
        const char* functionTag =
            TDeclaration_FindFunctionTagName(p, &program->GlobalScope);

        if (functionTag == NULL && !options->Options.bNoImplicitTag)
        {
            //implicity function tag

            if (pFirstParameter != NULL &&
                pSecondParameter != NULL &&
                IsSuffix(funcName, "_Reserve"))
            {
                functionTag = "reserve";
            }
            else if (pFirstParameter != NULL &&
                     pSecondParameter != NULL &&
                     IsSuffix(funcName, "_PushBack"))
            {
                functionTag = "push";
            }
        }

        if (functionTag && strcmp(functionTag, "reserve") == 0)
        {
            bool bItemIsPointer;
            bool bItemIsAutoPointer;
            struct StrBuilder itemType = STRBUILDER_INIT;
            struct StrBuilder arrayName = STRBUILDER_INIT;

            //Implemetancao para vector
            if (FindVectorStructPattern(program,
                pFirstParameter,
                &bItemIsPointer,
                &bItemIsAutoPointer,
                &itemType,
                &arrayName))
            {
                const char* pszTemplatePointer =
                    "if ($nelements > $p->Capacity)\n"
                    "{\n"
                    " $type** pnew = $p->$data;\n"
                    " pnew = ($type**)$realloc(pnew, $nelements * sizeof($type*));\n"
                    " if (pnew)\n"
                    " {\n"
                    "  $p->$data = pnew;\n"
                    "  $p->Capacity = $nelements;\n"
                    " }\n"
                    "}\n";

                const char* pszTemplateNotPointer =
                    "if ($nelements > $p->Capacity)\n"
                    "{\n"
                    " $type* pnew = $p->$data;\n"
                    " pnew = ($type*)$realloc(pnew, $nelements * sizeof($type));\n"
                    " if (pnew)\n"
                    " {\n"
                    "  $p->$data = pnew;\n"
                    "  $p->Capacity = $nelements;\n"
                    " }\n"
                    "}\n";

                const char* pszTemplate =
                    bItemIsPointer ? pszTemplatePointer : pszTemplateNotPointer;

                struct TemplateVar vars[] = {
                    {"p", TParameter_GetName(pFirstParameter)},
                {"nelements", TParameter_GetName(pSecondParameter)},
                {"type", itemType.c_str},
                {"data", arrayName.c_str},
                {"realloc", GetReallocStr(program)}
                };

                StrBuilder_Template(fp,
                                    pszTemplate,
                                    vars,
                                    sizeof(vars) / sizeof(vars[0]),
                                    1 /*options->IdentationLevel*/);
            }

            StrBuilder_Destroy(&itemType);
            StrBuilder_Destroy(&arrayName);
        }
        else if (functionTag && strcmp(functionTag, "push") == 0)
        {
            bool bItemIsPointer;
            bool bItemIsAutoPointer;
            struct StrBuilder itemType = STRBUILDER_INIT;
            struct StrBuilder arrayName = STRBUILDER_INIT;

            //Implemetancao para vector
            if (FindVectorStructPattern(program,
                pFirstParameter,
                &bItemIsPointer,
                &bItemIsAutoPointer,
                &itemType,
                &arrayName))
            {
                //TODO procurar pelas funcoes com tag
                bool bHasReserve =
                    SymbolMap_FindObjFunction2(&program->GlobalScope, functionPrefix.c_str, "Reserve") != 0;
                const char* pszTemplate = "";

                if (bHasReserve)
                {
                    pszTemplate = "if ($p->Size + 1 > $p->Capacity)\n"
                        "{\n"
                        " int n = $p->Capacity * 2;\n"
                        " if (n == 0)\n"
                        " {\n"
                        "  n = 1;\n"
                        " }\n"
                        " $prefix\b_Reserve($p, n);\n"
                        "}\n"
                        "$p->$data[$p->Size] = $nelements;\n"
                        "$p->Size++;\n";
                }
                else
                {
                    if (bItemIsPointer)
                    {
                        pszTemplate = "if ($p->Size + 1 > $p->Capacity)\n"
                            "{\n"
                            " int n = $p->Capacity * 2;\n"
                            " if (n == 0)\n"
                            " {\n"
                            "  n = 1;\n"
                            " }\n"
                            " $type** pnew = $p->$data;\n"
                            " pnew = ($type**)$realloc(pnew, n * sizeof($type*));\n"
                            " if (pnew)\n"
                            " {\n"
                            "  $p->$data = pnew;\n"
                            "  $p->Capacity = n;\n"
                            " }\n"
                            "}\n"
                            "$p->$data[$p->Size] = $nelements;\n"
                            "$p->Size++;\n";
                    }
                    else
                    {
                        pszTemplate = "if ($p->Size + 1 > $p->Capacity)\n"
                            "{\n"
                            " int n = $p->Capacity * 2;\n"
                            " if (n == 0)\n"
                            " {\n"
                            "  n = 1;\n"
                            " }\n"
                            " $type* pnew = $p->$data;\n"
                            " pnew = ($type*)$realloc(pnew, n * sizeof($type));\n"
                            " if (pnew)\n"
                            " {\n"
                            "  $p->$data = pnew;\n"
                            "  $p->Capacity = n;\n"
                            " }\n"
                            "}\n"
                            "$p->$data[$p->Size] = $nelements;\n"
                            "$p->Size++;\n";
                    }


                }

                struct TemplateVar vars[] = {
                    {"p", TParameter_GetName(pFirstParameter)},
                {"nelements", TParameter_GetName(pSecondParameter)},
                {"type", itemType.c_str},
                {"data", arrayName.c_str},
                {"prefix", functionPrefix.c_str},
                {"realloc", GetReallocStr(program)}
                };

                StrBuilder_Template(fp,
                                    pszTemplate,
                                    vars,
                                    sizeof(vars) / sizeof(vars[0]),
                                    1/*options->IdentationLevel*/);
            }
            else if (FindListStructPattern(program,
                     pFirstParameter,
                     &bItemIsPointer,
                     &bItemIsAutoPointer,
                     &itemType,
                     &arrayName))
            {
                struct TemplateVar vars[] = {
                    {"pList", TParameter_GetName(pFirstParameter)},
                {"pItem", TParameter_GetName(pSecondParameter)},
                {"type", itemType.c_str},
                {"data", arrayName.c_str},
                {"prefix", functionPrefix.c_str},
                {"null", GetNullStr(program)}
                };
                //o item apontado tem que ter pNext verificar isso
                //e colocar erro se nao tiver
                const char* pszTemplate =
                    "if ($pList->pHead == $null)\n"
                    "{\n"
                    " $pList->pHead = $pItem;\n"
                    "}\n"
                    "else\n"
                    "{\n"
                    " $pList->pTail->pNext = $pItem;\n"
                    "}\n"
                    "$pList->pTail = $pItem; \n";

                StrBuilder_Template(fp,
                                    pszTemplate,
                                    vars,
                                    sizeof(vars) / sizeof(vars[0]),
                                    1/*options->IdentationLevel*/);
            }

            StrBuilder_Destroy(&itemType);
            StrBuilder_Destroy(&arrayName);
        }
        else
        {
            if (pFirstParameter != NULL)
            {
                struct TStructUnionSpecifier* pStructUnionSpecifier =
                    GetStructSpecifier(program, &pFirstParameter->Specifiers);
                if (pStructUnionSpecifier &&
                    pStructUnionSpecifier->UnionSet.pHead != NULL)
                {
                    options->IdentationLevel++;
                    UnionTypeDefault(program,
                                     options,
                                     pStructUnionSpecifier->Tag,
                                     pArgs,
                                     TParameter_GetName(pFirstParameter),
                                     functionSuffix.c_str,
                                     fp);
                    options->IdentationLevel--;
                }
            }
        }
    }

    StrBuilder_Destroy(&functionPrefix);
    StrBuilder_Destroy(&functionSuffix);

}

static void TDeclaration_CodePrint(struct SyntaxTree* program,
                                   struct PrintCodeOptions* options,
                                   struct TDeclaration* p,

                                   struct StrBuilder* fp)
{
    TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, fp);

    TInitDeclaratorList_CodePrint(program,
                                  options,
                                  &p->Specifiers,
                                  &p->InitDeclaratorList, fp);

    if (p->FunctionTag && !p->bAutoTag)
    {
        TNodeClueList_CodePrint(options, &p->ClueList00, fp);

        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "/*@");
        }

        Output_Append(fp, options, ":");
        TNodeClueList_CodePrint(options, &p->ClueList001, fp);
        Output_Append(fp, options, p->FunctionTag);


        if (options->Options.Target == CompilerTarget_Annotated)
        {
            Output_Append(fp, options, "*/");
        }
    }

    if (p->pCompoundStatementOpt != NULL)
    {
        /*
        typedef struct Array { int data; ... } Items;
        void Items_Add(Items* p,int i) {...}
        void Items_Delete(Items* p,int i) {...}
        */

        if (p->bDefault)
        {
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);

            if (options->Options.Target == CompilerTarget_Annotated)
            {
                if (options->Options.Target == CompilerTarget_Annotated)
                {
                    Output_Append(fp, options, "/*@");
                }

                Output_Append(fp, options, "default");

                if (options->Options.Target == CompilerTarget_Annotated)
                {
                    Output_Append(fp, options, "*/");
                }


                TNodeClueList_CodePrint(options, &p->pCompoundStatementOpt->ClueList0, fp);
                Output_Append(fp, options, "{\n");

                DefaultFunctionDefinition_CodePrint(program,
                                                    options,
                                                    p,

                                                    fp);

                Output_Append(fp, options, "}");
            }
            else if (options->Options.Target == CompilerTarget_CXX)
            {
                Output_Append(fp, options, "default;");
            }


            return;
        }
        else
        {
            if (p->pCompoundStatementOpt != NULL)
            {
                //normal
                TCompoundStatement_CodePrint(program,
                                             options,
                                             p->pCompoundStatementOpt,

                                             fp);
            }
        }
    }
    else
    {


        if (p->bDefault)
        {

            if (options->Options.Target == CompilerTarget_Annotated)
            {
                TNodeClueList_CodePrint(options, &p->ClueList0, fp);

                if (options->Options.Target == CompilerTarget_Annotated)
                {
                    Output_Append(fp, options, "/*@");
                }
                Output_Append(fp, options, "default");

                if (options->Options.Target == CompilerTarget_Annotated)
                {
                    Output_Append(fp, options, "*/");
                }

                TNodeClueList_CodePrint(options, &p->ClueList1, fp);
                Output_Append(fp, options, "\n{\n");

                DefaultFunctionDefinition_CodePrint(program,
                                                    options,
                                                    p,

                                                    fp);

                Output_Append(fp, options, "}");
            }
            else if (options->Options.Target == CompilerTarget_CXX)
            {
                TNodeClueList_CodePrint(options, &p->ClueList1, fp);
                Output_Append(fp, options, " default");
                Output_Append(fp, options, ";");
            }


            return;
        }
        else
        {
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, options, ";");
        }
    }


    return;
}

void TTypeName_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TTypeName* p, struct StrBuilder* fp)
{

    TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, fp);

    TDeclarator_CodePrint(program, options, &p->Declarator, true/*bPrintName*/, fp);


}

static void TParameter_CodePrint(struct SyntaxTree* program,
                                 struct PrintCodeOptions* options,
                                 struct TParameter* p,

                                 struct StrBuilder* fp)
{
    TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, fp);
    TDeclarator_CodePrint(program, options, &p->Declarator, true/*bPrintName*/, fp);

    if (p->bHasComma)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, ",");
    }


}

static void TEofDeclaration_CodePrint(struct SyntaxTree* program,
                                      struct PrintCodeOptions* options,
                                      struct TEofDeclaration* p,

                                      struct StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
}

static void TStaticAssertDeclaration_CodePrint(struct SyntaxTree* program,
                                               struct PrintCodeOptions* options,
                                               struct TStaticAssertDeclaration* p,

                                               struct StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "_StaticAssert");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "(");
    TExpression_CodePrint(program, options, p->pConstantExpression, "", fp);
    Output_Append(fp, options, ",");
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);

    TNodeClueList_CodePrint(options, &p->ClueList3, fp);
    Output_Append(fp, options, p->Text);


    TNodeClueList_CodePrint(options, &p->ClueList4, fp);
    Output_Append(fp, options, ")");
    TNodeClueList_CodePrint(options, &p->ClueList5, fp);
    Output_Append(fp, options, ";");

}

static void TGroupDeclaration_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TGroupDeclaration* p, struct StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "#pragma region cprime");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, p->Identifier);
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, "\n");

    struct TDeclaration* pFunction =
        SymbolMap_FindFunction(&program->GlobalScope, p->Identifier);
    if (pFunction)
    {
        TDeclaration_CodePrint(program, options, pFunction, fp);
    }
    else
    {
        struct Map2 map = MAPSTRINGTOPTR_INIT;
        FindUnionSetOf(program, p->Identifier, &map);

        struct StrBuilder idname = STRBUILDER_INIT;

        int ir = FindRuntimeID(program,
                               p->Identifier,
                               &idname);

        for (int i = 0; i < (int)map.nHashTableSize; i++)
        {
            if (map.pHashTable[i])
            {
                const char* derivedName = (const char*)map.pHashTable[i]->Key;
                const char* baseName = p->Identifier;

                struct StrBuilder idnamelocal = STRBUILDER_INIT;

                int ir2 = FindIDValue(program,
                                      derivedName,
                                      &idnamelocal);

                struct TemplateVar vars0[] = {
                    {"base", baseName},
                {"derived", derivedName},
                {"id", idname.c_str},
                {"idvalue", idnamelocal.c_str}
                };

                if ((int)map.pHashTable[i]->pValue == 2)
                {




                    if (ir == 2)
                    {
                        StrBuilder_Template(fp,
                                            "inline struct $derived* $base\b_As_$derived(struct $base* p) { return p->$id == $idvalue ? (struct $derived*) p : 0;}\n"
                                            "inline struct $base* $derived\b_As_$base(struct $derived* p) { return (struct $base*) p; }\n",
                                            vars0,
                                            sizeof(vars0) / sizeof(vars0[0]),
                                            options->IdentationLevel);
                    }
                    else
                    {
                        if (ir == 2)
                        {
                            StrBuilder_Template(fp,
                                                "inline struct $derived* $base\b_As_$derived(struct $base* p) { return p->$id == $idvalue ? (struct $derived*) p : 0;}\n"
                                                "inline struct $base* $derived\b_As_$base(struct $derived* p) { return (struct $base*) p; }\n",
                                                vars0,
                                                sizeof(vars0) / sizeof(vars0[0]),
                                                options->IdentationLevel);
                        }
                        else
                        {
                            StrBuilder_Template(fp,
                                                "inline struct $derived* $base\b_As_$derived($base* p) { return p->$id == $idvalue ? (struct $derived*) p : 0;}\n"
                                                "inline $base* $derived\b_As_$base(struct $derived* p) { return ($base*) p; }\n",
                                                vars0,
                                                sizeof(vars0) / sizeof(vars0[0]),
                                                options->IdentationLevel);
                        }
                    }

                }
                else
                {
                    StrBuilder_Template(fp,
                                        "inline $derived* $base\b_As_$derived($base* p) { return p->$id == $idvalue ? ($derived*) p : 0;}\n"
                                        "inline $base* $derived\b_As_$base($derived* p) { return ($base*) p; }\n",
                                        vars0,
                                        sizeof(vars0) / sizeof(vars0[0]),
                                        options->IdentationLevel);
                }

                StrBuilder_Destroy(&idnamelocal);
            }
        }

        Map2_Destroy(&map, NULL);
        StrBuilder_Destroy(&idname);

    }

    //for (int i = 0; i < p->Declarations.Size; i++)
    //{
      //TAnyDeclaration_CodePrint(program, options, p->Declarations.pItems[i], fp);
    //}
    //TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "#pragma endregion cprime\n");
}

static void TAnyDeclaration_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TAnyDeclaration* pDeclaration, struct StrBuilder* fp)
{
    switch (pDeclaration->Type)
    {
        case TGroupDeclaration_ID:
            TGroupDeclaration_CodePrint(program, options, (struct TGroupDeclaration*)pDeclaration, fp);
            break;

        case TEofDeclaration_ID:
            TEofDeclaration_CodePrint(program, options, (struct TEofDeclaration*)pDeclaration, fp);
            break;

        case TStaticAssertDeclaration_ID:
            TStaticAssertDeclaration_CodePrint(program, options, (struct TStaticAssertDeclaration*)pDeclaration, fp);
            break;

        case TDeclaration_ID:
            TDeclaration_CodePrint(program, options, (struct TDeclaration*)pDeclaration, fp);
            break;

        default:
            //assert(false);
            break;
    }


}

static void TDesignatorList_CodePrint(struct SyntaxTree* program, struct PrintCodeOptions* options, struct TDesignatorList* p, struct StrBuilder* fp)
{



    ForEachListItem(struct TDesignator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
        {
            Output_Append(fp, options, ",");
        }
        TDesignator_CodePrint(program, options, pItem, fp);
    }



}


static void TInitializerListItem_CodePrint(struct SyntaxTree* program,
                                           struct PrintCodeOptions* options,
                                           struct TDeclarator* pDeclarator,
                                           struct TDeclarationSpecifiers* pDeclarationSpecifiers,
                                           struct TInitializerListItem* p,

                                           struct StrBuilder* fp)
{
    if (p->DesignatorList.pHead != NULL)
    {
        TDesignatorList_CodePrint(program, options, &p->DesignatorList, fp);
    }

    TInitializer_CodePrint(program,
                           options,
                           pDeclarator,
                           pDeclarationSpecifiers,
                           p->pInitializer,
                           fp);

    TNodeClueList_CodePrint(options, &p->ClueList, fp);
}



void SyntaxTree_PrintCodeToFile(struct SyntaxTree* pProgram,
                                struct Options* options0,
                                const char* outFileName,
                                const char* inputFileName)
{
    struct PrintCodeOptions options = CODE_PRINT_OPTIONS_INIT;
    options.Options = *options0;

    global_lambda_counter = 0;

    FILE* fp = fopen(outFileName, "w");

    if (fp == NULL)
    {
        printf("cannot open output file %s", outFileName);
        return;
    }



    int k = 0;

    //for (int i = 0; i < pProgram->Files2.size; i++)
    //{
    //  struct TFile *pFile = pProgram->Files2.pItems[i];
    //  printf("\"%s\"\n", pFile->FullPath);
    //}

    struct StrBuilder sb = STRBUILDER_INIT;
    StrBuilder_Reserve(&sb, 80 * 5000);

    for (int i = 0; i < pProgram->Declarations.Size; i++)
    {
        struct TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];

        StrBuilder_Clear(&options.sbPreDeclaration);

        struct StrBuilder sbDeclaration = STRBUILDER_INIT;
        TAnyDeclaration_CodePrint(pProgram, &options, pItem, &sbDeclaration);

        StrBuilder_Append(&sb, options.sbPreDeclaration.c_str);
        StrBuilder_Append(&sb, sbDeclaration.c_str);

        StrBuilder_Destroy(&sbDeclaration);


        fprintf(fp, "%s", sb.c_str);


        StrBuilder_Clear(&sb);
        k++;
    }
    StrBuilder_Destroy(&sb);
    fclose(fp);
}

void SyntaxTree_PrintCodeToString(struct SyntaxTree* pProgram,
                                  struct Options* options0,
                                  struct StrBuilder* output)
{
    struct PrintCodeOptions options = CODE_PRINT_OPTIONS_INIT;
    options.Options = *options0;
    global_lambda_counter = 0;
    int k = 0;


    struct StrBuilder sb = STRBUILDER_INIT;
    StrBuilder_Reserve(&sb, 80 * 5000);

    for (int i = 0; i < pProgram->Declarations.Size; i++)
    {
        struct TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];

        StrBuilder_Clear(&options.sbPreDeclaration);

        struct StrBuilder sbDeclaration = STRBUILDER_INIT;
        TAnyDeclaration_CodePrint(pProgram, &options, pItem, &sbDeclaration);

        StrBuilder_Append(&sb, options.sbPreDeclaration.c_str);
        StrBuilder_Append(&sb, sbDeclaration.c_str);

        StrBuilder_Destroy(&sbDeclaration);

        StrBuilder_Append(output, sb.c_str);


        StrBuilder_Clear(&sb);
        k++;
    }
    StrBuilder_Destroy(&sb);

}


static const char* GetFreeStr(struct SyntaxTree* program)
{
    bool bCustomFree =
        SymbolMap_FindFunction(&program->GlobalScope, "Free") != NULL ||
        MacroMap_Find(&program->Defines, "Free") != NULL;

    return bCustomFree ? "Free" : "free";
}

static const char* GetMallocStr(struct SyntaxTree* program)
{
    bool bCustomMalloc =
        SymbolMap_FindFunction(&program->GlobalScope, "Malloc") != NULL ||
        MacroMap_Find(&program->Defines, "Malloc") != NULL;

    return bCustomMalloc ? "Malloc" : "malloc";
}

static const char* GetReallocStr(struct SyntaxTree* program)
{
    bool bCustomMalloc =
        SymbolMap_FindFunction(&program->GlobalScope, "Realloc") != NULL ||
        MacroMap_Find(&program->Defines, "Realloc") != NULL;

    return bCustomMalloc ? "Realloc" : "realloc";
}


static const char* GetFalseStr(struct SyntaxTree* program)
{
    bool bHasFalse =
        MacroMap_Find(&program->Defines, "false") != NULL;

    return bHasFalse ? "false" : "0";
}

static const char* GetNullStr(struct SyntaxTree* program)
{
    bool bHasFalse =
        MacroMap_Find(&program->Defines, "NULL") != NULL;

    return bHasFalse ? "NULL" : "0";
}



static void PrintIfNotNullLn(struct SyntaxTree* program,
                             struct PrintCodeOptions* options,
                             const char* pInitExpressionText, //(x->p->i = 0)    
                             struct StrBuilder* fp)
{
    bool bHasNULL =
        MacroMap_Find(&program->Defines, "NULL") != NULL;

    if (bHasNULL)
    {
        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                               "if (%s != NULL)",
                               pInitExpressionText);
    }
    else
    {
        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                               "if (%s)",
                               pInitExpressionText);
    }
}

static struct TDeclaration* FindHighLevelFunctionCore(struct SymbolMap* pMap,
                                                      struct TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
                                                      struct TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
                                                      const char* functionTagName)
{
    struct TDeclaration* pResult = NULL;

    if (functionTagName == NULL)
    {
        return NULL;
    }

    if (pMap->pHashTable != NULL)
    {
        unsigned int nHashBucket, HashValue;
        struct SymbolMapItem* pKeyValue =
            SymbolMap_GetAssocAt(pMap,
                                 functionTagName,
                                 &nHashBucket,
                                 &HashValue);

        while (pKeyValue != NULL)
        {
            //Obs enum struct e union compartilham um mapa unico
            if (pKeyValue->pValue->Type == TDeclaration_ID)
            {
                if (strcmp(pKeyValue->Key, functionTagName) == 0)
                {
                    //agora tem que verificar o tipo.
                    struct TDeclaration* pDeclaration =
                        (struct TDeclaration*)pKeyValue->pValue;

                    if (pDeclaration->FunctionTag &&
                        strcmp(pDeclaration->FunctionTag, functionTagName) == 0)
                    {
                        struct TDeclarationSpecifiers* pDeclarationSpecifiersOfArg1 =
                            TDeclaration_GetArgTypeSpecifier(pDeclaration, 0);

                        if (pDeclarationSpecifiersOfArg1)
                        {
                            if (TSpecifierQualifierList_Compare(pDeclarationSpecifiersOfArg1, pSpecifierQualifierList))
                            {
                                pResult = pDeclaration;
                                break;
                            }
                            else
                            {
                                //pode ser que pDeclarationSpecifiersOfArg1 seja typedef para pSpecifierQualifierList
                                //ou vice versa
                                const char* typedefName = TDeclarationSpecifiers_GetTypedefName(pDeclarationSpecifiersOfArg1);
                                if (typedefName)
                                {
                                    struct TTypeSpecifier* p = SymbolMap_FindTypedefSpecifierTarget(pMap, typedefName);
                                    if (TTypeSpecifier_Compare(p, pSpecifierQualifierList->pData[0]))
                                    {
                                        pResult = pDeclaration;
                                        break;
                                    }
                                }
                                else
                                {
                                    const char* typedefName = TDeclarationSpecifiers_GetTypedefName(pSpecifierQualifierList);
                                    if (typedefName)
                                    {
                                        struct TTypeSpecifier* p = SymbolMap_FindTypedefSpecifierTarget(pMap, typedefName);
                                        if (TTypeSpecifier_Compare(p, pDeclarationSpecifiersOfArg1->pData[0]))
                                        {
                                            pResult = pDeclaration;
                                            break;
                                        }
                                    }
                                }
                                //nao eh igual 
                                pResult = 0;
                            }
                        }
                    }
                }
            }
            pKeyValue = pKeyValue->pNext;
        }
    }



    return pResult;
}

static bool FindHighLevelFunction(struct SyntaxTree* program,
                                  struct PrintCodeOptions* options,
                                  struct TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
                                  struct TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
                                  struct TParameterTypeList* pArgsOpt, //parametros do create /init
                                  struct TInitializer* pInitializerOpt,
                                  const char* pInitExpressionText, //(x->p->i = 0)    
                                  const char* pszAutoPointerLenExpressionOpt,
                                  const enum Action action,
                                  enum Search search,
                                  const char* nameToFind,
                                  struct StrBuilder* fp)
{
    if (nameToFind == NULL)
    {
        //pode ser null struct sem nome
        return false;
    }




    bool bComplete = false;

    //TPointerList_Printf(&pDeclatator->PointerList);

    //TODO FAZER FLAGS e OLHAR P TIPO E DECLARATOR AMBOS
    bool bIsPointerToObject = TPointerList_IsPointerToObject(&pDeclatator->PointerList);
    bool bIsAutoPointerToObject = TPointerList_IsAutoPointerToObject(&pDeclatator->PointerList);
    bool bIsAutoPointerToAutoPointer = TPointerList_IsAutoPointerToAutoPointer(&pDeclatator->PointerList);
    bool bIsAutoPointerToPointer = TPointerList_IsAutoPointerToPointer(&pDeclatator->PointerList);
    bool bIsPointer = TPointerList_IsPointer(&pDeclatator->PointerList);
    bool bIsAutoPointerSizeToObject = TPointerList_IsAutoPointerSizeToObject(&pDeclatator->PointerList);

    if (action == ActionDestroy || action == ActionDestroyContent)
    {
        if (bIsPointer)
        {
            if (bIsAutoPointerSizeToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
            {
                //nao procurar delete bIsAutoPointerSizeToObject
                //nao eh ponteiro
                if (search == SearchAll ||
                    search == SearchDelete)
                {
                    //vamos procurar pela funcao conceito _Delete
                    struct TDeclaration* pDeclarationDestroy =
                        FindHighLevelFunctionCore(&program->GlobalScope,
                                                  pSpecifierQualifierList,
                                                  pDeclatator,
                                                  "delete");
                    if (pDeclarationDestroy)
                    {
                        const char* funcName = TDeclaration_GetFunctionName(pDeclarationDestroy);
                        if (bIsAutoPointerToObject)
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                   "%s(%s);",
                                                   funcName,
                                                   pInitExpressionText);
                            bComplete = true;
                        }
                        else if (bIsAutoPointerToAutoPointer)
                        {

                            if (pszAutoPointerLenExpressionOpt)
                            {
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

                                options->IdentationLevel++;

                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                       "%s(%s[i]);",
                                                       funcName,
                                                       pInitExpressionText);

                                options->IdentationLevel--;
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                       "%s((void*)%s);",
                                                       GetFreeStr(program),
                                                       pInitExpressionText);
                            }
                            else
                            {
                                //1 auto pointer para 1 autopointer
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                       "%s(%s[0]);",
                                                       funcName,
                                                       pInitExpressionText);

                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                       "%s((void*)%s);",
                                                       GetFreeStr(program),
                                                       pInitExpressionText);
                            }

                            bComplete = true;
                        }
                    }
                    else
                    {
                        if (search == SearchAll ||
                            search == SearchDestroy)
                        {
                            //se nao achou delete procura a destroy 
                            //e depois chama free
                            struct TDeclaration* pDeclarationDestroy2 =
                                FindHighLevelFunctionCore(&program->GlobalScope,
                                                          pSpecifierQualifierList,
                                                          pDeclatator,
                                                          "destroy");
                            if (pDeclarationDestroy2)
                            {
                                const char* funcName = TDeclaration_GetFunctionName(pDeclarationDestroy2);

                                if (bIsAutoPointerToObject)
                                {
                                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                           "%s(%s);",
                                                           funcName,
                                                           pInitExpressionText);

                                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                           "%s((void*)%s);",
                                                           GetFreeStr(program),
                                                           pInitExpressionText);
                                }
                                else if (bIsAutoPointerToAutoPointer)
                                {
                                    if (pszAutoPointerLenExpressionOpt)
                                    {
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

                                        options->IdentationLevel++;

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                               "%s(%s[i]);",
                                                               funcName,
                                                               pInitExpressionText);

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                               "%s((void*)%s[i]);",
                                                               GetFreeStr(program),
                                                               pInitExpressionText);

                                        options->IdentationLevel--;
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                               "%s((void*)%s);",
                                                               GetFreeStr(program),
                                                               pInitExpressionText);
                                    }
                                    else
                                    {
                                        //1 auto pointer para 1 auto pointer

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                               "%s(%s[0]);",
                                                               funcName,
                                                               pInitExpressionText);

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                               "%s((void*)%s[0]);",
                                                               GetFreeStr(program),
                                                               pInitExpressionText);

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                               "%s((void*)%s);",
                                                               GetFreeStr(program),
                                                               pInitExpressionText);
                                    }

                                }
                                else if (bIsAutoPointerSizeToObject)
                                {
                                    if (pszAutoPointerLenExpressionOpt)
                                    {
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

                                        options->IdentationLevel++;

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                               "%s(%s[i]);",
                                                               funcName,
                                                               pInitExpressionText);

                                        // StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                        //   "free((void*)%s[i]);",
                                        // pInitExpressionText);

                                        options->IdentationLevel--;
                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                               "%s((void*)%s);",
                                                               GetFreeStr(program),
                                                               pInitExpressionText);
                                    }
                                    else
                                    {
                                        //1 auto pointer para 1 auto pointer

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                               "%s(%s[0]);",
                                                               funcName,
                                                               pInitExpressionText);

                                        // StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                        //   "free((void*)%s[0]);",
                                        //   pInitExpressionText);

                                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                               "%s((void*)%s);",
                                                               GetFreeStr(program),
                                                               pInitExpressionText);
                                    }
                                }

                                bComplete = true;
                            }
                        }
                    }
                }
            }
            else if (bIsAutoPointerToPointer)
            {
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                       "%s((void*)%s);",
                                       GetFreeStr(program),
                                       pInitExpressionText);

                //nada
                bComplete = true;
            }
            else
            {
                if (action != ActionDestroyContent)
                {
                    //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "//%s = NULL;", pInitExpressionText);
                    bComplete = true;
                }
            }

        }
        else
        {
            //nao eh ponteiro
            if (!bIsAutoPointerToPointer)
            {
                if (search == SearchAll ||
                    search == SearchDestroy)
                {
                    struct TDeclaration* pDeclarationDestroy =
                        FindHighLevelFunctionCore(&program->GlobalScope,
                                                  pSpecifierQualifierList,
                                                  pDeclatator,
                                                  "destroy"
                        );

                    //vamos procurar pela funcao conceito _Destroy
                    //struct TDeclaration* pDeclarationDestroy =
                      //  SymbolMap_FindObjFunction(&program->GlobalScope,
                        //    nameToFind,
                          //  "Destroy");
                    if (pDeclarationDestroy)
                    {
                        const char* destroyFuncName =
                            TDeclaration_GetFunctionName(pDeclarationDestroy);
                        if (destroyFuncName)
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                                   "%s(&%s);",
                                                   destroyFuncName,
                                                   pInitExpressionText);
                        }
                        else
                        {
                            assert(false);
                        }

                        //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                          //  "%s_Destroy(&%s);",
                            //nameToFind,
                            //pInitExpressionText);
                        bComplete = true;
                    }
                }
            }

        }
    }
    else if (action == ActionDelete)
    {
        //nao eh ponteiro
        if (search == SearchAll ||
            search == SearchDelete)
        {
            //vamos procurar pela funcao conceito _Delete
            struct TDeclaration* pDeclarationDestroy =
                FindHighLevelFunctionCore(&program->GlobalScope,
                                          pSpecifierQualifierList,
                                          pDeclatator,
                                          "delete");
            if (pDeclarationDestroy)
            {
                const char* funcName = TDeclaration_GetFunctionName(pDeclarationDestroy);
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                       "%s(%s);",
                                       funcName,
                                       pInitExpressionText);
                bComplete = true;
            }
            else
            {
                if (search == SearchAll ||
                    search == SearchDestroy)
                {
                    //se nao achou delete procura a destroy 
                    //e depois chama free
                    struct TDeclaration* pDeclarationDestroy2 =
                        FindHighLevelFunctionCore(&program->GlobalScope,
                                                  pSpecifierQualifierList,
                                                  pDeclatator,
                                                  "destroy");
                    if (pDeclarationDestroy2)
                    {
                        const char* funcName = TDeclaration_GetFunctionName(pDeclarationDestroy2);
                        StrBuilder_AppendFmtLn(fp, 4 * 1,
                                               "%s(%s);",
                                               funcName,
                                               pInitExpressionText);

                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                               "%s((void*)%s);",
                                               GetFreeStr(program),
                                               pInitExpressionText);
                        bComplete = true;
                    }
                }

            }
        }
        else
        {
            //nao procurar pela delete mas procurar pela destroy
            //posso procurar pela destroy
            //se nao achou delete procura a destroy 
            //e depois chama free
            if (search == SearchAll ||
                search == SearchDestroy)
            {
                struct TDeclaration* pDeclarationDestroy =
                    FindHighLevelFunctionCore(&program->GlobalScope,
                                              pSpecifierQualifierList,
                                              pDeclatator,
                                              "destroy");
                if (pDeclarationDestroy)
                {
                    const char* funcName = TDeclaration_GetFunctionName(pDeclarationDestroy);

                    PrintIfNotNullLn(program, options, pInitExpressionText, fp);



                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "{");

                    options->IdentationLevel++;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "%s(%s);",
                                           funcName,
                                           pInitExpressionText);
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "%s((void*)%s);",
                                           GetFreeStr(program),
                                           pInitExpressionText);
                    options->IdentationLevel--;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "}",
                                           pInitExpressionText);

                    bComplete = true;
                }
            }

        }
    }
    else if (action == ActionInit)
    {
        if (bIsPointer)
        {
            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                   "%s = %s;",
                                   pInitExpressionText,
                                   GetNullStr(program));
            bComplete = true;
        }
        else
        {
            if (search == SearchAll ||
                search == SearchInit)
            {
                //pega o nome
                //const char * TStructUnionSpecifier_GetSpecialMemberName(struct TStructUnionSpecifier * p, enum DefaultFunctionTags type)


                struct TDeclaration* pDeclarationInit =
                    FindHighLevelFunctionCore(&program->GlobalScope,
                                              pSpecifierQualifierList,
                                              pDeclatator,
                                              "init");
                if (pDeclarationInit)
                {
                    const char* funcName = TDeclaration_GetFunctionName(pDeclarationInit);

                    StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
                                              "%s(&%s",
                                              funcName,
                                              pInitExpressionText);

                    TParameterTypeList_GetArgsString(pArgsOpt, fp);

                    StrBuilder_Append(fp, ");\n");

                    bComplete = true;
                }
            }

        }
    }
    else if (action == ActionInitContent)
    {
        if (search == SearchAll ||
            search == SearchInit)
        {
            struct TDeclaration* pDeclarationInit =
                FindHighLevelFunctionCore(&program->GlobalScope,
                                          pSpecifierQualifierList,
                                          pDeclatator,
                                          "init");
            if (pDeclarationInit)
            {
                const char* funcName = TDeclaration_GetFunctionName(pDeclarationInit);

                if (bIsPointer)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "%s(%s);",
                                           funcName,
                                           pInitExpressionText);
                }
                else
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "%s(&%s);",
                                           funcName,
                                           pInitExpressionText);
                }
                bComplete = true;
            }

        }
    }
    else if (action == ActionCreate)
    {
        if (search == SearchAll ||
            search == SearchInit)
        {
            struct TDeclaration* pDeclarationInit =
                FindHighLevelFunctionCore(&program->GlobalScope,
                                          pSpecifierQualifierList,
                                          pDeclatator,
                                          "init");
            if (pDeclarationInit)
            {
                const char* funcName = TDeclaration_GetFunctionName(pDeclarationInit);


                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                       "struct %s *p = (struct %s *) %s(sizeof * p);",
                                       nameToFind,
                                       nameToFind,
                                       GetMallocStr(program));


                PrintIfNotNullLn(program, options, "p", fp);


                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                       "{");
                options->IdentationLevel++;

                StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
                                          "%s(p",
                                          funcName);

                if (TParameterTypeList_HasNamedArgs(pArgsOpt))
                {
                    StrBuilder_Append(fp, ", ");
                    TParameterTypeList_GetArgsString(pArgsOpt, fp);
                }

                StrBuilder_Append(fp, ");\n");


                options->IdentationLevel--;

                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                       "}");

                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                       "return p;");

                bComplete = true;
            }

        }
    }
    else if (action == ActionStaticInit)
    {
        if (pInitializerOpt)
        {
            StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "/*%s=*/", pInitExpressionText);
            struct PrintCodeOptions options2 = *options;
            TInitializer_CodePrint(program, &options2, pDeclatator, (struct TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
            bComplete = true;
        }
        else if (bIsPointer)
        {
            StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, GetNullStr(program));
            bComplete = true;
        }


    }
    return bComplete;
}


//Verifica se tem "cara" de ser o vector
static bool IsVector(struct TStructUnionSpecifier* pStructUnionSpecifier)
{
    bool bHasVector = false;
    bool bHasSize = false;
    bool bHasCapacity = false;

    if (pStructUnionSpecifier)
    {
        //Vou analisar a "digital" da struct
        //ok tem a definicao completa da struct
        for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
        {
            struct TAnyStructDeclaration* pAnyStructDeclaration =
                pStructUnionSpecifier->StructDeclarationList.pItems[i];

            struct TStructDeclaration* pStructDeclaration =
                TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);
            if (pStructDeclaration)
            {
                TStructDeclarator* pStructDeclarator =
                    pStructDeclaration->DeclaratorList.pHead;

                while (pStructDeclarator)
                {
                    const char* structDeclaratorName =
                        TDeclarator_GetName(pStructDeclarator->pDeclarator);

                    bool bIsPointer1 =
                        TPointerList_IsPointerN(&pStructDeclarator->pDeclarator->PointerList, 1);

                    if (bIsPointer1)
                    {
                        bHasVector = true;
                    }
                    else  if (TSpecifierQualifierList_IsAnyInteger(&pStructDeclaration->SpecifierQualifierList))
                    {
                        if (strcmp(structDeclaratorName, "Size") == 0)
                        {
                            bHasSize = true;
                        }
                        else if (strcmp(structDeclaratorName, "Capacity") == 0)
                        {
                            bHasCapacity = true;
                        }
                    }

                    pStructDeclarator = (pStructDeclarator)->pNext;
                }
            }
        }
    }

    return bHasSize && bHasCapacity&& bHasVector;
}

void UnionTypeDefault(struct SyntaxTree* program,
                      struct PrintCodeOptions* options,
                      const char* structName,
                      struct TParameterTypeList* pArgsOpt, //parametros
                      const char* parameterName0,
                      const char* functionSuffix,
                      struct StrBuilder* fp)
{
    struct Map2 map = MAPSTRINGTOPTR_INIT;
    FindUnionSetOf(program, structName, &map);

    struct StrBuilder strid = STRBUILDER_INIT;
    FindRuntimeID(program, structName, &strid);

    struct StrBuilder args = STRBUILDER_INIT;

    if (pArgsOpt != NULL)
    {
        //lista argumentos separados por virgula
        TParameterTypeList_GetArgsString(pArgsOpt, &args);
    }
    else
    {
        StrBuilder_Append(&args, parameterName0);
    }

    struct TemplateVar vars0[] = {
        {"p", parameterName0},
    {"id", strid.c_str}
    };

    StrBuilder_Template(fp,
                        "switch ($p->$id)\n"
                        "{\n",
                        vars0,
                        sizeof(vars0) / sizeof(vars0[0]),
                        options->IdentationLevel);

    StrBuilder_Destroy(&strid);

    for (int i = 0; i < (int)map.nHashTableSize; i++)
    {
        if (map.pHashTable[i])
        {
            struct StrBuilder idvalue = STRBUILDER_INIT;

            FindIDValue(program,
                (const char*)map.pHashTable[i]->Key,
                        &idvalue);

            struct TemplateVar vars[] = {
                {"type", (const char*)map.pHashTable[i]->Key},
            {"suffix", functionSuffix},
            {"value", idvalue.c_str},
            {"args", args.c_str}
            };
            if ((int)map.pHashTable[i]->pValue == 2)
            {
                //2 is struct
                StrBuilder_Template(fp,
                                    " case $value:\n"
                                    "  $type\b_$suffix((struct $type*)$args);\n"
                                    " break;\n",
                                    vars,
                                    sizeof(vars) / sizeof(vars[0]),
                                    options->IdentationLevel);
            }
            else
            {
                //1 is typedef
                StrBuilder_Template(fp,
                                    " case $value:\n"
                                    "  $type\b_$suffix(($type*)$args);\n"
                                    " break;\n",
                                    vars,
                                    sizeof(vars) / sizeof(vars[0]),
                                    options->IdentationLevel);
            }
            StrBuilder_Destroy(&idvalue);
        }
    }

    StrBuilder_Template(fp,
                        " default:\n"
                        " break;\n"
                        "}\n",
                        NULL,
                        0,
                        options->IdentationLevel);

    StrBuilder_Destroy(&args);

#pragma message ( "leak?" )
    Map2_Destroy(&map, NULL); //LEAK?
}

void InstanciateDestroy2(struct SyntaxTree* program,
                         struct PrintCodeOptions* options,
                         struct TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
                         struct TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
                         struct TInitializer* pInitializerOpt, //usado para inicializacao estatica
                         struct TParameterTypeList* pArgsOpt, //parametros do create /init
                         const char* pInitExpressionText, //(x->p->i = 0)    
                         const char* pszAutoPointerLenExpressionOpt, //expressao usada para definir o tamanho de um spaw de auto pointers
                                     //se passar null eh pq nao interessa
                         const enum Action action,
                         enum Search search,
                         bool* pbHasInitializers,
                         struct StrBuilder* fp)
{
    if (pInitializerOpt && pbHasInitializers)
    {
        *pbHasInitializers = true;
    }


    bool bIsPointerToObject = TPointerList_IsPointerToObject(&pDeclatator->PointerList);
    bool bIsAutoPointerToObject = TPointerList_IsAutoPointerToObject(&pDeclatator->PointerList);
    bool bIsAutoPointerToAutoPointer = TPointerList_IsAutoPointerToAutoPointer(&pDeclatator->PointerList);
    bool bIsAutoPointerToPointer = TPointerList_IsAutoPointerToPointer(&pDeclatator->PointerList);
    bool bIsPointer = TPointerList_IsPointer(&pDeclatator->PointerList);

    struct TDeclarationSpecifier* pMainSpecifier =
        TSpecifierQualifierList_GetMainSpecifier(pSpecifierQualifierList);

    if (pMainSpecifier == NULL)
    {
        //error
        return;
    }

    if (pMainSpecifier->Type == TSingleTypeSpecifier_ID)
    {
        struct TSingleTypeSpecifier* pSingleTypeSpecifier =
            (struct TSingleTypeSpecifier*)pMainSpecifier;

        if (pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
        {
            bool bComplete = false;
            struct TDeclarator declarator;
            TDeclarator_Init(&declarator);
            //Pode ter uma cadeia de typdefs
            //ele vai entrandando em cada uma ...
            //ate que chega no fim recursivamente
            //enquanto ele vai andando ele vai tentando
            //algo com o nome do typedef
            struct TDeclarationSpecifiers* pDeclarationSpecifiers =
                SymbolMap_FindTypedefFirstTarget(&program->GlobalScope,
                                                 pSingleTypeSpecifier->TypedefName,
                                                 &declarator);
            if (pDeclarationSpecifiers)
            {
                ForEachListItem(struct TPointer, pItem, &pDeclatator->PointerList)
                {
                    struct TPointer* pNew = TPointer_Create();
                    TPointer_Copy(pNew, pItem);
                    TPointerList_PushBack(&declarator.PointerList, pNew);
                }

                //TPointerList_Printf(&declarator.PointerList);

                if (action == ActionCreate)
                {
                    //create do typedef eh um pouco difernet
                    //das outras

                    //vou deixar o malloc aqui fora
                    //existe typedef p struct sem nome
                    //entao queremos usar o nome do typedef
                    //typedef struct { int i; } X; X* X_Create();
                    //para poder fazer 
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "%s *p = (%s*) %s(sizeof * p);",
                                           pSingleTypeSpecifier->TypedefName,
                                           pSingleTypeSpecifier->TypedefName,
                                           GetMallocStr(program));

                    PrintIfNotNullLn(program, options, "p", fp);

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "{");

                    options->IdentationLevel++;

                    /////////////////
                    //vou ver se tem init para typedef

                    struct TDeclaration* pDeclarationInit =
                        FindHighLevelFunctionCore(&program->GlobalScope,
                                                  pSpecifierQualifierList,
                                                  pDeclatator,
                                                  "init");

                    //struct TDeclaration * pDeclarationInit =
                      //  SymbolMap_FindObjFunctionByType(&program->GlobalScope,
                        //    pSingleTypeSpecifier->TypedefName,
                          //  "init");

                    if (pDeclarationInit)
                    {
                        const char* funcName = TDeclaration_GetFunctionName(pDeclarationInit);


                        StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
                                                  "%s(p",
                                                  funcName);

                        //StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel,
                            //"%s_Init(p",
                            //pSingleTypeSpecifier->TypedefName);

                        if (TParameterTypeList_HasNamedArgs(pArgsOpt))
                        {
                            StrBuilder_Append(fp, ", ");
                            TParameterTypeList_GetArgsString(pArgsOpt, fp);
                        }

                        StrBuilder_Append(fp, ");\n");

                        bComplete = true;
                    }
                    ////////////////


                    if (!bComplete)
                    {

                        //passa a informacao do tipo correto agora
                        InstanciateDestroy2(program,
                                            options,
                                            (struct TSpecifierQualifierList*)pDeclarationSpecifiers,
                                            &declarator,
                                            NULL,
                                            pArgsOpt,
                                            "p",
                                            NULL /*not used*/,
                                            ActionInitContent,
                                            SearchNone, //se tivesse init ja tinha achado
                                            pbHasInitializers,
                                            fp);
                    }

                    options->IdentationLevel--;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "}");

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "return p;");

                }
                else
                {
                    bComplete = FindHighLevelFunction(program,
                                                      options,
                                                      pSpecifierQualifierList,//<-dupla para entender o tipo
                                                      pDeclatator,                        //<-dupla para entender o tipo
                                                      pArgsOpt, //parametros do create /init
                                                      pInitializerOpt,
                                                      pInitExpressionText, //(x->p->i = 0)    
                                                      pszAutoPointerLenExpressionOpt,
                                                      action,
                                                      search,
                                                      pSingleTypeSpecifier->TypedefName,
                                                      fp);


                    if (!bComplete)
                    {
                        enum Action action2 = action;

                        //passa a informacao do tipo correto agora
                        InstanciateDestroy2(program,
                                            options,
                                            (struct TSpecifierQualifierList*)pDeclarationSpecifiers,
                                            &declarator,
                                            pInitializerOpt,
                                            pArgsOpt,
                                            pInitExpressionText,
                                            pszAutoPointerLenExpressionOpt,
                                            action2,
                                            search,
                                            pbHasInitializers,
                                            fp);
                    }
                }

                TDeclarator_Destroy(&declarator);
            }
            else
            {
                //nao achou a declaracao
                //assert(false);
            }

        }
        else if (pSingleTypeSpecifier->Token2 == TK_STRUCT ||
                 pSingleTypeSpecifier->Token2 == TK_UNION)
        {
            struct TStructUnionSpecifier* pStructUnionSpecifier = NULL;

            //Indica se consegui fazer sem entrar na struct
            bool bComplete = false;

            bComplete = FindHighLevelFunction(program,
                                              options,
                                              pSpecifierQualifierList,//<-dupla para entender o tipo
                                              pDeclatator,                        //<-dupla para entender o tipo
                                              pArgsOpt,
                                              pInitializerOpt,
                                              pInitExpressionText, //(x->p->i = 0)    
                                              pszAutoPointerLenExpressionOpt,
                                              action,
                                              search,
                                              pSingleTypeSpecifier->TypedefName,
                                              fp);

            //Exemplos
            //struct Y *pY e é para destruir o conteudo
            //struct Y *pY e NAO é para destruir o conteudo
            //struct Y * auto pY; e é para destruir o conteudo ou nao
            //struct Y y; //eh para destruir o conteudo
            if (!bComplete) //se for para entrar na struct
            {
                if (pSingleTypeSpecifier &&
                    pSingleTypeSpecifier->TypedefName != NULL)
                {
                    //se nao eh completa tenta achar
                    //vou procurar a definicao completa da struct
                    pStructUnionSpecifier =
                        SymbolMap_FindCompleteStructUnionSpecifier(&program->GlobalScope, pSingleTypeSpecifier->TypedefName);
                }

                /////////////////////////////////////////////////////////////////////////////////////////////
                //DAQUI para baixo o codigo eh todo igual ao da struct
                //COMPARTILHAR        
                bool bIsUnionTypes = pStructUnionSpecifier &&
                    pStructUnionSpecifier->UnionSet.pHead != NULL;

                if (pStructUnionSpecifier &&
                    pStructUnionSpecifier->StructDeclarationList.Size > 0)
                {
                    if (action == ActionDelete)
                    {
                        PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{", pInitExpressionText);
                        options->IdentationLevel++;
                    }
                    else if (action == ActionDestroy)
                    {
                        if (bIsAutoPointerToObject)
                        {
                            PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                            options->IdentationLevel++;
                        }
                        else if (bIsAutoPointerToAutoPointer)
                        {

                            PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                            options->IdentationLevel++;

                            if (pszAutoPointerLenExpressionOpt)
                            {
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                                options->IdentationLevel++;
                            }
                            else
                            {
                                ////assert(false);
                            }

                        }

                    }
                    else if (action == ActionCreate)
                    {
                        //struct sem nome tem que ser criada
                        //com typedef que chama outro codigo
                        //assert(pStructUnionSpecifier->Name != NULL);

                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                               "struct %s* p = (struct %s*) %s(sizeof * p);",
                                               pStructUnionSpecifier->Tag,
                                               pStructUnionSpecifier->Tag,
                                               GetMallocStr(program));

                        PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                               "{");
                        options->IdentationLevel++;
                    }
                    else if (action == ActionStaticInit)
                    {
                        StrBuilder_AppendIdent(fp, 4 * options->IdentationLevel, "{");
                    }

                    if (bIsUnionTypes)
                    {
                        if (action == ActionDelete)
                        {
                            options->IdentationLevel++;
                            UnionTypeDefault(program,
                                             options,
                                             pStructUnionSpecifier->Tag,
                                             NULL, /*args*/
                                             pInitExpressionText,
                                             "Delete",
                                             fp);
                            options->IdentationLevel--;
                        }
                        else if (action == ActionDestroyContent ||
                                 action == ActionDestroy)
                        {
                            options->IdentationLevel++;
                            UnionTypeDefault(program,
                                             options,
                                             pStructUnionSpecifier->Tag,
                                             NULL, /*args*/
                                             pInitExpressionText,
                                             "Destroy",
                                             fp);
                            options->IdentationLevel--;
                        }
                        else
                        {

                        }
                    }
                    else
                    {
                        int variableCount = 0;
                        //ok tem a definicao completa da struct
                        for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
                        {




                            struct TAnyStructDeclaration* pAnyStructDeclaration =
                                pStructUnionSpecifier->StructDeclarationList.pItems[i];

                            struct TStructDeclaration* pStructDeclaration =
                                TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);

                            if (pStructDeclaration != NULL)
                            {
                                TStructDeclarator* pStructDeclarator =
                                    pStructDeclaration->DeclaratorList.pHead;

                                struct StrBuilder strVariableName = STRBUILDER_INIT;
                                struct StrBuilder strPonterSizeExpr = STRBUILDER_INIT;


                                while (pStructDeclarator)
                                {

                                    if (action == ActionStaticInit && variableCount > 0)
                                    {
                                        StrBuilder_Append(fp, ", ");
                                    }

                                    variableCount++;
                                    //O padrao eh ser o inicializador do tipo
                                    struct TInitializer* pStructMemberInitializer =
                                        pStructDeclarator->pInitializer;

                                    struct TPrimaryExpressionValue initializerExpression;
                                    TPrimaryExpressionValue_Init(&initializerExpression);


                                    StrBuilder_Clear(&strVariableName);
                                    StrBuilder_Clear(&strPonterSizeExpr);

                                    const char* structDeclaratorName =
                                        TDeclarator_GetName(pStructDeclarator->pDeclarator);
                                    if (action != ActionStaticInit)
                                    {
                                        if (pInitExpressionText)
                                            StrBuilder_Set(&strVariableName, pInitExpressionText);


                                        if (bIsAutoPointerToAutoPointer)
                                        {
                                            if (pszAutoPointerLenExpressionOpt)
                                            {
                                                StrBuilder_Append(&strVariableName, "[i]");
                                            }
                                            else
                                            {
                                                StrBuilder_Append(&strVariableName, "[0]");
                                            }
                                        }

                                        if (bIsPointer)
                                        {
                                            StrBuilder_Append(&strVariableName, "->");
                                        }
                                        else
                                        {
                                            StrBuilder_Append(&strVariableName, ".");
                                        }
                                    }
                                    else
                                    {
                                        StrBuilder_Append(&strVariableName, ".");
                                    }

                                    StrBuilder_Append(&strVariableName, structDeclaratorName);


                                    enum Action action2 = action;
                                    if (action == ActionDestroyContent ||
                                        action == ActionDelete)
                                    {
                                        //destroy normal
                                        action2 = ActionDestroy;
                                    }
                                    else if (action == ActionInitContent)
                                    {

                                        struct TParameter* pParameter = NULL;
                                        if (pArgsOpt)
                                        {
                                            pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
                                            if (pParameter != NULL)
                                            {
                                                pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
                                                initializerExpression.token = TK_IDENTIFIER;
                                                PTR_STRING_REPLACE(initializerExpression.lexeme, structDeclaratorName);
                                            }
                                        }

                                        action2 = ActionInit;
                                    }
                                    else if (action == ActionCreate)
                                    {
                                        struct TParameter* pParameter = NULL;
                                        if (pArgsOpt)
                                        {
                                            pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
                                            if (pParameter != NULL)
                                            {
                                                pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
                                                initializerExpression.token = TK_IDENTIFIER;
                                                PTR_STRING_REPLACE(initializerExpression.lexeme, structDeclaratorName);
                                            }
                                        }

                                        action2 = ActionInit;
                                    }

                                    if (action2 == ActionDestroy)
                                    {

                                        //Tem que detectar isso aqui!
                                        // char * /*@auto*/ pItems;
                                        // X * /*@auto*/ * /*@auto*/ pItems;
                                        //sef or ele vai precisar da informacao do _size
                                        // X * /*@auto*/ * /*@auto*/ _size(Size) pItems;
                                        //e dai ele passa a char para  funcao gerar


                                        const char* pszSize =
                                            TPointerList_GetSize(&pStructDeclarator->pDeclarator->PointerList);
                                        if (pszSize)
                                        {
                                            if (pInitExpressionText)
                                                StrBuilder_Set(&strPonterSizeExpr, pInitExpressionText);

                                            if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                                            {
                                                StrBuilder_Append(&strPonterSizeExpr, "->");
                                            }
                                            else
                                            {
                                                StrBuilder_Append(&strPonterSizeExpr, ".");
                                            }
                                            StrBuilder_Append(&strPonterSizeExpr, pszSize);
                                        }
                                        else
                                        {
                                            //nao tem size
                                        }
                                    }

                                    //Se for destroy e sor 
                                    InstanciateDestroy2(program,
                                                        options,
                                                        &pStructDeclaration->SpecifierQualifierList,
                                                        pStructDeclarator->pDeclarator,
                                                        pStructMemberInitializer,
                                                        NULL, //nao passa os args
                                                        strVariableName.c_str,
                                                        strPonterSizeExpr.c_str,
                                                        action2,
                                                        SearchAll,
                                                        pbHasInitializers,
                                                        fp);



                                    //Variavel local
                                    TPrimaryExpressionValue_Destroy(&initializerExpression);

                                    pStructDeclarator = (pStructDeclarator)->pNext;
                                }

                                StrBuilder_Destroy(&strVariableName);
                                StrBuilder_Destroy(&strPonterSizeExpr);

                            }
                        }
                    }

                    if (action == ActionDestroy)
                    {
                        if (bIsAutoPointerToObject)
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                            options->IdentationLevel--;
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                        }
                        else if (bIsAutoPointerToAutoPointer)
                        {
                            if (pszAutoPointerLenExpressionOpt)
                            {
                                options->IdentationLevel--;
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}"); //fecha  for
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                                options->IdentationLevel--;
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");//fecha or for
                            }
                            else
                            {
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                                options->IdentationLevel--;
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");//fecha or for
                            }


                            //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
                        }
                    }
                    else if (action == ActionDestroyContent)
                    {
                        if (bIsAutoPointerToAutoPointer)
                        {
                            //    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
                            //  options->IdentationLevel--;
                            //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                            //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
                        }
                    }
                    else if (action == ActionDelete)
                    {
                        if (bIsUnionTypes)
                        {

                        }
                        else
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                        }
                        options->IdentationLevel--;
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                    }
                    else if (action == ActionCreate)
                    {
                        options->IdentationLevel--;
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                               "}");

                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                               "return p;");
                    }
                    else if (action == ActionStaticInit)
                    {

                        StrBuilder_AppendIdent(fp, 4 * options->IdentationLevel, "}");


                    }
                }
                else
                {
                    //error nao tem a definicao completa da struct
                    StrBuilder_AppendFmt(fp, "/*incomplete type %s*/\n", pInitExpressionText);
                }
                ////////////////////////////////////////////////////////////////////////////////////////////////
            }//complete


        }
        else if (pSingleTypeSpecifier->Token2 == TK_ENUM)
        {
            //sample
            //enum E {A}; E* E_Create();
        }
        else
        {
            //nao eh typedef, deve ser int, double etc..
            if (action == ActionDestroy)
            {
                if (bIsAutoPointerToObject)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                }
                else if (bIsAutoPointerToAutoPointer)
                {
                    if (pszAutoPointerLenExpressionOpt)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");

                        options->IdentationLevel++;
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s[i]);", GetFreeStr(program), pInitExpressionText);
                        options->IdentationLevel--;
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                    }
                    else
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s[0]);", GetFreeStr(program), pInitExpressionText);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                    }

                    //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                }
                else
                {
                    //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "//%s = 0;", pInitExpressionText);
                }
            }
            else if (action == ActionInit)
            {
                if (pInitializerOpt)
                {
                    StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
                    struct PrintCodeOptions options2 = *options;
                    TInitializer_CodePrint(program, &options2, pDeclatator, (struct TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
                    StrBuilder_Append(fp, ";\n");
                }
                else
                {


                    if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, GetNullStr(program));
                    }
                    else
                    {
                        if (TSpecifierQualifierList_IsBool(pSpecifierQualifierList))
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, GetFalseStr(program));
                        }
                        else
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = 0;", pInitExpressionText);
                        }

                    }
                }
            }
            else if (action == ActionStaticInit)
            {
                if (pInitializerOpt)
                {
                    StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "/*%s=*/", pInitExpressionText);
                    struct PrintCodeOptions options2 = *options;
                    TInitializer_CodePrint(program, &options2, pDeclatator, (struct TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
                }
                else
                {
                    if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                    {
                        StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, GetNullStr(program));
                    }
                    else
                    {
                        StrBuilder_AppendFmt(fp, "/*%s=*/0", pInitExpressionText);
                    }
                }
            }
        }
    }
    else if (pMainSpecifier->Type == TStructUnionSpecifier_ID)
    {
        struct TStructUnionSpecifier* pStructUnionSpecifier =
            (struct TStructUnionSpecifier*)pMainSpecifier;

        //Indica se consegui fazer sem entrar na struct
        bool bComplete = false;


        bComplete = FindHighLevelFunction(program,
                                          options,
                                          pSpecifierQualifierList,//<-dupla para entender o tipo
                                          pDeclatator,                        //<-dupla para entender o tipo
                                          pArgsOpt,
                                          pInitializerOpt,
                                          pInitExpressionText, //(x->p->i = 0)    
                                          pszAutoPointerLenExpressionOpt,
                                          action,
                                          search,
                                          pStructUnionSpecifier->Tag,
                                          fp);

        //Exemplos
        //struct Y *pY e é para destruir o conteudo
        //struct Y *pY e NAO é para destruir o conteudo
        //struct Y * auto pY; e é para destruir o conteudo ou nao
        //struct Y y; //eh para destruir o conteudo
        if (!bComplete) //se for para entrar na struct
        {
            if (pStructUnionSpecifier &&
                pStructUnionSpecifier->Tag != NULL)
            {
                //se nao eh completa tenta achar
                //vou procurar a definicao completa da struct
                pStructUnionSpecifier =
                    SymbolMap_FindCompleteStructUnionSpecifier(&program->GlobalScope, pStructUnionSpecifier->Tag);
            }

            bool bIsUnionTypes = pStructUnionSpecifier &&
                pStructUnionSpecifier->UnionSet.pHead != NULL;


            if (pStructUnionSpecifier &&
                pStructUnionSpecifier->StructDeclarationList.Size > 0)
            {
                if (action == ActionDelete)
                {
                    PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{", pInitExpressionText);
                    options->IdentationLevel++;
                }
                else if (action == ActionDestroy)
                {
                    if (bIsAutoPointerToObject)
                    {
                        PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                        options->IdentationLevel++;
                    }
                    else if (bIsAutoPointerToAutoPointer)
                    {

                        PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                        options->IdentationLevel++;

                        if (pszAutoPointerLenExpressionOpt)
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "for (int i = 0; i < %s; i++)", pszAutoPointerLenExpressionOpt);
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                            options->IdentationLevel++;
                        }
                        else
                        {
                            ////assert(false);
                        }

                    }

                }
                else if (action == ActionCreate)
                {
                    //struct sem nome tem que ser criada
                    //com typedef que chama outro codigo
                    //assert(pStructUnionSpecifier->Name != NULL);

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "struct %s* p = (struct %s*) %s(sizeof * p);",
                                           pStructUnionSpecifier->Tag,
                                           pStructUnionSpecifier->Tag,
                                           GetMallocStr(program));

                    PrintIfNotNullLn(program, options, pInitExpressionText, fp);
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "{");
                    options->IdentationLevel++;
                }
                else if (action == ActionStaticInit)
                {
                    StrBuilder_AppendIdent(fp, 4 * options->IdentationLevel, "{");

                    //if (bCanApplyFunction)
                    //{
                    //o primeiro nao precisa do {

                    //  StrBuilder_AppendFmt(fp, "/*%s=*/{", pInitExpressionText);
                    //}
                }

                if (bIsUnionTypes)
                {
                    if (action == ActionDelete)
                    {
                        options->IdentationLevel++;
                        UnionTypeDefault(program,
                                         options,
                                         pStructUnionSpecifier->Tag,
                                         NULL, /*args*/
                                         pInitExpressionText,
                                         "Delete",
                                         fp);
                        options->IdentationLevel--;
                    }
                    else if (action == ActionDestroyContent ||
                             action == ActionDestroy)
                    {
                        options->IdentationLevel++;
                        UnionTypeDefault(program,
                                         options,
                                         pStructUnionSpecifier->Tag,
                                         NULL, /*args*/
                                         pInitExpressionText,
                                         "Destroy",
                                         fp);
                        options->IdentationLevel--;
                    }
                    else
                    {

                    }
                }
                else
                {
                    int variableCount = 0;
                    //ok tem a definicao completa da struct
                    for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.Size; i++)
                    {




                        struct TAnyStructDeclaration* pAnyStructDeclaration =
                            pStructUnionSpecifier->StructDeclarationList.pItems[i];

                        struct TStructDeclaration* pStructDeclaration =
                            TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);

                        if (pStructDeclaration != NULL)
                        {
                            TStructDeclarator* pStructDeclarator =
                                pStructDeclaration->DeclaratorList.pHead;

                            struct StrBuilder strVariableName = STRBUILDER_INIT;
                            struct StrBuilder strPonterSizeExpr = STRBUILDER_INIT;


                            while (pStructDeclarator)
                            {

                                if (action == ActionStaticInit && variableCount > 0)
                                {
                                    StrBuilder_Append(fp, ", ");
                                }
                                variableCount++;

                                //O padrao eh ser o inicializador do tipo
                                struct TInitializer* pStructMemberInitializer =
                                    pStructDeclarator->pInitializer;

                                struct TPrimaryExpressionValue initializerExpression;
                                TPrimaryExpressionValue_Init(&initializerExpression);


                                StrBuilder_Clear(&strVariableName);
                                StrBuilder_Clear(&strPonterSizeExpr);

                                const char* structDeclaratorName =
                                    TDeclarator_GetName(pStructDeclarator->pDeclarator);
                                if (action != ActionStaticInit)
                                {
                                    if (pInitExpressionText)
                                        StrBuilder_Set(&strVariableName, pInitExpressionText);


                                    if (bIsAutoPointerToAutoPointer)
                                    {
                                        if (pszAutoPointerLenExpressionOpt)
                                        {
                                            StrBuilder_Append(&strVariableName, "[i]");
                                        }
                                        else
                                        {
                                            StrBuilder_Append(&strVariableName, "[0]");
                                        }
                                    }

                                    if (bIsPointer)
                                    {
                                        StrBuilder_Append(&strVariableName, "->");
                                    }
                                    else
                                    {
                                        StrBuilder_Append(&strVariableName, ".");
                                    }
                                }
                                else
                                {
                                    StrBuilder_Append(&strVariableName, ".");
                                }

                                StrBuilder_Append(&strVariableName, structDeclaratorName);


                                enum Action action2 = action;
                                if (action == ActionDestroyContent ||
                                    action == ActionDelete)
                                {
                                    //destroy normal
                                    action2 = ActionDestroy;
                                }
                                else if (action == ActionInitContent)
                                {

                                    struct TParameter* pParameter = NULL;
                                    if (pArgsOpt)
                                    {
                                        pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
                                        if (pParameter != NULL)
                                        {
                                            pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
                                            initializerExpression.token = TK_IDENTIFIER;
                                            PTR_STRING_REPLACE(initializerExpression.lexeme, structDeclaratorName);
                                        }
                                    }

                                    action2 = ActionInit;
                                }
                                else if (action == ActionCreate)
                                {
                                    struct TParameter* pParameter = NULL;
                                    if (pArgsOpt)
                                    {
                                        pParameter = TParameterTypeList_FindParameterByName(pArgsOpt, structDeclaratorName);
                                        if (pParameter != NULL)
                                        {
                                            pStructMemberInitializer = TExpression_As_TInitializer(TPrimaryExpressionValue_As_TExpression(&initializerExpression));
                                            initializerExpression.token = TK_IDENTIFIER;
                                            PTR_STRING_REPLACE(initializerExpression.lexeme, structDeclaratorName);
                                        }
                                    }

                                    action2 = ActionInit;
                                }

                                if (action2 == ActionDestroy)
                                {

                                    //Tem que detectar isso aqui!
                                    // char * /*@auto*/ pItems;
                                    // X * /*@auto*/ * /*@auto*/ pItems;
                                    //sef or ele vai precisar da informacao do _size
                                    // X * /*@auto*/ * /*@auto*/ _size(Size) pItems;
                                    //e dai ele passa a char para  funcao gerar


                                    const char* pszSize =
                                        TPointerList_GetSize(&pStructDeclarator->pDeclarator->PointerList);
                                    if (pszSize)
                                    {
                                        if (pInitExpressionText)
                                            StrBuilder_Set(&strPonterSizeExpr, pInitExpressionText);

                                        if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                                        {
                                            StrBuilder_Append(&strPonterSizeExpr, "->");
                                        }
                                        else
                                        {
                                            StrBuilder_Append(&strPonterSizeExpr, ".");
                                        }
                                        StrBuilder_Append(&strPonterSizeExpr, pszSize);
                                    }
                                    else
                                    {
                                        //nao tem size
                                    }
                                }

                                //Se for destroy e sor 
                                InstanciateDestroy2(program,
                                                    options,
                                                    &pStructDeclaration->SpecifierQualifierList,
                                                    pStructDeclarator->pDeclarator,
                                                    pStructMemberInitializer,
                                                    NULL, //nao passa os args
                                                    strVariableName.c_str,
                                                    strPonterSizeExpr.c_str,
                                                    action2,
                                                    SearchAll,
                                                    pbHasInitializers,
                                                    fp);



                                //Variavel local
                                TPrimaryExpressionValue_Destroy(&initializerExpression);

                                pStructDeclarator = (pStructDeclarator)->pNext;
                            }

                            StrBuilder_Destroy(&strVariableName);
                            StrBuilder_Destroy(&strPonterSizeExpr);

                        }
                    }
                }

                if (action == ActionDestroy)
                {
                    if (bIsAutoPointerToObject)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                        options->IdentationLevel--;
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                    }
                    else if (bIsAutoPointerToAutoPointer)
                    {
                        if (pszAutoPointerLenExpressionOpt)
                        {
                            options->IdentationLevel--;
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}"); //fecha  for
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                            options->IdentationLevel--;
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");//fecha or for
                        }
                        else
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                            options->IdentationLevel--;
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");//fecha or for
                        }


                        //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
                    }
                }
                else if (action == ActionDestroyContent)
                {
                    if (bIsAutoPointerToAutoPointer)
                    {
                        //    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
                        //  options->IdentationLevel--;
                        //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");
                        //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free((void*)%s);", pInitExpressionText);
                    }
                }
                else if (action == ActionDelete)
                {
                    if (bIsUnionTypes)
                    {

                    }
                    else
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
                    }
                    options->IdentationLevel--;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                }
                else if (action == ActionCreate)
                {
                    options->IdentationLevel--;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "}");

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                           "return p;");
                }
                else if (action == ActionStaticInit)
                {
                    StrBuilder_AppendIdent(fp, 4 * options->IdentationLevel, "}");

                    //if (bCanApplyFunction)
                    //{
                    //  //o primeiro nao tem 
                    //StrBuilder_Append(fp, "}");
                    //}
                }
            }
            else
            {
                //error nao tem a definicao completa da struct
                StrBuilder_AppendFmt(fp, "/*incomplete type %s*/\n", pInitExpressionText);
            }
        }//complete

    }
    else if (pMainSpecifier->Type == TEnumSpecifier_ID)
    {
        struct TEnumSpecifier* pEnumSpecifier =
            TDeclarationSpecifier_As_TEnumSpecifier(pMainSpecifier);

        pEnumSpecifier =
            SymbolMap_FindCompleteEnumSpecifier(&program->GlobalScope, pEnumSpecifier->Tag);

        if (pEnumSpecifier == NULL)
        {

            assert(false);
            //erro nao achou definicao comlpeta.
        }

        //nao eh typedef, deve ser int, double etc..
        if (action == ActionDestroy)
        {
            if (bIsAutoPointerToObject)
            {
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
            }
            else if (bIsAutoPointerToAutoPointer)
            {
                //assert(false);
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s((void*)%s);", GetFreeStr(program), pInitExpressionText);
            }
            else
            {
                //StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "//%s = 0;", pInitExpressionText);
            }
        }
        else if (action == ActionInit)
        {
            if (pInitializerOpt)
            {
                StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
                struct PrintCodeOptions options2 = *options;
                TInitializer_CodePrint(program, &options2, pDeclatator, (struct TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
                StrBuilder_Append(fp, ";\n");
            }
            else
            {
                

                //TODO achar a definicao completa do enum
                const char* firstValue =
                    pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
                    "0";

                if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, GetNullStr(program));
                }
                else
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, firstValue);
                }
            }

        }
        else if (action == ActionInitContent)
        {
            if (pInitializerOpt)
            {
                StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
                struct PrintCodeOptions options2 = *options;
                TInitializer_CodePrint(program, &options2, pDeclatator, (struct TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
                StrBuilder_Append(fp, ";");
            }
            else
            {
                //TODO achar a definicao completa do enum
                const char* firstValue =
                    pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
                    "0";

                if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "*%s = %s;", pInitExpressionText, GetNullStr(program));
                }
                else
                {

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = %s;", pInitExpressionText, firstValue);
                }
            }
        }
        else if (action == ActionStaticInit)
        {
            if (pInitializerOpt)
            {
                StrBuilder_AppendFmtIdent(fp, 4 * options->IdentationLevel, "%s = ", pInitExpressionText);
                struct PrintCodeOptions options2 = *options;
                TInitializer_CodePrint(program, &options2, pDeclatator, (struct TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
            }
            else
            {
                //TODO achar a definicao completa do enum
                const char* firstValue =
                    pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
                    "0";

                if (bIsPointerToObject || bIsAutoPointerToObject || bIsAutoPointerToAutoPointer)
                {
                    StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, GetNullStr(program));
                }
                else
                {
                    StrBuilder_AppendFmt(fp, "/*%s=*/%s", pInitExpressionText, firstValue);
                }
            }
        }
    }
    else
    {
        //assert(false);
    }

}


struct TStructUnionSpecifier* GetStructSpecifier(struct SyntaxTree* program, struct TDeclarationSpecifiers* specifiers)
{
    if (specifiers == NULL)
        return NULL;

    struct TStructUnionSpecifier* pTStructUnionSpecifier =
        TDeclarationSpecifier_As_TStructUnionSpecifier(specifiers->pData[0]);

    struct TSingleTypeSpecifier* pSingleTypeSpecifier =
        TDeclarationSpecifier_As_TSingleTypeSpecifier(specifiers->pData[0]);

    if (pTStructUnionSpecifier == NULL)
    {
        if (pSingleTypeSpecifier != NULL &&
            pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
        {
            const char* typedefName = pSingleTypeSpecifier->TypedefName;

            struct TDeclaration* pDeclaration = SyntaxTree_GetFinalTypeDeclaration(program, typedefName);
            if (pDeclaration)
            {
                if (pDeclaration->Specifiers.Size > 1)
                {
                    pTStructUnionSpecifier =
                        TDeclarationSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pData[1]);
                }
            }
        }
    }

    //Procura pela definicao completa da struct
    if (pTStructUnionSpecifier &&
        pTStructUnionSpecifier->Tag != NULL)
    {
        pTStructUnionSpecifier =
            SymbolMap_FindCompleteStructUnionSpecifier(&program->GlobalScope, pTStructUnionSpecifier->Tag);
    }
    else  if (pSingleTypeSpecifier != NULL &&
              pSingleTypeSpecifier->Token2 == TK_STRUCT)
    {
        //Modelo C++ que o nome da struct ja eh suficiente
        pTStructUnionSpecifier =
            SymbolMap_FindCompleteStructUnionSpecifier(&program->GlobalScope, pSingleTypeSpecifier->TypedefName);
    }

    return pTStructUnionSpecifier;
}

