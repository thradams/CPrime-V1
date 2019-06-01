#include "Array.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "StringEx.h"
#include "Mem.h"


void StrArray_Init(struct StrArray* p) /*@default*/
{
    p->pItems = NULL;
    p->size = 0;
    p->capacity = 0;
}

void StrArray_Push(struct StrArray* p,  const char* text)
{
    text = StrDup(text);
    if (p->size + 1 > p->capacity)
    {
        int n = p->capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        const char** pnew = p->pItems;
        pnew = (const char**)realloc((char**)pnew, n * sizeof(const char*));
        if (pnew)
        {
            p->pItems = pnew;
            p->capacity = n;
        }
    }
    p->pItems[p->size] = text;
    p->size++;
}

void StrArray_Destroy(struct StrArray* p) /*@default*/
{
    for (int i = 0; i < p->size; i++)
    {
        Free((void*)p->pItems[i]);
    }
    Free((void*)p->pItems);
}

void StrArray_Swap(struct StrArray* p1, struct StrArray* p2)
{
    struct StrArray temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}





