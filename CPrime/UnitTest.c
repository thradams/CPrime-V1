#include "UnitTest.h"
#include "Base\Stream.h"
#include "Parser\BasicScanner.h"
#include "Parser\Scanner.h"

#include "Parser\Parser.h"

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


#define MATCH(scanner, TK) \
 TEST(Scanner_CurrentToken((scanner)) == TK&& \
      Scanner_CurrentTokenIsActive((scanner)));\
 Scanner_Match((scanner));

#define MATCH_INACTIVE(scanner, TK) \
 TEST(Scanner_CurrentToken((scanner)) == TK && \
      !Scanner_CurrentTokenIsActive((scanner)));\
 Scanner_Match((scanner));

#define  MATCH_INACTIVE2(scanner, TK, lexeme)\
TEST(Scanner_CurrentToken((scanner)) == TK &&\
     strcmp(Scanner_CurrentLexeme(scanner), lexeme) == 0 &&\
     !Scanner_CurrentTokenIsActive((scanner)));\
Scanner_Match((scanner));

#define  MATCH2(scanner, TK, lexeme)\
TEST(Scanner_CurrentToken((scanner)) == TK &&\
     strcmp(Scanner_CurrentLexeme(scanner), lexeme) == 0 &&\
     Scanner_CurrentTokenIsActive((scanner)));\
Scanner_Match((scanner));

void Scanner_Test1()
{    
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Test\\Test1.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF)
        MATCH(&scanner2, TK_PRE_DEFINE)

        TEST(Scanner_LookAheadToken(&scanner2, 1) == TK_DECIMAL_INTEGER);
    TEST(Scanner_LookAheadToken(&scanner2, 1) == TK_DECIMAL_INTEGER);
    TEST(Scanner_LookAheadToken(&scanner2, 2) == TK_MACRO_EOF);
    TEST(Scanner_LookAheadToken(&scanner2, 3) == TK_BREAKLINE);
    TEST(Scanner_LookAheadToken(&scanner2, 4) == TK_EOF);
    TEST(Scanner_LookAheadToken(&scanner2, 5) == TK_EOF);
    TEST(Scanner_LookAheadToken(&scanner2, 6) == TK_EOF);

    MATCH(&scanner2, TK_MACRO_CALL)
        MATCH(&scanner2, TK_DECIMAL_INTEGER)
        MATCH(&scanner2, TK_MACRO_EOF)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)

        Scanner_Destroy(&scanner2);
}

void Scanner_Test2()
{    
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Test\\Test2.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_MACRO_CALL)
        MATCH(&scanner2, TK_DECIMAL_INTEGER)
        MATCH(&scanner2, TK_MACRO_EOF)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)

        Scanner_Destroy(&scanner2);
}
void Scanner_Test3()
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Test\\Test3.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF)
        MATCH(&scanner2, TK_PRE_DEFINE)

    
        MATCH(&scanner2, TK_MACRO_CALL)

   


        MATCH(&scanner2, TK_DECIMAL_INTEGER)
        MATCH(&scanner2, TK_SPACES)
        MATCH(&scanner2, TK_DECIMAL_INTEGER)
        MATCH(&scanner2, TK_MACRO_EOF)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_MACRO_CALL)
        MATCH(&scanner2, TK_STRING_LITERAL)
        MATCH(&scanner2, TK_MACRO_EOF)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)


        
        Scanner_Destroy(&scanner2);

   
}

void Scanner_Test4()
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Test\\Test4.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF)

        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_MACRO_CALL)
        MATCH(&scanner2, TK_LEFT_PARENTHESIS)
        MATCH(&scanner2, TK_DECIMAL_INTEGER)
        MATCH(&scanner2, TK_SPACES)
        MATCH(&scanner2, TK_PLUS_SIGN)
        MATCH(&scanner2, TK_SPACES)
        MATCH2(&scanner2, TK_IDENTIFIER, "foo")
        MATCH(&scanner2, TK_RIGHT_PARENTHESIS)
        MATCH(&scanner2, TK_MACRO_EOF)
        MATCH(&scanner2, TK_BREAKLINE)

        Scanner_Destroy(&scanner2);
}

void Scanner_Test5()
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Test\\Test5.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_MACRO_CALL)
        MATCH2(&scanner2, TK_STRING_LITERAL, "\"x ## y\"")
        MATCH(&scanner2, TK_MACRO_EOF)

        Scanner_Destroy(&scanner2);
}
void Scanner_Test6()
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Test\\Test6.h", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF)
        MATCH2(&scanner2, TK_IDENTIFIER, "BEGIN")
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_IF)
        MATCH2(&scanner2, TK_IDENTIFIER, "A")
        MATCH(&scanner2, TK_SPACES)
        MATCH2(&scanner2, TK_IDENTIFIER, "B")
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_ELSE)

        //MATCH_INACTIVE(&scanner2, TK_BREAKLINE) //#else
        MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "B")
        MATCH_INACTIVE(&scanner2, TK_SPACES)
        MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "D")
        MATCH_INACTIVE(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_ENDIF)
        //MATCH(&scanner2, TK_BREAKLINE) //#endif

        MATCH2(&scanner2, TK_IDENTIFIER, "END")
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)
        Scanner_Destroy(&scanner2);
    ///////////////////////////
}

void Scanner_Test7()
{
    //
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Test\\Test7.h", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF)
        //Test7.h
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_PRAGMA)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_VOID)
        MATCH(&scanner2, TK_SPACES)
        MATCH(&scanner2, TK_IDENTIFIER)
        MATCH(&scanner2, TK_LEFT_PARENTHESIS)
        MATCH(&scanner2, TK_RIGHT_PARENTHESIS)
        MATCH(&scanner2, TK_SEMICOLON)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)
        //Test7.h
        Scanner_Destroy(&scanner2);
    ///////////////////////////

    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Test\\Test7.c", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF)

        MATCH(&scanner2, TK_PRE_INCLUDE)

        //Test7.h
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_PRAGMA)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_VOID)
        MATCH(&scanner2, TK_SPACES)
        MATCH(&scanner2, TK_IDENTIFIER)
        MATCH(&scanner2, TK_LEFT_PARENTHESIS)
        MATCH(&scanner2, TK_RIGHT_PARENTHESIS)
        MATCH(&scanner2, TK_SEMICOLON)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_FILE_EOF)
        //Test7.h

        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_VOID)
        MATCH(&scanner2, TK_SPACES)
        MATCH(&scanner2, TK_IDENTIFIER)
        MATCH(&scanner2, TK_LEFT_PARENTHESIS)
        MATCH(&scanner2, TK_RIGHT_PARENTHESIS)
        MATCH(&scanner2, TK_SEMICOLON)
        MATCH(&scanner2, TK_BREAKLINE)

        MATCH(&scanner2, TK_EOF)
        Scanner_Destroy(&scanner2);

}


void Scanner_Test9()
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Test\\Test6.h", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF)
        MATCH2(&scanner2, TK_IDENTIFIER, "BEGIN")
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_IF)
        MATCH2(&scanner2, TK_IDENTIFIER, "A")
        MATCH(&scanner2, TK_SPACES)
        MATCH2(&scanner2, TK_IDENTIFIER, "B")
        MATCH(&scanner2, TK_BREAKLINE)
        
        TEST(Scanner_LookAheadTokenActive(&scanner2, 1) == 0);

        MATCH(&scanner2, TK_PRE_ELSE)

        //MATCH_INACTIVE(&scanner2, TK_BREAKLINE) //#else
        MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "B")
        MATCH_INACTIVE(&scanner2, TK_SPACES)
        MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "D")
        MATCH_INACTIVE(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_ENDIF)
        //MATCH(&scanner2, TK_BREAKLINE) //#endif

        MATCH2(&scanner2, TK_IDENTIFIER, "END")
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)
        Scanner_Destroy(&scanner2);
    ///////////////////////////
}


void Scanner_Test8()
{

    //
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Test\\Test8.h", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF)
        //Test8.h
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_EOF)
        //Test7.h
        Scanner_Destroy(&scanner2);
    ///////////////////////////

    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Test\\Test8.c", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF)

        MATCH(&scanner2, TK_PRE_INCLUDE)

        //Test8.h
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_PRE_DEFINE)
        MATCH(&scanner2, TK_FILE_EOF)
        //Test8.h

        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_INT)
        MATCH(&scanner2, TK_SPACES)
        MATCH(&scanner2, TK_IDENTIFIER)
        MATCH(&scanner2, TK_SEMICOLON)
        MATCH(&scanner2, TK_BREAKLINE)
        MATCH(&scanner2, TK_EOF)
        Scanner_Destroy(&scanner2);



}

void Stream_Test1()
{
    SStream stream;
    SStream_Init(&stream, "name", "123");
    TEST(SStream_MatchChar(&stream, L'1'));
    TEST(SStream_LookAhead(&stream) == '3');
    TEST(SStream_MatchChar(&stream, L'2'));
    TEST(SStream_MatchChar(&stream, L'3'));
    TEST(SStream_MatchChar(&stream, L'\0'));
    TEST(SStream_MatchChar(&stream, L'\0'));
    SStream_Destroy(&stream);
}

void BasicScanner_Test1()
{
    BasicScanner scanner;

    BasicScanner_Init(&scanner, "name", "#if 1", BasicScannerType_Token);
    scanner.m_Token = TK_PRE_IF;

    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_PRE_IF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));

    BasicScanner_Destroy(&scanner);
}

void BasicScanner_Test2()
{
    BasicScanner scanner;
    BasicScanner_Init(&scanner, "name", "123\r\n", BasicScannerType_File);

    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_DECIMAL_INTEGER));
    TEST(BasicScanner_MatchToken(&scanner, TK_BREAKLINE));
    TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
    BasicScanner_Destroy(&scanner);
}

void BasicScanner_Test3()
{
    BasicScanner scanner;
    BasicScanner_Init(&scanner, "name", "#pragma once\r\n", BasicScannerType_File);

    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_PREPROCESSOR));
    TEST(BasicScanner_MatchToken(&scanner, TK_IDENTIFIER));
    TEST(BasicScanner_MatchToken(&scanner, TK_SPACES));
    TEST(BasicScanner_MatchToken(&scanner, TK_IDENTIFIER));
    TEST(BasicScanner_MatchToken(&scanner, TK_BREAKLINE));
    TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
    BasicScanner_Destroy(&scanner);
}

void BasicScanner_Test4()
{
    BasicScanner scanner;

    BasicScanner_Init(&scanner, "name", "//comment", BasicScannerType_File);
    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_LINE_COMMENT));
    TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
    BasicScanner_Destroy(&scanner);
}

void BasicScanner_Test5()
{
    BasicScanner scanner;

    BasicScanner_Init(&scanner, "name", "/*comment*/", BasicScannerType_File);

    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_COMMENT));
    TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
    BasicScanner_Destroy(&scanner);
}

#define ParserMatch(parser, token) \
 Parser_MatchToken((parser), (token), NULL); \
 TEST(!Parser_HasError((parser)));

void Parser_Test1()
{
    Parser parser;
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
    ParserMatch(&parser, TK_EOF);
    Parser_Destroy(&parser);
}

void Parser_Test2()
{
    Parser parser;
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


void Parser_Test3()
{
    Parser parser;
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


void Parser_Test4()
{
    const char* code =
        "a = \n"
        "#if 0\n"
        "1\n"
        "#else\n"
        "int\n"
        "#endif\n"
        "\n";

    Parser parser;
    Parser_InitString(&parser, "a", code);
    ParserMatch(&parser, TK_IDENTIFIER);
    TEST(Parser_LookAheadToken(&parser) == TK_INT);
    ParserMatch(&parser, TK_EQUALS_SIGN);    
    ParserMatch(&parser, TK_EOF);
    Parser_Destroy(&parser);
}

void AllTests()
{
    printf("RUNNING TESTS ...\n");

    Stream_Test1();

    BasicScanner_Test1();
    BasicScanner_Test2();
    BasicScanner_Test3();
    BasicScanner_Test4();
    BasicScanner_Test5();

    Scanner_Test8();
    Scanner_Test7();
    Scanner_Test3();


    Scanner_Test1();
    Scanner_Test2();

    Scanner_Test4();
    Scanner_Test5();
    Scanner_Test6();
    Scanner_Test7();
    Scanner_Test8();
    Scanner_Test9();

    Parser_Test1();
    Parser_Test2();
    Parser_Test3();
    Parser_Test4();

    if (error_count == 0)
    {
        printf("ALL TESTS OK\n");
    }
}
