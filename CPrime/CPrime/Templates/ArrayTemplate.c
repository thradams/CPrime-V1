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
            StrBuilder_AppendFmt(fp, "%s->pData = NULL;\n", pVariableName);
            StrBuilder_AppendFmt(fp, "%s->Size = 0;\n", pVariableName);
            StrBuilder_AppendFmt(fp, "%s->Capacity = 0;\n", pVariableName);
            break;
            case BuildTypeDestroy:
            case BuildTypeDelete:
            {
                bool bIsPointer = TDeclarator_IsDirectPointer(&pTypeName->Declarator);
                bool bAuto = TPointerList_IsAutoPointer(&pTypeName->Declarator.PointerList);

                //TSpecifierQualifierList_is
                //StrBuilder_AppendFmt(fp, "%s *pItem = %s->pHead;\n", itemTypeStr.c_str, pVariableName);
                StrBuilder_AppendFmt(fp, "for (int i =0 ; i < %s->Size; i++)\n", pVariableName);
                StrBuilder_AppendFmt(fp, "{\n");

                if (bIsPointer)
                {
                    StrBuilder_AppendFmt(fp, "  %s *pCurrent = %s->pData[i];\n", itemTypeStr.c_str, pVariableName);
                    if (bAuto)
                    {
                        StrBuilder_AppendFmt(fp, "  %s_Delete(pCurrent);\n", itemTypeStr.c_str);
                    }
                }
                else
                {
                    StrBuilder_AppendFmt(fp, "  %s *pCurrent = %s->pData[i];\n", itemTypeStr.c_str, pVariableName);
                    StrBuilder_AppendFmt(fp, "  %s_Destroy(pCurrent);\n", itemTypeStr.c_str);
                }

                //printf("  T* pCurrent = pItem;\n");
                StrBuilder_AppendFmt(fp, "}\n");
            }
            break;
            case BuildTypeCreate:
            StrBuilder_AppendFmt(fp, "%s->pData = NULL;\n", pVariableName);
            StrBuilder_AppendFmt(fp, "%s->Size = 0;\n", pVariableName);
            StrBuilder_AppendFmt(fp, "%s->Capacity = 0;\n", pVariableName);
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

//Implementa 'default'
bool ArrayPlugin_CodePrint(TProgram* program,
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
                        strcmp(pStructUnionSpecifier->TemplateName, "Array") == 0)
                    {
                        StrBuilder_Append(fp, " if (p->Size + 1 > p->Capacity)\n");
                        StrBuilder_Append(fp, " {\n");
                        StrBuilder_Append(fp, "    int new_nelements = p->Capacity + p->Capacity / 2;\n");
                        StrBuilder_Append(fp, " \n");
                        StrBuilder_Append(fp, " if (new_nelements < 1)\n");
                        StrBuilder_Append(fp, " {\n");
                        StrBuilder_Append(fp, "     new_nelements = 1;\n");
                        StrBuilder_Append(fp, " }\n");

                        StrBuilder_Append(fp, " void** pnew = (void**) p->pData;\n");
                        StrBuilder_Append(fp, " pnew = (void**)realloc(pnew, new_nelements * sizeof(void*));\n");
                        StrBuilder_Append(fp, " if (pnew)\n");
                        StrBuilder_Append(fp, " {\n");
                        StrBuilder_Append(fp, "    p->pData = pnew;\n");
                        StrBuilder_Append(fp, "    p->Capacity = new_nelements;\n");
                        StrBuilder_Append(fp, " }\n");
                        StrBuilder_Append(fp, " }\n");
                        StrBuilder_Append(fp, "    p->pData[p->Size] = pItem;\n");
                        StrBuilder_Append(fp, "    p->Size++;\n");
                        StrBuilder_Append(fp, " \n");
                    };

                }
            }
        }//_Add
    }
    return false;
}
