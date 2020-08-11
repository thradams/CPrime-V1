#include "../cpr.h"


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
        if (strcmp(sb.c_str, "int i = 1;") == 0)
        {
        }
        StrBuilder_Destroy(&sb);
    }

}

int main()
{
    AstTest();
}