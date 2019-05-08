#include "Ast.h"
#include "Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Mem.h"

bool IsAutoToken(Tokens token)
{
	return token == TK_AUTO;
}

bool IsSizeToken(Tokens token)
{
	// [Size]
	return token == TK_LEFT_SQUARE_BRACKET;
}

void TDeclarations_Destroy(TDeclarations* p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        TAnyDeclaration_Delete(p->pItems[i]);
    }
    Free((void*)p->pItems);
}
void TDeclarations_Init(TDeclarations* p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}
void TDeclarations_Reserve(TDeclarations* p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        TAnyDeclaration** pnew = p->pItems;
        pnew = (TAnyDeclaration**)Realloc(pnew, n * sizeof(TAnyDeclaration*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}
void TDeclarations_PushBack(TDeclarations* p, TAnyDeclaration* pItem) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TDeclarations_Reserve(p, n);
    }
    p->pItems[p->Size] = pItem;
    p->Size++;
}

TGroupDeclaration* TGroupDeclaration_Create() /*@default*/
{
    TGroupDeclaration *p = (TGroupDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TGroupDeclaration_ID;
        TDeclarations_Init(&p->Declarations);
        String_Init(&p->Identifier);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}
void TGroupDeclaration_Delete(TGroupDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarations_Destroy(&p->Declarations);
        String_Destroy(&p->Identifier);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

void TStructDeclarationList_Destroy(TStructDeclarationList* p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        TAnyStructDeclaration_Delete(p->pItems[i]);
    }
    Free((void*)p->pItems);
}
void TStructDeclarationList_Init(TStructDeclarationList* p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}

void TStructDeclarationList_Reserve(TStructDeclarationList* p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        TAnyStructDeclaration** pnew = p->pItems;
        pnew = (TAnyStructDeclaration**)Realloc(pnew, n * sizeof(TAnyStructDeclaration*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}


void TStructDeclarationList_PushBack(TStructDeclarationList* p, TAnyStructDeclaration* pItem) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TStructDeclarationList_Reserve(p, n);
    }
    p->pItems[p->Size] = pItem;
    p->Size++;
}

void TBlockItemList_Init(TBlockItemList* p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}

void TBlockItemList_Destroy(TBlockItemList* p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        TBlockItem_Delete(p->pItems[i]);
    }
    Free((void*)p->pItems);
}
void TBlockItemList_Reserve(TBlockItemList* p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        TBlockItem** pnew = p->pItems;
        pnew = (TBlockItem**)Realloc(pnew, n * sizeof(TBlockItem*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}
void TBlockItemList_PushBack(TBlockItemList* p, TBlockItem* pItem)/*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TBlockItemList_Reserve(p, n);
    }
    p->pItems[p->Size] = pItem;
    p->Size++;
}

TCompoundStatement* TCompoundStatement_Create() /*@default*/
{
    TCompoundStatement *p = (TCompoundStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TCompoundStatement_ID;
        TBlockItemList_Init(&p->BlockItemList);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}


void TCompoundStatement_Delete(TCompoundStatement* p) /*@default*/
{
    if (p != NULL)
    {
        TBlockItemList_Destroy(&p->BlockItemList);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}

TLabeledStatement* TLabeledStatement_Create(void) /*@default*/
{
    TLabeledStatement *p = (TLabeledStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TLabeledStatement_ID;
        p->pStatementOpt = NULL;
        p->pExpression = NULL;
        String_Init(&p->Identifier);
        p->token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}

void TLabeledStatement_Delete(TLabeledStatement* p)/*@default*/
{
    if (p != NULL)
    {
        TStatement_Delete(p->pStatementOpt);
        TExpression_Delete(p->pExpression);
        String_Destroy(&p->Identifier);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}
TForStatement* TForStatement_Create(void)/*@default*/
{
    TForStatement *p = (TForStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TForStatement_ID;
        p->pInitDeclarationOpt = NULL;
        p->pExpression1 = NULL;
        p->pExpression2 = NULL;
        p->pExpression3 = NULL;
        p->pStatement = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
        TScannerItemList_Init(&p->ClueList4);
    }
    return p;
}

void TForStatement_Delete(TForStatement* p)/*@default*/
{
    if (p != NULL)
    {
        TAnyDeclaration_Delete(p->pInitDeclarationOpt);
        TExpression_Delete(p->pExpression1);
        TExpression_Delete(p->pExpression2);
        TExpression_Delete(p->pExpression3);
        TStatement_Delete(p->pStatement);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        TScannerItemList_Destroy(&p->ClueList4);
        Free((void*)p);
    }
}

TWhileStatement* TWhileStatement_Create(void) /*@default*/
{
    TWhileStatement *p = (TWhileStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TWhileStatement_ID;
        p->pExpression = NULL;
        p->pStatement = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}

void TWhileStatement_Delete(TWhileStatement* p)/*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TStatement_Delete(p->pStatement);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

TDoStatement* TDoStatement_Create(void) /*@default*/
{
    TDoStatement *p = (TDoStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TDoStatement_ID;
        p->pExpression = NULL;
        p->pStatement = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
        TScannerItemList_Init(&p->ClueList4);
    }
    return p;
}

void TDoStatement_Delete(TDoStatement* p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TStatement_Delete(p->pStatement);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        TScannerItemList_Destroy(&p->ClueList4);
        Free((void*)p);
    }
}


TExpressionStatement* TExpressionStatement_Create(void) /*@default*/
{
    TExpressionStatement *p = (TExpressionStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TExpressionStatement_ID;
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}

void TExpressionStatement_Delete(TExpressionStatement* p)/*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}

TJumpStatement* TJumpStatement_Create(void) /*@default*/
{
    TJumpStatement *p = (TJumpStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TJumpStatement_ID;
        p->token = TK_NONE;
        String_Init(&p->Identifier);
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}

void TJumpStatement_Delete(TJumpStatement* p) /*@default*/
{
    if (p != NULL)
    {
        String_Destroy(&p->Identifier);
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}




TAsmStatement* TAsmStatement_Create(void) /*@default*/
{
    TAsmStatement *p = (TAsmStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TAsmStatement_ID;
        TScannerItemList_Init(&p->ClueList);
    }
    return p;
}

void TAsmStatement_Delete(TAsmStatement* p) /*@default*/
{
    if (p != NULL)
    {
        TScannerItemList_Destroy(&p->ClueList);
        Free((void*)p);
    }
}

TSwitchStatement* TSwitchStatement_Create(void) /*@default*/
{
    TSwitchStatement *p = (TSwitchStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TSwitchStatement_ID;
        p->pConditionExpression = NULL;
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}

void TSwitchStatement_Delete(TSwitchStatement* p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pConditionExpression);
        TStatement_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}


TIfStatement* TIfStatement_Create(void) /*@default*/
{
    TIfStatement *p = (TIfStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TIfStatement_ID;
        p->pConditionExpression = NULL;
        p->pStatement = NULL;
        p->pElseStatement = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}

void TIfStatement_Delete(TIfStatement* p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pConditionExpression);
        TStatement_Delete(p->pStatement);
        TStatement_Delete(p->pElseStatement);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        Free((void*)p);
    }
}

void TStatement_Delete(TStatement* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TForStatement_ID:
                    TForStatement_Delete((TForStatement*)p);
                break;
                case TJumpStatement_ID:
                    TJumpStatement_Delete((TJumpStatement*)p);
                break;
                case TExpressionStatement_ID:
                    TExpressionStatement_Delete((TExpressionStatement*)p);
                break;
                case TIfStatement_ID:
                    TIfStatement_Delete((TIfStatement*)p);
                break;
                case TWhileStatement_ID:
                    TWhileStatement_Delete((TWhileStatement*)p);
                break;
                case TSwitchStatement_ID:
                    TSwitchStatement_Delete((TSwitchStatement*)p);
                break;
                case TAsmStatement_ID:
                    TAsmStatement_Delete((TAsmStatement*)p);
                break;
                case TDoStatement_ID:
                    TDoStatement_Delete((TDoStatement*)p);
                break;
                case TLabeledStatement_ID:
                    TLabeledStatement_Delete((TLabeledStatement*)p);
                break;
                case TCompoundStatement_ID:
                    TCompoundStatement_Delete((TCompoundStatement*)p);
                break;
                default:
                break;
            }
    }
}



void TBlockItem_Delete(TBlockItem* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TForStatement_ID:
                    TForStatement_Delete((TForStatement*)p);
                break;
                case TJumpStatement_ID:
                    TJumpStatement_Delete((TJumpStatement*)p);
                break;
                case TExpressionStatement_ID:
                    TExpressionStatement_Delete((TExpressionStatement*)p);
                break;
                case TDeclaration_ID:
                    TDeclaration_Delete((TDeclaration*)p);
                break;
                case TIfStatement_ID:
                    TIfStatement_Delete((TIfStatement*)p);
                break;
                case TWhileStatement_ID:
                    TWhileStatement_Delete((TWhileStatement*)p);
                break;
                case TSwitchStatement_ID:
                    TSwitchStatement_Delete((TSwitchStatement*)p);
                break;
                case TAsmStatement_ID:
                    TAsmStatement_Delete((TAsmStatement*)p);
                break;
                case TDoStatement_ID:
                    TDoStatement_Delete((TDoStatement*)p);
                break;
                case TLabeledStatement_ID:
                    TLabeledStatement_Delete((TLabeledStatement*)p);
                break;
                case TCompoundStatement_ID:
                    TCompoundStatement_Delete((TCompoundStatement*)p);
                break;
                default:
                break;
            }
    }
}

void TPrimaryExpressionValue_Init(TPrimaryExpressionValue* p) /*@default*/
{
    p->Type = TPrimaryExpressionValue_ID;
    p->token = TK_NONE;
    String_Init(&p->lexeme);
    p->pExpressionOpt = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
}

void TPrimaryExpressionValue_Destroy(TPrimaryExpressionValue* p) /*@default*/
{
    String_Destroy(&p->lexeme);
    TExpression_Delete(p->pExpressionOpt);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

TPrimaryExpressionValue* TPrimaryExpressionValue_Create() /*@default*/
{
    TPrimaryExpressionValue *p = (TPrimaryExpressionValue*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TPrimaryExpressionValue_Init(p);
    }
    return p;
}

void TPrimaryExpressionValue_Delete(TPrimaryExpressionValue* p) /*@default*/
{
    if (p != NULL)
    {
        TPrimaryExpressionValue_Destroy(p);
        Free((void*)p);
    }
}

TPrimaryExpressionLambda* TPrimaryExpressionLambda_Create() /*@default*/
{
    TPrimaryExpressionLambda *p = (TPrimaryExpressionLambda*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TPrimaryExpressionLambda_ID;
        p->pCompoundStatement = NULL;
        p->pParameterTypeListOpt = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}

void TPrimaryExpressionLambda_Delete(TPrimaryExpressionLambda* p) /*@default*/
{
    if (p != NULL)
    {
        TParameterTypeList_Delete(p->pParameterTypeListOpt);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        Free((void*)p);
    }
}

void TPostfixExpressionCore_Delete(TPostfixExpressionCore* p) /*@default*/
{
    if (p != NULL)
    {
        String_Destroy(&p->lexeme);
        TExpression_Delete(p->pExpressionLeft);
        TExpression_Delete(p->pExpressionRight);
        TPostfixExpressionCore_Delete(p->pNext);
        TInitializerList_Destroy(&p->InitializerList);
        String_Destroy(&p->Identifier);
        TTypeName_Delete(p->pTypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        TScannerItemList_Destroy(&p->ClueList4);
        Free((void*)p);
    }
}

TBinaryExpression* TBinaryExpression_Create(void) /*@default*/
{
    TBinaryExpression *p = (TBinaryExpression*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TBinaryExpression_ID;
        p->token = TK_NONE;
        p->pExpressionLeft = NULL;
        p->pExpressionRight = NULL;
        p->Position.FileIndex = 0;
        p->Position.Line = 0;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}

void TBinaryExpression_Delete(TBinaryExpression* p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpressionLeft);
        TExpression_Delete(p->pExpressionRight);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}


void TUnaryExpressionOperator_Delete(TUnaryExpressionOperator* p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpressionRight);
        TTypeName_Destroy(&p->TypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}


void TCastExpressionType_Delete(TCastExpressionType* p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TTypeName_Destroy(&p->TypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}

TTernaryExpression* TTernaryExpression_Create(void) /*@default*/
{
    TTernaryExpression *p = (TTernaryExpression*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TTernaryExpression_ID;
        p->token = TK_NONE;
        p->pExpressionLeft = NULL;
        p->pExpressionMiddle = NULL;
        p->pExpressionRight = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}

void TTernaryExpression_Delete(TTernaryExpression* p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpressionLeft);
        TExpression_Delete(p->pExpressionMiddle);
        TExpression_Delete(p->pExpressionRight);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}

void TPrimaryExpressionLiteralItem_Delete(TPrimaryExpressionLiteralItem *p) /*@default*/
{
    if (p != NULL)
    {
        String_Destroy(&p->lexeme);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}
TPrimaryExpressionLiteralItem* TPrimaryExpressionLiteralItem_Create() /*@default*/
{
    TPrimaryExpressionLiteralItem *p = (TPrimaryExpressionLiteralItem*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        String_Init(&p->lexeme);
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}

TPrimaryExpressionLiteral* TPrimaryExpressionLiteral_Create() /*@default*/
{
    TPrimaryExpressionLiteral *p = (TPrimaryExpressionLiteral*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TPrimaryExpressionLiteral_ID;
        TPrimaryExpressionLiteralItemList_Init(&p->List);
    }
    return p;
}


void TPrimaryExpressionLiteral_Delete(TPrimaryExpressionLiteral* p) /*@default*/
{
    if (p != NULL)
    {
        TPrimaryExpressionLiteralItemList_Destroy(&p->List);
        Free((void*)p);
    }
}

void TExpression_Delete(TExpression* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TBinaryExpression_ID:
                    TBinaryExpression_Delete((TBinaryExpression*)p);
                break;
                case TPrimaryExpressionLambda_ID:
                    TPrimaryExpressionLambda_Delete((TPrimaryExpressionLambda*)p);
                break;
                case TUnaryExpressionOperator_ID:
                    TUnaryExpressionOperator_Delete((TUnaryExpressionOperator*)p);
                break;
                case TCastExpressionType_ID:
                    TCastExpressionType_Delete((TCastExpressionType*)p);
                break;
                case TPrimaryExpressionValue_ID:
                    TPrimaryExpressionValue_Delete((TPrimaryExpressionValue*)p);
                break;
                case TPostfixExpressionCore_ID:
                    TPostfixExpressionCore_Delete((TPostfixExpressionCore*)p);
                break;
                case TPrimaryExpressionLiteral_ID:
                    TPrimaryExpressionLiteral_Delete((TPrimaryExpressionLiteral*)p);
                break;
                case TTernaryExpression_ID:
                    TTernaryExpression_Delete((TTernaryExpression*)p);
                break;
                default:
                break;
            }
    }
}


TEofDeclaration* TEofDeclaration_Create() /*@default*/
{
    TEofDeclaration *p = (TEofDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TEofDeclaration_ID;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}


void TEofDeclaration_Delete(TEofDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}



TStaticAssertDeclaration* TStaticAssertDeclaration_Create() /*@default*/
{
    TStaticAssertDeclaration *p = (TStaticAssertDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStaticAssertDeclaration_ID;
        p->pConstantExpression = NULL;
        String_Init(&p->Text);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
        TScannerItemList_Init(&p->ClueList4);
        TScannerItemList_Init(&p->ClueList5);
    }
    return p;
}

void TStaticAssertDeclaration_Delete(TStaticAssertDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pConstantExpression);
        String_Destroy(&p->Text);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        TScannerItemList_Destroy(&p->ClueList4);
        TScannerItemList_Destroy(&p->ClueList5);
        Free((void*)p);
    }
}

TEnumerator* TEnumerator_Create(void) /*@default*/
{
    TEnumerator *p = (TEnumerator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        String_Init(&p->Name);
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        p->bHasComma = false;
    }
    return p;
}

void TEnumerator_Delete(TEnumerator* p) /*@default*/
{
    if (p != NULL)
    {
        String_Destroy(&p->Name);
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

void TEnumeratorList_Init(TEnumeratorList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TEnumeratorList_Destroy(TEnumeratorList* p) 
{
    TEnumerator* pCurrent = p->pHead;
    while (pCurrent)
    {
      TEnumerator* pItem = pCurrent;
      pCurrent = pCurrent->pNext;
      TEnumerator_Delete(pItem);
    }
}

TEnumSpecifier* TEnumSpecifier_Create(void) /*@default*/
{
    TEnumSpecifier *p = (TEnumSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TEnumSpecifier_ID;
        String_Init(&p->Name);
        TEnumeratorList_Init(&p->EnumeratorList);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}

void TEnumSpecifier_Delete(TEnumSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        String_Destroy(&p->Name);
        TEnumeratorList_Destroy(&p->EnumeratorList);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        Free((void*)p);
    }
}



TUnionSetItem* TUnionSetItem_Create() /*@default*/
{
    TUnionSetItem *p = (TUnionSetItem*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        p->Token = TK_NONE;
        p->TokenFollow = TK_NONE;
        String_Init(&p->Name);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}
void TUnionSetItem_Delete(TUnionSetItem* p) /*@default*/
{
    if (p != NULL)
    {
        String_Destroy(&p->Name);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

void TUnionSet_Init(TUnionSet* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);

}

void TUnionSet_Destroy(TUnionSet* p) 
{
    //TUnionSetItem_Delete(p->pHead);
	TUnionSetItem* pCurrent = p->pHead;
	while (pCurrent)
	{
		TUnionSetItem* pItem = pCurrent;
		pCurrent = pCurrent->pNext;
		TUnionSetItem_Delete(pItem);
	}
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    
}


void TUnionSet_PushBack(TUnionSet* pList, TUnionSetItem* pItem)
{
	if (pList->pHead == NULL)
	{
		pList->pHead = (pItem);
	}
	else
	{
		pList->pTail->pNext = pItem;
	}
	pList->pTail = pItem;
}




TStructUnionSpecifier* TStructUnionSpecifier_Create() /*@default*/
{
    TStructUnionSpecifier *p = (TStructUnionSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStructUnionSpecifier_ID;
        TStructDeclarationList_Init(&p->StructDeclarationList);
        String_Init(&p->Name);
        p->Token = TK_NONE;
        p->Token2 = TK_NONE;
        TUnionSet_Init(&p->UnionSet);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}
void TStructUnionSpecifier_Delete(TStructUnionSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        TStructDeclarationList_Destroy(&p->StructDeclarationList);
        String_Destroy(&p->Name);
        TUnionSet_Destroy(&p->UnionSet);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        Free((void*)p);
    }
}


TSingleTypeSpecifier* TSingleTypeSpecifier_Create(void) /*@default*/
{
    TSingleTypeSpecifier *p = (TSingleTypeSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TSingleTypeSpecifier_ID;
        p->Token2 = TK_NONE;
        String_Init(&p->TypedefName);
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TSingleTypeSpecifier_Destroy(TSingleTypeSpecifier* p) /*@default*/
{
    String_Destroy(&p->TypedefName);
    TScannerItemList_Destroy(&p->ClueList0);
}
void TSingleTypeSpecifier_Delete(TSingleTypeSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        TSingleTypeSpecifier_Destroy(p);
        Free((void*)p);
    }
}


const char* TSingleTypeSpecifier_GetTypedefName(TSingleTypeSpecifier* p)
{
	const char* result = NULL;
	if (p->Token2 == TK_IDENTIFIER)
	{
		result = p->TypedefName;
	}
	return result;
}

void TTypeSpecifier_Delete(TTypeSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TStructUnionSpecifier_ID:
                    TStructUnionSpecifier_Delete((TStructUnionSpecifier*)p);
                break;
                case TAtomicTypeSpecifier_ID:
                    TAtomicTypeSpecifier_Delete((TAtomicTypeSpecifier*)p);
                break;
                case TSingleTypeSpecifier_ID:
                    TSingleTypeSpecifier_Delete((TSingleTypeSpecifier*)p);
                break;
                case TEnumSpecifier_ID:
                    TEnumSpecifier_Delete((TEnumSpecifier*)p);
                break;
                default:
                break;
            }
    }
}


void TDeclarator_Init(TDeclarator* p) /*@default*/
{
    p->PointerList.pHead = NULL;
    p->PointerList.pTail = NULL;
    p->pDirectDeclarator = NULL;
    TScannerItemList_Init(&p->ClueList);
}

TDeclarator* TDeclarator_Create() /*@default*/
{
    TDeclarator *p = (TDeclarator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TDeclarator_Init(p);
    }
    return p;
}

void TDeclarator_Destroy(TDeclarator* p) /*@default*/
{
    TPointerList_Destroy(&p->PointerList);
    TDirectDeclarator_Delete(p->pDirectDeclarator);
    TScannerItemList_Destroy(&p->ClueList);
}

void TDeclarator_Swap(TDeclarator* a, TDeclarator* b)
{
  TDeclarator t = *a;
  *a = *b;
  *b = t;
}

void TDeclarator_Delete(TDeclarator* p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarator_Destroy(p);
        Free((void*)p);
    }
}

TInitDeclarator* TInitDeclarator_Create() /*@default*/
{
    TInitDeclarator *p = (TInitDeclarator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pDeclarator = NULL;
        p->pInitializer = NULL;
        p->pNext = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}

void TInitDeclarator_Destroy(TInitDeclarator* p) /*@default*/
{
    TDeclarator_Delete(p->pDeclarator);
    TInitializer_Delete(p->pInitializer);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

void TInitDeclarator_Delete(TInitDeclarator* p) /*@default*/
{
    if (p != NULL)
    {
        TInitDeclarator_Destroy(p);
        Free((void*)p);
    }
}

void TParameterTypeList_Init(TParameterTypeList* p) /*@default*/
{
    TParameterList_Init(&p->ParameterList);
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    p->bVariadicArgs = false;
}
void TParameterTypeList_Destroy(TParameterTypeList* p) /*@default*/
{
    TParameterList_Destroy(&p->ParameterList);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

TParameterTypeList* TParameterTypeList_Create() /*@default*/
{
    TParameterTypeList *p = (TParameterTypeList*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TParameterTypeList_Init(p);
    }
    return p;
}
void TParameterTypeList_Delete(TParameterTypeList* p) /*@default*/
{
    if (p != NULL)
    {
        TParameterTypeList_Destroy(p);
        Free((void*)p);
    }
}

const char* TParameterTypeList_GetFirstParameterName(TParameterTypeList* p)
{
	const char* name = "";
	if (p->ParameterList.pHead)
	{
		name = TDeclarator_GetName(&p->ParameterList.pHead->Declarator);
	}
	return name;
}

bool TParameterTypeList_HasNamedArgs(TParameterTypeList* p)
{
	bool result = false;
	if (p != NULL)
	{
		ForEachListItem(TParameter, pParameter, &p->ParameterList)
		{
			const char* parameterName = TParameter_GetName(pParameter);
			if (parameterName != NULL)
			{
				result = true;
				break;
			}
		}
	}
	return result;
}



void TParameterTypeList_GetArgsString(TParameterTypeList* p, StrBuilder* sb)
{
	if (p != NULL)
	{
		int index = 0;
		ForEachListItem(TParameter, pParameter, &p->ParameterList)
		{
			const char* parameterName = TParameter_GetName(pParameter);
			if (parameterName)
			{
				if (index > 0)
				{
					StrBuilder_Append(sb, ", ");
				}

				StrBuilder_Append(sb, parameterName);
			}

			index++;
		}
	}
}

TParameter* TParameterTypeList_GetParameterByIndex(TParameterTypeList* p, int index)
{
	TParameter* pParameterResult = NULL;
	int indexLocal = 0;

	ForEachListItem(TParameter, pParameter, &p->ParameterList)
	{
		if (indexLocal == index)
		{
			pParameterResult = pParameter;
			break;
		}
		indexLocal++;
	}

	return pParameterResult;
}

TParameter* TParameterTypeList_FindParameterByName(TParameterTypeList* p, const char* name)
{
	TParameter* pParameterResult = NULL;
	if (name)
	{
		ForEachListItem(TParameter, pParameter, &p->ParameterList)
		{
			//F(void) neste caso nao tem nome
			const char* parameterName = TParameter_GetName(pParameter);
			if (parameterName && strcmp(parameterName, name) == 0)
			{
				pParameterResult = pParameter;
				break;
			}
		}
	}
	return pParameterResult;
}

const char* TParameterTypeList_GetSecondParameterName(TParameterTypeList* p)
{
	const char* name = "";
	if (p->ParameterList.pHead &&
		p->ParameterList.pHead->pNext)
	{
		name = TDeclarator_GetName(&p->ParameterList.pHead->pNext->Declarator);
	}
	return name;
}

void TDirectDeclarator_Destroy(TDirectDeclarator* p) /*@default*/
{
    String_Destroy(&p->Identifier);
    TDeclarator_Delete(p->pDeclarator);
    TDirectDeclarator_Delete(p->pDirectDeclarator);
    TParameterTypeList_Destroy(&p->Parameters);
    TExpression_Delete(p->pExpression);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    TScannerItemList_Destroy(&p->ClueList3);
}

void TDirectDeclarator_Delete(TDirectDeclarator* p) /*@default*/
{
    if (p != NULL)
    {
        TDirectDeclarator_Destroy(p);
        Free((void*)p);
    }
}

TDeclarationSpecifier* TSpecifierQualifierList_GetMainSpecifier(TSpecifierQualifierList* p)
{
	TDeclarationSpecifier* pSpecifier = NULL;
	for (int i = 0; i < p->Size; i++)
	{
		TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
		if (pSpecifierQualifier->Type == TSingleTypeSpecifier_ID ||
			pSpecifierQualifier->Type == TStructUnionSpecifier_ID ||
			pSpecifierQualifier->Type == TEnumSpecifier_ID)
		{
            //ATENCAO
			pSpecifier = (TDeclarationSpecifier *)pSpecifierQualifier;
			break;
		}
	}
	return pSpecifier;
}

const char* TSpecifierQualifierList_GetTypedefName(TSpecifierQualifierList* p)
{
	const char* typedefName = NULL;

	for (int i = 0; i < p->Size; i++)
	{
		TSpecifierQualifier* pSpecifierQualifier = p->pData[i];


		TSingleTypeSpecifier* pSingleTypeSpecifier =
			TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
		if (pSingleTypeSpecifier &&
			pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
		{
			typedefName = pSingleTypeSpecifier->TypedefName;
			break;
		}
	}
	return typedefName;
}

bool TSpecifierQualifierList_IsTypedefQualifier(TSpecifierQualifierList* p)
{
	bool bResult = false;
	for (int i = 0; i < p->Size; i++)
	{
		TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
		TStorageSpecifier* pStorageSpecifier =
			TSpecifierQualifier_As_TStorageSpecifier(pSpecifierQualifier);
		if (pStorageSpecifier &&
			pStorageSpecifier->Token == TK_TYPEDEF)
		{
			bResult = true;
			break;
		}
	}
	return bResult;
}

bool TSpecifierQualifierList_IsChar(TSpecifierQualifierList* p)
{
	bool bResult = false;
	for (int i = 0; i < p->Size; i++)
	{
		TSpecifierQualifier* pSpecifierQualifier = p->pData[i];

		TSingleTypeSpecifier* pSingleTypeSpecifier =
			TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
		if (pSingleTypeSpecifier &&
			pSingleTypeSpecifier->Token2 == TK_CHAR)
		{
			bResult = true;
			break;
		}
	}
	return bResult;
}


bool TSpecifierQualifierList_IsAnyInteger(TSpecifierQualifierList* p)
{
	bool bResult = false;
	for (int i = 0; i < p->Size; i++)
	{
		TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
		TSingleTypeSpecifier* pSingleTypeSpecifier =
			TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
		if (pSingleTypeSpecifier &&
			(pSingleTypeSpecifier->Token2 == TK_INT ||
				pSingleTypeSpecifier->Token2 == TK_SHORT ||
				pSingleTypeSpecifier->Token2 == TK_SIGNED ||
				pSingleTypeSpecifier->Token2 == TK_UNSIGNED ||
				pSingleTypeSpecifier->Token2 == TK__INT8 ||
				pSingleTypeSpecifier->Token2 == TK__INT16 ||
				pSingleTypeSpecifier->Token2 == TK__INT32 ||
				pSingleTypeSpecifier->Token2 == TK__INT64 ||
				pSingleTypeSpecifier->Token2 == TK__WCHAR_T)
			)
		{
			bResult = true;
			break;
		}
	}
	return bResult;
}


bool TSpecifierQualifierList_IsAnyFloat(TSpecifierQualifierList* p)
{
	bool bResult = false;
	for (int i = 0; i < p->Size; i++)
	{
		TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
		TSingleTypeSpecifier* pSingleTypeSpecifier =
			TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
		if (pSingleTypeSpecifier &&
			(pSingleTypeSpecifier->Token2 == TK_DOUBLE ||
				pSingleTypeSpecifier->Token2 == TK_FLOAT))
		{
			bResult = true;
			break;
		}
	}
	return bResult;
}

bool TSpecifierQualifierList_IsBool(TSpecifierQualifierList* p)
{
	bool bResult = false;
	for (int i = 0; i < p->Size; i++)
	{
		TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
		TSingleTypeSpecifier* pSingleTypeSpecifier =
			TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);

		if (pSingleTypeSpecifier &&
			pSingleTypeSpecifier->Token2 == TK__BOOL)
		{
			bResult = true;
			break;
		}
	}
	return bResult;
}

const char* TDeclarator_GetName(TDeclarator*   p)
{
	if (p == NULL)
	{
		return NULL;
	}
	TDirectDeclarator* pDirectDeclarator = p->pDirectDeclarator;
	while (pDirectDeclarator != NULL)
	{
		if (pDirectDeclarator->Identifier != NULL &&
			pDirectDeclarator->Identifier[0] != 0)
		{
			return pDirectDeclarator->Identifier;
		}

		if (pDirectDeclarator->pDeclarator)
		{
			const char* name =
				TDeclarator_GetName(pDirectDeclarator->pDeclarator);
			if (name != NULL)
			{
				return name;
			}
		}
		pDirectDeclarator =
			pDirectDeclarator->pDirectDeclarator;
	}
	return NULL;
}

const char* TInitDeclarator_FindName(TInitDeclarator* p)
{
	//assert(p->pDeclarator != NULL);
	return TDeclarator_GetName(p->pDeclarator);
}



TAlignmentSpecifier* TAlignmentSpecifier_Create(void) /*@default*/
{
    TAlignmentSpecifier *p = (TAlignmentSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TAlignmentSpecifier_ID;
        String_Init(&p->TypeName);
    }
    return p;
}
void TAlignmentSpecifier_Destroy(TAlignmentSpecifier* p) /*@default*/
{
    String_Destroy(&p->TypeName);
}

void TAlignmentSpecifier_Delete(TAlignmentSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        TAlignmentSpecifier_Destroy(p);
        Free((void*)p);
    }
}


TStructDeclaration* TStructDeclaration_Create() /*@default*/
{
    TStructDeclaration *p = (TStructDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStructDeclaration_ID;
        p->SpecifierQualifierList.pData = NULL;
        p->SpecifierQualifierList.Size = 0;
        p->SpecifierQualifierList.Capacity = 0;
        TStructDeclaratorList_Init(&p->DeclaratorList);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}


void TStructDeclaratorList_Destroy(TStructDeclaratorList* p) 
{
  TInitDeclarator* pCurrent = p->pHead;
  while (pCurrent)
  {
    TInitDeclarator* pItem = pCurrent;
    pCurrent = pCurrent->pNext;
    TInitDeclarator_Delete(pItem);
  }    
}

void TStructDeclaratorList_Init(TStructDeclaratorList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TStructDeclaratorList_Add(TStructDeclaratorList* pList, TInitDeclarator* pItem)
{
	if (pList->pHead == NULL)
	{
		pList->pHead = pItem;
		pList->pTail = pItem;
	}
	else
	{
		pList->pTail->pNext = pItem;
		pList->pTail = pItem;
	}
}

void TStructDeclaration_Destroy(TStructDeclaration* p) /*@default*/
{
    TSpecifierQualifierList_Destroy(&p->SpecifierQualifierList);
    TStructDeclaratorList_Destroy(&p->DeclaratorList);
    TScannerItemList_Destroy(&p->ClueList1);
}

void TStructDeclaration_Delete(TStructDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
        TStructDeclaration_Destroy(p);
        Free((void*)p);
    }
}


void TAnyStructDeclaration_Delete(TAnyStructDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TStaticAssertDeclaration_ID:
                    TStaticAssertDeclaration_Delete((TStaticAssertDeclaration*)p);
                break;
                case TStructDeclaration_ID:
                    TStructDeclaration_Delete((TStructDeclaration*)p);
                break;
                default:
                break;
            }
    }
}

bool TPointerList_IsAutoPointer(TPointerList* pPointerlist)
{
	bool bIsPointer = false;
	bool bIsAuto = false;
	if (pPointerlist)
	{
		bIsPointer = (pPointerlist->pHead != NULL);

		//ForEachListItem(TPointer, pItem, pPointerlist)
		TPointer* pItem = pPointerlist->pHead;
		//for (T * var = (list)->pHead; var != NULL; var = var->pNext)
		while (pItem)
		{
			for (int i = 0; i < pItem->Qualifier.Size; i++)
			{
				TTypeQualifier* pQualifier = pItem->Qualifier.Data[i];
				if (IsAutoToken(pQualifier->Token))
				{
					bIsAuto = true;
					break;
				}
			}
			if (bIsAuto && bIsPointer)
				break;

			pItem = pItem->pNext;
		}
	}
	return bIsAuto;
}

void TPointerList_Destroy(TPointerList* p)
{
	TPointer* pCurrent = p->pHead;
	while (pCurrent)
	{
		TPointer* pItem = pCurrent;
		pCurrent = pCurrent->pNext;
		TPointer_Delete(pItem);
	}
}

TPointer* TPointer_Create(void) /*@default*/
{
    TPointer *p = (TPointer*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TTypeQualifierList_Init(&p->Qualifier);
        p->pNext = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TPointer_Destroy(TPointer* p) /*@default*/
{
    TTypeQualifierList_Destroy(&p->Qualifier);
    TScannerItemList_Destroy(&p->ClueList0);
}

void TPointerList_PushBack(TPointerList* pList, TPointer* pItem)
{
	if ((pList)->pHead == NULL)
	{
		(pList)->pHead = (pItem);
		(pList)->pTail = (pItem);
	}
	else
	{
		(pList)->pTail->pNext = (pItem);
		(pList)->pTail = (pItem);
	}
}

void TPointer_Delete(TPointer* p) /*@default*/
{
    if (p != NULL)
    {
        TPointer_Destroy(p);
        Free((void*)p);
    }
}

void TPointerList_Printf(TPointerList* p)
{
	ForEachListItem(TPointer, pItem, p)
	{
		printf("*");

		for (int i = 0; i < pItem->Qualifier.Size; i++)
		{
			if (i > 0)
				printf(" ");
			TTypeQualifier* pQualifier = pItem->Qualifier.Data[i];
			printf("%s", TokenToString(pQualifier->Token));

			if (IsSizeToken(pQualifier->Token))
			{
				printf("(%s)", pQualifier->SizeIdentifier);
			}
		}
	}
	printf("\n");
}

void TPointerList_Swap(TPointerList* a, TPointerList* b)
{
	TPointerList t = *a;
	*a = *b;
	*b = t;
}

void TPointer_Copy(TPointer* dest, TPointer* src)
{
	TTypeQualifierList_Copy(&dest->Qualifier, &src->Qualifier);
}

bool TPointerList_IsPointer(TPointerList* pPointerlist)
{
	return pPointerlist->pHead != NULL;
}


const char * TPointerList_GetSize(TPointerList* pPointerlist)
{
	//Esta definicao esta estranha..tem que pegar o size de 1 cara so

	const char* pszResult = NULL;

	if (pPointerlist)
	{
		ForEachListItem(TPointer, pItem, pPointerlist)
		{
			for (int i = 0; i < pItem->Qualifier.Size; i++)
			{
				TTypeQualifier* pQualifier = pItem->Qualifier.Data[i];

				if (IsSizeToken(pQualifier->Token))
				{
					pszResult = pQualifier->SizeIdentifier;
					break;
				}
			}
		}
	}
	return pszResult;
}

bool TPointerList_IsPointerN(TPointerList* pPointerlist, int n)
{
	int k = 0;
	if (pPointerlist)
	{
		ForEachListItem(TPointer, pItem, pPointerlist)
		{

			k++;

		}
	}
	return k == n;
}

bool TPointerList_IsPointerToObject(TPointerList* pPointerlist)
{
	bool bResult = false;
	TPointer* pPointer = pPointerlist->pHead;
	if (pPointer != NULL)
	{
		if (pPointer->Qualifier.Size == 0)
		{
			pPointer = pPointer->pNext;
			if (pPointer == NULL)
			{
				bResult = true;
			}
		}
	}


	return bResult;
}

bool TPointerList_IsAutoPointerToObject(TPointerList* pPointerlist)
{
	//retorna true se tem 1 ponteiro qualificado auto
	bool bResult = false;
	TPointer* pPointer = pPointerlist->pHead;
	if (pPointer != NULL && pPointer->pNext == NULL)
	{
		//so tem 1 ponteiro
		//procura se tem algum qualificador auto
		for (int i = 0; i < pPointer->Qualifier.Size; i++)
		{
			if (IsAutoToken(pPointer->Qualifier.Data[i]->Token))
			{
				bResult = true;
				break;
			}
		}
	}

	return bResult;
}


bool TPointerList_IsAutoPointerSizeToObject(TPointerList* pPointerlist)
{
	bool bResult = false;
	TPointer* pPointer = pPointerlist->pHead;
	if (pPointer != NULL)
	{
		if (pPointer->Qualifier.Size == 2 &&
			pPointer->pNext == NULL)
		{
			bResult = (IsAutoToken(pPointer->Qualifier.Data[0]->Token) &&
				IsSizeToken(pPointer->Qualifier.Data[1]->Token)) ||
				(IsSizeToken(pPointer->Qualifier.Data[0]->Token) &&
					IsAutoToken(pPointer->Qualifier.Data[0]->Token));
		}
	}


	return bResult;
}

bool TPointerList_IsAutoPointerToPointer(TPointerList* pPointerlist)
{
	bool bResult = false;
	TPointer* pPointer = pPointerlist->pHead;
	if (pPointer != NULL)
	{
		if (pPointer->Qualifier.Size == 1 &&
			IsAutoToken(pPointer->Qualifier.Data[0]->Token))
		{
			pPointer = pPointer->pNext;
			if (pPointer != NULL)
			{
				if (pPointer->Qualifier.Size == 0)
				{
					bResult = true;
				}
			}
		}
	}


	return bResult;
}


bool TPointerList_IsAutoPointerToAutoPointer(TPointerList* pPointerlist)
{
	bool bResult = false;
	TPointer* pPointer = pPointerlist->pHead;
	if (pPointer != NULL)
	{
		if (pPointer->Qualifier.Size == 1 &&
			IsAutoToken(pPointer->Qualifier.Data[0]->Token))
		{
			pPointer = pPointer->pNext;
			if (pPointer != NULL)
			{
				if (pPointer->Qualifier.Size == 1 &&
					IsAutoToken(pPointer->Qualifier.Data[0]->Token))
				{
					bResult = true;
				}
				else if (pPointer->Qualifier.Size == 2)
				{
					//auto _size()
					// _size() auto
					bResult = IsAutoToken(pPointer->Qualifier.Data[0]->Token)||
						IsAutoToken(pPointer->Qualifier.Data[1]->Token) ;
				}
			}
		}
	}

	return bResult;
}



void TTypeQualifierList_Destroy(TTypeQualifierList* p)  /*custom*/
{
	for (int i = 0; i < p->Size; i++)
	{
		TTypeQualifier_Delete(p->Data[i]);
	}
}


void TTypeQualifierList_Init(TTypeQualifierList* p)
{
	p->Data[0] = NULL;
	p->Size = 0;
}

void TTypeQualifierList_Copy(TTypeQualifierList* dest, TTypeQualifierList* src)
{
	TTypeQualifierList_Destroy(dest);
	TTypeQualifierList_Init(dest);

	for (int i = 0; i < src->Size; i++)
	{
		TTypeQualifier* pItem = TTypeQualifier_Create();
		TTypeQualifier_Copy(pItem, src->Data[i]);
		TTypeQualifierList_PushBack(dest, pItem);
	}
}

void TTypeQualifierList_PushBack(TTypeQualifierList* p, TTypeQualifier* pItem)
{

	if (p->Size + 1 > 4)
	{
		//nao eh p acontecer!

	}
	else
	{
		p->Data[p->Size] = pItem;
		p->Size++;
	}

}

TTypeQualifier* TTypeQualifier_Create(void) /*@default*/
{
    TTypeQualifier *p = (TTypeQualifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TTypeQualifier_ID;
        String_Init(&p->SizeIdentifier);
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TTypeQualifier_Destroy(TTypeQualifier* p) /*@default*/
{
    String_Destroy(&p->SizeIdentifier);
    TScannerItemList_Destroy(&p->ClueList0);
}
void TTypeQualifier_Delete(TTypeQualifier* p) /*@default*/
{
    if (p != NULL)
    {
        TTypeQualifier_Destroy(p);
        Free((void*)p);
    }
}

void TTypeQualifier_Copy(TTypeQualifier* dest, TTypeQualifier* src)
{
	String_Set(&dest->SizeIdentifier, src->SizeIdentifier);
	dest->Token = src->Token;
	//dest->ClueList0 nao vamos copiar
	//dest->Type nao precisa copiar
}


TStorageSpecifier* TStorageSpecifier_Create(void) /*@default*/
{
    TStorageSpecifier *p = (TStorageSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStorageSpecifier_ID;
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TStorageSpecifier_Destroy(TStorageSpecifier* p) /*@default*/
{
    TScannerItemList_Destroy(&p->ClueList0);
}
void TStorageSpecifier_Delete(TStorageSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        TStorageSpecifier_Destroy(p);
        Free((void*)p);
    }
}


void TAtomicTypeSpecifier_Delete(TAtomicTypeSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        TTypeName_Destroy(&p->TypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

void TSpecifierQualifierList_Destroy(TSpecifierQualifierList* pDeclarationSpecifiers) /*@default*/
{
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TSpecifierQualifier_Delete(pDeclarationSpecifiers->pData[i]);
    }
    Free((void*)pDeclarationSpecifiers->pData);
}


void TSpecifierQualifierList_Reserve(TSpecifierQualifierList* p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        TSpecifierQualifier** pnew = p->pData;
        pnew = (TSpecifierQualifier**)Realloc(pnew, n * sizeof(TSpecifierQualifier*));
        if (pnew)
        {
            p->pData = pnew;
            p->Capacity = n;
        }
    }
}

void TSpecifierQualifierList_PushBack(TSpecifierQualifierList* p, TSpecifierQualifier* pItem) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TSpecifierQualifierList_Reserve(p, n);
    }
    p->pData[p->Size] = pItem;
    p->Size++;
}




bool TSpecifierQualifierList_CanAdd(TSpecifierQualifierList* p, Tokens token, const char* lexeme)
{
	bool bResult = false;

	bool bStruct = false;
	bool bEnum = false;

	bool bTypeDef = false;
	bool bInt = false;
	for (int i = 0; i < p->Size; i++)
	{
		TSpecifierQualifier* pSpecifier = p->pData[i];
		switch (pSpecifier->Type)
		{
			CASE(TSingleTypeSpecifier) :
			{     TSingleTypeSpecifier* pTSingleTypeSpecifier =
				(TSingleTypeSpecifier*)pSpecifier;
			switch (pTSingleTypeSpecifier->Token2)
			{
			case TK_INT:
				bInt = true;
				break;
			case TK_DOUBLE:
				break;

			case TK_IDENTIFIER:
				bTypeDef = true;
				break;
			default:
				//assert(false);
				break;
			}
			}
			break;

			CASE(TStructUnionSpecifier) :
				bStruct = true;
			break;

			CASE(TEnumSpecifier) :
				bEnum = true;
			break;

			CASE(TStorageSpecifier) :

				break;
			CASE(TTypeQualifier) :

				break;
			CASE(TFunctionSpecifier) :

				break;
			CASE(TAlignmentSpecifier) :

				break;
		default:
			//assert(false);
			break;
		}
	}


	if (token == TK_IDENTIFIER)
	{
		if (!bTypeDef && !bInt)
		{
			//Exemplo que se quer evitar
			//typedef int X;
			//void F(int X)
			//nao pode ter nada antes
			bResult = true;
		}
	}
	else
	{
		//verificar combinacoes unsigned float etc.
		bResult = true;
	}
	return bResult;

}

bool TDeclarationSpecifiers_CanAddSpeficier(TDeclarationSpecifiers* pDeclarationSpecifiers,
	Tokens token,
	const char* lexeme)
{
	bool bResult = false;
	bool bStruct = false;
	bool bEnum = false;

	TStructUnionSpecifier* pTStructUnionSpecifier = NULL;
	TEnumSpecifier* pEnumSpecifier = NULL;
	bool bTypeDef = false;
	bool bOther = false;

	for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
	{
		TDeclarationSpecifier* pSpecifier = pDeclarationSpecifiers->pData[i];

		switch (pSpecifier->Type)
		{
			CASE(TSingleTypeSpecifier) :
			{     TSingleTypeSpecifier* pTSingleTypeSpecifier =
				(TSingleTypeSpecifier*)pSpecifier;
			switch (pTSingleTypeSpecifier->Token2)
			{
			//case TK_INT:				
			//case TK_DOUBLE:
				//..etc...
				//bOther = true;
				//break; 

			case TK_IDENTIFIER:
				bTypeDef = true;
				break;
			default:
				bOther = true;
				break;
				////assert(false);
				break;
			}
			}
			break;

			CASE(TStructUnionSpecifier) :
				bStruct = true;
			    pTStructUnionSpecifier = (TStructUnionSpecifier*)pSpecifier;
			break;

			CASE(TEnumSpecifier) :
				bEnum = true;
			pEnumSpecifier = (TEnumSpecifier*)pSpecifier;
			break;

			CASE(TStorageSpecifier) :

				break;
			CASE(TTypeQualifier) :

				break;
			CASE(TFunctionSpecifier) :

				break;
			CASE(TAlignmentSpecifier) :

				break;

		default:
			//assert(false);
			break;
		}
	}


	if (token == TK_IDENTIFIER)
	{
		if (pTStructUnionSpecifier)
		{
			//ja tem uma struct
			if (pTStructUnionSpecifier->Name &&
				strcmp(pTStructUnionSpecifier->Name, lexeme) == 0)
			{
				//typedef struct X X;
			}
			else
			{
				bResult = true;
			}
		}
		else if (pEnumSpecifier)
		{
			//ja tem uma struct
			if (pEnumSpecifier->Name &&
				strcmp(pEnumSpecifier->Name, lexeme) == 0)
			{
				//typedef enum X X;
			}
			else
			{
				bResult = true;
			}
		}
		else if (!bTypeDef && !bOther)
		{
			//Exemplo que se quer evitar
			//typedef int X;
			//void F(int X)
			//nao pode ter nada antes
			bResult = true;
		}
	}
	else
	{
		//verificar combinacoes unsigned float etc.
		bResult = true;
	}
	return bResult;
}

const char* TDeclarationSpecifiers_GetTypedefName(TDeclarationSpecifiers* pDeclarationSpecifiers)
{
	if (pDeclarationSpecifiers == NULL)
	{
		return NULL;
	}
	const char* typeName = NULL;


	for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
	{
		TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];

		TSingleTypeSpecifier* pSingleTypeSpecifier =
			TDeclarationSpecifier_As_TSingleTypeSpecifier(pItem);
		if (pSingleTypeSpecifier != NULL)
		{
			if (pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
			{
				typeName = pSingleTypeSpecifier->TypedefName;
				break;
			}
		}
	}
	return typeName;
}

void TSpecifierQualifier_Delete(TSpecifierQualifier* pItem) /*@default*/
{
    if (pItem != NULL)
    {
            switch (pItem->Type)
            {
                case TTypeQualifier_ID:
                    TTypeQualifier_Delete((TTypeQualifier*)pItem);
                break;
                case TStructUnionSpecifier_ID:
                    TStructUnionSpecifier_Delete((TStructUnionSpecifier*)pItem);
                break;
                case TAtomicTypeSpecifier_ID:
                    TAtomicTypeSpecifier_Delete((TAtomicTypeSpecifier*)pItem);
                break;
                case TSingleTypeSpecifier_ID:
                    TSingleTypeSpecifier_Delete((TSingleTypeSpecifier*)pItem);
                break;
                case TEnumSpecifier_ID:
                    TEnumSpecifier_Delete((TEnumSpecifier*)pItem);
                break;
                default:
                break;
            }
    }
}

void TDeclarationSpecifier_Delete(TDeclarationSpecifier* pItem) /*@default*/
{
    if (pItem != NULL)
    {
            switch (pItem->Type)
            {
                case TTypeQualifier_ID:
                    TTypeQualifier_Delete((TTypeQualifier*)pItem);
                break;
                case TStructUnionSpecifier_ID:
                    TStructUnionSpecifier_Delete((TStructUnionSpecifier*)pItem);
                break;
                case TStorageSpecifier_ID:
                    TStorageSpecifier_Delete((TStorageSpecifier*)pItem);
                break;
                case TAtomicTypeSpecifier_ID:
                    TAtomicTypeSpecifier_Delete((TAtomicTypeSpecifier*)pItem);
                break;
                case TSingleTypeSpecifier_ID:
                    TSingleTypeSpecifier_Delete((TSingleTypeSpecifier*)pItem);
                break;
                case TAlignmentSpecifier_ID:
                    TAlignmentSpecifier_Delete((TAlignmentSpecifier*)pItem);
                break;
                case TFunctionSpecifier_ID:
                    TFunctionSpecifier_Delete((TFunctionSpecifier*)pItem);
                break;
                case TEnumSpecifier_ID:
                    TEnumSpecifier_Delete((TEnumSpecifier*)pItem);
                break;
                default:
                break;
            }
    }
}

void TDeclarationSpecifiers_Init(TDeclarationSpecifiers* pDeclarationSpecifiers) /*@default*/
{
    pDeclarationSpecifiers->pData = NULL;
    pDeclarationSpecifiers->Size = 0;
    pDeclarationSpecifiers->Capacity = 0;
}

void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers* pDeclarationSpecifiers) /*@default*/
{
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TDeclarationSpecifier_Delete(pDeclarationSpecifiers->pData[i]);
    }
    Free((void*)pDeclarationSpecifiers->pData);
}


void TDeclarationSpecifiers_Reserve(TDeclarationSpecifiers* p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        TDeclarationSpecifier** pnew = p->pData;
        pnew = (TDeclarationSpecifier**)Realloc(pnew, n * sizeof(TDeclarationSpecifier*));
        if (pnew)
        {
            p->pData = pnew;
            p->Capacity = n;
        }
    }
}

void TDeclarationSpecifiers_PushBack(TDeclarationSpecifiers* p, TDeclarationSpecifier* pItem) /*@default*/
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        TDeclarationSpecifiers_Reserve(p, n);
    }
    p->pData[p->Size] = pItem;
    p->Size++;
}


TDeclarator* TDeclaration_FindDeclarator(TDeclaration*  p, const char* name)
{
	if (p == NULL)
	{
		return NULL;
	}
	TDeclarator*  pResult = NULL;

	ForEachListItem(TInitDeclarator, pInitDeclarator, &p->InitDeclaratorList)
	{
		if (pInitDeclarator->pDeclarator &&
			pInitDeclarator->pDeclarator->pDirectDeclarator &&
			pInitDeclarator->pDeclarator->pDirectDeclarator->Identifier)
		{
			if (strcmp(pInitDeclarator->pDeclarator->pDirectDeclarator->Identifier, name) == 0)
			{
				pResult = pInitDeclarator->pDeclarator;
				break;
			}
		}
	}
	return pResult;
}

TFunctionSpecifier* TFunctionSpecifier_Create(void) /*@default*/
{
    TFunctionSpecifier *p = (TFunctionSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TFunctionSpecifier_ID;
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TFunctionSpecifier_Destroy(TFunctionSpecifier* p) /*@default*/
{
    TScannerItemList_Destroy(&p->ClueList0);
}
void TFunctionSpecifier_Delete(TFunctionSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        TFunctionSpecifier_Destroy(p);
        Free((void*)p);
    }
}



bool TDeclaration_Is_StructOrUnionDeclaration(TDeclaration* p)
{
	bool bIsStructOrUnion = false;
	for (int i = 0; i < p->Specifiers.Size; i++)
	{
		TDeclarationSpecifier* pItem = p->Specifiers.pData[i];
		if (TDeclarationSpecifier_As_TStructUnionSpecifier(pItem))
		{
			bIsStructOrUnion = true;
			break;
		}

	}
	return bIsStructOrUnion;
}

void TInitDeclaratorList_Init(TInitDeclaratorList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TInitDeclaratorList_Destroy(TInitDeclaratorList* p)
{
	TInitDeclarator* pCurrent = p->pHead;
	while (pCurrent)
	{
		TInitDeclarator* pItem = pCurrent;
		pCurrent = pCurrent->pNext;
		TInitDeclarator_Delete(pItem);
	}

}



void TDeclaration_Delete(TDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarationSpecifiers_Destroy(&p->Specifiers);
        TInitDeclaratorList_Destroy(&p->InitDeclaratorList);
        TCompoundStatement_Delete(p->pCompoundStatementOpt);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}
TDeclaration* TDeclaration_Create() /*@default*/
{
    TDeclaration *p = (TDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TDeclaration_ID;
        TDeclarationSpecifiers_Init(&p->Specifiers);
        TInitDeclaratorList_Init(&p->InitDeclaratorList);
        p->pCompoundStatementOpt = NULL;
        p->FileIndex = 0;
        p->Line = 0;
        TScannerItemList_Init(&p->ClueList0);
        p->bDefault = false;
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}


void TParameter_Swap(TParameter* a, TParameter* b)
{
	TParameter temp = *a;
	*a = *b;
	*b = temp;
}

const char* TDeclarationSpecifier_GetTypedefName(TDeclarationSpecifiers* p)
{
	const char* typedefName = NULL;
	for (int i = 0; i < p->Size; i++)
	{
		TDeclarationSpecifier* pSpecifier = p->pData[i];
		TSingleTypeSpecifier *pSingleTypeSpecifier =
			TDeclarationSpecifier_As_TSingleTypeSpecifier(pSpecifier);
		if (pSingleTypeSpecifier &&
			pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
		{
			typedefName = pSingleTypeSpecifier->TypedefName;
		}
	}
	return typedefName;
}

const char* TParameter_GetName(TParameter* p)
{
	//F(void) neste caso nao tem nome
	return TDeclarator_GetName(&p->Declarator);
}

const char* TParameter_GetTypedefName(TParameter* p)
{
	return TDeclarationSpecifier_GetTypedefName(&p->Specifiers);
}

bool TDeclarator_IsDirectPointer(TDeclarator* p)
{
	int n = 0;
	ForEachListItem(TPointer, pPointer, &p->PointerList)
	{
		n++;
		if (n > 1)
		{
			break;
		}
	}
	return n == 1;
}

bool TParameter_IsDirectPointer(TParameter* p)
{
	return TDeclarator_IsDirectPointer(&p->Declarator);
}


TParameter* TParameter_Create() /*@default*/
{
    TParameter *p = (TParameter*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        TDeclarationSpecifiers_Init(&p->Specifiers);
        TDeclarator_Init(&p->Declarator);
        TScannerItemList_Init(&p->ClueList0);
        p->bHasComma = false;
    }
    return p;
}

void TParameter_Delete(TParameter* p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarationSpecifiers_Destroy(&p->Specifiers);
        TDeclarator_Destroy(&p->Declarator);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}

void TParameterList_Init(TParameterList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TParameterList_Destroy(TParameterList* p)
{
	TParameter* pCurrent = p->pHead;
	while (pCurrent)
	{
		TParameter* p = pCurrent;
		pCurrent = pCurrent->pNext;
		TParameter_Delete(p);
	}
}


bool TAnyDeclaration_Is_StructOrUnionDeclaration(TAnyDeclaration* pAnyDeclaration)
{
	TDeclaration *  pDeclaration = TAnyDeclaration_As_TDeclaration(pAnyDeclaration);
	if (pDeclaration != NULL)
	{
		return TDeclaration_Is_StructOrUnionDeclaration(pDeclaration);
	}

	return false;
}


bool TDeclarationSpecifiers_IsTypedef(TDeclarationSpecifiers* pDeclarationSpecifiers)
{
	bool bResult = false;
	for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
	{
		TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];
		switch (pItem->Type)
		{
			CASE(TStorageSpecifier) :
			{
				TStorageSpecifier* pStorageSpecifier =
					(TStorageSpecifier*)pItem;

				if (pStorageSpecifier->Token == TK_TYPEDEF)
				{
					bResult = true;
				}
			}

			break;
		default:
			//assert(false);
			break;
		}

		if (bResult)
		{
			break;
		}
	}
	return bResult;
}

bool TAnyDeclaration_IsTypedef(TAnyDeclaration* pDeclaration)
{
	bool bResult = false;
	switch (pDeclaration->Type)
	{
	case TDeclaration_ID:
	{
		TDeclaration* p = (TDeclaration*)pDeclaration;
		bResult = TDeclarationSpecifiers_IsTypedef(&p->Specifiers);
	}
	break;
	default:
		//assert(false);
		break;
	}
	return bResult;
}

int TAnyDeclaration_GetFileIndex(TAnyDeclaration* pDeclaration)
{
	int result = -1;
	switch (pDeclaration->Type)
	{
	case TDeclaration_ID:
		result = ((TDeclaration*)pDeclaration)->FileIndex;
		break;
	case TStaticAssertDeclaration_ID:
		break;
	default:
		//assert(false);
		break;
	}
	return result;
}

void TAnyDeclaration_Delete(TAnyDeclaration* pDeclaration) /*@default*/
{
    if (pDeclaration != NULL)
    {
            switch (pDeclaration->Type)
            {
                case TGroupDeclaration_ID:
                    TGroupDeclaration_Delete((TGroupDeclaration*)pDeclaration);
                break;
                case TStaticAssertDeclaration_ID:
                    TStaticAssertDeclaration_Delete((TStaticAssertDeclaration*)pDeclaration);
                break;
                case TDeclaration_ID:
                    TDeclaration_Delete((TDeclaration*)pDeclaration);
                break;
                case TEofDeclaration_ID:
                    TEofDeclaration_Delete((TEofDeclaration*)pDeclaration);
                break;
                default:
                break;
            }
    }
}

void TDesignation_Destroy(TDesignation* pDesignation) /*@default*/
{
    TDesignatorList_Destroy(&pDesignation->DesignatorList);
    TScannerItemList_Destroy(&pDesignation->ClueList0);
}

TDesignator* TDesignator_Create(void) /*@default*/
{
    TDesignator *p = (TDesignator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        String_Init(&p->Name);
        p->pExpression = NULL;
        p->pNext = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}
void TDesignator_Destroy(TDesignator* p) /*@default*/
{
    String_Destroy(&p->Name);
    TExpression_Delete(p->pExpression);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}
void TDesignator_Delete(TDesignator* p) /*@default*/
{
    if (p != NULL)
    {
        TDesignator_Destroy(p);
        Free((void*)p);
    }
}


TInitializerListType* TInitializerListType_Create(void) /*@default*/
{
    TInitializerListType *p = (TInitializerListType*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TInitializerListType_ID;
        TInitializerList_Init(&p->InitializerList);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        p->bDefault = false;
    }
    return p;
}
void TInitializerListType_Destroy(TInitializerListType* p) /*@default*/
{
    TInitializerList_Destroy(&p->InitializerList);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
}
void TInitializerListType_Delete(TInitializerListType* p) /*@default*/
{
    if (p != NULL)
    {
        TInitializerListType_Destroy(p);
        Free((void*)p);
    }
}

void TInitializerList_Init(TInitializerList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TInitializerList_Destroy(TInitializerList* p)
{
	TInitializerListItem* pCurrent = p->pHead;
	while (pCurrent)
	{
		TInitializerListItem* p = pCurrent;
		pCurrent = pCurrent->pNext;
		TInitializerListItem_Delete(p);
	}
    
}

void TInitializer_Delete(TInitializer* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TBinaryExpression_ID:
                    TBinaryExpression_Delete((TBinaryExpression*)p);
                break;
                case TPrimaryExpressionLambda_ID:
                    TPrimaryExpressionLambda_Delete((TPrimaryExpressionLambda*)p);
                break;
                case TUnaryExpressionOperator_ID:
                    TUnaryExpressionOperator_Delete((TUnaryExpressionOperator*)p);
                break;
                case TCastExpressionType_ID:
                    TCastExpressionType_Delete((TCastExpressionType*)p);
                break;
                case TInitializerListType_ID:
                    TInitializerListType_Delete((TInitializerListType*)p);
                break;
                case TPrimaryExpressionValue_ID:
                    TPrimaryExpressionValue_Delete((TPrimaryExpressionValue*)p);
                break;
                case TPostfixExpressionCore_ID:
                    TPostfixExpressionCore_Delete((TPostfixExpressionCore*)p);
                break;
                case TPrimaryExpressionLiteral_ID:
                    TPrimaryExpressionLiteral_Delete((TPrimaryExpressionLiteral*)p);
                break;
                case TTernaryExpression_ID:
                    TTernaryExpression_Delete((TTernaryExpression*)p);
                break;
                default:
                break;
            }
    }
}


void TDesignatorList_Init(TDesignatorList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TDesignatorList_Destroy(TDesignatorList* p)
{
	TDesignator* pCurrent = p->pHead;
	while (pCurrent)
	{
		TDesignator* p = pCurrent;
		pCurrent = pCurrent->pNext;
		TDesignator_Delete(p);
	}

}

void TDesignatorList_PushBack(TDesignatorList* pList, TDesignator* pItem)
{
	if (pList->pHead == NULL)
	{
		pList->pHead = pItem;
	}
	else
	{
		pList->pTail->pNext = pItem;
	}
	pList->pTail = pItem;
}

void TInitializerListItem_Destroy(TInitializerListItem* p) /*@default*/
{
    TDesignatorList_Destroy(&p->DesignatorList);
    TInitializer_Delete(p->pInitializer);
    TScannerItemList_Destroy(&p->ClueList);
}

TInitializerListItem* TInitializerListItem_Create() /*@default*/
{
    TInitializerListItem *p = (TInitializerListItem*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TDesignatorList_Init(&p->DesignatorList);
        p->pInitializer = NULL;
        p->pNext = NULL;
        TScannerItemList_Init(&p->ClueList);
        p->bDefault = false;
    }
    return p;
}
void TInitializerListItem_Delete(TInitializerListItem* p) /*@default*/
{
    if (p != NULL)
    {
        TInitializerListItem_Destroy(p);
        Free((void*)p);
    }
}




TDeclaration* TProgram_FindDeclaration(TProgram* p, const char* name)
{
	TTypePointer* pt = SymbolMap_Find(&p->GlobalScope, name);
	if (pt != NULL &&
		pt->Type == TDeclaration_ID)
	{
		return (TDeclaration*)pt;
	}
	return NULL;
	//return DeclarationsMap_FindDeclaration(&p->Symbols, name);
}

TDeclaration* TProgram_FindFunctionDeclaration(TProgram* p, const char* name)
{
	TTypePointer* pt = SymbolMap_Find(&p->GlobalScope, name);
	if (pt != NULL &&
		pt->Type == TDeclaration_ID)
	{
		return (TDeclaration*)pt;
	}
	return NULL;
}



//Retorna a declaracao final do tipo entrando em cada typedef. 
TDeclaration* TProgram_GetFinalTypeDeclaration(TProgram* p, const char* typeName)
{
	return SymbolMap_FindTypedefDeclarationTarget(&p->GlobalScope, typeName);
}


void TProgram_Init(TProgram* p) /*@default*/
{
    TDeclarations_Init(&p->Declarations);
    TFileArray_Init(&p->Files2);
    SymbolMap_Init(&p->GlobalScope);
    MacroMap_Init(&p->Defines);
    StrBuilder_Init(&p->sbPreDeclaration);
}


void TProgram_Destroy(TProgram * p) /*@default*/
{
    TDeclarations_Destroy(&p->Declarations);
    TFileArray_Destroy(&p->Files2);
    SymbolMap_Destroy(&p->GlobalScope);
    MacroMap_Destroy(&p->Defines);
    StrBuilder_Destroy(&p->sbPreDeclaration);
}



///////////////////////////////////////////

static bool TPostfixExpressionCore_CodePrint2(TPostfixExpressionCore * p,
	int *pResult)
{

	int result = *pResult;

	if (p->pExpressionLeft)
	{
		int left;
		EvaluateConstantExpression(p->pExpressionLeft, &left);
	}

	//if (p->pInitializerList)
	{
		//falta imprimeir typename
		//TTypeName_Print*
		//b = TInitializerList_CodePrint(p->pInitializerList, b, fp);
	}

	switch (p->token)
	{
	case TK_FULL_STOP:
		//fprintf(fp, ".%s", p->Identifier);
		//assert(false);
		break;
	case TK_ARROW:
		//fprintf(fp, "->%s", p->Identifier);
		//b = true;
		//assert(false);
		break;

	case TK_LEFT_SQUARE_BRACKET:
	{
		int index;
		//fprintf(fp, "[");
		EvaluateConstantExpression(p->pExpressionRight, &index);
		//fprintf(fp, "]");
		//assert(false);
	}
	break;

	case TK_LEFT_PARENTHESIS:
	{
		EvaluateConstantExpression(p->pExpressionRight, &result);
	}
	break;

	case TK_PLUSPLUS:
		//assert(false);
		break;
	case TK_MINUSMINUS:
		//assert(false);
		break;
	default:
		//assert(false);
		break;
	}



	if (p->pNext)
	{
		int result2 = result;
		TPostfixExpressionCore_CodePrint2(p->pNext, &result2);
		result = result2;
	}

	return true;
}

//Criado para avaliacao do #if
//Tem que arrumar para fazer os casts do enum
bool EvaluateConstantExpression(TExpression *  p, int *pResult)
{
	int result = -987654321;

	if (p == NULL)
	{
		return false;
	}
	bool b = false;

	switch (p->Type)
	{
		CASE(TBinaryExpression) :
		{
			TBinaryExpression* pBinaryExpression =
				(TBinaryExpression*)p;

			int left;
			b = EvaluateConstantExpression(pBinaryExpression->pExpressionLeft, &left);

			int right;
			b = EvaluateConstantExpression(pBinaryExpression->pExpressionRight, &right);

			switch (pBinaryExpression->token)
			{
			case TK_ASTERISK:
				result = (left * right);
				b = true;
				break;
			case TK_PLUS_SIGN:
				result = (left + right);
				b = true;
				break;
			case TK_HYPHEN_MINUS:
				result = (left - right);
				b = true;
				break;
			case TK_ANDAND:
				result = (left && right);
				b = true;
				break;
			case TK_OROR:
				result = (left || right);
				b = true;
				break;
			case TK_NOTEQUAL:
				result = (left != right);
				b = true;
				break;
			case TK_EQUALEQUAL:
				result = (left == right);
				b = true;
				break;
			case TK_GREATEREQUAL:
				result = (left >= right);
				b = true;
				break;
			case TK_LESSEQUAL:
				result = (left <= right);
				b = true;
				break;
			case TK_GREATER_THAN_SIGN:
				result = (left > right);
				b = true;
				break;
			case TK_LESS_THAN_SIGN:
				result = (left < right);
				b = true;
				break;
			case TK_AMPERSAND:
				result = (left & right);
				b = true;
				break;
			case TK_GREATERGREATER:
				result = (left >> right);
				b = true;
				break;
			case TK_LESSLESS:
				result = (left << right);
				b = true;
				break;
			case TK_VERTICAL_LINE:
				result = (left | right);
				b = true;
				break;

			case TK_SOLIDUS:
				if (right != 0)
				{
					result = (left / right);
					b = true;
				}
				else
				{
					b = false;
					//SetError
				}
				break;


			default:
				//TODO ADD THE OPERADOR?
				//assert(false);
				b = false;
				break;
			}

			//if (pBinaryExpression->)
		}
		break;

		CASE(TTernaryExpression) :
		{
			int e1, e2, e3;
			b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionLeft, &e1);

			b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionMiddle, &e2);

			b = EvaluateConstantExpression(((TTernaryExpression*)p)->pExpressionRight, &e3);
			//assert(false);
		}
		break;

		CASE(TPrimaryExpressionValue) :
		{
			TPrimaryExpressionValue* pPrimaryExpressionValue =
				(TPrimaryExpressionValue*)p;

			if (pPrimaryExpressionValue->pExpressionOpt != NULL)
			{
				b = EvaluateConstantExpression(pPrimaryExpressionValue->pExpressionOpt, &result);
			}
			else
			{
				switch (pPrimaryExpressionValue->token)
				{
				case TK_IDENTIFIER:
					result = 0; //para macro
					b = true;
					break;

				case TK_DECIMAL_INTEGER:
					result = atoi(pPrimaryExpressionValue->lexeme);
					b = true;
					break;

				case TK_HEX_INTEGER:
					result = strtol(pPrimaryExpressionValue->lexeme, NULL, 16);
					b = true;
					break;

				case TK_CHAR_LITERAL:
					if (pPrimaryExpressionValue->lexeme != NULL)
					{
						//vem com 'A'
						result = pPrimaryExpressionValue->lexeme[1];
						b = true;
					}
					else
					{
						result = 0;
					}
					break;
				default:
					b = false;
					//assert(0);
					break;
				}

			}
		}
		break;

		CASE(TPostfixExpressionCore) :
		{
			TPostfixExpressionCore* pPostfixExpressionCore =
				(TPostfixExpressionCore*)p;
			b = TPostfixExpressionCore_CodePrint2(pPostfixExpressionCore, &result);
			//assert(false);
		}
		break;

		CASE(TUnaryExpressionOperator) :
		{

			TUnaryExpressionOperator* pTUnaryExpressionOperator =
				(TUnaryExpressionOperator*)p;

			if (pTUnaryExpressionOperator->token == TK_SIZEOF)
			{

				//if (TDeclarationSpecifiers_IsTypedef(pTUnaryExpressionOperator->TypeName.SpecifierQualifierList))
				{

					//b = TTypeQualifier_CodePrint2(&pTUnaryExpressionOperator->TypeName.qualifiers, fp);
					//b = TTypeSpecifier_CodePrint2(pTUnaryExpressionOperator->TypeName.pTypeSpecifier, b, fp);
					// b = TDeclarator_CodePrint(&pTUnaryExpressionOperator->TypeName.declarator, b, fp);


				}
				//else
				{
					b = EvaluateConstantExpression(pTUnaryExpressionOperator->pExpressionRight, &result);
				}
			}
			else
			{
				int localResult;
				b = EvaluateConstantExpression(pTUnaryExpressionOperator->pExpressionRight, &localResult);
				switch (pTUnaryExpressionOperator->token)
				{
				case TK_EXCLAMATION_MARK:
					result = !localResult;
					b = true;
					break;
				case TK_HYPHEN_MINUS:
					result = -localResult;
					b = true;
					break;
				default:
					//assert(false);
					break;
				}
			}


		}
		break;

		CASE(TCastExpressionType) :
		{
			TCastExpressionType * pCastExpressionType =
				(TCastExpressionType*)p;


			//b = TTypeQualifier_CodePrint2(&pCastExpressionType->TypeName.qualifiers, fp);
			//b = TTypeSpecifier_CodePrint2(pCastExpressionType->TypeName.pTypeSpecifier, b, fp);
			//b = TDeclarator_CodePrint(&pCastExpressionType->TypeName.declarator, b, fp);

			b = EvaluateConstantExpression(pCastExpressionType->pExpression, &result);
			//assert(false);

		}
		break;

	default:
		//assert(false);
		break;
	}

	//assert(result != -987654321);
	*pResult = result;
	return b;
}



TDeclarationSpecifiers* TDeclaration_GetArgTypeSpecifier(TDeclaration* p, int index)
{
	TDeclarationSpecifiers* pResult = NULL;
	TParameterTypeList *pArguments = TDeclaration_GetFunctionArguments(p);
	int n = 0;
	ForEachListItem(TParameter, pItem, &pArguments->ParameterList)
	{
		if (n == index)
		{
			pResult = &pItem->Specifiers;
			break;
		}
		n++;
	}
	return pResult;
}

TParameterTypeList * TDeclaration_GetFunctionArguments(TDeclaration* p)
{
	TParameterTypeList* pParameterTypeList = NULL;

	if (p->InitDeclaratorList.pHead != NULL)
	{
		if (p->InitDeclaratorList.pHead->pNext == NULL)
		{
			if (p->InitDeclaratorList.pHead->pDeclarator != NULL)
			{
				if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator)
				{
					if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
					{
						pParameterTypeList =
							&p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Parameters;

					}
				}
			}
		}
	}
	return pParameterTypeList;
}

const char* TDeclaration_GetFunctionName(TDeclaration* p)
{
	const char* functionName = NULL;

	if (p->InitDeclaratorList.pHead != NULL)
	{
		if (p->InitDeclaratorList.pHead->pNext == NULL)
		{
			if (p->InitDeclaratorList.pHead->pDeclarator != NULL)
			{
				if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator)
				{
					if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
					{
						functionName =
							p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Identifier;
					}
				}
			}
		}
	}
	return functionName;
}

TCompoundStatement* TDeclaration_Is_FunctionDefinition(TDeclaration* p)
{
	TCompoundStatement* pCompoundStatement = NULL;

	if (p->InitDeclaratorList.pHead != NULL)
	{
		if (p->InitDeclaratorList.pHead->pNext == NULL)
		{
			if (p->InitDeclaratorList.pHead->pDeclarator != NULL)
			{
				if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator)
				{
					if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
					{
						pCompoundStatement = p->pCompoundStatementOpt;
					}
				}
			}
		}
	}
	return pCompoundStatement;
}

TStructUnionSpecifier* TDeclarationSpecifiers_Find_StructUnionSpecifier(TDeclarationSpecifiers* p)
{
	TStructUnionSpecifier* pStructUnionSpecifier = NULL;

	for (int i = 0; i < p->Size; i++)
	{
		TDeclarationSpecifier* pDeclarationSpecifier = p->pData[i];

		pStructUnionSpecifier =
			TDeclarationSpecifier_As_TStructUnionSpecifier(pDeclarationSpecifier);
		if (pStructUnionSpecifier)
		{
			break;
		}
	}
	return pStructUnionSpecifier;
}

TStructUnionSpecifier* TParameter_Is_DirectPointerToStruct(TProgram* program, TParameter* pParameter)
{
	TStructUnionSpecifier* pStructUnionSpecifier = NULL;
	if (TParameter_IsDirectPointer(pParameter))
	{
		const char* typedefName = TParameter_GetTypedefName(pParameter);
		if (typedefName != NULL)
		{
			TDeclaration* pArgType = TProgram_FindDeclaration(program, TParameter_GetTypedefName(pParameter));
			if (pArgType)
			{
				pStructUnionSpecifier =
					TDeclarationSpecifiers_Find_StructUnionSpecifier(&pArgType->Specifiers);
			}
		}
	}
	return pStructUnionSpecifier;
}

void TPrimaryExpressionLiteralItemList_Init(TPrimaryExpressionLiteralItemList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TPrimaryExpressionLiteralItemList_Destroy(TPrimaryExpressionLiteralItemList* p)
{
	TPrimaryExpressionLiteralItem* pCurrent = p->pHead;
	while (pCurrent)
	{
		TPrimaryExpressionLiteralItem* pItem = pCurrent;
		pCurrent = pCurrent->pNext;
		TPrimaryExpressionLiteralItem_Delete(pItem);
	}
}

void TPrimaryExpressionLiteralItemList_Add(TPrimaryExpressionLiteralItemList* pList, TPrimaryExpressionLiteralItem *pItem)
{
	if (pList->pHead == NULL)
	{
		pList->pHead = pItem;
		pList->pTail = pItem;
	}
	else
	{
		pList->pTail->pNext = pItem;
		pList->pTail = pItem;
	}

}

const char* TDeclaration_GetArgName(TDeclaration* p, int index)
{
	const char* argName = NULL;
	TParameterTypeList *pArguments = TDeclaration_GetFunctionArguments(p);
	int n = 0;
	ForEachListItem(TParameter, pItem, &pArguments->ParameterList)
	{
		if (n == index)
		{
			argName = TParameter_GetName(pItem);
			break;
		}
		n++;
	}
	return argName;
}


int TDeclaration_GetNumberFuncArgs(TDeclaration* p)
{
	TParameterTypeList *pArguments = TDeclaration_GetFunctionArguments(p);
	int n = 0;
	ForEachListItem(TParameter, pItem, &pArguments->ParameterList)
	{
		n++;
	}
	return n;
}






TDirectDeclarator* TDirectDeclarator_Create() /*@default*/
{
    TDirectDeclarator *p = (TDirectDeclarator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        String_Init(&p->Identifier);
        p->pDeclarator = NULL;
        p->pDirectDeclarator = NULL;
        p->Position.FileIndex = 0;
        p->Position.Line = 0;
        TParameterTypeList_Init(&p->Parameters);
        p->pExpression = NULL;
        p->DeclaratorType = TDirectDeclaratorTypeNone;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}


TTypeName* TTypeName_Create() /*@default*/
{
    TTypeName *p = (TTypeName*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TTypeName_Init(p);
    }
    return p;
}


void TTypeName_Destroy(TTypeName* p) /*@default*/
{
    TSpecifierQualifierList_Destroy(&p->SpecifierQualifierList);
    TDeclarator_Destroy(&p->Declarator);
}

void TTypeName_Delete(TTypeName* p) /*@default*/
{
    if (p != NULL)
    {
        TTypeName_Destroy(p);
        Free((void*)p);
    }
}


TAtomicTypeSpecifier* TAtomicTypeSpecifier_Create() /*@default*/
{
    TAtomicTypeSpecifier *p = (TAtomicTypeSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TAtomicTypeSpecifier_ID;
        TTypeName_Init(&p->TypeName);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}




TPostfixExpressionCore* TPostfixExpressionCore_Create() /*@default*/
{
    TPostfixExpressionCore *p = (TPostfixExpressionCore*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TPostfixExpressionCore_ID;
        p->token = TK_NONE;
        String_Init(&p->lexeme);
        p->pExpressionLeft = NULL;
        p->pExpressionRight = NULL;
        p->pNext = NULL;
        TInitializerList_Init(&p->InitializerList);
        String_Init(&p->Identifier);
        p->pTypeName = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
        TScannerItemList_Init(&p->ClueList4);
    }
    return p;
}

TCastExpressionType* TCastExpressionType_Create() /*@default*/
{
    TCastExpressionType *p = (TCastExpressionType*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TCastExpressionType_ID;
        p->pExpression = NULL;
        TTypeName_Init(&p->TypeName);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}


TUnaryExpressionOperator* TUnaryExpressionOperator_Create() /*@default*/
{
    TUnaryExpressionOperator *p = (TUnaryExpressionOperator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TUnaryExpressionOperator_ID;
        p->token = TK_NONE;
        p->pExpressionRight = NULL;
        TTypeName_Init(&p->TypeName);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}



