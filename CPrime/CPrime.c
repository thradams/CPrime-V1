


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


void AstPlayground(TProgram* program)
{
    TDeclaration * p = TProgram_FindDeclaration(program, "F");

    TDeclaration_Is_FunctionDeclaration(p);
    //    TDeclaration_GetFunctionArguments();

    TDeclaration_Is_FunctionDefinition(p);

    TParameterTypeList * pArgs =
        TDeclaration_GetFunctionArguments(p);
    if (pArgs)
    {
        ForEachListItem(TParameter, pParameter, &pArgs->ParameterList)
        {
            printf("%s\n", TParameter_GetName(pParameter));
            printf("%s\n", TParameter_GetTypedefName(pParameter));
            printf(TParameter_IsDirectPointer(pParameter) ? "true" : "false");

            printf("\n");

            TStructUnionSpecifier* pStruct =
                TParameter_Is_DirectPointerToStruct(program, pParameter);
            if (pStruct)
            {
                TSpecifierQualifierList *pSpecifierQualifierList = NULL;
                TStructDeclarator* pStructDeclarator = NULL;
                int i = 0;
                while (EachStructDeclarator(pStruct, &i, &pSpecifierQualifierList, &pStructDeclarator))
                {          
                    if (TDeclarator_IsPointer(pStructDeclarator->pDeclarator))
                    {
                        printf("%s = NULL\n", TDeclarator_GetName(pStructDeclarator->pDeclarator));
                    }
                    else
                    {
                        if (TSpecifierQualifierList_IsBool(pSpecifierQualifierList))
                        {
                            printf("%s = false\n", TDeclarator_GetName(pStructDeclarator->pDeclarator));
                        }
                        else if (TSpecifierQualifierList_IsChar(pSpecifierQualifierList))
                        {
                            printf("%s = '\0'\n", TDeclarator_GetName(pStructDeclarator->pDeclarator));
                        }
                        else if (TSpecifierQualifierList_IsAnyInteger(pSpecifierQualifierList))
                        {
                            printf("%s = 0\n", TDeclarator_GetName(pStructDeclarator->pDeclarator));
                        }
                        else if (TSpecifierQualifierList_IsAnyFloat(pSpecifierQualifierList))
                        {
                            printf("%s = 0.0\n", TDeclarator_GetName(pStructDeclarator->pDeclarator));
                        }
                        else
                        {
                            const char* typedefName = 
                                TSpecifierQualifierList_GetTypedefName(pSpecifierQualifierList);
                            if (typedefName)
                            {
                              //ve se tem funcao _Destroy
                              //typedefName
                              TDeclaration* pDeclaration2 =
                                  TProgram_GetFinalTypeDeclaration(program, typedefName);
                              if (pDeclaration2)
                              {
                                  //pDeclaration2->Specifiers
                              }
                            }
                        }
                        
                    }
                    
                }

            
            }

        }
    }
}
