#include "..\CodePrint.h"
#include "..\..\Base\Array.h"
#include "..\..\Base\Path.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>


//Instancia as funcoes especias new create delete
void ListPlugin_BuildDestroy(TProgram* program,
                             TStructUnionSpecifier* pStructUnionSpecifier,
                             const char* pVariableName,
                             bool bVariableNameIsPointer,
                             BuildType buildType)
{
    if (strcmp(pStructUnionSpecifier->TemplateName, "List") == 0)
    {
        switch (buildType)
        {
            case BuildTypeInit:
            printf("%s->pHead = NULL;\n", pVariableName);
            printf("%s->pTail = NULL;\n", pVariableName);
            break;
            case BuildTypeDestroy:
            printf("T *pItem = %s->pHead;\n", pVariableName);
            printf("while (pItem)\n");
            printf("{\n");
            printf("  T* pCurrent = pItem;\n");
            printf("  pItem = pItem->pNext;\n");
            //printf("  T* pCurrent = pItem;\n");
            printf("}\n");
            break;
            case BuildTypeCreate:
            printf("%s->pHead = NULL;\n", pVariableName);
            printf("%s->pTail = NULL;\n", pVariableName);
            break;
            case BuildTypeDelete:
            printf("T *pItem = %s->pHead;\n", pVariableName);
            printf("while (pItem)\n");
            printf("{\n");
            printf("  pItem = pItem->pNext;\n");
            printf("}\n");
            break;
            case BuildTypeStaticInit:
            printf("NULL, NULL");
            break;
            default:
            break;
        }
    }
}


void Output_Append(StrBuilder* p,
                   const char* source);

//Gera estrutura de ad
bool ListPlugin_Type_CodePrint(TProgram* program,
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
                    
                }
            }
        }//_Add
    }
    return false;
}
