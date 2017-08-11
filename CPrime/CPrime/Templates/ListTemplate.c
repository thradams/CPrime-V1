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
            StrBuilder_AppendFmt(fp, "%s->pHead = NULL;\n", pVariableName);
            StrBuilder_AppendFmt(fp, "%s->pTail = NULL;\n", pVariableName);
            break;
        case BuildTypeDestroy:
        case BuildTypeDelete:
        {
            bool bIsPointer = TDeclarator_IsDirectPointer(&pTypeName->Declarator);
            bool bAuto =  TPointerList_IsAutoPointer(&pTypeName->Declarator.PointerList);

        //TSpecifierQualifierList_is
        StrBuilder_AppendFmt(fp, "%s *pItem = %s->pHead;\n", itemTypeStr.c_str, pVariableName);
        StrBuilder_AppendFmt(fp, "while (pItem)\n");
        StrBuilder_AppendFmt(fp, "{\n");
        
        if (bIsPointer)
        {
            StrBuilder_AppendFmt(fp, "  %s *pCurrent = pItem;\n", itemTypeStr.c_str);
            StrBuilder_AppendFmt(fp, "  pItem = pItem->pNext;\n");
            if (bAuto)
            {
                StrBuilder_AppendFmt(fp, "  %s_Delete(pCurrent);\n", itemTypeStr.c_str);
            }
        }
        else
        {
            StrBuilder_AppendFmt(fp, "  %s* pCurrent = pItem;\n", itemTypeStr.c_str);
            StrBuilder_AppendFmt(fp, "  pItem = pItem->pNext;\n");
            StrBuilder_AppendFmt(fp, "  %s_Destroy(pCurrent);\n", itemTypeStr.c_str);
        }

        //printf("  T* pCurrent = pItem;\n");
        StrBuilder_AppendFmt(fp, "}\n");
        }
        break;
        case BuildTypeCreate:
            StrBuilder_AppendFmt(fp, "%s->pHead = NULL;\n", pVariableName);
            StrBuilder_AppendFmt(fp, "%s->pTail = NULL;\n", pVariableName);
            break;
        
        case BuildTypeStaticInit:
            StrBuilder_AppendFmt(fp, "NULL, NULL");
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
    bool bResult = false;
    if (p->TemplateName != NULL)
    {
        if (strcmp(p->TemplateName, "List") == 0)
        {
            if (p->Args.pHead)
            {
                Output_Append(fp, "List(");
                TTypeName_CodePrint(program, options, &p->Args.pHead->TypeName, false, fp);
                Output_Append(fp, ")");
                bResult = true;

                //bResult = true;
                //Output_Append(fp, " ");
                //Output_Append(fp, "{");

                //TTypeName_CodePrint(program, options, &p->Args.pHead->TypeName, b, fp);
                //Output_Append(fp, "* pHead, *pTail;");

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

//Implementa 'default'
bool ListPlugin_CodePrint(TProgram* program,
    Options * options,
    TDeclaration* p,
    bool b,
    StrBuilder* fp)
{
    if (p->InitDeclaratorList.pHead != NULL &&
        p->InitDeclaratorList.pHead->pNext == NULL)
    {
        TInitDeclarator *pInitDeclarator =
            p->InitDeclaratorList.pHead;

        const char* functionName =
            pInitDeclarator->pDeclarator->pDirectDeclarator->Identifier;

        if (IsSuffix(functionName, "_Add"))
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
                        //GetArgTypeName

                        const char* arg1Name = 
                            TDeclaration_GetArgName(p, 0);

                        const char* arg2Name =
                            TDeclaration_GetArgName(p, 1);


                        StrBuilder_AppendFmtIdent(fp, 1* 4,  
                            "\n"
                            "    if (%s->pHead == NULL) {\n"
                            "        %s->pHead = %s; \n"
                            "    }\n"
                            "    else\n"
                            "    {\n"
                            "        %s->pTail->pNext = %s; \n"                            
                            "    }\n"
                            "    %s->pTail = %s; \n",
                            arg1Name, 
                            arg1Name, 
                            arg2Name, 
                            arg1Name, 
                            arg2Name, 
                            arg1Name, 
                            arg2Name);
                    }

                }
            }
        }//_Add
    }
    return false;
}
