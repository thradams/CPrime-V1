#include  "StringEx.h"
#include <ctype.h>

char* StrDup(const char* p)
{
    char* a = 0;
    if (p)
    {
        a = Malloc(strlen(p) + 1);
        if (a)
            strcpy(a, p);
    }
    else
    {
        a = Malloc(1);
        if (a)
        {
            a[0] = '\0';
        }
    }
    return a;
}

int StrIComp(char const* a, char const* b)
{
    for (;; a++, b++)
    {
        int d = tolower((unsigned char)* a) - tolower((unsigned char)* b);
        if (d != 0 || !*a)
            return d;
    }
}

char* StrIStr(const char* str1, const char* str2)
{
    const char* p1 = str1;
    const char* p2 = str2;
    const char* r = *p2 == 0 ? str1 : 0;

    while (*p1 != 0 && *p2 != 0)
    {
        if (tolower((unsigned char)* p1) == tolower((unsigned char)* p2))
        {
            if (r == 0)
            {
                r = p1;
            }

            p2++;
        }
        else
        {
            p2 = str2;
            if (r != 0)
            {
                p1 = r + 1;
            }

            if (tolower((unsigned char)* p1) == tolower((unsigned char)* p2))
            {
                r = p1;
                p2++;
            }
            else
            {
                r = 0;
            }
        }

        p1++;
    }

    return *p2 == 0 ? (char*)r : 0;
}

bool IsSuffix(const char* s, const char* suffix)
{
    bool bResult = false;
    int len = (int)strlen(s);
    int len2 = (int)strlen(suffix);
    if (len > len2)
    {
        const char* pEndPart = &s[len - len2];
        if (StrIComp(pEndPart, suffix) == 0) //case insensitive
        {
            bResult = true;
        }
    }
    return bResult;

}


