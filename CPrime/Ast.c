#include "Ast.h"
#include "Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

void TDeclarations_Destroy(TDeclarations* p) _default
{
    for (int i = 0; i < p->Size; i++)
    {
        TAnyDeclaration_Delete(p->pItems[i]);
    }
    free((void*)p->pItems);
}
void TDeclarations_Init(TDeclarations* p) _default
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}
void TDeclarations_Reserve(TDeclarations* p, int n) _default
{
    if (n > p->Capacity)
    {
        TAnyDeclaration** pnew = p->pItems;
        pnew = (TAnyDeclaration**)realloc(pnew, n * sizeof(TAnyDeclaration*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}
void TDeclarations_PushBack(TDeclarations* p, TDeclaration* pItem) _default
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

TGroupDeclaration* TGroupDeclaration_Create() _default
{
    TGroupDeclaration *p = (TGroupDeclaration*) malloc(sizeof * p);
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
void TGroupDeclaration_Delete(TGroupDeclaration* p) _default
{
    if (p != NULL)
    {
        TDeclarations_Destroy(&p->Declarations);
        String_Destroy(&p->Identifier);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        free((void*)p);
    }
}

void TStructDeclarationList_Destroy(TStructDeclarationList* p) _default
{
    for (int i = 0; i < p->Size; i++)
    {
        TAnyStructDeclaration_Delete(p->pItems[i]);
    }
    free((void*)p->pItems);
}
void TStructDeclarationList_Init(TStructDeclarationList* p) _default
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}

void TStructDeclarationList_Reserve(TStructDeclarationList* p, int n) _default
{
    if (n > p->Capacity)
    {
        TAnyStructDeclaration** pnew = p->pItems;
        pnew = (TAnyStructDeclaration**)realloc(pnew, n * sizeof(TAnyStructDeclaration*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}


void TStructDeclarationList_PushBack(TStructDeclarationList* p, TAnyStructDeclaration* pItem) _default
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

void TBlockItemList_Init(TBlockItemList* p) _default
{
    p->pItems = NULL;
    p->Size = 0;
    p->Capacity = 0;
}

void TBlockItemList_Destroy(TBlockItemList* p) _default
{
    for (int i = 0; i < p->Size; i++)
    {
        TBlockItem_Delete(p->pItems[i]);
    }
    free((void*)p->pItems);
}
void TBlockItemList_Reserve(TBlockItemList* p, int n) _default
{
    if (n > p->Capacity)
    {
        TBlockItem** pnew = p->pItems;
        pnew = (TBlockItem**)realloc(pnew, n * sizeof(TBlockItem*));
        if (pnew)
        {
            p->pItems = pnew;
            p->Capacity = n;
        }
    }
}
void TBlockItemList_PushBack(TBlockItemList* p, TBlockItem* pItem)_default
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

TCompoundStatement* TCompoundStatement_Create() _default
{
    TCompoundStatement *p = (TCompoundStatement*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TCompoundStatement_ID;
        TBlockItemList_Init(&p->BlockItemList);
        TScannerItemList_Init(&p->ClueList0);
        TScannerItemList_Init(&p->ClueList1);
    }
    return p;
}


void TCompoundStatement_Delete(TCompoundStatement* p) _default
{
    if (p != NULL)
    {
        TBlockItemList_Destroy(&p->BlockItemList);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        free((void*)p);
    }
}

TLabeledStatement* TLabeledStatement_Create(void) _default
{
    TLabeledStatement *p = (TLabeledStatement*) malloc(sizeof * p);
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

void TLabeledStatement_Delete(TLabeledStatement* p)_default
{
    if (p != NULL)
    {
        TStatement_Delete(p->pStatementOpt);
        TExpression_Delete(p->pExpression);
        String_Destroy(&p->Identifier);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        free((void*)p);
    }
}
TForStatement* TForStatement_Create(void)_default
{
    TForStatement *p = (TForStatement*) malloc(sizeof * p);
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

void TForStatement_Delete(TForStatement* p)_default
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
        free((void*)p);
    }
}

TWhileStatement* TWhileStatement_Create(void) _default
{
    TWhileStatement *p = (TWhileStatement*) malloc(sizeof * p);
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

void TWhileStatement_Delete(TWhileStatement* p)_default
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TStatement_Delete(p->pStatement);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        free((void*)p);
    }
}

TDoStatement* TDoStatement_Create(void) _default
{
    TDoStatement *p = (TDoStatement*) malloc(sizeof * p);
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

void TDoStatement_Delete(TDoStatement* p) _default
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
        free((void*)p);
    }
}


TExpressionStatement* TExpressionStatement_Create(void) _default
{
    TExpressionStatement *p = (TExpressionStatement*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TExpressionStatement_ID;
        p->pExpression = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}

void TExpressionStatement_Delete(TExpressionStatement* p)_default
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        free((void*)p);
    }
}

TJumpStatement* TJumpStatement_Create(void) _default
{
    TJumpStatement *p = (TJumpStatement*) malloc(sizeof * p);
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

void TJumpStatement_Delete(TJumpStatement* p) _default
{
    if (p != NULL)
    {
        String_Destroy(&p->Identifier);
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        free((void*)p);
    }
}




TAsmStatement* TAsmStatement_Create(void) _default
{
    TAsmStatement *p = (TAsmStatement*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TAsmStatement_ID;
        TScannerItemList_Init(&p->ClueList);
    }
    return p;
}

void TAsmStatement_Delete(TAsmStatement* p) _default
{
    if (p != NULL)
    {
        TScannerItemList_Destroy(&p->ClueList);
        free((void*)p);
    }
}

TSwitchStatement* TSwitchStatement_Create(void) _default
{
    TSwitchStatement *p = (TSwitchStatement*) malloc(sizeof * p);
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

void TSwitchStatement_Delete(TSwitchStatement* p) _default
{
    if (p != NULL)
    {
        TExpression_Delete(p->pConditionExpression);
        TStatement_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        free((void*)p);
    }
}


TIfStatement* TIfStatement_Create(void) _default
{
    TIfStatement *p = (TIfStatement*) malloc(sizeof * p);
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

void TIfStatement_Delete(TIfStatement* p) _default
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
        free((void*)p);
    }
}

void TStatement_Delete(TStatement* p) _default
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



void TBlockItem_Delete(TBlockItem* p) _default
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

void TPrimaryExpressionValue_Init(TPrimaryExpressionValue* p) _default
{
    p->Type = TPrimaryExpressionValue_ID;
    p->token = TK_NONE;
    String_Init(&p->lexeme);
    p->pExpressionOpt = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
}

void TPrimaryExpressionValue_Destroy(TPrimaryExpressionValue* p) _default
{
    String_Destroy(&p->lexeme);
    TExpression_Delete(p->pExpressionOpt);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

TPrimaryExpressionValue* TPrimaryExpressionValue_Create() _default
{
    TPrimaryExpressionValue *p = (TPrimaryExpressionValue*) malloc(sizeof * p);
    if (p != NULL)
    {
        TPrimaryExpressionValue_Init(p);
    }
    return p;
}

void TPrimaryExpressionValue_Delete(TPrimaryExpressionValue* p) _default
{
    if (p != NULL)
    {
        TPrimaryExpressionValue_Destroy(p);
        free((void*)p);
    }
}



void TPostfixExpressionCore_Delete(TPostfixExpressionCore* p) _default
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
        free((void*)p);
    }
}

TBinaryExpression* TBinaryExpression_Create(void) _default
{
    TBinaryExpression *p = (TBinaryExpression*) malloc(sizeof * p);
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

void TBinaryExpression_Delete(TBinaryExpression* p) _default
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpressionLeft);
        TExpression_Delete(p->pExpressionRight);
        TScannerItemList_Destroy(&p->ClueList0);
        free((void*)p);
    }
}


void TUnaryExpressionOperator_Delete(TUnaryExpressionOperator* p) _default
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpressionRight);
        TTypeName_Destroy(&p->TypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        free((void*)p);
    }
}


void TCastExpressionType_Delete(TCastExpressionType* p) _default
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpression);
        TTypeName_Destroy(&p->TypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        free((void*)p);
    }
}

TTernaryExpression* TTernaryExpression_Create(void) _default
{
    TTernaryExpression *p = (TTernaryExpression*) malloc(sizeof * p);
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

void TTernaryExpression_Delete(TTernaryExpression* p) _default
{
    if (p != NULL)
    {
        TExpression_Delete(p->pExpressionLeft);
        TExpression_Delete(p->pExpressionMiddle);
        TExpression_Delete(p->pExpressionRight);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        free((void*)p);
    }
}

void TPrimaryExpressionLiteralItem_Delete(TPrimaryExpressionLiteralItem *p) _default
{
    if (p != NULL)
    {
        TPrimaryExpressionLiteralItem_Delete(p->pNext);
        String_Destroy(&p->lexeme);
        TScannerItemList_Destroy(&p->ClueList0);
        free((void*)p);
    }
}
TPrimaryExpressionLiteralItem* TPrimaryExpressionLiteralItem_Create() _default
{
    TPrimaryExpressionLiteralItem *p = (TPrimaryExpressionLiteralItem*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->pNext = NULL;
        String_Init(&p->lexeme);
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}

TPrimaryExpressionLiteral* TPrimaryExpressionLiteral_Create() _default
{
    TPrimaryExpressionLiteral *p = (TPrimaryExpressionLiteral*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TPrimaryExpressionLiteral_ID;
        TPrimaryExpressionLiteralItemList_Init(&p->List);
    }
    return p;
}


void TPrimaryExpressionLiteral_Delete(TPrimaryExpressionLiteral* p) _default
{
    if (p != NULL)
    {
        TPrimaryExpressionLiteralItemList_Destroy(&p->List);
        free((void*)p);
    }
}

void TExpression_Delete(TExpression* p) _default
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TBinaryExpression_ID:
                    TBinaryExpression_Delete((TBinaryExpression*)p);
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
                default:
                break;
            }
    }
}


TEofDeclaration* TEofDeclaration_Create() _default
{
    TEofDeclaration *p = (TEofDeclaration*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TEofDeclaration_ID;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}


void TEofDeclaration_Delete(TEofDeclaration* p) _default
{
    if (p != NULL)
    {
        TScannerItemList_Destroy(&p->ClueList0);
        free((void*)p);
    }
}



TStaticAssertDeclaration* TStaticAssertDeclaration_Create() _default
{
    TStaticAssertDeclaration *p = (TStaticAssertDeclaration*) malloc(sizeof * p);
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

void TStaticAssertDeclaration_Delete(TStaticAssertDeclaration* p) _default
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
        free((void*)p);
    }
}

TEnumerator* TEnumerator_Create(void) _default
{
    TEnumerator *p = (TEnumerator*) malloc(sizeof * p);
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

void TEnumerator_Delete(TEnumerator* p) _default
{
    if (p != NULL)
    {
        TEnumerator_Delete(p->pNext);
        String_Destroy(&p->Name);
        TExpression_Delete(p->pExpression);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        free((void*)p);
    }
}

void TEnumeratorList_Init(TEnumeratorList* p) _default
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TEnumeratorList_Destroy(TEnumeratorList* p) _default
{
    TEnumerator_Delete(p->pHead);
}

TEnumSpecifier* TEnumSpecifier_Create(void) _default
{
    TEnumSpecifier *p = (TEnumSpecifier*) malloc(sizeof * p);
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

void TEnumSpecifier_Delete(TEnumSpecifier* p) _default
{
    if (p != NULL)
    {
        String_Destroy(&p->Name);
        TEnumeratorList_Destroy(&p->EnumeratorList);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        TScannerItemList_Destroy(&p->ClueList3);
        free((void*)p);
    }
}



TUnionSetItem* TUnionSetItem_Create() _default
{
    TUnionSetItem *p = (TUnionSetItem*) malloc(sizeof * p);
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
void TUnionSetItem_Delete(TUnionSetItem* p) _default
{
    if (p != NULL)
    {
        TUnionSetItem_Delete(p->pNext);
        String_Destroy(&p->Name);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        free((void*)p);
    }
}

void TUnionSet_Init(TUnionSet* p) _default
{
    p->pHead = NULL;
    p->pTail = NULL;
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    TScannerItemList_Init(&p->ClueList2);
}

void TUnionSet_Destroy(TUnionSet* p) _default
{
    TUnionSetItem_Delete(p->pHead);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
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




TStructUnionSpecifier* TStructUnionSpecifier_Create() _default
{
    TStructUnionSpecifier *p = (TStructUnionSpecifier*) malloc(sizeof * p);
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
void TStructUnionSpecifier_Delete(TStructUnionSpecifier* p) _default
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
        free((void*)p);
    }
}


TSingleTypeSpecifier* TSingleTypeSpecifier_Create(void) _default
{
    TSingleTypeSpecifier *p = (TSingleTypeSpecifier*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TSingleTypeSpecifier_ID;
        p->Token = TK_NONE;
        String_Init(&p->TypedefName);
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TSingleTypeSpecifier_Destroy(TSingleTypeSpecifier* p) _default
{
    String_Destroy(&p->TypedefName);
    TScannerItemList_Destroy(&p->ClueList0);
}
void TSingleTypeSpecifier_Delete(TSingleTypeSpecifier* p) _default
{
    if (p != NULL)
    {
        TSingleTypeSpecifier_Destroy(p);
        free((void*)p);
    }
}


const char* TSingleTypeSpecifier_GetTypedefName(TSingleTypeSpecifier* p)
{
	const char* result = NULL;
	if (p->Token == TK_IDENTIFIER)
	{
		result = p->TypedefName;
	}
	return result;
}

void TTypeSpecifier_Delete(TTypeSpecifier* p) _default
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


void TDeclarator_Init(TDeclarator* p) _default
{
    p->PointerList.pHead = NULL;
    p->PointerList.pTail = NULL;
    p->pDirectDeclarator = NULL;
    TScannerItemList_Init(&p->ClueList);
}

TDeclarator* TDeclarator_Create() _default
{
    TDeclarator *p = (TDeclarator*) malloc(sizeof * p);
    if (p != NULL)
    {
        TDeclarator_Init(p);
    }
    return p;
}

void TDeclarator_Destroy(TDeclarator* p) _default
{
    TPointerList_Destroy(&p->PointerList);
    TDirectDeclarator_Delete(p->pDirectDeclarator);
    TScannerItemList_Destroy(&p->ClueList);
}

void TDeclarator_Delete(TDeclarator* p) _default
{
    if (p != NULL)
    {
        TDeclarator_Destroy(p);
        free((void*)p);
    }
}

TInitDeclarator* TInitDeclarator_Create() _default
{
    TInitDeclarator *p = (TInitDeclarator*) malloc(sizeof * p);
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

void TInitDeclarator_Destroy(TInitDeclarator* p) _default
{
    TDeclarator_Delete(p->pDeclarator);
    TInitializer_Delete(p->pInitializer);
    TInitDeclarator_Delete(p->pNext);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}

void TInitDeclarator_Delete(TInitDeclarator* p) _default
{
    if (p != NULL)
    {
        TInitDeclarator_Destroy(p);
        free((void*)p);
    }
}

void TParameterTypeList_Init(TParameterTypeList* p) _default
{
    TParameterList_Init(&p->ParameterList);
    TScannerItemList_Init(&p->ClueList0);
    TScannerItemList_Init(&p->ClueList1);
    p->bVariadicArgs = false;
}
void TParameterTypeList_Destroy(TParameterTypeList* p) _default
{
    TParameterList_Destroy(&p->ParameterList);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
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
	bool bFound = false;
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

void TDirectDeclarator_Destroy(TDirectDeclarator* p) _default
{
    String_Destroy(&p->Identifier);
    TDeclarator_Delete(p->pDeclarator);
    TDirectDeclarator_Delete(p->pDirectDeclarator);
    TParameterTypeList_Destroy(&p->Parameters);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
    TScannerItemList_Destroy(&p->ClueList3);
}

void TDirectDeclarator_Delete(TDirectDeclarator* p) _default
{
    if (p != NULL)
    {
        TDirectDeclarator_Destroy(p);
        free((void*)p);
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
			pSpecifier = pSpecifierQualifier;
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
			pSingleTypeSpecifier->Token == TK_IDENTIFIER)
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
			pSingleTypeSpecifier->Token == TK_CHAR)
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
			(pSingleTypeSpecifier->Token == TK_INT ||
				pSingleTypeSpecifier->Token == TK_SHORT ||
				pSingleTypeSpecifier->Token == TK_SIGNED ||
				pSingleTypeSpecifier->Token == TK_UNSIGNED ||
				pSingleTypeSpecifier->Token == TK__INT8 ||
				pSingleTypeSpecifier->Token == TK__INT16 ||
				pSingleTypeSpecifier->Token == TK__INT32 ||
				pSingleTypeSpecifier->Token == TK__INT64 ||
				pSingleTypeSpecifier->Token == TK__WCHAR_T)
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
			(pSingleTypeSpecifier->Token == TK_DOUBLE ||
				pSingleTypeSpecifier->Token == TK_FLOAT))
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
			pSingleTypeSpecifier->Token == TK__BOOL)
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
	ASSERT(p->pDeclarator != NULL);
	return TDeclarator_GetName(p->pDeclarator);
}



TAlignmentSpecifier* TAlignmentSpecifier_Create(void) _default
{
    TAlignmentSpecifier *p = (TAlignmentSpecifier*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TAlignmentSpecifier_ID;
        String_Init(&p->TypeName);
    }
    return p;
}
void TAlignmentSpecifier_Destroy(TAlignmentSpecifier* p) _default
{
    String_Destroy(&p->TypeName);
}

void TAlignmentSpecifier_Delete(TAlignmentSpecifier* p) _default
{
    if (p != NULL)
    {
        TAlignmentSpecifier_Destroy(p);
        free((void*)p);
    }
}


TStructDeclaration* TStructDeclaration_Create() _default
{
    TStructDeclaration *p = (TStructDeclaration*) malloc(sizeof * p);
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


void TStructDeclaratorList_Destroy(TStructDeclaratorList* p) _default
{
    TInitDeclarator_Delete(p->pHead);
}

void TStructDeclaratorList_Init(TStructDeclaratorList* p) _default
{
    p->pHead = NULL;
    p->pTail = NULL;
}


void TStructDeclaration_Destroy(TStructDeclaration* p) _default
{
    TSpecifierQualifierList_Destroy(&p->SpecifierQualifierList);
    TStructDeclaratorList_Destroy(&p->DeclaratorList);
    TScannerItemList_Destroy(&p->ClueList1);
}

void TStructDeclaration_Delete(TStructDeclaration* p) _default
{
    if (p != NULL)
    {
        TStructDeclaration_Destroy(p);
        free((void*)p);
    }
}


void TAnyStructDeclaration_Delete(TAnyStructDeclaration* p) _default
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
				if (pQualifier->Token == TK__AUTO ||
					pQualifier->Token == TK_OWN_QUALIFIER)
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

void TPointerList_Destroy(TPointerList* p) _default
{
    TPointer_Delete(p->pHead);
}

TPointer* TPointer_Create(void) _default
{
    TPointer *p = (TPointer*) malloc(sizeof * p);
    if (p != NULL)
    {
        TTypeQualifierList_Init(&p->Qualifier);
        p->pNext = NULL;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TPointer_Destroy(TPointer* p) _default
{
    TTypeQualifierList_Destroy(&p->Qualifier);
    TPointer_Delete(p->pNext);
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

void TPointer_Delete(TPointer* p) _default
{
    if (p != NULL)
    {
        TPointer_Destroy(p);
        free((void*)p);
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

			if (pQualifier->Token == TK__SIZE)
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

				if (pQualifier->Token == TK__SIZE)
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
	bool bResult = false;
	TPointer* pPointer = pPointerlist->pHead;
	if (pPointer != NULL)
	{
		if (pPointer->Qualifier.Size == 1 &&
			pPointer->Qualifier.Data[0]->Token == TK__AUTO)
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


bool TPointerList_IsAutoPointerSizeToObject(TPointerList* pPointerlist)
{
	bool bResult = false;
	TPointer* pPointer = pPointerlist->pHead;
	if (pPointer != NULL)
	{
		if (pPointer->Qualifier.Size == 2 &&
			pPointer->pNext == NULL)
		{
			bResult = (pPointer->Qualifier.Data[0]->Token == TK__AUTO &&
				pPointer->Qualifier.Data[1]->Token == TK__SIZE) ||
				(pPointer->Qualifier.Data[0]->Token == TK__SIZE &&
					pPointer->Qualifier.Data[0]->Token == TK__AUTO);
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
			pPointer->Qualifier.Data[0]->Token == TK__AUTO)
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
			pPointer->Qualifier.Data[0]->Token == TK__AUTO)
		{
			pPointer = pPointer->pNext;
			if (pPointer != NULL)
			{
				if (pPointer->Qualifier.Size == 1 &&
					pPointer->Qualifier.Data[0]->Token == TK__AUTO)
				{
					bResult = true;
				}
				else if (pPointer->Qualifier.Size == 2)
				{
					//auto _size()
					// _size() auto
					bResult = pPointer->Qualifier.Data[0]->Token == TK__AUTO ||
						pPointer->Qualifier.Data[1]->Token == TK__AUTO;
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

TTypeQualifier* TTypeQualifier_Create(void) _default
{
    TTypeQualifier *p = (TTypeQualifier*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TTypeQualifier_ID;
        String_Init(&p->SizeIdentifier);
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TTypeQualifier_Destroy(TTypeQualifier* p) _default
{
    String_Destroy(&p->SizeIdentifier);
    TScannerItemList_Destroy(&p->ClueList0);
}
void TTypeQualifier_Delete(TTypeQualifier* p) _default
{
    if (p != NULL)
    {
        TTypeQualifier_Destroy(p);
        free((void*)p);
    }
}

void TTypeQualifier_Copy(TTypeQualifier* dest, TTypeQualifier* src)
{
	String_Set(&dest->SizeIdentifier, src->SizeIdentifier);
	dest->Token = src->Token;
	//dest->ClueList0 nao vamos copiar
	//dest->Type nao precisa copiar
}


TStorageSpecifier* TStorageSpecifier_Create(void) _default
{
    TStorageSpecifier *p = (TStorageSpecifier*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TStorageSpecifier_ID;
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TStorageSpecifier_Destroy(TStorageSpecifier* p) _default
{
    TScannerItemList_Destroy(&p->ClueList0);
}
void TStorageSpecifier_Delete(TStorageSpecifier* p) _default
{
    if (p != NULL)
    {
        TStorageSpecifier_Destroy(p);
        free((void*)p);
    }
}


void TAtomicTypeSpecifier_Delete(TAtomicTypeSpecifier* p) _default
{
    if (p != NULL)
    {
        TTypeName_Destroy(&p->TypeName);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        TScannerItemList_Destroy(&p->ClueList2);
        free((void*)p);
    }
}

void TSpecifierQualifierList_Destroy(TSpecifierQualifierList* pDeclarationSpecifiers) _default
{
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TSpecifierQualifier_Delete(pDeclarationSpecifiers->pData[i]);
    }
    free((void*)pDeclarationSpecifiers->pData);
}


void TSpecifierQualifierList_Reserve(TSpecifierQualifierList* p, int n) _default
{
    if (n > p->Capacity)
    {
        TSpecifierQualifier** pnew = p->pData;
        pnew = (TSpecifierQualifier**)realloc(pnew, n * sizeof(TSpecifierQualifier*));
        if (pnew)
        {
            p->pData = pnew;
            p->Capacity = n;
        }
    }
}

void TSpecifierQualifierList_PushBack(TSpecifierQualifierList* p, TSpecifierQualifier* pItem) _default
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
			switch (pTSingleTypeSpecifier->Token)
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
				ASSERT(false);
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
			ASSERT(false);
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


	bool bTypeDef = false;
	bool bInt = false;

	for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
	{
		TDeclarationSpecifier* pSpecifier = pDeclarationSpecifiers->pData[i];

		switch (pSpecifier->Type)
		{
			CASE(TSingleTypeSpecifier) :
			{     TSingleTypeSpecifier* pTSingleTypeSpecifier =
				(TSingleTypeSpecifier*)pSpecifier;
			switch (pTSingleTypeSpecifier->Token)
			{
			case TK_INT:
				bInt = true;
				break;
			case TK_DOUBLE:
			case TK_IDENTIFIER:
				bTypeDef = true;
				break;
			default:
				ASSERT(false);
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
			ASSERT(false);
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
			if (pSingleTypeSpecifier->Token == TK_IDENTIFIER)
			{
				typeName = pSingleTypeSpecifier->TypedefName;
				break;
			}
		}
	}
	return typeName;
}

void TSpecifierQualifier_Delete(TSpecifierQualifier* pItem) _default
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

void TDeclarationSpecifier_Delete(TDeclarationSpecifier* pItem) _default
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

void TDeclarationSpecifiers_Init(TDeclarationSpecifiers* pDeclarationSpecifiers) _default
{
    pDeclarationSpecifiers->pData = NULL;
    pDeclarationSpecifiers->Size = 0;
    pDeclarationSpecifiers->Capacity = 0;
}

void TDeclarationSpecifiers_Destroy(TDeclarationSpecifiers* pDeclarationSpecifiers) _default
{
    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        TDeclarationSpecifier_Delete(pDeclarationSpecifiers->pData[i]);
    }
    free((void*)pDeclarationSpecifiers->pData);
}


void TDeclarationSpecifiers_Reserve(TDeclarationSpecifiers* p, int n) _default
{
    if (n > p->Capacity)
    {
        TDeclarationSpecifier** pnew = p->pData;
        pnew = (TDeclarationSpecifier**)realloc(pnew, n * sizeof(TDeclarationSpecifier*));
        if (pnew)
        {
            p->pData = pnew;
            p->Capacity = n;
        }
    }
}

void TDeclarationSpecifiers_PushBack(TDeclarationSpecifiers* p, TDeclarationSpecifier* pItem) _default
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

TFunctionSpecifier* TFunctionSpecifier_Create(void) _default
{
    TFunctionSpecifier *p = (TFunctionSpecifier*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->Type = TFunctionSpecifier_ID;
        p->Token = TK_NONE;
        TScannerItemList_Init(&p->ClueList0);
    }
    return p;
}
void TFunctionSpecifier_Destroy(TFunctionSpecifier* p) _default
{
    TScannerItemList_Destroy(&p->ClueList0);
}
void TFunctionSpecifier_Delete(TFunctionSpecifier* p) _default
{
    if (p != NULL)
    {
        TFunctionSpecifier_Destroy(p);
        free((void*)p);
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

void TInitDeclaratorList_Init(TInitDeclaratorList* p) _default
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TInitDeclaratorList_Destroy(TInitDeclaratorList* p) _default
{
    TInitDeclarator_Delete(p->pHead);
}



void TDeclaration_Delete(TDeclaration* p) _default
{
    if (p != NULL)
    {
        TDeclarationSpecifiers_Destroy(&p->Specifiers);
        TInitDeclaratorList_Destroy(&p->InitDeclaratorList);
        TCompoundStatement_Delete(p->pCompoundStatementOpt);
        TScannerItemList_Destroy(&p->ClueList0);
        TScannerItemList_Destroy(&p->ClueList1);
        free((void*)p);
    }
}
TDeclaration* TDeclaration_Create() _default
{
    TDeclaration *p = (TDeclaration*) malloc(sizeof * p);
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
			pSingleTypeSpecifier->Token == TK_IDENTIFIER)
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


TParameter* TParameter_Create() _default
{
    TParameter *p = (TParameter*) malloc(sizeof * p);
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

void TParameter_Delete(TParameter* p) _default
{
    if (p != NULL)
    {
        TParameter_Delete(p->pNext);
        TDeclarationSpecifiers_Destroy(&p->Specifiers);
        TDeclarator_Destroy(&p->Declarator);
        TScannerItemList_Destroy(&p->ClueList0);
        free((void*)p);
    }
}

void TParameterList_Init(TParameterList* p) _default
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TParameterList_Destroy(TParameterList* p) _default
{
    TParameter_Delete(p->pHead);
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
			ASSERT(false);
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
		ASSERT(false);
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
		ASSERT(false);
		break;
	}
	return result;
}

void TAnyDeclaration_Delete(TAnyDeclaration* pDeclaration) _default
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

void TDesignation_Destroy(TDesignation* pDesignation) _default
{
    TDesignatorList_Destroy(&pDesignation->DesignatorList);
    TScannerItemList_Destroy(&pDesignation->ClueList0);
}

TDesignator* TDesignator_Create(void) _default
{
    TDesignator *p = (TDesignator*) malloc(sizeof * p);
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
void TDesignator_Destroy(TDesignator* p) _default
{
    String_Destroy(&p->Name);
    TExpression_Delete(p->pExpression);
    TDesignator_Delete(p->pNext);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
}
void TDesignator_Delete(TDesignator* p) _default
{
    if (p != NULL)
    {
        TDesignator_Destroy(p);
        free((void*)p);
    }
}


TInitializerListType* TInitializerListType_Create(void) _default
{
    TInitializerListType *p = (TInitializerListType*) malloc(sizeof * p);
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
void TInitializerListType_Destroy(TInitializerListType* p) _default
{
    TInitializerList_Destroy(&p->InitializerList);
    TScannerItemList_Destroy(&p->ClueList0);
    TScannerItemList_Destroy(&p->ClueList1);
    TScannerItemList_Destroy(&p->ClueList2);
}
void TInitializerListType_Delete(TInitializerListType* p) _default
{
    if (p != NULL)
    {
        TInitializerListType_Destroy(p);
        free((void*)p);
    }
}

void TInitializerList_Init(TInitializerList* p) _default
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TInitializerList_Destroy(TInitializerList* p) _default
{
    TInitializerListItem_Delete(p->pHead);
}

void TInitializer_Delete(TInitializer* p) _default
{
    if (p != NULL)
    {
            switch (p->Type)
            {
                case TBinaryExpression_ID:
                    TBinaryExpression_Delete((TBinaryExpression*)p);
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
                default:
                break;
            }
    }
}


void TDesignatorList_Init(TDesignatorList* p) _default
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TDesignatorList_Destroy(TDesignatorList* p) _default
{
    TDesignator_Delete(p->pHead);
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

void TInitializerListItem_Destroy(TInitializerListItem* p) _default
{
    TDesignatorList_Destroy(&p->DesignatorList);
    TInitializer_Delete(p->pInitializer);
    TInitializerListItem_Delete(p->pNext);
    TScannerItemList_Destroy(&p->ClueList);
}

TInitializerListItem* TInitializerListItem_Create() _default
{
    TInitializerListItem *p = (TInitializerListItem*) malloc(sizeof * p);
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
void TInitializerListItem_Delete(TInitializerListItem* p) _default
{
    if (p != NULL)
    {
        TInitializerListItem_Destroy(p);
        free((void*)p);
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


void TProgram_Init(TProgram* p) _default
{
    TDeclarations_Init(&p->Declarations);
    TFileArray_Init(&p->Files2);
    SymbolMap_Init(&p->GlobalScope);
    MacroMap_Init(&p->Defines);
}


void TProgram_Destroy(TProgram * p) _default
{
    TDeclarations_Destroy(&p->Declarations);
    TFileArray_Destroy(&p->Files2);
    SymbolMap_Destroy(&p->GlobalScope);
    MacroMap_Destroy(&p->Defines);
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
		ASSERT(false);
		break;
	case TK_ARROW:
		//fprintf(fp, "->%s", p->Identifier);
		//b = true;
		ASSERT(false);
		break;

	case TK_LEFT_SQUARE_BRACKET:
	{
		int index;
		//fprintf(fp, "[");
		EvaluateConstantExpression(p->pExpressionRight, &index);
		//fprintf(fp, "]");
		ASSERT(false);
	}
	break;

	case TK_LEFT_PARENTHESIS:
	{
		EvaluateConstantExpression(p->pExpressionRight, &result);
	}
	break;

	case TK_PLUSPLUS:
		ASSERT(false);
		break;
	case TK_MINUSMINUS:
		ASSERT(false);
		break;
	default:
		ASSERT(false);
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
				ASSERT(false);
				b = false;
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
			ASSERT(false);
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
					ASSERT(0);
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
			ASSERT(false);
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
					ASSERT(false);
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
			ASSERT(false);

		}
		break;

	default:
		ASSERT(false);
	}

	ASSERT(result != -987654321);
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

void TPrimaryExpressionLiteralItemList_Init(TPrimaryExpressionLiteralItemList* p) _default
{
    p->pHead = NULL;
    p->pTail = NULL;
}

void TPrimaryExpressionLiteralItemList_Destroy(TPrimaryExpressionLiteralItemList* p) _default
{
    TPrimaryExpressionLiteralItem_Delete(p->pHead);
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






TDirectDeclarator* TDirectDeclarator_Create() _default
{
    TDirectDeclarator *p = (TDirectDeclarator*) malloc(sizeof * p);
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


TTypeName* TTypeName_Create() _default
{
    TTypeName *p = (TTypeName*) malloc(sizeof * p);
    if (p != NULL)
    {
        TTypeName_Init(p);
    }
    return p;
}


void TTypeName_Destroy(TTypeName* p) _default
{
    TSpecifierQualifierList_Destroy(&p->SpecifierQualifierList);
    TDeclarator_Destroy(&p->Declarator);
}

void TTypeName_Delete(TTypeName* p) _default
{
    if (p != NULL)
    {
        TTypeName_Destroy(p);
        free((void*)p);
    }
}


TAtomicTypeSpecifier* TAtomicTypeSpecifier_Create() _default
{
    TAtomicTypeSpecifier *p = (TAtomicTypeSpecifier*) malloc(sizeof * p);
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




TPostfixExpressionCore* TPostfixExpressionCore_Create() _default
{
    TPostfixExpressionCore *p = (TPostfixExpressionCore*) malloc(sizeof * p);
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

TCastExpressionType* TCastExpressionType_Create() _default
{
    TCastExpressionType *p = (TCastExpressionType*) malloc(sizeof * p);
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


TUnaryExpressionOperator* TUnaryExpressionOperator_Create() _default
{
    TUnaryExpressionOperator *p = (TUnaryExpressionOperator*) malloc(sizeof * p);
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



