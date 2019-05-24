#include "AstPrint2.h"
#include "List.h"

struct PrintXMLContext
{
    FILE* fp;
};


void PrintText(struct PrintXMLContext* ctx, const char* text)
{
    while (*text)
    {
        switch (*text)
        {
        case '&':
            fprintf(ctx->fp, "&amp;");
            break;
        case '<':
            fprintf(ctx->fp, "&lt;");
            break;
        case '>':
            fprintf(ctx->fp, "&gt;");
            break;
        case '\'':
            fprintf(ctx->fp, "&apos;");
            break;
        case '"':
            fprintf(ctx->fp, "&quot;");
            break;
        default:
            fprintf(ctx->fp, "%c", *text);
            break;
        }
        text++;
    }

}

void Print(struct PrintXMLContext* ctx, const char* format, ...)
{
    va_list argList;

    va_start(argList, format);
    vfprintf(ctx->fp, format, argList);
    va_end(argList);
}

void PrintLn(struct PrintXMLContext* ctx, const char* format, ...)
{
    va_list argList;

    va_start(argList, format);
    vfprintf(ctx->fp, format, argList);
    va_end(argList);


    fprintf(ctx->fp, "\n");
}
void TDeclarator_PrintXML(TDeclarator* p,
    struct PrintXMLContext* ctx);

void TDeclarationSpecifiers_PrintXML(TDeclarationSpecifiers* p,
    struct PrintXMLContext* ctx);

void TStructDeclaration_PrintXML(TStructDeclaration* p, struct PrintXMLContext* ctx);

void TAnyStructDeclaration_PrintXML(TAnyStructDeclaration* p, struct PrintXMLContext* ctx);
void TTypeQualifier_PrintXML(TTypeQualifier* p, struct PrintXMLContext* ctx);


int HasItemsToPrint(TScannerItemList* list)
{
    /* ScannerItem* pCurrent = list->pHead;
     while (pCurrent)
     {
         switch (pCurrent->token)
         {
         case TK_PRE_INCLUDE:
         case TK_MACRO_CALL:
         case TK_FILE_EOF:
         case TK_MACRO_EOF:
             return 1;
         default:
             break;
         }
         pCurrent = pCurrent->pNext;
     }*/
    return 0;
}

void TScannerItemList_PrintXML(TScannerItemList* list,
    struct PrintXMLContext* ctx)
{

    if (HasItemsToPrint(list))
    {
        PrintLn(ctx, "<pr>");
        ScannerItem* pCurrent = list->pHead;
        while (pCurrent)
        {
            const char* name = TokenToString(pCurrent->token);
            switch (pCurrent->token)
            {
            case TK_PRE_INCLUDE:
                PrintLn(ctx, "<%s>", name);
                PrintText(ctx, pCurrent->lexeme.c_str);
                PrintLn(ctx, "</%s>", name);
                break;
            case TK_MACRO_CALL:
                PrintLn(ctx, "<%s>", name);
                PrintText(ctx, pCurrent->lexeme.c_str);
                PrintLn(ctx, "</%s>", name);
                break;
            case TK_FILE_EOF:
                PrintLn(ctx, "<TK_FILE_EOF/>");
                break;
            case TK_MACRO_EOF:
                PrintLn(ctx, "<TK_MACRO_EOF/>");
                break;
                //case TK_BREAKLINE:
                  //  PrintLn(ctx, "<BR/>");
                    //break;
            default:
                //PrintLn(ctx, "<TK>%s</TK>", pCurrent->lexeme.c_str);
                break;
            }
            pCurrent = pCurrent->pNext;
        }
        PrintLn(ctx, "</pr>");
    }
}

void TBinaryExpression_PrintXML(TBinaryExpression* p, struct PrintXMLContext* ctx)
{
}

void TPrimaryExpressionLambda_PrintXML(TPrimaryExpressionLambda* p, struct PrintXMLContext* ctx)
{
}
void TUnaryExpressionOperator_PrintXML(TUnaryExpressionOperator* p, struct PrintXMLContext* ctx)
{
}
void TCastExpressionType_PrintXML(TCastExpressionType* p, struct PrintXMLContext* ctx)
{
}
void TPrimaryExpressionValue_PrintXML(TPrimaryExpressionValue* p, struct PrintXMLContext* ctx)
{
}

void TPostfixExpressionCore_PrintXML(TPostfixExpressionCore* p, struct PrintXMLContext* ctx)
{
}

void TPrimaryExpressionLiteral_PrintXML(TPrimaryExpressionLiteral* p, struct PrintXMLContext* ctx)
{
}

void TTernaryExpression_PrintXML(TTernaryExpression* p, struct PrintXMLContext* ctx)
{
}

void TExpression_PrintXML(TExpression* p, struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
    case TBinaryExpression_ID:
        TBinaryExpression_PrintXML((TBinaryExpression*)p, ctx);
        break;
    case TPrimaryExpressionLambda_ID:
        TPrimaryExpressionLambda_PrintXML((TPrimaryExpressionLambda*)p, ctx);
        break;
    case TUnaryExpressionOperator_ID:
        TUnaryExpressionOperator_PrintXML((TUnaryExpressionOperator*)p, ctx);
        break;
    case TCastExpressionType_ID:
        TCastExpressionType_PrintXML((TCastExpressionType*)p, ctx);
        break;
    case TPrimaryExpressionValue_ID:
        TPrimaryExpressionValue_PrintXML((TPrimaryExpressionValue*)p, ctx);
        break;
    case TPostfixExpressionCore_ID:
        TPostfixExpressionCore_PrintXML((TPostfixExpressionCore*)p, ctx);
        break;
    case TPrimaryExpressionLiteral_ID:
        TPrimaryExpressionLiteral_PrintXML((TPrimaryExpressionLiteral*)p, ctx);
        break;
    case TTernaryExpression_ID:
        TTernaryExpression_PrintXML((TTernaryExpression*)p, ctx);
        break;
    default:
        break;
    }
}

void TForStatement_PrintXML(TForStatement* p, struct PrintXMLContext* ctx)
{
}

void TJumpStatement_PrintXML(TJumpStatement* p, struct PrintXMLContext* ctx)
{
}


void TExpressionStatement_PrintXML(TExpressionStatement* p, struct PrintXMLContext* ctx)
{
}


void TIfStatement_PrintXML(TIfStatement* p, struct PrintXMLContext* ctx)
{
}


void TWhileStatement_PrintXML(TWhileStatement* p, struct PrintXMLContext* ctx)
{
}


void TSwitchStatement_PrintXML(TSwitchStatement* p, struct PrintXMLContext* ctx)
{
}


void TAsmStatement_PrintXML(TAsmStatement* p, struct PrintXMLContext* ctx)
{
}


void TDoStatement_PrintXML(TDoStatement* p, struct PrintXMLContext* ctx)
{
}


void TLabeledStatement_PrintXML(TLabeledStatement* p, struct PrintXMLContext* ctx)
{
}

void TCompoundStatement_PrintXML(TCompoundStatement* p, struct PrintXMLContext* ctx)
{
}

void TStatement_PrintXML(TStatement* p, struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
    case TForStatement_ID:
        TForStatement_PrintXML((TForStatement*)p, ctx);
        break;
    case TJumpStatement_ID:
        TJumpStatement_PrintXML((TJumpStatement*)p, ctx);
        break;
    case TExpressionStatement_ID:
        TExpressionStatement_PrintXML((TExpressionStatement*)p, ctx);
        break;
    case TIfStatement_ID:
        TIfStatement_PrintXML((TIfStatement*)p, ctx);
        break;
    case TWhileStatement_ID:
        TWhileStatement_PrintXML((TWhileStatement*)p, ctx);
        break;
    case TSwitchStatement_ID:
        TSwitchStatement_PrintXML((TSwitchStatement*)p, ctx);
        break;
    case TAsmStatement_ID:
        TAsmStatement_PrintXML((TAsmStatement*)p, ctx);
        break;
    case TDoStatement_ID:
        TDoStatement_PrintXML((TDoStatement*)p, ctx);
        break;
    case TLabeledStatement_ID:
        TLabeledStatement_PrintXML((TLabeledStatement*)p, ctx);
        break;
    case TCompoundStatement_ID:
        TCompoundStatement_PrintXML((TCompoundStatement*)p, ctx);
        break;
    default:
        break;
    }
}

void TGroupDeclaration_PrintXML(TGroupDeclaration* p,
    struct PrintXMLContext* ctx)
{
}

void TStaticAssertDeclaration_PrintXML(TStaticAssertDeclaration* p,
    struct PrintXMLContext* ctx)
{
}
void TParameter_PrintXML(TParameter* p, struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<parameter>");
    TDeclarationSpecifiers_PrintXML(&p->Specifiers, ctx);
    TDeclarator_PrintXML(&p->Declarator, ctx);
    PrintLn(ctx, "</parameter>");
}


void TParameterList_PrintXML(TParameterList* p, struct PrintXMLContext* ctx)
{
    if (p->pHead)
    {
        PrintLn(ctx, "<parameter-list>");
        TParameter* pCurrent = p->pHead;
        while (pCurrent)
        {
            TParameter_PrintXML(pCurrent, ctx);
            pCurrent = pCurrent->pNext;
        }
        PrintLn(ctx, "</parameter-list>");
    }
}

void TParameterTypeList_PrintXML(TParameterTypeList* p,
    struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<parameter-type-list>");
    TParameterList_PrintXML(&p->ParameterList, ctx);
    PrintLn(ctx, "</parameter-type-list>");
}

void TDirectDeclarator_PrintXML(TDirectDeclarator* p,
    struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<direct-declarator>");
    if (p->Identifier)
    {
        PrintLn(ctx, "<id>");
        PrintText(ctx, p->Identifier);
        PrintLn(ctx, "</id>");
    }
    else  if (p->pDeclarator)
    {
        TDeclarator_PrintXML(p->pDeclarator, ctx);
    }


    if (p->DeclaratorType == TDirectDeclaratorTypeArray)
    {
    }
    else  if (p->DeclaratorType == TDirectDeclaratorTypeFunction)
    {
        TParameterTypeList_PrintXML(&p->Parameters, ctx);
    }

    if (p->pDirectDeclarator)
    {
        TDirectDeclarator_PrintXML(p->pDirectDeclarator, ctx);
    }
    //p->
    PrintLn(ctx, "</direct-declarator>");
}



void TTypeQualifierList_PrintXML(TTypeQualifierList* p,
    struct PrintXMLContext* ctx)
{
    if (p->Size)
    {
        PrintLn(ctx, "<qualifiers>");
        for (int i = 0; i < p->Size; i++)
        {
            TTypeQualifier_PrintXML(p->Data[i], ctx);
        }
        PrintLn(ctx, "</qualifiers>");
    }
}

void TPointer_PrintXML(TPointer* p,
    struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<pointer>");
    
    TTypeQualifierList_PrintXML(&p->Qualifier, ctx);

    PrintLn(ctx, "</pointer>");
}
void TPointerList_PrintXML(TPointerList* p,
    struct PrintXMLContext* ctx)
{
    TPointer* pCurrent = p->pHead;
    if (pCurrent)
    {
        PrintLn(ctx, "<pointer-list>");
        while (pCurrent)
        {
            TPointer_PrintXML(pCurrent, ctx);
            pCurrent = pCurrent->pNext;
        }
        PrintLn(ctx, "</pointer-list>");
    }
}

void TDeclarator_PrintXML(TDeclarator* p,
    struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<declarator>");
    TDirectDeclarator_PrintXML(p->pDirectDeclarator, ctx);    
    TPointerList_PrintXML(&p->PointerList, ctx);
    PrintLn(ctx, "</declarator>");
}

void TInitDeclarator_PrintXML(TInitDeclarator* p,
    struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<init-declarator>");
    TDeclarator_PrintXML(p->pDeclarator, ctx);
    PrintLn(ctx, "</init-declarator>");
}

void TInitDeclaratorList_PrintXML(TInitDeclaratorList* p,
    struct PrintXMLContext* ctx)
{
    TInitDeclarator* pCurrent = p->pHead;
    while (pCurrent)
    {
        TInitDeclarator_PrintXML(pCurrent, ctx);
        pCurrent = pCurrent->pNext;
    }
}

void TDeclaration_PrintXML(TDeclaration* p, struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<declaration>");
    TScannerItemList_PrintXML(&p->ClueList0, ctx);

    TDeclarationSpecifiers_PrintXML(&p->Specifiers, ctx);
    TInitDeclaratorList_PrintXML(&p->InitDeclaratorList, ctx);
    TScannerItemList_PrintXML(&p->ClueList1, ctx);
    PrintLn(ctx, "</declaration>");
}


void TSingleTypeSpecifier_PrintXML(TSingleTypeSpecifier* p,
    struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<single-type-specifier>");

    TScannerItemList_PrintXML(&p->ClueList0, ctx);

    if (p->TypedefName)
    {
        PrintText(ctx, p->TypedefName);
    }
    else
    {
        PrintText(ctx, TokenToString(p->Token2));
    }

    PrintLn(ctx, "</single-type-specifier>");
}

void TTypeQualifier_PrintXML(TTypeQualifier* p, struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<type-qualifier>");
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
    PrintLn(ctx, "</type-qualifier>");
}

void TStructDeclarationList_PrintXML(TStructDeclarationList* p, struct PrintXMLContext* ctx)
{
    for (int i = 0; i < p->Size; i++)
    {
        TAnyStructDeclaration* pCurrent = p->pItems[i];
        TAnyStructDeclaration_PrintXML(pCurrent, ctx);
    }
}

void TStructUnionSpecifier_PrintXML(TStructUnionSpecifier* p, struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<struct-union-specifier>");
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
    TStructDeclarationList_PrintXML(&p->StructDeclarationList, ctx);
    PrintLn(ctx, "</struct-union-specifier>");


}

void TStorageSpecifier_PrintXML(TStorageSpecifier* p,
    struct PrintXMLContext* ctx)
{
    Print(ctx, "<storage-specifier>");
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
    PrintText(ctx, TokenToString(p->Token));
    PrintLn(ctx, "</storage-specifier>");
}


void TAtomicTypeSpecifier_PrintXML(TAtomicTypeSpecifier* p,
    struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<atomic-specifier>");
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
    //PrintText(ctx, TokenToString(p->Token));
    PrintLn(ctx, "</atomic-specifier>");


}


void TAlignmentSpecifier_PrintXML(TAlignmentSpecifier* p,
    struct PrintXMLContext* ctx)
{
    //TScannerItemList_PrintXML(&p->ClueList0, ctx);
}



void TFunctionSpecifier_PrintXML(TFunctionSpecifier* p,
    struct PrintXMLContext* ctx)
{
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
}

void TEnumSpecifier_PrintXML(TEnumSpecifier* p, struct PrintXMLContext* ctx)
{
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
}


void TStructDeclaratorList_PrintXML(TStructDeclaratorList* p, struct PrintXMLContext* ctx)
{
    if (p->pHead)
    {
        PrintLn(ctx, "<struct-declarator-list>");
        TInitDeclarator* pCurrent = p->pHead;
        while (pCurrent)
        {
            TInitDeclarator_PrintXML(pCurrent, ctx);
            pCurrent = pCurrent->pNext;
        }
        PrintLn(ctx, "</struct-declarator-list>");
    }
}

void TStructDeclaration_PrintXML(TStructDeclaration* p, struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<struct-declaration>");
    TStructDeclaratorList_PrintXML(&p->DeclaratorList, ctx);
    PrintLn(ctx, "</struct-declaration>");
}

void TAnyStructDeclaration_PrintXML(TAnyStructDeclaration* p, struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
    case TStaticAssertDeclaration_ID:
        TStaticAssertDeclaration_PrintXML((TStaticAssertDeclaration*)p, ctx);
        break;
    case TStructDeclaration_ID:
        TStructDeclaration_PrintXML((TStructDeclaration*)p, ctx);
        break;
    default:
        break;
    }
}
void TTypeSpecifier_PrintXML(TTypeSpecifier* p, struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
    case TStructUnionSpecifier_ID:
        TStructUnionSpecifier_PrintXML((TStructUnionSpecifier*)p, ctx);
        break;
    case TAtomicTypeSpecifier_ID:
        TAtomicTypeSpecifier_PrintXML((TAtomicTypeSpecifier*)p, ctx);
        break;
    case TSingleTypeSpecifier_ID:
        TSingleTypeSpecifier_PrintXML((TSingleTypeSpecifier*)p, ctx);
        break;
    case TEnumSpecifier_ID:
        TEnumSpecifier_PrintXML((TEnumSpecifier*)p, ctx);
        break;
    default:
        break;
    }
}

void TDeclarationSpecifier_PrintXML(TDeclarationSpecifier* p, struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
    case TTypeQualifier_ID:
        TTypeQualifier_PrintXML((TTypeQualifier*)p, ctx);
        break;
    case TStructUnionSpecifier_ID:
        TStructUnionSpecifier_PrintXML((TStructUnionSpecifier*)p, ctx);
        break;
    case TStorageSpecifier_ID:
        TStorageSpecifier_PrintXML((TStorageSpecifier*)p, ctx);
        break;
    case TAtomicTypeSpecifier_ID:
        TAtomicTypeSpecifier_PrintXML((TAtomicTypeSpecifier*)p, ctx);
        break;
    case TSingleTypeSpecifier_ID:
        TSingleTypeSpecifier_PrintXML((TSingleTypeSpecifier*)p, ctx);
        break;
    case TAlignmentSpecifier_ID:
        TAlignmentSpecifier_PrintXML((TAlignmentSpecifier*)p, ctx);
        break;
    case TFunctionSpecifier_ID:
        TFunctionSpecifier_PrintXML((TFunctionSpecifier*)p, ctx);
        break;
    case TEnumSpecifier_ID:
        TEnumSpecifier_PrintXML((TEnumSpecifier*)p, ctx);
        break;
    default:
        break;
    }
}

void TDeclarationSpecifiers_PrintXML(TDeclarationSpecifiers* p,
    struct PrintXMLContext* ctx)
{
    if (p->Size > 0)
    {
        PrintLn(ctx, "<especifiers>");
        for (int i = 0; i < p->Size; i++)
        {
            TDeclarationSpecifier_PrintXML(p->pData[i], ctx);
        }
        PrintLn(ctx, "</especifiers>");
    }


}



void TEofDeclaration_PrintXML(TEofDeclaration* p,
    struct PrintXMLContext* ctx)
{
    TScannerItemList_PrintXML(&p->ClueList0, ctx);
    PrintLn(ctx, "<eof-declaration/>");
}

void TAnyDeclaration_PrintXML(TAnyDeclaration* p,
    struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
    case TGroupDeclaration_ID:
        TGroupDeclaration_PrintXML((TGroupDeclaration*)p, ctx);
        break;
    case TStaticAssertDeclaration_ID:
        TStaticAssertDeclaration_PrintXML((TStaticAssertDeclaration*)p, ctx);
        break;
    case TDeclaration_ID:
        TDeclaration_PrintXML((TDeclaration*)p, ctx);
        break;
    case TEofDeclaration_ID:
        TEofDeclaration_PrintXML((TEofDeclaration*)p, ctx);
        break;
    default:
        break;
    }
}


void TProgram_PrintAstToXML(TProgram* pProgram,
    const char* fileName,
    const char* inputFileName)
{
    FILE* fp = fopen(fileName, "w");
    //TDeclarations_Print(&pProgram->Declarations, false, fp);

    struct PrintXMLContext ctx = { 0 };
    ctx.fp = fp;
    bool b = false;
    fprintf(fp, "<AST>\n");

    for (int i = 0; i < pProgram->Declarations.Size; i++)
    {
        TAnyDeclaration* pItem = pProgram->Declarations.pItems[i];
        TAnyDeclaration_PrintXML(pItem, &ctx);
    }

    fprintf(fp, "</AST>");

    fclose(fp);
}


