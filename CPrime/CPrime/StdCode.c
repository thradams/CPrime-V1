#include "CodePrint.h"
#include "..\Base\Array.h"
#include "..\Base\Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>

void Output_Append(StrBuilder* p,
                   const char* source);

bool GetTypeAndFunction(const char* source,
                        StrBuilder* strBuilderType,
                        StrBuilder* strBuilderFunc);

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

static bool HasFunction(TProgram* program, const char* prefix, const char* suffix)
{
    StrBuilder nameDestroy = STRBUILDER_INIT;
    StrBuilder_Append(&nameDestroy, prefix);
    StrBuilder_Append(&nameDestroy, suffix);
    TDeclaration * pDeclaration2 = TProgram_GetFinalTypeDeclaration(program, nameDestroy.c_str);
    StrBuilder_Destroy(&nameDestroy);
    return pDeclaration2 != NULL;
}

//Gera estrutura de ad
bool StructTemplate_CodePrint(TProgram* program,
                              Options * options,
                              TStructUnionSpecifier* p, 
                              bool b, StrBuilder* fp)
{
    bool bResult = false;
    if (p->TemplateName != NULL)
    {
        if (strcmp(p->TemplateName, "List") == 0)
        {
            if (p->Args.pHead)
            {
                bResult = true;
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
        else if (strcmp(p->TemplateName, "Union") == 0)
        {
            bResult = true;
            Output_Append(fp, "{ int type; }");
        }
    }

    return true;
}

TStructUnionSpecifier* GetStructSpecifier(TProgram* program, TDeclarationSpecifiers* specifiers)
{
    TStructUnionSpecifier* pTStructUnionSpecifier =
        TSpecifier_As_TStructUnionSpecifier(specifiers->pHead);

    if (pTStructUnionSpecifier == NULL)
    {
        TSingleTypeSpecifier *pSingleTypeSpecifier =
            TSpecifier_As_TSingleTypeSpecifier(specifiers->pHead);

        if (pSingleTypeSpecifier != NULL &&
            pSingleTypeSpecifier->Token == TK_IDENTIFIER)
        {
            const char * typedefName = pSingleTypeSpecifier->TypedefName;

            TDeclaration * pDeclaration = TProgram_GetFinalTypeDeclaration(program, typedefName);
            if (pDeclaration)
            {
                pTStructUnionSpecifier =
                    TSpecifier_As_TStructUnionSpecifier(pDeclaration->Specifiers.pHead->pNext);

            }
        }
    }

    return pTStructUnionSpecifier;
}

bool InstanciateUnionTypeFunction(TProgram* program,
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
    }
    return bResult;
}


bool Std_Template_CodePrint(TProgram* program,
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

    bool bResult = InstanciateUnionTypeFunction(program,
                                      options,
                                      p,
                                      b,
                                      fp);
    if (bResult)    
    { 
       return true;
    }

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
                pSingleTypeSpecifier->Token == TK_IDENTIFIER)
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
            TParameter* pParameterDeclaration =
                pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

            if (pParameterDeclaration != NULL)
            {
                TSingleTypeSpecifier *pSingleTypeSpecifier =
                    TSpecifier_As_TSingleTypeSpecifier(pParameterDeclaration->Specifiers.pHead);

                if (pSingleTypeSpecifier != NULL &&
                    pSingleTypeSpecifier->Token == TK_IDENTIFIER)
                {

                    StrBuilder_Append(fp,
                                      "\n"
                                      "   if (p)\n"
                                      "   {\n"
                                      "      ");
                    StrBuilder str = STRBUILDER_INIT;
                    StrBuilder_Append(&str, pSingleTypeSpecifier->TypedefName);
                    StrBuilder_Append(&str, "_Destroy");

                    TDeclaration* pFunc = 
                        TProgram_FindFunctionDeclaration(program, str.c_str);

                    if (pFunc)
                    {
                        StrBuilder_Append(fp, str.c_str);
                        StrBuilder_Append(fp, "(p);\n"                                          );
                    }
                    
                    StrBuilder_Append(fp,
                                      "      free(p);\n"
                                      "   }\n");

                    StrBuilder_Destroy(&str);                                       
                }
            }

        }
        else if (IsSuffix(functionName, "_ToString"))
        {
            TParameter* pParameterDeclaration =
                pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

            if (pParameterDeclaration != NULL)
            {
                TSingleTypeSpecifier *pSingleTypeSpecifier =
                    TSpecifier_As_TSingleTypeSpecifier(pParameterDeclaration->Specifiers.pHead);

                if (pSingleTypeSpecifier != NULL &&
                    pSingleTypeSpecifier->Token == TK_IDENTIFIER)
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
            TParameter* pParameterDeclaration =
                pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

            if (pParameterDeclaration != NULL)
            {
                
                TStructUnionSpecifier* pStructUnionSpecifier =
                    GetStructSpecifier(program, &pParameterDeclaration->Specifiers);

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
                                    pSingleTypeSpecifier2->Token == TK_IDENTIFIER)
                                {
                                    StrBuilder nameDestroy = STRBUILDER_INIT;
                                    const char* typedefName2 = pSingleTypeSpecifier2->TypedefName;

                                    StrBuilder_Append(&nameDestroy, typedefName2);
                                    StrBuilder_Append(&nameDestroy, "_Destroy");
                                    TDeclaration * pDeclaration2 = TProgram_GetFinalTypeDeclaration(program, nameDestroy.c_str);

                                    StrBuilder_Destroy(&nameDestroy);
                                    if (pDeclaration2)
                                    {
                                        const char* name = pDeclaration2->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Identifier;
                                        ForEachListItem(TStructDeclarator, pTStructDeclarator, &pItem->DeclaratorList)
                                        {
                                            StrBuilder_Append(fp, "    ");
                                            StrBuilder_Append(fp, typedefName2);
                                            StrBuilder_Append(fp, "_Destroy(&p->");
                                            StrBuilder_Append(fp, pTStructDeclarator->pDeclarator->pDirectDeclarator->Identifier);
                                            StrBuilder_Append(fp, ");\n");

                                        }
                                                    }

                                }
                            }

                            StrBuilder_Append(fp, "\n");
                        }
                    }
                }
            }
        }//destroy


        //
        if (IsSuffix(functionName, "_Add") ||
            IsSuffix(functionName, "_Destroy") ||
            IsSuffix(functionName, "_Init"))
        {
            TParameter* pParameterDeclaration =
                pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

            if (pParameterDeclaration != NULL)
            {
                TStructUnionSpecifier* pStructUnionSpecifier =
                    GetStructSpecifier(program, &pParameterDeclaration->Specifiers);

                if (pStructUnionSpecifier)
                {
                    if (IsSuffix(functionName, "_Add") &&
                        strcmp(pStructUnionSpecifier->TemplateName, "List") == 0)
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
                             pStructUnionSpecifier->TemplateName &&
                             strcmp(pStructUnionSpecifier->TemplateName, "List") == 0)
                    {
                        StrBuilder strBuilder = STRBUILDER_INIT;
                        if (pStructUnionSpecifier->Args.pHead)
                        {
                            TTypeName_CodePrint(program, options, &pStructUnionSpecifier->Args.pHead->TypeName, false, &strBuilder);
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
        }//_Add

        if (IsSuffix(functionName, "_Init"))
        {
            TParameter* pParameterDeclaration =
                pInitDeclarator->pDeclarator->pDirectDeclarator->Parameters.ParameterList.pHead;

            if (pParameterDeclaration != NULL)
            {
                TSingleTypeSpecifier *pSingleTypeSpecifier =
                    TSpecifier_As_TSingleTypeSpecifier(pParameterDeclaration->Specifiers.pHead);

                if (pSingleTypeSpecifier != NULL &&
                    pSingleTypeSpecifier->Token == TK_IDENTIFIER)
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
                                            pSingleTypeSpecifier2->Token == TK_IDENTIFIER)
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

