
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LocalStrBuilder.h"
#include "Mem.h"

void LocalStrBuilder_Init(struct LocalStrBuilder * p)
{
    p->capacity = LOCALSTRBUILDER_NCHARS;
    p->size = 0;
    p->c_str = p->chars;
}

void LocalStrBuilder_Swap(struct LocalStrBuilder * pA, struct LocalStrBuilder * pB)
{
    int bA = (pA->c_str == pA->chars);
    int bB = (pB->c_str == pB->chars);

    struct LocalStrBuilder temp = *pA;
    *pA = *pB;
    *pB = temp;

    if (bA)
    {
        pB->c_str = pB->chars;
    }
    if (bB)
    {
        pA->c_str = pA->chars;
    }
}

void LocalStrBuilder_Destroy(struct LocalStrBuilder * p)
{
    if (p->c_str != p->chars)
    {
        Free(p->c_str);
    }
}

void LocalStrBuilder_Reserve(struct LocalStrBuilder * p, int nelements)
{
    if (nelements > p->capacity)
    {
        char * pnew = NULL;
        if (nelements <= LOCALSTRBUILDER_NCHARS)
        {
            pnew = p->chars;
            p->capacity = LOCALSTRBUILDER_NCHARS;
            p->c_str = pnew;
        }
        else
        {
            if (p->capacity <= LOCALSTRBUILDER_NCHARS)
            {
                pnew = (char *)Malloc((nelements + 1) * sizeof(char));
                memcpy(pnew, p->chars, LOCALSTRBUILDER_NCHARS);
            }
            else
            {
                pnew = (char *)Realloc(p->c_str, (nelements + 1) * sizeof(char));
            }

            p->c_str = pnew;

            if (p->size == 0)
            {
                pnew[0] = '\0';
            }
            p->capacity = nelements;
        }
    }
}

void LocalStrBuilder_Print(struct LocalStrBuilder * p)
{
    printf("size = %d, capacity = %d, c_str = '%s', internal buffer = %s \n",
        (int)p->size,
           (int)p->capacity,
           p->c_str,
           (p->c_str == p->chars ? "yes" : "no"));
}

void LocalStrBuilder_Clear(struct LocalStrBuilder * p)
{
    if (p->c_str)
    {
        p->c_str[0] = 0;
    }
    p->size = 0;
}

void LocalStrBuilder_Grow(struct LocalStrBuilder * p, int nelements)
{
    if (nelements > p->capacity)
    {
        int new_nelements = p->capacity + p->capacity / 2;

        if (new_nelements < nelements)
        {
            new_nelements = nelements;
        }

        LocalStrBuilder_Reserve(p, new_nelements);
    }
}

void LocalStrBuilder_Append(struct LocalStrBuilder * p, const char * source)
{
    while (*source)
    {
        LocalStrBuilder_AppendChar(p, *source);
        source++;
    }
}


void LocalStrBuilder_Set(struct LocalStrBuilder * p, const char * source)
{
    LocalStrBuilder_Clear(p);
    while (*source)
    {
        LocalStrBuilder_AppendChar(p, *source);
        source++;
    }
}



void LocalStrBuilder_AppendChar(struct LocalStrBuilder * p, char ch)
{
    LocalStrBuilder_Grow(p, p->size + 1);

    p->c_str[p->size] = ch;
    p->c_str[p->size + 1] = 0;
    p->size++;
}

