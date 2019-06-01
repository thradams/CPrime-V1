#include "Ast.h"
#include "Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Mem.h"

bool IsAutoToken(enum Tokens token)
{
    return token == TK_AUTO;
}

bool IsSizeToken(enum Tokens token)
{
    // [Size]
    return token == TK_LEFT_SQUARE_BRACKET;
}

void TDeclarations_Destroy(struct TDeclarations* p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        TAnyDeclaration_Delete(p->pItems[i]);
    }
    Free((void*)p->pItems);
}
void TDeclarations_Init(struct TDeclarations* p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}
void TDeclarations_Reserve(struct TDeclarations* p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        struct TAnyDeclaration** pnew = p->pItems;
        pnew = (struct TAnyDeclaration**)Realloc(pnew, n * sizeof(struct TAnyDeclaration*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}
void TDeclarations_PushBack(struct TDeclarations* p, struct TAnyDeclaration* pItem) /*@default*/
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

struct TGroupDeclaration* TGroupDeclaration_Create() /*@default*/
{
    struct TGroupDeclaration* p = (struct TGroupDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TGroupDeclaration_ID;
        TDeclarations_Init(&p->Declarations);
        p->Identifier = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}
void TGroupDeclaration_Delete(struct TGroupDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarations_Destroy(&p->Declarations);
        Free((void*)p->Identifier);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

void TStructDeclarationList_Destroy(struct TStructDeclarationList* p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        TAnyStructDeclaration_Delete(p->pItems[i]);
    }
    Free((void*)p->pItems);
}
void TStructDeclarationList_Init(struct TStructDeclarationList* p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}

void TStructDeclarationList_Reserve(struct TStructDeclarationList* p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        struct TAnyStructDeclaration** pnew = p->pItems;
        pnew = (struct TAnyStructDeclaration**)Realloc(pnew, n * sizeof(struct TAnyStructDeclaration*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}


void TStructDeclarationList_PushBack(struct TStructDeclarationList* p, struct TAnyStructDeclaration* pItem) /*@default*/
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

void TBlockItemList_Init(struct TBlockItemList* p) /*@default*/
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}

void TBlockItemList_Destroy(struct TBlockItemList* p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        TBlockItem_Delete(p->pItems[i]);
    }
    Free((void*)p->pItems);
}
void TBlockItemList_Reserve(struct TBlockItemList* p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        struct TBlockItem** pnew = p->pItems;
        pnew = (struct TBlockItem**)Realloc(pnew, n * sizeof(struct TBlockItem*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}
void TBlockItemList_PushBack(struct TBlockItemList* p, struct TBlockItem* pItem)/*@default*/
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

struct TCompoundStatement* TCompoundStatement_Create() /*@default*/
{
    struct TCompoundStatement* p = (struct TCompoundStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TCompoundStatement_ID;
        TBlockItemList_Init(&p->BlockItemList);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}


void TCompoundStatement_Delete(struct TCompoundStatement* p) /*@default*/
{
    if (p != NULL)
    {
        TBlockItemList_Destroy(&p->BlockItemList);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}

struct TLabeledStatement* TLabeledStatement_Create(void) /*@default*/
{
    struct TLabeledStatement* p = (struct TLabeledStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TLabeledStatement_ID;
        p->pStatementOpt = NULL;
        p->pExpression = NULL;
        p->Identifier = NULL;
        p->token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}

void TLabeledStatement_Delete(struct TLabeledStatement* p)/*@default*/
{
    if (p != NULL)
    {
        TStatement_Delete(p->pStatementOpt);
        TExpression_Delete(p->pExpression);
        Free((void*)p->Identifier);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}
struct TForStatement* TForStatement_Create(void)/*@default*/
{
    struct TForStatement* p = (struct TForStatement*) Malloc(sizeof * p);
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

void TForStatement_Delete(struct TForStatement* p)/*@default*/
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

struct TWhileStatement* TWhileStatement_Create(void) /*@default*/
{
    struct TWhileStatement* p = (struct TWhileStatement*) Malloc(sizeof * p);
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

void TWhileStatement_Delete(struct TWhileStatement* p)/*@default*/
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

struct TDoStatement* TDoStatement_Create(void) /*@default*/
{
    struct TDoStatement* p = (struct TDoStatement*) Malloc(sizeof * p);
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

void TDoStatement_Delete(struct TDoStatement* p) /*@default*/
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


struct TExpressionStatement* TExpressionStatement_Create(void) /*@default*/
{
    struct TExpressionStatement* p = (struct TExpressionStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TExpressionStatement_ID;
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}

void TExpressionStatement_Delete(struct TExpressionStatement* p)/*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}

struct TJumpStatement* TJumpStatement_Create(void) /*@default*/
{
    struct TJumpStatement* p = (struct TJumpStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TJumpStatement_ID;
        p->token = TK_NONE;
        p->Identifier = NULL;
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}

void TJumpStatement_Delete(struct TJumpStatement* p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->Identifier);
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}




struct TAsmStatement* TAsmStatement_Create(void) /*@default*/
{
    struct TAsmStatement* p = (struct TAsmStatement*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TAsmStatement_ID;
        TScannerItemList_Init(&p->ClueList);
    }
    return p;
}

void TAsmStatement_Delete(struct TAsmStatement* p) /*@default*/
{
    if (p != NULL)
    {
        TScannerItemList_Destroy(&p->ClueList);
        Free((void*)p);
    }
}

struct TSwitchStatement* TSwitchStatement_Create(void) /*@default*/
{
    struct TSwitchStatement* p = (struct TSwitchStatement*) Malloc(sizeof * p);
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

void TSwitchStatement_Delete(struct TSwitchStatement* p) /*@default*/
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


struct TIfStatement* TIfStatement_Create(void) /*@default*/
{
    struct TIfStatement* p = (struct TIfStatement*) Malloc(sizeof * p);
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

void TIfStatement_Delete(struct TIfStatement* p) /*@default*/
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

void TStatement_Delete(struct TStatement* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TForStatement_ID:
                    TForStatement_Delete((struct TForStatement*)p);
                break;
                case TJumpStatement_ID:
                    TJumpStatement_Delete((struct TJumpStatement*)p);
                break;
                case TExpressionStatement_ID:
                    TExpressionStatement_Delete((struct TExpressionStatement*)p);
                break;
                case TIfStatement_ID:
                    TIfStatement_Delete((struct TIfStatement*)p);
                break;
                case TWhileStatement_ID:
                    TWhileStatement_Delete((struct TWhileStatement*)p);
                break;
                case TSwitchStatement_ID:
                    TSwitchStatement_Delete((struct TSwitchStatement*)p);
                break;
                case TAsmStatement_ID:
                    TAsmStatement_Delete((struct TAsmStatement*)p);
                break;
                case TDoStatement_ID:
                    TDoStatement_Delete((struct TDoStatement*)p);
                break;
                case TLabeledStatement_ID:
                    TLabeledStatement_Delete((struct TLabeledStatement*)p);
                break;
                case TCompoundStatement_ID:
                    TCompoundStatement_Delete((struct TCompoundStatement*)p);
                break;
                default:
                break;
            }
    }
}



void TBlockItem_Delete(struct TBlockItem* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TForStatement_ID:
                    TForStatement_Delete((struct TForStatement*)p);
                break;
                case TJumpStatement_ID:
                    TJumpStatement_Delete((struct TJumpStatement*)p);
                break;
                case TExpressionStatement_ID:
                    TExpressionStatement_Delete((struct TExpressionStatement*)p);
                break;
                case TDeclaration_ID:
                    TDeclaration_Delete((struct TDeclaration*)p);
                break;
                case TIfStatement_ID:
                    TIfStatement_Delete((struct TIfStatement*)p);
                break;
                case TWhileStatement_ID:
                    TWhileStatement_Delete((struct TWhileStatement*)p);
                break;
                case TSwitchStatement_ID:
                    TSwitchStatement_Delete((struct TSwitchStatement*)p);
                break;
                case TAsmStatement_ID:
                    TAsmStatement_Delete((struct TAsmStatement*)p);
                break;
                case TDoStatement_ID:
                    TDoStatement_Delete((struct TDoStatement*)p);
                break;
                case TLabeledStatement_ID:
                    TLabeledStatement_Delete((struct TLabeledStatement*)p);
                break;
                case TCompoundStatement_ID:
                    TCompoundStatement_Delete((struct TCompoundStatement*)p);
                break;
                default:
                break;
            }
    }
}

void TPrimaryExpressionValue_Init(struct TPrimaryExpressionValue* p) /*@default*/
{
    p->Type = TPrimaryExpressionValue_ID;
    p->token = TK_NONE;
    p->lexeme = NULL;
    p->pExpressionOpt = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
}

void TPrimaryExpressionValue_Destroy(struct TPrimaryExpressionValue* p) /*@default*/
{
    Free((void*)p->lexeme);
    TExpression_Delete(p->pExpressionOpt);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

struct TPrimaryExpressionValue* TPrimaryExpressionValue_Create() /*@default*/
{
    struct TPrimaryExpressionValue *p = (struct TPrimaryExpressionValue *) Malloc(sizeof * p);
    if (p != NULL)
    {
        TPrimaryExpressionValue_Init(p);
    }
    return p;
}

void TPrimaryExpressionValue_Delete(struct TPrimaryExpressionValue* p) /*@default*/
{
    if (p != NULL)
    {
        TPrimaryExpressionValue_Destroy(p);
        Free((void*)p);
    }
}

struct TPrimaryExpressionLambda* TPrimaryExpressionLambda_Create() /*@default*/
{
    struct TPrimaryExpressionLambda* p = (struct TPrimaryExpressionLambda*) Malloc(sizeof * p);
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

void TPrimaryExpressionLambda_Delete(struct TPrimaryExpressionLambda* p) /*@default*/
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

void TPostfixExpressionCore_Delete(struct TPostfixExpressionCore* p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->lexeme);
        TExpression_Delete(p->pExpressionLeft);
        TExpression_Delete(p->pExpressionRight);
        TPostfixExpressionCore_Delete(p->pNext);
        TInitializerList_Destroy(&p->InitializerList);
        Free((void*)p->Identifier);
        TTypeName_Delete(p->pTypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        TScannerItemList_Destroy(&p->ClueList4);
        Free((void*)p);
    }
}

struct TBinaryExpression* TBinaryExpression_Create(void) /*@default*/
{
    struct TBinaryExpression* p = (struct TBinaryExpression*) Malloc(sizeof * p);
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

void TBinaryExpression_Delete(struct TBinaryExpression* p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpressionLeft);
        TExpression_Delete(p->pExpressionRight);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}


void TUnaryExpressionOperator_Delete(struct TUnaryExpressionOperator* p) /*@default*/
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


void TCastExpressionType_Delete(struct TCastExpressionType* p) /*@default*/
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

struct TTernaryExpression* TTernaryExpression_Create(void) /*@default*/
{
    struct TTernaryExpression* p = (struct TTernaryExpression*) Malloc(sizeof * p);
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

void TTernaryExpression_Delete(struct TTernaryExpression* p) /*@default*/
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

void TPrimaryExpressionLiteralItem_Delete(struct TPrimaryExpressionLiteralItem* p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->lexeme);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}
struct TPrimaryExpressionLiteralItem* TPrimaryExpressionLiteralItem_Create() /*@default*/
{
    struct TPrimaryExpressionLiteralItem* p = (struct TPrimaryExpressionLiteralItem*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        p->lexeme = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}

struct TPrimaryExpressionLiteral* TPrimaryExpressionLiteral_Create() /*@default*/
{
    struct TPrimaryExpressionLiteral* p = (struct TPrimaryExpressionLiteral*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TPrimaryExpressionLiteral_ID;
        TPrimaryExpressionLiteralItemList_Init(&p->List);
    }
    return p;
}


void TPrimaryExpressionLiteral_Delete(struct TPrimaryExpressionLiteral* p) /*@default*/
{
    if (p != NULL)
    {
        TPrimaryExpressionLiteralItemList_Destroy(&p->List);
        Free((void*)p);
    }
}

void TExpression_Delete(struct TExpression* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TBinaryExpression_ID:
                    TBinaryExpression_Delete((struct TBinaryExpression*)p);
                break;
                case TPrimaryExpressionLambda_ID:
                    TPrimaryExpressionLambda_Delete((struct TPrimaryExpressionLambda*)p);
                break;
                case TUnaryExpressionOperator_ID:
                    TUnaryExpressionOperator_Delete((struct TUnaryExpressionOperator*)p);
                break;
                case TCastExpressionType_ID:
                    TCastExpressionType_Delete((struct TCastExpressionType*)p);
                break;
                case TPrimaryExpressionValue_ID:
                    TPrimaryExpressionValue_Delete((struct TPrimaryExpressionValue*)p);
                break;
                case TPostfixExpressionCore_ID:
                    TPostfixExpressionCore_Delete((struct TPostfixExpressionCore*)p);
                break;
                case TPrimaryExpressionLiteral_ID:
                    TPrimaryExpressionLiteral_Delete((struct TPrimaryExpressionLiteral*)p);
                break;
                case TTernaryExpression_ID:
                    TTernaryExpression_Delete((struct TTernaryExpression*)p);
                break;
                default:
                break;
            }
    }
}


struct TEofDeclaration* TEofDeclaration_Create() /*@default*/
{
    struct TEofDeclaration* p = (struct TEofDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TEofDeclaration_ID;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}


void TEofDeclaration_Delete(struct TEofDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}



struct TStaticAssertDeclaration* TStaticAssertDeclaration_Create() /*@default*/
{
    struct TStaticAssertDeclaration* p = (struct TStaticAssertDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStaticAssertDeclaration_ID;
        p->pConstantExpression = NULL;
        p->Text = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
        TScannerItemList_Init(&p->ClueList4);
        TScannerItemList_Init(&p->ClueList5);
    }
    return p;
}

void TStaticAssertDeclaration_Delete(struct TStaticAssertDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
        TExpression_Delete(p->pConstantExpression);
        Free((void*)p->Text);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        TScannerItemList_Destroy(&p->ClueList4);
        TScannerItemList_Destroy(&p->ClueList5);
        Free((void*)p);
    }
}

struct TEnumerator* TEnumerator_Create(void) /*@default*/
{
    struct TEnumerator* p = (struct TEnumerator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        p->Name = NULL;
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        p->bHasComma = false;
    }
    return p;
}

void TEnumerator_Delete(struct TEnumerator* p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->Name);
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

void TEnumeratorList_Init(struct TEnumeratorList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TEnumeratorList_Destroy(struct TEnumeratorList* p)
{
    struct TEnumerator* pCurrent = p->pHead;
    while (pCurrent)
    {
        struct TEnumerator* pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TEnumerator_Delete(pItem);
    }
}

struct TEnumSpecifier* TEnumSpecifier_Create(void) /*@default*/
{
    struct TEnumSpecifier* p = (struct TEnumSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TEnumSpecifier_ID;
        p->Tag = NULL;
        TEnumeratorList_Init(&p->EnumeratorList);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}

void TEnumSpecifier_Delete(struct TEnumSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->Tag);
        TEnumeratorList_Destroy(&p->EnumeratorList);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        Free((void*)p);
    }
}

bool TEnumSpecifier_CompareTagName(struct TEnumSpecifier* p1, struct TEnumSpecifier* p2)
{
    bool result = false;

    if (p1->Tag && p2->Tag && strcmp(p1->Tag, p2->Tag) == 0)
    {
        result = true;
    }
    return result;
}

struct TUnionSetItem* TUnionSetItem_Create() /*@default*/
{
    struct TUnionSetItem* p = (struct TUnionSetItem*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        p->Token = TK_NONE;
        p->TokenFollow = TK_NONE;
        p->Name = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
    }
    return p;
}
void TUnionSetItem_Delete(struct TUnionSetItem* p) /*@default*/
{
    if (p != NULL)
    {
        Free((void*)p->Name);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        Free((void*)p);
    }
}

void TUnionSet_Init(struct TUnionSet* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
}

void TUnionSet_Destroy(struct TUnionSet* p)
{
    struct TUnionSetItem* pCurrent = p->pHead;
    while (pCurrent)
    {
        struct TUnionSetItem* pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TUnionSetItem_Delete(pItem);
    }
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);

}


void TUnionSet_PushBack(struct TUnionSet* pList, struct TUnionSetItem* pItem)
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




struct TStructUnionSpecifier* TStructUnionSpecifier_Create() /*@default*/
{
    struct TStructUnionSpecifier* p = (struct TStructUnionSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStructUnionSpecifier_ID;
        TStructDeclarationList_Init(&p->StructDeclarationList);
        p->Tag = NULL;
        p->Token = TK_NONE;
        TUnionSet_Init(&p->UnionSet);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
    }
    return p;
}
void TStructUnionSpecifier_Delete(struct TStructUnionSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        TStructDeclarationList_Destroy(&p->StructDeclarationList);
        Free((void*)p->Tag);
        TUnionSet_Destroy(&p->UnionSet);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        Free((void*)p);
    }
}

bool TStructUnionSpecifier_CompareTagName(struct TStructUnionSpecifier* p1, struct TStructUnionSpecifier* p2)
{
    bool result = false;
    if (p1->Token == p2->Token)
    {
        if (p1->Tag && p2->Tag && strcmp(p1->Tag, p2->Tag) == 0)
        {
            result = true;
        }
    }
    return result;
}

int StrCmpNull(char const* s1, char const* s2)
{
    if (s1 == 0)
        return -1;
    return strcmp(s1, s2);
}


struct TSingleTypeSpecifier* TSingleTypeSpecifier_Create(void) /*@default*/
{
    struct TSingleTypeSpecifier* p = (struct TSingleTypeSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TSingleTypeSpecifier_ID;
        p->Token2 = TK_NONE;
        p->TypedefName = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TSingleTypeSpecifier_Destroy(struct TSingleTypeSpecifier* p) /*@default*/
{
    Free((void*)p->TypedefName);
    TScannerItemList_Destroy(&p->ClueList0);
}
void TSingleTypeSpecifier_Delete(struct TSingleTypeSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        TSingleTypeSpecifier_Destroy(p);
        Free((void*)p);
    }
}

bool TSingleTypeSpecifier_Compare(struct TSingleTypeSpecifier* p1, struct TSingleTypeSpecifier* p2)
{
    bool result = false;
    if (p1->Token2 == p2->Token2)
    {
        if (p1->TypedefName && p2->TypedefName &&
            strcmp(p1->TypedefName, p2->TypedefName) == 0)
        {
            result = true;
        }
    }
    return result;
}

const char* TSingleTypeSpecifier_GetTypedefName(struct TSingleTypeSpecifier* p)
{
    const char* result = NULL;
    if (p->Token2 == TK_IDENTIFIER)
    {
        result = p->TypedefName;
    }
    return result;
}

bool TTypeSpecifier_Compare(struct TTypeSpecifier* p1, struct TTypeSpecifier* p2)
{
    bool result = false;

    if (p1->Type != p2->Type)
    {
        return false;
    }

    switch (p1->Type)
    {
        case TStructUnionSpecifier_ID:
            result = TStructUnionSpecifier_CompareTagName((struct TStructUnionSpecifier*)p1, (struct TStructUnionSpecifier*)p2);
            break;
        case TAtomicTypeSpecifier_ID:
            result = TAtomicTypeSpecifier_Compare((struct TAtomicTypeSpecifier*)p1, (struct TAtomicTypeSpecifier*)p2);
            break;
        case TSingleTypeSpecifier_ID:
            result = TSingleTypeSpecifier_Compare((struct TSingleTypeSpecifier*)p1, (struct TSingleTypeSpecifier*)p2);
            break;
        case TEnumSpecifier_ID:
            result = TEnumSpecifier_CompareTagName((struct TEnumSpecifier*)p1, (struct TEnumSpecifier*)p2);
            break;
        default:
            break;
    }
    return result;
}

void TTypeSpecifier_Delete(struct TTypeSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TStructUnionSpecifier_ID:
                    TStructUnionSpecifier_Delete((struct TStructUnionSpecifier*)p);
                break;
                case TAtomicTypeSpecifier_ID:
                    TAtomicTypeSpecifier_Delete((struct TAtomicTypeSpecifier*)p);
                break;
                case TSingleTypeSpecifier_ID:
                    TSingleTypeSpecifier_Delete((struct TSingleTypeSpecifier*)p);
                break;
                case TEnumSpecifier_ID:
                    TEnumSpecifier_Delete((struct TEnumSpecifier*)p);
                break;
                default:
                break;
            }
    }
}


void TDeclarator_Init(struct TDeclarator* p) /*@default*/
{
    p->PointerList.pHead = NULL;
    p->PointerList.pTail = NULL;
    p->pDirectDeclarator = NULL;
    TScannerItemList_Init(&p->ClueList);
}

struct TDeclarator* TDeclarator_Create() /*@default*/
{
    struct TDeclarator *p = (struct TDeclarator *) Malloc(sizeof * p);
    if (p != NULL)
    {
        TDeclarator_Init(p);
    }
    return p;
}

void TDeclarator_Destroy(struct TDeclarator* p) /*@default*/
{
    TPointerList_Destroy(&p->PointerList);
    TDirectDeclarator_Delete(p->pDirectDeclarator);
    TScannerItemList_Destroy(&p->ClueList);
}

void TDeclarator_Swap(struct TDeclarator* a, struct TDeclarator* b)
{
    struct TDeclarator t = *a;
    *a = *b;
    *b = t;
}

void TDeclarator_Delete(struct TDeclarator* p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarator_Destroy(p);
        Free((void*)p);
    }
}

struct TInitDeclarator* TInitDeclarator_Create() /*@default*/
{
    struct TInitDeclarator* p = (struct TInitDeclarator*) Malloc(sizeof * p);
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

void TInitDeclarator_Destroy(struct TInitDeclarator* p) /*@default*/
{
    TDeclarator_Delete(p->pDeclarator);
    TInitializer_Delete(p->pInitializer);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

void TInitDeclarator_Delete(struct TInitDeclarator* p) /*@default*/
{
    if (p != NULL)
    {
        TInitDeclarator_Destroy(p);
        Free((void*)p);
    }
}

void TParameterTypeList_Init(struct TParameterTypeList* p) /*@default*/
{
    TParameterList_Init(&p->ParameterList);
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    p->bVariadicArgs = false;
}
void TParameterTypeList_Destroy(struct TParameterTypeList* p) /*@default*/
{
    TParameterList_Destroy(&p->ParameterList);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

struct TParameterTypeList* TParameterTypeList_Create() /*@default*/
{
    struct TParameterTypeList *p = (struct TParameterTypeList *) Malloc(sizeof * p);
    if (p != NULL)
    {
        TParameterTypeList_Init(p);
    }
    return p;
}
void TParameterTypeList_Delete(struct TParameterTypeList* p) /*@default*/
{
    if (p != NULL)
    {
        TParameterTypeList_Destroy(p);
        Free((void*)p);
    }
}

const char* TParameterTypeList_GetFirstParameterName(struct TParameterTypeList* p)
{
    const char* name = "";
    if (p->ParameterList.pHead)
    {
        name = TDeclarator_GetName(&p->ParameterList.pHead->Declarator);
    }
    return name;
}

bool TParameterTypeList_HasNamedArgs(struct TParameterTypeList* p)
{
    bool result = false;
    if (p != NULL)
    {
        ForEachListItem(struct TParameter, pParameter, &p->ParameterList)
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



void TParameterTypeList_GetArgsString(struct TParameterTypeList* p, StrBuilder * sb)
{
    if (p != NULL)
    {
        int index = 0;
        ForEachListItem(struct TParameter, pParameter, &p->ParameterList)
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

struct TParameter* TParameterTypeList_GetParameterByIndex(struct TParameterTypeList* p, int index)
{
    struct TParameter* pParameterResult = NULL;


    if (index == 0)
    {
        //A funcao TParameterTypeList_GetParameterByIndex deve retornar
        //null caso o primeiro parametro seja void. void Function(void)
        //
        if (p->ParameterList.pHead)
        {
            if (p->ParameterList.pHead->Specifiers.Size == 1 &&
                p->ParameterList.pHead->Specifiers.pData[0]->Type == TSingleTypeSpecifier_ID)
            {
                struct TSingleTypeSpecifier* pSingleTypeSpecifier =
                    p->ParameterList.pHead->Specifiers.pData[0];
                if (pSingleTypeSpecifier)
                {
                    if (pSingleTypeSpecifier->Token2 == TK_VOID)
                    {
                        if (p->ParameterList.pHead->Declarator.PointerList.pHead == 0)
                        {
                            return NULL;
                        }
                    }
                }
            }
        }
    }

    int indexLocal = 0;

    ForEachListItem(struct TParameter, pParameter, &p->ParameterList)
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

struct TParameter* TParameterTypeList_FindParameterByName(struct TParameterTypeList* p, const char* name)
{
    struct TParameter* pParameterResult = NULL;
    if (name)
    {
        ForEachListItem(struct TParameter, pParameter, &p->ParameterList)
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

const char* TParameterTypeList_GetSecondParameterName(struct TParameterTypeList* p)
{
    const char* name = "";
    if (p->ParameterList.pHead &&
        p->ParameterList.pHead->pNext)
    {
        name = TDeclarator_GetName(&p->ParameterList.pHead->pNext->Declarator);
    }
    return name;
}

void TDirectDeclarator_Destroy(struct TDirectDeclarator* p) /*@default*/
{
    Free((void*)p->Identifier);
    TDeclarator_Delete(p->pDeclarator);
    TDirectDeclarator_Delete(p->pDirectDeclarator);
    TParameterTypeList_Destroy(&p->Parameters);
    TExpression_Delete(p->pExpression);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    TScannerItemList_Destroy(&p->ClueList3);
}

void TDirectDeclarator_Delete(struct TDirectDeclarator* p) /*@default*/
{
    if (p != NULL)
    {
        TDirectDeclarator_Destroy(p);
        Free((void*)p);
    }
}

struct TDeclarationSpecifier* TSpecifierQualifierList_GetMainSpecifier(struct TSpecifierQualifierList* p)
{
    struct TDeclarationSpecifier* pSpecifier = NULL;
    for (int i = 0; i < p->Size; i++)
    {
        struct TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
        if (pSpecifierQualifier->Type == TSingleTypeSpecifier_ID ||
            pSpecifierQualifier->Type == TStructUnionSpecifier_ID ||
            pSpecifierQualifier->Type == TEnumSpecifier_ID)
        {
            //ATENCAO
            pSpecifier = (struct TDeclarationSpecifier*)pSpecifierQualifier;
            break;
        }
    }
    return pSpecifier;
}

const char* TSpecifierQualifierList_GetTypedefName(struct TSpecifierQualifierList* p)
{
    const char* typedefName = NULL;

    for (int i = 0; i < p->Size; i++)
    {
        struct TSpecifierQualifier* pSpecifierQualifier = p->pData[i];


        struct TSingleTypeSpecifier* pSingleTypeSpecifier =
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

bool TSpecifierQualifierList_Compare(struct TSpecifierQualifierList* p1, struct TSpecifierQualifierList* p2)
{
    if (p1->Size != p2->Size)
    {
        return false;
    }

    bool bResult = false;
    for (int i = 0; i < p1->Size; i++)
    {
        if (p1->pData[i]->Type == p2->pData[i]->Type)
        {
            switch (p1->pData[i]->Type)
            {

                case TSingleTypeSpecifier_ID:
                    if (!TSingleTypeSpecifier_Compare((struct TSingleTypeSpecifier*)p1->pData[i],
                        (struct TSingleTypeSpecifier*)p2->pData[i]))
                    {
                        return false;
                    }
                break;

                case TStorageSpecifier_ID:
                    if (!TStorageSpecifier_Compare((struct TStorageSpecifier*)p1->pData[i],
                        (struct TStorageSpecifier*)p2->pData[i]))
                    {
                        return false;
                    }
                break;
                case TTypeQualifier_ID:
                    if (!TTypeQualifier_Compare((struct TTypeQualifier*)p1->pData[i],
                        (struct TTypeQualifier*)p2->pData[i]))
                    {
                        return false;
                    }
                break;
                case TFunctionSpecifier_ID:
                    if (!TFunctionSpecifier_Compare((struct TFunctionSpecifier*)p1->pData[i],
                        (struct TFunctionSpecifier*)p2->pData[i]))
                    {
                        return false;
                    }
                break;


                case TStructUnionSpecifier_ID:
                    if (!TStructUnionSpecifier_CompareTagName((struct TStructUnionSpecifier*)p1->pData[i],
                        (struct TStructUnionSpecifier*)p2->pData[i]))
                    {
                        return false;
                    }
                break;

                case TEnumSpecifier_ID:
                    if (!TEnumSpecifier_CompareTagName((struct TEnumSpecifier*)p1->pData[i],
                        (struct TEnumSpecifier*)p2->pData[i]))
                    {
                        return false;
                    }
                break;

                default:
                    //assert(false);
                    break;
            }
        }
        else
        {
            return false;
        }
    }

    return true;
}

bool TSpecifierQualifierList_IsTypedefQualifier(struct TSpecifierQualifierList* p)
{
    bool bResult = false;
    for (int i = 0; i < p->Size; i++)
    {
        struct TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
        struct TStorageSpecifier* pStorageSpecifier =
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

bool TSpecifierQualifierList_IsChar(struct TSpecifierQualifierList* p)
{
    bool bResult = false;
    for (int i = 0; i < p->Size; i++)
    {
        struct TSpecifierQualifier* pSpecifierQualifier = p->pData[i];

        struct TSingleTypeSpecifier* pSingleTypeSpecifier =
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


bool TSpecifierQualifierList_IsAnyInteger(struct TSpecifierQualifierList* p)
{
    bool bResult = false;
    for (int i = 0; i < p->Size; i++)
    {
        struct TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
        struct TSingleTypeSpecifier* pSingleTypeSpecifier =
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


bool TSpecifierQualifierList_IsAnyFloat(struct TSpecifierQualifierList* p)
{
    bool bResult = false;
    for (int i = 0; i < p->Size; i++)
    {
        struct TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
        struct TSingleTypeSpecifier* pSingleTypeSpecifier =
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

bool TSpecifierQualifierList_IsBool(struct TSpecifierQualifierList* p)
{
    bool bResult = false;
    for (int i = 0; i < p->Size; i++)
    {
        struct TSpecifierQualifier* pSpecifierQualifier = p->pData[i];
        struct TSingleTypeSpecifier* pSingleTypeSpecifier =
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

const char* TDeclarator_GetName(struct TDeclarator* p)
{
    if (p == NULL)
    {
        return NULL;
    }
    struct TDirectDeclarator* pDirectDeclarator = p->pDirectDeclarator;
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

const char* TInitDeclarator_FindName(struct TInitDeclarator* p)
{
    //assert(p->pDeclarator != NULL);
    return TDeclarator_GetName(p->pDeclarator);
}



struct TAlignmentSpecifier* TAlignmentSpecifier_Create(void) /*@default*/
{
    struct TAlignmentSpecifier* p = (struct TAlignmentSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TAlignmentSpecifier_ID;
        p->TypeName = NULL;
    }
    return p;
}
void TAlignmentSpecifier_Destroy(struct TAlignmentSpecifier* p) /*@default*/
{
    Free((void*)p->TypeName);
}

void TAlignmentSpecifier_Delete(struct TAlignmentSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        TAlignmentSpecifier_Destroy(p);
        Free((void*)p);
    }
}


struct TStructDeclaration* TStructDeclaration_Create() /*@default*/
{
    struct TStructDeclaration* p = (struct TStructDeclaration*) Malloc(sizeof * p);
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


void TStructDeclaratorList_Destroy(struct TStructDeclaratorList* p)
{
    struct TInitDeclarator* pCurrent = p->pHead;
    while (pCurrent)
    {
        struct TInitDeclarator* pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TInitDeclarator_Delete(pItem);
    }
}

void TStructDeclaratorList_Init(struct TStructDeclaratorList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TStructDeclaratorList_Add(struct TStructDeclaratorList* pList, struct TInitDeclarator* pItem)
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

void TStructDeclaration_Destroy(struct TStructDeclaration* p) /*@default*/
{
    TSpecifierQualifierList_Destroy(&p->SpecifierQualifierList);
    TStructDeclaratorList_Destroy(&p->DeclaratorList);
    TScannerItemList_Destroy(&p->ClueList1);
}

void TStructDeclaration_Delete(struct TStructDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
        TStructDeclaration_Destroy(p);
        Free((void*)p);
    }
}


void TAnyStructDeclaration_Delete(struct TAnyStructDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TStaticAssertDeclaration_ID:
                    TStaticAssertDeclaration_Delete((struct TStaticAssertDeclaration*)p);
                break;
                case TStructDeclaration_ID:
                    TStructDeclaration_Delete((struct TStructDeclaration*)p);
                break;
                default:
                break;
            }
    }
}

bool TPointerList_IsAutoPointer(struct TPointerList* pPointerlist)
{
    bool bIsPointer = false;
    bool bIsAuto = false;
    if (pPointerlist)
    {
        bIsPointer = (pPointerlist->pHead != NULL);

        //ForEachListItem(struct TPointer, pItem, pPointerlist)
        struct TPointer* pItem = pPointerlist->pHead;
        //for (T * var = (list)->pHead; var != NULL; var = var->pNext)
        while (pItem)
        {
            for (int i = 0; i < pItem->Qualifier.Size; i++)
            {
                struct TTypeQualifier* pQualifier = pItem->Qualifier.Data[i];
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

void TPointerList_Destroy(struct TPointerList* p)
{
    struct TPointer* pCurrent = p->pHead;
    while (pCurrent)
    {
        struct TPointer* pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TPointer_Delete(pItem);
    }
}

struct TPointer* TPointer_Create(void) /*@default*/
{
    struct TPointer* p = (struct TPointer*) Malloc(sizeof * p);
    if (p != NULL)
    {
        TTypeQualifierList_Init(&p->Qualifier);
        p->pNext = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TPointer_Destroy(struct TPointer* p) /*@default*/
{
    TTypeQualifierList_Destroy(&p->Qualifier);
    TScannerItemList_Destroy(&p->ClueList0);
}

void TPointerList_PushBack(struct TPointerList* pList, struct TPointer* pItem)
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

void TPointer_Delete(struct TPointer* p) /*@default*/
{
    if (p != NULL)
    {
        TPointer_Destroy(p);
        Free((void*)p);
    }
}

void TPointerList_Printf(struct TPointerList* p)
{
    ForEachListItem(struct TPointer, pItem, p)
    {
        printf("*");

        for (int i = 0; i < pItem->Qualifier.Size; i++)
        {
            if (i > 0)
                printf(" ");
            struct TTypeQualifier* pQualifier = pItem->Qualifier.Data[i];
            printf("%s", TokenToString(pQualifier->Token));

            if (IsSizeToken(pQualifier->Token))
            {
                printf("(%s)", pQualifier->SizeIdentifier);
            }
        }
    }
    printf("\n");
}

void TPointerList_Swap(struct TPointerList* a, struct TPointerList* b)
{
    struct TPointerList t = *a;
    *a = *b;
    *b = t;
}

void TPointer_Copy(struct TPointer* dest, struct TPointer* src)
{
    TTypeQualifierList_Copy(&dest->Qualifier, &src->Qualifier);
}

bool TPointerList_IsPointer(struct TPointerList* pPointerlist)
{
    return pPointerlist->pHead != NULL;
}


const char* TPointerList_GetSize(struct TPointerList* pPointerlist)
{
    //Esta definicao esta estranha..tem que pegar o size de 1 cara so

    const char* pszResult = NULL;

    if (pPointerlist)
    {
        ForEachListItem(struct TPointer, pItem, pPointerlist)
        {
            for (int i = 0; i < pItem->Qualifier.Size; i++)
            {
                struct TTypeQualifier* pQualifier = pItem->Qualifier.Data[i];

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

bool TPointerList_IsPointerN(struct TPointerList* pPointerlist, int n)
{
    int k = 0;
    if (pPointerlist)
    {
        ForEachListItem(struct TPointer, pItem, pPointerlist)
        {

            k++;

        }
    }
    return k == n;
}

bool TPointerList_IsPointerToObject(struct TPointerList* pPointerlist)
{
    bool bResult = false;
    struct TPointer* pPointer = pPointerlist->pHead;
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

bool TPointerList_IsAutoPointerToObject(struct TPointerList* pPointerlist)
{
    //retorna true se tem 1 ponteiro qualificado auto
    bool bResult = false;
    struct TPointer* pPointer = pPointerlist->pHead;
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


bool TPointerList_IsAutoPointerSizeToObject(struct TPointerList* pPointerlist)
{
    bool bResult = false;
    struct TPointer* pPointer = pPointerlist->pHead;
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

bool TPointerList_IsAutoPointerToPointer(struct TPointerList* pPointerlist)
{
    bool bResult = false;
    struct TPointer* pPointer = pPointerlist->pHead;
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


bool TPointerList_IsAutoPointerToAutoPointer(struct TPointerList* pPointerlist)
{
    bool bResult = false;
    struct TPointer* pPointer = pPointerlist->pHead;
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
                    bResult = IsAutoToken(pPointer->Qualifier.Data[0]->Token) ||
                        IsAutoToken(pPointer->Qualifier.Data[1]->Token);
                }
            }
        }
    }

    return bResult;
}



void TTypeQualifierList_Destroy(struct TTypeQualifierList* p)  /*custom*/
{
    for (int i = 0; i < p->Size; i++)
    {
        TTypeQualifier_Delete(p->Data[i]);
    }
}


void TTypeQualifierList_Init(struct TTypeQualifierList* p)
{
    p->Data[0] = NULL;
    p->Size = 0;
}

void TTypeQualifierList_Copy(struct TTypeQualifierList* dest, struct TTypeQualifierList* src)
{
    TTypeQualifierList_Destroy(dest);
    TTypeQualifierList_Init(dest);

    for (int i = 0; i < src->Size; i++)
    {
        struct TTypeQualifier* pItem = TTypeQualifier_Create();
        TTypeQualifier_Copy(pItem, src->Data[i]);
        TTypeQualifierList_PushBack(dest, pItem);
    }
}

void TTypeQualifierList_PushBack(struct TTypeQualifierList* p, struct TTypeQualifier* pItem)
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

struct TTypeQualifier* TTypeQualifier_Create(void) /*@default*/
{
    struct TTypeQualifier* p = (struct TTypeQualifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TTypeQualifier_ID;
        p->SizeIdentifier = NULL;
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TTypeQualifier_Destroy(struct TTypeQualifier* p) /*@default*/
{
    Free((void*)p->SizeIdentifier);
    TScannerItemList_Destroy(&p->ClueList0);
}
void TTypeQualifier_Delete(struct TTypeQualifier* p) /*@default*/
{
    if (p != NULL)
    {
        TTypeQualifier_Destroy(p);
        Free((void*)p);
    }
}

void TTypeQualifier_Copy(struct TTypeQualifier* dest, struct TTypeQualifier* src)
{
    PTR_STRING_REPLACE(dest->SizeIdentifier, src->SizeIdentifier);
    dest->Token = src->Token;
    //dest->ClueList0 nao vamos copiar
    //dest->Type nao precisa copiar
}

bool TTypeQualifier_Compare(struct TTypeQualifier* p1, struct TTypeQualifier* p2)
{
    bool result = false;
    if (p1->Token == p2->Token)
    {
        if (p1->SizeIdentifier == p2->SizeIdentifier)
        {
            result = true;
        }
    }
    return result;
}

struct TStorageSpecifier* TStorageSpecifier_Create(void) /*@default*/
{
    struct TStorageSpecifier* p = (struct TStorageSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStorageSpecifier_ID;
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TStorageSpecifier_Destroy(struct TStorageSpecifier* p) /*@default*/
{
    TScannerItemList_Destroy(&p->ClueList0);
}
void TStorageSpecifier_Delete(struct TStorageSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        TStorageSpecifier_Destroy(p);
        Free((void*)p);
    }
}

bool TStorageSpecifier_Compare(struct TStorageSpecifier* p1, struct TStorageSpecifier* p2)
{
    bool result = false;
    if (p1->Token == p2->Token)
    {
        result = true;
    }
    return result;
}
void TAtomicTypeSpecifier_Delete(struct TAtomicTypeSpecifier* p) /*@default*/
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
bool TAtomicTypeSpecifier_Compare(struct TAtomicTypeSpecifier* p1, struct TAtomicTypeSpecifier* p2)
{
    //bool result = false;
    //if (p1->TypeName && p2->TypeName &&
      //  strcmp(p1->TypeName, p2->TypeName) == 0)
    //{
      //  result = true;
    //}
    //so eh usado em 1 context que nao faz diferenca hj
    assert(false);
    return true;// result;
}
void TSpecifierQualifierList_Destroy(struct TSpecifierQualifierList* pDeclarationSpecifiers) /*@default*/
{
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TSpecifierQualifier_Delete(pDeclarationSpecifiers->pData[i]);
    }
    Free((void*)pDeclarationSpecifiers->pData);
}


void TSpecifierQualifierList_Reserve(struct TSpecifierQualifierList* p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        struct TSpecifierQualifier** pnew = p->pData;
        pnew = (struct TSpecifierQualifier**)Realloc(pnew, n * sizeof(struct TSpecifierQualifier*));
        if (pnew)
        {
            p->pData = pnew;
            p->Capacity = n;
        }
    }
}

void TSpecifierQualifierList_PushBack(struct TSpecifierQualifierList* p, struct TSpecifierQualifier* pItem) /*@default*/
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




bool TSpecifierQualifierList_CanAdd(struct TSpecifierQualifierList* p, enum Tokens token, const char* lexeme)
{
    bool bResult = false;

    bool bStruct = false;
    bool bEnum = false;

    bool bTypeDef = false;
    bool bInt = false;
    for (int i = 0; i < p->Size; i++)
    {
        struct TSpecifierQualifier* pSpecifier = p->pData[i];
        switch (pSpecifier->Type)
        {
            case TSingleTypeSpecifier_ID:
            {     struct TSingleTypeSpecifier* pTSingleTypeSpecifier =
                (struct TSingleTypeSpecifier*)pSpecifier;
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

            case TStructUnionSpecifier_ID:
                bStruct = true;
            break;

            case TEnumSpecifier_ID:
                bEnum = true;
            break;

            case TStorageSpecifier_ID:

                break;
            case TTypeQualifier_ID:

                break;
            case TFunctionSpecifier_ID:

                break;
            case TAlignmentSpecifier_ID:

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


struct TDeclarationSpecifier* TDeclarationSpecifiers_GetMainSpecifier(struct TDeclarationSpecifiers* p, enum Type type)
{
    struct TDeclarationSpecifier* pSpecifier = NULL;
    for (int i = 0; i < p->Size; i++)
    {
        struct TDeclarationSpecifier* pSpecifierQualifier = p->pData[i];
        if (pSpecifierQualifier->Type == type)
        {
            //ATENCAO
            pSpecifier = (struct TDeclarationSpecifier*)pSpecifierQualifier;
            break;
        }
    }
    return pSpecifier;
}

bool TDeclarationSpecifiers_CanAddSpeficier(struct TDeclarationSpecifiers* pDeclarationSpecifiers,
                                            enum Tokens token,
                                            const char* lexeme)
{
    bool bResult = false;
    bool bStruct = false;
    bool bEnum = false;

    struct TStructUnionSpecifier* pTStructUnionSpecifier = NULL;
    struct TEnumSpecifier* pEnumSpecifier = NULL;
    bool bTypeDef = false;
    bool bOther = false;

    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        struct TDeclarationSpecifier* pSpecifier = pDeclarationSpecifiers->pData[i];

        switch (pSpecifier->Type)
        {
            case TSingleTypeSpecifier_ID:
            {     struct TSingleTypeSpecifier* pTSingleTypeSpecifier =
                (struct TSingleTypeSpecifier*)pSpecifier;
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

            case TStructUnionSpecifier_ID:
                bStruct = true;
            pTStructUnionSpecifier = (struct TStructUnionSpecifier*)pSpecifier;
            break;

            case TEnumSpecifier_ID:
                bEnum = true;
            pEnumSpecifier = (struct TEnumSpecifier*)pSpecifier;
            break;

            case TStorageSpecifier_ID:

                break;
            case TTypeQualifier_ID:

                break;
            case TFunctionSpecifier_ID:

                break;
            case TAlignmentSpecifier_ID:

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
            if (pTStructUnionSpecifier->Tag &&
                strcmp(pTStructUnionSpecifier->Tag, lexeme) == 0)
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
            if (pEnumSpecifier->Tag &&
                strcmp(pEnumSpecifier->Tag, lexeme) == 0)
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

struct TStructUnionSpecifier* TDeclarationSpecifiers_GetCompleteStructUnionSpecifier(struct SymbolMap* pSymbolMap,
    struct TDeclarationSpecifiers* pDeclarationSpecifiers)
{
    struct TStructUnionSpecifier* pStructUnionSpecifier = NULL;

    struct TDeclarationSpecifier* pFirstArgSpecifier =
        TDeclarationSpecifiers_GetMainSpecifier(pDeclarationSpecifiers, TStructUnionSpecifier_ID);

    if (pFirstArgSpecifier == NULL)
    {
        pFirstArgSpecifier = TDeclarationSpecifiers_GetMainSpecifier(pDeclarationSpecifiers, TSingleTypeSpecifier_ID);
    }

    if (pFirstArgSpecifier)
    {
        pStructUnionSpecifier =
            TDeclarationSpecifier_As_TStructUnionSpecifier(pFirstArgSpecifier);

        if (pStructUnionSpecifier && pStructUnionSpecifier->Tag && pStructUnionSpecifier->StructDeclarationList.Size == 0)
        {
            //procura declaracao completa
            pStructUnionSpecifier =
                SymbolMap_FindStructUnion(pSymbolMap, pStructUnionSpecifier->Tag);
        }
        else
        {
            struct TDeclarator declarator;
            TDeclarator_Init(&declarator);


            struct TSingleTypeSpecifier* pSingleTypeSpecifier =
                TDeclarationSpecifier_As_TSingleTypeSpecifier(pFirstArgSpecifier);
            if (pSingleTypeSpecifier)
            {
                if (pSingleTypeSpecifier->TypedefName)
                {
                    struct TDeclarationSpecifiers* p2 =
                        SymbolMap_FindTypedefTarget(pSymbolMap, pSingleTypeSpecifier->TypedefName, &declarator);

                    if (p2)
                    {
                        pStructUnionSpecifier =
                            TDeclarationSpecifiers_GetMainSpecifier(p2, TStructUnionSpecifier_ID);

                        if (pStructUnionSpecifier &&
                            pStructUnionSpecifier->StructDeclarationList.Size == 0 &&
                            pStructUnionSpecifier->Tag != NULL)
                        {
                            pStructUnionSpecifier =
                                SymbolMap_FindStructUnion(pSymbolMap, pStructUnionSpecifier->Tag);
                        }
                    }
                }

            }
        }
    }
    return pStructUnionSpecifier;
}

const char* TDeclarationSpecifiers_GetTypedefName(struct TDeclarationSpecifiers* pDeclarationSpecifiers)
{
    if (pDeclarationSpecifiers == NULL)
    {
        return NULL;
    }
    const char* typeName = NULL;


    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        struct TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];

        struct TSingleTypeSpecifier* pSingleTypeSpecifier =
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

void TSpecifierQualifier_Delete(struct TSpecifierQualifier* pItem) /*@default*/
{
    if (pItem != NULL)
    {
            switch (pItem->Type)
            {
                case TTypeQualifier_ID:
                    TTypeQualifier_Delete((struct TTypeQualifier*)pItem);
                break;
                case TStructUnionSpecifier_ID:
                    TStructUnionSpecifier_Delete((struct TStructUnionSpecifier*)pItem);
                break;
                case TAtomicTypeSpecifier_ID:
                    TAtomicTypeSpecifier_Delete((struct TAtomicTypeSpecifier*)pItem);
                break;
                case TSingleTypeSpecifier_ID:
                    TSingleTypeSpecifier_Delete((struct TSingleTypeSpecifier*)pItem);
                break;
                case TEnumSpecifier_ID:
                    TEnumSpecifier_Delete((struct TEnumSpecifier*)pItem);
                break;
                default:
                break;
            }
    }
}

void TDeclarationSpecifier_Delete(struct TDeclarationSpecifier* pItem) /*@default*/
{
    if (pItem != NULL)
    {
            switch (pItem->Type)
            {
                case TTypeQualifier_ID:
                    TTypeQualifier_Delete((struct TTypeQualifier*)pItem);
                break;
                case TStructUnionSpecifier_ID:
                    TStructUnionSpecifier_Delete((struct TStructUnionSpecifier*)pItem);
                break;
                case TStorageSpecifier_ID:
                    TStorageSpecifier_Delete((struct TStorageSpecifier*)pItem);
                break;
                case TAtomicTypeSpecifier_ID:
                    TAtomicTypeSpecifier_Delete((struct TAtomicTypeSpecifier*)pItem);
                break;
                case TSingleTypeSpecifier_ID:
                    TSingleTypeSpecifier_Delete((struct TSingleTypeSpecifier*)pItem);
                break;
                case TAlignmentSpecifier_ID:
                    TAlignmentSpecifier_Delete((struct TAlignmentSpecifier*)pItem);
                break;
                case TFunctionSpecifier_ID:
                    TFunctionSpecifier_Delete((struct TFunctionSpecifier*)pItem);
                break;
                case TEnumSpecifier_ID:
                    TEnumSpecifier_Delete((struct TEnumSpecifier*)pItem);
                break;
                default:
                break;
            }
    }
}

void TDeclarationSpecifiers_Init(struct TDeclarationSpecifiers* pDeclarationSpecifiers) /*@default*/
{
    pDeclarationSpecifiers->pData = NULL;
    pDeclarationSpecifiers->Size = 0;
    pDeclarationSpecifiers->Capacity = 0;
}

void TDeclarationSpecifiers_Destroy(struct TDeclarationSpecifiers* pDeclarationSpecifiers) /*@default*/
{
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TDeclarationSpecifier_Delete(pDeclarationSpecifiers->pData[i]);
    }
    Free((void*)pDeclarationSpecifiers->pData);
}


void TDeclarationSpecifiers_Reserve(struct TDeclarationSpecifiers* p, int n) /*@default*/
{
    if (n > p->Capacity)
    {
        struct TDeclarationSpecifier** pnew = p->pData;
        pnew = (struct TDeclarationSpecifier**)Realloc(pnew, n * sizeof(struct TDeclarationSpecifier*));
        if (pnew)
        {
            p->pData = pnew;
            p->Capacity = n;
        }
    }
}

void TDeclarationSpecifiers_PushBack(struct TDeclarationSpecifiers* p, struct TDeclarationSpecifier* pItem) /*@default*/
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


struct TDeclarator* TDeclaration_FindDeclarator(struct TDeclaration* p, const char* name)
{
    if (p == NULL)
    {
        return NULL;
    }
    struct TDeclarator* pResult = NULL;

    ForEachListItem(struct TInitDeclarator, pInitDeclarator, &p->InitDeclaratorList)
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

struct TFunctionSpecifier* TFunctionSpecifier_Create(void) /*@default*/
{
    struct TFunctionSpecifier* p = (struct TFunctionSpecifier*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TFunctionSpecifier_ID;
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TFunctionSpecifier_Destroy(struct TFunctionSpecifier* p) /*@default*/
{
    TScannerItemList_Destroy(&p->ClueList0);
}
void TFunctionSpecifier_Delete(struct TFunctionSpecifier* p) /*@default*/
{
    if (p != NULL)
    {
        TFunctionSpecifier_Destroy(p);
        Free((void*)p);
    }
}

bool TFunctionSpecifier_Compare(struct TFunctionSpecifier* p1, struct TFunctionSpecifier* p2)
{
    bool result = false;
    if (p1->Token == p2->Token)
    {
        result = true;
    }
    return result;
}



bool TDeclaration_Is_StructOrUnionDeclaration(struct TDeclaration* p)
{
    bool bIsStructOrUnion = false;
    for (int i = 0; i < p->Specifiers.Size; i++)
    {
        struct TDeclarationSpecifier* pItem = p->Specifiers.pData[i];
        if (TDeclarationSpecifier_As_TStructUnionSpecifier(pItem))
        {
            bIsStructOrUnion = true;
            break;
        }

    }
    return bIsStructOrUnion;
}

void TInitDeclaratorList_Init(struct TInitDeclaratorList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TInitDeclaratorList_Destroy(struct TInitDeclaratorList* p)
{
    struct TInitDeclarator* pCurrent = p->pHead;
    while (pCurrent)
    {
        struct TInitDeclarator* pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TInitDeclarator_Delete(pItem);
    }

}



void TDeclaration_Delete(struct TDeclaration* p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarationSpecifiers_Destroy(&p->Specifiers);
        TInitDeclaratorList_Destroy(&p->InitDeclaratorList);
        TCompoundStatement_Delete(p->pCompoundStatementOpt);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList00);
        TScannerItemList_Destroy(&p->ClueList001);
        Free((void*)p->FunctionTag);
        TScannerItemList_Destroy(&p->ClueList1);
        Free((void*)p);
    }
}
struct TDeclaration* TDeclaration_Create() /*@default*/
{
    struct TDeclaration* p = (struct TDeclaration*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TDeclaration_ID;
        TDeclarationSpecifiers_Init(&p->Specifiers);
        TInitDeclaratorList_Init(&p->InitDeclaratorList);
        p->pCompoundStatementOpt = NULL;
        p->FileIndex = 0;
        p->Line = 0;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList00);
        TScannerItemList_Init(&p->ClueList001);
        p->bDefault = false;
        p->FunctionTag = NULL;
        p->bAutoTag = false;
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}


void TParameter_Swap(struct TParameter* a, struct TParameter* b)
{
    struct TParameter temp = *a;
    *a = *b;
    *b = temp;
}

const char* TDeclarationSpecifier_GetTypedefName(struct TDeclarationSpecifiers* p)
{
    const char* typedefName = NULL;
    for (int i = 0; i < p->Size; i++)
    {
        struct TDeclarationSpecifier* pSpecifier = p->pData[i];
        struct TSingleTypeSpecifier* pSingleTypeSpecifier =
            TDeclarationSpecifier_As_TSingleTypeSpecifier(pSpecifier);
        if (pSingleTypeSpecifier &&
            pSingleTypeSpecifier->Token2 == TK_IDENTIFIER)
        {
            typedefName = pSingleTypeSpecifier->TypedefName;
        }
    }
    return typedefName;
}

const char* TParameter_GetName(struct TParameter* p)
{
    //F(void) neste caso nao tem nome
    return TDeclarator_GetName(&p->Declarator);
}

const char* TParameter_GetTypedefName(struct TParameter* p)
{
    return TDeclarationSpecifier_GetTypedefName(&p->Specifiers);
}

bool TDeclarator_IsDirectPointer(struct TDeclarator* p)
{
    int n = 0;
    ForEachListItem(struct TPointer, pPointer, &p->PointerList)
    {
        n++;
        if (n > 1)
        {
            break;
        }
    }
    return n == 1;
}

bool TParameter_IsDirectPointer(struct TParameter* p)
{
    return TDeclarator_IsDirectPointer(&p->Declarator);
}


struct TParameter* TParameter_Create() /*@default*/
{
    struct TParameter* p = (struct TParameter*) Malloc(sizeof * p);
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

void TParameter_Delete(struct TParameter* p) /*@default*/
{
    if (p != NULL)
    {
        TDeclarationSpecifiers_Destroy(&p->Specifiers);
        TDeclarator_Destroy(&p->Declarator);
        TScannerItemList_Destroy(&p->ClueList0);
        Free((void*)p);
    }
}

void TParameterList_Init(struct TParameterList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TParameterList_Destroy(struct TParameterList* p)
{
    struct TParameter* pCurrent = p->pHead;
    while (pCurrent)
    {
        struct TParameter* p = pCurrent;
        pCurrent = pCurrent->pNext;
        TParameter_Delete(p);
    }
}


bool TAnyDeclaration_Is_StructOrUnionDeclaration(struct TAnyDeclaration* pAnyDeclaration)
{
    struct TDeclaration* pDeclaration = TAnyDeclaration_As_TDeclaration(pAnyDeclaration);
    if (pDeclaration != NULL)
    {
        return TDeclaration_Is_StructOrUnionDeclaration(pDeclaration);
    }

    return false;
}

bool TDeclarationSpecifiers_IsStatic(struct TDeclarationSpecifiers* pDeclarationSpecifiers)
{
    bool bResult = false;
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        struct TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];
        switch (pItem->Type)
        {
            case TStorageSpecifier_ID:
            {
                struct TStorageSpecifier* pStorageSpecifier =
                    (struct TStorageSpecifier*)pItem;

                if (pStorageSpecifier->Token == TK_STATIC)
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

bool TDeclarationSpecifiers_IsTypedef(struct TDeclarationSpecifiers* pDeclarationSpecifiers)
{
    bool bResult = false;
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        struct TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];
        switch (pItem->Type)
        {
            case TStorageSpecifier_ID:
            {
                struct TStorageSpecifier* pStorageSpecifier =
                    (struct TStorageSpecifier*)pItem;

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

bool TAnyDeclaration_IsTypedef(struct TAnyDeclaration* pDeclaration)
{
    bool bResult = false;
    switch (pDeclaration->Type)
    {
        case TDeclaration_ID:
        {
            struct TDeclaration* p = (struct TDeclaration*)pDeclaration;
            bResult = TDeclarationSpecifiers_IsTypedef(&p->Specifiers);
        }
        break;
        default:
            //assert(false);
            break;
    }
    return bResult;
}

int TAnyDeclaration_GetFileIndex(struct TAnyDeclaration* pDeclaration)
{
    int result = -1;
    switch (pDeclaration->Type)
    {
        case TDeclaration_ID:
            result = ((struct TDeclaration*)pDeclaration)->FileIndex;
            break;
        case TStaticAssertDeclaration_ID:
            break;
        default:
            //assert(false);
            break;
    }
    return result;
}

void TAnyDeclaration_Delete(struct TAnyDeclaration* pDeclaration) /*@default*/
{
    if (pDeclaration != NULL)
    {
            switch (pDeclaration->Type)
            {
                case TGroupDeclaration_ID:
                    TGroupDeclaration_Delete((struct TGroupDeclaration*)pDeclaration);
                break;
                case TStaticAssertDeclaration_ID:
                    TStaticAssertDeclaration_Delete((struct TStaticAssertDeclaration*)pDeclaration);
                break;
                case TDeclaration_ID:
                    TDeclaration_Delete((struct TDeclaration*)pDeclaration);
                break;
                case TEofDeclaration_ID:
                    TEofDeclaration_Delete((struct TEofDeclaration*)pDeclaration);
                break;
                default:
                break;
            }
    }
}

void TDesignation_Destroy(struct TDesignation* pDesignation) /*@default*/
{
    TDesignatorList_Destroy(&pDesignation->DesignatorList);
    TScannerItemList_Destroy(&pDesignation->ClueList0);
}

struct TDesignator* TDesignator_Create(void) /*@default*/
{
    struct TDesignator* p = (struct TDesignator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Name = NULL;
        p->pExpression = NULL;
        p->pNext = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}
void TDesignator_Destroy(struct TDesignator* p) /*@default*/
{
    Free((void*)p->Name);
    TExpression_Delete(p->pExpression);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}
void TDesignator_Delete(struct TDesignator* p) /*@default*/
{
    if (p != NULL)
    {
        TDesignator_Destroy(p);
        Free((void*)p);
    }
}


struct TInitializerListType* TInitializerListType_Create(void) /*@default*/
{
    struct TInitializerListType* p = (struct TInitializerListType*) Malloc(sizeof * p);
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
void TInitializerListType_Destroy(struct TInitializerListType* p) /*@default*/
{
    TInitializerList_Destroy(&p->InitializerList);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
}
void TInitializerListType_Delete(struct TInitializerListType* p) /*@default*/
{
    if (p != NULL)
    {
        TInitializerListType_Destroy(p);
        Free((void*)p);
    }
}

void TInitializerList_Init(struct TInitializerList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TInitializerList_Destroy(struct TInitializerList* p)
{
    struct TInitializerListItem* pCurrent = p->pHead;
    while (pCurrent)
    {
        struct TInitializerListItem* p = pCurrent;
        pCurrent = pCurrent->pNext;
        TInitializerListItem_Delete(p);
    }

}

void TInitializer_Delete(struct TInitializer* p) /*@default*/
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TBinaryExpression_ID:
                    TBinaryExpression_Delete((struct TBinaryExpression*)p);
                break;
                case TPrimaryExpressionLambda_ID:
                    TPrimaryExpressionLambda_Delete((struct TPrimaryExpressionLambda*)p);
                break;
                case TUnaryExpressionOperator_ID:
                    TUnaryExpressionOperator_Delete((struct TUnaryExpressionOperator*)p);
                break;
                case TCastExpressionType_ID:
                    TCastExpressionType_Delete((struct TCastExpressionType*)p);
                break;
                case TInitializerListType_ID:
                    TInitializerListType_Delete((struct TInitializerListType*)p);
                break;
                case TPrimaryExpressionValue_ID:
                    TPrimaryExpressionValue_Delete((struct TPrimaryExpressionValue*)p);
                break;
                case TPostfixExpressionCore_ID:
                    TPostfixExpressionCore_Delete((struct TPostfixExpressionCore*)p);
                break;
                case TPrimaryExpressionLiteral_ID:
                    TPrimaryExpressionLiteral_Delete((struct TPrimaryExpressionLiteral*)p);
                break;
                case TTernaryExpression_ID:
                    TTernaryExpression_Delete((struct TTernaryExpression*)p);
                break;
                default:
                break;
            }
    }
}


void TDesignatorList_Init(struct TDesignatorList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TDesignatorList_Destroy(struct TDesignatorList* p)
{
    struct TDesignator* pCurrent = p->pHead;
    while (pCurrent)
    {
        struct TDesignator* p = pCurrent;
        pCurrent = pCurrent->pNext;
        TDesignator_Delete(p);
    }

}

void TDesignatorList_PushBack(struct TDesignatorList* pList, struct TDesignator* pItem)
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

void TInitializerListItem_Destroy(struct TInitializerListItem* p) /*@default*/
{
    TDesignatorList_Destroy(&p->DesignatorList);
    TInitializer_Delete(p->pInitializer);
    TScannerItemList_Destroy(&p->ClueList);
}

struct TInitializerListItem* TInitializerListItem_Create() /*@default*/
{
    struct TInitializerListItem* p = (struct TInitializerListItem*) Malloc(sizeof * p);
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
void TInitializerListItem_Delete(struct TInitializerListItem* p) /*@default*/
{
    if (p != NULL)
    {
        TInitializerListItem_Destroy(p);
        Free((void*)p);
    }
}




struct TDeclaration* SyntaxTree_FindDeclaration(struct SyntaxTree* p, const char* name)
{
    struct TTypePointer* pt = SymbolMap_Find(&p->GlobalScope, name);
    if (pt != NULL &&
        pt->Type == TDeclaration_ID)
    {
        return (struct TDeclaration*)pt;
    }
    return NULL;
    //return DeclarationsMap_FindDeclaration(&p->Symbols, name);
}

struct TDeclaration* SyntaxTree_FindFunctionDeclaration(struct SyntaxTree* p, const char* name)
{
    struct TTypePointer* pt = SymbolMap_Find(&p->GlobalScope, name);
    if (pt != NULL &&
        pt->Type == TDeclaration_ID)
    {
        return (struct TDeclaration*)pt;
    }
    return NULL;
}



//Retorna a declaracao final do tipo entrando em cada typedef. 
struct TDeclaration* SyntaxTree_GetFinalTypeDeclaration(struct SyntaxTree* p, const char* typeName)
{
    return SymbolMap_FindTypedefDeclarationTarget(&p->GlobalScope, typeName);
}


void SyntaxTree_Init(struct SyntaxTree* p) /*@default*/
{
    TDeclarations_Init(&p->Declarations);
    TFileArray_Init(&p->Files2);
    SymbolMap_Init(&p->GlobalScope);
    MacroMap_Init(&p->Defines);
}


void SyntaxTree_Destroy(struct SyntaxTree* p) /*@default*/
{
    TDeclarations_Destroy(&p->Declarations);
    TFileArray_Destroy(&p->Files2);
    SymbolMap_Destroy(&p->GlobalScope);
    MacroMap_Destroy(&p->Defines);
}



///////////////////////////////////////////

static bool TPostfixExpressionCore_CodePrint2(struct TPostfixExpressionCore* p,
                                              int* pResult)
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
bool EvaluateConstantExpression(struct TExpression* p, int* pResult)
{
    int result = -987654321;

    if (p == NULL)
    {
        return false;
    }
    bool b = false;

    switch (p->Type)
    {
        case TBinaryExpression_ID:
        {
            struct TBinaryExpression* pBinaryExpression =
                (struct TBinaryExpression*)p;

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

        case TTernaryExpression_ID:
        {
            int e1, e2, e3;
            b = EvaluateConstantExpression(((struct TTernaryExpression*)p)->pExpressionLeft, &e1);

            b = EvaluateConstantExpression(((struct TTernaryExpression*)p)->pExpressionMiddle, &e2);

            b = EvaluateConstantExpression(((struct TTernaryExpression*)p)->pExpressionRight, &e3);
            //assert(false);
        }
        break;

        case TPrimaryExpressionValue_ID:
        {
            struct TPrimaryExpressionValue* pPrimaryExpressionValue =
                (struct TPrimaryExpressionValue*)p;

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

        case TPostfixExpressionCore_ID:
        {
            struct TPostfixExpressionCore* pPostfixExpressionCore =
                (struct TPostfixExpressionCore*)p;
            b = TPostfixExpressionCore_CodePrint2(pPostfixExpressionCore, &result);
            //assert(false);
        }
        break;

        case TUnaryExpressionOperator_ID:
        {

            struct TUnaryExpressionOperator* pTUnaryExpressionOperator =
                (struct TUnaryExpressionOperator*)p;

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

        case TCastExpressionType_ID:
        {
            struct TCastExpressionType* pCastExpressionType =
                (struct TCastExpressionType*)p;


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



struct TDeclarationSpecifiers* TDeclaration_GetArgTypeSpecifier(struct TDeclaration* p, int index)
{
    struct TDeclarationSpecifiers* pResult = NULL;
    struct TParameterTypeList* pArguments = TDeclaration_GetFunctionArguments(p);
    int n = 0;
    ForEachListItem(struct TParameter, pItem, &pArguments->ParameterList)
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

struct TParameterTypeList* TDeclaration_GetFunctionArguments(struct TDeclaration* p)
{
    struct TParameterTypeList* pParameterTypeList = NULL;

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


const char* TDeclaration_FindFunctionTagName(struct TDeclaration* p, struct SymbolMap* pMap)
{
    if (p->FunctionTag)
        return p->FunctionTag;
    const char* funcName = TDeclaration_GetFunctionName(p);
    if (funcName)
    {
        struct SymbolMapItem* pBucket = SymbolMap_FindBucket(pMap, funcName);

        while (pBucket)
        {
            if (pBucket->pValue->Type == TDeclaration_ID &&
                strcmp(pBucket->Key, funcName) == 0)
            {
                struct TDeclaration* pDeclaration = (struct TDeclaration*)pBucket->pValue;
                if (pDeclaration->FunctionTag)
                    return pDeclaration->FunctionTag;
            }
            pBucket = pBucket->pNext;
        }
    }
    return NULL;
}

const char* TDeclaration_GetFunctionName(struct TDeclaration* p)
{
    if (p == NULL)
        return NULL;

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

struct TCompoundStatement* TDeclaration_Is_FunctionDefinition(struct TDeclaration* p)
{
    struct TCompoundStatement* pCompoundStatement = NULL;

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

struct TStructUnionSpecifier* TDeclarationSpecifiers_Find_StructUnionSpecifier(struct TDeclarationSpecifiers* p)
{
    struct TStructUnionSpecifier* pStructUnionSpecifier = NULL;

    for (int i = 0; i < p->Size; i++)
    {
        struct TDeclarationSpecifier* pDeclarationSpecifier = p->pData[i];

        pStructUnionSpecifier =
            TDeclarationSpecifier_As_TStructUnionSpecifier(pDeclarationSpecifier);
        if (pStructUnionSpecifier)
        {
            break;
        }
    }
    return pStructUnionSpecifier;
}

struct TStructUnionSpecifier* TParameter_Is_DirectPointerToStruct(struct SyntaxTree* program, struct TParameter* pParameter)
{
    struct TStructUnionSpecifier* pStructUnionSpecifier = NULL;
    if (TParameter_IsDirectPointer(pParameter))
    {
        const char* typedefName = TParameter_GetTypedefName(pParameter);
        if (typedefName != NULL)
        {
            struct TDeclaration* pArgType = SyntaxTree_FindDeclaration(program, TParameter_GetTypedefName(pParameter));
            if (pArgType)
            {
                pStructUnionSpecifier =
                    TDeclarationSpecifiers_Find_StructUnionSpecifier(&pArgType->Specifiers);
            }
        }
    }
    return pStructUnionSpecifier;
}

void TPrimaryExpressionLiteralItemList_Init(struct TPrimaryExpressionLiteralItemList* p) /*@default*/
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TPrimaryExpressionLiteralItemList_Destroy(struct TPrimaryExpressionLiteralItemList* p)
{
    struct TPrimaryExpressionLiteralItem* pCurrent = p->pHead;
    while (pCurrent)
    {
        struct TPrimaryExpressionLiteralItem* pItem = pCurrent;
        pCurrent = pCurrent->pNext;
        TPrimaryExpressionLiteralItem_Delete(pItem);
    }
}

void TPrimaryExpressionLiteralItemList_Add(struct TPrimaryExpressionLiteralItemList* pList, struct TPrimaryExpressionLiteralItem* pItem)
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

const char* TDeclaration_GetArgName(struct TDeclaration* p, int index)
{
    const char* argName = NULL;
    struct TParameterTypeList* pArguments = TDeclaration_GetFunctionArguments(p);
    int n = 0;
    ForEachListItem(struct TParameter, pItem, &pArguments->ParameterList)
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


int TDeclaration_GetNumberFuncArgs(struct TDeclaration* p)
{
    struct TParameterTypeList* pArguments = TDeclaration_GetFunctionArguments(p);
    int n = 0;
    ForEachListItem(struct TParameter, pItem, &pArguments->ParameterList)
    {
        n++;
    }
    return n;
}






struct TDirectDeclarator* TDirectDeclarator_Create() /*@default*/
{
    struct TDirectDeclarator* p = (struct TDirectDeclarator*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Identifier = NULL;
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


struct TTypeName* TTypeName_Create() /*@default*/
{
    struct TTypeName *p = (struct TTypeName *) Malloc(sizeof * p);
    if (p != NULL)
    {
        TTypeName_Init(p);
    }
    return p;
}


void TTypeName_Destroy(struct TTypeName* p) /*@default*/
{
    TSpecifierQualifierList_Destroy(&p->SpecifierQualifierList);
    TDeclarator_Destroy(&p->Declarator);
}

void TTypeName_Delete(struct TTypeName* p) /*@default*/
{
    if (p != NULL)
    {
        TTypeName_Destroy(p);
        Free((void*)p);
    }
}


struct TAtomicTypeSpecifier* TAtomicTypeSpecifier_Create() /*@default*/
{
    struct TAtomicTypeSpecifier* p = (struct TAtomicTypeSpecifier*) Malloc(sizeof * p);
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




struct TPostfixExpressionCore* TPostfixExpressionCore_Create() /*@default*/
{
    struct TPostfixExpressionCore* p = (struct TPostfixExpressionCore*) Malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TPostfixExpressionCore_ID;
        p->token = TK_NONE;
        p->lexeme = NULL;
        p->pExpressionLeft = NULL;
        p->pExpressionRight = NULL;
        p->pNext = NULL;
        TInitializerList_Init(&p->InitializerList);
        p->Identifier = NULL;
        p->pTypeName = NULL;
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
        TScannerItemList_Init(&p->ClueList2);
        TScannerItemList_Init(&p->ClueList3);
        TScannerItemList_Init(&p->ClueList4);
    }
    return p;
}

struct TCastExpressionType* TCastExpressionType_Create() /*@default*/
{
    struct TCastExpressionType* p = (struct TCastExpressionType*) Malloc(sizeof * p);
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


struct TUnaryExpressionOperator* TUnaryExpressionOperator_Create() /*@default*/
{
    struct TUnaryExpressionOperator* p = (struct TUnaryExpressionOperator*) Malloc(sizeof * p);
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



