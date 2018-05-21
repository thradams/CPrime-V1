
#pragma once

#include <stdbool.h>
#include "config.h"
#include "Result.h"
#include "StringEx.h"


typedef char * String;
#define STRING_INIT NULL

void String_Init(String* s);


void   String_Destroy(String* pString);
void   String_Reset(String* pString);
void   String_Attach(String* pString, char* psz);
void   String_Swap(String* pA, String* pB);

int IsEmptyStr(const char*  psz);


#ifdef SEARCH_LEAKS
#include <crtdbg.h>

#define String_Set(pS1, psz100) \
do {\
  const char* psz1 = psz100;\
  _free_dbg(*(pS1), _CLIENT_BLOCK);\
   int len = 0;\
   if (psz1)\
    len = strlen(psz1);\
  if (len > 0)\
  {\
    int len = strlen(psz1);\
    *(pS1) = _malloc_dbg(sizeof(char) * len + 1, _CLIENT_BLOCK, __FILE__, __LINE__);\
    memcpy(*(pS1), psz1, len);\
    (*(pS1))[len] = 0;\
  }\
  else\
  {\
    *(pS1) = 0;\
  }\
} while (0)

#define String_InitWith(pS1, psz100) \
do {\
  const char* psz1 = psz100;\
 int len = 0;\
   if (psz1)\
    len = strlen(psz1);\
  if (len > 0)\
  {\
    int len = strlen(psz1);\
    *(pS1) = _malloc_dbg(sizeof(char) * len + 1, _CLIENT_BLOCK, __FILE__, __LINE__);\
    memcpy(*(pS1), psz1, len);\
    (*(pS1))[len] = 0; \
  }\
  else\
  {\
    *(pS1) = 0;\
  }\
} while (0)
#else
Result String_InitWith(String* pString, const char* source);
Result String_Set(String *pS1, const char* psz1);
#endif
