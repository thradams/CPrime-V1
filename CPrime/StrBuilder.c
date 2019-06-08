

#include "StrBuilder.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>

#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>
#include <ctype.h>

#ifdef USE_UTF8
#include  "Utf8.h"
#endif
#include "StringEx.h"

#include "Mem.h"

void StrBuilder_Init(struct StrBuilder* p) /*@default*/
{
    p->c_str = NULL;
    p->size = 0;
    p->capacity = 0;
}

void StrBuilder_Swap(struct StrBuilder* str1,
                     struct StrBuilder* str2)
{
    struct StrBuilder temp_Moved = *str1;
    *str1 = *str2;
    *str2 = temp_Moved;
}

void StrBuilder_Destroy(struct StrBuilder* p)
{
    if (p)
    {
        Free(p->c_str);
        p->c_str = NULL;
        p->size = 0;
        p->capacity = 0;
    }
}

bool StrBuilder_Reserve(struct StrBuilder* p, int nelements)
{
    bool r = true;

    if (nelements > p->capacity)
    {
        char* pnew = (char*)Realloc(p->c_str,
            (nelements + 1) * sizeof(p->c_str[0]));

        if (pnew)
        {
            if (p->c_str == NULL)
            {
                pnew[0] = '\0';
            }

            p->c_str = pnew;
            p->capacity = nelements;
        }

        else
        {
            r = false /*nomem*/;
        }
    }

    return r;
}

static bool StrBuilder_Grow(struct StrBuilder* p, int nelements)
{
    bool r = true;

    if (nelements > p->capacity)
    {
        int new_nelements = p->capacity + p->capacity / 2;

        if (new_nelements < nelements)
        {
            new_nelements = nelements;
        }

        r = StrBuilder_Reserve(p, new_nelements);
    }

    return r;
}

bool StrBuilder_SetN(struct StrBuilder* p,
                     const char* source,
                     int nelements)
{
    bool r = StrBuilder_Grow(p, nelements);

    if (r)
    {
        strncpy(p->c_str, /*p->capacity + 1,*/ source, nelements);
        p->c_str[nelements] = '\0';
        p->size = nelements;
    }

    return r;
}

bool StrBuilder_Set(struct StrBuilder* p,
                    const char* source)
{
    bool r = true;
    if (source == NULL)
    {
        StrBuilder_Clear(p);
    }
    else
    {
        int n = (int)strlen(source);
        StrBuilder_Clear(p);

        if (n > 0)
        {
            r = StrBuilder_SetN(p, source, (int)strlen(source));
        }
    }
    return r;
}

bool StrBuilder_AppendN(struct StrBuilder* p,
                        const char* source,
                        int nelements)
{
    if (source == NULL || source[0] == '\0')
    {
        return true;
    }

    bool r = StrBuilder_Grow(p, p->size + nelements);

    if (r == true)
    {
        strncpy(p->c_str + p->size,
                /*(p->capacity + 1) - p->size,*/
                source,
                nelements);
        p->c_str[p->size + nelements] = '\0';
        p->size += nelements;
    }

    return r;
}

bool StrBuilder_AppendIdent(struct StrBuilder* p,
                            int nspaces,
                            const char* source)
{
    for (int i = 0; i < nspaces; i++)
    {
        StrBuilder_Append(p, " ");
    }
    return StrBuilder_Append(p, source);
}

bool StrBuilder_Append(struct StrBuilder* p,
                       const char* source)
{
    if (source == NULL || source[0] == '\0')
    {
        return true;
    }

    return StrBuilder_AppendN(p, source, (int)strlen(source));
}

void StrBuilder_Clear(struct StrBuilder* p)
{
    if (p->c_str != NULL)
    {
        p->c_str[0] = '\0';
        p->size = 0;
    }
}

char* StrBuilder_Release(struct StrBuilder* p)
{
    char* pResult = p->c_str;

    if (pResult != NULL)
    {
        p->c_str = NULL;
        p->size = 0;
        p->capacity = 0;
    }

    return pResult;
}


void StrBuilder_Attach(struct StrBuilder* pStrBuilder,
                       char* psz,
                       int nBytes)
{
    if (psz != NULL)
    {
        //assert(nBytes > 0);
        StrBuilder_Destroy(pStrBuilder);
        pStrBuilder->c_str = psz;
        pStrBuilder->capacity = nBytes - 1;
        pStrBuilder->size = 0;
        pStrBuilder->c_str[0] = '\0';
    }
}

bool StrBuilder_AppendWChar(struct StrBuilder* p, wchar_t wch)
{
#ifdef USE_UTF8
    char buffer[5] = {0};
    int nbytes = EncodeCharToUTF8Bytes(wch, buffer);
    return StrBuilder_AppendN(p, buffer, nbytes);
#else
    char ch = (char)wch;
    return StrBuilder_AppendN(p, &ch, 1);
#endif
}


bool StrBuilder_AppendChar(struct StrBuilder* p, char ch)
{
    return StrBuilder_AppendN(p, &ch, 1);
}

bool StrBuilder_AppendW(struct StrBuilder* p, const wchar_t* psz)
{
    bool result = false;

    while (*psz)
    {
        result = StrBuilder_AppendWChar(p, *psz);

        if (result != true)
        {
            break;
        }

        psz++;
    }

    return result;
}


void StrBuilder_Trim(struct StrBuilder* p)
{
    struct StrBuilder temp;
    StrBuilder_Init(&temp);

    StrBuilder_Reserve(&temp, p->size);

    bool bCopy = false;

    for (int i = 0; i < p->size; i++)
    {
        char ch = p->c_str[i];

        if (!bCopy && ch != ' ')
        {
            //a partir de agora copia
            bCopy = true;
        }

        if (bCopy)
            StrBuilder_AppendChar(&temp, ch);
    }

    //indice do ultimo que nao eh espaco
    int k = ((int)(temp.size)) - 1;

    for (; k >= 0; k--)
    {
        char ch = temp.c_str[k];

        if (ch != ' ')
        {
            break;
        }
    }

    temp.c_str[k + 1] = '\0';
    temp.size = k + 1;
    StrBuilder_Swap(&temp, p);
    StrBuilder_Destroy(&temp);
}



bool StrBuilder_AppendUpper(struct StrBuilder* p, const char* s)
{
    if (s != NULL)
    {
        while (*s)
        {
            StrBuilder_AppendChar(p, toupper(*s));
            s++;
        }
    }

    return true;
}


void StrBuilder_AppendFmtV(struct StrBuilder* p, const char* fmt, va_list va)
{
    char buffer[500];
    vsnprintf(buffer, 500, fmt, va);
    StrBuilder_Append(p, buffer);
}

void StrBuilder_AppendFmt(struct StrBuilder* p, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char buffer[500];
    vsnprintf(buffer, 500, fmt, args);
    StrBuilder_Append(p, buffer);
    va_end(args);

}

void StrBuilder_AppendFmtIdent(struct StrBuilder* p, int nspaces, const char* fmt, ...)
{
    for (int i = 0; i < nspaces; i++)
    {
        StrBuilder_Append(p, " ");
    }

    va_list args;
    va_start(args, fmt);
    char buffer[500];
    vsnprintf(buffer, 500, fmt, args);
    StrBuilder_Append(p, buffer);
    va_end(args);

}

void StrBuilder_AppendFmtLn(struct StrBuilder* p,
                            int nspaces,
                            const char* fmt,
                            ...)
{
    for (int i = 0; i < nspaces; i++)
    {
        StrBuilder_Append(p, " ");
    }

    va_list args;
    va_start(args, fmt);
    char buffer[500];
    vsnprintf(buffer, 500, fmt, args);
    StrBuilder_Append(p, buffer);
    va_end(args);

    StrBuilder_Append(p, "\n");
}


