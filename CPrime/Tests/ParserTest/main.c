

#include "..\..\Parser.h"

#include <stdio.h>
#include <string.h>

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



#define ParserMatch(parser, token) \
 Parser_MatchToken((parser), (token), NULL); \
 TEST(!Parser_HasError((parser)));

void Parser_Test1(void)
{
    //Este parte do parser poderia ser mais um scanner
    //
    struct Parser parser;
    Parser_InitString(&parser, "a", "int a /*comment*/ = 1 + 2;");
    ParserMatch(&parser, TK_INT);

    TEST(Parser_LookAheadToken(&parser) == TK_EQUALS_SIGN);

    ParserMatch(&parser, TK_IDENTIFIER);
    ParserMatch(&parser, TK_EQUALS_SIGN);
    ParserMatch(&parser, TK_DECIMAL_INTEGER);
    ParserMatch(&parser, TK_PLUS_SIGN);
    ParserMatch(&parser, TK_DECIMAL_INTEGER);
    ParserMatch(&parser, TK_SEMICOLON);
    ParserMatch(&parser, TK_EOF);
    Parser_Destroy(&parser);
}

void Parser_Test2(void)
{
    struct Parser parser;
    Parser_InitString(&parser, "a", "int a = 1 + 2;");
    ParserMatch(&parser, TK_INT);
    ParserMatch(&parser, TK_IDENTIFIER);

    ParserMatch(&parser, TK_EQUALS_SIGN);
    ParserMatch(&parser, TK_DECIMAL_INTEGER);
    ParserMatch(&parser, TK_PLUS_SIGN);
    ParserMatch(&parser, TK_DECIMAL_INTEGER);
    ParserMatch(&parser, TK_SEMICOLON);
    ParserMatch(&parser, TK_EOF);
    ParserMatch(&parser, TK_EOF);
    Parser_Destroy(&parser);
}


void Parser_Test3(void)
{
    struct Parser parser;
    Parser_InitString(&parser, "a", "int a  =  1 + 2;");
    ParserMatch(&parser, TK_INT);
    ParserMatch(&parser, TK_IDENTIFIER);
    TEST(Parser_LookAheadToken(&parser) == TK_DECIMAL_INTEGER);
    TEST(Parser_LookAheadToken(&parser) == TK_DECIMAL_INTEGER);

    ParserMatch(&parser, TK_EQUALS_SIGN);
    ParserMatch(&parser, TK_DECIMAL_INTEGER);
    ParserMatch(&parser, TK_PLUS_SIGN);
    ParserMatch(&parser, TK_DECIMAL_INTEGER);
    ParserMatch(&parser, TK_SEMICOLON);
    ParserMatch(&parser, TK_EOF);
    ParserMatch(&parser, TK_EOF);
    Parser_Destroy(&parser);
}


void Parser_Test4(void)
{
    const char* code =
        "a = \n"
        "#if 0\n"
        "1\n"
        "#else\n"
        "int\n"
        "#endif\n"
        "\n";

    struct Parser parser;
    Parser_InitString(&parser, "a", code);
    ParserMatch(&parser, TK_IDENTIFIER);
    TEST(Parser_LookAheadToken(&parser) == TK_INT);
    ParserMatch(&parser, TK_EQUALS_SIGN);
    ParserMatch(&parser, TK_INT);
    ParserMatch(&parser, TK_EOF);
    Parser_Destroy(&parser);
}


void Parser_Test5(void)
{
    const char* code =
        "#define false 0\n"
        "int main()\n"
        "{\n"
        "return (false);\n"
        "}\n";

    struct Parser parser;
    Parser_InitString(&parser, "a", code);
    ParserMatch(&parser, TK_INT);

    ParserMatch(&parser, TK_IDENTIFIER);
    ParserMatch(&parser, TK_LEFT_PARENTHESIS);
    ParserMatch(&parser, TK_RIGHT_PARENTHESIS);
    ParserMatch(&parser, TK_LEFT_CURLY_BRACKET);
    ParserMatch(&parser, TK_RETURN);


    TEST(Scanner_TokenAt(&parser.Scanner, 0) == TK_LEFT_PARENTHESIS);

    TEST(Scanner_TokenAt(&parser.Scanner, 1) == TK_MACRO_CALL);


    TEST(Scanner_TokenAt(&parser.Scanner, 2) == TK_DECIMAL_INTEGER);



    TEST(Scanner_TokenAt(&parser.Scanner, 3) == TK_MACRO_EOF);

    TEST(Parser_LookAheadToken(&parser) == TK_DECIMAL_INTEGER);
    ParserMatch(&parser, TK_LEFT_PARENTHESIS);


    ParserMatch(&parser, TK_DECIMAL_INTEGER);
    ParserMatch(&parser, TK_RIGHT_PARENTHESIS);
    ParserMatch(&parser, TK_SEMICOLON);
    ParserMatch(&parser, TK_RIGHT_CURLY_BRACKET);
    ParserMatch(&parser, TK_EOF);
    Parser_Destroy(&parser);
}

void Parser_Test6(void)
{
    const char* code =
        "#define false 0\n"
        "int main()\n"
        "{\n"
        "return (false);\n"
        "}\n";

    struct Parser parser;
    Parser_InitString(&parser, "a", code);
    ParserMatch(&parser, TK_INT);

    ParserMatch(&parser, TK_IDENTIFIER);
    ParserMatch(&parser, TK_LEFT_PARENTHESIS);
    ParserMatch(&parser, TK_RIGHT_PARENTHESIS);
    ParserMatch(&parser, TK_LEFT_CURLY_BRACKET);
    ParserMatch(&parser, TK_RETURN);
    ParserMatch(&parser, TK_LEFT_PARENTHESIS);
    ParserMatch(&parser, TK_DECIMAL_INTEGER);
    ParserMatch(&parser, TK_RIGHT_PARENTHESIS);
    ParserMatch(&parser, TK_SEMICOLON);
    ParserMatch(&parser, TK_RIGHT_CURLY_BRACKET);
    ParserMatch(&parser, TK_EOF);
    Parser_Destroy(&parser);
}


int main()
{
    printf("RUNNING TESTS ...\n");
   

    Parser_Test1();
    Parser_Test2();
    Parser_Test3();
    Parser_Test4();
    Parser_Test5();
    Parser_Test6();

    if (error_count == 0)
    {
        printf("ALL TESTS OK\n");
    }
    printf("\n");

    return error_count;
}
