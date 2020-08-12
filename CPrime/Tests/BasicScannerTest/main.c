
#include "..\..\BasicScanner.h"


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

void BasicScanner_Test1(void)
{
    struct BasicScanner scanner;

    BasicScanner_Init(&scanner, "name", "#if 1", BasicScannerType_Token);
    scanner.m_Token = TK_PRE_IF;

    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_PRE_IF));

    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));

    BasicScanner_Destroy(&scanner);
}

void BasicScanner_Test2(void)
{
    struct BasicScanner scanner;
    BasicScanner_Init(&scanner, "name", "123\r\n", BasicScannerType_File);

    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_DECIMAL_INTEGER));
    TEST(BasicScanner_MatchToken(&scanner, TK_BREAKLINE));
    TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
    BasicScanner_Destroy(&scanner);
}

void BasicScanner_Test3(void)
{
    struct BasicScanner scanner;
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

void BasicScanner_Test4(void)
{
    struct BasicScanner scanner;

    BasicScanner_Init(&scanner, "name", "//comment", BasicScannerType_File);
    TEST(BasicScanner_MatchToken(&scanner, TK_BOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_LINE_COMMENT));
    TEST(BasicScanner_MatchToken(&scanner, TK_FILE_EOF));
    TEST(BasicScanner_MatchToken(&scanner, TK_EOF));
    BasicScanner_Destroy(&scanner);
}

int main()
{
    BasicScanner_Test1();
    BasicScanner_Test2();
    BasicScanner_Test3();
    BasicScanner_Test4();
    //BasicScanner_Test5();

    if (error_count == 0)
    {
        printf("BasicScanner TEST PASSED\n");
    }
    return error_count;
}
