

#pragma once
#pragma source

#include <string.h>
#include <stdarg.h>
#include <wchar.h>

#include <stdbool.h>

typedef struct
{
    char* c_str;
    int size;
    int capacity;

} StrBuilder;

#define STRBUILDER_INIT { 0, 0, 0 }
#define STRBUILDER_DEFAULT_SIZE 17

void StrBuilder_Init(StrBuilder* p);

bool StrBuilder_Reserve(StrBuilder* p, int nelements);

void StrBuilder_Attach(StrBuilder* wstr,
                       char* psz,
                       int nBytes);

void StrBuilder_Destroy(StrBuilder* wstr);
void StrBuilder_Swap(StrBuilder* str1, StrBuilder* str2);


void StrBuilder_Clear(StrBuilder* wstr);

bool StrBuilder_SetN(StrBuilder* p,
                     const char* source,
                     int nelements);

bool StrBuilder_Set(StrBuilder* p,
                    const char* source);

bool StrBuilder_AppendN(StrBuilder* p,
                        const char* source,
                        int nelements);

bool StrBuilder_Append(StrBuilder* p,
                       const char* source);

char* StrBuilder_Release(StrBuilder* p);


void StrBuilder_AppendFmt(StrBuilder* p, const char* fmt, ...);
void StrBuilder_AppendFmtIdent(StrBuilder* p, int nspaces, const char* fmt, ...);

bool StrBuilder_AppendWChar(StrBuilder* p, wchar_t wch);
bool StrBuilder_AppendW(StrBuilder* p, const wchar_t* psz);
bool StrBuilder_AppendChar(StrBuilder* p, char wch);
void StrBuilder_Trim(StrBuilder* p);
bool StrBuilder_AppendUpper(StrBuilder* p, const char* s);

bool StrBuilder_AppendIdent(StrBuilder* p,
                            int nspaces,
                            const char* source);


void StrBuilder_AppendFmtLn(StrBuilder* p,
                            int nspaces,
                            const char* fmt,
                            ...);
void StrBuilder_AppendFmtV(StrBuilder* p, const char* fmt, va_list va);
