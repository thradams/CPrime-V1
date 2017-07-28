


#include <stdio.h>

#include ".\Parser\AstPrint.h"
#include ".\Parser\Parser.h"
#include ".\CPrime\CodePrint.h"
#include "..\CPrime\Base\Path.h"
#include "UnitTest.h"

///
#include "..\CPrime\CPrime\Templates\ListTemplate.h"
///
void AstPlayground(TProgram* program);

void Compile(const char* configFileName,
    const char* inputFileName,
	const char* outputFileName,
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

            //strcat(dir, "\\out\\");
            //MakePath(outc, drive, dir, fname, ext);

            printf("Generating code for %s...\n", inputFileName);
            TProgram_PrintCodeToFile(&program, options, outputFileName, inputFileName);
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
	printf("          cprime -config config.h hello.c -out hello.c\n");
    printf("          cprime -config config.h -P hello.c\n");	
    printf("          cprime -E hello.c\n");
    printf("\n");
    printf("Options:\n");
    printf("-config FILE                          Configuration file.\n");
    printf("-help                                 Print this message.\n");
	printf("-out                                  Sets ouput file name.\n");
    printf("-E                                    Preprocess to console.\n");
    printf("-P                                    Preprocess to file.\n");
    printf("-A                                    Output AST to file.\n");

}
int main(int argc, char* argv[])
{
    printf("\n");
    printf("C' Version " __DATE__ "\n");
    printf("https://github.com/thradams/CPrime\n\n");


    //AllTests();

    if (argc < 2)
    {
        PrintHelp();
        return 1;
    }

    const char* configFileName = NULL;

	String outputFullPath = NULL;
	

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
            if (i + 1 < argc)
            {
                configFileName = argv[i + 1];
                i++;
            }
            else
            {
                printf("missing file\n");
            }
        }
		else if (strcmp(option, "-out") == 0)
		{
			if (i + 1 < argc)
			{
				GetFullPath(argv[i + 1], &outputFullPath);
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
                Compile(configFileName, inputFullPath, outputFullPath, &options, bPrintASTFile);
            }
            String_Destroy(&inputFullPath);
		        
		}

    }
	String_Destroy(&outputFullPath);

    return 0;
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
   
        
}
