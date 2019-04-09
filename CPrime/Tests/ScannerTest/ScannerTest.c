


#include "..\..\Scanner.h"


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

void Match(Scanner* pScanner,
    Tokens token,
    bool bExpectedActive,
    const char* expectedLexeme,
    const char* func,
    int line)
{
    Tokens tk = Scanner_TokenAt((pScanner), 0);
    const char* lexeme = Scanner_LexemeAt((pScanner), 0);
    bool bIsActive = Scanner_IsActiveAt((pScanner), 0);

    if (tk == token &&
        bIsActive == bExpectedActive &&
        (expectedLexeme == NULL || strcmp(expectedLexeme, lexeme) == 0))
    {
        Scanner_Match(pScanner);
        sucess_count++;
    }
    else
    {
        printf("%s LINE %d FAILED!\n", func, line);
        error_count++;
    }
}

#define MATCH(scanner, TK) \
  Match(scanner, TK, true, NULL, __FUNCTION__, __LINE__)

#define MATCH_INACTIVE(scanner, TK) \
  Match(scanner, TK, false, NULL, __FUNCTION__, __LINE__)

#define  MATCH_INACTIVE2(scanner, TK, lexeme)\
  Match(scanner, TK, false, lexeme, __FUNCTION__, __LINE__)

#define  MATCH2(scanner, TK, lexeme)\
  Match(scanner, TK, true, lexeme, __FUNCTION__, __LINE__)

void Scanner_Test1(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test1.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF);
    MATCH(&scanner2, TK_PRE_DEFINE);

    TEST(Scanner_TokenAt(&scanner2, 0) == TK_MACRO_CALL);
    TEST(Scanner_TokenAt(&scanner2, 1) == TK_DECIMAL_INTEGER);
    TEST(Scanner_TokenAt(&scanner2, 2) == TK_MACRO_EOF);
    TEST(Scanner_TokenAt(&scanner2, 3) == TK_BREAKLINE);
    //TEST(Scanner_TokenAt(&scanner2, 4) == TK_FILE_EOF);
    TEST(Scanner_TokenAt(&scanner2, 5) == TK_EOF);
    TEST(Scanner_TokenAt(&scanner2, 6) == TK_EOF);

    MATCH(&scanner2, TK_MACRO_CALL);
    MATCH(&scanner2, TK_DECIMAL_INTEGER);
    MATCH(&scanner2, TK_MACRO_EOF);
    MATCH(&scanner2, TK_BREAKLINE);
    //MATCH(&scanner2, TK_FILE_EOF)
    MATCH(&scanner2, TK_EOF);

    Scanner_Destroy(&scanner2);
}

void Scanner_Test2(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test2.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_MACRO_CALL);
    MATCH(&scanner2, TK_DECIMAL_INTEGER);
    MATCH(&scanner2, TK_MACRO_EOF);
    MATCH(&scanner2, TK_BREAKLINE);
    //MATCH(&scanner2, TK_FILE_EOF)
    MATCH(&scanner2, TK_EOF);

    Scanner_Destroy(&scanner2);
}
void Scanner_Test3(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test3.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF);

    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_MACRO_CALL);
    MATCH(&scanner2, TK_DECIMAL_INTEGER);
    MATCH(&scanner2, TK_SPACES);
    MATCH(&scanner2, TK_DECIMAL_INTEGER);
    MATCH(&scanner2, TK_MACRO_EOF);
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_MACRO_CALL);
    MATCH(&scanner2, TK_STRING_LITERAL);
    MATCH(&scanner2, TK_MACRO_EOF);
    MATCH(&scanner2, TK_BREAKLINE);
    //MATCH(&scanner2, TK_FILE_EOF)
    MATCH(&scanner2, TK_EOF);



    Scanner_Destroy(&scanner2);


}

void Scanner_Test4(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test4.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF);

    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_MACRO_CALL);
    MATCH(&scanner2, TK_LEFT_PARENTHESIS);
    MATCH(&scanner2, TK_DECIMAL_INTEGER);
    MATCH(&scanner2, TK_SPACES);
    MATCH(&scanner2, TK_PLUS_SIGN);
    MATCH(&scanner2, TK_SPACES);

    MATCH2(&scanner2, TK_IDENTIFIER, "foo");
    MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
    MATCH(&scanner2, TK_MACRO_EOF);
    MATCH(&scanner2, TK_BREAKLINE);

    Scanner_Destroy(&scanner2);
}

void Scanner_Test5(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test5.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_MACRO_CALL);
    MATCH2(&scanner2, TK_STRING_LITERAL, "\"x ## y\"");
    MATCH(&scanner2, TK_MACRO_EOF);

    Scanner_Destroy(&scanner2);
}

void Scanner_Test10(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test9.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_PRE_DEFINE);


    MATCH(&scanner2, TK_MACRO_CALL);
    MATCH(&scanner2, TK_DECIMAL_INTEGER);
    MATCH(&scanner2, TK_MACRO_EOF);
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_EOF);


    Scanner_Destroy(&scanner2);
}

void Scanner_Test11(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test12.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_IDENTIFIER);
    MATCH(&scanner2, TK_SPACES);
    MATCH(&scanner2, TK_PLUS_SIGN);
    MATCH(&scanner2, TK_SPACES);
    MATCH(&scanner2, TK_DECIMAL_INTEGER);
    MATCH(&scanner2, TK_EOF);

    Scanner_Destroy(&scanner2);
}




void Scanner_Test12(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test10.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_PRE_DEFINE);

    MATCH(&scanner2, TK_MACRO_CALL);
    MATCH(&scanner2, TK_DECIMAL_INTEGER);
    MATCH(&scanner2, TK_MACRO_EOF);
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_EOF);


    Scanner_Destroy(&scanner2);
}

void Scanner_Test13(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test11.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_PRE_DEFINE);

    MATCH(&scanner2, TK_MACRO_CALL);
    MATCH(&scanner2, TK_IDENTIFIER);
    MATCH(&scanner2, TK_MACRO_EOF);
    MATCH(&scanner2, TK_LEFT_PARENTHESIS);
    MATCH(&scanner2, TK_DECIMAL_INTEGER);
    MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_EOF);


    Scanner_Destroy(&scanner2);
}

void Scanner_Test15(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test14.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_BREAKLINE);

    MATCH(&scanner2, TK_MACRO_CALL);
    MATCH(&scanner2, TK_IDENTIFIER);
    MATCH(&scanner2, TK_SPACES);
    MATCH(&scanner2, TK_IDENTIFIER);

    MATCH(&scanner2, TK_MACRO_EOF);

    MATCH(&scanner2, TK_EOF);


    Scanner_Destroy(&scanner2);
}

void Scanner_Test14(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test13.h", FileIncludeTypeQuoted, false);

    MATCH(&scanner2, TK_BOF);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_PRE_DEFINE);

    MATCH(&scanner2, TK_MACRO_CALL);
    MATCH(&scanner2, TK_IDENTIFIER);
    MATCH(&scanner2, TK_MACRO_EOF);
    MATCH(&scanner2, TK_SPACES);
    MATCH(&scanner2, TK_IDENTIFIER);
    MATCH(&scanner2, TK_LEFT_PARENTHESIS);
    MATCH(&scanner2, TK_DECIMAL_INTEGER);
    MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_EOF);


    Scanner_Destroy(&scanner2);
}


void Scanner_Test6(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test6.h", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF);
    MATCH2(&scanner2, TK_IDENTIFIER, "BEGIN");
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_PRE_IF);
    MATCH2(&scanner2, TK_IDENTIFIER, "A");
    MATCH(&scanner2, TK_SPACES);
    MATCH2(&scanner2, TK_IDENTIFIER, "B");
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH_INACTIVE(&scanner2, TK_PRE_ELSE);

    //MATCH_INACTIVE(&scanner2, TK_BREAKLINE) //#else
    MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "B");
    MATCH_INACTIVE(&scanner2, TK_SPACES);
    MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "D");
    MATCH_INACTIVE(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_PRE_ENDIF);
    //MATCH(&scanner2, TK_BREAKLINE) //#endif

    MATCH2(&scanner2, TK_IDENTIFIER, "END");
    MATCH(&scanner2, TK_BREAKLINE);
    //MATCH(&scanner2, TK_FILE_EOF)
    MATCH(&scanner2, TK_EOF);
    Scanner_Destroy(&scanner2);
    ///////////////////////////
}

void Scanner_Test7(void)
{
    //
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test7.h", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF);
    //Test7.h
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_PRE_PRAGMA);
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_VOID);
    MATCH(&scanner2, TK_SPACES);
    MATCH(&scanner2, TK_IDENTIFIER);
    MATCH(&scanner2, TK_LEFT_PARENTHESIS);
    MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
    MATCH(&scanner2, TK_SEMICOLON);
    MATCH(&scanner2, TK_BREAKLINE);
    //MATCH(&scanner2, TK_FILE_EOF)
    MATCH(&scanner2, TK_EOF);
    //Test7.h
    Scanner_Destroy(&scanner2);
    ///////////////////////////

    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test7.c", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF);

    MATCH(&scanner2, TK_PRE_INCLUDE);

    //Test7.h
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_PRE_PRAGMA);
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_VOID);
    MATCH(&scanner2, TK_SPACES);
    MATCH(&scanner2, TK_IDENTIFIER);
    MATCH(&scanner2, TK_LEFT_PARENTHESIS);
    MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
    MATCH(&scanner2, TK_SEMICOLON);
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_FILE_EOF);
    //Test7.h;

    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_VOID);
    MATCH(&scanner2, TK_SPACES);
    MATCH(&scanner2, TK_IDENTIFIER);
    MATCH(&scanner2, TK_LEFT_PARENTHESIS);
    MATCH(&scanner2, TK_RIGHT_PARENTHESIS);
    MATCH(&scanner2, TK_SEMICOLON);
    MATCH(&scanner2, TK_BREAKLINE);
    //MATCH(&scanner2, TK_FILE_EOF)
    MATCH(&scanner2, TK_EOF);
    Scanner_Destroy(&scanner2);

}


void Scanner_Test9(void)
{
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test6.h", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF);
    MATCH2(&scanner2, TK_IDENTIFIER, "BEGIN");
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_PRE_IF);
    MATCH2(&scanner2, TK_IDENTIFIER, "A");
    MATCH(&scanner2, TK_SPACES);
    MATCH2(&scanner2, TK_IDENTIFIER, "B");
    MATCH(&scanner2, TK_BREAKLINE);

    TEST(Scanner_IsActiveAt(&scanner2, 1) == 0);

    MATCH_INACTIVE(&scanner2, TK_PRE_ELSE);

    //MATCH_INACTIVE(&scanner2, TK_BREAKLINE) //#else
    MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "B");
    MATCH_INACTIVE(&scanner2, TK_SPACES);
    MATCH_INACTIVE2(&scanner2, TK_IDENTIFIER, "D");
    MATCH_INACTIVE(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_PRE_ENDIF);
    //MATCH(&scanner2, TK_BREAKLINE) //#endif

    MATCH2(&scanner2, TK_IDENTIFIER, "END");
    MATCH(&scanner2, TK_BREAKLINE);
    //MATCH(&scanner2, TK_FILE_EOF)
    MATCH(&scanner2, TK_EOF);
    Scanner_Destroy(&scanner2);
    ///////////////////////////
}


void Scanner_Test8(void)
{

    //
    Scanner scanner2;
    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test8.h", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF);
    //Test8.h
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_PRE_DEFINE);
    //MATCH(&scanner2, TK_FILE_EOF)
    MATCH(&scanner2, TK_EOF);
    //Test7.h
    Scanner_Destroy(&scanner2);
    ///////////////////////////

    Scanner_Init(&scanner2);
    Scanner_IncludeFile(&scanner2, ".\\Files\\Test8.c", FileIncludeTypeQuoted, false);
    MATCH(&scanner2, TK_BOF);

    MATCH(&scanner2, TK_PRE_INCLUDE);

    //Test8.h
    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_PRE_DEFINE);
    MATCH(&scanner2, TK_FILE_EOF);
    //Test8.h

    MATCH(&scanner2, TK_BREAKLINE);
    MATCH(&scanner2, TK_INT);
    MATCH(&scanner2, TK_SPACES);
    MATCH(&scanner2, TK_IDENTIFIER);
    MATCH(&scanner2, TK_SEMICOLON);
    MATCH(&scanner2, TK_BREAKLINE);
    //MATCH(&scanner2, TK_FILE_EOF)
    MATCH(&scanner2, TK_EOF);
    Scanner_Destroy(&scanner2);



}




int main()
{
    printf("RUNNING TESTS ...\n");
    //Scanner_Test15();
    Scanner_Test14();
    Scanner_Test10();
    Scanner_Test11();
    Scanner_Test12();
    Scanner_Test13();
    Scanner_Test1();
    Scanner_Test2();
    Scanner_Test3();
    Scanner_Test4();
    Scanner_Test5();
    Scanner_Test6();
    Scanner_Test7();
    Scanner_Test8();
    Scanner_Test9();
    Scanner_Test10();
    Scanner_Test11();

    if (error_count == 0)
    {
        printf("ALL TESTS OK\n");
    }
    printf("\n");
    return error_count;
}
