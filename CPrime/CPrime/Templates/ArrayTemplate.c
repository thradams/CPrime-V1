#include "..\CodePrint.h"
#include "..\..\Base\Array.h"
#include "..\..\Base\Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>


//Instancia as funcoes especias new create delete
bool ArrayPlugin_BuildDestroy(TProgram* program,
    TStructUnionSpecifier* pStructUnionSpecifier,
    const char* pVariableName,
    bool bVariableNameIsPointer,
    BuildType buildType,
    StrBuilder* fp)
{
    bool bInstanciated = false;
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
            StrBuilder_AppendFmtLn(fp, 4, "%s->pData = NULL;", pVariableName);
            StrBuilder_AppendFmtLn(fp, 4, "%s->Size = 0;", pVariableName);
            StrBuilder_AppendFmtLn(fp, 4, "%s->Capacity = 0;", pVariableName);
            break;
        case BuildTypeDestroy:
        case BuildTypeDelete:
        {
            bool bIsPointer = TDeclarator_IsDirectPointer(&pTypeName->Declarator);
            bool bAuto = TPointerList_IsAutoPointer(&pTypeName->Declarator.PointerList);


            if (bIsPointer && bAuto)
            {
                StrBuilder_AppendFmtLn(fp, 4, "for (int i = 0 ; i < %s->Size; i++)", pVariableName);
                StrBuilder_AppendFmtLn(fp, 4, "{");
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
                StrBuilder_AppendFmtLn(fp, 2 * 4, "%s_Delete(%s->pData[i]);", itemTypeStr.c_str, pVariableName);
                StrBuilder_AppendFmtLn(fp, 4, "}");
            }
            else if (!bIsPointer)
            {
                StrBuilder_AppendFmtLn(fp, 4, "for (int i = 0 ; i < %s->Size; i++)", pVariableName);
                StrBuilder_AppendFmtLn(fp, 2 * 4, "%s_Destroy(&%s->pData[i]);", itemTypeStr.c_str, pVariableName);
                StrBuilder_AppendFmtLn(fp, 4, "}");
            }
            StrBuilder_AppendFmtIdent(fp, 4, "free(%s->pData);\n", pVariableName);
        }
        break;
        case BuildTypeCreate:
            StrBuilder_AppendFmtLn(fp, 4, "%s->pData = NULL;", pVariableName);
            StrBuilder_AppendFmtLn(fp, 4, "%s->Size = 0;", pVariableName);
            StrBuilder_AppendFmtLn(fp, 4, "%s->Capacity = 0;", pVariableName);
            break;

        case BuildTypeStaticInit:
            StrBuilder_AppendFmt(fp, "NULL, 0, 0");
            break;
        default:
            break;
        }
        StrBuilder_Destroy(&itemTypeStr);
    }
    return bInstanciated;
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
                //Output_Append(fp, " ");
                //Output_Append(fp, "{");

                //TSpecifierQualifierList_CodePrint(program, options, &p->Args.pHead->TypeName.SpecifierQualifierList, false, fp);

                //TTypeName_CodePrint(program, options, &p->Args.pHead->TypeName, b, fp);
                //Output_Append(fp, "**pData; int Size, Capacity;");

                //Output_Append(fp, "}");
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

const char* TDeclaration_GetArgTypeName(TDeclaration* p, int index, StrBuilder* sb)
{
    TDeclarationSpecifiers* pDeclarationSpecifiers =
        TDeclaration_GetArgTypeSpecifier(p, index);
    if (pDeclarationSpecifiers)
    {
        Options options = OPTIONS_INIT;
        options.bIncludeComments = false;
        TDeclarationSpecifiers_CodePrint(NULL, &options, pDeclarationSpecifiers, false, sb);
    }
    return sb->c_str;
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
    const char* firstParameterName =
        TDeclaration_GetArgName(p, 0);

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
        const char* secondParameterName =
            TDeclaration_GetArgName(p, 1);

        if (secondParameterName != NULL)
        {
            StrBuilder itemTypeStr1 = STRBUILDER_INIT;
            TDeclaration_GetArgTypeName(p, 0, &itemTypeStr1);
            //Tem que ver se %s_Reserve existe
            //senao existir gera um erro

            StrBuilder itemTypeStr = STRBUILDER_INIT;
            TDeclaration_GetArgTypeName(p, 1, &itemTypeStr);

            bInstanciated = true;
            StrBuilder_AppendFmtLn(fp, 4, "if (%s_Reserve(%s, %s->Size + 1) > 0)", itemTypeStr1.c_str, firstParameterName, firstParameterName);
            StrBuilder_AppendFmtLn(fp, 4, "{");
            StrBuilder_AppendFmtLn(fp, 4 * 2, "%s->pData[%s->Size] = %s;", firstParameterName, firstParameterName, secondParameterName);
            StrBuilder_AppendFmtLn(fp, 4 * 2, "%s->Size++;", firstParameterName);
            StrBuilder_AppendFmtLn(fp, 4, "}");
            StrBuilder_Destroy(&itemTypeStr);
            StrBuilder_Destroy(&itemTypeStr1);

        }

    }//_Add
    else if (IsSuffix(funcName, "_Reserve"))
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


                bInstanciated = true;
                StrBuilder_AppendFmtLn(fp, 4, "int iResult = 0;");
                StrBuilder_AppendFmtLn(fp, 4, "if (%s > %s->Capacity)", secondParameterName, firstParameterName);
                StrBuilder_AppendFmtLn(fp, 4, "{");
                StrBuilder_AppendFmtLn(fp, 4 * 2, "%s** pNew = %s->pData;", itemTypeStr.c_str, firstParameterName, firstParameterName);
                StrBuilder_AppendFmtLn(fp, 4 * 2, "pNew = (%s**)realloc(pNew, %s * sizeof(%s*));", itemTypeStr.c_str, secondParameterName, itemTypeStr.c_str);
                StrBuilder_AppendFmtLn(fp, 4 * 2, "if (pNew != NULL)");
                StrBuilder_AppendFmtLn(fp, 4 * 2, "{");
                StrBuilder_AppendFmtLn(fp, 4 * 3, "%s->pData = pNew;", firstParameterName);
                StrBuilder_AppendFmtLn(fp, 4 * 3, "%s->Capacity = %s;", firstParameterName, secondParameterName);
                StrBuilder_AppendFmtLn(fp, 4 * 3, "iResult = %s;", secondParameterName);
                StrBuilder_AppendFmtLn(fp, 4 * 2, "}\n");
                StrBuilder_AppendFmtLn(fp, 4, "}");
                StrBuilder_AppendFmtLn(fp, 4, "return iResult;");

                StrBuilder_Destroy(&itemTypeStr);
            }
        }
    }//Grow


    return bInstanciated;
}
