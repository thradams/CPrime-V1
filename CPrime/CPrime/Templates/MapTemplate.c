#include "..\CodePrint.h"
#include "..\..\Base\Array.h"
#include "..\..\Base\Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>


//Instancia as funcoes especias new create delete
bool MapPlugin_InstanciateSpecialFunctions(TProgram* program,
    TStructUnionSpecifier* pStructUnionSpecifier,
    const char* pVariableName,
    
    BuildType buildType,
    StrBuilder* fp)
{
    bool bInstanciated = false;
    if (strcmp(pStructUnionSpecifier->TemplateName, "Map") == 0)
    {
        bInstanciated = true;
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
            StrBuilder_AppendFmt(fp, "%s->pHashTable = NULL;\n", pVariableName);
            StrBuilder_AppendFmt(fp, "%s->HashTableSize = 0;\n", pVariableName);
            StrBuilder_AppendFmt(fp, "%s->Count = 0;\n", pVariableName);
            break;
        case BuildTypeDestroy:
        case BuildTypeDelete:
        {
            bool bIsPointer = TDeclarator_IsDirectPointer(&pTypeName->Declarator);
            bool bAuto = TPointerList_IsAutoPointer(&pTypeName->Declarator.PointerList);


            StrBuilder_AppendFmtLn(fp, 4, "if (%s->pHashTable != NULL)", pVariableName);
            StrBuilder_AppendFmtLn(fp, 4, "{");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "for (unsigned int nHash = 0;");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "   nHash < %s->HashTableSize;", pVariableName);
            StrBuilder_AppendFmtLn(fp, 2 * 4, "   nHash++)");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "{");
            StrBuilder_AppendFmtLn(fp, 3 * 4, "MapItem2* pKeyValue =");
            StrBuilder_AppendFmtLn(fp, 4 * 4, "%s->pHashTable[nHash];", pVariableName);
            StrBuilder_AppendFmtLn(fp, 2 * 4, "");
            StrBuilder_AppendFmtLn(fp, 3 * 4, "while (pKeyValue != NULL)");
            StrBuilder_AppendFmtLn(fp, 3 * 4, "{");
            StrBuilder_AppendFmtLn(fp, 4 * 4, "MapItem2* pKeyValueCurrent = pKeyValue;");
            StrBuilder_AppendFmtLn(fp, 4 * 4, "pKeyValue = pKeyValue->pNext;");

            if (bAuto)
            {
                StrBuilder_AppendFmtLn(fp, 4 * 4, "%s_Delete((%s*) pKeyValueCurrent->pValue);", itemTypeStr.c_str, itemTypeStr.c_str);
            }

            StrBuilder_AppendFmtLn(fp, 4 * 4, "KeyValue_Delete(pKeyValueCurrent);");
            StrBuilder_AppendFmtLn(fp, 3 * 4, "}");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "}");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "free(%s->pHashTable);", pVariableName);
            StrBuilder_AppendFmtLn(fp, 2 * 4, "%s->pHashTable = NULL;", pVariableName);
            StrBuilder_AppendFmtLn(fp, 2 * 4, "%s->Count = 0;", pVariableName);
            StrBuilder_AppendFmtLn(fp, 4, "}");
        }
        break;
        case BuildTypeCreate:
            StrBuilder_AppendFmt(fp, "%s->pHashTable = NULL;\n", pVariableName);
            StrBuilder_AppendFmt(fp, "%s->HashTableSize = 0;\n", pVariableName);
            StrBuilder_AppendFmt(fp, "%s->Count = 0;\n", pVariableName);
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
    Options * options,
    const char* source);

//Gera estrutura de ad
bool MapPlugin_InstanciateType(TProgram* program,
    Options * options,
    TStructUnionSpecifier* p,
   StrBuilder* fp)
{
    bool bInstanciated = false;
    if (p->TemplateName != NULL)
    {
        if (strcmp(p->TemplateName, "Map") == 0)
        {
            bInstanciated = true;
            if (p->Args.pHead)
            {
                Output_Append(fp, options, "Map(");
                TTypeName_CodePrint(program, options, &p->Args.pHead->TypeName, fp);
                Output_Append(fp, options, ")");

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

const char* TDeclaration_GetArgTypeName(TDeclaration* p, int index, StrBuilder* sb);

//Implementa 'default'
bool MapPlugin_InstanciateFunction(TProgram* program,
    Options * options,
    TDeclaration* p,
   
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
        
		if (!TStructUnionSpecifier_IsTemplate(pStructUnionSpecifier, "Map"))
        {
            return false;
        }
        TSpecifierQualifierList_CodePrint(program, options, &pStructUnionSpecifier->Args.pHead->TypeName.SpecifierQualifierList,  &itemTypeStr);
    }


    if (nArgs == 2)
    {
        const char* arg1Name =
            TDeclaration_GetArgName(p, 0);

        const char* arg2Name =
            TDeclaration_GetArgName(p, 1);



        StrBuilder itemTypeStr1 = STRBUILDER_INIT;
        TDeclaration_GetArgTypeName(p, 0, &itemTypeStr1);

        StrBuilder itemTypeStr2 = STRBUILDER_INIT;
        TDeclaration_GetArgTypeName(p, 1, &itemTypeStr2);


        if (IsSuffix(functionName, "_RemoveKey"))
        {
            bInstanciated = true;
            StrBuilder_AppendFmtLn(fp, 4, "void* pv;");
            StrBuilder_AppendFmtLn(fp, 4, "Map2_RemoveKey((Map2*)%s, %s,  &pv);", arg1Name, arg2Name);
            StrBuilder_AppendFmtLn(fp, 4, "if (pv)");
            StrBuilder_AppendFmtLn(fp, 4, "{");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "%s_Delete((%s*)pv);", itemTypeStr.c_str, itemTypeStr.c_str);
            StrBuilder_AppendFmtLn(fp, 4, "}");
        }
        else if (IsSuffix(functionName, "_Lookup"))
        {
            bInstanciated = true;
            StrBuilder_AppendFmtLn(fp, 1 * 4, "void* pv;");
            StrBuilder_AppendFmtLn(fp, 1 * 4, "if (Map2_Lookup((Map2*)%s, %s, &pv))", arg1Name, arg2Name);
            StrBuilder_AppendFmtLn(fp, 1 * 4, "{");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "  return (%s*)pv;", itemTypeStr.c_str);
            StrBuilder_AppendFmtLn(fp, 1 * 4, "}");
            StrBuilder_AppendFmtLn(fp, 1 * 4, "return NULL;");
        }


        StrBuilder_Destroy(&itemTypeStr2);
        StrBuilder_Destroy(&itemTypeStr1);


    }
    else if (nArgs == 3)
    {
        const char* arg1Name =
            TDeclaration_GetArgName(p, 0);

        const char* arg2Name =
            TDeclaration_GetArgName(p, 1);

        const char* arg3Name =
            TDeclaration_GetArgName(p, 2);

        StrBuilder itemTypeStr1 = STRBUILDER_INIT;
        TDeclaration_GetArgTypeName(p, 0, &itemTypeStr1);

        StrBuilder itemTypeStr2 = STRBUILDER_INIT;
        TDeclaration_GetArgTypeName(p, 1, &itemTypeStr2);

        StrBuilder itemTypeStr3 = STRBUILDER_INIT;
        TDeclaration_GetArgTypeName(p, 2, &itemTypeStr3);


        if (IsSuffix(functionName, "_Set"))
        {
            bInstanciated = true;
            StrBuilder_AppendFmtLn(fp, 4, "void* pv;");
            StrBuilder_AppendFmtLn(fp, 4, "Map2_SetAt((Map2*)%s, %s, %s, &pv);", arg1Name, arg2Name, arg3Name);
            StrBuilder_AppendFmtLn(fp, 4, "if (pv)");
            StrBuilder_AppendFmtLn(fp, 4, "{");
            StrBuilder_AppendFmtLn(fp, 2 * 4, "%s_Delete((%s*)pv);", itemTypeStr.c_str, itemTypeStr.c_str);
            StrBuilder_AppendFmtLn(fp, 4, "}");
        }



        StrBuilder_Destroy(&itemTypeStr2);
        StrBuilder_Destroy(&itemTypeStr1);
        StrBuilder_Destroy(&itemTypeStr3);
    }
    StrBuilder_Destroy(&itemTypeStr);


    return bInstanciated;
}
