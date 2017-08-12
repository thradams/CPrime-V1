#include "..\CodePrint.h"
#include "..\..\Base\Array.h"
#include "..\..\Base\Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>


//Instancia as funcoes especias new create delete
bool ListPlugin_BuildDestroy(TProgram* program,
    TStructUnionSpecifier* pStructUnionSpecifier,
    const char* pVariableName,
    bool bVariableNameIsPointer,
    BuildType buildType,
    StrBuilder* fp)
{
    bool bInstanciated = false;

    if (strcmp(pStructUnionSpecifier->TemplateName, "List") == 0)
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
            StrBuilder_AppendFmtLn(fp, 1 * 4, "%s->pHead = NULL;", pVariableName);
            StrBuilder_AppendFmtLn(fp, 1 * 4, "%s->pTail = NULL;", pVariableName);
            break;
        case BuildTypeDestroy:
        case BuildTypeDelete:
        {
            bool bIsPointer = TDeclarator_IsDirectPointer(&pTypeName->Declarator);
            bool bAuto =  TPointerList_IsAutoPointer(&pTypeName->Declarator.PointerList);

        //TSpecifierQualifierList_is
        StrBuilder_AppendFmtLn(fp, 1 * 4, "%s *pItem = %s->pHead;", itemTypeStr.c_str, pVariableName);
        StrBuilder_AppendFmtLn(fp, 1 * 4, "while (pItem)");
        StrBuilder_AppendFmtLn(fp, 1 * 4, "{");
        
        if (bIsPointer)
        {
            StrBuilder_AppendFmtLn(fp, 2 * 4, "%s *pCurrent = pItem;", itemTypeStr.c_str);
            StrBuilder_AppendFmtLn(fp, 2 * 4, "pItem = pItem->pNext;");
            if (bAuto)
            {
                StrBuilder_AppendFmtLn(fp, 2 * 4, "%s_Delete(pCurrent);", itemTypeStr.c_str);
            }
        }
        else
        {
            StrBuilder_AppendFmtLn(fp, 2 * 4, "%s* pCurrent = pItem;", itemTypeStr.c_str);
            StrBuilder_AppendFmtLn(fp, 2 * 4, "pItem = pItem->pNext;");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "%s_Destroy(pCurrent);", itemTypeStr.c_str);
        }

        //printf("  T* pCurrent = pItem;\n");
        StrBuilder_AppendFmtLn(fp, 1 * 4, "}");
        }
        break;
        case BuildTypeCreate:
            StrBuilder_AppendFmtLn(fp, 1 * 4, "%s->pHead = NULL;", pVariableName);
            StrBuilder_AppendFmtLn(fp, 1 * 4, "%s->pTail = NULL;", pVariableName);
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
bool ListPlugin_Type_CodePrint(TProgram* program,
    Options * options,
    TStructUnionSpecifier* p,
    bool b, 
    StrBuilder* fp)
{
    bool bInstanciated = false;
    bool bResult = false;
    if (p->TemplateName != NULL)
    {
        if (strcmp(p->TemplateName, "List") == 0)
        {
            if (p->Args.pHead)
            {
                bInstanciated = true;
                Output_Append(fp, "List(");
                TTypeName_CodePrint(program, options, &p->Args.pHead->TypeName, false, fp);
                Output_Append(fp, ")");
                bResult = true;
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

//Implementa 'default'
bool ListPlugin_CodePrint(TProgram* program,
    Options * options,
    TDeclaration* p,
    bool b,
    StrBuilder* fp)
{
    bool bInstanciated = false;
    
    const char* functionName = TDeclaration_GetFunctionName(p);
    int nArgs = TDeclaration_GetNumberFuncArgs(p);
    
    if (nArgs > 0)
    {
        TDeclarationSpecifiers* pFirst =
            TDeclaration_GetArgTypeSpecifier(p, 0);

        TStructUnionSpecifier* pStructUnionSpecifier =
            GetStructSpecifier(program, pFirst);
        if (strcmp(pStructUnionSpecifier->TemplateName, "List") != 0)
        {
            return false;
        }
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

        if (IsSuffix(functionName, "_Add"))
        {
            bInstanciated = true;
            StrBuilder_AppendFmtLn(fp, 1 * 4, "if (%s->pHead == NULL)", arg1Name);
            StrBuilder_AppendFmtLn(fp, 1 * 4, "{");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "%s->pHead = %s;", arg1Name, arg2Name);
            StrBuilder_AppendFmtLn(fp, 1 * 4, "}");
            StrBuilder_AppendFmtLn(fp, 1 * 4, "else");
            StrBuilder_AppendFmtLn(fp, 1 * 4, "{");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "%s->pTail->pNext = %s;", arg1Name, arg2Name);
            StrBuilder_AppendFmtLn(fp, 1 * 4, "}");
            StrBuilder_AppendFmtLn(fp, 1 * 4, "%s->pTail = %s;", arg1Name, arg2Name);
        }
    }
    
    return bInstanciated;
}
