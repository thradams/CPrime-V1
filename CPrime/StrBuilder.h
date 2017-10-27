

#pragma once

#include <string.h>
#include <stdarg.h>
#include <wchar.h>

#include "Result.h"

typedef struct
{
    char*  c_str;
    int size;
    int capacity;

} StrBuilder;

#define STRBUILDER_INIT { 0, 0, 0 }
#define STRBUILDER_DEFAULT_SIZE 17

Result StrBuilder_Init(StrBuilder* p, int capacity);

Result StrBuilder_Reserve(StrBuilder* p, int nelements);

void StrBuilder_Attach(StrBuilder* wstr,
                       char* psz,
                       int nBytes);

void StrBuilder_Destroy(StrBuilder* wstr);
void StrBuilder_Swap(StrBuilder* str1, StrBuilder* str2);


void StrBuilder_Clear(StrBuilder* wstr);

Result StrBuilder_SetN(StrBuilder* p,
                       const char* source,
                       int nelements);

Result StrBuilder_Set(StrBuilder* p,
                      const char* source);

Result StrBuilder_AppendN(StrBuilder* p,
                          const char* source,
                          int nelements);

Result StrBuilder_Append(StrBuilder* p,
                         const char* source);

char* StrBuilder_Release(StrBuilder* p);


void StrBuilder_AppendFmt(StrBuilder * p, const char* fmt, ...);
void StrBuilder_AppendFmtIdent(StrBuilder * p, int nspaces, const char* fmt, ...);

Result StrBuilder_AppendWChar(StrBuilder * p, wchar_t wch);
Result StrBuilder_AppendW(StrBuilder * p, const wchar_t* psz);
Result StrBuilder_AppendChar(StrBuilder * p, char wch);
void StrBuilder_Trim(StrBuilder* p);
Result StrBuilder_AppendUpper(StrBuilder *p, const char* s);

Result StrBuilder_AppendIdent(StrBuilder* p,
	int nspaces,
	const char* source);


void StrBuilder_AppendFmtLn(StrBuilder * p,
    int nspaces,
    const char* fmt,
    ...);
void StrBuilder_AppendFmtV(StrBuilder * p, const char* fmt, va_list va);
