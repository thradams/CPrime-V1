#include "..\CodePrint.h"
#include "..\..\Base\Array.h"
#include "..\..\Base\Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>


//Instancia as funcoes especias new create delete
void ArrayPlugin_BuildDestroy(TProgram* program,
    TStructUnionSpecifier* pStructUnionSpecifier,
    const char* pVariableName,
    bool bVariableNameIsPointer,
    BuildType buildType,
    StrBuilder* fp)
{
    if (strcmp(pStructUnionSpecifier->TemplateName, "Array") == 0)
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
            StrBuilder_AppendFmtIdent(fp, 4, "%s->pData = NULL;\n", pVariableName);
            StrBuilder_AppendFmtIdent(fp, 4, "%s->Size = 0;\n", pVariableName);
            StrBuilder_AppendFmtIdent(fp, 4, "%s->Capacity = 0;\n", pVariableName);
            break;
        case BuildTypeDestroy:
        case BuildTypeDelete:
        {
            bool bIsPointer = TDeclarator_IsDirectPointer(&pTypeName->Declarator);
            bool bAuto = TPointerList_IsAutoPointer(&pTypeName->Declarator.PointerList);

            
                if (bIsPointer && bAuto)
                {
                    StrBuilder_AppendFmtIdent(fp, 4, "for (int i = 0 ; i < %s->Size; i++)\n", pVariableName);
                    StrBuilder_AppendIdent(fp, 4, "{\n");
                    /*
                    BuildDestroy(program,
                        &options,
                        &pTypeName->SpecifierQualifierList,
                        NULL,
                        NULL,
                        itemTypeStr.c_str,
                        true,
                        BuildTypeDelete,
                        fp);
                        */
                    //StrBuilder_AppendFmtIdent(fp, 2 * 4, "%s *pCurrent = ;\n", itemTypeStr.c_str, pVariableName);
                    StrBuilder_AppendFmtIdent(fp, 2 * 4, "%s_Delete(%s->pData[i]);\n", itemTypeStr.c_str, pVariableName);
                    StrBuilder_AppendFmtIdent(fp, 4, "}\n");
                }
                else if (!bIsPointer)
                {
                    StrBuilder_AppendFmtIdent(fp, 4, "for (int i = 0 ; i < %s->Size; i++)\n", pVariableName);
                    //StrBuilder_AppendFmtIdent(fp, 2 * 4, "%s *pCurrent = %s->pData[i];\n", itemTypeStr.c_str, pVariableName);
                    //StrBuilder_AppendFmtIdent(fp, 2 * 4, "%s_Destroy(pCurrent);\n", itemTypeStr.c_str);
                    StrBuilder_AppendFmtIdent(fp, 2 * 4, "%s_Destroy(&%s->pData[i]);\n", itemTypeStr.c_str, pVariableName);
                    StrBuilder_AppendFmtIdent(fp, 4, "}\n");
                }
                StrBuilder_AppendFmtIdent(fp, 4, "free(%s->pData);\n", pVariableName);

            
         
        }
        break;
        case BuildTypeCreate:
            StrBuilder_AppendFmtIdent(fp, 4, "%s->pData = NULL;\n", pVariableName);
            StrBuilder_AppendFmtIdent(fp, 4, "%s->Size = 0;\n", pVariableName);
            StrBuilder_AppendFmtIdent(fp, 4, "%s->Capacity = 0;\n", pVariableName);
            break;

        case BuildTypeStaticInit:
            StrBuilder_AppendFmt(fp, "NULL, 0, 0");
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
bool ArrayPlugin_Type_CodePrint(TProgram* program,
    Options * options,
    TStructUnionSpecifier* p,
    bool b, StrBuilder* fp)
{
    bool bResult = false;
    if (p->TemplateName != NULL)
    {
        if (strcmp(p->TemplateName, "Array") == 0)
        {
            if (p->Args.pHead)
            {
                Output_Append(fp, "Array(");
                TTypeName_CodePrint(program, options, &p->Args.pHead->TypeName, false, fp);
                Output_Append(fp, ")");

                bResult = true;
                Output_Append(fp, " ");
                Output_Append(fp, "{");

                TSpecifierQualifierList_CodePrint(program, options, &p->Args.pHead->TypeName.SpecifierQualifierList, false, fp);

                //TTypeName_CodePrint(program, options, &p->Args.pHead->TypeName, b, fp);
                Output_Append(fp, "**pData; int Size, Capacity;");

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

TStructUnionSpecifier* TParameter_GetTypedefStruct(TProgram* program,
    TParameter* pParameter)
{
    TStructUnionSpecifier* pResult = NULL;
    const char* typedefName =
        TDeclarationSpecifiers_GetTypedefName(&pParameter->Specifiers);
    if (typedefName)
    {
        TDeclaration* pTypedefDeclaration =
            TProgram_GetFinalTypeDeclaration(program, typedefName);
        if (pTypedefDeclaration != NULL)
        {
            ForEachListItem(TSpecifier, pItem, &pTypedefDeclaration->Specifiers)
            {
                TStructUnionSpecifier* pStructUnionSpecifier =
                    TSpecifier_As_TStructUnionSpecifier(pItem);
                if (pStructUnionSpecifier)
                {
                    pResult = pStructUnionSpecifier;
                    break;
                }
            }
        }

    }
    return pResult;
}


bool ArrayPlugin_CodePrint(TProgram* program,
    Options * options,
    TDeclaration* p,
    bool b,
    StrBuilder* fp)
{

    const char* funcName = TDeclaration_GetFunctionName(p);
    if (funcName == NULL)
    {
        return false;
    }

    TParameterTypeList *pArguments = TDeclaration_GetFunctionArguments(p);
    if (pArguments == NULL || pArguments->ParameterList.pHead == NULL)
    {
        return false;
    }

    const char* firstParameterName = TParameter_GetName(pArguments->ParameterList.pHead);

    if (firstParameterName == NULL)
    {
        return false;
    }
    TStructUnionSpecifier* pMainType =
        TParameter_GetTypedefStruct(program, pArguments->ParameterList.pHead);
    if (pMainType == NULL ||
        pMainType->TemplateName == NULL ||
        strcmp(pMainType->TemplateName, "Array") != 0)
    {
        return false;
    }

    bool bInstanciated = false;
    if (IsSuffix(funcName, "_Add"))
    {
        TParameter* pSecondParameter = pArguments->ParameterList.pHead->pNext;
        if (pSecondParameter != NULL)
        {
            const char* secondParameterName = TParameter_GetName(pSecondParameter);
            if (secondParameterName != NULL)
            {
                StrBuilder itemTypeStr = STRBUILDER_INIT;
                Options  options = OPTIONS_INIT;
                TSpecifierQualifierList_CodePrint(program, &options, &pMainType->Args.pHead->TypeName.SpecifierQualifierList, false, &itemTypeStr);


                //TDeclarationSpecifiers_CodePrint(program, options&, pMainType->Args.pHead->TypeName)

                bInstanciated = true;
                StrBuilder_AppendFmtIdent(fp, 4, "if (%s->Size + 1 > %s->Capacity)\n", firstParameterName, firstParameterName);
                StrBuilder_AppendIdent(fp, 4, " {\n");
                StrBuilder_AppendFmtIdent(fp, 4 * 2, "int new_nelements = %s->Capacity + %s->Capacity / 2;\n", firstParameterName, firstParameterName);
                StrBuilder_Append(fp, "\n");
                StrBuilder_AppendIdent(fp, 4 * 2, "if (new_nelements < 1)\n");
                StrBuilder_AppendIdent(fp, 4 * 2, "{\n");
                StrBuilder_AppendIdent(fp, 4 * 3, "new_nelements = 1;\n");
                StrBuilder_AppendIdent(fp, 4 * 2, "}\n");

                StrBuilder_AppendFmtIdent(fp, 4 * 2, "void** pnew = (void**) %s->pData;\n", firstParameterName, firstParameterName);
                StrBuilder_AppendIdent(fp, 4 * 2, "pnew = (void**)realloc(pnew, new_nelements * sizeof(void*));\n");
                StrBuilder_AppendIdent(fp, 4 * 2, "if (pnew)\n");
                StrBuilder_AppendIdent(fp, 4 * 2, "{\n");
                StrBuilder_AppendFmtIdent(fp, 4 * 3, "%s->pData = (%s**)pnew;\n", firstParameterName, itemTypeStr.c_str);
                StrBuilder_AppendFmtIdent(fp, 4 * 3, "%s->Capacity = new_nelements;\n", firstParameterName);
                StrBuilder_AppendIdent(fp, 4 * 2, "}\n");
                StrBuilder_AppendIdent(fp, 4, "}\n");
                StrBuilder_AppendFmtIdent(fp, 4, "%s->pData[%s->Size] = %s;\n", firstParameterName, firstParameterName, secondParameterName);
                StrBuilder_AppendFmtIdent(fp, 4, "%s->Size++;\n", firstParameterName);
                //StrBuilder_Append(fp, "\n");

                StrBuilder_Destroy(&itemTypeStr);
            }
        }
    }//_Add


    return bInstanciated;
}
