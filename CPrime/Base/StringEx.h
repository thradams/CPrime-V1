
#pragma once

#include <stdbool.h>
#include "config.h"
#include "Result.h"
#include "StringEx.h"

typedef char * String;
#define STRING_INIT NULL
inline void String_Init(String* s) { *s = NULL; }

Result String_InitWith(String* pString, const char* source);
void   String_Destroy(String* pString);
void   String_Reset(String* pString);
void   String_Attach(String* pString, char* psz);
void   String_Swap(String* pA, String* pB);

Result String_Set(String *pS1, const char* psz1);

int IsEmptyStr(const char*  psz);



