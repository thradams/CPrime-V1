
#include "CodePrint.h"
#include "..\Base\Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\Base\Path.h"



#include "Templates\AllTemplates.h"


//bool bExpandMacros;

void Options_Destroy(Options* options) _default
{
}

static void TInitializerListItem_CodePrint2(TProgram* program,
    Options * options,
    TDeclarator* pDeclarator,
    TSpecifierQualifierList* pSpecifierQualifierList,
    TInitializerListItem* p,

    StrBuilder* fp);



void TSpecifierQualifierList_CodePrint(TProgram* program, Options * options, TSpecifierQualifierList* pDeclarationSpecifiers, StrBuilder* fp);

void TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p, StrBuilder* fp);

static void TInitializer_CodePrint(TProgram* program,
    Options * options,
    TDeclarator* pDeclarator,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    TInitializer* pTInitializer,

    StrBuilder* fp);

static void TInitializerList_CodePrint(TProgram* program,
    Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    TDeclarator* pDeclarator,
    TInitializerList*p,

    StrBuilder* fp);


static void TInitializerListItem_CodePrint(TProgram* program,
    Options * options,
    TDeclarator* pDeclarator,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    TInitializerListItem* p,

    StrBuilder* fp);


static void TTypeQualifierList_CodePrint(TProgram* program, Options * options, TTypeQualifierList* p, StrBuilder* fp);

static void TAnyDeclaration_CodePrint(TProgram* program, Options * options, TAnyDeclaration *pDeclaration, StrBuilder* fp);
static void TTypeSpecifier_CodePrint(TProgram* program, Options * options, TTypeSpecifier* p, StrBuilder* fp);
static void TAnyStructDeclaration_CodePrint(TProgram* program, Options * options, TAnyStructDeclaration* p, StrBuilder* fp);
static void TTypeQualifier_CodePrint(TProgram* program, Options * options, TTypeQualifier* p, StrBuilder* fp);
static void TDeclaration_CodePrint(TProgram* program, Options * options, TDeclaration* p, StrBuilder* fp);
static void TExpression_CodePrint(TProgram* program, Options * options, TExpression * p, const char* name, StrBuilder* fp);
static void TStatement_CodePrint(TProgram* program, Options * options, TStatement * p, StrBuilder* fp);
static void TBlockItem_CodePrint(TProgram* program, Options * options, TBlockItem * p, StrBuilder* fp);

static void TPointer_CodePrint(TProgram* program, Options * options, TPointer* pPointer, StrBuilder* fp);
static void TParameter_CodePrint(TProgram* program, Options * options, TParameter* p, StrBuilder* fp);
//static void TInitializerListItem_CodePrint(TProgram* program, Options * options, TTypeSpecifier* pTypeSpecifier, bool bIsPointer, TInitializerListItem* p,  StrBuilder* fp);



void Output_Append(StrBuilder* p,
    Options* options,
    const char* source)
{
    if (options->bInclude  && options->IncludeLevel == 0)
        StrBuilder_Append(p, source);
}

static void TNodeClueList_CodePrint(Options* options, TScannerItemList* list,
    StrBuilder* fp)
{

    if (options->bDontPrintClueList)
    {
        if (list->pHead != NULL)
        {
            //Output_Append(fp, options,  " ");
        }
        return;
    }

    ForEachListItem(ScannerItem, pNodeClue, list)
    {
        switch (pNodeClue->token)
        {
        case TK_PRE_INCLUDE:

            Output_Append(fp, options, pNodeClue->lexeme.c_str);
            Output_Append(fp, options, "\n");
            //if (pNodeClue->bActive)

            options->IncludeLevel++;
            //}
            break;

        case TK_FILE_EOF:
            options->IncludeLevel--;
            //ASSERT(IncludeLevel > 0);
            //bInclude = true;
            break;
        case TK_PRE_DEFINE:
            //TODO gerar macros como init
            Output_Append(fp, options, pNodeClue->lexeme.c_str);
            Output_Append(fp, options, "\n");
            break;

        case TK_PRE_UNDEF:
        case TK_PRE_PRAGMA:
        case TK_PRE_IF:
        case TK_PRE_ENDIF:
        case TK_PRE_ELSE:
        case TK_PRE_IFDEF:
        case TK_PRE_IFNDEF:
        case TK_PRE_ELIF:
            Output_Append(fp, options, pNodeClue->lexeme.c_str);
            Output_Append(fp, options, "\n");
            break;

        case TK_COMMENT:
            if (options->bIncludeComments)
            {
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
            }
            else
            {
                Output_Append(fp, options, " ");
            }

            break;

        case TK_LINE_COMMENT:
            if (options->bIncludeComments)
            {
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
            }
            else
            {
                Output_Append(fp, options, "\n");
            }
            break;

        case TK_BREAKLINE:
            Output_Append(fp, options, "\n");

            break;

        case TK_MACRO_CALL:
            if (options->bExpandMacros)
            {

            }
            else
            {
                Output_Append(fp, options, pNodeClue->lexeme.c_str);
                options->bInclude = false;
            }
            break;


        case TK_MACRO_EOF:
            if (options->bExpandMacros)
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









static void TCompoundStatement_CodePrint(TProgram* program,
    Options * options,
    TCompoundStatement * p,

    StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "{");

    for (size_t j = 0; j < p->BlockItemList.size; j++)
    {
        TBlockItem *pBlockItem = p->BlockItemList.pItems[j];
        TBlockItem_CodePrint(program, options, pBlockItem, fp);
    }

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, "}");

}


static void TLabeledStatement_CodePrint(TProgram* program, Options * options, TLabeledStatement * p, StrBuilder* fp)
{


    if (p->token == TK_CASE)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "case");
        if (p->pStatementOpt)
        {
            TExpression_CodePrint(program, options, p->pExpression, "", fp);
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

static void TForStatement_CodePrint(TProgram* program, Options * options, TForStatement * p, StrBuilder* fp)
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


static void TWhileStatement_CodePrint(TProgram* program, Options * options, TWhileStatement * p, StrBuilder* fp)
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



static void TDoStatement_CodePrint(TProgram* program, Options * options, TDoStatement * p, StrBuilder* fp)
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


static void TExpressionStatement_CodePrint(TProgram* program, Options * options, TExpressionStatement * p, StrBuilder* fp)
{
    TExpression_CodePrint(program, options, p->pExpression, "", fp);

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, ";");


}


static void TJumpStatement_CodePrint(TProgram* program, Options * options, TJumpStatement * p, StrBuilder* fp)
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
        ASSERT(false);
    }


    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, options, ";");


}

static void TAsmStatement_CodePrint(TProgram* program, Options * options, TAsmStatement * p, StrBuilder* fp)
{
    Output_Append(fp, options, "\"type\":\"asm-statement\"");

}

static void TSwitchStatement_CodePrint(TProgram* program, Options * options, TSwitchStatement * p, StrBuilder* fp)
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


static void TIfStatement_CodePrint(TProgram* program, Options * options, TIfStatement * p, StrBuilder* fp)
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

static void TStatement_CodePrint(TProgram* program, Options * options, TStatement *  p, StrBuilder* fp)
{
    if (p == NULL)
    {
        return;
    }

    switch (p->Type)
    {
    case TExpressionStatement_ID:
        TExpressionStatement_CodePrint(program, options, (TExpressionStatement*)p, fp);
        break;

    case TSwitchStatement_ID:
        TSwitchStatement_CodePrint(program, options, (TSwitchStatement*)p, fp);
        break;

    case TLabeledStatement_ID:
        TLabeledStatement_CodePrint(program, options, (TLabeledStatement*)p, fp);
        break;

    case TForStatement_ID:
        TForStatement_CodePrint(program, options, (TForStatement*)p, fp);
        break;

    case TJumpStatement_ID:
        TJumpStatement_CodePrint(program, options, (TJumpStatement*)p, fp);
        break;

    case TAsmStatement_ID:
        TAsmStatement_CodePrint(program, options, (TAsmStatement*)p, fp);
        break;

    case TCompoundStatement_ID:
        TCompoundStatement_CodePrint(program, options, (TCompoundStatement*)p, fp);
        break;

    case TIfStatement_ID:
        TIfStatement_CodePrint(program, options, (TIfStatement*)p, fp);
        break;

    case TDoStatement_ID:
        TDoStatement_CodePrint(program, options, (TDoStatement*)p, fp);
        break;

    default:
        ASSERT(false);
        break;
    }


}

static void TBlockItem_CodePrint(TProgram* program, Options * options, TBlockItem *  p, StrBuilder* fp)
{
    if (p == NULL)
    {
        ASSERT(false);
        return;
    }


    switch (p->Type)
    {
    case TEofDeclaration_ID:
        break;

    case TStaticAssertDeclaration_ID:
        break;

    case TSwitchStatement_ID:

        TSwitchStatement_CodePrint(program, options, (TSwitchStatement*)p, fp);

        break;

    case TJumpStatement_ID:

        TJumpStatement_CodePrint(program, options, (TJumpStatement*)p, fp);

        break;

    case TForStatement_ID:

        TForStatement_CodePrint(program, options, (TForStatement*)p, fp);

        break;

    case TIfStatement_ID:

        TIfStatement_CodePrint(program, options, (TIfStatement*)p, fp);

        break;

    case TWhileStatement_ID:

        TWhileStatement_CodePrint(program, options, (TWhileStatement*)p, fp);

        break;

    case TDoStatement_ID:

        TDoStatement_CodePrint(program, options, (TDoStatement*)p, fp);

        break;

    case TDeclaration_ID:
        TDeclaration_CodePrint(program, options, (TDeclaration*)p, fp);
        //Output_Append(fp, options,  "\n");
        break;

    case TLabeledStatement_ID:

        TLabeledStatement_CodePrint(program, options, (TLabeledStatement*)p, fp);

        break;

    case TCompoundStatement_ID:
        TCompoundStatement_CodePrint(program, options, (TCompoundStatement*)p, fp);
        break;

    case TExpressionStatement_ID:

        TExpressionStatement_CodePrint(program, options, (TExpressionStatement*)p, fp);

        break;


    case TAsmStatement_ID:

        TAsmStatement_CodePrint(program, options, (TAsmStatement*)p, fp);

        break;

    default:
        ASSERT(false);
        break;
    }


}



bool GetType(const char* source,
    StrBuilder* strBuilderType)
{

    while (*source  &&
        *source != '_')
    {
        StrBuilder_AppendChar(strBuilderType, *source);
        source++;
    }


    return *source == '_';
}


bool GetTypeAndFunction(const char* source,
    StrBuilder* strBuilderType,
    StrBuilder* strBuilderFunc)
{

    while (*source  &&
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




static void TPostfixExpressionCore_CodePrint(TProgram* program,
    Options * options,
    TPostfixExpressionCore * p,

    StrBuilder* fp)
{




    if (p->pExpressionLeft)
    {
        TExpression_CodePrint(program, options, p->pExpressionLeft, "l", fp);
    }


    {
        bool bIsPointer = false;
        TTypeName *pTypeName = NULL;
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
                (TDeclarationSpecifiers*)&p->pTypeName->SpecifierQualifierList,
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
        break;
    }



    if (p->pNext)
    {
        TPostfixExpressionCore_CodePrint(program, options, p->pNext, fp);
    }



}

static void TExpression_CodePrint(TProgram* program, Options * options, TExpression *  p,
    const char* name,

    StrBuilder* fp)
{
    if (p == NULL)
    {
        //ASSERT(false);
        return;
    }



    switch (p->Type)
    {
        CASE(TBinaryExpression) :
        {
            TBinaryExpression* pBinaryExpression = (TBinaryExpression*)p;

            TExpression_CodePrint(program, options, pBinaryExpression->pExpressionLeft, "l-expr", fp);

            TNodeClueList_CodePrint(options, &pBinaryExpression->ClueList00, fp);
            Output_Append(fp, options, TokenToString(pBinaryExpression->token));

            TExpression_CodePrint(program, options, ((TBinaryExpression*)p)->pExpressionRight, "r-expr", fp);
        }
        break;

        CASE(TTernaryExpression) :
        {
            TTernaryExpression* pTernaryExpression =
                (TTernaryExpression*)p;


            TExpression_CodePrint(program, options, pTernaryExpression->pExpressionLeft, "l-expr", fp);

            TNodeClueList_CodePrint(options, &pTernaryExpression->ClueList0, fp);
            Output_Append(fp, options, "?");

            TExpression_CodePrint(program, options, pTernaryExpression->pExpressionMiddle, "m-expr", fp);

            TNodeClueList_CodePrint(options, &pTernaryExpression->ClueList1, fp);
            Output_Append(fp, options, ":");

            TExpression_CodePrint(program, options, pTernaryExpression->pExpressionRight, "r-expr", fp);
        }
        break;

        CASE(TPrimaryExpressionLiteral) :
        {
            TPrimaryExpressionLiteral* pPrimaryExpressionLiteral
                = (TPrimaryExpressionLiteral*)p;

            ForEachListItem(TPrimaryExpressionLiteralItem, pItem, &pPrimaryExpressionLiteral->List)
            {
                TNodeClueList_CodePrint(options, &pItem->ClueList0, fp);
                Output_Append(fp, options, pItem->lexeme);
            }
        }
        break;

        CASE(TPrimaryExpressionValue) :
        {
            TPrimaryExpressionValue* pPrimaryExpressionValue =
                (TPrimaryExpressionValue*)p;

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

        CASE(TPostfixExpressionCore) :
        {
            TPostfixExpressionCore* pPostfixExpressionCore =
                (TPostfixExpressionCore*)p;
            TPostfixExpressionCore_CodePrint(program, options, pPostfixExpressionCore, fp);
        }
        break;

        CASE(TUnaryExpressionOperator) :
        {
            TUnaryExpressionOperator* pTUnaryExpressionOperator =
                (TUnaryExpressionOperator*)p;

            TNodeClueList_CodePrint(options, &pTUnaryExpressionOperator->ClueList00, fp);

            if (pTUnaryExpressionOperator->token == TK_SIZEOF)
            {
                if (pTUnaryExpressionOperator->TypeName.SpecifierQualifierList.pHead != NULL)
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
                Output_Append(fp, options, TokenToString(((TBinaryExpression*)p)->token));
                TExpression_CodePrint(program, options, pTUnaryExpressionOperator->pExpressionRight, "expr", fp);
            }
        }
        break;

        CASE(TCastExpressionType) :
        {
            TCastExpressionType * pCastExpressionType =
                (TCastExpressionType*)p;
            TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList0, fp);
            Output_Append(fp, options, "(");

            TTypeName_CodePrint(program, options, &pCastExpressionType->TypeName, fp);


            TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList1, fp);
            Output_Append(fp, options, ")");

            TExpression_CodePrint(program, options, pCastExpressionType->pExpression, "expr", fp);
        }
        break;

    default:

        ASSERT(false);
    }



}



static   void TEnumerator_CodePrint(TProgram* program, Options * options, TEnumerator* pTEnumerator, StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &pTEnumerator->ClueList0, fp);
    Output_Append(fp, options, pTEnumerator->Name);

    if (pTEnumerator->pExpression)
    {
        TNodeClueList_CodePrint(options, &pTEnumerator->ClueList1, fp);
        Output_Append(fp, options, "=");

        TExpression_CodePrint(program, options, pTEnumerator->pExpression, "expr", fp);


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

static void TEnumSpecifier_CodePrint(TProgram* program, Options * options, TEnumSpecifier* p, StrBuilder* fp)
{
    //true;

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, options, "enum");

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, p->Name);

    TNodeClueList_CodePrint(options, &p->ClueList2, fp);

    if (p->EnumeratorList.pHead != NULL)
    {
        Output_Append(fp, options, "{");

        ForEachListItem(TEnumerator, pTEnumerator, &p->EnumeratorList)
        {
            TEnumerator_CodePrint(program, options, pTEnumerator, fp);
        }

        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, options, "}");
    }


}


static void TStructUnionSpecifier_CodePrint(TProgram* program, Options * options, TStructUnionSpecifier* p, StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    //true;

    if (p->bIsStruct)
        Output_Append(fp, options, "struct");

    else
        Output_Append(fp, options, "union");

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, p->Name);

    if (p->TemplateName != NULL)
    {

        //TNodeClueList_CodePrint(options, &p->ClueList2, fp);

        AllPlugin_InstanciateType(program,
            options,
            p,

            fp);

    }
    else
    {
        if (p->StructDeclarationList.size > 0)
        {
            TNodeClueList_CodePrint(options, &p->ClueList2, fp);

            Output_Append(fp, options, "{");

            for (size_t i = 0; i < p->StructDeclarationList.size; i++)
            {
                TAnyStructDeclaration * pStructDeclaration = p->StructDeclarationList.pItems[i];
                TAnyStructDeclaration_CodePrint(program, options, pStructDeclaration, fp);
            }

            TNodeClueList_CodePrint(options, &p->ClueList3, fp);
            Output_Append(fp, options, "}");
        }
    }


}

static void TSingleTypeSpecifier_CodePrint(TProgram* program, Options * options, TSingleTypeSpecifier* p, StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    //true;
    if (p->Token != TK_IDENTIFIER)
    {
        Output_Append(fp, options,
            TokenToString(p->Token));
    }
    else
    {
        Output_Append(fp, options, p->TypedefName);
    }


}

static void TTypeSpecifier_CodePrint(TProgram* program, Options * options, TTypeSpecifier*  p, StrBuilder* fp)
{
    if (p == NULL)
    {
        //declaracao vazia: ;
        return;
    }

    switch (p->Type)
    {
    case TStructUnionSpecifier_ID:
        //TAnyStructDeclaration_CodePrint();
        TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier*)p, fp);
        break;

    case TEnumSpecifier_ID:
        TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier*)p, fp);
        break;

    case TSingleTypeSpecifier_ID:
        TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier*)p, fp);
        break;

    default:
        break;
    }


}

static void TDesignator_CodePrint(TProgram* program, Options * options, TDesignator* p, StrBuilder* fp)
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


static void TInitializerList_CodePrint(TProgram* program,
    Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers, //<- usadao para construir {}
    TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
    TInitializerList*p,

    StrBuilder* fp)
{
    if (List_HasOneItem(p) &&
        List_Back(p)->pInitializer == NULL/* &&
                                          pSpecifierQualifierList != NULL*/)
    {
        if (!options->bHideDefaultImplementation)
        {
            Output_Append(fp, options, "_default ");
        }
        //a partir de {} e um tipo consegue gerar o final  
        StrBuilder sb = STRBUILDER_INIT;
        bool bHasInitializers = false;
        InstanciateDestroy2(program,
            options,
            (TSpecifierQualifierList*)(pDeclarationSpecifiers),
            pDeclatator,                        //<-dupla para entender o tipo
            NULL,
            "",
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

        ForEachListItem(TInitializerListItem, pItem, p)
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

static void TInitializerListType_CodePrint(TProgram* program,
    Options * options,
    TDeclarator* pDeclarator,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    TInitializerListType*p,

    StrBuilder* fp)
{

    if (p->bDefault)
    {
        TNodeClueList_CodePrint(options, &p->ClueList00, fp);
        TInitializer* pInitializer = NULL;
        //p->InitializerList.pHead ?
        //p->InitializerList.pHead->pInitializer : NULL;

        Output_Append(fp, options, "_default");
        Output_Append(fp, options, " {");
        if (options->bHideDefaultImplementation)
        {
        }
        else
        {
            StrBuilder sb = STRBUILDER_INIT;
            bool bHasInitializers = false;
            InstanciateDestroy2(program,
                options,
                (TSpecifierQualifierList*)(pDeclarationSpecifiers),
                pDeclarator,                        //<-dupla para entender o tipo
                pInitializer,
                "",
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
                Output_Append(fp, options, "0");
            }

            StrBuilder_Destroy(&sb);
        }
        Output_Append(fp, options, "}");
    }
    else
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "{");

        TInitializerList_CodePrint(program,
            options,
            pDeclarationSpecifiers,
            pDeclarator,
            &p->InitializerList,

            fp);

        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, "}");
    }


}


static void TInitializer_CodePrint(TProgram* program,
    Options * options,
    TDeclarator* pDeclarator,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    TInitializer* pTInitializer,

    StrBuilder* fp)
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
            (TInitializerListType*)pTInitializer, fp);
    }
    else
    {
        TExpression_CodePrint(program, options, (TExpression*)pTInitializer, "", fp);
    }


}



static void TPointerList_CodePrint(TProgram* program, Options * options, TPointerList *p, StrBuilder* fp)
{


    ForEachListItem(TPointer, pItem, p)
    {
        TPointer_CodePrint(program, options, pItem, fp);
    }


}



static void TParameterList_CodePrint(TProgram* program, Options * options, TParameterList *p, StrBuilder* fp)
{



    ForEachListItem(TParameter, pItem, p)
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

static void TParameterTypeList_CodePrint(TProgram* program, Options * options, TParameterTypeList *p, StrBuilder* fp)
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
static void TDeclarator_CodePrint(TProgram* program, Options * options, TDeclarator* p, bool bPrintName, StrBuilder* fp);

static void TDirectDeclarator_CodePrint(TProgram* program, Options * options, TDirectDeclarator* pDirectDeclarator,

    bool bPrintName,
    StrBuilder* fp)
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

    if (pDirectDeclarator->Type == TDirectDeclaratorTypeArray)
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


    if (pDirectDeclarator->Type == TDirectDeclaratorTypeFunction)
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

static void TDeclarator_CodePrint(TProgram* program, Options * options, TDeclarator* p, bool bPrintName, StrBuilder* fp)
{
    TPointerList_CodePrint(program, options, &p->PointerList, fp);
    TDirectDeclarator_CodePrint(program, options, p->pDirectDeclarator, bPrintName, fp);

}

//void TInitDeclarator_CodePrint(TProgram* program, 
    //Options * options, 
    //TI/nitDeclarator* p,    
    //StrBuilder* fp);



void TStructDeclarator_CodePrint(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    TStructDeclarator* p,
    StrBuilder* fp)
{

    TDeclarator_CodePrint(program, options, p->pDeclarator, true/*bPrintName*/, fp);
    if (p->pInitializer)
    {
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, options, "_defval");

        Output_Append(fp, options, "(");

        Options opt = *options;
        opt.bExpandMacros = true;
        opt.bIncludeComments = false;


        TInitializer_CodePrint(program,
            &opt,
            p->pDeclarator,
            (TDeclarationSpecifiers*)pSpecifierQualifierList,
            p->pInitializer,

            fp);
        Output_Append(fp, options, ")");
    }

}

static void TStructDeclaratorList_CodePrint(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    TStructDeclaratorList *p,
    StrBuilder* fp)
{




    ForEachListItem(TInitDeclarator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
        {
            TNodeClueList_CodePrint(options, &pItem->ClueList00, fp);
            Output_Append(fp, options, ",");
        }
        TStructDeclarator_CodePrint(program, options, pSpecifierQualifierList, pItem, fp);
    }



}

static void TStructDeclaration_CodePrint(TProgram* program,
    Options * options,
    TStructDeclaration* p,
    StrBuilder* fp)
{
    TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, fp);
    TStructDeclaratorList_CodePrint(program,
        options,
        &p->SpecifierQualifierList,
        &p->DeclaratorList, fp);


    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, options, ";");


}

static void TAnyStructDeclaration_CodePrint(TProgram* program, Options * options, TAnyStructDeclaration* p, StrBuilder* fp)
{
    switch (p->Type)
    {
    case TStructDeclaration_ID:
        TStructDeclaration_CodePrint(program, options, (TStructDeclaration*)p, fp);
        break;

    default:
        ASSERT(false);
        break;
    }


}

static void StorageSpecifier_CodePrint(TProgram* program, Options * options, TStorageSpecifier* p, StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    if (p->bIsAuto)
    {
        Output_Append(fp, options, "auto");

    }

    if (p->bIsExtern)
    {
        Output_Append(fp, options, "extern");

    }

    if (p->bIsRegister)
    {
        Output_Append(fp, options, "register");

    }

    if (p->bIsStatic)
    {
        Output_Append(fp, options, "static");

    }




    if (p->bIsThread_local)
    {
        Output_Append(fp, options, "[Thread_local]");

    }

    if (p->bIsTypedef)
    {
        Output_Append(fp, options, "typedef");

    }


}



static void TTemplateTypeSpecifier_CodePrint(TProgram* program, Options * options, TTemplateTypeSpecifier* p, StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    if (strcmp(p->Identifier, "List") == 0)
    {

        StrBuilder strBuilder = STRBUILDER_INIT;

        if (p->Args.pHead != NULL)
        {
            TTypeName_CodePrint(program, options, &p->Args.pHead->TypeName, &strBuilder);
        }
        else
        {
            //TODO
            //tem que ter 1 arg
        }


        Output_Append(fp, options, "struct {");
        Output_Append(fp, options, strBuilder.c_str);
        Output_Append(fp, options, "* pHead; ");
        Output_Append(fp, options, strBuilder.c_str);
        Output_Append(fp, options, "* pTail; }");

        StrBuilder_Destroy(&strBuilder);
    }
    else if (strcmp(p->Identifier, "Union") == 0)
    {
        Output_Append(fp, options, "struct { int type; }");
    }
    else
    {
        //ERROR
        printf("ERROR _Template\n");
        Output_Append(fp, options, "struct { /*error*/}");

        //TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        //Output_Append(fp, options,  "_Template");


        //Output_Append(fp, options,  "(");
        //Output_Append(fp, options,  p->Identifier);
        //Output_Append(fp, options,  ",");
        //TTypeName_CodePrint(program, options, &p->TypeName,  fp);

        //Output_Append(fp, options,  ")");
    }

}

static void TFunctionSpecifier_CodePrint(TProgram* program, Options * options, TFunctionSpecifier* p, StrBuilder* fp)
{
    if (p->bIsInline)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "inline");

    }
    if (p->bIsNoReturn)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, options, "[noreturn]");

    }

}


static void TTypeQualifier_CodePrint(TProgram* program, Options * options, TTypeQualifier* p, StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    Output_Append(fp, options, TokenToString(p->Token));


}

static void TTypeQualifierList_CodePrint(TProgram* program, Options * options, TTypeQualifierList* p, StrBuilder* fp)
{
    ForEachListItem(TTypeQualifier, pItem, p)
    {
        TTypeQualifier_CodePrint(program, options, pItem, fp);
    }

}
static void TPointer_CodePrint(TProgram* program, Options * options, TPointer* pPointer, StrBuilder* fp)
{
    if (pPointer->bPointer)
    {
        TNodeClueList_CodePrint(options, &pPointer->ClueList0, fp);
        Output_Append(fp, options, "*");
    }
    else
    {
        TTypeQualifierList_CodePrint(program, options, &pPointer->Qualifier, fp);
    }


}

void TSpecifierQualifierList_CodePrint(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pDeclarationSpecifiers,

    StrBuilder* fp)
{
    ForEachListItem(TSpecifierQualifier, pItem, pDeclarationSpecifiers)
    {
        switch (pItem->Type)
        {

            CASE(TSingleTypeSpecifier) :
                TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier*)pItem, fp);
            break;

            CASE(TStorageSpecifier) :
                StorageSpecifier_CodePrint(program, options, (TStorageSpecifier*)pItem, fp);
            break;
            CASE(TTypeQualifier) :
                TTypeQualifier_CodePrint(program, options, (TTypeQualifier*)pItem, fp);
            break;
            CASE(TFunctionSpecifier) :
                TFunctionSpecifier_CodePrint(program, options, (TFunctionSpecifier*)pItem, fp);
            break;
            //CASE(TAlignmentSpecifier) : 
            ///TAlignmentSpecifier_CodePrint(program, options, (TAlignmentSpecifier*)pItem,  fp);
            //break;

            CASE(TStructUnionSpecifier) :
                TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier*)pItem, fp);
            break;

            CASE(TEnumSpecifier) :
                TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier*)pItem, fp);
            break;

        default:
            ASSERT(false);
            break;
        }
    }


}

void TDeclarationSpecifiers_CodePrint(TProgram* program, Options * options, TDeclarationSpecifiers* pDeclarationSpecifiers, StrBuilder* fp)
{

    ForEachListItem(TSpecifier, pItem, pDeclarationSpecifiers)
    {
        switch (pItem->Type)
        {

            CASE(TSingleTypeSpecifier) :
                TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier*)pItem, fp);
            break;

            CASE(TStructUnionSpecifier) :
                TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier*)pItem, fp);
            break;

            CASE(TEnumSpecifier) :
                TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier*)pItem, fp);
            break;

            CASE(TStorageSpecifier) :
                StorageSpecifier_CodePrint(program, options, (TStorageSpecifier*)pItem, fp);
            break;
            CASE(TTypeQualifier) :
                TTypeQualifier_CodePrint(program, options, (TTypeQualifier*)pItem, fp);
            break;
            CASE(TFunctionSpecifier) :
                TFunctionSpecifier_CodePrint(program, options, (TFunctionSpecifier*)pItem, fp);
            break;

            CASE(TTemplateTypeSpecifier) :
                TTemplateTypeSpecifier_CodePrint(program, options, (TTemplateTypeSpecifier*)pItem, fp);
            break;
            //CASE(TAlignmentSpecifier) : 
            ///TAlignmentSpecifier_CodePrint(program, options, (TAlignmentSpecifier*)pItem,  fp);
            //break;

        default:
            ASSERT(false);
            break;
        }
    }





}

void TInitDeclarator_CodePrint(TProgram* program,
    Options * options,
    TDeclarator* pDeclarator,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    TInitDeclarator* p,
    StrBuilder* fp)
{
    TDeclarator_CodePrint(program, options, p->pDeclarator, true/*bPrintName*/, fp);

    if (p->pInitializer)
    {
        TNodeClueList_CodePrint(options, &p->ClueList00, fp);
        Output_Append(fp, options, "=");
        TInitializer_CodePrint(program,
            options,
            pDeclarator,
            pDeclarationSpecifiers,
            p->pInitializer,

            fp);
    }

}



void TInitDeclaratorList_CodePrint(TProgram* program,
    Options * options,

    TDeclarationSpecifiers *pDeclarationSpecifiers,
    TInitDeclaratorList *p,

    StrBuilder* fp)
{

    //fprintf(fp, "[");
    ForEachListItem(TInitDeclarator, pInitDeclarator, p)
    {
        if (!List_IsFirstItem(p, pInitDeclarator))
            Output_Append(fp, options, ",");

        bool bIsPointer =
            TPointerList_IsPointer(&pInitDeclarator->pDeclarator->PointerList);

        TInitDeclarator_CodePrint(program,
            options,
            pInitDeclarator->pDeclarator,
            pDeclarationSpecifiers,
            pInitDeclarator,
            fp);
    }

    //  fprintf(fp, "]");

}



void InstanciateDestroy2(TProgram* program,
    Options* options,
    TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
    TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
    TInitializer* pInitializerOpt,
    const char* pInitExpressionText, //(x->p->i = 0),
    const Action action,
    Search search,
    bool * pbHasInitializers,
    StrBuilder* fp);

static void DefaultFunctionDefinition_CodePrint(TProgram* program,
    Options * options,
    TDeclaration* p,

    StrBuilder* fp)
{

    //Retorno da funcao
    TDeclarationSpecifiers* pSpecifiers =
        &p->Specifiers;


    const char* funcName =
        TDeclarator_GetName(p->InitDeclaratorList.pHead->pDeclarator);

    //parametros
    TParameter* pFirstParameter = NULL;
    const char* firstParameterName = NULL;
    TParameterTypeList * pArgs =
        TDeclaration_GetFunctionArguments(p);
    if (pArgs)
    {
        int i = 0;
        ForEachListItem(TParameter, pParameter, &pArgs->ParameterList)
        {
            if (i == 0)
            {
                pFirstParameter = pParameter;
                firstParameterName = TParameter_GetName(pParameter);
            }
            i++;
        }
    }

    if (IsSuffix(funcName, "_Create"))
    {
        options->IdentationLevel++;

        InstanciateDestroy2(program,
            options,
            (TSpecifierQualifierList*)(&pSpecifiers),
            p->InitDeclaratorList.pHead->pDeclarator,
            NULL,
            "p",
            ActionCreate,
            SearchInit,
            NULL,
            fp);
        options->IdentationLevel--;
    }
    else if (IsSuffix(funcName, "_Init") && pFirstParameter)
    {
        options->IdentationLevel++;

        InstanciateDestroy2(program,
            options,
            (TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
            &pFirstParameter->Declarator,
            NULL,
            firstParameterName,
            ActionInitContent,
            SearchNone,
            NULL,
            fp);
        options->IdentationLevel--;
    }
    else if (IsSuffix(funcName, "_Destroy"))
    {

        options->IdentationLevel++;
        InstanciateDestroy2(program,
            options,
            (TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
            &pFirstParameter->Declarator,
            NULL,
            firstParameterName,
            ActionDestroyContent,
            SearchNone,
            NULL,
            fp);
        options->IdentationLevel--;
    }
    else if (IsSuffix(funcName, "_Delete"))
    {

        options->IdentationLevel++;
        InstanciateDestroy2(program,
            options,
            (TSpecifierQualifierList*)(&pFirstParameter->Specifiers),
            &pFirstParameter->Declarator,
            NULL,
            firstParameterName,
            ActionDelete,
            SearchDestroy,
            NULL,
            fp);
        options->IdentationLevel--;
    }
    else
    {

        AllPlugin_CodePrint(program,
            options,
            p,
            fp);

    }
    //////////////////////////


    /////////////////////////

    //TParameterTypeList * pArgs =
    //      TDeclaration_GetFunctionArguments(p);
    //  if (pArgs)
    //{
    //  ForEachListItem(TParameter, pParameter, &pArgs->ParameterList)
    //{
    //  printf("%s\n", TParameter_GetName(pParameter));
    //printf("%s\n", TParameter_GetTypedefName(pParameter));
    //printf(TParameter_IsDirectPointer(pParameter) ? "true" : "false");


    // Std_Template_CodePrint(program,
    //                   options,
    //                   p,
    //                      
    //                    fp);



}

static void TDeclaration_CodePrint(TProgram* program,
    Options * options,
    TDeclaration* p,

    StrBuilder* fp)
{
    TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, fp);

    TInitDeclaratorList_CodePrint(program,
        options,
        &p->Specifiers,
        &p->InitDeclaratorList, fp);

    if (p->pCompoundStatementOpt != NULL)
    {
        /*
        typedef struct Array { int data; ... } Items;
        void Items_Add(Items* p,int i) {...}
        void Items_Delete(Items* p,int i) {...}
        */

        if (p->bDefault)
        {
            TNodeClueList_CodePrint(options, &p->ClueList00, fp);
            StrBuilder_Append(fp, "_default");

            if (options->bHideDefaultImplementation)
            {
                Output_Append(fp, options, ";");
            }
            else
            {
                TNodeClueList_CodePrint(options, &p->pCompoundStatementOpt->ClueList0, fp);
                Output_Append(fp, options, "{\n");

                DefaultFunctionDefinition_CodePrint(program,
                    options,
                    p,

                    fp);

                Output_Append(fp, options, "}");

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

            if (!options->bHideDefaultImplementation)
            {
                TNodeClueList_CodePrint(options, &p->ClueList00, fp);
                StrBuilder_Append(fp, "_default");
                //Output_Append(fp, options,  " /*default*/\n");
                TNodeClueList_CodePrint(options, &p->ClueList1, fp);
                Output_Append(fp, options, "\n{\n");

                DefaultFunctionDefinition_CodePrint(program,
                    options,
                    p,

                    fp);

                Output_Append(fp, options, "\n");
                Output_Append(fp, options, "}");
            }
            else
            {
                TNodeClueList_CodePrint(options, &p->ClueList1, fp);
                StrBuilder_Append(fp, " _default");
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

void TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p, StrBuilder* fp)
{

    TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, fp);

    TDeclarator_CodePrint(program, options, &p->Declarator, true/*bPrintName*/, fp);


}

static void TParameter_CodePrint(TProgram* program,
    Options * options,
    TParameter* p,

    StrBuilder* fp)
{
    TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, fp);
    TDeclarator_CodePrint(program, options, &p->Declarator, true/*bPrintName*/, fp);

    if (p->bHasComma)
    {
        TNodeClueList_CodePrint(options, &p->ClueList00, fp);
        Output_Append(fp, options, ",");
    }


}

static void TEofDeclaration_CodePrint(TProgram* program,
    Options * options,
    TEofDeclaration *p,

    StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

}

static void TStaticAssertDeclaration_CodePrint(TProgram* program,
    Options * options,
    TStaticAssertDeclaration *p,

    StrBuilder* fp)
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

static void TAnyDeclaration_CodePrint(TProgram* program, Options * options, TAnyDeclaration *pDeclaration, StrBuilder* fp)
{
    switch (pDeclaration->Type)
    {
    case TEofDeclaration_ID:
        TEofDeclaration_CodePrint(program, options, (TEofDeclaration*)pDeclaration, fp);
        break;

    case TStaticAssertDeclaration_ID:
        TStaticAssertDeclaration_CodePrint(program, options, (TStaticAssertDeclaration*)pDeclaration, fp);
        break;

    case TDeclaration_ID:
        TDeclaration_CodePrint(program, options, (TDeclaration*)pDeclaration, fp);
        break;

    default:
        ASSERT(false);
        break;
    }


}

static void TDesignatorList_CodePrint(TProgram* program, Options * options, TDesignatorList *p, StrBuilder* fp)
{



    ForEachListItem(TDesignator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
        {
            Output_Append(fp, options, ",");
        }
        TDesignator_CodePrint(program, options, pItem, fp);
    }



}


static void TInitializerListItem_CodePrint(TProgram* program,
    Options * options,
    TDeclarator* pDeclarator,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    TInitializerListItem* p,

    StrBuilder* fp)
{
    if (!List_IsEmpty(&p->DesignatorList))
    {
        TDesignatorList_CodePrint(program, options, &p->DesignatorList, fp);
    }

    TInitializer_CodePrint(program,
        options,
        pDeclarator,
        pDeclarationSpecifiers,
        p->pInitializer,
        fp);
}


static void TDeclarations_CodePrint(TProgram* program, Options * options, TDeclarations *p, StrBuilder* fp)
{



    for (size_t i = 0; i < p->size; i++)
    {
        if (i > 0)
            Output_Append(fp, options, ",");

        TAnyDeclaration* pItem = p->pItems[i];
        TAnyDeclaration_CodePrint(program, options, pItem, fp);

    }


}

/*
static void TProgram_PrintToFile(TProgram* pProgram,
const char* fileName)
{
StrBuilder * fp = fopen(fileName, "w");
TDeclarations_CodePrint(&pProgram->Declarations, fp);
fclose(fp);
}*/




void TProgram_PrintCodeToFile(TProgram* pProgram,
    Options* options,
    const char* outFileName,
    const char* inputFileName)
{
    FILE * fp = fopen(outFileName, "w");

    if (fp == NULL)
    {
        printf("cannot open output file %s", outFileName);
        return;
    }



    int k = 0;

    //for (int i = 0; i < pProgram->Files2.size; i++)
    //{
    //  TFile *pFile = pProgram->Files2.pItems[i];
    //  printf("\"%s\"\n", pFile->FullPath);
    //}

    StrBuilder sb = STRBUILDER_INIT;

    for (size_t i = 0; i < pProgram->Declarations.size; i++)
    {
        TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];


        TAnyDeclaration_CodePrint(pProgram, options, pItem, &sb);


        fprintf(fp, "%s", sb.c_str);




        StrBuilder_Clear(&sb);
        k++;
    }
    StrBuilder_Destroy(&sb);
    fclose(fp);
}




static bool FindHighLevelFunction(TProgram* program,
    Options* options,
    TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
    TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
    TInitializer* pInitializerOpt,
    const char* pInitExpressionText, //(x->p->i = 0)    
    const Action action,
    Search search,
    const char* nameToFind,
    StrBuilder* fp)
{
    if (nameToFind == NULL)
    {
        //pode ser null struct sem nome
        return false;
    }

    bool bComplete = false;


    bool bDeclaratorIsPointer = pDeclatator ? TDeclarator_IsPointer(pDeclatator) : false;
    bool bDeclaratorIsAutoPointer = pDeclatator ? TDeclarator_IsAutoPointer(pDeclatator) : false;


    if (action == ActionDestroy || action == ActionDestroyContent)
    {
        if (bDeclaratorIsPointer)
        {
            if (bDeclaratorIsAutoPointer)
            {
                //nao eh ponteiro
                if (search == SearchAll ||
                    search == SearchDelete)
                {
                    //vamos procurar pela funcao conceito _Delete
                    TDeclaration* pDeclarationDestroy =
                        SymbolMap_FindObjFunction(&program->GlobalScope,
                            nameToFind,
                            "Delete");
                    if (pDeclarationDestroy)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                            "%s_Delete(%s);",
                            nameToFind,
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
                            TDeclaration* pDeclarationDestroy =
                                SymbolMap_FindObjFunction(&program->GlobalScope,
                                    nameToFind,
                                    "Destroy");
                            if (pDeclarationDestroy)
                            {
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                    "%s_Destroy(%s);",
                                    nameToFind,
                                    pInitExpressionText);
                                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                                    "free(%s);",
                                    pInitExpressionText);
                                bComplete = true;
                            }
                        }
                    }
                }
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
            if (search == SearchAll ||
                search == SearchDestroy)
            {
                //vamos procurar pela funcao conceito _Destroy
                TDeclaration* pDeclarationDestroy =
                    SymbolMap_FindObjFunction(&program->GlobalScope,
                        nameToFind,
                        "Destroy");
                if (pDeclarationDestroy)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "%s_Destroy(&%s);",
                        nameToFind,
                        pInitExpressionText);
                    bComplete = true;
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
            TDeclaration* pDeclarationDestroy =
                SymbolMap_FindObjFunction(&program->GlobalScope,
                    nameToFind,
                    "Delete");
            if (pDeclarationDestroy)
            {
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "%s_Delete(%s);",
                    nameToFind,
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
                    TDeclaration* pDeclarationDestroy =
                        SymbolMap_FindObjFunction(&program->GlobalScope,
                            nameToFind,
                            "Destroy");
                    if (pDeclarationDestroy)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * 1,
                            "%s_Destroy(%s);",
                            nameToFind,
                            pInitExpressionText);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                            "free(%s);",
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
                TDeclaration* pDeclarationDestroy =
                    SymbolMap_FindObjFunction(&program->GlobalScope,
                        nameToFind,
                        "Destroy");
                if (pDeclarationDestroy)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "if (%s){\n",
                        pInitExpressionText);
                    options->IdentationLevel++;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "%s_Destroy(%s);",
                        nameToFind,
                        pInitExpressionText);
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "free(%s);",
                        pInitExpressionText);
                    options->IdentationLevel--;
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "}\n",
                        pInitExpressionText);

                    bComplete = true;
                }
            }

        }
    }
    else if (action == ActionInit)
    {
        if (bDeclaratorIsPointer)
        {
            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                "%s = 0/*NULL*/;",
                pInitExpressionText);
            bComplete = true;
        }
        else
        {
            if (search == SearchAll ||
                search == SearchInit)
            {
                TDeclaration* pDeclarationInit =
                    SymbolMap_FindObjFunction(&program->GlobalScope,
                        nameToFind,
                        "Init");
                if (pDeclarationInit)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "%s_Init(&%s);",
                        nameToFind,
                        pInitExpressionText);
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
            TDeclaration* pDeclarationInit =
                SymbolMap_FindObjFunction(&program->GlobalScope,
                    nameToFind,
                    "Init");
            if (pDeclarationInit)
            {
                if (bDeclaratorIsPointer)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "%s_Init(%s);",
                        nameToFind,
                        pInitExpressionText);
                }
                else
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "%s_Init(&%s);",
                        nameToFind,
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
            TDeclaration* pDeclarationInit =
                SymbolMap_FindObjFunction(&program->GlobalScope,
                    nameToFind,
                    "Init");
            if (pDeclarationInit)
            {
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "struct %s *p = malloc(sizeof * p);",
                    nameToFind);


                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "if (p)");
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "{");
                options->IdentationLevel++;
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                    "%s_Init(p);",
                    nameToFind);

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
            Options options2 = *options;
            TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);

        }
        else if (bDeclaratorIsPointer)
        {
            StrBuilder_AppendFmt(fp, "/*%s=*/0/*NULL*/", pInitExpressionText);
            bComplete = true;
        }


    }
    return bComplete;
}

void InstanciateDestroy2(TProgram* program,
    Options* options,
    TSpecifierQualifierList* pSpecifierQualifierList,//<-dupla para entender o tipo
    TDeclarator* pDeclatator,                        //<-dupla para entender o tipo
    TInitializer* pInitializerOpt,
    const char* pInitExpressionText, //(x->p->i = 0)    
    const Action action,
    Search search,
    bool* pbHasInitializers,
    StrBuilder* fp)
{
    if (pInitializerOpt && pbHasInitializers)
    {
        *pbHasInitializers = true;
    }

    bool bDeclaratorIsPointer = pDeclatator ? TDeclarator_IsPointer(pDeclatator) : false;
    bool bDeclaratorIsAutoPointer = pDeclatator ? TDeclarator_IsAutoPointer(pDeclatator) : false;

    TSpecifier* pMainSpecifier =
        TSpecifierQualifierList_GetMainSpecifier(pSpecifierQualifierList);

    if (pMainSpecifier == NULL)
    {
        //error
        return;
    }

    if (pMainSpecifier->Type == TSingleTypeSpecifier_ID)
    {
        TSingleTypeSpecifier* pSingleTypeSpecifier =
            (TSingleTypeSpecifier*)pMainSpecifier;

        if (pSingleTypeSpecifier->Token == TK_IDENTIFIER)
        {
            bool bComplete = false;
            TDeclarator declarator = TDECLARATOR_INIT;
            //Pode ter uma cadeia de typdefs
            //ele vai entrandando em cada uma ...
            //ate que chega no fim recursivamente
            //enquanto ele vai andando ele vai tentando
            //algo com o nome do typedef
            TDeclarationSpecifiers* pDeclarationSpecifiers =
                SymbolMap_FindTypedefFirstTarget(&program->GlobalScope,
                    pSingleTypeSpecifier->TypedefName,
                    &declarator);
            if (pDeclarationSpecifiers)
            {
                //Copia as partes deste declarador já
                //(vai acumulando ponteiros) typedef para typedef para typedef...
                ForEachListItem(TPointer, pItem, &pDeclatator->PointerList)
                {
                    TPointer * pNew = TPointer_Create();
                    pNew->bPointer = pItem->bPointer;
                    pNew->Qualifier = pItem->Qualifier;
                    List_Add(&declarator.PointerList, pNew);
                }


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
                        "%s *p = (%s*) malloc(sizeof * p);",
                        pSingleTypeSpecifier->TypedefName,
                        pSingleTypeSpecifier->TypedefName);

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "if (p != NULL)");
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "{");

                    options->IdentationLevel++;

                    /////////////////
                    //vou ver se tem init para typedef

                    TDeclaration* pDeclarationInit =
                        SymbolMap_FindObjFunction(&program->GlobalScope,
                            pSingleTypeSpecifier->TypedefName,
                            "Init");

                    if (pDeclarationInit)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                            "%s_Init(p);",
                            pSingleTypeSpecifier->TypedefName);

                        bComplete = true;
                    }
                    ////////////////


                    if (!bComplete)
                    {
                        
                        //passa a informacao do tipo correto agora
                        InstanciateDestroy2(program,
                            options,
                            (TSpecifierQualifierList*)pDeclarationSpecifiers,
                            &declarator,
                            NULL,
                            "p",
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
                        pInitializerOpt,
                        pInitExpressionText, //(x->p->i = 0)    
                        action,
                        search,
                        pSingleTypeSpecifier->TypedefName,
                        fp);


                    if (!bComplete)
                    {
                        Action action2 = action;

                        //passa a informacao do tipo correto agora
                        InstanciateDestroy2(program,
                            options,
                            (TSpecifierQualifierList*)pDeclarationSpecifiers,
                            &declarator,
                            NULL,
                            pInitExpressionText,
                            action2,
                            SearchAll,
                            pbHasInitializers,
                            fp);
                    }
                }
                TDeclarator_Destroy(&declarator);
            }
            else
            {
                //nao achou a declaracao
                ASSERT(false);
            }

        }
        else
        {
            //nao eh typedef, deve ser int, double etc..
            if (action == ActionDestroy)
            {
                if (bDeclaratorIsAutoPointer)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free(%s);", pInitExpressionText);
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
                    Options options2 = *options;
                    TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
                    StrBuilder_Append(fp, ";\n");
                }
                else
                {
                    if (bDeclaratorIsPointer)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = 0/*NULL*/;", pInitExpressionText);
                    }
                    else
                    {
                        if (TSpecifierQualifierList_IsBool(pSpecifierQualifierList))
                        {
                            StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = 0;/*false*/", pInitExpressionText);
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
                    Options options2 = *options;
                    TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
                }
                else
                {
                    if (bDeclaratorIsPointer)
                    {
                        StrBuilder_AppendFmt(fp, "/*%s=*/0/*NULL*/", pInitExpressionText);

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
        TStructUnionSpecifier* pStructUnionSpecifier =
            (TStructUnionSpecifier*)pMainSpecifier;

        //Indica se consegui fazer sem entrar na struct
        bool bComplete = false;


        bComplete = FindHighLevelFunction(program,
            options,
            pSpecifierQualifierList,//<-dupla para entender o tipo
            pDeclatator,                        //<-dupla para entender o tipo
            pInitializerOpt,
            pInitExpressionText, //(x->p->i = 0)    
            action,
            search,
            pStructUnionSpecifier->Name,
            fp);

        //Exemplos
        //struct Y *pY e é para destruir o conteudo
        //struct Y *pY e NAO é para destruir o conteudo
        //struct Y * auto pY; e é para destruir o conteudo ou nao
        //struct Y y; //eh para destruir o conteudo
        if (!bComplete) //se for para entrar na struct
        {
            if (pStructUnionSpecifier &&
                pStructUnionSpecifier->Name != NULL)
            {
                //se nao eh completa tenta achar
                //vou procurar a definicao completa da struct
                pStructUnionSpecifier =
                    SymbolMap_FindStructUnion(&program->GlobalScope, pStructUnionSpecifier->Name);
            }

            if (pStructUnionSpecifier &&
                pStructUnionSpecifier->StructDeclarationList.size > 0)
            {
                if (action == ActionDelete)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "if (%s)", pInitExpressionText);
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{", pInitExpressionText);
                    options->IdentationLevel++;
                }
                else if (action == ActionDestroy)
                {
                    if (bDeclaratorIsAutoPointer)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "if (%s)", pInitExpressionText);
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "{");
                        options->IdentationLevel++;
                    }
                }
                else if (action == ActionCreate)
                {
                    Options op = OPTIONS_INIT;
                    op.IdentationLevel = options->IdentationLevel;
                    op.bDontPrintClueList = true;

                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "");

                    TSpecifierQualifierList_CodePrint(program,
                        &op,
                        pSpecifierQualifierList,
                        fp);

                    StrBuilder_Append(fp, "*p = (");

                    TSpecifierQualifierList_CodePrint(program,
                        &op,
                        pSpecifierQualifierList,
                        fp);
                    StrBuilder_Append(fp, ")");

                    StrBuilder_Append(fp, "malloc(sizeof * p);\n");


                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "if (p)");
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel,
                        "{");
                    options->IdentationLevel++;
                }
                else if (action == ActionStaticInit)
                {
                    //if (bCanApplyFunction)
                    //{
                        //o primeiro nao precisa do {

                      //  StrBuilder_AppendFmt(fp, "/*%s=*/{", pInitExpressionText);
                    //}
                }

                //ok tem a definicao completa da struct
                for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.size; i++)
                {
                    if (action == ActionStaticInit && i > 0)
                    {
                        StrBuilder_Append(fp, ", ");
                    }

                    TAnyStructDeclaration* pAnyStructDeclaration =
                        pStructUnionSpecifier->StructDeclarationList.pItems[i];

                    TStructDeclaration* pStructDeclaration =
                        TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);

                    if (pStructDeclaration != NULL)
                    {
                        TStructDeclarator* pStructDeclarator =
                            pStructDeclaration->DeclaratorList.pHead;

                        bool bStructDeclaratorIsPointer =
                            TPointerList_IsPointer(&pStructDeclarator->pDeclarator->PointerList);

                        bool bStructDeclaratorIsAutoPointer =
                            TPointerList_IsAutoPointer(&pStructDeclarator->pDeclarator->PointerList);

                        StrBuilder strVariableName = STRBUILDER_INIT;


                        while (pStructDeclarator)
                        {
                            StrBuilder_Clear(&strVariableName);

                            const char* structDeclaratorName =
                                TDeclarator_GetName(pStructDeclarator->pDeclarator);
                            if (action != ActionStaticInit)
                            {
                                if (pInitExpressionText)
                                    StrBuilder_Set(&strVariableName, pInitExpressionText);

                                if (bDeclaratorIsPointer)
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

                            Action action2 = action;
                            if (action == ActionDestroyContent ||
                                action == ActionDelete)
                            {
                                //destroy normal
                                action2 = ActionDestroy;
                            }
                            else if (action == ActionInitContent)
                            {
                                action2 = ActionInit;
                            }
                            else if (action == ActionCreate)
                            {
                                action2 = ActionInit;
                            }

                            InstanciateDestroy2(program,
                                options,
                                &pStructDeclaration->SpecifierQualifierList,
                                pStructDeclarator->pDeclarator,
                                pStructDeclarator->pInitializer,
                                strVariableName.c_str,
                                action2,
                                SearchAll,
                                pbHasInitializers,
                                fp);



                            pStructDeclarator = (pStructDeclarator)->pNext;
                        }

                        StrBuilder_Destroy(&strVariableName);
                    }
                }

                if (action == ActionDestroy)
                {
                    if (bDeclaratorIsAutoPointer)
                    {
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free(%s);", pInitExpressionText);
                        options->IdentationLevel--;
                        StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "}");

                    }
                }
                else if (action == ActionDelete)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free(%s);", pInitExpressionText);
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
                StrBuilder_AppendFmt(fp, "/*type not found %s*/", pInitExpressionText);
            }
        }//complete

    }
    else if (pMainSpecifier->Type == TEnumSpecifier_ID)
    {
        TEnumSpecifier *pEnumSpecifier =
            TSpecifier_As_TEnumSpecifier(pMainSpecifier);


        //nao eh typedef, deve ser int, double etc..
        if (action == ActionDestroy)
        {
            if (bDeclaratorIsAutoPointer)
            {
                StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "free(%s);", pInitExpressionText);
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
                Options options2 = *options;
                TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
                StrBuilder_Append(fp, ";");
            }
            else
            {
                //TODO achar a definicao completa do enum
                const char* firstValue =
                    pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
                    "0";

                if (bDeclaratorIsPointer)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "%s = 0/*NULL*/;", pInitExpressionText);
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
                Options options2 = *options;
                TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
                StrBuilder_Append(fp, ";");
            }
            else
            {
                //TODO achar a definicao completa do enum
                const char* firstValue =
                    pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
                    "0";

                if (bDeclaratorIsPointer)
                {
                    StrBuilder_AppendFmtLn(fp, 4 * options->IdentationLevel, "*%s = 0/*NULL*/;", pInitExpressionText);
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
                Options options2 = *options;
                TInitializer_CodePrint(program, &options2, pDeclatator, (TDeclarationSpecifiers*)pSpecifierQualifierList, pInitializerOpt, fp);
            }
            else
            {
                //TODO achar a definicao completa do enum
                const char* firstValue =
                    pEnumSpecifier->EnumeratorList.pHead ? pEnumSpecifier->EnumeratorList.pHead->Name :
                    "0";

                if (bDeclaratorIsPointer)
                {
                    StrBuilder_AppendFmt(fp, "/*%s=*/0/*NULL*/", pInitExpressionText);
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
        ASSERT(false);
    }

}



bool IsSuffix(const char* s, const char* suffix)
{
    bool bResult = false;
    int len = strlen(s);
    int len2 = strlen(suffix);
    if (len > len2)
    {
        const char* pEndPart = &s[len - len2];
        if (strcmp(pEndPart, suffix) == 0)
        {
            bResult = true;
        }
    }
    return bResult;

}

TStructUnionSpecifier* GetStructSpecifier(TProgram* program, TDeclarationSpecifiers* specifiers)
{
    TStructUnionSpecifier* pTStructUnionSpecifier =
        TSpecifier_As_TStructUnionSpecifier(specifiers->pHead);

    if (pTStructUnionSpecifier == NULL)
    {
        TSingleTypeSpecifier *pSingleTypeSpecifier =
            TSpecifier_As_TSingleTypeSpecifier(specifiers->pHead);

        if (pSingleTypeSpecifier != NULL &&
            pSingleTypeSpecifier->Token == TK_IDENTIFIER)
        {
            const char * typedefName = pSingleTypeSpecifier->TypedefName;

            TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
            if (pDeclaration)
            {
                pTStructUnionSpecifier =
                    TSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pHead->pNext);

            }
        }
    }

    return pTStructUnionSpecifier;
}

