
#pragma once
#pragma source

#include "Mem.h"

#include <string.h>
#include <stdbool.h>

typedef char String;



String * StrDup(const char * p);
int StrIComp(char const* a, char const* b);
char* StrIStr(const char* str1, const char* str2);
bool IsSuffix(const char * s, const char * suffix);

#define PTR_STRING_REPLACE(a, b)\
do\
{\
  Free(a);\
  if (b)\
  {\
   a = Malloc(strlen(b) + 1);\
   if (a)\
    strcpy(a, b);\
  }\
  else\
  {\
    a = 0;\
  }\
} while (0)


#define PTR_SWAP(a, b)\
do\
{\
  void* t = (a);\
  (a) = (b);\
  (b) = t;\
} while (0)

