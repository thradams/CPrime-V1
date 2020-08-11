#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#define chdir _chdir
#else
#endif

#include "build.h"


/*
Este projeto cria a versao amalgamated do c e do header
*/
int main()
{
    //vai para diretorio do cprime
    chdir("../");

    //monta amalgamation
    const char* files[] = {
        "StringEx.c",
        "StrArray.c",
        "Stream.c",
        "StrBuilder.c",
        "Mem.c",
        "Map2.c",
        "Map.c",
        "Macro.c",
        "SymbolMap.c",
        "Scanner.c",
        "PPToken.c",
        "Path.c",
        "TokenArray.c",
        "Options.c",        
        "LocalStrBuilder.c",
        "CodePrint.c",
        "BasicScanner.c",
        "Ast.c",
        "Parser.c"
    };
        

    amalgamate("cpr.c", /*bHeaderMode*/false, files, (sizeof(files) / sizeof(files[0])));


    //monta header publico selecionando alguns headers para incluir
    const char* headers[] = {
        
        "Path.h",
        "StringEx.h",
        "StrArray.h",
        "Stream.h",
        "StrBuilder.h",
        "LocalStrBuilder.h",
        "Map.h",
        "Mem.c",
        "Map2.h",
        "SymbolMap.h",
        "PPToken.h",
        "TokenArray.h",
        "Options.h",
        "Macro.h",
        "BasicScanner.h",                
        "Scanner.h",
        "Ast.h",
        "Parser.h",
        "CodePrint.h"
    };


    amalgamate("cpr.h",  /*bHeaderMode*/true, headers, (sizeof(headers) / sizeof(headers[0])));
}
