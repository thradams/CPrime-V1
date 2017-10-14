#include "CodePrint.h"
#include "Array.h"
#include "Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

static bool UnionPlugin_CodePrintCore(TProgram* program,
    Options * options,
    TStructUnionSpecifier* pTStructUnionSpecifier3,
    const char* strBuilderFunc,
  
    StrBuilder* fp);

//Implementa 'default'
static bool CodePrintCasts(TProgram* program,
    Options * options,
    TStructUnionSpecifier* pTStructUnionSpecifier3,
    StrBuilder* fp);

//Instancia as funcoes especias new create delete
bool UnionPlugin_InstanciateSpecialFunctions(TProgram* program,
    TStructUnionSpecifier* pStructUnionSpecifier,
    const char* pVariableName,
    
    BuildType buildType,
    StrBuilder* fp)
{
    bool bInstanciated = false;

    if (strcmp(pStructUnionSpecifier->TemplateName, "Union") == 0)
    {
        StrBuilder itemTypeStr = STRBUILDER_INIT;


        TTypeName* pTypeName = NULL;
        Options  options = OPTIONS_INIT;
        if (pStructUnionSpecifier->Args.pHead)
        {
            pTypeName = &pStructUnionSpecifier->Args.pHead->TypeName;
            //TTypeName_CodePrint(program, &options, &pStructUnionSpecifier->Args.pHead->TypeName, false, &itemTypeStr);
            TSpecifierQualifierList_CodePrint(program, &options, &pStructUnionSpecifier->Args.pHead->TypeName.SpecifierQualifierList,  &itemTypeStr);
        }

        switch (buildType)
        {
        case BuildTypeInit:
            StrBuilder_AppendFmt(fp, "static_assert(false, \"er\";\n", pVariableName);
            break;
        case BuildTypeDestroy:

            StrBuilder_AppendFmt(fp, "/*\n");
            CodePrintCasts(program,
                &options,
                pStructUnionSpecifier,
                fp);
            StrBuilder_AppendFmt(fp, "*/\n");
            //Implementa 'default'
            UnionPlugin_CodePrintCore(program,
                &options,
                pStructUnionSpecifier,
                "_Destroy",
                
                fp);

            break;

        case BuildTypeDelete:

            //Implementa 'default'
            UnionPlugin_CodePrintCore(program,
                &options,
                pStructUnionSpecifier,
                "_Delete",
                
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
    return bInstanciated;
}


void Output_Append(StrBuilder* p,
    Options* options,
    const char* source);

//Gera estrutura de ad
bool UnionPlugin_InstanciateType(TProgram* program,
    Options * options,
    TStructUnionSpecifier* p,
    StrBuilder* fp)
{
    bool bInstanciated = false;
    if (p->TemplateName != NULL)
    {
        if (strcmp(p->TemplateName, "Union") == 0)
        {
            bInstanciated = true;
            int i = 0;
            Output_Append(fp, options, " Union(");
            ForEachListItem(TTemplateTypeSpecifierArgument, pItem, &p->Args)
            {
                if (i > 0)
                    Output_Append(fp, options, ",");
                TTypeName_CodePrint(program, options, &pItem->TypeName, fp);
                i++;
            }
            Output_Append(fp, options, ")");
        }
    }

    return bInstanciated;
}


bool IsSuffix(const char* s, const char* suffix);
TStructUnionSpecifier* GetStructSpecifier(TProgram* program, TDeclarationSpecifiers* specifiers);

bool GetTypeAndFunction(const char* source,
    StrBuilder* strBuilderType,
    StrBuilder* strBuilderFunc);

void GetAllUnionTypes(TProgram* program,
    TStructUnionSpecifier* pTStructUnionSpecifier3,
    Map2* map)
{
    ForEachListItem(TTemplateTypeSpecifierArgument, pItem, (TTemplateTypeSpecifierArgumentList*)&pTStructUnionSpecifier3->Args)
    {
        TSingleTypeSpecifier* pSingleTypeSpecifier =
            TSpecifier_As_TSingleTypeSpecifier(pItem->TypeName.SpecifierQualifierList.pHead);
        if (pSingleTypeSpecifier &&
            pSingleTypeSpecifier->Token == TK_IDENTIFIER)
        {
            const char* typedefName = pSingleTypeSpecifier->TypedefName;
            TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
            if (pDeclaration)
            {
                TStructUnionSpecifier* pStructUnionSpecifier =
                    TSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pHead->pNext);
                if (pStructUnionSpecifier)
                {
                    if (pStructUnionSpecifier->TemplateName != NULL &&
                        strcmp(pStructUnionSpecifier->TemplateName, "Union") == 0)
                    {
                        void *pv;
                        Map2_SetAt(map, typedefName, pStructUnionSpecifier, &pv);

                        GetAllUnionTypes(program,
                            pStructUnionSpecifier,
                            map);
                    }
                    else
                    {
                        void *pv;
                        Map2_SetAt(map, typedefName, pStructUnionSpecifier, &pv);
                    }
                }
            }
        }
    }
}

//Implementa 'default'
static bool UnionPlugin_CodePrintCore(TProgram* program,
    Options * options,
    TStructUnionSpecifier* pTStructUnionSpecifier3,
    const char* strBuilderFunc,

    StrBuilder* fp)
{
    bool bResult = false;


    if (pTStructUnionSpecifier3 && pTStructUnionSpecifier3->TemplateName)
    {
        //eh template tipo
        if (strcmp(pTStructUnionSpecifier3->TemplateName, "Union") == 0)
        {
            StrBuilder_Append(fp, "\n");
            StrBuilder_Append(fp, "    switch(p->type) {\n");


            Map2 map;
            Map2_Init(&map);
            GetAllUnionTypes(program,
                pTStructUnionSpecifier3,
                &map);

            if (map.pHashTable != NULL)
            {
                for (unsigned int nHash = 0;
                    nHash < map.nHashTableSize;
                    nHash++)
                {
                    MapItem2* pKeyValue =
                        map.pHashTable[nHash];
                    while (pKeyValue != NULL)
                    {
                        const char* typedefName = pKeyValue->Key;
                        TStructUnionSpecifier* pStructUnionSpecifier =
                            (TStructUnionSpecifier*)pKeyValue->pValue;
                        ////////


                        if (pStructUnionSpecifier &&
                            pStructUnionSpecifier->StructDeclarationList.size > 0 &&
                            pStructUnionSpecifier->TemplateName == NULL)
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

                        //////
                        pKeyValue = pKeyValue->pNext;
                    }
                }
            }
            StrBuilder_Append(fp, "    }\n");
            Map2_Destroy(&map);
        }
    }
    return bResult;
}



//Implementa 'default'
static bool CodePrintCasts(TProgram* program,
    Options * options,
    TStructUnionSpecifier* pTStructUnionSpecifier3,
    StrBuilder* fp)
{
    bool bResult = false;


    if (pTStructUnionSpecifier3 && pTStructUnionSpecifier3->TemplateName)
    {
        //eh template tipo
        if (strcmp(pTStructUnionSpecifier3->TemplateName, "Union") == 0)
        {
            Map2 map;
            Map2_Init(&map);
            GetAllUnionTypes(program,
                pTStructUnionSpecifier3,
                &map);

            if (map.pHashTable != NULL)
            {
                for (unsigned int nHash = 0;
                    nHash < map.nHashTableSize;
                    nHash++)
                {
                    MapItem2* pKeyValue =
                        map.pHashTable[nHash];
                    while (pKeyValue != NULL)
                    {
                        const char* typedefName = pKeyValue->Key;
                        TStructUnionSpecifier* pStructUnionSpecifier =
                            (TStructUnionSpecifier*)pKeyValue->pValue;
                        ////////


                        if (pStructUnionSpecifier)
                        {
                            StrBuilder_Append(fp, "inline ");
                            StrBuilder_Append(fp, typedefName);
                            StrBuilder_Append(fp, "* ");

                            if (pTStructUnionSpecifier3->Name)
                            {
                                StrBuilder_Append(fp, pTStructUnionSpecifier3->Name);
                            }
                            else
                            {
                            }
                            StrBuilder_Append(fp, "_As_");
                            StrBuilder_Append(fp, typedefName);
                            StrBuilder_Append(fp, "(");
                            if (pTStructUnionSpecifier3->Name)
                            {
                                StrBuilder_Append(fp, pTStructUnionSpecifier3->Name);
                            }
                            else
                            {
                            }
                            StrBuilder_Append(fp, "*p) ");
                            StrBuilder_Append(fp, "{");

                            if (pStructUnionSpecifier->StructDeclarationList.size > 0 &&
                                pStructUnionSpecifier->TemplateName == NULL)
                            {
                                TStructDeclaration* pStructDeclaration =
                                    TAnyStructDeclaration_As_TStructDeclaration(pStructUnionSpecifier->StructDeclarationList.pItems[0]);
                                if (pStructDeclaration)
                                {
                                    TPrimaryExpressionValue* pExpression =
                                        TExpression_As_TPrimaryExpressionValue(TInitializer_As_TExpression(pStructDeclaration->DeclaratorList.pHead->pInitializer));

                                    if (pExpression)
                                    {
                                        StrBuilder_Append(fp, "return p->type == ");
                                        StrBuilder_Append(fp, pExpression->lexeme);
                                        StrBuilder_Append(fp, " ? ");
                                        StrBuilder_Append(fp, "(");
                                        StrBuilder_Append(fp, typedefName);
                                        StrBuilder_Append(fp, "*) p : ");
                                        StrBuilder_Append(fp, "(");
                                        StrBuilder_Append(fp, typedefName);
                                        StrBuilder_Append(fp, "*) NULL;");
                                        
                                    }
                                }
                            }
                            else
                            {
                                StrBuilder_Append(fp, "return (");
                                StrBuilder_Append(fp, typedefName);
                                StrBuilder_Append(fp, "*) p;");                                
                            }
                        }
                        StrBuilder_Append(fp, "}\n");

                        //////////

                        StrBuilder_Append(fp, "inline ");
                        
                        if (pTStructUnionSpecifier3->Name)
                        {
                            StrBuilder_Append(fp, pTStructUnionSpecifier3->Name);
                        }
                        else
                        {
                        }
                        StrBuilder_Append(fp, "* ");

                        StrBuilder_Append(fp, typedefName);

                        StrBuilder_Append(fp, "_As_");
                        if (pTStructUnionSpecifier3->Name)
                        {
                            StrBuilder_Append(fp, pTStructUnionSpecifier3->Name);
                        }
                        else
                        {
                        }
                        StrBuilder_Append(fp, "(");
                        StrBuilder_Append(fp, typedefName);

                        
                        StrBuilder_Append(fp, "*p) ");
                        StrBuilder_Append(fp, "{");

                        StrBuilder_Append(fp, "return (");
                        if (pTStructUnionSpecifier3->Name)
                        {
                            StrBuilder_Append(fp, pTStructUnionSpecifier3->Name);
                        }
                        else
                        {
                        }
                        StrBuilder_Append(fp, "*) p;");

                        StrBuilder_Append(fp, "}\n");


                        ///////////
                        pKeyValue = pKeyValue->pNext;
                    }
                }
            }

            Map2_Destroy(&map);
        }
    }
    return bResult;
}

//Implementa 'default'
bool UnionPlugin_InstanciateFunction(TProgram* program,
    Options * options,
    TDeclaration* p,

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
                        
                        fp);
                }
            }

            StrBuilder_Destroy(&strBuilderType);
            StrBuilder_Destroy(&strBuilderFunc);

        }
    }
    return bResult;
}