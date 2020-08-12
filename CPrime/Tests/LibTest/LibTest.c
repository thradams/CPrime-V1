#include "../../cpr.h"

static int error_count = 0;
static int sucess_count = 0;

#define TEST(condition) \
if (condition)\
{\
  sucess_count++;\
}\
else\
{\
  printf("%s LINE %d FAILED!\n", __FUNCTION__, __LINE__); \
  error_count++;\
}


void AstTest()
{
    struct Options options2 = OPTIONS_INIT;
    options2.Target = (enum CompilerTarget)CompilerTarget_Annotated;
    options2.bNoImplicitTag = false;

    struct SyntaxTree syntaxTree;
    SyntaxTree_Init(&syntaxTree);
    if (GetASTFromString("int i = 1;", &options2, &syntaxTree))
    {
        struct StrBuilder sb = STRBUILDER_INIT;
        StrBuilder_Reserve(&sb, 500);
        SyntaxTree_PrintCodeToString(&syntaxTree, &options2, &sb);
        TEST(strcmp(sb.c_str, "int i = 1;") == 0);
        
        StrBuilder_Destroy(&sb);
    }
    SyntaxTree_Destroy(&syntaxTree);
}

void TestStruct()
{
    #define ENDL  "\n"
    const char* code =
        " struct X         " ENDL
        " {                " ENDL                  
        "   char * auto s; " ENDL
        " };               " ENDL;
        "struct X *p;      " ENDL;

    struct Options options2 = OPTIONS_INIT;
    options2.Target = (enum CompilerTarget)CompilerTarget_Annotated;
    options2.bNoImplicitTag = false;

    struct SyntaxTree syntaxTree;
    SyntaxTree_Init(&syntaxTree);
    if (GetASTFromString(code, &options2, &syntaxTree))
    {
        
        struct TStructUnionSpecifier* pDeclaration = 
            SymbolMap_FindCompleteStructUnionSpecifier(&syntaxTree.GlobalScope, "X");

        
        struct StrBuilder sb = STRBUILDER_INIT;
        StrBuilder_Reserve(&sb, 500);

        


      
       

        StrBuilder_Destroy(&sb);
    }
    SyntaxTree_Destroy(&syntaxTree);
}


/*
 Este programa testa o uso da lib na forma almagamated (cpr.h e cpr.c)
*/
int main()
{
    TestStruct();
    AstTest();
}
