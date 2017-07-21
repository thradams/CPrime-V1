


#include <stdio.h>

#include ".\Parser\AstPrint.h"
#include ".\Parser\Parser.h"
#include ".\CPrime\CodePrint.h"
#include ".\CPrime\TCLint2.h"
#include "..\CPrime\Base\Path.h"
#include "UnitTest.h"

void AstPlayground(TProgram* program);

void Compile(const char* configFileName,
    const char* inputFileName,
    Options* options,
             bool bPrintASTFile)
{
    TProgram program = TPROGRAM_INIT;

    printf("Parsing...\n");
    if (GetAST(inputFileName, configFileName, &program))
    {
        AstPlayground(&program);

        char drive[_MAX_DRIVE];
        char dir[_MAX_DIR];
        char fname[_MAX_FNAME];
        char ext[_MAX_EXT];
        SplitPath(inputFileName, drive, dir, fname, ext); // C4996

        if (bPrintASTFile)
        {
            printf("Generating ast for %s...\n", inputFileName);
            char outjs[_MAX_DRIVE + _MAX_DIR + _MAX_FNAME + _MAX_EXT + 1];
            MakePath(outjs, drive, dir, fname, ".json");
            TProgram_PrintAstToFile(&program, outjs, inputFileName);
        }
        else
        {
            char outc[_MAX_DRIVE + _MAX_DIR + _MAX_FNAME + _MAX_EXT + 1];
            MakePath(outc, drive, dir, fname, ".json");

            strcat(dir, "\\out\\");
            MakePath(outc, drive, dir, fname, ext);

            printf("Generating code for %s...\n", inputFileName);
            TProgram_PrintCodeToFile(&program, options, outc, inputFileName);
        }

        printf("Done!\n");
    }
    TProgram_Destroy(&program);
}

void PrintHelp()
{
    printf("Syntax: cprime [options] [file ...]\n");
    printf("\n");
    printf("Examples: cprime hello.c\n");
    printf("          cprime -config config.h hello.c\n");
    printf("          cprime -config config.h -P hello.c\n");
    printf("          cprime -E hello.c\n");
    printf("\n");
    printf("Options:\n");
    printf("-config FILE                          Configuration file.\n");
    printf("-help                                 Print this message.\n");
    printf("-E                                    Preprocess to console.\n");
    printf("-P                                    Preprocess to file.\n");
    printf("-A                                    Output AST to file.\n");

}
int main(int argc, char* argv[])
{
    printf("\n");
    printf("Version " __DATE__ "\n");
    printf("https://github.com/thradams/CPrime\n\n");


    //AllTests();

    if (argc < 2)
    {
        PrintHelp();
        return 1;
    }

    const char* configFileName = NULL;


    Options options = OPTIONS_INIT;
    bool bPrintPreprocessedToFile = false;
    bool bPrintPreprocessedToConsole = false;
    bool bPrintASTFile = false;

    for (int i = 1; i < argc; i++)
    {
        const char * option = argv[i];
        if (strcmp(option, "-P") == 0)
        {
            bPrintPreprocessedToFile = true;
        }
        else if (strcmp(option, "-E") == 0)
        {
            bPrintPreprocessedToConsole = true;
        }
        else if (strcmp(option, "-A") == 0)
        {
            bPrintASTFile = true;
        }
        else if (strcmp(option, "-help") == 0)
        {
            PrintHelp();
        }
        else if (strcmp(option, "-config") == 0)
        {
            if (i + i < argc)
            {
                configFileName = argv[i + 1];
                i++;
            }
            else
            {
                printf("missing file\n");
            }
        }
        else
        {
            const char* inputFileName = option;
            String inputFullPath = NULL;
            GetFullPath(inputFileName, &inputFullPath);

            if (bPrintPreprocessedToFile)
            {
                PrintPreprocessedToFile(inputFullPath, configFileName);
            }
            else if (bPrintPreprocessedToConsole)
            {
                PrintPreprocessedToConsole(inputFullPath, configFileName);
            }
            else
            {
                Compile(configFileName, inputFullPath, &options, bPrintASTFile);
            }
            String_Destroy(&inputFullPath);
        }
    }


    return 0;
}


TParameterTypeList * TDeclaration_GetFunctionArguments(TDeclaration* p)
{
    TParameterTypeList* pParameterTypeList = NULL;

    if (p->InitDeclaratorList.pHead != NULL)
    {
        if (p->InitDeclaratorList.pHead->pNext == NULL)
        {
            if (p->InitDeclaratorList.pHead->pDeclarator != NULL)
            {
                if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator)
                {
                    if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Type == TDirectDeclaratorTypeFunction)
                    {
                        pParameterTypeList =
                            &p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Parameters;

                    }
                }
            }
        }
    }
    return pParameterTypeList;
}

const char* TDeclaration_Is_FunctionDeclaration(TDeclaration* p)
{
    const char* functionName = NULL;

    if (p->InitDeclaratorList.pHead != NULL)
    {
        if (p->InitDeclaratorList.pHead->pNext == NULL)
        {
            if (p->InitDeclaratorList.pHead->pDeclarator != NULL)
            {
                if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator)
                {
                    if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Type == TDirectDeclaratorTypeFunction)
                    {
                        functionName =
                            p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Identifier;
                    }
                }
            }
        }
    }
    return functionName;
}

TCompoundStatement* TDeclaration_Is_FunctionDefinition(TDeclaration* p)
{
    TCompoundStatement* pCompoundStatement = NULL;

    if (p->InitDeclaratorList.pHead != NULL)
    {
        if (p->InitDeclaratorList.pHead->pNext == NULL)
        {
            if (p->InitDeclaratorList.pHead->pDeclarator != NULL)
            {
                if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator)
                {
                    if (p->InitDeclaratorList.pHead->pDeclarator->pDirectDeclarator->Type == TDirectDeclaratorTypeFunction)
                    {
                        pCompoundStatement = p->pCompoundStatementOpt;
                    }
                }
            }
        }
    }
    return pCompoundStatement;
}

TStructUnionSpecifier* TDeclarationSpecifiers_Find_StructUnionSpecifier(TDeclarationSpecifiers* p)
{
    TStructUnionSpecifier* pStructUnionSpecifier = NULL;
    ForEachListItem(TSpecifier, pDeclarationSpecifier, p)
    {
        pStructUnionSpecifier =
            TSpecifier_As_TStructUnionSpecifier(pDeclarationSpecifier);
        if (pStructUnionSpecifier)
        {
            break;
        }
    }
    return pStructUnionSpecifier;
}

TStructUnionSpecifier* TParameter_Is_DirectPointerToStruct(TProgram* program, TParameter* pParameter)
{
    TStructUnionSpecifier* pStructUnionSpecifier = NULL;
    if (TParameter_IsDirectPointer(pParameter))
    {
        const char* typedefName = TParameter_GetTypedefName(pParameter);
        if (typedefName != NULL)
        {
            TDeclaration* pArgType = TProgram_FindDeclaration(program, TParameter_GetTypedefName(pParameter));
            if (pArgType)
            {
                pStructUnionSpecifier =
                    TDeclarationSpecifiers_Find_StructUnionSpecifier(&pArgType->Specifiers);
            }
        }
    }
    return pStructUnionSpecifier;
}




bool EachStructDeclarator(TStructUnionSpecifier* pStruct,
                          int *i,
                          TSpecifierQualifierList **ppSpecifierQualifierList,
                          TStructDeclarator** ppStructDeclarator)
{
    /*
     Exemplo:
      TSpecifierQualifierList *pSpecifierQualifierList = NULL;
      TStructDeclarator* pStructDeclarator = NULL;
      int i = 0;
      while (EachStructDeclarator(pStruct, &i, &pSpecifierQualifierList, &pStructDeclarator))
      {
            printf("%s\n", TDeclarator_GetName(pStructDeclarator->pDeclarator));
      }
    */
    if (*ppStructDeclarator != NULL)
    {
        goto Continue;
    }

    for (; *i < pStruct->StructDeclarationList.size; (*i)++)
    {
        TAnyStructDeclaration* pAnyStructDeclaration =
            pStruct->StructDeclarationList.pItems[*i];

        TStructDeclaration* pStructDeclaration =
            TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);

        if (pStructDeclaration != NULL)
        {
            *ppSpecifierQualifierList =
                &pStructDeclaration->SpecifierQualifierList;
            *ppStructDeclarator =
                pStructDeclaration->DeclaratorList.pHead;

            while (*ppStructDeclarator != NULL)
            {
                return true;
            Continue:
                *ppStructDeclarator = (*ppStructDeclarator)->pNext;
            }
        }
    }
    return false;
}

typedef enum
{
    BuildTypeInit,
    BuildTypeDestroy,
    BuildTypeCreate,
    BuildTypeDelete,    
    BuildTypeStaticInit,
} BuildType;

void BuildDestroy(TProgram* program,
                  TSpecifierQualifierList* pSpecifierQualifierList,
                  TDeclarator* pDeclarator,
                  TInitializer* pInitializer,
                  const char* pVariableName,
                  bool bVariableNameIsPointer,
                  BuildType buildType);

void Typedef_BuildDestroy(TProgram* program,
                                       TDeclaration* pDeclaration2,
                                       TInitializer* pInitializer,
                                       const char* pVariableName,
                                       bool bVariableNameIsPointer,
                                       const char* declaratorName,
                                       const char* typedefName,
                                       bool bIsPointer,
                                       bool bIsAutoPointer,
                                       BuildType buildType)

{
    StrBuilder strFuncName = STRBUILDER_INIT;
    if (pDeclaration2)
    {
        if (buildType == BuildTypeInit)
        {
            if (bVariableNameIsPointer)
            {
                printf("%s = NULL;\n", pVariableName);
            }
            else
            {
                //inicializando nao pointer

                StrBuilder_Set(&strFuncName, typedefName);
                StrBuilder_Append(&strFuncName, "_Init");
                TDeclaration *pFunctionDeclaration =
                    TProgram_FindFunctionDeclaration(program, strFuncName.c_str);

                if (pFunctionDeclaration != NULL)
                {
                    //tem Init
                    if (bVariableNameIsPointer)
                    {
                        printf("%s(%s);\n", strFuncName.c_str, pVariableName);
                    }
                    else
                    {
                        printf("%s(&%s);\n", strFuncName.c_str, pVariableName);
                    }
                }
                else
                {
                    //nao tem nem Init
                    TDeclarator* pTypedefDeclarator =
                        TDeclaration_FindDeclarator(pDeclaration2, typedefName);
                    if (pTypedefDeclarator != NULL)
                    {
                        // "inline"
                        BuildDestroy(program,
                            (TSpecifierQualifierList*)&pDeclaration2->Specifiers,
                                     pTypedefDeclarator,
                                     pInitializer,
                                     pVariableName,
                                     bVariableNameIsPointer,
                                     BuildTypeInit);
                    }
                }
            }

        }
        else if (buildType == BuildTypeDestroy)
        {
            if (bIsPointer && !bIsAutoPointer)
            {
                //printf("//%s = NULL;\n", pVariableName);
            }
            else if (bIsPointer && bIsAutoPointer)
            {
                //Destruindo um auto pointer
                StrBuilder_Append(&strFuncName, typedefName);
                StrBuilder_Append(&strFuncName, "_Delete");

                //ve se tem delete
                TDeclaration *pFunctionDeclaration =
                    TProgram_FindFunctionDeclaration(program, strFuncName.c_str);

                if (pFunctionDeclaration != NULL)
                {
                    //tem delete
                    printf("%s(&%s);\n", strFuncName.c_str, pVariableName);
                }
                else
                {
                    //nao tem delete ve se tem destroy
                    StrBuilder_Set(&strFuncName, typedefName);
                    StrBuilder_Append(&strFuncName, "_Destroy");
                    pFunctionDeclaration =
                        TProgram_FindFunctionDeclaration(program, strFuncName.c_str);

                    if (pFunctionDeclaration != NULL)
                    {
                        //tem destroy
                        printf("if (%s) {\n", pVariableName);


                        if (bVariableNameIsPointer)
                        {
                            printf("%s(%s);\n", strFuncName.c_str, pVariableName);
                            printf("free(%s);\n", pVariableName);
                        }
                        else
                        {
                            printf("%s(&%s);\n", strFuncName.c_str, pVariableName);
                            printf("free(&%s);\n", pVariableName);
                        }

                        printf("}\n");
                    }
                    else
                    {
                        //nao tem nem delete nem destroy
                        TDeclarator* pTypedefDeclarator =
                            TDeclaration_FindDeclarator(pDeclaration2, typedefName);
                        if (pTypedefDeclarator != NULL)
                        {
                            printf("if (%s) {\n", pVariableName);
                            BuildDestroy(program,
                                (TSpecifierQualifierList*)&pDeclaration2->Specifiers,
                                         pTypedefDeclarator,
                                         pInitializer,
                                         pVariableName,
                                         bVariableNameIsPointer,
                                         BuildTypeDestroy);

                            if (bVariableNameIsPointer)
                            {
                                printf("free(%s);\n", pVariableName);
                            }
                            else
                            {
                                printf("free(&%s);\n", pVariableName);
                            }

                            printf("}\n");
                        }
                    }
                }

            }
            else
            {
                //destruindo nao pointer
                //nao tem delete ve se tem destroy
                StrBuilder_Set(&strFuncName, typedefName);
                StrBuilder_Append(&strFuncName, "_Destroy");
                TDeclaration *pFunctionDeclaration =
                    TProgram_FindFunctionDeclaration(program, strFuncName.c_str);

                if (pFunctionDeclaration != NULL)
                {
                    //tem destroy
                    if (bVariableNameIsPointer)
                    {
                        printf("%s(%s);\n", strFuncName.c_str, pVariableName);
                    }
                    else
                    {
                        printf("%s(&%s);\n", strFuncName.c_str, pVariableName);
                    }
                }
                else
                {
                    //nao tem nem delete nem destroy
                    TDeclarator* pTypedefDeclarator =
                        TDeclaration_FindDeclarator(pDeclaration2, typedefName);
                    if (pTypedefDeclarator != NULL)
                    {
                        // "inline"
                        BuildDestroy(program,
                            (TSpecifierQualifierList*)&pDeclaration2->Specifiers,
                                     pTypedefDeclarator,
                                     pInitializer,
                                     pVariableName,
                                     bVariableNameIsPointer,
                                     BuildTypeDestroy);

                    }
                }
            }
        }
        else if (buildType == BuildTypeDelete)
        {
            if (bIsPointer && !bIsAutoPointer)
            {
                //printf("//%s = NULL;\n", pVariableName);
            }
            else
            {
                StrBuilder strFuncName = STRBUILDER_INIT;
                StrBuilder_Append(&strFuncName, typedefName);

                TDeclaration *pFunctionDeclaration = NULL;

                if (bIsAutoPointer)
                {
                    StrBuilder_Append(&strFuncName, "_Delete");
                }
                else
                {
                    StrBuilder_Append(&strFuncName, "_Destroy");
                }

                pFunctionDeclaration =
                    TProgram_FindFunctionDeclaration(program, strFuncName.c_str);


                //printf("%s {\n", typedefName);
                if (pFunctionDeclaration != NULL)
                {
                    //esta funcao substitui o conceito
                    //destroy, init, delete
                    if (bVariableNameIsPointer)
                    {
                        printf("%s(%s);\n", strFuncName.c_str, pVariableName);
                    }
                    else
                    {
                        printf("%s(&%s);\n", strFuncName.c_str, pVariableName);
                    }
                }
                else
                {
                    printf("////// %s //////\n", declaratorName);

                    TDeclarator* pTypedefDeclarator =
                        TDeclaration_FindDeclarator(pDeclaration2, typedefName);
                    if (pTypedefDeclarator != NULL)
                    {
                        BuildType buildTypeModified = buildType;

                        if (bIsAutoPointer && buildType == BuildTypeDestroy)
                        {
                            buildTypeModified = BuildTypeDestroy;
                        }

                        BuildDestroy(program,
                            (TSpecifierQualifierList*)&pDeclaration2->Specifiers,
                                     pTypedefDeclarator,
                                     pInitializer,
                                     pVariableName,
                                     bVariableNameIsPointer,
                                     buildTypeModified);

                        if (bIsAutoPointer && buildType == BuildTypeDestroy)
                        {
                            if (bVariableNameIsPointer)
                            {
                                printf("free(%s);\n", pVariableName);
                            }
                            else
                            {
                                printf("free(&%s);\n", pVariableName);
                            }
                        }

                        //printf("//%s }\n", declaratorName);

                    }
                    else
                    {
                        ASSERT(false);
                    }
                }

                //printf("}\n");
                StrBuilder_Destroy(&strFuncName);
            }
        }
        else if (buildType == BuildTypeCreate)
        {
            if (bIsPointer && !bIsAutoPointer)
            {
                printf("%s = NULL;\n", pVariableName);
            }
            else
            {
                StrBuilder strFuncName = STRBUILDER_INIT;
                StrBuilder_Append(&strFuncName, typedefName);

                TDeclaration *pFunctionDeclaration = NULL;

                
                
                pFunctionDeclaration =
                    TProgram_FindFunctionDeclaration(program, strFuncName.c_str);


                //printf("%s {\n", typedefName);
                if (pFunctionDeclaration != NULL)
                {
                    //esta funcao substitui o conceito
                    //destroy, init, delete
                    if (bVariableNameIsPointer)
                    {
                        printf("%s(%s);\n", strFuncName.c_str, pVariableName);
                    }
                    else
                    {
                        printf("%s(&%s);\n", strFuncName.c_str, pVariableName);
                    }
                }
                else
                {
                    printf("////// %s //////\n", declaratorName);

                    TDeclarator* pTypedefDeclarator =
                        TDeclaration_FindDeclarator(pDeclaration2, typedefName);
                    if (pTypedefDeclarator != NULL)
                    {
                        BuildType buildTypeModified = buildType;

                        if (bIsAutoPointer && buildType == BuildTypeDestroy)
                        {
                            buildTypeModified = BuildTypeDestroy;
                        }

                        BuildDestroy(program,
                            (TSpecifierQualifierList*)&pDeclaration2->Specifiers,
                                     pTypedefDeclarator,
                                     pInitializer,
                                     pVariableName,
                                     bVariableNameIsPointer,
                                     buildTypeModified);

                        if (bIsAutoPointer && buildType == BuildTypeDestroy)
                        {
                            if (bVariableNameIsPointer)
                            {
                                printf("free(%s);\n", pVariableName);
                            }
                            else
                            {
                                printf("free(&%s);\n", pVariableName);
                            }
                        }

                        //printf("//%s }\n", declaratorName);

                    }
                    else
                    {
                        ASSERT(false);
                    }
                }

                //printf("}\n");
                StrBuilder_Destroy(&strFuncName);
            }
        }
        else if (buildType == BuildTypeStaticInit)
        {
            if (bVariableNameIsPointer)
            {
                printf("/*%s*/ NULL,", pVariableName);
            }
            else
            {
                TDeclarator* pTypedefDeclarator =
                    TDeclaration_FindDeclarator(pDeclaration2, typedefName);
                if (pTypedefDeclarator != NULL)
                {
                    // "inline"
                    BuildDestroy(program,
                        (TSpecifierQualifierList*)&pDeclaration2->Specifiers,
                                 pTypedefDeclarator,
                                 pInitializer,
                                 pVariableName,
                                 bVariableNameIsPointer,
                                 BuildTypeStaticInit);
                }
            }
        }
        else
        {
            ASSERT(false);
        }
    }
    else
    {
        //nao achou este typedef
        ASSERT(false);
    }
    StrBuilder_Destroy(&strFuncName);
}

void TSingleTypeSpecifier_BuildDestroy(TProgram* program,
                                       TSingleTypeSpecifier* pSingleTypeSpecifier,
                                       const char* pVariableName,
                                       bool bVariableNameIsPointer,
                                       bool bIsPointer,
                                       bool bIsAutoPointer,
                                       BuildType buildType)
{
    if (pSingleTypeSpecifier->Token == TK_INT ||
        pSingleTypeSpecifier->Token == TK_LONG ||
        pSingleTypeSpecifier->Token == TK_SHORT ||
        //
        pSingleTypeSpecifier->Token == TK_DOUBLE ||
        pSingleTypeSpecifier->Token == TK_FLOAT ||
        //
        pSingleTypeSpecifier->Token == TK__BOOL ||
        //
        pSingleTypeSpecifier->Token == TK_char
        )
    {
        if (buildType == BuildTypeInit || 
            buildType == BuildTypeCreate)
        {
            if (bIsPointer)
            {
                printf("%s = NULL;\n", pVariableName);
            }
            else
            {
                printf("%s = 0;\n", pVariableName);
            }
        }
        else if (buildType == BuildTypeDestroy)
        {
            if (bIsPointer && !bIsAutoPointer)
            {
                //printf("//%s = NULL;\n", pVariableName);
            }
            else if (bIsAutoPointer)
            {
                if (bVariableNameIsPointer)
                {
                    printf("free(%s);\n", pVariableName);
                }
                else
                {
                    printf("free(&%s);\n", pVariableName);
                }
            }
            else
            {
                //printf("//%s = 0;\n", pVariableName);
            }
        }
        else if (buildType == BuildTypeDelete)
        {
        }
        else if (buildType == BuildTypeStaticInit)
        {
            if (bIsPointer)
            {
                printf("/*%s*/NULL,", pVariableName);
            }
            else
            {
                printf("/*%s*/0,", pVariableName);
            }
        }
    }
    else
    {
        ASSERT(false);
    }
}


void TStructUnionSpecifier_BuildDestroy(TProgram* program,
                                        TStructUnionSpecifier* pStructUnionSpecifier,
                                        const char* pVariableName,
                                        bool bVariableNameIsPointer,
                                        BuildType buildType)
{
    //TStructUnionSpecifier* pStructUnionSpecifier =
      //  TSpecifier_As_TStructUnionSpecifier(pSpecifier);

    if (pStructUnionSpecifier != NULL)
    {
        if (pStructUnionSpecifier->TemplateName != NULL)
        {
            //printf("template struct %s %s\n", declaratorName, pStructUnionSpecifier->TemplateName);
        }
        else
        {
            for (int i = 0; i < pStructUnionSpecifier->StructDeclarationList.size; i++)
            {
                TAnyStructDeclaration* pAnyStructDeclaration =
                    pStructUnionSpecifier->StructDeclarationList.pItems[i];

                TStructDeclaration* pStructDeclaration =
                    TAnyStructDeclaration_As_TStructDeclaration(pAnyStructDeclaration);

                if (pStructDeclaration != NULL)
                {
                    TStructDeclarator* pStructDeclarator =
                        pStructDeclaration->DeclaratorList.pHead;

                    StrBuilder strVariableName = STRBUILDER_INIT;

                    while (pStructDeclarator)
                    {
                        const char* declaratorName = TDeclarator_GetName(pStructDeclarator->pDeclarator);

                        //if (buildType != BuildTypeStaticInit)
                        {
                            if (pVariableName)
                            {
                                StrBuilder_Set(&strVariableName, pVariableName);
                            }

                            if (bVariableNameIsPointer)
                            {
                                StrBuilder_Append(&strVariableName, "->");
                            }
                            else
                            {
                                StrBuilder_Append(&strVariableName, ".");
                            }

                            StrBuilder_Append(&strVariableName, declaratorName);
                        }

                        bool bStructDeclaratorIsPointer =
                            TPointerList_IsPointer(&pStructDeclarator->pDeclarator->PointerList);

                        BuildDestroy(program,
                                     &pStructDeclaration->SpecifierQualifierList,
                                     pStructDeclarator->pDeclarator,
                                     pStructDeclarator->pInitializer,
                                     strVariableName.c_str,
                                     bStructDeclaratorIsPointer,
                                     buildType);


                        pStructDeclarator = (pStructDeclarator)->pNext;
                    }

                    StrBuilder_Destroy(&strVariableName);
                }
            }
            //                    
        }
    }
}

void BuildDestroy(TProgram* program,
                  TSpecifierQualifierList* pSpecifierQualifierList,
                  TDeclarator* pDeclarator,
                  TInitializer* pInitializer,
                  const char* pVariableName,
                  bool bVariableNameIsPointer,
                  BuildType buildType)
{
    const char* declaratorName = TDeclarator_GetName(pDeclarator);
    //
    bool bIsPointer = TDeclarator_IsPointer(pDeclarator);
    bool bIsAutoPointer = TPointerList_IsAutoPointer(&pDeclarator->PointerList);
    bool bIsTypedef = TSpecifierQualifierList_IsTypedefQualifier(pSpecifierQualifierList);

    //{
    TSpecifier* pSpecifier =
        TSpecifierQualifierList_GetMainSpecifier(pSpecifierQualifierList);

    if (pSpecifier->Type == TSingleTypeSpecifier_ID)
    {
        TSingleTypeSpecifier *pSingleTypeSpecifier =
            TSpecifier_As_TSingleTypeSpecifier(pSpecifier);
        if (pSingleTypeSpecifier->Token == TK_IDENTIFIER)
        {
            const char* typedefName = pSingleTypeSpecifier->TypedefName;

            TDeclaration* pDeclaration2 =
                TProgram_GetFinalTypeDeclaration(program, typedefName);

            if (pDeclaration2)
            {
                Typedef_BuildDestroy(program,
                                         pDeclaration2,
                                      pInitializer,
                                         pVariableName,
                                        bVariableNameIsPointer,
                                          declaratorName,
                                          typedefName,
                                          bIsPointer,
                                          bIsAutoPointer,
                                          buildType);
            }
            else
            {
                //nao achou este typedef
                ASSERT(false);
            }
        }
        else
        {
            TSingleTypeSpecifier_BuildDestroy(program,
                                                   pSingleTypeSpecifier,
                                                  pVariableName,
                                              bVariableNameIsPointer,
                                                   bIsPointer,
                                                   bIsAutoPointer,
                                                   buildType);
        }
    }
    else if (pSpecifier->Type == TStructUnionSpecifier_ID)
    {
        if (bIsTypedef)
        {
            if (buildType == BuildTypeDelete)
            {
                //vou procurar o conceito de destroy
                StrBuilder strFuncName = STRBUILDER_INIT;
                StrBuilder_Append(&strFuncName, declaratorName);

                TDeclaration *pFunctionDeclaration = NULL;
                StrBuilder_Append(&strFuncName, "_Destroy");
                pFunctionDeclaration =
                    TProgram_FindFunctionDeclaration(program, strFuncName.c_str);
                if (pFunctionDeclaration != NULL)
                {
                    if (bVariableNameIsPointer)
                    {
                        printf("%s(%s);\n", strFuncName.c_str, pVariableName);
                        printf("free(%s);\n", pVariableName);
                    }
                    else
                    {
                        printf("%s(&%s);\n", strFuncName.c_str, pVariableName);
                        printf("free(&%s);\n", pVariableName);
                    }

                }
                else
                {
                    TStructUnionSpecifier* pStructUnionSpecifier =
                        TSpecifier_As_TStructUnionSpecifier(pSpecifier);
                    TStructUnionSpecifier_BuildDestroy(program,
                                                       pStructUnionSpecifier,
                                                       pVariableName,
                                                       bVariableNameIsPointer,
                                                       BuildTypeDestroy);

                    if (bVariableNameIsPointer)
                    {
                        printf("free(%s);\n", pVariableName);
                    }
                    else
                    {
                        printf("free(&%s);\n", pVariableName);
                    }
                }
            }
            else if (buildType == BuildTypeCreate )
            {
                //vou procurar o conceito de destroy
                StrBuilder strFuncName = STRBUILDER_INIT;
                StrBuilder_Append(&strFuncName, declaratorName);

                TDeclaration *pFunctionDeclaration = NULL;
                StrBuilder_Append(&strFuncName, "_Init");
                pFunctionDeclaration =
                    TProgram_FindFunctionDeclaration(program, strFuncName.c_str);
                if (pFunctionDeclaration != NULL)
                {
                    if (bVariableNameIsPointer)
                    {
                        printf("%s(%s);\n", strFuncName.c_str, pVariableName);                        
                        //printf("%s = NULL;\n", pVariableName);
                    }
                    else
                    {
                        printf("%s(&%s);\n", strFuncName.c_str, pVariableName);
                    }
                }
                else
                {
                    TStructUnionSpecifier* pStructUnionSpecifier =
                        TSpecifier_As_TStructUnionSpecifier(pSpecifier);
                    TStructUnionSpecifier_BuildDestroy(program,
                                                       pStructUnionSpecifier,
                                                       pVariableName,
                                                       bVariableNameIsPointer,
                                                       BuildTypeInit);                    
                }
            }
            else if (buildType == BuildTypeDestroy ||
                     buildType == BuildTypeInit ||                     
                     buildType == BuildTypeStaticInit)
            {
                TStructUnionSpecifier* pStructUnionSpecifier =
                    TSpecifier_As_TStructUnionSpecifier(pSpecifier);
                TStructUnionSpecifier_BuildDestroy(program,
                                                   pStructUnionSpecifier,
                                                   pVariableName,
                                                   bVariableNameIsPointer,
                                                   buildType);
            }
            else
            {
                ASSERT(false);
            }
        }
        else
        {
            TStructUnionSpecifier* pStructUnionSpecifier =
                TSpecifier_As_TStructUnionSpecifier(pSpecifier);
            TStructUnionSpecifier_BuildDestroy(program,
                                               pStructUnionSpecifier,
                                               pVariableName,
                                               bVariableNameIsPointer,
                                               buildType);
        }

    }
    else if (pSpecifier->Type == TEnumSpecifier_ID)
    {
        printf("enum %s\n", declaratorName);
        ASSERT(false);
    }
    else
    {
        ASSERT(false);
    }
    //printf("%s = false\n", TDeclarator_GetName(pStructDeclarator->pDeclarator));
}
//}


void AstPlayground(TProgram* program)
{
    TDeclaration * p = TProgram_FindDeclaration(program, "X");
    TDeclarator *pDeclarator = TDeclaration_FindDeclarator(p, "X");

    printf("void X_Destroy(X* pX) {\n");
    BuildDestroy(program,
        (TSpecifierQualifierList*)&p->Specifiers,
                 pDeclarator,
                 NULL,
                 "pX",
                 true,
                 BuildTypeDestroy);

    printf("}\n");
    printf("------------------------------------------\n");

    printf("X* X_Create() {\n");
    BuildDestroy(program,
        (TSpecifierQualifierList*)&p->Specifiers,
                 pDeclarator,
                 NULL,
                 "pX",
                 true,
                 BuildTypeCreate);

    printf("}\n");

    printf("void X_Delete(X* pX) {\n");
    BuildDestroy(program,
        (TSpecifierQualifierList*)&p->Specifiers,
                 pDeclarator,
                 NULL,
                 "pX",
                 true,
                 BuildTypeDelete);

    printf("}\n");
    printf("------------------------------------------\n");
    printf("void X_Init(X* pX) {\n");
    BuildDestroy(program,
        (TSpecifierQualifierList*)&p->Specifiers,
                 pDeclarator,
                 NULL,
                 "pX",
                 true,
                 BuildTypeInit);

    printf("}\n");
    printf("------------------------------------------\n");
    printf("static init = {\n");
    BuildDestroy(program,
        (TSpecifierQualifierList*)&p->Specifiers,
                 pDeclarator,
                 NULL,
                 NULL,
                 false,
                 BuildTypeStaticInit);
    printf("}\n");

    //TDeclaration_Is_FunctionDeclaration(p);
    //    TDeclaration_GetFunctionArguments();

    //TDeclaration_Is_FunctionDefinition(p);

    //TParameterTypeList * pArgs =
      //  TDeclaration_GetFunctionArguments(p);
    //if (pArgs)
    //{
      //  ForEachListItem(TParameter, pParameter, &pArgs->ParameterList)
        //{
          //  printf("%s\n", TParameter_GetName(pParameter));
            //printf("%s\n", TParameter_GetTypedefName(pParameter));
            //printf(TParameter_IsDirectPointer(pParameter) ? "true" : "false");

            //printf("\n");

            //BuildDestroy(program,
              //  (TSpecifierQualifierList*)&pParameter->Specifiers,
                //          &pParameter->Declarator,
                  //        NULL);
        //}
    //}
}
