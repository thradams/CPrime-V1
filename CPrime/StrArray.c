#include "StrArray.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "StringEx.h"
#include "Mem.h"


void StrArray_Init(struct StrArray* p) /*@default*/
{
    p->pData = NULL;
    p->Size = 0;
    p->Capacity = 0;
}

void StrArray_PushCore(struct StrArray* p, const char* text) 
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        const char** pnew = p->pData;
        pnew = (const char**)Realloc(pnew, n * sizeof(const char*));
        if (pnew)
        {
            p->pData = pnew;
            p->Capacity = n;
        }
    }
    p->pData[p->Size] = text;
    p->Size++;
}

void StrArray_Push(struct StrArray* p,  const char* text)
{
    text = StrDup(text);
    if (text)
      StrArray_PushCore(p, text);    
}

void StrArray_Destroy(struct StrArray* p) /*@default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        Free((void*)p->pData[i]);
    }
    Free((void*)p->pData);
}

void StrArray_Swap(struct StrArray* p1, struct StrArray* p2)
{
    struct StrArray temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}





