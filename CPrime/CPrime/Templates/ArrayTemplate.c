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
        bInstanciated = true;
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
            StrBuilder_AppendFmt(fp, "0");
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
    bool bInstanciated = false;
    if (p->TemplateName != NULL)
    {
        if (strcmp(p->TemplateName, "Array") == 0)
        {
            if (p->Args.pHead)
            {
                Output_Append(fp, "Array(");
                TTypeName_CodePrint(program, options, &p->Args.pHead->TypeName, false, fp);
                Output_Append(fp, ")");
                bInstanciated = true;
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

    return bInstanciated;
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





const char* TDeclaration_GetArgTypeName(TDeclaration* p, int index, StrBuilder* sb);


bool ArrayPlugin_CodePrint(TProgram* program,
    Options * options,
    TDeclaration* p,
    bool b,
    StrBuilder* fp)
{
    bool bInstanciated = false;

    const char* functionName = TDeclaration_GetFunctionName(p);
    int nArgs = TDeclaration_GetNumberFuncArgs(p);

    StrBuilder itemTypeStr = STRBUILDER_INIT;


    if (nArgs > 0)
    {
        TDeclarationSpecifiers* pFirst =
            TDeclaration_GetArgTypeSpecifier(p, 0);

        TStructUnionSpecifier* pStructUnionSpecifier =
            GetStructSpecifier(program, pFirst);
        if (strcmp(pStructUnionSpecifier->TemplateName, "Array") != 0)
        {
            return false;
        }
        TSpecifierQualifierList_CodePrint(program, options, &pStructUnionSpecifier->Args.pHead->TypeName.SpecifierQualifierList, false, &itemTypeStr);
    }



    if (nArgs == 1)
    {
        const char* arg1Name =
            TDeclaration_GetArgName(p, 0);

    }
    else if (nArgs == 2)
    {
        const char* arg1Name =
            TDeclaration_GetArgName(p, 0);

        const char* arg2Name =
            TDeclaration_GetArgName(p, 1);

        StrBuilder itemTypeStr1 = STRBUILDER_INIT;
        TDeclaration_GetArgTypeName(p, 0, &itemTypeStr1);

        StrBuilder itemTypeStr0 = STRBUILDER_INIT;
        TDeclaration_GetArgTypeName(p, 1, &itemTypeStr0);

        if (IsSuffix(functionName, "_Add"))
        {
            bInstanciated = true;

            StrBuilder_AppendFmtLn(fp, 4, "/*requires*/");
            StrBuilder_AppendFmtLn(fp, 4, "/*int %s_Reserve(%s* %s, int n) default;*/", itemTypeStr1.c_str, itemTypeStr1.c_str, arg1Name);

            StrBuilder_AppendFmtLn(fp, 4, "if (%s_Reserve(%s, %s->Size + 1) > 0)", itemTypeStr1.c_str, arg1Name, arg1Name);
            StrBuilder_AppendFmtLn(fp, 4, "{");
            StrBuilder_AppendFmtLn(fp, 4 * 2, "%s->pData[%s->Size] = %s;", arg1Name, arg1Name, arg2Name);
            StrBuilder_AppendFmtLn(fp, 4 * 2, "%s->Size++;", arg1Name);
            StrBuilder_AppendFmtLn(fp, 4, "}");
        }
        else if (IsSuffix(functionName, "_Reserve"))
        {
            bInstanciated = true;
            StrBuilder_AppendFmtLn(fp, 4, "int iResult = 0;");
            StrBuilder_AppendFmtLn(fp, 4, "if (%s > %s->Capacity)", arg2Name, arg1Name);
            StrBuilder_AppendFmtLn(fp, 4, "{");
            StrBuilder_AppendFmtLn(fp, 4 * 2, "%s** pNew = %s->pData;", itemTypeStr.c_str, arg1Name, arg1Name);
            StrBuilder_AppendFmtLn(fp, 4 * 2, "pNew = (%s**)realloc(pNew, %s * sizeof(%s*));", itemTypeStr.c_str, arg2Name, itemTypeStr.c_str);
            StrBuilder_AppendFmtLn(fp, 4 * 2, "if (pNew != NULL)");
            StrBuilder_AppendFmtLn(fp, 4 * 2, "{");
            StrBuilder_AppendFmtLn(fp, 4 * 3, "%s->pData = pNew;", arg1Name);
            StrBuilder_AppendFmtLn(fp, 4 * 3, "%s->Capacity = %s;", arg1Name, arg2Name);
            StrBuilder_AppendFmtLn(fp, 4 * 3, "iResult = %s;", arg2Name);
            StrBuilder_AppendFmtLn(fp, 4 * 2, "}\n");
            StrBuilder_AppendFmtLn(fp, 4, "}");
            StrBuilder_AppendFmtLn(fp, 4, "return iResult;");
        }

        StrBuilder_Destroy(&itemTypeStr0);
        StrBuilder_Destroy(&itemTypeStr1);
    }

    StrBuilder_Destroy(&itemTypeStr);

    return bInstanciated;
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

