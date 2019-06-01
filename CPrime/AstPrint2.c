#include "AstPrint2.h"


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
void TDeclarator_PrintXML(struct TDeclarator* p,
                          struct PrintXMLContext* ctx);

void TDeclarationSpecifiers_PrintXML(struct TDeclarationSpecifiers* p,
                                     struct PrintXMLContext* ctx);

void TStructDeclaration_PrintXML(struct TStructDeclaration* p, struct PrintXMLContext* ctx);

void TAnyStructDeclaration_PrintXML(struct TAnyStructDeclaration* p, struct PrintXMLContext* ctx);
void TTypeQualifier_PrintXML(struct TTypeQualifier* p, struct PrintXMLContext* ctx);


int HasItemsToPrint(struct TScannerItemList* list)
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
    return 1;
}

void TScannerItemList_PrintXML(const char* tokenString, struct TScannerItemList* list,
                               struct PrintXMLContext* ctx)
{

    if (HasItemsToPrint(list))
    {
        PrintLn(ctx, "<CLUE token=\"%s\">", tokenString);
        struct ScannerItem* pCurrent = list->pHead;
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
                case TK_BREAKLINE:
                    PrintLn(ctx, "<TK_BREAKLINE/>");
                    break;
                default:
                    PrintLn(ctx, "<%s>%s</%s>", TokenToString(pCurrent->token), pCurrent->lexeme.c_str, TokenToString(pCurrent->token));
                    break;
            }
            pCurrent = pCurrent->pNext;
        }
        PrintLn(ctx, "</CLUE>");
    }
}

void TBinaryExpression_PrintXML(struct TBinaryExpression* p, struct PrintXMLContext* ctx)
{
}

void TPrimaryExpressionLambda_PrintXML(struct TPrimaryExpressionLambda* p, struct PrintXMLContext* ctx)
{
}
void TUnaryExpressionOperator_PrintXML(struct TUnaryExpressionOperator* p, struct PrintXMLContext* ctx)
{
}
void TCastExpressionType_PrintXML(struct TCastExpressionType* p, struct PrintXMLContext* ctx)
{
}
void TPrimaryExpressionValue_PrintXML(struct TPrimaryExpressionValue* p, struct PrintXMLContext* ctx)
{
}

void TPostfixExpressionCore_PrintXML(struct TPostfixExpressionCore* p, struct PrintXMLContext* ctx)
{
}

void TPrimaryExpressionLiteral_PrintXML(struct TPrimaryExpressionLiteral* p, struct PrintXMLContext* ctx)
{
}

void TTernaryExpression_PrintXML(struct TTernaryExpression* p, struct PrintXMLContext* ctx)
{
}

void TExpression_PrintXML(struct TExpression* p, struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
        case TBinaryExpression_ID:
            TBinaryExpression_PrintXML((struct TBinaryExpression*)p, ctx);
        break;
        case TPrimaryExpressionLambda_ID:
            TPrimaryExpressionLambda_PrintXML((struct TPrimaryExpressionLambda*)p, ctx);
        break;
        case TUnaryExpressionOperator_ID:
            TUnaryExpressionOperator_PrintXML((struct TUnaryExpressionOperator*)p, ctx);
        break;
        case TCastExpressionType_ID:
            TCastExpressionType_PrintXML((struct TCastExpressionType*)p, ctx);
        break;
        case TPrimaryExpressionValue_ID:
            TPrimaryExpressionValue_PrintXML((struct TPrimaryExpressionValue*)p, ctx);
        break;
        case TPostfixExpressionCore_ID:
            TPostfixExpressionCore_PrintXML((struct TPostfixExpressionCore*)p, ctx);
        break;
        case TPrimaryExpressionLiteral_ID:
            TPrimaryExpressionLiteral_PrintXML((struct TPrimaryExpressionLiteral*)p, ctx);
        break;
        case TTernaryExpression_ID:
            TTernaryExpression_PrintXML((struct TTernaryExpression*)p, ctx);
        break;
        default:
        break;
    }
}

void TForStatement_PrintXML(struct TForStatement* p, struct PrintXMLContext* ctx)
{
}

void TJumpStatement_PrintXML(struct TJumpStatement* p, struct PrintXMLContext* ctx)
{
}


void TExpressionStatement_PrintXML(struct TExpressionStatement* p, struct PrintXMLContext* ctx)
{
}


void TIfStatement_PrintXML(struct TIfStatement* p, struct PrintXMLContext* ctx)
{
}


void TWhileStatement_PrintXML(struct TWhileStatement* p, struct PrintXMLContext* ctx)
{
}


void TSwitchStatement_PrintXML(struct TSwitchStatement* p, struct PrintXMLContext* ctx)
{
}


void TAsmStatement_PrintXML(struct TAsmStatement* p, struct PrintXMLContext* ctx)
{
}


void TDoStatement_PrintXML(struct TDoStatement* p, struct PrintXMLContext* ctx)
{
}


void TLabeledStatement_PrintXML(struct TLabeledStatement* p, struct PrintXMLContext* ctx)
{
}

void TCompoundStatement_PrintXML(struct TCompoundStatement* p, struct PrintXMLContext* ctx)
{
}

void TStatement_PrintXML(struct TStatement* p, struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
        case TForStatement_ID:
            TForStatement_PrintXML((struct TForStatement*)p, ctx);
        break;
        case TJumpStatement_ID:
            TJumpStatement_PrintXML((struct TJumpStatement*)p, ctx);
        break;
        case TExpressionStatement_ID:
            TExpressionStatement_PrintXML((struct TExpressionStatement*)p, ctx);
        break;
        case TIfStatement_ID:
            TIfStatement_PrintXML((struct TIfStatement*)p, ctx);
        break;
        case TWhileStatement_ID:
            TWhileStatement_PrintXML((struct TWhileStatement*)p, ctx);
        break;
        case TSwitchStatement_ID:
            TSwitchStatement_PrintXML((struct TSwitchStatement*)p, ctx);
        break;
        case TAsmStatement_ID:
            TAsmStatement_PrintXML((struct TAsmStatement*)p, ctx);
        break;
        case TDoStatement_ID:
            TDoStatement_PrintXML((struct TDoStatement*)p, ctx);
        break;
        case TLabeledStatement_ID:
            TLabeledStatement_PrintXML((struct TLabeledStatement*)p, ctx);
        break;
        case TCompoundStatement_ID:
            TCompoundStatement_PrintXML((struct TCompoundStatement*)p, ctx);
        break;
        default:
        break;
    }
}

void TGroupDeclaration_PrintXML(struct TGroupDeclaration* p,
                                struct PrintXMLContext* ctx)
{
}

void TStaticAssertDeclaration_PrintXML(struct TStaticAssertDeclaration* p,
                                       struct PrintXMLContext* ctx)
{
}
void TParameter_PrintXML(struct TParameter* p, struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<parameter>");
    TDeclarationSpecifiers_PrintXML(&p->Specifiers, ctx);
    TDeclarator_PrintXML(&p->Declarator, ctx);
    PrintLn(ctx, "</parameter>");
}


void TParameterList_PrintXML(struct TParameterList* p, struct PrintXMLContext* ctx)
{
    if (p->pHead)
    {
        PrintLn(ctx, "<parameter-list>");
        struct TParameter* pCurrent = p->pHead;
        while (pCurrent)
        {
            TParameter_PrintXML(pCurrent, ctx);
            pCurrent = pCurrent->pNext;
        }
        PrintLn(ctx, "</parameter-list>");
    }
}

void TParameterTypeList_PrintXML(struct TParameterTypeList* p,
                                 struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<parameter-type-list>");
    TParameterList_PrintXML(&p->ParameterList, ctx);
    PrintLn(ctx, "</parameter-type-list>");
}

void TDirectDeclarator_PrintXML(struct TDirectDeclarator* p,
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



void TTypeQualifierList_PrintXML(struct TTypeQualifierList* p,
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

void TPointer_PrintXML(struct TPointer* p,
                       struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<pointer>");

    TTypeQualifierList_PrintXML(&p->Qualifier, ctx);

    PrintLn(ctx, "</pointer>");
}
void TPointerList_PrintXML(struct TPointerList* p,
                           struct PrintXMLContext* ctx)
{
    struct TPointer* pCurrent = p->pHead;
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

void TDeclarator_PrintXML(struct TDeclarator* p,
                          struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<declarator>");
    TDirectDeclarator_PrintXML(p->pDirectDeclarator, ctx);
    TPointerList_PrintXML(&p->PointerList, ctx);
    PrintLn(ctx, "</declarator>");
}

void TInitDeclarator_PrintXML(struct TInitDeclarator* p,
                              struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<init-declarator>");
    TDeclarator_PrintXML(p->pDeclarator, ctx);
    PrintLn(ctx, "</init-declarator>");
}

void TInitDeclaratorList_PrintXML(struct TInitDeclaratorList* p,
                                  struct PrintXMLContext* ctx)
{
    struct TInitDeclarator* pCurrent = p->pHead;
    while (pCurrent)
    {
        TInitDeclarator_PrintXML(pCurrent, ctx);
        pCurrent = pCurrent->pNext;
    }
}

void TDeclaration_PrintXML(struct TDeclaration* p, struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<declaration>");

    TScannerItemList_PrintXML(":", &p->ClueList00, ctx);
    TScannerItemList_PrintXML("tag", &p->ClueList001, ctx);
    TScannerItemList_PrintXML("default", &p->ClueList0, ctx);

    TDeclarationSpecifiers_PrintXML(&p->Specifiers, ctx);
    TInitDeclaratorList_PrintXML(&p->InitDeclaratorList, ctx);
    TScannerItemList_PrintXML(";", &p->ClueList1, ctx);
    PrintLn(ctx, "</declaration>");
}


void TSingleTypeSpecifier_PrintXML(struct TSingleTypeSpecifier* p,
                                   struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<single-type-specifier>");

    TScannerItemList_PrintXML("", &p->ClueList0, ctx);

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

void TTypeQualifier_PrintXML(struct TTypeQualifier* p, struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<type-qualifier>");
    TScannerItemList_PrintXML("", &p->ClueList0, ctx);
    PrintLn(ctx, "</type-qualifier>");
}

void TStructDeclarationList_PrintXML(struct TStructDeclarationList* p, struct PrintXMLContext* ctx)
{
    for (int i = 0; i < p->Size; i++)
    {
        struct TAnyStructDeclaration* pCurrent = p->pItems[i];
        TAnyStructDeclaration_PrintXML(pCurrent, ctx);
    }
}

void TStructUnionSpecifier_PrintXML(struct TStructUnionSpecifier* p, struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<struct-union-specifier>");
    TScannerItemList_PrintXML("", &p->ClueList0, ctx);
    TStructDeclarationList_PrintXML(&p->StructDeclarationList, ctx);
    PrintLn(ctx, "</struct-union-specifier>");


}

void TStorageSpecifier_PrintXML(struct TStorageSpecifier* p,
                                struct PrintXMLContext* ctx)
{
    Print(ctx, "<storage-specifier>");
    TScannerItemList_PrintXML("", &p->ClueList0, ctx);
    PrintText(ctx, TokenToString(p->Token));
    PrintLn(ctx, "</storage-specifier>");
}


void TAtomicTypeSpecifier_PrintXML(struct TAtomicTypeSpecifier* p,
                                   struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<atomic-specifier>");
    TScannerItemList_PrintXML("", &p->ClueList0, ctx);
    //PrintText(ctx, TokenToString(p->Token));
    PrintLn(ctx, "</atomic-specifier>");


}


void TAlignmentSpecifier_PrintXML(struct TAlignmentSpecifier* p,
                                  struct PrintXMLContext* ctx)
{
    //TScannerItemList_PrintXML(&p->ClueList0, ctx);
}



void TFunctionSpecifier_PrintXML(struct TFunctionSpecifier* p,
                                 struct PrintXMLContext* ctx)
{
    TScannerItemList_PrintXML("", &p->ClueList0, ctx);
}

void TEnumSpecifier_PrintXML(struct TEnumSpecifier* p, struct PrintXMLContext* ctx)
{
    TScannerItemList_PrintXML("", &p->ClueList0, ctx);
}


void TStructDeclaratorList_PrintXML(struct TStructDeclaratorList* p, struct PrintXMLContext* ctx)
{
    if (p->pHead)
    {
        PrintLn(ctx, "<struct-declarator-list>");
        struct TInitDeclarator* pCurrent = p->pHead;
        while (pCurrent)
        {
            TInitDeclarator_PrintXML(pCurrent, ctx);
            pCurrent = pCurrent->pNext;
        }
        PrintLn(ctx, "</struct-declarator-list>");
    }
}

void TStructDeclaration_PrintXML(struct TStructDeclaration* p, struct PrintXMLContext* ctx)
{
    PrintLn(ctx, "<struct-declaration>");
    TStructDeclaratorList_PrintXML(&p->DeclaratorList, ctx);
    PrintLn(ctx, "</struct-declaration>");
}

void TAnyStructDeclaration_PrintXML(struct TAnyStructDeclaration* p, struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
        case TStaticAssertDeclaration_ID:
            TStaticAssertDeclaration_PrintXML((struct TStaticAssertDeclaration*)p, ctx);
        break;
        case TStructDeclaration_ID:
            TStructDeclaration_PrintXML((struct TStructDeclaration*)p, ctx);
        break;
        default:
        break;
    }
}
void TTypeSpecifier_PrintXML(struct TTypeSpecifier* p, struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
        case TStructUnionSpecifier_ID:
            TStructUnionSpecifier_PrintXML((struct TStructUnionSpecifier*)p, ctx);
        break;
        case TAtomicTypeSpecifier_ID:
            TAtomicTypeSpecifier_PrintXML((struct TAtomicTypeSpecifier*)p, ctx);
        break;
        case TSingleTypeSpecifier_ID:
            TSingleTypeSpecifier_PrintXML((struct TSingleTypeSpecifier*)p, ctx);
        break;
        case TEnumSpecifier_ID:
            TEnumSpecifier_PrintXML((struct TEnumSpecifier*)p, ctx);
        break;
        default:
        break;
    }
}

void TDeclarationSpecifier_PrintXML(struct TDeclarationSpecifier* p, struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
        case TTypeQualifier_ID:
            TTypeQualifier_PrintXML((struct TTypeQualifier*)p, ctx);
        break;
        case TStructUnionSpecifier_ID:
            TStructUnionSpecifier_PrintXML((struct TStructUnionSpecifier*)p, ctx);
        break;
        case TStorageSpecifier_ID:
            TStorageSpecifier_PrintXML((struct TStorageSpecifier*)p, ctx);
        break;
        case TAtomicTypeSpecifier_ID:
            TAtomicTypeSpecifier_PrintXML((struct TAtomicTypeSpecifier*)p, ctx);
        break;
        case TSingleTypeSpecifier_ID:
            TSingleTypeSpecifier_PrintXML((struct TSingleTypeSpecifier*)p, ctx);
        break;
        case TAlignmentSpecifier_ID:
            TAlignmentSpecifier_PrintXML((struct TAlignmentSpecifier*)p, ctx);
        break;
        case TFunctionSpecifier_ID:
            TFunctionSpecifier_PrintXML((struct TFunctionSpecifier*)p, ctx);
        break;
        case TEnumSpecifier_ID:
            TEnumSpecifier_PrintXML((struct TEnumSpecifier*)p, ctx);
        break;
        default:
        break;
    }
}

void TDeclarationSpecifiers_PrintXML(struct TDeclarationSpecifiers* p,
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



void TEofDeclaration_PrintXML(struct TEofDeclaration* p,
                              struct PrintXMLContext* ctx)
{
    TScannerItemList_PrintXML("", &p->ClueList0, ctx);
    PrintLn(ctx, "<eof-declaration/>");
}

void TAnyDeclaration_PrintXML(struct TAnyDeclaration* p,
                              struct PrintXMLContext* ctx) /*@default*/
{
    switch (p->Type)
    {
        case TGroupDeclaration_ID:
            TGroupDeclaration_PrintXML((struct TGroupDeclaration*)p, ctx);
        break;
        case TStaticAssertDeclaration_ID:
            TStaticAssertDeclaration_PrintXML((struct TStaticAssertDeclaration*)p, ctx);
        break;
        case TDeclaration_ID:
            TDeclaration_PrintXML((struct TDeclaration*)p, ctx);
        break;
        case TEofDeclaration_ID:
            TEofDeclaration_PrintXML((struct TEofDeclaration*)p, ctx);
        break;
        default:
        break;
    }
}


void SyntaxTree_PrintAstToXML(struct SyntaxTree* pSyntaxTree,
                              const char* fileName,
                              const char* inputFileName)
{
    FILE* fp = fopen(fileName, "w");
    //TDeclarations_Print(&pSyntaxTree->Declarations, false, fp);

    struct PrintXMLContext ctx = { 0 };
    ctx.fp = fp;
    bool b = false;
    fprintf(fp, "<AST>\n");

    for (int i = 0; i < pSyntaxTree->Declarations.Size; i++)
    {
        struct TAnyDeclaration* pItem = pSyntaxTree->Declarations.pItems[i];
        TAnyDeclaration_PrintXML(pItem, &ctx);
    }

    fprintf(fp, "</AST>");

    fclose(fp);
}


