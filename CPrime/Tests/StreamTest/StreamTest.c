#include "..\..\Stream.h"

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

void Stream_Test1(void)
{
    struct Stream stream;
    Stream_Init(&stream, "name", "123");
    TEST(Stream_MatchChar(&stream, L'1'));
    TEST(Stream_LookAhead(&stream) == '3');
    TEST(Stream_MatchChar(&stream, L'2'));
    TEST(Stream_MatchChar(&stream, L'3'));
    TEST(Stream_MatchChar(&stream, L'\0'));
    TEST(Stream_MatchChar(&stream, L'\0'));
    Stream_Destroy(&stream);
}


int main()
{
    Stream_Test1(); 
    return error_count;
}

