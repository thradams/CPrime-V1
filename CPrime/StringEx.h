
#pragma once
#pragma source

#include "Mem.h"

#include <string.h>
typedef char String;



String* StrDup(const char* p);

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
