


#include <stdio.h>
#include <time.h>  
#include "AstPrint.h"
#include "Parser.h"
#include "CodePrint.h"
#include "Path.h"
#include "Mem.h"
#include "Options.h"
#include "AstPrint2.h"

int Compile(const char* configFileName,
    const char* inputFileName,
    const char* outputFileName,
    Options* options,
    bool bPrintASTFile)
{
    int bSuccess = 0;
    TProgram program;
    TProgram_Init(&program);

    clock_t tstart = clock();

    printf("Parsing...\n");
    if (GetAST(inputFileName, configFileName, options, &program))
    {
        bSuccess = 1;


        char drive[CPRIME_MAX_DRIVE];
        char dir[CPRIME_MAX_DIR];
        char fname[CPRIME_MAX_FNAME];
        char ext[CPRIME_MAX_EXT];
        SplitPath(inputFileName, drive, dir, fname, ext); // C4996


        printf("Generating code for %s...\n", inputFileName);
        if (outputFileName)
        {
            if (bPrintASTFile)
            {
                //TProgram_PrintAstToFile(&program, outputFileName, inputFileName);
                TProgram_PrintAstToXML(&program, outputFileName, inputFileName);
            }
            else
            {
                TProgram_PrintCodeToFile(&program, options, outputFileName, inputFileName);
            }
        }
        else
        {
            char outc[CPRIME_MAX_DRIVE + CPRIME_MAX_DIR + CPRIME_MAX_FNAME + CPRIME_MAX_EXT + 1];

            if (bPrintASTFile)
            {
                //faz um  arquivo com extensao json
                //MakePath(outc, drive, dir, fname, ".json");
                //TProgram_PrintAstToFile(&program, outc, inputFileName);
                MakePath(outc, drive, dir, fname, ".xml");
                TProgram_PrintAstToXML(&program, outc, inputFileName);
            }
            else
            {
                //gera em cima do proprio arquivo
                MakePath(outc, drive, dir, fname, ext);
                TProgram_PrintCodeToFile(&program, options, outc, inputFileName);
            }
        }

        clock_t tend = clock();
        printf("Completed in %d second(s)\n", (int)((tend - tstart) / CLOCKS_PER_SEC));

    }
    TProgram_Destroy(&program);
    return bSuccess;
}

void PrintHelp()
{
    printf("Syntax: cprime [options] [file ...]\n");
    printf("\n");
    printf("Examples: cprime hello.c\n");
    printf("          cprime -config config.h hello.c\n");
    printf("          cprime -config config.h hello.c -o hello.c\n");
    printf("          cprime -config config.h -P hello.c\n");
    printf("          cprime -E hello.c\n");
    printf("          cprime -P hello.c\n");
    printf("          cprime -A hello.c\n");
    printf("\n");
    printf("PrintCodeOptions:\n");
    printf("-config FILE                          Configuration fp.\n");    
    printf("-outDir                               Directory for output.\n");
    printf("-help                                 Print this message.\n");
    printf("-o FILE                               Sets ouput file name.\n");
    printf("-E                                    Preprocess to console.\n");
    printf("-P                                    Preprocess to file.\n");
    printf("-A                                    Output AST to file.\n");
    printf("-r                                    Reverts generation.\n");
    printf("--removeComments                      Remove comments from output\n");
    printf("-build FILE                           Compile each file separatelly to outDir\n");

}



char* CompileText(int type, char* input)
{
    char* output = NULL;
    TProgram program;
    TProgram_Init(&program);
    if (GetASTFromString(input, &program))
    {
        Options options2 = OPTIONS_INIT;
        options2.Target = (enum CompilerTarget) type;


        StrBuilder sb = STRBUILDER_INIT;
        StrBuilder_Reserve(&sb, 500);
        if (options2.Target == CompilerTarget_Preprocessed)
        {
            PrintPreprocessedToString2(&sb, input, NULL);
        }
        else
        {
            TProgram_PrintCodeToString(&program, &options2, &sb);
        }
        output = sb.c_str;
    }
    return output;
}


int main(int argc, char* argv[])
{
    printf("\n");
    printf("C' Version " __DATE__ "\n");
    printf("https://github.com/thradams/CPrime\n\n");

#ifdef _DEBUG
    //AllTests();
#endif
    if (argc < 2)
    {
        PrintHelp();
        return 1;
    }

    const char* outputFileName = NULL;
    const char* configFileName = NULL;
    const char* outputDir = NULL;
    

    String * /*@auto*/ outputFullPath = NULL;
    String * /*@auto*/ inputFullPath = NULL;
    String * /*@auto*/ buildFileFullPath = NULL;

    Options options = OPTIONS_INIT;
    options.Target = CompilerTarget_Annotated;

    bool bPrintPreprocessedToFile = false;
    bool bPrintPreprocessedToConsole = false;
    bool bPrintASTFile = false;

    clock_t tstart = clock();
    struct FileNodeList sources = { 0 };

    int numberOfFiles = 0;
    //a primeira fase é para recolher opcoes
    //a segunda eh para processar arquivos
    for (int fase = 0; fase < 2; fase++)
    {
        for (int i = 1; i < argc; i++)
        {
            const char* option = argv[i];
            if (strcmp(option, "-P") == 0)
            {
                options.Target = CompilerTarget_Preprocessed;
                bPrintPreprocessedToFile = true;
            }
            else if (strcmp(option, "-E") == 0)
            {
                options.Target = CompilerTarget_Preprocessed;
                bPrintPreprocessedToConsole = true;
            }
            else if (strcmp(option, "-r") == 0)
            {
                bPrintPreprocessedToConsole = true;
            }
            else if (strcmp(option, "-A") == 0)
            {
                bPrintASTFile = true;
            }
            else if (strcmp(option, "-a") == 0)
            {              
              options.bAmalgamate = true;
            }            
            else if (strcmp(option, "-help") == 0)
            {
                if (fase == 1)
                {
                    PrintHelp();
                }
            }
            else if (strcmp(option, "-build") == 0)
            {
                if (fase == 0)
                {
                    if (i + 1 < argc)
                    {
                        const char* buildFileName = argv[i + 1];
                        GetFullDir(buildFileName, &buildFileFullPath);
                        GetSources(NULL, buildFileName, &sources);
                    }
                    else
                    {
                        printf("missing file\n");
                        break;
                    }
                }
                i++;

            }
            else if (strcmp(option, "-cx") == 0)
            {
                options.Target = CompilerTarget_CXX;
            }            
            else if (strcmp(option, "-ca") == 0)
            {
                options.Target = CompilerTarget_Annotated;
            }
            else if (strcmp(option, "--removeComments") == 0)
            {
                options.bIncludeComments = false;
            }
            else if (strcmp(option, "-pr") == 0)
            {
                options.Target = CompilerTarget_Preprocessed;
            }
            else if (strcmp(option, "-outDir") == 0)
            {
                if (fase == 0)
                {
                    if (i + 1 < argc)
                    {
                        outputDir = argv[i + 1];
                    }
                    else
                    {
                        printf("missing file\n");
                        break;
                    }
                }
                i++;
            }
            else if (strcmp(option, "-config") == 0)
            {
                if (fase == 0)
                {
                    if (i + 1 < argc)
                    {
                        configFileName = argv[i + 1];
                    }
                    else
                    {
                        printf("missing file\n");
                        break;
                    }
                }
                i++;
            }
            else if (strcmp(option, "-o") == 0)
            {
                if (i + 1 < argc)
                {
                    outputFileName = argv[i + 1];
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
                if (fase == 1)
                {
                    //const char* inputFileName = option;
                    //String inputFullPath = NULL;
                    GetFullPath(option, &inputFullPath);

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
                }
                else
                {
                    numberOfFiles++;
                }
            }

        }
    }

    
    if (sources.pHead != NULL)
    {
        char inputItemPath[2000] = { 0 };
        char outputItemPath[2000] = { 0 };

        //criar o diretorio de output se nao existe
        strcat(outputItemPath, buildFileFullPath);
        strcat(outputItemPath, outputDir);
        strcat(outputItemPath, "\\");

        MkDir(outputItemPath);

      
        struct FileNode* pCurrent = sources.pHead;
        while (pCurrent != NULL)
        {
            inputItemPath[0] = 0;
            strcat(inputItemPath, buildFileFullPath);
            strcat(inputItemPath, pCurrent->Key);

            outputItemPath[0] = 0;
            if (outputDir)
            {
                //output eh relativo ao build.c
                strcat(outputItemPath, buildFileFullPath);
                strcat(outputItemPath, outputDir);
                strcat(outputItemPath, "\\");
                strcat(outputItemPath, pCurrent->Key);
            }

            if (!Compile(configFileName, inputItemPath, outputItemPath, &options, bPrintASTFile))
            {
                break;
            }
        
            pCurrent = pCurrent->pNext;
        }
    }

    clock_t tend = clock();
    printf("Total %d files in = %d seconds\n", numberOfFiles, (int)((tend - tstart) / CLOCKS_PER_SEC));

    FileNodeList_Destroy(&sources);
    Free(outputFullPath);
    Free(inputFullPath);
    Free(buildFileFullPath);

    PrintMemory();
    return 0;
}

