#include "Ast.h"
#include "Array.h"
#include "Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "AstPrint.h"

bool TFunctionSpecifier_Print(struct TFunctionSpecifier* p, bool b, FILE* fp);
bool StorageSpecifier_Print(struct TStorageSpecifier* p, bool b, FILE* fp);
bool TTypeQualifierList_Print(struct TTypeQualifierList* p, bool b, FILE* fp);
bool TDeclarator_Print(struct TDeclarator* p, bool b, FILE* fp);
bool TAnyDeclaration_Print(struct TAnyDeclaration* pDeclaration, bool b, FILE* fp);
bool TTypeSpecifier_Print(struct TTypeSpecifier* p, bool b, FILE* fp);
bool TStructDeclaration_Print(struct TAnyStructDeclaration* p, bool b, FILE* fp);
bool TTypeQualifier_Print(struct TTypeQualifier* p, bool b, FILE* fp);
bool TDeclaration_Print(struct TDeclaration* p, bool b, FILE* fp);
bool TExpression_Print(struct TExpression* p, const char* name, bool b, FILE* fp);
bool TStatement_Print(struct TStatement* p, bool b, FILE* fp);
bool TBlockItem_Print(struct TBlockItem* p, bool b, FILE* fp);
bool TInitializer_Print(struct TInitializer* p, bool b, FILE* fp);
bool TPointer_Print(struct TPointer* pPointer, bool b, FILE* fp);
bool TParameter_Print(struct TParameter* p, bool b, FILE* fp);
bool TInitializerListItem_Print(struct TInitializerListItem* p, bool b, FILE* fp);

bool TCompoundStatement_Print(struct TCompoundStatement* p, bool b, FILE* fp)
{
    if (b)
    {
        fprintf(fp, ",");
    }

    b = true;
    fprintf(fp, "\"compound-statement\": [");

    for (int j = 0; j < p->BlockItemList.Size; j++)
    {
        struct TBlockItem* pBlockItem = p->BlockItemList.pItems[j];
        TBlockItem_Print(pBlockItem, j > 0, fp);
    }

    fprintf(fp, "]");
    return b;
}


bool TLabeledStatement_Print(struct TLabeledStatement* p, bool b, FILE* fp)
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

bool TForStatement_Print(struct TForStatement* p, bool b, FILE* fp)
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


bool TWhileStatement_Print(struct TWhileStatement* p, bool b, FILE* fp)
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


bool TDoStatement_Print(struct TDoStatement* p, bool b, FILE* fp)
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

bool TExpressionStatement_Print(struct TExpressionStatement* p, bool b, FILE* fp)
{
    TExpression_Print(p->pExpression, "expression-statement", b, fp);
    //fprintf(fp, ",");
    //TExpression_Print(&p->Expression, false, fp);
    //fprintf(fp, "}");
    return true;
}


bool TJumpStatement_Print(struct TJumpStatement* p, bool b, FILE* fp)
{
    fprintf(fp, "\"type\":\"jump-statement\"");
    //fprintf(fp, ",");
    //fprintf(fp, "\"statement\": {");
    b = TExpression_Print(p->pExpression, "statement", false, fp);
    //fprintf(fp, "}");
    return true;
}

bool TAsmStatement_Print(struct TAsmStatement* p, bool b, FILE* fp)
{
    fprintf(fp, "\"type\":\"asm-statement\"");
    return true;
}

bool TSwitchStatement_Print(struct TSwitchStatement* p, bool b, FILE* fp)
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


bool TIfStatement_Print(struct TIfStatement* p, bool b, FILE* fp)
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

bool TStatement_Print(struct TStatement* p, bool b, FILE* fp)
{
    if (p == NULL)
    {
        return false;
    }

    switch (p->Type)
    {
        case TExpressionStatement_ID:
            b = TExpressionStatement_Print((struct TExpressionStatement*)p, b, fp);
            break;

        case TSwitchStatement_ID:
            b = TSwitchStatement_Print((struct TSwitchStatement*)p, b, fp);
            break;

        case TLabeledStatement_ID:
            b = TLabeledStatement_Print((struct TLabeledStatement*)p, b, fp);
            break;

        case TForStatement_ID:
            b = TForStatement_Print((struct TForStatement*)p, b, fp);
            break;

        case TJumpStatement_ID:
            b = TJumpStatement_Print((struct TJumpStatement*)p, b, fp);
            break;

        case TAsmStatement_ID:
            b = TAsmStatement_Print((struct TAsmStatement*)p, b, fp);
            break;

        case TCompoundStatement_ID:
            b = TCompoundStatement_Print((struct TCompoundStatement*)p, b, fp);
            break;

        case TIfStatement_ID:
            b = TIfStatement_Print((struct TIfStatement*)p, b, fp);
            break;

        case TDoStatement_ID:
            TDoStatement_Print((struct TDoStatement*)p, b, fp);
            break;

        default:
            //assert(false);
            break;
    }

    return b;
}

bool TBlockItem_Print(struct TBlockItem* p, bool b, FILE* fp)
{
    if (p == NULL)
    {
        //assert(false);
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
            b = TSwitchStatement_Print((struct TSwitchStatement*)p, false, fp);
            fprintf(fp, "}");
            break;

        case TJumpStatement_ID:
            fprintf(fp, "{");
            b = TJumpStatement_Print((struct TJumpStatement*)p, false, fp);
            fprintf(fp, "}");
            break;

        case TForStatement_ID:
            fprintf(fp, "{");
            b = TForStatement_Print((struct TForStatement*)p, false, fp);
            fprintf(fp, "}");
            break;

        case TIfStatement_ID:
            fprintf(fp, "{");
            b = TIfStatement_Print((struct TIfStatement*)p, false, fp);
            fprintf(fp, "}");
            break;

        case TWhileStatement_ID:
            fprintf(fp, "{");
            b = TWhileStatement_Print((struct TWhileStatement*)p, b, fp);
            fprintf(fp, "}");
            break;

        case TDoStatement_ID:
            fprintf(fp, "{");
            b = TDoStatement_Print((struct TDoStatement*)p, false, fp);
            fprintf(fp, "}");
            break;

        case TDeclaration_ID:
            b = TDeclaration_Print((struct TDeclaration*)p, false, fp);
            break;

        case TLabeledStatement_ID:
            fprintf(fp, "{");
            b = TLabeledStatement_Print((struct TLabeledStatement*)p, false, fp);
            fprintf(fp, "}");
            break;

        case TCompoundStatement_ID:
            fprintf(fp, "{");
            b = TCompoundStatement_Print((struct TCompoundStatement*)p, false, fp);
            fprintf(fp, "}");
            break;

        case TExpressionStatement_ID:
            fprintf(fp, "{");
            b = TExpressionStatement_Print((struct TExpressionStatement*)p, false, fp);
            fprintf(fp, "}");
            break;

        case TAsmStatement_ID:
            fprintf(fp, "{");
            b = TAsmStatement_Print((struct TAsmStatement*)p, false, fp);
            fprintf(fp, "}");
            break;

        default:
            //assert(false);
            break;
    }

    return b;
}

bool TPostfixExpressionCore_Print(struct TPostfixExpressionCore* p, bool b, FILE* fp)
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
        default:
            //assert(false);
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

bool TTypeName_Print(struct TTypeName* p, const char* name, bool b, FILE* fp)
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

bool TExpression_Print(struct TExpression* p, const char* name, bool b, FILE* fp)
{
    if (p == NULL)
    {
        ////assert(false);
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
        case TBinaryExpression_ID:
            b = TExpression_Print(((struct TBinaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
        b = TExpression_Print(((struct TBinaryExpression*)p)->pExpressionRight, "r-expr", b, fp);
        fprintf(fp, ",\"binary\":\"%s\"", TokenToString(((struct TBinaryExpression*)p)->token));

        //fprintf(fp, "op\"%s\":[", ((struct TBinaryExpression*)p)->token);
        break;

        case TTernaryExpression_ID:
            b = TExpression_Print(((struct TTernaryExpression*)p)->pExpressionLeft, "l-expr", b, fp);
        b = TExpression_Print(((struct TTernaryExpression*)p)->pExpressionMiddle, "m-expr", b, fp);
        b = TExpression_Print(((struct TTernaryExpression*)p)->pExpressionRight, "r-expr", b, fp);
        fprintf(fp, ",\"ternary\":\"%s\"", TokenToString(((struct TTernaryExpression*)p)->token));

        //fprintf(fp, "op\"%s\":[", ((struct TBinaryExpression*)p)->token);
        break;

        case TPrimaryExpressionValue_ID:
        {
            struct TPrimaryExpressionValue* pPrimaryExpressionValue =
                (struct TPrimaryExpressionValue*)p;

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

        case TPostfixExpressionCore_ID:
        {
            struct TPostfixExpressionCore* pPostfixExpressionCore =
                (struct TPostfixExpressionCore*)p;
            b = TPostfixExpressionCore_Print(pPostfixExpressionCore, b, fp);
        }
        break;

        case TUnaryExpressionOperator_ID:
        {
            struct TUnaryExpressionOperator* pTUnaryExpressionOperator =
                (struct TUnaryExpressionOperator*)p;

            if (pTUnaryExpressionOperator->token == TK_SIZEOF)
            {
                //ttypename_print pTUnaryExpressionOperator->TypeName


                //tem algo?
                if (pTUnaryExpressionOperator->TypeName.SpecifierQualifierList.Size > 0)
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
                    b = TExpression_Print(pTUnaryExpressionOperator->pExpressionRight, "expr", b, fp);
                }
            }
            else
            {
                b = TExpression_Print(pTUnaryExpressionOperator->pExpressionRight, "expr", b, fp);
            }

            fprintf(fp, ",\"unary\":\"%s\"", TokenToString(((struct TBinaryExpression*)p)->token));
        }
        break;

        case TCastExpressionType_ID:
        {
            struct TCastExpressionType* pCastExpressionType =
                (struct TCastExpressionType*)p;

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

            //assert(false);
            break;
    }

    fprintf(fp, "}");
    return b;
}


bool TEnumerator_Print(struct TEnumerator* pTEnumerator, bool b, FILE* fp)
{
    fprintf(fp, "{");
    fprintf(fp, "\"name\":\"%s\"", pTEnumerator->Name);
    //fprintf(fp, ",");
    if (pTEnumerator->pConstantExpression)
    {
        TExpression_Print(pTEnumerator->pConstantExpression, "expr", true, fp);
    }
    else
    {
        //vou criar uma expressionp enum?
    }
    fprintf(fp, "}");
    return true;
}

bool TEnumSpecifier_Print(struct TEnumSpecifier* p, bool b, FILE* fp)
{
    if (b)
    {
        fprintf(fp, ",");
    }

    b = true;
    fprintf(fp, "\"enum-specifier\": {");
    fprintf(fp, "\"name\":\"%s\",", p->Tag);
    fprintf(fp, "\"enumerator-list\":[");

    //for (int i = 0; i < p->EnumeratorList.size; i++)
    int i = 0;
    ForEachListItem(struct TEnumerator, pTEnumerator, &p->EnumeratorList)
    {
        //struct TEnumerator *pTEnumerator = p->EnumeratorList.pItems[i];

        if (i > 0)
            fprintf(fp, ",");

        TEnumerator_Print(pTEnumerator, false, fp);
        i++;
    }

    fprintf(fp, "]");
    fprintf(fp, "}");
    return true;
}


bool TStructUnionSpecifier_Print(struct TStructUnionSpecifier* p, bool b, FILE* fp)
{
    b = true;
    fprintf(fp, "{");
    if (p->Token == TK_STRUCT)
        fprintf(fp, "\"type:\":\"struct-specifier\",");
    else if (p->Token == TK_UNION)
        fprintf(fp, "\"type:\":\"union-specifier\",");

    fprintf(fp, "\"name\":\"%s\",", p->Tag);

    fprintf(fp, "\"struct-declaration-list\":[");

    for (int i = 0; i < p->StructDeclarationList.Size; i++)
    {
        struct TAnyStructDeclaration* pStructDeclaration = p->StructDeclarationList.pItems[i];

        if (i > 0)
            fprintf(fp, ",");

        b = TStructDeclaration_Print(pStructDeclaration, b, fp);
    }

    fprintf(fp, "]");
    fprintf(fp, "}");

    return true;
}

bool TSingleTypeSpecifier_Print(struct TSingleTypeSpecifier* p, bool b, FILE* fp)
{
    fprintf(fp, "{");
    b = true;
    fprintf(fp, "\"type\":\"type-specifier\",");
    fprintf(fp, "\"lexeme\":");

    fprintf(fp, "\"");

    if (p->Token2 == TK_IDENTIFIER)
    {
        fprintf(fp, "%s", p->TypedefName);
    }
    else
    {
        fprintf(fp, "%s", TokenToString(p->Token2));
    }

    fprintf(fp, "\"");

    fprintf(fp, "}");

    return b;
}

bool TTypeSpecifier_Print(struct TTypeSpecifier* p, bool b, FILE* fp)
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
            b = TStructUnionSpecifier_Print((struct TStructUnionSpecifier*)p, b, fp);
            break;

        case TEnumSpecifier_ID:
            b = TEnumSpecifier_Print((struct TEnumSpecifier*)p, b, fp);
            break;

        case TSingleTypeSpecifier_ID:
            b = TSingleTypeSpecifier_Print((struct TSingleTypeSpecifier*)p, b, fp);
            break;

        default:
            break;
    }

    return b;
}

bool TDesignator_Print(struct TDesignator* p, bool b, FILE* fp)
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

bool TInitializerList_Print(struct TInitializerList* p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");

    ForEachListItem(struct TInitializerListItem, pItem, p)

    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");
        b = TInitializerListItem_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}


bool TInitializer_Print(struct TInitializer* p, bool b, FILE* fp)
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
            b = TExpression_Print((struct TExpression*)p, "initializer-expression", false, fp);
            //fprintf(fp, "}");
            break;

        case TInitializerListType_ID:
            fprintf(fp, "\"initializer\":");
            b = TInitializerList_Print(&((struct TInitializerListType*)p)->InitializerList, b, fp);
            break;

        default:
            //assert(false);
            break;
    }

    return b;
}


bool TPointerList_Print(struct TPointerList* p, bool b, FILE* fp)
{
    b = false;


    fprintf(fp, "[");
    int i = 0;
    //for (int i = 0; i < p->size; i++)
    ForEachListItem(struct TPointer, pItem, p)
    {
        if (i > 0)
            fprintf(fp, ",");

        //struct TPointer * pItem = p->pItems[i];
        b = TPointer_Print(pItem, b, fp);
        i++;
    }

    fprintf(fp, "]");
    b = true;


    return b;
}

bool TParameterList_Print(struct TParameterList* p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");

    ForEachListItem(struct TParameter, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");

        b = TParameter_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}
bool TParameterTypeList_Print(struct TParameterTypeList* p, bool b, FILE* fp)
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

bool TInitDeclarator_Print(struct TInitDeclarator* p, bool b, FILE* fp)
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

bool TDirectDeclarator_Print(struct TDirectDeclarator* pDirectDeclarator,
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

    if (pDirectDeclarator->DeclaratorType == TDirectDeclaratorTypeFunction)
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

bool TDeclarator_Print(struct TDeclarator* p, bool b, FILE* fp)
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

bool TStructDeclaratorList_Print(struct TStructDeclaratorList* p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");


    ForEachListItem(struct TInitDeclarator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");
        b = TStructDeclarator_Print(pItem, b, fp);

    }

    fprintf(fp, "]");
    return true;
}

bool TInitDeclaratorList_Print(struct TInitDeclaratorList* p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");
    ForEachListItem(struct TInitDeclarator, pInitDeclarator, p)
    {
        if (!List_IsFirstItem(p, pInitDeclarator))
            fprintf(fp, ",");

        b = TInitDeclarator_Print(pInitDeclarator, b, fp);
    }

    fprintf(fp, "]");
    return true;
}

bool SpecifierQualifier_Print(struct TSpecifierQualifier* pItem, bool b, FILE* fp)
{
    switch (pItem->Type)
    {
        case TStorageSpecifier_ID:
            b = StorageSpecifier_Print((struct TStorageSpecifier*)pItem, b, fp);
        break;
        case TTypeQualifier_ID:
            b = TTypeQualifier_Print((struct TTypeQualifier*)pItem, b, fp);
        break;
        case TFunctionSpecifier_ID:
            b = TFunctionSpecifier_Print((struct TFunctionSpecifier*)pItem, b, fp);
        break;

        case TSingleTypeSpecifier_ID:
            b = TSingleTypeSpecifier_Print((struct TSingleTypeSpecifier*)pItem, b, fp);
        break;

        case TStructUnionSpecifier_ID:
            b = TStructUnionSpecifier_Print((struct TStructUnionSpecifier*)pItem, b, fp);
        break;

        case TEnumSpecifier_ID:
            b = TEnumSpecifier_Print((struct TEnumSpecifier*)pItem, b, fp);
        break;

        //case TAlignmentSpecifier_ID:
        //  AlignmentSpecifier_Print((struct TAlignmentSpecifier*)pItem, b, fp);
        //break;
        default:
            //assert(false);
            break;
    }
    return b;
}
bool SpecifierQualifierList_Print(struct TSpecifierQualifierList* p, bool b, FILE* fp)
{
    fprintf(fp, "\"specifier-qualifier-list\" : [");
    for (int i = 0; i < p->Size; i++)
    {
        struct TSpecifierQualifier* pItem = p->pData[i];
        if (b)
            fprintf(fp, ",");

        b = SpecifierQualifier_Print(pItem, b, fp);
    }
    fprintf(fp, "]");
    return b;
}

bool TStructDeclarationBase_Print(struct TStructDeclaration* p, bool b, FILE* fp)
{
    fprintf(fp, "{");

    b = SpecifierQualifierList_Print(&p->SpecifierQualifierList, false, fp);
    //b = TTypeQualifierList_Print(&p->Qualifier, false, fp);
    //b = TTypeSpecifier_Print(p->pSpecifier, b, fp);

    if (b)
        fprintf(fp, ",");

    fprintf(fp, "\"declarators\":");
    b = TStructDeclaratorList_Print(&p->DeclaratorList, b, fp);
    fprintf(fp, "}");
    return true;
}

bool TStructDeclaration_Print(struct TAnyStructDeclaration* p, bool b, FILE* fp)
{
    switch (p->Type)
    {
        case TStructDeclaration_ID:
            b = TStructDeclarationBase_Print((struct TStructDeclaration*)p, b, fp);
            break;

        default:
            //assert(false);
            break;
    }

    return b;
}

bool StorageSpecifier_Print(struct TStorageSpecifier* p, bool b, FILE* fp)
{
    b = true;
    fprintf(fp, "{");
    fprintf(fp, "\"type\":\"storage-specifer\",");
    fprintf(fp, "\"lexeme\":\"");

    fprintf(fp, TokenToString(p->Token));

    fprintf(fp, "\"}");

    return b;
}

bool TFunctionSpecifier_Print(struct TFunctionSpecifier* p, bool b, FILE* fp)
{
    int i = 0;


    if (b)
    {
        fprintf(fp, ",");
    }

    b = true;
    fprintf(fp, "\"function-specifers\" : {");

    if (p->Token == TK_INLINE)
    {
        if (i > 0)
            fprintf(fp, ",");

        fprintf(fp, "\"inline\":true");
        i++;
    }

    if (p->Token == TK__NORETURN)
    {
        if (i > 0)
            fprintf(fp, ",");

        fprintf(fp, "\"noreturn\":true");
        i++;
    }




    fprintf(fp, "\"}");
    return b;
}



bool TTypeQualifier_Print(struct TTypeQualifier* p, bool b, FILE* fp)
{
    fprintf(fp, "{");
    fprintf(fp, "\"type\": \"type-qualifier\",");
    fprintf(fp, "\"lexeme\": \"");


    fprintf(fp, "%s", TokenToString(p->Token));


    fprintf(fp, "\"}");

    return true;
}

bool TTypeQualifierList_Print(struct TTypeQualifierList* p, bool b, FILE* fp)
{
    fprintf(fp, "\"type-qualifier-list\":[");
    b = false;
    for (int i = 0; i < p->Size; i++)
    {
        struct TTypeQualifier* pItem = p->Data[i];

        if (b)
        {
            fprintf(fp, ",");
        }
        b = TTypeQualifier_Print(pItem, b, fp);
    }
    fprintf(fp, "]");
    return b;
}



bool TPointer_Print(struct TPointer* pPointer, bool b, FILE* fp)
{
    fprintf(fp, "{");
    TTypeQualifierList_Print(&pPointer->Qualifier, false, fp);
    fprintf(fp, "}");
    return true;
}

bool TDeclarationSpecifier_Print(struct TDeclarationSpecifier* pItem, bool b, FILE* fp)
{
    switch (pItem->Type)
    {
        case TStorageSpecifier_ID:
            b = StorageSpecifier_Print((struct TStorageSpecifier*)pItem, b, fp);
        break;
        case TTypeQualifier_ID:
            b = TTypeQualifier_Print((struct TTypeQualifier*)pItem, b, fp);
        break;

        case TFunctionSpecifier_ID:
            b = TFunctionSpecifier_Print((struct TFunctionSpecifier*)pItem, b, fp);
        break;

        case TSingleTypeSpecifier_ID:
            b = TSingleTypeSpecifier_Print((struct TSingleTypeSpecifier*)pItem, b, fp);
        break;

        case TStructUnionSpecifier_ID:
            b = TStructUnionSpecifier_Print((struct TStructUnionSpecifier*)pItem, b, fp);
        break;

        case TEnumSpecifier_ID:
            b = TEnumSpecifier_Print((struct TEnumSpecifier*)pItem, b, fp);
        break;

        default:
            //assert(false);
            break;
            //case TAlignmentSpecifier_ID:
            //  AlignmentSpecifier_Print((struct TAlignmentSpecifier*)pItem, b, fp);
            //break;

    }
    return b;
}
bool TDeclarationSpecifiers_Print(struct TDeclarationSpecifiers* pDeclarationSpecifiers, bool b, FILE* fp)
{
    fprintf(fp, "\"declarations-specifiers\": [");
    b = false;

    for (int i = 0; i < pDeclarationSpecifiers->Size; i++)
    {
        struct TDeclarationSpecifier* pItem = pDeclarationSpecifiers->pData[i];


        if (b)
        {
            fprintf(fp, ",");
        }
        b = TDeclarationSpecifier_Print(pItem, b, fp);
    }
    fprintf(fp, "]");
    //b = TFunctionSpecifier_Print(&pDeclarationSpecifiers->FunctionSpecifiers, b, fp);
    //b = StorageSpecifier_Print(&pDeclarationSpecifiers->StorageSpecifiers, b, fp);
    //b = TTypeQualifierList_Print(&pDeclarationSpecifiers->TypeQualifiers, b, fp);
    //b/ = TTypeSpecifier_Print(pDeclarationSpecifiers->pTypeSpecifierOpt, b, fp);
    return b;
}

bool TDeclaration_Print(struct TDeclaration* p, bool b, FILE* fp)
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


bool TParameter_Print(struct TParameter* p, bool b, FILE* fp)
{
    fprintf(fp, "{");
    b = TDeclarationSpecifiers_Print(&p->Specifiers, false, fp);
    fprintf(fp, ",");
    fprintf(fp, "\"declarator\":");
    b = TDeclarator_Print(&p->Declarator, b, fp);
    fprintf(fp, "}");
    return b;
}

bool TAnyDeclaration_Print(struct TAnyDeclaration* pDeclaration, bool b, FILE* fp)
{
    switch (pDeclaration->Type)
    {
        case TEofDeclaration_ID:
            break;

        case TStaticAssertDeclaration_ID:
            break;

        case TDeclaration_ID:
            b = TDeclaration_Print((struct TDeclaration*)pDeclaration, b, fp);
            break;

        default:
            //assert(false);
            break;
    }

    return b;
}

bool TDesignatorList_Print(struct TDesignatorList* p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");


    ForEachListItem(struct TDesignator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
            fprintf(fp, ",");

        b = TDesignator_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}


bool TInitializerListItem_Print(struct TInitializerListItem* p, bool b, FILE* fp)
{
    fprintf(fp, "{");
    b = false;

    if (p->DesignatorList.pHead)
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


bool TDeclarations_Print(struct TDeclarations* p, bool b, FILE* fp)
{
    b = false;
    fprintf(fp, "[");

    for (int i = 0; i < p->Size; i++)
    {
        if (i > 0)
            fprintf(fp, ",");

        struct TAnyDeclaration* pItem = p->pItems[i];
        b = TAnyDeclaration_Print(pItem, b, fp);
    }

    fprintf(fp, "]");
    return true;
}


void SyntaxTree_PrintAstToFile(struct SyntaxTree* pProgram,
                               const char* fileName,
                               const char* inputFileName)
{
    FILE* fp = fopen(fileName, "w");
    //TDeclarations_Print(&pProgram->Declarations, false, fp);


    bool b = false;
    fprintf(fp, "[");

    for (int i = 0; i < pProgram->Declarations.Size; i++)
    {
        struct TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];
        if (b)
            fprintf(fp, ",");
        b = TAnyDeclaration_Print(pItem, b, fp);

    }

    fprintf(fp, "]");

    fclose(fp);
}






