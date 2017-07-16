

#pragma once

#include <string.h>
#include "Result.h"

typedef struct
{
    char*  c_str;
    size_t size;
    size_t capacity;

} StrBuilder;

#define STRBUILDER_INIT { 0, 0, 0 }
#define STRBUILDER_DEFAULT_SIZE 17

Result StrBuilder_Init(StrBuilder* p, size_t capacity);

Result StrBuilder_Reserve(StrBuilder* p, size_t nelements);

void StrBuilder_Attach(StrBuilder* wstr,
                       char* psz,
                       size_t nBytes);

void StrBuilder_Destroy(StrBuilder* wstr);
void StrBuilder_Swap(StrBuilder* str1, StrBuilder* str2);


void StrBuilder_Clear(StrBuilder* wstr);

Result StrBuilder_SetN(StrBuilder* p,
                       const char* source,
                       size_t nelements);

Result StrBuilder_Set(StrBuilder* p,
                      const char* source);

Result StrBuilder_AppendN(StrBuilder* p,
                          const char* source,
                          size_t nelements);

Result StrBuilder_Append(StrBuilder* p,
                         const char* source);

char* StrBuilder_Release(StrBuilder* p);

Result StrBuilder_AppendInt(StrBuilder * p, int i);


Result StrBuilder_AppendWChar(StrBuilder * p, wchar_t wch);
Result StrBuilder_AppendW(StrBuilder * p, const wchar_t* psz);
Result StrBuilder_AppendChar(StrBuilder * p, char wch);
void StrBuilder_Trim(StrBuilder* p);
Result StrBuilder_AppendUpper(StrBuilder *p, const char* s);