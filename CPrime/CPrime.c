


#include <stdio.h>
#include <time.h>  
#include "Path.h"
#include "cpr.h"


#define CONFIG_FILE_NAME "config.txt"
#define EXECUTABLE_NAME "cpc"

int Compile(const char* configFileName,
            const char* inputFileName,
            const char* outputFileName,
            struct Options* options)
{
    int bSuccess = 0;
    struct SyntaxTree pSyntaxTree;
    SyntaxTree_Init(&pSyntaxTree);

    clock_t tstart = clock();

    printf("Parsing...\n");
    if (GetAST(inputFileName, configFileName, options, &pSyntaxTree))
    {
        bSuccess = 1;


        char drive[CPRIME_MAX_DRIVE];
        char dir[CPRIME_MAX_DIR];
        char fname[CPRIME_MAX_FNAME];
        char ext[CPRIME_MAX_EXT];
        SplitPath(inputFileName, drive, dir, fname, ext); // C4996


        printf("Generating code for %s...\n", inputFileName);
        if (outputFileName[0] != '\0')
        {

            SyntaxTree_PrintCodeToFile(&pSyntaxTree, options, outputFileName, inputFileName);

        }
        else
        {
            char outc[CPRIME_MAX_DRIVE + CPRIME_MAX_DIR + CPRIME_MAX_FNAME + CPRIME_MAX_EXT + 1];


            //gera em cima do proprio arquivo
            MakePath(outc, drive, dir, fname, ext);
            SyntaxTree_PrintCodeToFile(&pSyntaxTree, options, outc, inputFileName);
        }

        clock_t tend = clock();
        printf("Completed in %d second(s)\n", (int)((tend - tstart) / CLOCKS_PER_SEC));

    }
    SyntaxTree_Destroy(&pSyntaxTree);
    return bSuccess;
}

void PrintHelp()
{
    printf("Syntax: " EXECUTABLE_NAME " [options] [file ...]\n");
    printf("\n");
    printf("Examples: " EXECUTABLE_NAME " hello.c\n");
    printf("          " EXECUTABLE_NAME " -config config.h hello.c\n");
    printf("          " EXECUTABLE_NAME " -config config.h hello.c -o hello.c\n");
    printf("          " EXECUTABLE_NAME " -config config.h -P hello.c\n");
    printf("          " EXECUTABLE_NAME " -E hello.c\n");
    printf("          " EXECUTABLE_NAME " -P hello.c\n");
    printf("          " EXECUTABLE_NAME " -A hello.c\n");
    printf("\n");
    printf("struct PrintCodeOptions:\n");
    printf("-config FILE                          Configuration fp.\n");
    printf("-outDir                               Set the directory for output.\n");
    printf("-help                                 Print this message.\n");
    printf("-o FILE                               Sets ouput file name.\n");
    printf("-E                                    Preprocess to console.\n");
    printf("-P                                    Preprocess to file.\n");    
    printf("-cx                                   Generate C'.\n");
    printf("-ca                                   Generated C annotated\n");
    printf("-removeComments                       Remove comments from output\n");
    printf("-buildfile                            Compile all sources defined in inputfile\n");
    printf("                                      (not recursive)\n");
    printf("-build                                Build of all sources used by the input file\n");
    printf("                                      -build with -o generates amalgamation\n");
    printf("                                      -outDir can define build output\n");
    printf("-sources                              Prints all sources used\n");
    printf("-noImplicitTag                        Disable implicit function tags\n");

}



char* CompileText(int type, int bNoImplicitTag, char* input)
{
    char* output = NULL;

    struct Options options2 = OPTIONS_INIT;
    options2.Target = (enum CompilerTarget)type;
    options2.bNoImplicitTag = bNoImplicitTag;

    struct SyntaxTree pSyntaxTree;
    SyntaxTree_Init(&pSyntaxTree);
    if (GetASTFromString(input, &options2, &pSyntaxTree))
    {


        struct StrBuilder sb = STRBUILDER_INIT;
        StrBuilder_Reserve(&sb, 500);
        if (options2.Target == CompilerTarget_Preprocessed)
        {
            PrintPreprocessedToString2(&sb, input, NULL);
        }
        else
        {
            SyntaxTree_PrintCodeToString(&pSyntaxTree, &options2, &sb);
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

    //char * includes = getenv("INCLUDES");

#ifdef _DEBUG
    //AllTests();
#endif
    if (argc < 2)
    {
        PrintHelp();
        return 1;
    }

    char outputDirFullPath[CPRIME_MAX_PATH] = { 0 };

    char cxconfigFileFullPath[CPRIME_MAX_PATH];
    GetFullDirS(argv[0], cxconfigFileFullPath, CPRIME_MAX_PATH);
    strcat(cxconfigFileFullPath, CONFIG_FILE_NAME);


    if (FileExists(cxconfigFileFullPath))
    {
        printf("using config file %s\n", cxconfigFileFullPath);
        // configFileName = cxconfigFileFullPath;
    }
    else
    {
        cxconfigFileFullPath[0] = 0;
    }


    char outputFileFullPath[CPRIME_MAX_PATH] = { 0 };
    char inputFileFullPath[CPRIME_MAX_PATH] = { 0 };


    struct Options options = OPTIONS_INIT;
    options.Target = CompilerTarget_Annotated;

    bool bPrintPreprocessedToFile = false;
    bool bPrintPreprocessedToConsole = false;
    
    bool bBuildFile = false;
    bool bBuild = false;
    bool bSources = false;

    clock_t tstart = clock();
    struct FileNodeList sources = { 0 };


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
        else if (strcmp(option, "-a") == 0)
        {
            options.bAmalgamate = true;
        }
        else if (strcmp(option, "-help") == 0)
        {
            PrintHelp();
            return 0;
        }
        else if (strcmp(option, "-buildfile") == 0)
        {

            bBuildFile = true;
        }
        else if (strcmp(option, "-build") == 0)
        {
            bBuild = true;
        }
        else if (strcmp(option, "-sources") == 0)
        {
            bSources = true;
        }
        else if (strcmp(option, "-cx") == 0)
        {
            options.Target = CompilerTarget_CXX;
        }
        else if (strcmp(option, "-ca") == 0)
        {
            options.Target = CompilerTarget_Annotated;
        }
        else if (strcmp(option, "-removeComments") == 0)
        {
            options.bIncludeComments = false;
        }
        else if (strcmp(option, "-noImplicitTag") == 0)
        {
            options.bNoImplicitTag = true;
        }
        else if (strcmp(option, "-pr") == 0)
        {
            options.Target = CompilerTarget_Preprocessed;
        }
        else if (strcmp(option, "-outDir") == 0)
        {
            if (i + 1 < argc)
            {
                GetFullPathS(argv[i + 1], outputDirFullPath);
                i++;
            }
            else
            {
                printf("missing file\n");
                break;
            }
        }
        else if (strcmp(option, "-config") == 0)
        {

            if (i + 1 < argc)
            {
                GetFullPathS(argv[i + 1], cxconfigFileFullPath);
                i++;
            }
            else
            {
                printf("missing file\n");
                break;
            }
        }
        else if (strcmp(option, "-o") == 0)
        {
            if (i + 1 < argc)
            {
                GetFullPathS(argv[i + 1], outputFileFullPath);
                i++;
            }
            else
            {
                printf("missing file\n");
            }
        }
        else
        {
            GetFullPathS(argv[i], inputFileFullPath);
        }
    }


    int numberOfFiles = 1;

    //-build without -o is generate all files
    if ((bBuildFile || bBuild)
        && outputFileFullPath[0] == '\0'
        )
    {
        printf("Output dir : %s\n", outputDirFullPath);
        if (bBuildFile)
        {
            GetSources(NULL, inputFileFullPath, false, &sources);
        }
        else
        {
            GetSources(cxconfigFileFullPath, inputFileFullPath, true, &sources);
        }
        if (sources.pHead != NULL)
        {
            char inputFileFullDir[CPRIME_MAX_PATH];
            GetFullDirS(inputFileFullPath, inputFileFullDir, CPRIME_MAX_PATH);
            const int inputFullDirLength = strlen(inputFileFullDir);

            //Cria o diretorio de ouput
            if (outputDirFullPath[0] != '\0')
            {
                MkDir(outputDirFullPath);
            }

            char outputItemPath[2000] = { 0 };
            struct FileNode* pCurrent = sources.pHead;
            while (pCurrent != NULL)
            {
                outputItemPath[0] = 0;
                if (outputDirFullPath[0] != '\0')
                {
                    strcat(outputItemPath, outputDirFullPath);
                    strcat(outputItemPath, "\\");
                }
                strcat(outputItemPath, pCurrent->Key + inputFullDirLength);

                if (!Compile(cxconfigFileFullPath, pCurrent->Key, outputItemPath, &options))
                {
                    numberOfFiles++;
                    break;
                }
                else
                {
                }

                pCurrent = pCurrent->pNext;
            }
        }
    }
    else if (bSources)
    {
        GetSources(cxconfigFileFullPath, inputFileFullPath, true, &sources);
        int fileCount = 0;
        struct FileNode* pCurrent = sources.pHead;
        while (pCurrent != NULL)
        {
            fileCount++;
            printf("%d: %s\n", fileCount, pCurrent->Key);
            pCurrent = pCurrent->pNext;
        }
    }
    else
    {
        if (bPrintPreprocessedToFile)
        {
            PrintPreprocessedToFile(inputFileFullPath, cxconfigFileFullPath);
        }
        else if (bPrintPreprocessedToConsole)
        {
            PrintPreprocessedToConsole(inputFileFullPath, cxconfigFileFullPath);
        }
        else
        {
            //-build with -o is amalgamate
            options.bAmalgamate = bBuild && outputFileFullPath[0] != '\0';

            Compile(cxconfigFileFullPath, inputFileFullPath, outputFileFullPath, &options);
            numberOfFiles++;
        }
    }



    clock_t tend = clock();
    printf("Total %d files in = %d seconds\n", numberOfFiles, (int)((tend - tstart) / CLOCKS_PER_SEC));

    FileNodeList_Destroy(&sources);


    void PrintMemory();
    PrintMemory();
    return 0;
}

