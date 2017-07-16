#include "Ast.h"
#include "..\Base\Array.h"
#include "..\Base\Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "AstPrint.h"

bool TFunctionSpecifier_Print(TFunctionSpecifier* p, bool b, FILE* fp);
bool StorageSpecifier_Print(TStorageSpecifier* p, bool b, FILE* fp);
bool TTypeQualifierList_Print(TTypeQualifierList* p, bool b, FILE* fp);
bool TDeclarator_Print(TDeclarator* p, bool b, FILE* fp);
bool TAnyDeclaration_Print(TAnyDeclaration *pDeclaration, bool b, FILE* fp);
bool TTypeSpecifier_Print(TTypeSpecifier* p, bool b, FILE* fp);
bool TStructDeclaration_Print(TAnyStructDeclaration* p, bool b, FILE* fp);
bool TTypeQualifier_Print(TTypeQualifier* p, bool b, FILE* fp);
bool TDeclaration_Print(TDeclaration* p, bool b, FILE* fp);
bool TExpression_Print(TExpression * p, const char* name, bool b, FILE* fp);
bool TStatement_Print(TStatement * p, bool b, FILE* fp);
bool TBlockItem_Print(TBlockItem * p, bool b, FILE* fp);
bool TInitializer_Print(TInitializer* p, bool b, FILE* fp);
bool TPointer_Print(TPointer* pPointer, bool b, FILE* fp);
bool TParameterDeclaration_Print(TParameterDeclaration* p, bool b, FILE* fp);
bool TInitializerListItem_Print(TInitializerListItem* p, bool b, FILE* fp);

bool TCompoundStatement_Print(TCompoundStatement * p, bool b, FILE* fp)
{
    if (b)
    {
        fprintf(fp, ",");
    }

    b = true;
    fprintf(fp, "\"compound-statement\": [");

    for (size_t j = 0; j < p->BlockItemList.size; j++)
    {
        TBlockItem *pBlockItem = p->BlockItemList.pItems[j];
        TBlockItem_Print(pBlockItem, j > 0, fp);
    }

    fprintf(fp, "]");
    return b;
}


bool TLabeledStatement_Print(TLabeledStatement * p, bool b, FILE* fp)
{
    b = true;
    fprintf(fp, "\"type\":\"labeled-statement\"");

    if (p->pStatementOpt)
    {
        fprintf(fp, ",");
        fprintf(fp, "\"statement\": {");
        b = TStatement_Print(p->pStatementOpt, false, fp);
        fprintf(fp, "}");
    }

    return b;
}

bool TForStatement_Print(TForStatement * p, bool b, FILE* fp)
{
    b = true;
    fprintf(fp, "\"type\":\"for-statement\"");
    fprintf(fp, ",");



    if (p->pInitDeclarationOpt != NULL)
    {
        fprintf(fp, "\"initdecl\":");
        b = TAnyDeclaration_Print(p->pInitDeclarationOpt, b, fp);
        //fprintf(fp, "}");
        b = true;
    }

    b = TExpression_Print(p->pExpression1, "expr1", true, fp);
    //fprintf(fp, ",");
    b = TExpression_Print(p->pExpression2, "expr2", b, fp);
    //fprintf(fp, ",");
    b = TExpression_Print(p->pExpression3, "expr3", b, fp);

    if (b)
        fprintf(fp, ",");

    fprintf(fp, "\"statement\": {");
    b = TStatement_Print(p->pStatement, false, fp);
    fprintf(fp, "}");
    return b;
}


bool TWhileStatement_Print(TWhileStatement * p, bool b, FILE* fp)
{
    b = true;
    fprintf(fp, "\"type\":\"while-statement\"");
    fprintf(fp, ",");
    b = TExpression_Print(p->pExpression, "expr", false, fp);
    fprintf(fp, ",");
    fprintf(fp, "\"statement\": {");
    b = TStatement_Print(p->pStatement, false, fp);
    fprintf(fp, "}");
    return b;
}


bool TReturnStatement_Print(TReturnStatement * p, bool b, FILE* fp)
{
    TExpression_Print(p->pExpression, "return-statement", false, fp);
    return true;
}

bool TDoStatement_Print(TDoStatement * p, bool b, FILE* fp)
{
    b = true;
    fprintf(fp, "\"type\":\"do-statement\"");
    fprintf(fp, ",");
    b = TExpression_Print(p->pExpression, "expr", false, fp);
    fprintf(fp, ",");
    fprintf(fp, "\"statement\": {");
    b = TStatement_Print(p->pStatement, false, fp);
    fprintf(fp, "}");
    return b;
}

void PrintLiteralString(FILE* fp, const char* psz)
{
    fprintf(fp, "\"");

    while (*psz)
    {
        switch (*psz)
        {
            case '"':
            fprintf(fp, "\\\"");
            break;

            case '/':
            fprintf(fp, "\\/");
            break;

            case '\b':
            fprintf(fp, "\\b");
            break;

            case '\f':
            fprintf(fp, "\\f");
            break;

            case '\n':
            fprintf(fp, "\\n");
            break;

            case L'\r':
            fprintf(fp, "\\r");
            break;

            case L'\t':
            fprintf(fp, "\\t");
            break;

            case L'\\':
            fprintf(fp, "\\\\");
            break;

            default:
            fprintf(fp, "%c", *psz);
            break;
        }

        psz++;
    }

    fprintf(fp, "\"");
}

bool TExpressionStatement_Print(TExpressionStatement * p, bool b, FILE* fp)
{
    TExpression_Print(p->pExpression, "expression-statement", b, fp);
    //fprintf(fp, ",");
    //TExpression_Print(&p->Expression, false, fp);
    //fprintf(fp, "}");
    return true;
}


bool TJumpStatement_Print(TJumpStatement * p, bool b, FILE* fp)
{
    fprintf(fp, "\"type\":\"jump-statement\"");
    //fprintf(fp, ",");
    //fprintf(fp, "\"statement\": {");
    b = TExpression_Print(p->pExpression, "statement", false, fp);
    //fprintf(fp, "}");
    return true;
}

bool TAsmStatement_Print(TAsmStatement * p, bool b, FILE* fp)
{
    fprintf(fp, "\"type\":\"asm-statement\"");
    return true;
}

bool TSwitchStatement_Print(TSwitchStatement * p, bool b, FILE* fp)
{
    b = true;
    fprintf(fp, "\"type\":\"switch-statement\"");
    fprintf(fp, ",");
    b = TExpression_Print(p->pConditionExpression, "expr", false, fp);
    fprintf(fp, ",");
    fprintf(fp, "\"statement\": {");
    b = TStatement_Print(p->pExpression, false, fp);
    fprintf(fp, "}");
    return b;
}


bool TIfStatement_Print(TIfStatement * p, bool b, FILE* fp)
{
    b = true;
    fprintf(fp, "\"type\":\"if-statement\"");
    fprintf(fp, ",");
    b = TExpression_Print(p->pConditionExpression, "expr", false, fp);
    fprintf(fp, ",");
    fprintf(fp, "\"statement\": {");
    b = TStatement_Print(p->pStatement, false, fp);
    fprintf(fp, "}");
    return b;
}

bool TStatement_Print(TStatement *  p, bool b, FILE* fp)
{
    if (p == NULL)
    {
        return false;
    }

    switch (p->Type)
    {
        case TExpressionStatement_ID:
        b = TExpressionStatement_Print((TExpressionStatement*)p, b, fp);
        break;

        case TSwitchStatement_ID:
        b = TSwitchStatement_Print((TSwitchStatement*)p, b, fp);
        break;

        case TLabeledStatement_ID:
        b = TLabeledStatement_Print((TLabeledStatement*)p, b, fp);
        break;

        case TForStatement_ID:
        b = TForStatement_Print((TForStatement*)p, b, fp);
        break;

        case TJumpStatement_ID:
        b = TJumpStatement_Print((TJumpStatement*)p, b, fp);
        break;

        case TAsmStatement_ID:
        b = TAsmStatement_Print((TAsmStatement*)p, b, fp);
        break;

        case TCompoundStatement_ID:
        b = TCompoundStatement_Print((TCompoundStatement*)p, b, fp);
        break;

        case TIfStatement_ID:
        b = TIfStatement_Print((TIfStatement*)p, b, fp);
        break;

        case TDoStatement_ID:
        TDoStatement_Print((TDoStatement*)p, b, fp);
        break;

        case TReturnStatement_ID:
        TReturnStatement_Print((TReturnStatement*)p, b, fp);
        break;

        default:
        ASSERT(false);
        break;
    }

    return b;
}

bool TBlockItem_Print(TBlockItem *  p, bool b, FILE* fp)
{
    if (p == NULL)
    {
        ASSERT(false);
        return false;
    }

    if (b)
    {
        fprintf(fp, ",");
    }

    switch (p->Type)
    {
        case TStaticAssertDeclaration_ID:
        break;

        case TSwitchStatement_ID:
        fprintf(fp, "{");
        b = TSwitchStatement_Print((TSwitchStatement*)p, false, fp);
        fprintf(fp, "}");
        break;

        case TJumpStatement_ID:
        fprintf(fp, "{");
        b = TJumpStatement_Print((TJumpStatement*)p, false, fp);
        fprintf(fp, "}");
        break;

        case TForStatement_ID:
        fprintf(fp, "{");
        b = TForStatement_Print((TForStatement*)p, false, fp);
        fprintf(fp, "}");
        break;

        case TIfStatement_ID:
        fprintf(fp, "{");
        b = TIfStatement_Print((TIfStatement*)p, false, fp);
        fprintf(fp, "}");
        break;

        case TWhileStatement_ID:
        fprintf(fp, "{");
        b = TWhileStatement_Print((TWhileStatement*)p, b, fp);
        fprintf(fp, "}");
        break;

        case TDoStatement_ID:
        fprintf(fp, "{");
        b = TDoStatement_Print((TDoStatement*)p, false, fp);
        fprintf(fp, "}");
        break;

        case TDeclaration_ID:
        b = TDeclaration_Print((TDeclaration*)p, false, fp);
        break;

        case TLabeledStatement_ID:
        fprintf(fp, "{");
        b = TLabeledStatement_Print((TLabeledStatement*)p, false, fp);
        fprintf(fp, "}");
        break;

        case TCompoundStatement_ID:
        fprintf(fp, "{");
        b = TCompoundStatement_Print((TCompoundStatement*)p, false, fp);
        fprintf(fp, "}");
        break;

        case TExpressionStatement_ID:
        fprintf(fp, "{");
        b = TExpressionStatement_Print((TExpressionStatement*)p, false, fp);
        fprintf(fp, "}");
        break;

        case TReturnStatement_ID:
        fprintf(fp, "{");
        b = TReturnStatement_Print((TReturnStatement*)p, false, fp);
        fprintf(fp, "}");
        break;

        case TAsmStatement_ID:
        fprintf(fp, "{");
        b = TAsmStatement_Print((TAsmStatement*)p, false, fp);
        fprintf(fp, "}");
        break;

        default:
        ASSERT(false);
        break;
    }

    return b;
}

bool TPostfixExpressionCore_Print(TPostfixExpressionCore * p, bool b, FILE* fp)
{
    if (b)
    {
        fprintf(fp, ",");
    }

    fprintf(fp, "\"postfix\":{");
    b = false;

    if (p->pExpressionLeft)
    {
        b = TExpression_Print(p->pExpressionLeft, "l", b, fp);
    }


    switch (p->token)
    {
        case TK_FULL_STOP:
        case TK_ARROW:
        if (b)
        {
            fprintf(fp, ",");
        }

        fprintf(fp, "\"identifier\":\"%s\"", p->Identifier);
        b = true;
        break;

        case TK_LEFT_SQUARE_BRACKET:
        b = TExpression_Print(p->pExpressionRight, "r", b, fp);
        break;

        case TK_LEFT_PARENTHESIS:
        b = TExpression_Print(p->pExpressionRight, "r", b, fp);
        break;

        case TK_PLUSPLUS:
        case TK_MINUSMINUS:
        break;
    }

    if (b)
    {
        fprintf(fp, ",");
    }


    fprintf(fp, "\"op\":\"%s\"", TokenToString(p->token));
    b = true;
    if (p->pNext)
    {
        if (b)
        {
            fprintf(fp, ",");
        }

        fprintf(fp, "\"next\":{");
        b = TPostfixExpressionCore_Print(p->pNext, false, fp);
        fprintf(fp, "}");
    }

    fprintf(fp, "}");
    b = true;
    return b;
}

bool TTypeName_Print(TTypeName *  p, const char* name, bool b, FILE* fp)
{
    fprintf(fp, "\"type\":{");
    //b = TTypeQualifierList_Print(&pTUnaryExpressionOperator->TypeName.Specifiers.TypeQualifiers, false, fp);
    //b = TTypeSpecifier_Print(pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);

    if (b)
    {
        fprintf(fp, ",");
    }

    fprintf(fp, "}");
    return b;
}

bool TExpression_Print(TExpression *  p, const char* name, bool b, FILE* fp)
{
    if (p == NULL)
    {
        //ASSERT(false);
        return b;
    }

    if (b)
    {
        fprintf(fp, ",");
    }

    fprintf(fp, "\"%s\":{", name);
    b = false;

    switch (p->Type)
    {
        CASE(TBinaryExpression) :
            b = TExpression_Print(((TBinaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
        b = TExpression_Print(((TBinaryExpression*)p)->pExpressionRight, "r-expr", b, fp);
        fprintf(fp, ",\"binary\":\"%s\"", TokenToString(((TBinaryExpression*)p)->token));

        //fprintf(fp, "op\"%s\":[", ((TBinaryExpression*)p)->token);
        break;

        CASE(TTernaryExpression) :
            b = TExpression_Print(((TTernaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
        b = TExpression_Print(((TTernaryExpression*)p)->pExpressionMiddle, "m-expr", b, fp);
        b = TExpression_Print(((TTernaryExpression*)p)->pExpressionRight, "r-expr", b, fp);
        fprintf(fp, ",\"ternary\":\"%s\"", TokenToString(((TTernaryExpression*)p)->token));

        //fprintf(fp, "op\"%s\":[", ((TBinaryExpression*)p)->token);
        break;

        CASE(TPrimaryExpressionValue) :
        {
            TPrimaryExpressionValue* pPrimaryExpressionValue =
                (TPrimaryExpressionValue*)p;

            if (pPrimaryExpressionValue->pExpressionOpt != NULL)
            {
                b = TExpression_Print(pPrimaryExpressionValue->pExpressionOpt, "expr", b, fp);
            }
            else
            {

                fprintf(fp, "\"lexeme\":");
                PrintLiteralString(fp, pPrimaryExpressionValue->lexeme);
            }

            b = true;
        }
        break;

        CASE(TPostfixExpressionCore) :
        {
            TPostfixExpressionCore* pPostfixExpressionCore =
                (TPostfixExpressionCore*)p;
            b = TPostfixExpressionCore_Print(pPostfixExpressionCore, b, fp);
        }
        break;

        CASE(TUnaryExpressionOperator) :
        {
            TUnaryExpressionOperator* pTUnaryExpressionOperator =
                (TUnaryExpressionOperator*)p;

            if (pTUnaryExpressionOperator->token == TK_SIZEOF)
            {
                //ttypename_print pTUnaryExpressionOperator->TypeName


                //tem algo?
                if (pTUnaryExpressionOperator->TypeName.SpecifierQualifierList.pHead != NULL)
                {
                    TTypeName_Print(&pTUnaryExpressionOperator->TypeName, "", b, fp);
                    //fprintf(fp, "\"type\":{");
                    //b = TTypeQualifierList_Print(&pTUnaryExpressionOperator->TypeName.Specifiers.TypeQualifiers, false, fp);
                    //b/ = TTypeSpecifier_Print(pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);

                    //if (b)
                    //{
                      //fprintf(fp, ",");
                    //}

                    //fprintf(fp, "\"declarator\":");
                    //b = TDeclarator_Print(&pTUnaryExpressionOperator->TypeName.Declarator, b, fp);

                    //fprintf(fp, "}");
                }
                else
                {
                    b = TExpression_Print(pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);
                }
            }
            else
            {
                b = TExpression_Print(pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);
            }

            fprintf(fp, ",\"unary\":\"%s\"", TokenToString(((TBinaryExpression*)p)->token));
        }
        break;

        CASE(TCastExpressionType) :
        {
            TCastExpressionType * pCastExpressionType =
                (TCastExpressionType*)p;

            b = TExpression_Print(pCastExpressionType->pExpression, "expr", b, fp);


            //fprintf(fp, ",\"cast\":{");
            TTypeName_Print(&pCastExpressionType->TypeName, "cast", b, fp);
            //b = TTypeQualifierList_Print(&pCastExpressionType->TypeName.Specifiers.TypeQualifiers, false, fp);
            //b = TTypeSpecifier_Print(pCastExpressionType->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);

            //if (b)
            //{
              //fprintf(fp, ",");
            //}

            //fprintf(fp, "\"declarator\":");
            //b = TDeclarator_Print(&pCastExpressionType->TypeName.Declarator, b, fp);

            //fprintf(fp, "}");

        }
        break;

        default:

        ASSERT(false);
    }

    fprintf(fp, "}");
    return b;
}


bool TEnumerator_Print(TEnumerator* pTEnumerator, bool b, FILE* fp)
{
    fprintf(fp, "{");
    fprintf(fp, "\"name\":\"%s\"", pTEnumerator->Name);
    //fprintf(fp, ",");
    if (pTEnumerator->pExpression)
    {
        TExpression_Print(pTEnumerator->pExpression, "expr", true, fp);
    }
    else
    {
        //vou criar uma expressionp enum?
    }
    fprintf(fp, "}");
    return true;
}

bool TEnumSpecifier_Print(TEnumSpecifier* p, bool b, FILE* fp)
{
    if (b)
    {
        fprintf(fp, ",");
    }

    b = true;
    fprintf(fp, "\"enum-specifier\": {");
    fprintf(fp, "\"name\":\"%s\",", p->Name);
    fprintf(fp, "\"enumerator-list\":[");

    //for (size_t i = 0; i < p->EnumeratorList.size; i++)
    int i = 0;
    ForEachListItem(TEnumerator, pTEnumerator, &p->EnumeratorList)
    {
        //TEnumerator *pTEnumerator = p->EnumeratorList.pItems[i];

        if (i > 0)
            fprintf(fp, ",");

        TEnumerator_Print(pTEnumerator, false, fp);
        i++;
    }

    fprintf(fp, "]");
    fprintf(fp, "}");
    return true;
}


bool TStructUnionSpecifier_Print(TStructUnionSpecifier* p, bool b, FILE* fp)
{
    if (b)
    {
        fprintf(fp, ",");
    }

    b = true;

    if (p->bIsStruct)
        fprintf(fp, "\"struct-specifier\": {");

    else
        fprintf(fp, "\"union-specifier\": {");

    fprintf(fp, "\"name\":\"%s\",", p->Name);
    //fprintf(fp, "\"isstruct\":%s,", p->bIsStruct ? "true" : "false");
    fprintf(fp, "\"struct-declaration-list\":[");

    for (size_t i = 0; i < p->StructDeclarationList.size; i++)
    {
        TAnyStructDeclaration * pStructDeclaration = p->StructDeclarationList.pItems[i];

        if (i > 0)
            fprintf(fp, ",");

        b = TStructDeclaration_Print(pStructDeclaration, b, fp);
    }

    fprintf(fp, "]");
    fprintf(fp, "}");
    return true;
}

bool TSingleTypeSpecifier_Print(TSingleTypeSpecifier* p, bool b, FILE* fp)
{
    if (b)
    {
        fprintf(fp, ",");
    }

    b = true;
    fprintf(fp, "\"type-specifier\":\"");
    int i = 0;

    if (p->bIsVoid)
    {
        if (i > 0)
            fprintf(fp, " ");

        fprintf(fp, "void");
        i++;
    }

    if (p->bIsUnsigned)
    {
        if (i > 0)
            fprintf(fp, " ");

        fprintf(fp, "unsigned");
        i++;
    }

    if (p->bIsBool)
    {
        if (i > 0)
            fprintf(fp, " ");

        fprintf(fp, "bool");
        i++;
    }

    if (p->bIsChar)
    {
        if (i > 0)
            fprintf(fp, " ");

        fprintf(fp, "char");
        i++;
    }

    if (p->bIsShort)
    {
        if (i > 0)
            fprintf(fp, " ");

        fprintf(fp, "short");
        i++;
    }

    for (int j = 0; j < p->nLong; j++)
    {
        if (i > 0)
            fprintf(fp, " ");

        fprintf(fp, "long");
        i++;
    }

    if (p->bIsInt)
    {
        if (i > 0)
            fprintf(fp, " ");

        fprintf(fp, "int");
        i++;
    }

    if (p->bIsDouble)
    {
        if (i > 0)
            fprintf(fp, " ");

        fprintf(fp, "double");
        i++;
    }

    if (p->bIsFloat)
    {
        if (i > 0)
            fprintf(fp, " ");

        fprintf(fp, "float");
        i++;
    }

    if (p->bIsTypeDef)
    {
        if (i > 0)
            fprintf(fp, " ");

        fprintf(fp, "%s", p->TypedefName);
        i++;
    }

    fprintf(fp, "\"");
    ASSERT(i > 0);
    return b;
}

bool TTypeSpecifier_Print(TTypeSpecifier*  p, bool b, FILE* fp)
{
    if (p == NULL)
    {
        //declaracao vazia: ;
        if (b)
        {
            fprintf(fp, ",");
        }

        fprintf(fp, "\"type-specifier\":null");
        return true;
    }

    switch (p->Type)
    {
        case TStructUnionSpecifier_ID:
        //TStructDeclaration_Print();
        b = TStructUnionSpecifier_Print((TStructUnionSpecifier*)p, b, fp);
        break;

        case TEnumSpecifier_ID:
        b = TEnumSpecifier_Print((TEnumSpecifier*)p, b, fp);
        break;

        case TSingleTypeSpecifier_ID:
        b = TSingleTypeSpecifier_Print((TSingleTypeSpecifier*)p, b, fp);
        break;

        default:
        break;
    }

    return b;
}

bool TDesignator_Print(TDesignator* p, bool b, FILE* fp)
{
    if (b)
        fprintf(fp, ",");

    fprintf(fp, "{");

    //
    if (p->Name)
    {
        //.identifier
        fprintf(fp, "\"member-name\":\"%s\"", p->Name);
    }

    else
    {
        //[constant-expression]
        TExpression_Print(p->pExpression, "index", b, fp);
    }

    fprintf(fp, "}");
    return b;
}

bool TInitializerList_Print(TInitializerList*p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");

    ForEachListItem(TInitializerListItem, pItem, p)

    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");
        b = TInitializerListItem_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}


bool TInitializer_Print(TInitializer* p, bool b, FILE* fp)
{
    if (p == NULL)
    {
        return false;
    }

    switch (p->Type)
    {
        case TPrimaryExpression_ID:
        case TUnaryExpressionOperator_ID:
        case TCastExpressionType_ID:
        case TPrimaryExpressionValue_ID:
        case TPostfixExpressionCore_ID:
        case TBinaryExpression_ID:
        case TTernaryExpression_ID:

        //fprintf(fp, "{");
        b = TExpression_Print((TExpression*)p, "initializer-expression", false, fp);
        //fprintf(fp, "}");
        break;

        case TInitializerListType_ID:
        fprintf(fp, "\"initializer\":");
        b = TInitializerList_Print(&((TInitializerListType*)p)->InitializerList, b, fp);
        break;

        default:
        ASSERT(false);
        break;
    }

    return b;
}


bool TPointerList_Print(TPointerList *p, bool b, FILE* fp)
{
    b = false;


    fprintf(fp, "[");
    int i = 0;
    //for (size_t i = 0; i < p->size; i++)
    ForEachListItem(TPointer, pItem, p)
    {
        if (i > 0)
            fprintf(fp, ",");

        //TPointer * pItem = p->pItems[i];
        b = TPointer_Print(pItem, b, fp);
        i++;
    }

    fprintf(fp, "]");
    b = true;


    return b;
}

bool TParameterList_Print(TParameterList *p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");

    ForEachListItem(TParameterDeclaration, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");

        b = TParameterDeclaration_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}
bool TParameterTypeList_Print(TParameterTypeList *p, bool b, FILE* fp)
{
    return TParameterList_Print(&p->ParameterList, b, fp);
}

bool TStructDeclarator_Print(TStructDeclarator* p, bool b, FILE* fp)
{

    fprintf(fp, "{");
    b = false;

    fprintf(fp, "\"declarator\":");
    b = TDeclarator_Print(p->pDeclarator, b, fp);

    if (p->pInitializer)
    {
        if (b)
        {
            fprintf(fp, ",");
        }
        //fprintf(fp, "\"initializer\":");
        TInitializer_Print(p->pInitializer, b, fp);

    }

    fprintf(fp, "}");
    return true;
}

bool TInitDeclarator_Print(TInitDeclarator* p, bool b, FILE* fp)
{

    fprintf(fp, "{");
    b = false;

    fprintf(fp, "\"declarator\":");
    b = TDeclarator_Print(p->pDeclarator, b, fp);

    if (p->pInitializer)
    {
        if (b)
        {
            fprintf(fp, ",");
        }
        //fprintf(fp, "\"initializer\":");
        TInitializer_Print(p->pInitializer, b, fp);

    }

    fprintf(fp, "}");
    return true;
}

bool TDirectDeclarator_Print(TDirectDeclarator* pDirectDeclarator,
  bool b,
  FILE* fp)
{
    fprintf(fp, "{");
    b = false;

    if (pDirectDeclarator->Identifier)
    {
        //identifier
        fprintf(fp, "\"identifier\":");
        fprintf(fp, "\"%s\"", pDirectDeclarator->Identifier);
        b = true;
    }
    else  if (pDirectDeclarator->pDeclarator)
    {
        //( declarator )
        fprintf(fp, "\"declarator\":");
        b = TDeclarator_Print(pDirectDeclarator->pDeclarator, b, fp);
    }

    if (pDirectDeclarator->pExpression)
    {
        /*
         direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
         direct-declarator [ static type-qualifier-listopt assignment-expression ]
         direct-declarator [ type-qualifier-list static assignment-expression ]
        */
        b = TExpression_Print(pDirectDeclarator->pExpression, "assignment-expression", b, fp);
    }

    if (pDirectDeclarator->Type == TDirectDeclaratorTypeFunction)
    {
        //( parameter-type-list )
        fprintf(fp, ",");
        fprintf(fp, "\"parameter-type-list\":");
        TParameterTypeList_Print(&pDirectDeclarator->Parameters, b, fp);
    }

    if (pDirectDeclarator->pDirectDeclarator)
    {
        if (b)
        {
            fprintf(fp, ",");
        }
        fprintf(fp, "\"direct-declarator\":");
        TDirectDeclarator_Print(pDirectDeclarator->pDirectDeclarator, b, fp);
    }


    fprintf(fp, "}");
    return b;
}

bool TDeclarator_Print(TDeclarator* p, bool b, FILE* fp)
{
    fprintf(fp, "{");
    b = false;

    fprintf(fp, "\"pointer\":");
    b = TPointerList_Print(&p->PointerList, b, fp);

    if (b)
    {
        fprintf(fp, ",");
    }

    if (p->pDirectDeclarator)
    {
        fprintf(fp, "\"direct-declarator\":");
        b = TDirectDeclarator_Print(p->pDirectDeclarator, b, fp);
    }

    fprintf(fp, "}");
    return true;
}

bool TStructDeclaratorList_Print(TStructDeclaratorList *p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");


    ForEachListItem(TInitDeclarator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");
        b = TStructDeclarator_Print(pItem, b, fp);

    }

    fprintf(fp, "]");
    return true;
}

bool TInitDeclaratorList_Print(TInitDeclaratorList *p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");
    ForEachListItem(TInitDeclarator, pInitDeclarator, p)
    {
        if (!List_IsFirstItem(p, pInitDeclarator))
            fprintf(fp, ",");

        b = TInitDeclarator_Print(pInitDeclarator, b, fp);
    }

    fprintf(fp, "]");
    return true;
}

bool SpecifierQualifierList_Print(TSpecifierQualifierList* p, bool b, FILE* fp)
{
    ForEachListItem(TSpecifierQualifier, pItem, p)
    {
        switch (pItem->Type)
        {
            CASE(TStorageSpecifier) :
                StorageSpecifier_Print((TStorageSpecifier*)pItem, b, fp);
                break;
            CASE(TTypeQualifier) :
                TTypeQualifier_Print((TTypeQualifier*)pItem, b, fp);
                break;
            CASE(TFunctionSpecifier) :
                TFunctionSpecifier_Print((TFunctionSpecifier*)pItem, b, fp);
                break;
            //CASE(TAlignmentSpecifier) :
              //  AlignmentSpecifier_Print((TAlignmentSpecifier*)pItem, b, fp);
                //break;

        }
    }
    return b;
}

bool TStructDeclarationBase_Print(TStructDeclaration* p, bool b, FILE* fp)
{
    fprintf(fp, "{");

    SpecifierQualifierList_Print(&p->SpecifierQualifierList, b, fp);
    //b = TTypeQualifierList_Print(&p->Qualifier, false, fp);
    //b = TTypeSpecifier_Print(p->pSpecifier, b, fp);

    if (b)
        fprintf(fp, ",");

    fprintf(fp, "\"declarators\":");
    b = TStructDeclaratorList_Print(&p->DeclaratorList, b, fp);
    fprintf(fp, "}");
    return true;
}

bool TStructDeclaration_Print(TAnyStructDeclaration* p, bool b, FILE* fp)
{
    switch (p->Type)
    {
        case TStructDeclaration_ID:
        b = TStructDeclarationBase_Print((TStructDeclaration*)p, b, fp);
        break;

        default:
        ASSERT(false);
        break;
    }

    return b;
}

bool StorageSpecifier_Print(TStorageSpecifier* p, bool b, FILE* fp)
{
    int i = 0;

    if (p->bIsAuto ||
      p->bIsExtern ||
      p->bIsRegister ||
      p->bIsStatic ||
      p->bIsThread_local ||
      p->bIsTypedef)
    {
        if (b)
        {
            fprintf(fp, ",");
        }

        b = true;
        fprintf(fp, "\"storage-specifers\" : {");

        if (p->bIsAuto)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"auto\":true");
            i++;
        }

        if (p->bIsExtern)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"extern\":true");
            i++;
        }

        if (p->bIsRegister)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"register\":true");
            i++;
        }

        if (p->bIsStatic)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"static\":true");
            i++;
        }

        if (p->bIsThread_local)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"threadlocal\":true");
            i++;
        }

        if (p->bIsTypedef)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"typedef\":true");
            i++;
        }

        fprintf(fp, "}");
    }

    return b;
}

bool TFunctionSpecifier_Print(TFunctionSpecifier* p, bool b, FILE* fp)
{
    int i = 0;

    if (p->bIsInline ||
      p->bIsNoReturn)
    {
        if (b)
        {
            fprintf(fp, ",");
        }

        b = true;
        fprintf(fp, "\"function-specifers\" : {");

        if (p->bIsInline)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"inline\":true");
            i++;
        }

        if (p->bIsNoReturn)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"noreturn\":true");
            i++;
        }

        fprintf(fp, "}");
    }

    return b;
}



bool TTypeQualifier_Print(TTypeQualifier* p, bool b, FILE* fp)
{
    int i = 0;

    if (p->bIsAtomic ||
      p->bIsConst ||
      p->bIsRestrict ||
      p->bIsVolatile)
    {
        if (b)
        {
            fprintf(fp, ",");
        }

        b = true;
        fprintf(fp, "\"qualifiers\" : {");

        if (p->bIsAtomic)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"atomic\":true");
            i++;
        }

        if (p->bIsConst)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"const\":true");
            i++;
        }

        if (p->bIsRestrict)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"restrict\":true");
            i++;
        }

        if (p->bIsVolatile)
        {
            if (i > 0)
                fprintf(fp, ",");

            fprintf(fp, "\"volatile\":true");
            i++;
        }

        fprintf(fp, "}");
    }

    return b;
}

bool TTypeQualifierList_Print(TTypeQualifierList* p, bool b, FILE* fp)
{

    ForEachListItem(TTypeQualifier, pItem, p)
    {
        b = TTypeQualifier_Print(pItem, b, fp);
    }
    return b;
}



bool TPointer_Print(TPointer* pPointer, bool b, FILE* fp)
{
    fprintf(fp, "{");
    TTypeQualifierList_Print(&pPointer->Qualifier, false, fp);
    fprintf(fp, "}");
    return true;
}

bool TDeclarationSpecifiers_Print(TDeclarationSpecifiers* pDeclarationSpecifiers, bool b, FILE* fp)
{

    ForEachListItem(TSpecifier, pItem, pDeclarationSpecifiers)
    {
        switch (pItem->Type)
        {
            CASE(TStorageSpecifier) :
                StorageSpecifier_Print((TStorageSpecifier*)pItem, b, fp);
            break;
            CASE(TTypeQualifier) :
                TTypeQualifier_Print((TTypeQualifier*)pItem, b, fp);
            break;
            CASE(TFunctionSpecifier) :
                TFunctionSpecifier_Print((TFunctionSpecifier*)pItem, b, fp);
            break;
            //CASE(TAlignmentSpecifier) :
            //  AlignmentSpecifier_Print((TAlignmentSpecifier*)pItem, b, fp);
            //break;

        }
    }

    //b = TFunctionSpecifier_Print(&pDeclarationSpecifiers->FunctionSpecifiers, b, fp);
    //b = StorageSpecifier_Print(&pDeclarationSpecifiers->StorageSpecifiers, b, fp);
    //b = TTypeQualifierList_Print(&pDeclarationSpecifiers->TypeQualifiers, b, fp);
    //b/ = TTypeSpecifier_Print(pDeclarationSpecifiers->pTypeSpecifierOpt, b, fp);
    return b;
}

bool TDeclaration_Print(TDeclaration* p, bool b, FILE* fp)
{
    fprintf(fp, "{");
    b = TDeclarationSpecifiers_Print(&p->Specifiers, false, fp);

    if (b)
        fprintf(fp, ",");

    fprintf(fp, "\"init-declarator-list\":");
    b = TInitDeclaratorList_Print(&p->InitDeclaratorList, b, fp);

    if (p->pCompoundStatementOpt != NULL)
    {
        TCompoundStatement_Print(p->pCompoundStatementOpt, b, fp);
    }

    fprintf(fp, "}");
    return true;
}


bool TParameterDeclaration_Print(TParameterDeclaration* p, bool b, FILE* fp)
{
    fprintf(fp, "{");
    b = TDeclarationSpecifiers_Print(&p->Specifiers, false, fp);
    fprintf(fp, ",");
    fprintf(fp, "\"declarator\":");
    b = TDeclarator_Print(&p->Declarator, b, fp);
    fprintf(fp, "}");
    return b;
}

bool TAnyDeclaration_Print(TAnyDeclaration *pDeclaration, bool b, FILE* fp)
{
    switch (pDeclaration->Type)
    {
        case TStaticAssertDeclaration_ID:
        break;

        case TDeclaration_ID:
        b = TDeclaration_Print((TDeclaration*)pDeclaration, b, fp);
        break;

        default:
        ASSERT(false);
        break;
    }

    return b;
}

bool TDesignatorList_Print(TDesignatorList *p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");


    ForEachListItem(TDesignator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");

        b = TDesignator_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}


bool TInitializerListItem_Print(TInitializerListItem* p, bool b, FILE* fp)
{
    fprintf(fp, "{");
    b = false;

    if (!List_IsEmpty(&p->DesignatorList))
    {
        fprintf(fp, "\"designation\":");
        b = TDesignatorList_Print(&p->DesignatorList, b, fp);
    }

    if (b)
        fprintf(fp, ",");

    if (p->pInitializer)
    {
        fprintf(fp, "\"initializer\":");
        b = TInitializer_Print(p->pInitializer, b, fp);
    }
    fprintf(fp, "}");
    return true;
}


bool TDeclarations_Print(TDeclarations *p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");

    for (size_t i = 0; i < p->size; i++)
    {
        if (i > 0)
            fprintf(fp, ",");

        TAnyDeclaration* pItem = p->pItems[i];
        b = TAnyDeclaration_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}


void TProgram_PrintAstToFile(TProgram* pProgram,
  const char* fileName,
  const char* inputFileName)
{
    FILE * fp = fopen(fileName, "w");
    //TDeclarations_Print(&pProgram->Declarations, false, fp);


    bool b = false;
    fprintf(fp, "[");

    for (size_t i = 0; i < pProgram->Declarations.size; i++)
    {
        TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];
        if (b)
            fprintf(fp, ",");
        b = TAnyDeclaration_Print(pItem, b, fp);

    }

    fprintf(fp, "]");

    fclose(fp);
}






