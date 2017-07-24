#include "..\CodePrint.h"
#include "..\..\Base\Array.h"
#include "..\..\Base\Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

static bool UnionPlugin_CodePrintCore(TProgram* program,
                                      Options * options,
                                      TStructUnionSpecifier* pTStructUnionSpecifier3,
                                      const char* strBuilderFunc,
                                      bool b,
                                      StrBuilder* fp);


//Instancia as funcoes especias new create delete
void UnionPlugin_BuildDestroy(TProgram* program,
    TStructUnionSpecifier* pStructUnionSpecifier,
    const char* pVariableName,
    bool bVariableNameIsPointer,
    BuildType buildType,
    StrBuilder* fp)
{
    if (strcmp(pStructUnionSpecifier->TemplateName, "Union") == 0)
    {
        StrBuilder itemTypeStr = STRBUILDER_INIT;


        TTypeName* pTypeName = NULL;
        Options  options = OPTIONS_INIT;
        if (pStructUnionSpecifier->Args.pHead)
        {
            pTypeName = &pStructUnionSpecifier->Args.pHead->TypeName;
            //TTypeName_CodePrint(program, &options, &pStructUnionSpecifier->Args.pHead->TypeName, false, &itemTypeStr);
            TSpecifierQualifierList_CodePrint(program, &options, &pStructUnionSpecifier->Args.pHead->TypeName.SpecifierQualifierList, false, &itemTypeStr);
        }

        switch (buildType)
        {
            case BuildTypeInit:
            StrBuilder_AppendFmt(fp, "static_assert(false, \"er\";\n", pVariableName);
            break;
            case BuildTypeDestroy:
            //Implementa 'default'
            UnionPlugin_CodePrintCore(program,
                                      &options,
                                      pStructUnionSpecifier,
                                      "_Destroy",
                                      false,
                                      fp);

            break;

            case BuildTypeDelete:

            //Implementa 'default'
            UnionPlugin_CodePrintCore(program,
                                      &options,
                                      pStructUnionSpecifier,
                                                  "_Delete",
                                                  false,
                                                  fp);

            break;
            case BuildTypeCreate:
            case BuildTypeStaticInit:
            StrBuilder_AppendFmt(fp, "static_assert(false, \"er\";\n", pVariableName);
            break;
            default:
            break;
        }
        StrBuilder_Destroy(&itemTypeStr);
    }
}


void Output_Append(StrBuilder* p,
    const char* source);

//Gera estrutura de ad
bool UnionPlugin_Type_CodePrint(TProgram* program,
    Options * options,
    TStructUnionSpecifier* p,
    bool b, StrBuilder* fp)
{
    bool bResult = false;
    if (p->TemplateName != NULL)
    {
        if (strcmp(p->TemplateName, "Union") == 0)
        {
            if (p->Args.pHead)
            {
                bResult = true;
                Output_Append(fp, " ");
                Output_Append(fp, "{");

                Output_Append(fp, "int type;");

                Output_Append(fp, "}");
            }
            else
            {
                //error
            }
        }
    }

    return true;
}


bool IsSuffix(const char* s, const char* suffix);
TStructUnionSpecifier* GetStructSpecifier(TProgram* program, TDeclarationSpecifiers* specifiers);

bool GetTypeAndFunction(const char* source,
                        StrBuilder* strBuilderType,
                        StrBuilder* strBuilderFunc);

//Implementa 'default'
static bool UnionPlugin_CodePrintCore(TProgram* program,
    Options * options,
    TStructUnionSpecifier* pTStructUnionSpecifier3,
                                      const char* strBuilderFunc,
    bool b,
    StrBuilder* fp)
{
    bool bResult = false;


    if (pTStructUnionSpecifier3 && pTStructUnionSpecifier3->TemplateName)
    {
        //eh template tipo
        if (strcmp(pTStructUnionSpecifier3->TemplateName, "Union") == 0)
        {
            bResult = true;
            StrBuilder_Append(fp, "\n");
            StrBuilder_Append(fp, "    switch(p->type) {\n");
            ForEachListItem(TTemplateTypeSpecifierArgument, pItem, (TTemplateTypeSpecifierArgumentList*)&pTStructUnionSpecifier3->Args)
            {
                TSingleTypeSpecifier* pSingleTypeSpecifier =
                    TSpecifier_As_TSingleTypeSpecifier(pItem->TypeName.SpecifierQualifierList.pHead);
                if (pSingleTypeSpecifier && pSingleTypeSpecifier->Token == TK_IDENTIFIER)
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
                                    StrBuilder_Append(fp, strBuilderFunc);

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
    return bResult;
}


//Implementa 'default'
bool UnionPlugin_CodePrint(TProgram* program,
                           Options * options,
                           TDeclaration* p,
                           bool b,
                           StrBuilder* fp)
{
    bool bResult = false;

    if (p->InitDeclaratorList.pHead != NULL &&
        p->InitDeclaratorList.pHead->pNext == NULL)
    {
        TInitDeclarator *pInitDeclarator =
            p->InitDeclaratorList.pHead;

        const char* functionName =
            pInitDeclarator->pDeclarator->pDirectDeclarator->Identifier;

        TParameter* pParameterDeclaration =
            pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

        if (pParameterDeclaration != NULL)
        {
            StrBuilder strBuilderType = STRBUILDER_INIT;
            StrBuilder strBuilderFunc = STRBUILDER_INIT;

            GetTypeAndFunction(functionName,
                               &strBuilderType,
                               &strBuilderFunc);

            TSingleTypeSpecifier *pSingleTypeSpecifier =
                TSpecifier_As_TSingleTypeSpecifier(pParameterDeclaration->Specifiers.pHead);

            if (pSingleTypeSpecifier != NULL &&
                pSingleTypeSpecifier->Token == TK_IDENTIFIER)
            {
                const char * typedefName = pSingleTypeSpecifier->TypedefName;

                TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
                if (pDeclaration)
                {
                    TStructUnionSpecifier* pTStructUnionSpecifier3 =
                        TSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pHead->pNext);

                    UnionPlugin_CodePrintCore(program,
                                                          options,
                                                          pTStructUnionSpecifier3,
                                                          strBuilderFunc.c_str,
                                                          b,
                                                          fp);
                }
            }

            StrBuilder_Destroy(&strBuilderType);
            StrBuilder_Destroy(&strBuilderFunc);

        }
    }
    return bResult;
}
