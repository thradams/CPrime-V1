

#pragma once
#pragma source

#include <string.h>
#include <stdarg.h>
#include <wchar.h>

#include <stdbool.h>

struct StrBuilder
{
    char* c_str;
    int size;
    int capacity;
};

#define STRBUILDER_INIT { 0, 0, 0 }
#define STRBUILDER_DEFAULT_SIZE 17

void StrBuilder_Init(struct StrBuilder* p);

bool StrBuilder_Reserve(struct StrBuilder* p, int nelements);

void StrBuilder_Attach(struct StrBuilder* wstr,
                       char* psz,
                       int nBytes);

void StrBuilder_Destroy(struct StrBuilder* wstr);
void StrBuilder_Swap(struct StrBuilder* str1, struct StrBuilder* str2);


void StrBuilder_Clear(struct StrBuilder* wstr);

bool StrBuilder_SetN(struct StrBuilder* p,
                     const char* source,
                     int nelements);

bool StrBuilder_Set(struct StrBuilder* p,
                    const char* source);

bool StrBuilder_AppendN(struct StrBuilder* p,
                        const char* source,
                        int nelements);

bool StrBuilder_Append(struct StrBuilder* p,
                       const char* source);

char* StrBuilder_Release(struct StrBuilder* p);


void StrBuilder_AppendFmt(struct StrBuilder* p, const char* fmt, ...);
void StrBuilder_AppendFmtIdent(struct StrBuilder* p, int nspaces, const char* fmt, ...);

bool StrBuilder_AppendWChar(struct StrBuilder* p, wchar_t wch);
bool StrBuilder_AppendW(struct StrBuilder* p, const wchar_t* psz);
bool StrBuilder_AppendChar(struct StrBuilder* p, char wch);
void StrBuilder_Trim(struct StrBuilder* p);
bool StrBuilder_AppendUpper(struct StrBuilder* p, const char* s);

bool StrBuilder_AppendIdent(struct StrBuilder* p,
                            int nspaces,
                            const char* source);


void StrBuilder_AppendFmtLn(struct StrBuilder* p,
                            int nspaces,
                            const char* fmt,
                            ...);
void StrBuilder_AppendFmtV(struct StrBuilder* p, const char* fmt, va_list va);
