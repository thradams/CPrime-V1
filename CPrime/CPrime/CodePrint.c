#include "CodePrint.h"
#include "..\Base\Array.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\Base\Path.h"

bool bExpandMacros;

void Options_Destroy(Options* options)
{
    StrBuilder_Destroy(&options->TemplateDeclarations);
    StrBuilder_Destroy(&options->TemplateInstanciation);
}

static bool TInitializerListItem_CodePrint2(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    bool bIsPointer,
    TInitializerListItem* p,
    bool b,
    StrBuilder* fp);

static bool TInitializer_CodePrint2(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    bool bIsPointer,
    TInitializer* pTInitializer,
    bool b,
    StrBuilder* fp);

static bool TSpecifierQualifierList_CodePrint(TProgram* program, Options * options, TSpecifierQualifierList* pDeclarationSpecifiers, bool b, StrBuilder* fp);

static bool TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p, bool b, StrBuilder* fp);

static bool TInitializer_CodePrint(TProgram* program,
    Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    bool bIsPointer,
    TInitializer* pTInitializer,
    bool b,
    StrBuilder* fp);

static bool TInitializerList_CodePrint(TProgram* program,
    Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    bool bIsPointer,
    TInitializerList*p,
    bool b,
    StrBuilder* fp);

static bool TInitializerList_CodePrint2(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    bool bIsPointer,
    TInitializerList*p,
    bool b,
    StrBuilder* fp);

static bool TInitializerListItem_CodePrint(TProgram* program,
    Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    bool bIsPointer,
    TInitializerListItem* p,
    bool b,
    StrBuilder* fp);


static bool TTypeQualifierList_CodePrint(TProgram* program, Options * options, TTypeQualifierList* p, bool b, StrBuilder* fp);
//static bool TInitializerList_CodePrint(TProgram* program, Options * options, TTypeSpecifier* pTypeSpecifier, bool bIsPointer, TInitializerList*p, bool b, StrBuilder* fp);
//static bool TInitializerListType_CodePrint(TTypeSpecifier* pTypeSpecifier, bool b, StrBuilder* fp);
static bool TDeclarator_CodePrint(TProgram* program, Options * options, TDeclarator* p, bool b, StrBuilder* fp);
static bool TAnyDeclaration_CodePrint(TProgram* program, Options * options, TAnyDeclaration *pDeclaration, bool b, StrBuilder* fp);
static bool TTypeSpecifier_CodePrint(TProgram* program, Options * options, TTypeSpecifier* p, bool b, StrBuilder* fp);
static bool TAnyStructDeclaration_CodePrint(TProgram* program, Options * options, TAnyStructDeclaration* p, bool b, StrBuilder* fp);
static bool TTypeQualifier_CodePrint(TProgram* program, Options * options, TTypeQualifier* p, bool b, StrBuilder* fp);
static bool TDeclaration_CodePrint(TProgram* program, Options * options, TDeclaration* p, bool b, StrBuilder* fp);
static bool TExpression_CodePrint(TProgram* program, Options * options, TExpression * p, const char* name, bool b, StrBuilder* fp);
static bool TStatement_CodePrint(TProgram* program, Options * options, TStatement * p, bool b, StrBuilder* fp);
static bool TBlockItem_CodePrint(TProgram* program, Options * options, TBlockItem * p, bool b, StrBuilder* fp);

static bool TPointer_CodePrint(TProgram* program, Options * options, TPointer* pPointer, bool b, StrBuilder* fp);
static bool TParameterDeclaration_CodePrint(TProgram* program, Options * options, TParameterDeclaration* p, bool b, StrBuilder* fp);
//static bool TInitializerListItem_CodePrint(TProgram* program, Options * options, TTypeSpecifier* pTypeSpecifier, bool bIsPointer, TInitializerListItem* p, bool b, StrBuilder* fp);

static bool bInclude = true;
static int IncludeLevel = 0;

void Output_Append(StrBuilder* p,
    const char* source)
{
    if (bInclude  && IncludeLevel == 0)
        StrBuilder_Append(p, source);
}

static void TNodeClueList_CodePrint(Options* options, TScannerItemList* list,
    StrBuilder* fp)
{
    ForEachListItem(ScannerItem, pNodeClue, list)
    {
        switch (pNodeClue->token)
        {
            case TK_PRE_INCLUDE:
            Output_Append(fp, pNodeClue->lexeme.c_str);
            Output_Append(fp, "\n");
            IncludeLevel++;
            break;

            case TK_FILE_EOF:
            IncludeLevel--;
            //bInclude = true;
            break;
            case TK_PRE_DEFINE:
            case TK_PRE_UNDEF:
            case TK_PRE_PRAGMA:
            case TK_PRE_IF:
            case TK_PRE_ENDIF:
            case TK_PRE_ELSE:
            case TK_PRE_IFDEF:
            case TK_PRE_IFNDEF:

            Output_Append(fp, pNodeClue->lexeme.c_str);
            Output_Append(fp, "\n");
            break;

            case TK_COMMENT:
            if (options->bIncludeComments)
            {
                Output_Append(fp, pNodeClue->lexeme.c_str);
            }
            else
            {
                Output_Append(fp, " ");
            }

            break;

            case TK_LINE_COMMENT:
            if (options->bIncludeComments)
            {
                Output_Append(fp, pNodeClue->lexeme.c_str);
            }
            else
            {
                Output_Append(fp, "\n");
            }
            break;

            case TK_BREAKLINE:
            Output_Append(fp, "\n");

            break;

            case TK_MACRO_CALL:
            if (options->bExpandMacros)
            {

            }
            else
            {
                Output_Append(fp, pNodeClue->lexeme.c_str);
                bInclude = false;
            }
            break;


            case TK_MACRO_EOF:
            if (options->bExpandMacros)
            {

            }
            else
            {
                bInclude = true;
            }


            break;

            case TK_SPACES:
            Output_Append(fp, pNodeClue->lexeme.c_str);
            break;

            //case NodeClueTypeNone:      
            default:
            Output_Append(fp, pNodeClue->lexeme.c_str);
            break;
        }

    }
}



void BuildEnumSpecifierInitialization(TProgram* program, Options * options,
    TEnumSpecifier* pTEnumSpecifier,
    StrBuilder* strBuilder)
{
    Output_Append(strBuilder, "0");
}


void BuildInitialization(TProgram* program,
    Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    bool bIsPointer,
    StrBuilder* strBuilder);

void BuildInitialization2(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    bool bIsPointer,
    StrBuilder* strBuilder);


static void BuildInitializationForTypedef(TProgram* program,
    Options * options,
    const char* typedefName,
    StrBuilder* strBuilder)
{
    TDeclaration * p = TProgram_GetFinalTypeDeclaration(program, typedefName);
    if (p)
    {
        //Tem que ver se o typedef nao era ponteiro tb
        TDeclarator* pDeclarator = TDeclaration_FindDeclarator(p, typedefName);
        if (pDeclarator)
        {
            BuildInitialization(program,
                options,
                &p->Specifiers,
                false,
                strBuilder);
        }
        else
        {
            Output_Append(strBuilder, "0");
        }
    }
}



void BuildSingleTypeSpecifierInitialization(TProgram* program,
    Options * options,
    TSingleTypeSpecifier* pSingleTypeSpecifier,
    bool bIsPointer,
    StrBuilder* strBuilder)
{

    if (pSingleTypeSpecifier->bIsTypeDef)
    {
        const char* typedefName = pSingleTypeSpecifier->TypedefName;
        TDeclaration * p = TProgram_GetFinalTypeDeclaration(program, typedefName);
        if (p)
        {
            //Tem que ver se o typedef nao era ponteiro tb
            TDeclarator* pDeclarator = TDeclaration_FindDeclarator(p, typedefName);
            if (pDeclarator)
            {
                BuildInitialization(program,
                    options,
                    &p->Specifiers,
                    bIsPointer || TPointerList_IsPointer(&pDeclarator->PointerList),
                    strBuilder);
            }
            else
            {
                ASSERT(false);
            }

        }
    }
    else
    {
        if (pSingleTypeSpecifier->bIsBool)
            Output_Append(strBuilder, "false");
        else if (pSingleTypeSpecifier->bIsDouble)
            Output_Append(strBuilder, "0.0");
        else
            Output_Append(strBuilder, "0");
    }
}


void BuildStructUnionSpecifierInitialization(TProgram* program,
    Options * options,
    TStructUnionSpecifier* pStructUnionSpecifier,
    StrBuilder* strBuilder)
{

    //struct X x = {};
    if (pStructUnionSpecifier->StructDeclarationList.size == 0)
    {
        TDeclaration* pStructDeclaration =
            TProgram_FindDeclaration(program, pStructUnionSpecifier->Name);
        if (pStructDeclaration != NULL)
        {
            pStructUnionSpecifier =
                TSpecifier_As_TStructUnionSpecifier(pStructDeclaration->Specifiers.pHead);
        }
    }

    if (pStructUnionSpecifier == NULL)
    {
        Output_Append(strBuilder, "{0}");
        return;
    }

    Output_Append(strBuilder, "{");
    int k = 0;
    for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.size; i++)
    {
        TAnyStructDeclaration* p =
            pStructUnionSpecifier->StructDeclarationList.pItems[i];
        TStructDeclaration* pStructDeclaration =
            TAnyStructDeclaration_As_TStructDeclaration(p);

        if (pStructDeclaration)
        {
            if (k > 0)
            {
                Output_Append(strBuilder, ",");
            }

            ForEachListItem(TInitDeclarator, pDeclarator, &pStructDeclaration->DeclaratorList)
            {
                if (pDeclarator->pInitializer)
                {
                    bool bExpandMacros = options->bExpandMacros;
                    bool bIncludeComments = options->bIncludeComments;

                    options->bExpandMacros = true;
                    options->bIncludeComments = false;

                    TInitializer_CodePrint2(program,
                        options,
                        &pStructDeclaration->SpecifierQualifierList,
                        TPointerList_IsPointer(&pDeclarator->pDeclarator->PointerList),
                        pDeclarator->pInitializer,
                        false,
                        strBuilder);

                    options->bExpandMacros = bExpandMacros;
                    options->bIncludeComments = bIncludeComments;
                }
                else
                {
                    BuildInitialization2(program,
                        options,
                        &pStructDeclaration->SpecifierQualifierList,
                        TPointerList_IsPointer(&pDeclarator->pDeclarator->PointerList),
                        strBuilder);
                }
                k++;
            }
        }
    }
    Output_Append(strBuilder, "}");
}

void BuildInitialization(TProgram* program,
    Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    bool bIsPointer,
    StrBuilder* strBuilder)
{
    if (bIsPointer)
    {
        Output_Append(strBuilder, "NULL");
    }
    else
    {
        TSpecifier *pSpecifier = pDeclarationSpecifiers->pHead;

        TStorageSpecifier *pStorageSpecifier =
            TSpecifier_As_TStorageSpecifier(pSpecifier);
        if (pStorageSpecifier)
        {
            //Exemplo typedef struct X {};
            if (pStorageSpecifier->bIsTypedef)
            {
                pSpecifier = pDeclarationSpecifiers->pHead->pNext;
            }
        }

        if (pSpecifier != NULL)
        {
            switch (pSpecifier->Type)
            {
                case TSingleTypeSpecifier_ID:
                BuildSingleTypeSpecifierInitialization(program, options, (TSingleTypeSpecifier*)pSpecifier, bIsPointer, strBuilder);
                break;
                case TEnumSpecifier_ID:
                BuildEnumSpecifierInitialization(program, options, (TEnumSpecifier*)pSpecifier, strBuilder);
                break;
                case TStructUnionSpecifier_ID:
                BuildStructUnionSpecifierInitialization(program, options, (TStructUnionSpecifier*)pSpecifier, strBuilder);
                break;


                case TTemplateTypeSpecifier_ID:
                Output_Append(strBuilder, "{0}");
                break;

                default:
                ASSERT(false);
                break;
            }
        }
    }
}


void BuildInitialization2(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    bool bIsPointer,
    StrBuilder* strBuilder)
{
    if (bIsPointer)
    {
        Output_Append(strBuilder, "NULL");
    }
    else
    {

        switch (pSpecifierQualifierList->pHead->Type)
        {
            case TSingleTypeSpecifier_ID:
            BuildSingleTypeSpecifierInitialization(program, options, (TSingleTypeSpecifier*)pSpecifierQualifierList->pHead, bIsPointer, strBuilder);
            break;
            case TEnumSpecifier_ID:
            BuildEnumSpecifierInitialization(program, options, (TEnumSpecifier*)pSpecifierQualifierList->pHead, strBuilder);
            break;
            case TStructUnionSpecifier_ID:
            BuildStructUnionSpecifierInitialization(program, options, (TStructUnionSpecifier*)pSpecifierQualifierList->pHead, strBuilder);
            break;
            default:
            ASSERT(false);
            break;
        }
    }
}




static bool TCompoundStatement_CodePrint(TProgram* program,
    Options * options,
    TCompoundStatement * p,
    bool b,
    StrBuilder* fp)
{



    //
    b = true;

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, "{");

    for (size_t j = 0; j < p->BlockItemList.size; j++)
    {
        TBlockItem *pBlockItem = p->BlockItemList.pItems[j];
        TBlockItem_CodePrint(program, options, pBlockItem, j > 0, fp);
    }

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, "}");
    return b;
}


static bool TLabeledStatement_CodePrint(TProgram* program, Options * options, TLabeledStatement * p, bool b, StrBuilder* fp)
{
    b = true;

    if (p->token == TK_CASE)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, "case");
        if (p->pStatementOpt)
        {
            b = TExpression_CodePrint(program, options, p->pExpression, "", false, fp);
        }
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, ":");
        b = TStatement_CodePrint(program, options, p->pStatementOpt, false, fp);
    }
    else if (p->token == TK_DEFAULT)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, "default");
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, ":");
        b = TStatement_CodePrint(program, options, p->pStatementOpt, false, fp);
    }
    else if (p->token == TK_IDENTIFIER)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, p->Identifier);
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, ":");
    }


    return b;
}

static bool TForStatement_CodePrint(TProgram* program, Options * options, TForStatement * p, bool b, StrBuilder* fp)
{
    b = true;
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, "for");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, "(");

    if (p->pInitDeclarationOpt)
    {
        TAnyDeclaration_CodePrint(program, options, p->pInitDeclarationOpt, b, fp);
        if (p->pExpression2)
        {
            b = TExpression_CodePrint(program, options, p->pExpression2, "expr2", true, fp);
        }
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, ";");
        b = TExpression_CodePrint(program, options, p->pExpression3, "expr3", b, fp);
    }
    else
    {
        b = TExpression_CodePrint(program, options, p->pExpression1, "expr1", true, fp);
        TNodeClueList_CodePrint(options, &p->ClueList2, fp);
        Output_Append(fp, ";");
        b = TExpression_CodePrint(program, options, p->pExpression2, "expr2", b, fp);
        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, ";");
        b = TExpression_CodePrint(program, options, p->pExpression3, "expr3", b, fp);
    }

    TNodeClueList_CodePrint(options, &p->ClueList4, fp);
    Output_Append(fp, ")");

    b = TStatement_CodePrint(program, options, p->pStatement, false, fp);

    return b;
}


static bool TWhileStatement_CodePrint(TProgram* program, Options * options, TWhileStatement * p, bool b, StrBuilder* fp)
{
    b = true;
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, "while");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, "(");
    b = TExpression_CodePrint(program, options, p->pExpression, "expr", false, fp);
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, ")");
    b = TStatement_CodePrint(program, options, p->pStatement, false, fp);
    return b;
}


static bool TReturnStatement_CodePrint(TProgram* program, Options * options, TReturnStatement * p, bool b, StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, "return ");
    TExpression_CodePrint(program, options, p->pExpression, "return-statement", false, fp);
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, ";");
    return true;
}

static bool TDoStatement_CodePrint(TProgram* program, Options * options, TDoStatement * p, bool b, StrBuilder* fp)
{
    b = true;
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, "do");

    b = TStatement_CodePrint(program, options, p->pStatement, false, fp);
    
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, "while");
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, "(");
    b = TExpression_CodePrint(program, options, p->pExpression, "expr", false, fp);
    TNodeClueList_CodePrint(options, &p->ClueList3, fp);
    Output_Append(fp, ")");
    TNodeClueList_CodePrint(options, &p->ClueList4, fp);
    Output_Append(fp, ";");
    
    return b;
}


static bool TExpressionStatement_CodePrint(TProgram* program, Options * options, TExpressionStatement * p, bool b, StrBuilder* fp)
{
    TExpression_CodePrint(program, options, p->pExpression, "", b, fp);

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, ";");

    return true;
}


static bool TJumpStatement_CodePrint(TProgram* program, Options * options, TJumpStatement * p, bool b, StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, TokenToString(((TBinaryExpression*)p)->token));

    if (p->pExpression)
    {
        b = TExpression_CodePrint(program, options, p->pExpression, "statement", false, fp);
    }

    if (p->token == TK_BREAK)
    {
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, ";");
    }
    else
    {
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, ";");
    }

    return true;
}

static bool TAsmStatement_CodePrint(TProgram* program, Options * options, TAsmStatement * p, bool b, StrBuilder* fp)
{
    Output_Append(fp, "\"type\":\"asm-statement\"");
    return true;
}

static bool TSwitchStatement_CodePrint(TProgram* program, Options * options, TSwitchStatement * p, bool b, StrBuilder* fp)
{
    b = true;
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, "switch");

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, "(");

    b = TExpression_CodePrint(program, options, p->pConditionExpression, "expr", false, fp);
    
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, ")");

    b = TStatement_CodePrint(program, options, p->pExpression, false, fp);
    return b;
}


static bool TIfStatement_CodePrint(TProgram* program, Options * options, TIfStatement * p, bool b, StrBuilder* fp)
{
    b = true;
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, "if");

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, "(");


    b = TExpression_CodePrint(program, options, p->pConditionExpression, "expr", false, fp);

    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, ")");

    if (p->pStatement->Type != TCompoundStatement_ID)
        Output_Append(fp, "");

    if (p->pStatement)
    {
        b = TStatement_CodePrint(program, options, p->pStatement, false, fp);
    }

    if (p->pElseStatement)
    {
        TNodeClueList_CodePrint(options, &p->ClueList3, fp);
        Output_Append(fp, "else");
        b = TStatement_CodePrint(program, options, p->pElseStatement, false, fp);
    }

    return b;
}

static bool TStatement_CodePrint(TProgram* program, Options * options, TStatement *  p, bool b, StrBuilder* fp)
{
    if (p == NULL)
    {
        return false;
    }

    switch (p->Type)
    {
        case TExpressionStatement_ID:
        b = TExpressionStatement_CodePrint(program, options, (TExpressionStatement*)p, b, fp);
        break;

        case TSwitchStatement_ID:
        b = TSwitchStatement_CodePrint(program, options, (TSwitchStatement*)p, b, fp);
        break;

        case TLabeledStatement_ID:
        b = TLabeledStatement_CodePrint(program, options, (TLabeledStatement*)p, b, fp);
        break;

        case TForStatement_ID:
        b = TForStatement_CodePrint(program, options, (TForStatement*)p, b, fp);
        break;

        case TJumpStatement_ID:
        b = TJumpStatement_CodePrint(program, options, (TJumpStatement*)p, b, fp);
        break;

        case TAsmStatement_ID:
        b = TAsmStatement_CodePrint(program, options, (TAsmStatement*)p, b, fp);
        break;

        case TCompoundStatement_ID:
        b = TCompoundStatement_CodePrint(program, options, (TCompoundStatement*)p, b, fp);
        break;

        case TIfStatement_ID:
        b = TIfStatement_CodePrint(program, options, (TIfStatement*)p, b, fp);
        break;

        case TDoStatement_ID:
        TDoStatement_CodePrint(program, options, (TDoStatement*)p, b, fp);
        break;

        case TReturnStatement_ID:
        TReturnStatement_CodePrint(program, options, (TReturnStatement*)p, b, fp);
        break;

        default:
        ASSERT(false);
        break;
    }

    return b;
}

static bool TBlockItem_CodePrint(TProgram* program, Options * options, TBlockItem *  p, bool b, StrBuilder* fp)
{
    if (p == NULL)
    {
        ASSERT(false);
        return false;
    }


    switch (p->Type)
    {
        case TStaticAssertDeclaration_ID:
        break;

        case TSwitchStatement_ID:

        b = TSwitchStatement_CodePrint(program, options, (TSwitchStatement*)p, false, fp);

        break;

        case TJumpStatement_ID:

        b = TJumpStatement_CodePrint(program, options, (TJumpStatement*)p, false, fp);

        break;

        case TForStatement_ID:

        b = TForStatement_CodePrint(program, options, (TForStatement*)p, false, fp);

        break;

        case TIfStatement_ID:

        b = TIfStatement_CodePrint(program, options, (TIfStatement*)p, false, fp);

        break;

        case TWhileStatement_ID:

        b = TWhileStatement_CodePrint(program, options, (TWhileStatement*)p, b, fp);

        break;

        case TDoStatement_ID:

        b = TDoStatement_CodePrint(program, options, (TDoStatement*)p, false, fp);

        break;

        case TDeclaration_ID:
        b = TDeclaration_CodePrint(program, options, (TDeclaration*)p, false, fp);
        //Output_Append(fp, "\n");
        break;

        case TLabeledStatement_ID:

        b = TLabeledStatement_CodePrint(program, options, (TLabeledStatement*)p, false, fp);

        break;

        case TCompoundStatement_ID:
        b = TCompoundStatement_CodePrint(program, options, (TCompoundStatement*)p, false, fp);
        break;

        case TExpressionStatement_ID:

        b = TExpressionStatement_CodePrint(program, options, (TExpressionStatement*)p, false, fp);

        break;

        case TReturnStatement_ID:

        b = TReturnStatement_CodePrint(program, options, (TReturnStatement*)p, false, fp);

        break;

        case TAsmStatement_ID:

        b = TAsmStatement_CodePrint(program, options, (TAsmStatement*)p, false, fp);

        break;

        default:
        ASSERT(false);
        break;
    }

    return b;
}

static bool IsSuffix(const char* s, const char* suffix)
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


bool GetType(const char* source,
                        StrBuilder* strBuilderType)
{

    while (*source  &&
           *source != '_')
    {
        StrBuilder_AppendChar(strBuilderType, *source);
        *source++;
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
        *source++;
    }

    while (*source)
    {
        StrBuilder_AppendChar(strBuilderFunc, *source);
        *source++;
    }

    return *source == '_';
}




static bool TPostfixExpressionCore_CodePrint(TProgram* program,
    Options * options,
    TPostfixExpressionCore * p,
    bool b,
    StrBuilder* fp)
{


    b = false;

    if (p->pExpressionLeft)
    {
        b = TExpression_CodePrint(program, options, p->pExpressionLeft, "l", b, fp);
    }


    {
        bool bIsPointer = false;
        TTypeName *pTypeName = NULL;
        if (p->pTypeName)
        {
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);
            Output_Append(fp, "(");
            TTypeName_CodePrint(program, options, p->pTypeName, b, fp);
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, ")");

            //pSpecifierQualifierList = &p->pTypeName->SpecifierQualifierList;
            bIsPointer = TPointerList_IsPointer(&p->pTypeName->Declarator.PointerList);

            //falta imprimeir typename
            //TTypeName_Print*
            b = TInitializerList_CodePrint2(program,
                options,
                &pTypeName->SpecifierQualifierList,
                bIsPointer,
                &p->InitializerList,
                b,
                fp);
        }

    }

    switch (p->token)
    {
        case TK_FULL_STOP:
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, ".");
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, p->Identifier);
        b = true;
        break;
        case TK_ARROW:
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, "->");
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, p->Identifier);
        b = true;
        break;

        case TK_LEFT_SQUARE_BRACKET:
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, "[");
        b = TExpression_CodePrint(program, options, p->pExpressionRight, "r", b, fp);
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, "]");
        break;

        case TK_LEFT_PARENTHESIS:
        //Do lado esquerdo vem o nome da funcao p->pExpressionLeft
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, "(");
        b = TExpression_CodePrint(program, options, p->pExpressionRight, "r", b, fp);
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, ")");
        break;

        case TK_PLUSPLUS:
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, "++");
        b = true;
        break;
        case TK_MINUSMINUS:
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, "--");
        b = true;
        break;
        break;
    }


    b = true;
    if (p->pNext)
    {
        b = TPostfixExpressionCore_CodePrint(program, options, p->pNext, false, fp);
    }

    b = true;
    return b;
}

static bool TExpression_CodePrint(TProgram* program, Options * options, TExpression *  p,
    const char* name,
    bool b,
    StrBuilder* fp)
{
    if (p == NULL)
    {
        //ASSERT(false);
        return b;
    }

    b = false;

    switch (p->Type)
    {
        CASE(TBinaryExpression) :
        {
            TBinaryExpression* pBinaryExpression = (TBinaryExpression*)p;

            b = TExpression_CodePrint(program, options, pBinaryExpression->pExpressionLeft, "l-expr", b, fp);

            TNodeClueList_CodePrint(options, &pBinaryExpression->ClueList0, fp);
            Output_Append(fp, TokenToString(pBinaryExpression->token));

            b = TExpression_CodePrint(program, options, ((TBinaryExpression*)p)->pExpressionRight, "r-expr", b, fp);
        }
        break;

        CASE(TTernaryExpression) :
        {
            TTernaryExpression* pTernaryExpression =
                (TTernaryExpression*)p;


            b = TExpression_CodePrint(program, options, pTernaryExpression->pExpressionLeft, "l-expr", b, fp);

            TNodeClueList_CodePrint(options, &pTernaryExpression->ClueList0, fp);
            Output_Append(fp, "?");

            b = TExpression_CodePrint(program, options, pTernaryExpression->pExpressionMiddle, "m-expr", b, fp);

            TNodeClueList_CodePrint(options, &pTernaryExpression->ClueList1, fp);
            Output_Append(fp, ":");

            b = TExpression_CodePrint(program, options, pTernaryExpression->pExpressionRight, "r-expr", b, fp);
        }
        break;

        CASE(TPrimaryExpressionValue) :
        {
            TPrimaryExpressionValue* pPrimaryExpressionValue =
                (TPrimaryExpressionValue*)p;

            if (pPrimaryExpressionValue->pExpressionOpt != NULL)
            {
                TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList0, fp);
                Output_Append(fp, "(");
                b = TExpression_CodePrint(program, options, pPrimaryExpressionValue->pExpressionOpt, "expr", b, fp);

                TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList1, fp);
                Output_Append(fp, ")");
            }
            else
            {
                TNodeClueList_CodePrint(options, &pPrimaryExpressionValue->ClueList0, fp);
                Output_Append(fp, pPrimaryExpressionValue->lexeme);
            }
        }
        b = true;

        break;

        CASE(TPostfixExpressionCore) :
        {
            TPostfixExpressionCore* pPostfixExpressionCore =
                (TPostfixExpressionCore*)p;
            b = TPostfixExpressionCore_CodePrint(program, options, pPostfixExpressionCore, b, fp);
        }
        break;

        CASE(TUnaryExpressionOperator) :
        {
            TUnaryExpressionOperator* pTUnaryExpressionOperator =
                (TUnaryExpressionOperator*)p;

            TNodeClueList_CodePrint(options, &pTUnaryExpressionOperator->ClueList0, fp);

            if (pTUnaryExpressionOperator->token == TK_SIZEOF)
            {

                if (pTUnaryExpressionOperator->TypeName.SpecifierQualifierList.pHead != NULL)
                {
                    Output_Append(fp, "sizeof (");
                    TTypeName_CodePrint(program, options, &pTUnaryExpressionOperator->TypeName, b, fp);
                    //b = TTypeQualifierList_CodePrint(program, options, &pTUnaryExpressionOperator->TypeName.Specifiers.TypeQualifiers, false, fp);
                    //b = TTypeSpecifier_CodePrint(program, options, pTUnaryExpressionOperator->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);
                    //b = TDeclarator_CodePrint(program, options, &pTUnaryExpressionOperator->TypeName.Declarator, b, fp);
                    Output_Append(fp, ")");

                }
                else
                {
                    Output_Append(fp, "sizeof ");
                    b = TExpression_CodePrint(program, options, pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);
                    Output_Append(fp, "");
                }
            }
            else
            {
                Output_Append(fp, TokenToString(((TBinaryExpression*)p)->token));
                b = TExpression_CodePrint(program, options, pTUnaryExpressionOperator->pExpressionLeft, "expr", b, fp);

            }


        }
        break;

        CASE(TCastExpressionType) :
        {
            TCastExpressionType * pCastExpressionType =
                (TCastExpressionType*)p;
            TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList0, fp);
            Output_Append(fp, "(");

            TTypeName_CodePrint(program, options, &pCastExpressionType->TypeName, b, fp);

            //b = TTypeQualifierList_CodePrint(program, options, &pCastExpressionType->TypeName.Specifiers.TypeQualifiers, false, fp);
            //b = TTypeSpecifier_CodePrint(program, options, pCastExpressionType->TypeName.Specifiers.pTypeSpecifierOpt, b, fp);
            //b = TDeclarator_CodePrint(program, options, &pCastExpressionType->TypeName.Declarator, b, fp);

            TNodeClueList_CodePrint(options, &pCastExpressionType->ClueList1, fp);
            Output_Append(fp, ")");

            b = TExpression_CodePrint(program, options, pCastExpressionType->pExpression, "expr", b, fp);
        }
        break;

        default:

        ASSERT(false);
    }


    return b;
}



static   bool TEnumerator_CodePrint(TProgram* program, Options * options, TEnumerator* pTEnumerator, bool b, StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &pTEnumerator->ClueList0, fp);
    Output_Append(fp, pTEnumerator->Name);

    if (pTEnumerator->pExpression)
    {
        TNodeClueList_CodePrint(options, &pTEnumerator->ClueList1, fp);
        Output_Append(fp, " = ");

        TExpression_CodePrint(program, options, pTEnumerator->pExpression, "expr", true, fp);


    }
    else
    {
        //vou criar uma expressionp enum?
    }

    return true;
}

static bool TEnumSpecifier_CodePrint(TProgram* program, Options * options, TEnumSpecifier* p, bool b, StrBuilder* fp)
{
    b = true;

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, "enum");

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, p->Name);

    TNodeClueList_CodePrint(options, &p->ClueList2, fp);
    Output_Append(fp, "{");


    ForEachListItem(TEnumerator, pTEnumerator, &p->EnumeratorList)
    {
        TEnumerator_CodePrint(program, options, pTEnumerator, false, fp);

        if (List_IsLastItem(&p->EnumeratorList, pTEnumerator))
        {
            //Output_Append(fp, "\n");
        }
        else
        {
            TNodeClueList_CodePrint(options, &pTEnumerator->ClueList2, fp);
            Output_Append(fp, ",");
        }
    }

    TNodeClueList_CodePrint(options, &p->ClueList3, fp);
    Output_Append(fp, "}");
    return true;
}


static bool TStructUnionSpecifier_CodePrint(TProgram* program, Options * options, TStructUnionSpecifier* p, bool b, StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    b = true;

    if (p->bIsStruct)
        Output_Append(fp, "struct");

    else
        Output_Append(fp, "union");

    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, p->Name);

    if (p->TemplateName != NULL)
    {
        if (strcmp(p->TemplateName, "List") == 0)
        {
            if (p->Args.pHead)
            {
                Output_Append(fp, " ");
                Output_Append(fp, "{");

                TTypeName_CodePrint(program, options, &p->Args.pHead->TypeName, b, fp);
                Output_Append(fp, "* pHead, *pTail;");

                Output_Append(fp, "}");
            }
            else
            {
                //error
            }
        }
    }
    else
    {
        if (p->StructDeclarationList.size > 0)
        {
            TNodeClueList_CodePrint(options, &p->ClueList2, fp);

            Output_Append(fp, "{");

            for (size_t i = 0; i < p->StructDeclarationList.size; i++)
            {
                TAnyStructDeclaration * pStructDeclaration = p->StructDeclarationList.pItems[i];
                b = TAnyStructDeclaration_CodePrint(program, options, pStructDeclaration, b, fp);
            }

            TNodeClueList_CodePrint(options, &p->ClueList3, fp);
            Output_Append(fp, "}");
        }
    }

    return true;
}

static bool TSingleTypeSpecifier_CodePrint(TProgram* program, Options * options, TSingleTypeSpecifier* p, bool b, StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);


    b = true;

    int i = 0;

    if (p->bIsVoid)
    {
        Output_Append(fp, "void");
        b = true;
    }

    if (p->bIsUnsigned)
    {
        Output_Append(fp, "unsigned");
        b = true;
    }

    if (p->bIsBool)
    {
        Output_Append(fp, "bool");
        b = true;
    }

    if (p->bIsChar)
    {
        Output_Append(fp, "char");
        b = true;
    }

    if (p->bIsShort)
    {
        Output_Append(fp, "short");
        b = true;
    }

    for (int j = 0; j < p->nLong; j++)
    {
        Output_Append(fp, "long");
        b = true;
    }

    if (p->bIsInt)
    {
        Output_Append(fp, "int");
        b = true;
    }

    if (p->bIsDouble)
    {
        Output_Append(fp, "double");
        b = true;
    }

    if (p->bIsFloat)
    {
        Output_Append(fp, "float");
        b = true;
    }

    if (p->bIsTypeDef)
    {
        Output_Append(fp, p->TypedefName);
        b = true;
    }


    return b;
}

static bool TTypeSpecifier_CodePrint(TProgram* program, Options * options, TTypeSpecifier*  p, bool b, StrBuilder* fp)
{
    if (p == NULL)
    {
        //declaracao vazia: ;
        return true;
    }

    switch (p->Type)
    {
        case TStructUnionSpecifier_ID:
        //TAnyStructDeclaration_CodePrint();
        b = TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier*)p, b, fp);
        break;

        case TEnumSpecifier_ID:
        b = TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier*)p, b, fp);
        break;

        case TSingleTypeSpecifier_ID:
        b = TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier*)p, b, fp);
        break;

        default:
        break;
    }

    return b;
}

static bool TDesignator_CodePrint(TProgram* program, Options * options, TDesignator* p, bool b, StrBuilder* fp)
{
    if (b)
        Output_Append(fp, ",");


    //
    if (p->Name)
    {
        //.identifier
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, ".");
        Output_Append(fp, p->Name);
        Output_Append(fp, "=");
        TExpression_CodePrint(program, options, p->pExpression, "index", b, fp);
    }
    else
    {
        //[constant-expression]
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        TExpression_CodePrint(program, options, p->pExpression, "index", b, fp);
        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    }


    return b;
}


static bool TInitializerList_CodePrint(TProgram* program,
    Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    bool bIsPointer,
    TInitializerList*p,
    bool b,
    StrBuilder* fp)
{


    b = false;

    if (List_HasOneItem(p) &&
        List_Back(p)->pInitializer == NULL/* &&
                                          pSpecifierQualifierList != NULL*/)
    {
        //a partir de {} e um tipo consegue gerar o final
        BuildInitialization(program, options, pDeclarationSpecifiers, bIsPointer, fp);

    }
    else
    {
        //TNodeClueList_CodePrint(&p->ClueList, fp, 0);

        //Output_Append(fp, "{");

        ForEachListItem(TInitializerListItem, pItem, p)
        {
            if (!List_IsFirstItem(p, pItem))
                Output_Append(fp, ",");

            b = TInitializerListItem_CodePrint(program, options, pDeclarationSpecifiers, bIsPointer, pItem, b, fp);
        }

        //Output_Append(fp, "}");
    }


    return true;
}

static bool TInitializerList_CodePrint2(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    bool bIsPointer,
    TInitializerList*p,
    bool b,
    StrBuilder* fp)
{


    b = false;

    if (List_HasOneItem(p) &&
        List_Back(p)->pInitializer == NULL/* &&
        pSpecifierQualifierList != NULL*/)
    {
        //a partir de {} e um tipo consegue gerar o final
        BuildInitialization2(program, options, pSpecifierQualifierList, bIsPointer, fp);
        ASSERT(false);
    }
    else
    {
        //TNodeClueList_CodePrint(&p->ClueList, fp, 0);

        //Output_Append(fp, "{");

        ForEachListItem(TInitializerListItem, pItem, p)
        {
            if (!List_IsFirstItem(p, pItem))
                Output_Append(fp, ",");

            b = TInitializerListItem_CodePrint2(program, options,
                pSpecifierQualifierList,
                bIsPointer, pItem, b, fp);
        }

        //Output_Append(fp, "}");
    }


    return true;
}


static bool TInitializerListType_CodePrint2(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    bool bIsPointer,
    TInitializerListType*p,
    bool b,
    StrBuilder* fp)
{

    if (List_HasOneItem(&p->InitializerList) &&
        List_Back(&p->InitializerList)->pInitializer == NULL /*&&
                                                             pSpecifierQualifierList != NULL*/)
    {
        //a partir de {} e um tipo consegue gerar o final
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        BuildInitialization2(program,
            options,
            pSpecifierQualifierList,
            bIsPointer,
            fp);
    }
    else
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, "{");

        b = TInitializerList_CodePrint2(program,
            options,
            pSpecifierQualifierList,
            bIsPointer,
            &p->InitializerList,
            b,
            fp);

        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, "}");
    }



    return true;
}


static bool TInitializerListType_CodePrint(TProgram* program,
    Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    bool bIsPointer,
    TInitializerListType*p,
    bool b,
    StrBuilder* fp)
{

    if (List_HasOneItem(&p->InitializerList) &&
        List_Back(&p->InitializerList)->pInitializer == NULL /*&&
        pSpecifierQualifierList != NULL*/)
    {
        //a partir de {} e um tipo consegue gerar o final
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        BuildInitialization(program,
            options,
            pDeclarationSpecifiers,
            bIsPointer,
            fp);
    }
    else
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, "{");

        b = TInitializerList_CodePrint(program,
            options,
            pDeclarationSpecifiers,
            bIsPointer,
            &p->InitializerList,
            b,
            fp);

        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, "}");
    }



    return true;
}



static bool TInitializer_CodePrint2(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    bool bIsPointer,
    TInitializer* pTInitializer,
    bool b,
    StrBuilder* fp)
{
    if (pTInitializer == NULL)
    {
        return false;
    }
    if (pTInitializer->Type == TInitializerListType_ID)
    {
        b = TInitializerListType_CodePrint2(program,
            options,
            pSpecifierQualifierList,
            bIsPointer,
            (TInitializerListType*)pTInitializer, b, fp);
    }
    else
    {
        b = TExpression_CodePrint(program, options, (TExpression*)pTInitializer, "", false, fp);
    }

    return b;
}


static bool TInitializer_CodePrint(TProgram* program,
    Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    bool bIsPointer,
    TInitializer* pTInitializer,
    bool b,
    StrBuilder* fp)
{
    if (pTInitializer == NULL)
    {
        return false;
    }
    if (pTInitializer->Type == TInitializerListType_ID)
    {
        b = TInitializerListType_CodePrint(program,
            options,
            pDeclarationSpecifiers,
            bIsPointer,
            (TInitializerListType*)pTInitializer, b, fp);
    }
    else
    {
        b = TExpression_CodePrint(program, options, (TExpression*)pTInitializer, "", false, fp);
    }

    return b;
}



static bool TPointerList_CodePrint(TProgram* program, Options * options, TPointerList *p, bool b, StrBuilder* fp)
{
    b = false;

    ForEachListItem(TPointer, pItem, p)
    {
        b = TPointer_CodePrint(program, options, pItem, b, fp);
    }

    return true;
}



static bool TParameterList_CodePrint(TProgram* program, Options * options, TParameterList *p, bool b, StrBuilder* fp)
{
    b = false;
    

    ForEachListItem(TParameterDeclaration, pItem, p)
    {
        //if (!List_IsFirstItem(p, pItem))
        //{
          //  TNodeClueList_CodePrint(options, &pItem->ClueList, fp);
//            Output_Append(fp, ",");
        //}
        //TParameterDeclaration * pItem = p->pItems[i];
        b = TParameterDeclaration_CodePrint(program, options, pItem, b, fp);
    }


    return true;
}

static bool TParameterTypeList_CodePrint(TProgram* program, Options * options, TParameterTypeList *p, bool b, StrBuilder* fp)
{
    //Output_Append(fp, "(");
    TParameterList_CodePrint(program, options, &p->ParameterList, b, fp);
    
    if (p->bVariadicArgs)
    {
        //TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        //Output_Append(fp, ",");

        TNodeClueList_CodePrint(options, &p->ClueList1, fp);
        Output_Append(fp, "...");
    }
    //Output_Append(fp, ")");
    return b;
}

static bool TDirectDeclarator_CodePrint(TProgram* program, Options * options, TDirectDeclarator* pDirectDeclarator,
    bool b,
    StrBuilder* fp)
{
    if (pDirectDeclarator == NULL)
    {
        return false;
    }
    //fprintf(fp, "{");
    b = false;

    if (pDirectDeclarator->Identifier)
    {
        //identifier
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList0, fp);
        Output_Append(fp, pDirectDeclarator->Identifier);
        b = true;
    }
    else  if (pDirectDeclarator->pDeclarator)
    {
        //( declarator )
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList0, fp);
        Output_Append(fp, "(");

        b = TDeclarator_CodePrint(program, options, pDirectDeclarator->pDeclarator, b, fp);

        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList1, fp);
        Output_Append(fp, ")");
    }

    if (pDirectDeclarator->Type == TDirectDeclaratorTypeArray)
    {
        /*
        direct-declarator [ type-qualifier-listopt assignment-expressionopt ]
        direct-declarator [ static type-qualifier-listopt assignment-expression ]
        direct-declarator [ type-qualifier-list static assignment-expression ]
        */
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList2, fp);
        Output_Append(fp, "[");
        if (pDirectDeclarator->pExpression)
        {
            b = TExpression_CodePrint(program, options, pDirectDeclarator->pExpression, "assignment-expression", b, fp);
        }
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList3, fp);
        Output_Append(fp, "]");
    }


    if (pDirectDeclarator->Type == TDirectDeclaratorTypeFunction)
    {
        //( parameter-type-list )
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList2, fp);
        Output_Append(fp, "(");
        TParameterTypeList_CodePrint(program, options, &pDirectDeclarator->Parameters, b, fp);
        TNodeClueList_CodePrint(options, &pDirectDeclarator->ClueList3, fp);
        Output_Append(fp, ")");
    }

    if (pDirectDeclarator->pDirectDeclarator)
    {
        //fprintf(fp, "\"direct-declarator\":");
        TDirectDeclarator_CodePrint(program, options, pDirectDeclarator->pDirectDeclarator, b, fp);
    }


    //fprintf(fp, "}");
    return b;
}

static bool TDeclarator_CodePrint(TProgram* program, Options * options, TDeclarator* p, bool b, StrBuilder* fp)
{
    b = TPointerList_CodePrint(program, options, &p->PointerList, b, fp);
    b = TDirectDeclarator_CodePrint(program, options, p->pDirectDeclarator, b, fp);
    return b;
}

bool TInitDeclarator_CodePrint(TProgram* program, Options * options, TInitDeclarator* p, bool b, StrBuilder* fp);



bool TStructDeclarator_CodePrint(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    TStructDeclarator* p,
    bool b,
    StrBuilder* fp)
{
    b = false;
    b = TDeclarator_CodePrint(program, options, p->pDeclarator, b, fp);
    if (p->pInitializer)
    {
        Output_Append(fp, " /* = ");

        Options opt = *options;
        opt.bExpandMacros = true;
        opt.bIncludeComments = false;

        TInitializer_CodePrint2(program,
            &opt,
            pSpecifierQualifierList,
            TPointerList_IsPointer(&p->pDeclarator->PointerList),
            p->pInitializer,
            b,
            fp);
        Output_Append(fp, " */");
    }
    return true;
}

static bool TStructDeclaratorList_CodePrint(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    TStructDeclaratorList *p,
    bool b,
    StrBuilder* fp)
{
    b = false;



    ForEachListItem(TInitDeclarator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
        {
            TNodeClueList_CodePrint(options, &pItem->ClueList0, fp);
            Output_Append(fp, ",");
        }
        b = TStructDeclarator_CodePrint(program, options, pSpecifierQualifierList, pItem, b, fp);
    }


    return true;
}

static bool TStructDeclaration_CodePrint(TProgram* program,
    Options * options,
    TStructDeclaration* p,
    bool b,
    StrBuilder* fp)
{
    TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, false, fp);
    //b = TTypeQualifierList_CodePrint(program, options, &p->Qualifier, false, fp);
    //b = TTypeSpecifier_CodePrint(program, options, p->pSpecifier, b, fp);
    b = TStructDeclaratorList_CodePrint(program,
        options,
        &p->SpecifierQualifierList,
        &p->DeclaratorList, b, fp);


    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, ";");

    return true;
}

static bool TAnyStructDeclaration_CodePrint(TProgram* program, Options * options, TAnyStructDeclaration* p, bool b, StrBuilder* fp)
{
    switch (p->Type)
    {
        case TStructDeclaration_ID:
        b = TStructDeclaration_CodePrint(program, options, (TStructDeclaration*)p, b, fp);
        break;

        default:
        ASSERT(false);
        break;
    }

    return b;
}

static bool StorageSpecifier_CodePrint(TProgram* program, Options * options, TStorageSpecifier* p, bool b, StrBuilder* fp)
{

    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    if (p->bIsAuto)
    {
        Output_Append(fp, "auto");
        b = true;
    }

    if (p->bIsExtern)
    {
        Output_Append(fp, "extern");
        b = true;
    }

    if (p->bIsRegister)
    {
        Output_Append(fp, "register");
        b = true;
    }

    if (p->bIsStatic)
    {
        Output_Append(fp, "static");
        b = true;
    }




    if (p->bIsThread_local)
    {
        Output_Append(fp, "[Thread_local]");
        b = true;
    }

    if (p->bIsTypedef)
    {
        Output_Append(fp, "typedef");
        b = true;
    }

    return b;
}



static bool TTemplateTypeSpecifier_CodePrint(TProgram* program, Options * options, TTemplateTypeSpecifier* p, bool b, StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    if (strcmp(p->Identifier, "List") == 0)
    {
        
        StrBuilder strBuilder = STRBUILDER_INIT;
        
        if (p->Args.pHead != NULL)
        {
            TTypeName_CodePrint(program, options, &p->Args.pHead->TypeName, false, &strBuilder);
        }
        else
        {
            //TODO
            //tem que ter 1 arg
        }
        

        Output_Append(fp, "struct {");
        Output_Append(fp, strBuilder.c_str);
        Output_Append(fp, "* pHead; ");
        Output_Append(fp, strBuilder.c_str);
        Output_Append(fp, "* pTail; }");

        StrBuilder_Destroy(&strBuilder);
    }
    else if (strcmp(p->Identifier, "Union") == 0)
    {
        Output_Append(fp, "struct { int type; }");        
    }
    else
    {
        //ERROR
        printf("ERROR _Template\n");
        Output_Append(fp, "struct { /*error*/}");

        //TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        //Output_Append(fp, "_Template");


        //Output_Append(fp, "(");
        //Output_Append(fp, p->Identifier);
        //Output_Append(fp, ",");
        //TTypeName_CodePrint(program, options, &p->TypeName, b, fp);

        //Output_Append(fp, ")");
    }
    return b;
}

static bool TFunctionSpecifier_CodePrint(TProgram* program, Options * options, TFunctionSpecifier* p, bool b, StrBuilder* fp)
{
    if (p->bIsInline)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, " inline");
        b = true;
    }
    if (p->bIsNoReturn)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, " [noreturn]");
        b = true;
    }
    return b;
}


static bool TTypeQualifier_CodePrint(TProgram* program, Options * options, TTypeQualifier* p, bool b, StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);

    if (p->bIsAtomic)
    {
        Output_Append(fp, "_Atomic");
        b = true;
    }


    if (p->bIsConst)
    {
        Output_Append(fp, "const");
        b = true;
    }

    if (p->bIsRestrict)
    {
        Output_Append(fp, "restrict");
        b = true;
    }
    if (p->bIsVolatile)
    {
        Output_Append(fp, "volatile");
        b = true;
    }
    return b;
}

static bool TTypeQualifierList_CodePrint(TProgram* program, Options * options, TTypeQualifierList* p, bool b, StrBuilder* fp)
{
    ForEachListItem(TTypeQualifier, pItem, p)
    {
        b = TTypeQualifier_CodePrint(program, options, pItem, b, fp);
    }
    return b;
}
static bool TPointer_CodePrint(TProgram* program, Options * options, TPointer* pPointer, bool b, StrBuilder* fp)
{
    if (pPointer->bPointer)
    {
        TNodeClueList_CodePrint(options, &pPointer->ClueList0, fp);
        Output_Append(fp, "*");
    }
    else
    {
        TTypeQualifierList_CodePrint(program, options, &pPointer->Qualifier, false, fp);
    }

    return true;
}

static bool TSpecifierQualifierList_CodePrint(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pDeclarationSpecifiers,
    bool b,
    StrBuilder* fp)
{
    ForEachListItem(TSpecifierQualifier, pItem, pDeclarationSpecifiers)
    {
        switch (pItem->Type)
        {

            CASE(TSingleTypeSpecifier) :
                TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier*)pItem, b, fp);
            break;

            CASE(TStorageSpecifier) :
                StorageSpecifier_CodePrint(program, options, (TStorageSpecifier*)pItem, b, fp);
            break;
            CASE(TTypeQualifier) :
                TTypeQualifier_CodePrint(program, options, (TTypeQualifier*)pItem, b, fp);
            break;
            CASE(TFunctionSpecifier) :
                TFunctionSpecifier_CodePrint(program, options, (TFunctionSpecifier*)pItem, b, fp);
            break;
            //CASE(TAlignmentSpecifier) : 
                ///TAlignmentSpecifier_CodePrint(program, options, (TAlignmentSpecifier*)pItem, b, fp);
                //break;

            CASE(TStructUnionSpecifier) :
                TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier*)pItem, b, fp);
            break;

            CASE(TEnumSpecifier) :
                TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier*)pItem, b, fp);
            break;

            default:
            ASSERT(false);
            break;
        }
    }

    return b;
}

static bool TDeclarationSpecifiers_CodePrint(TProgram* program, Options * options, TDeclarationSpecifiers* pDeclarationSpecifiers, bool b, StrBuilder* fp)
{

    ForEachListItem(TSpecifier, pItem, pDeclarationSpecifiers)
    {
        switch (pItem->Type)
        {

            CASE(TSingleTypeSpecifier) :
                TSingleTypeSpecifier_CodePrint(program, options, (TSingleTypeSpecifier*)pItem, b, fp);
            break;

            CASE(TStructUnionSpecifier) :
                TStructUnionSpecifier_CodePrint(program, options, (TStructUnionSpecifier*)pItem, b, fp);
            break;

            CASE(TEnumSpecifier) :
                TEnumSpecifier_CodePrint(program, options, (TEnumSpecifier*)pItem, b, fp);
            break;

            CASE(TStorageSpecifier) :
                StorageSpecifier_CodePrint(program, options, (TStorageSpecifier*)pItem, b, fp);
            break;
            CASE(TTypeQualifier) :
                TTypeQualifier_CodePrint(program, options, (TTypeQualifier*)pItem, b, fp);
            break;
            CASE(TFunctionSpecifier) :
                TFunctionSpecifier_CodePrint(program, options, (TFunctionSpecifier*)pItem, b, fp);
            break;

            CASE(TTemplateTypeSpecifier) :
                TTemplateTypeSpecifier_CodePrint(program, options, (TTemplateTypeSpecifier*)pItem, b, fp);
            break;
            //CASE(TAlignmentSpecifier) : 
            ///TAlignmentSpecifier_CodePrint(program, options, (TAlignmentSpecifier*)pItem, b, fp);
            //break;

            default:
            ASSERT(false);
            break;
        }
    }

    return b;

    //pDeclarationSpecifiers

    //    b = TFunctionSpecifier_CodePrint(program, options, &pDeclarationSpecifiers->FunctionSpecifiers, b, fp);
      //  b = StorageSpecifier_CodePrint(program, options, &pDeclarationSpecifiers->StorageSpecifiers, b, fp);
        //b = TTypeQualifierList_CodePrint(program, options, &pDeclarationSpecifiers->TypeQualifiers, b, fp);
        //b = TTypeSpecifier_CodePrint(program, options, pDeclarationSpecifiers->pTypeSpecifierOpt, b, fp);
    return b;
}

bool TInitDeclarator_CodePrint(TProgram* program, Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    bool bIsPointer,
    TInitDeclarator* p,
    bool b, StrBuilder* fp)
{
    b = false;
    b = TDeclarator_CodePrint(program, options, p->pDeclarator, b, fp);

    if (p->pInitializer)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, "=");
        b = TInitializer_CodePrint(program,
            options,
            pDeclarationSpecifiers,
            bIsPointer,
            p->pInitializer,
            b,
            fp);
    }
    return true;
}

//bool TInitDeclarator_CodePrint(TInitDeclarator* p, bool b, StrBuilder* fp);

bool TInitDeclaratorList_CodePrint(TProgram* program, Options * options,
    TDeclarationSpecifiers *pDeclarationSpecifiers,
    TInitDeclaratorList *p,
    bool b,
    StrBuilder* fp)
{
    b = false;
    //fprintf(fp, "[");
    ForEachListItem(TInitDeclarator, pInitDeclarator, p)
    {
        if (!List_IsFirstItem(p, pInitDeclarator))
            Output_Append(fp, ",");

        bool bIsPointer =
            TPointerList_IsPointer(&pInitDeclarator->pDeclarator->PointerList);

        b = TInitDeclarator_CodePrint(program, options, pDeclarationSpecifiers, bIsPointer, pInitDeclarator, b, fp);
    }

    //  fprintf(fp, "]");
    return true;
}
static bool HasFunction(TProgram* program, const char* prefix, const char* suffix)
{
    StrBuilder nameDestroy = STRBUILDER_INIT;
    StrBuilder_Append(&nameDestroy, prefix);
    StrBuilder_Append(&nameDestroy, suffix);
    TDeclaration * pDeclaration2 = TProgram_GetFinalTypeDeclaration(program, nameDestroy.c_str);
    StrBuilder_Destroy(&nameDestroy);
    return pDeclaration2 != NULL;
}

static bool Template_CodePrint(TProgram* program,
    Options * options,
    TDeclaration* p,
    bool b,
    StrBuilder* fp)
{
    /*
      typedef struct Array { int data; ... } Items;
      void Items_Add(Items* p,int i) {...}
      void Items_Delete(Items* p,int i) {...}


      typedef struct Map { const char* key;
      int data; ... } Items;

    */

    if (p->InitDeclaratorList.pHead != NULL &&
        p->InitDeclaratorList.pHead->pNext == NULL)
    {
        TInitDeclarator *pInitDeclarator =
            p->InitDeclaratorList.pHead;

        const char* functionName =
            pInitDeclarator->pDeclarator->pDirectDeclarator->Identifier;

        if (IsSuffix(functionName, "_Create"))
        {
            TSingleTypeSpecifier *pSingleTypeSpecifier =
                TSpecifier_As_TSingleTypeSpecifier(p->Specifiers.pHead);

            if (pSingleTypeSpecifier != NULL &&
                pSingleTypeSpecifier->bIsTypeDef)
            {
                StrBuilder strBuilder = STRBUILDER_INIT;

                //ve se ja colocou a implementacao do template
                StrBuilder_Append(fp, "\n");
                StrBuilder_Append(fp, "    ");

                StrBuilder_Append(fp,
                                  pSingleTypeSpecifier->TypedefName);

                StrBuilder_Append(fp,
                                  "* p = (");
                StrBuilder_Append(fp,
                                  pSingleTypeSpecifier->TypedefName);
                StrBuilder_Append(fp,
                                  "*) malloc(sizeof * p);\n"
                                  "   if (p)\n"
                                  "   {\n"
                                  "      ");
                ///////

                if (HasFunction(program, pSingleTypeSpecifier->TypedefName, "_Init"))
                {

                    StrBuilder_Append(fp,
                                      pSingleTypeSpecifier->TypedefName);
                    StrBuilder_Append(fp,
                                      "_Init(p);\n");
                    //

                }
                else
                {
                    BuildInitializationForTypedef(program,
                        options,
                        pSingleTypeSpecifier->TypedefName,
                        &strBuilder);

                    StrBuilder_Append(fp,
                                      pSingleTypeSpecifier->TypedefName);

                    StrBuilder_Append(fp,
                                      " temp = ");

                    StrBuilder_Append(fp, strBuilder.c_str);

                    StrBuilder_Append(fp,
                                      ";\n"
                                      "      *p = temp;\n");
                }
                StrBuilder_Append(fp,
                                  "   }\n"
                                  "   return p; \n");

                StrBuilder_Destroy(&strBuilder);
            }
        }
        else if (IsSuffix(functionName, "_Delete"))
        {
            TParameterDeclaration* pParameterDeclaration =
                pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

            if (pParameterDeclaration != NULL)
            {
                TSingleTypeSpecifier *pSingleTypeSpecifier =
                    TSpecifier_As_TSingleTypeSpecifier(pParameterDeclaration->Specifiers.pHead);

                if (pSingleTypeSpecifier != NULL &&
                    pSingleTypeSpecifier->bIsTypeDef)
                {

                    StrBuilder_Append(fp,
                        "\n"
                        "   if (p)\n"
                        "   {\n"
                        "      ");

                    StrBuilder_Append(fp, pSingleTypeSpecifier->TypedefName);

                    StrBuilder_Append(fp,
                        "_Destroy(p);\n"
                        "      free(p);\n"
                        "   }\n");
                }
            }

        }
        else if (IsSuffix(functionName, "_ToString"))
        {
            TParameterDeclaration* pParameterDeclaration =
                pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

            if (pParameterDeclaration != NULL)
            {
                TSingleTypeSpecifier *pSingleTypeSpecifier =
                    TSpecifier_As_TSingleTypeSpecifier(pParameterDeclaration->Specifiers.pHead);

                if (pSingleTypeSpecifier != NULL &&
                    pSingleTypeSpecifier->bIsTypeDef)
                {
                    const char * typedefName = pSingleTypeSpecifier->TypedefName;

                    TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
                    if (pDeclaration)
                    {
                        TEnumSpecifier* pEnumSpecifier =
                            TSpecifier_As_TEnumSpecifier(pDeclaration->Specifiers.pHead->pNext);

                        if (pEnumSpecifier)
                        {
                            StrBuilder_Append(fp, "\n");
                            StrBuilder_Append(fp, "    switch (e) {\n");
                            ForEachListItem(TEnumerator, pItem, &pEnumSpecifier->EnumeratorList)
                            {
                                StrBuilder_Append(fp, "        case ");
                                StrBuilder_Append(fp, pItem->Name);
                                StrBuilder_Append(fp, ": return \"");
                                StrBuilder_Append(fp, pItem->Name);
                                StrBuilder_Append(fp, "\";\n");
                            }
                            StrBuilder_Append(fp, "    }\n");
                            StrBuilder_Append(fp, "    return \"\";\n");
                        }
                        //Tem que ver se o typedef nao era ponteiro tb
                        //TDeclarator* pDeclarator = TDeclaration_FindDeclarator(p, typedefName);
                        //if (pDeclarator)
                        //{

                        //}
                    }
                }
            }
        }
        else if (IsSuffix(functionName, "_Destroy"))
        {
            TParameterDeclaration* pParameterDeclaration =
                pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

            if (pParameterDeclaration != NULL)
            {
                TSingleTypeSpecifier *pSingleTypeSpecifier =
                    TSpecifier_As_TSingleTypeSpecifier(pParameterDeclaration->Specifiers.pHead);

                if (pSingleTypeSpecifier != NULL &&
                    pSingleTypeSpecifier->bIsTypeDef)
                {
                    const char * typedefName = pSingleTypeSpecifier->TypedefName;

                    TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
                    if (pDeclaration)
                    {
                        TStructUnionSpecifier* pStructUnionSpecifier =
                            TSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pHead->pNext);

                        if (pStructUnionSpecifier)
                        {
                            StrBuilder_Append(fp, "\n");

                            for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.size; i++)
                            {
                                TStructDeclaration* pItem =
                                    TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[i]);

                                if (pItem)
                                {
                                    ForEachListItem(TSpecifierQualifier, pSpecifierQualifier, &pItem->SpecifierQualifierList)
                                    {
                                        TSingleTypeSpecifier* pSingleTypeSpecifier2 =
                                            TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
                                        if (pSingleTypeSpecifier2 != NULL &&
                                            pSingleTypeSpecifier2->bIsTypeDef)
                                        {
                                            StrBuilder nameDestroy = STRBUILDER_INIT;
                                            const char* typedefName2 = pSingleTypeSpecifier2->TypedefName;

                                            StrBuilder_Append(&nameDestroy, typedefName2);
                                            StrBuilder_Append(&nameDestroy, "_Destroy");
                                            TDeclaration * pDeclaration2 = TProgram_GetFinalTypeDeclaration(program, nameDestroy.c_str);

                                            StrBuilder_Destroy(&nameDestroy);
                                            if (pDeclaration2)
                                            {

                                                //if (pDeclaration2->Specifiers.pHead->pNext)
                                                //{
                                                    //TStructUnionSpecifier* pStructUnionSpecifier2 =
                                                        //TSpecifier_As_TStructUnionSpecifier(pDeclaration2->Specifiers.pHead->pNext);
                                                    //if (pStructUnionSpecifier2)
                                                    //{
                                                const char* name = pDeclaration2->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Identifier;
                                                ForEachListItem(TStructDeclarator, pTStructDeclarator, &pItem->DeclaratorList)
                                                {
                                                    StrBuilder_Append(fp, "    ");
                                                    StrBuilder_Append(fp, typedefName2);
                                                    StrBuilder_Append(fp, "_Destroy(&p->");
                                                    StrBuilder_Append(fp, pTStructDeclarator->pDeclarator->pDirectDeclarator->Identifier);
                                                    StrBuilder_Append(fp, ");\n");

                                                }
                                                //}
                                                //else
                                                //{

                                                //}
                                            //}
                                            }

                                        }
                                    }

                                    StrBuilder_Append(fp, "\n");
                                }
                            }

                        }

                        //Tem que ver se o typedef nao era ponteiro tb
                        //TDeclarator* pDeclarator = TDeclaration_FindDeclarator(p, typedefName);
                        //if (pDeclarator)
                        //{

                        //}
                    }
                }
            }
        }//destroy

        TParameterDeclaration* pParameterDeclaration =
            pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

        if (pParameterDeclaration != NULL)
        {
            StrBuilder strBuilderType = STRBUILDER_INIT;
            StrBuilder strBuilderFunc =  STRBUILDER_INIT;

            GetTypeAndFunction(functionName,
                                   &strBuilderType,
                                   &strBuilderFunc);

            TSingleTypeSpecifier *pSingleTypeSpecifier =
                TSpecifier_As_TSingleTypeSpecifier(pParameterDeclaration->Specifiers.pHead);

            if (pSingleTypeSpecifier != NULL &&
                pSingleTypeSpecifier->bIsTypeDef)
            {
                const char * typedefName = pSingleTypeSpecifier->TypedefName;

                TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
                if (pDeclaration)
                {
                    TStructUnionSpecifier* pTStructUnionSpecifier3 =
                        TSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pHead->pNext);

                    if (pTStructUnionSpecifier3 && pTStructUnionSpecifier3->TemplateName)
                    {
                        //eh template tipo
                        if (strcmp(pTStructUnionSpecifier3->TemplateName, "Union") == 0)
                        {
                            StrBuilder_Append(fp, "\n");
                            StrBuilder_Append(fp, "    switch(p->type) {\n");
                            ForEachListItem(TTemplateTypeSpecifierArgument, pItem, (TTemplateTypeSpecifierArgumentList*)&pTStructUnionSpecifier3->Args)
                            {
                                TSingleTypeSpecifier* pSingleTypeSpecifier =
                                 TSpecifier_As_TSingleTypeSpecifier(pItem->TypeName.SpecifierQualifierList.pHead);
                                if (pSingleTypeSpecifier && pSingleTypeSpecifier->bIsTypeDef)
                                {
                                    const char* typedefName = pSingleTypeSpecifier->TypedefName;
                                    TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
                                    if (pDeclaration)
                                    {
                                        TStructUnionSpecifier* pStructUnionSpecifier =
                                            TSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pHead->pNext);

                                        if (pStructUnionSpecifier && 
                                            pStructUnionSpecifier->StructDeclarationList.size > 0)
                                        {
                                            TStructDeclaration* pStructDeclaration =
                                                TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[0]);
                                            if (pStructDeclaration)
                                            {
                                                TPrimaryExpressionValue* pExpression =
                                                  TExpression_As_TPrimaryExpressionValue(TInitializer_As_TExpression(pStructDeclaration->DeclaratorList.pHead->pInitializer));
                                                
                                                if (pExpression)
                                                {

                                                    StrBuilder_Append(fp, "    case ");
                                                    StrBuilder_Append(fp, pExpression->lexeme);
                                                    StrBuilder_Append(fp, ":\n");

                                                    StrBuilder_Append(fp, "        ");
                                                    

                                                    StrBuilder_Append(fp, typedefName);
                                                    StrBuilder_Append(fp, strBuilderFunc.c_str);
                                                    
                                                    StrBuilder_Append(fp, "(");
                                                    StrBuilder_Append(fp, "(");
                                                    StrBuilder_Append(fp, typedefName);
                                                    StrBuilder_Append(fp, "*) p");
                                                    StrBuilder_Append(fp, ");\n");

                                                    StrBuilder_Append(fp, "    break;\n");

                                                    
                                                }

                                            }

                                        }
                                    }
                                
                                 
                                }

                               
                            }
                            StrBuilder_Append(fp, "    }\n");
                        }
                    }
                }
            }

            StrBuilder_Destroy(&strBuilderType);
            StrBuilder_Destroy(&strBuilderFunc);

        }
        //
        if (IsSuffix(functionName, "_Add") ||
            IsSuffix(functionName, "_Destroy") ||
            IsSuffix(functionName, "_Init"))
        {
            TParameterDeclaration* pParameterDeclaration =
                pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

            if (pParameterDeclaration != NULL)
            {
                TSingleTypeSpecifier *pSingleTypeSpecifier =
                    TSpecifier_As_TSingleTypeSpecifier(pParameterDeclaration->Specifiers.pHead);

                if (pSingleTypeSpecifier != NULL &&
                    pSingleTypeSpecifier->bIsTypeDef)
                {
                    const char * typedefName = pSingleTypeSpecifier->TypedefName;

                    TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
                    if (pDeclaration)
                    {
                        TStructUnionSpecifier* pStructUnionSpecifier4 =
                            TSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pHead->pNext);

                        if (pStructUnionSpecifier4 && pStructUnionSpecifier4->TemplateName)
                        {
                            if (IsSuffix(functionName, "_Add") &&
                                strcmp(pStructUnionSpecifier4->TemplateName, "List") == 0)
                            {
                                StrBuilder_Append(fp, "\n"
                                "    if (pList->pHead == NULL) {\n"
                                "        pList->pHead = pItem; \n"
                                "        pList->pTail = pItem; \n"
                                "    }\n"
                                "    else\n"
                                "    {\n"
                                "        pList->pTail->pNext = pItem; \n"
                                "        pList->pTail = pItem; \n"
                                "    }\n");
                            }
                            else if (IsSuffix(functionName, "_Destroy") &&
                                strcmp(pStructUnionSpecifier4->TemplateName, "List") == 0)
                            {
                                StrBuilder strBuilder = STRBUILDER_INIT;
                                if (pStructUnionSpecifier4->Args.pHead)
                                {
                                    TTypeName_CodePrint(program, options, &pStructUnionSpecifier4->Args.pHead->TypeName, false, &strBuilder);
                                }
                                StrBuilder_Append(fp, "\n");
                                StrBuilder_Append(fp,
                                                  "\n   while (p->pHead) {\n");
                                StrBuilder_Append(fp, "    ");
                                StrBuilder_Append(fp, strBuilder.c_str);
                                StrBuilder_Append(fp,
                                                  "* pCurrent = p->pHead; \n"
                                                  "     p->pHead = p->pHead->pNext; \n");
                                StrBuilder_Append(fp, "    ");
                                StrBuilder_Append(fp, strBuilder.c_str);
                                StrBuilder_Append(fp, "_Delete(pCurrent); \n"
                                                  "    }\n");

                                StrBuilder_Destroy(&strBuilder);
                            }
                        }
                    }
                }
            }
        }//_Add

        if (IsSuffix(functionName, "_Init"))
        {
            TParameterDeclaration* pParameterDeclaration =
                pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

            if (pParameterDeclaration != NULL)
            {
                TSingleTypeSpecifier *pSingleTypeSpecifier =
                    TSpecifier_As_TSingleTypeSpecifier(pParameterDeclaration->Specifiers.pHead);

                if (pSingleTypeSpecifier != NULL &&
                    pSingleTypeSpecifier->bIsTypeDef)
                {
                    const char * typedefName = pSingleTypeSpecifier->TypedefName;

                    TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
                    if (pDeclaration)
                    {
                        TStructUnionSpecifier* pStructUnionSpecifier =
                            TSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pHead->pNext);

                        if (pStructUnionSpecifier)
                        {
                            StrBuilder_Append(fp, "\n");

                            for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.size; i++)
                            {
                                TStructDeclaration* pItem =
                                    TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[i]);

                                if (pItem)
                                {
                                    ForEachListItem(TSpecifierQualifier, pSpecifierQualifier, &pItem->SpecifierQualifierList)
                                    {
                                        TSingleTypeSpecifier* pSingleTypeSpecifier2 =
                                            TSpecifierQualifier_As_TSingleTypeSpecifier(pSpecifierQualifier);
                                        if (pSingleTypeSpecifier2 != NULL &&
                                            pSingleTypeSpecifier2->bIsTypeDef)
                                        {
                                            StrBuilder nameDestroy = STRBUILDER_INIT;
                                            const char* typedefName2 = pSingleTypeSpecifier2->TypedefName;

                                            StrBuilder_Append(&nameDestroy, typedefName2);
                                            StrBuilder_Append(&nameDestroy, "_Init");
                                            TDeclaration * pDeclaration2 = TProgram_GetFinalTypeDeclaration(program, nameDestroy.c_str);

                                            StrBuilder_Destroy(&nameDestroy);
                                            if (pDeclaration2)
                                            {

                                                //if (pDeclaration2->Specifiers.pHead->pNext)
                                                //{
                                                //TStructUnionSpecifier* pStructUnionSpecifier2 =
                                                //TSpecifier_As_TStructUnionSpecifier(pDeclaration2->Specifiers.pHead->pNext);
                                                //if (pStructUnionSpecifier2)
                                                //{
                                                const char* name = pDeclaration2->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Identifier;
                                                ForEachListItem(TStructDeclarator, pTStructDeclarator, &pItem->DeclaratorList)
                                                {
                                                    StrBuilder_Append(fp, "    ");
                                                    StrBuilder_Append(fp, typedefName2);
                                                    StrBuilder_Append(fp, "_Init(&p->");
                                                    StrBuilder_Append(fp, pTStructDeclarator->pDeclarator->pDirectDeclarator->Identifier);
                                                    StrBuilder_Append(fp, ");\n");

                                                }
                                                //}
                                                //else
                                                //{

                                                //}
                                                //}
                                            }

                                        }
                                    }

                                    StrBuilder_Append(fp, "\n");
                                }
                            }

                        }

                        //Tem que ver se o typedef nao era ponteiro tb
                        //TDeclarator* pDeclarator = TDeclaration_FindDeclarator(p, typedefName);
                        //if (pDeclarator)
                        //{

                        //}
                    }
                }
            }
        }//init
    }


    return b;
}

static bool TDeclaration_CodePrint(TProgram* program,
    Options * options,
    TDeclaration* p,
    bool b,
    StrBuilder* fp)
{
    b = TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, false, fp);

    b = TInitDeclaratorList_CodePrint(program,
        options,
        &p->Specifiers,
        &p->InitDeclaratorList, b, fp);

    if (p->pCompoundStatementOpt != NULL)
    {
        /*
           typedef struct Array { int data; ... } Items;
           void Items_Add(Items* p,int i) {...}
           void Items_Delete(Items* p,int i) {...}
        */

        if (p->bDefault)
        {
            TNodeClueList_CodePrint(options, &p->pCompoundStatementOpt->ClueList0, fp);
            Output_Append(fp, "{");

            Template_CodePrint(program,
                options,
                p,
                b,
                fp);


            TNodeClueList_CodePrint(options, &p->pCompoundStatementOpt->ClueList1, fp);
            Output_Append(fp, "}");


            return true;
        }
        else
        {
            if (p->pCompoundStatementOpt != NULL)
            {
                //normal
                TCompoundStatement_CodePrint(program,
                    options,
                    p->pCompoundStatementOpt,
                    b,
                    fp);
            }
        }
    }
    else
    {
        if (p->bDefault)
        {
            TNodeClueList_CodePrint(options, &p->ClueList1, fp);
            Output_Append(fp, " /*default*/\n");
            Output_Append(fp, "{");

            Template_CodePrint(program,
                options,
                p,
                b,
                fp);

            Output_Append(fp, "\n");
            Output_Append(fp, "}");

            return true;
        }
        else
        {
            TNodeClueList_CodePrint(options, &p->ClueList0, fp);
            Output_Append(fp, ";");
        }
    }


    return true;
}

static bool TTypeName_CodePrint(TProgram* program, Options * options, TTypeName* p, bool b, StrBuilder* fp)
{

    TSpecifierQualifierList_CodePrint(program, options, &p->SpecifierQualifierList, false, fp);

    //p->Declarator
    //b = TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, false, fp);


    b = TDeclarator_CodePrint(program, options, &p->Declarator, b, fp);

    return b;
}

static bool TParameterDeclaration_CodePrint(TProgram* program,
    Options * options,
    TParameterDeclaration* p,
    bool b,
    StrBuilder* fp)
{

    b = TDeclarationSpecifiers_CodePrint(program, options, &p->Specifiers, false, fp);


    b = TDeclarator_CodePrint(program, options, &p->Declarator, b, fp);

    if (p->bHasComma)
    {
        TNodeClueList_CodePrint(options, &p->ClueList0, fp);
        Output_Append(fp, ",");
    }

    return b;
}

static bool TStaticAssertDeclaration_CodePrint(TProgram* program,
                                               Options * options,
                                               TStaticAssertDeclaration *p,
                                               bool b,
                                               StrBuilder* fp)
{
    TNodeClueList_CodePrint(options, &p->ClueList0, fp);
    Output_Append(fp, "_StaticAssert");
    TNodeClueList_CodePrint(options, &p->ClueList1, fp);
    Output_Append(fp, "(");
    TExpression_CodePrint(program, options, p->pConstantExpression, "", b, fp);
    Output_Append(fp, ",");
    TNodeClueList_CodePrint(options, &p->ClueList2, fp);

    TNodeClueList_CodePrint(options, &p->ClueList3, fp);
    Output_Append(fp, p->Text);


    TNodeClueList_CodePrint(options, &p->ClueList4, fp);
    Output_Append(fp, ")");
    TNodeClueList_CodePrint(options, &p->ClueList5, fp);
    Output_Append(fp, ";");
    return true;
}

static bool TAnyDeclaration_CodePrint(TProgram* program, Options * options, TAnyDeclaration *pDeclaration, bool b, StrBuilder* fp)
{
    switch (pDeclaration->Type)
    {
        case TStaticAssertDeclaration_ID:
        b = TStaticAssertDeclaration_CodePrint(program, options, (TStaticAssertDeclaration*)pDeclaration, b, fp);
        break;

        case TDeclaration_ID:
        b = TDeclaration_CodePrint(program, options, (TDeclaration*)pDeclaration, b, fp);
        break;

        default:
        ASSERT(false);
        break;
    }

    return b;
}

static bool TDesignatorList_CodePrint(TProgram* program, Options * options, TDesignatorList *p, bool b, StrBuilder* fp)
{
    b = false;


    ForEachListItem(TDesignator, pItem, p)
    {
        if (!List_IsFirstItem(p, pItem))
        {
            Output_Append(fp, ",");
        }
        b = TDesignator_CodePrint(program, options, pItem, b, fp);
    }


    return true;
}

static bool TInitializerListItem_CodePrint2(TProgram* program,
    Options * options,
    TSpecifierQualifierList* pSpecifierQualifierList,
    bool bIsPointer,
    TInitializerListItem* p,
    bool b,
    StrBuilder* fp)
{

    b = false;

    if (!List_IsEmpty(&p->DesignatorList))
    {
        b = TDesignatorList_CodePrint(program, options, &p->DesignatorList, b, fp);
    }

    b = TInitializer_CodePrint2(program,
        options,
        pSpecifierQualifierList,
        bIsPointer,
        p->pInitializer,
        b,
        fp);

    return true;
}

static bool TInitializerListItem_CodePrint(TProgram* program,
    Options * options,
    TDeclarationSpecifiers* pDeclarationSpecifiers,
    bool bIsPointer,
    TInitializerListItem* p,
    bool b,
    StrBuilder* fp)
{

    b = false;

    if (!List_IsEmpty(&p->DesignatorList))
    {
        b = TDesignatorList_CodePrint(program, options, &p->DesignatorList, b, fp);
    }

    b = TInitializer_CodePrint(program,
        options,
        pDeclarationSpecifiers,
        bIsPointer,
        p->pInitializer,
        b,
        fp);

    return true;
}


static bool TDeclarations_CodePrint(TProgram* program, Options * options, TDeclarations *p, bool b, StrBuilder* fp)
{
    b = false;


    for (size_t i = 0; i < p->size; i++)
    {
        if (i > 0)
            Output_Append(fp, ",");

        TAnyDeclaration* pItem = p->pItems[i];
        b = TAnyDeclaration_CodePrint(program, options, pItem, b, fp);

    }

    return true;
}

/*
static void TProgram_PrintToFile(TProgram* pProgram,
                        const char* fileName)
{
  StrBuilder * fp = fopen(fileName, "w");
  TDeclarations_CodePrint(&pProgram->Declarations, false, fp);
  fclose(fp);
}*/


static void TProgram_PrintFiles(TProgram* pProgram,
    StrBuilder* fp,
    const char* userpath)
{
    //TODO tem que ter um teste especial..

    //o arqquivo externo que foi incluido por um aquivo local
    //deve ser incluido..se ele foi incluido por outro nao.
    //tem que marcar se foi incluido por um da lista de includes e nao incluir

    Output_Append(fp, "/*external files*/\n");
    for (int i = 0; i < pProgram->Files2.size; i++)
    {
        TFile *pFile = pProgram->Files2.pItems[i];
        if (pFile->bDirectInclude)
        {
            //char drive[_MAX_DRIVE];
            //char dir[_MAX_DIR];
            //char fname[_MAX_FNAME];
            //char ext[_MAX_EXT];
            //SplitPath(pFile->IncludePath, drive, dir, fname, ext); // C4996

            if (pFile->bSystemLikeInclude)
            {
                Output_Append(fp, "#include <");
                Output_Append(fp, pFile->IncludePath);
                Output_Append(fp, ">\n");
            }
            else
            {
                Output_Append(fp, "#include \"");
                Output_Append(fp, pFile->IncludePath);
                Output_Append(fp, "\"\n");
            }

        }
    }
    Output_Append(fp, "\n");
}


void TProgram_PrintCodeToFile(TProgram* pProgram,
    Options* options,
    const char* outFileName,
    const char* inputFileName)
{
    FILE * fp = fopen(outFileName, "w");
    bool b = false;

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


        b = TAnyDeclaration_CodePrint(pProgram, options, pItem, b, &sb);
#if 0
        if (options->TemplateDeclarations.size > 0)
        {
            fprintf(fp, "\n\n");
            fprintf(fp, "%s", options->TemplateDeclarations.c_str);
            fprintf(fp, "\n");
            StrBuilder_Clear(&options->TemplateDeclarations);
        }
        if (options->TemplateInstanciation.size > 0)
        {
            fprintf(fp, "%s", options->TemplateInstanciation.c_str);
            fprintf(fp, "\n\n");
            StrBuilder_Clear(&options->TemplateInstanciation);
        }
#endif

        fprintf(fp, "%s", sb.c_str);




        StrBuilder_Clear(&sb);
        k++;
    }
    StrBuilder_Destroy(&sb);
    fclose(fp);
}


