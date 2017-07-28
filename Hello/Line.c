
#include "Line.h"
#include <stdlib.h>

void Lines_Init(Lines* pLines) _default
{
    pLines->pData = NULL;
    pLines->Size = 0;
    pLines->Capacity = 0;

}

static void Line_Init(Line* p) _default
{
    p->start.x = 1;
    p->start.y = 0;
    p->end.x = 1;
    p->end.y = 0;
}

Line* Line_Create() _default
{
    Line *p = (Line*) malloc(sizeof * p);
    if (p != NULL) {
        Line_Init(p);
    }
    return p;
}
void Line_Delete(Line* p) _default
{
    if (p != NULL) {
        free(p);
    }
}
void Lines_Destroy(Lines* pLines) _default
{
    for (int i = 0 ; i < pLines->Size; i++)
    {
        Line_Delete(pLines->pData[i]);
    }
    free(pLines->pData);
}
void Lines_Add(Lines* pLines, Line* pLine) _default
{
    if (pLines->Size + 1 > pLines->Capacity)
     {
        int new_nelements = pLines->Capacity + pLines->Capacity / 2;

        if (new_nelements < 1)
        {
            new_nelements = 1;
        }
        void** pnew = (void**) pLines->pData;
        pnew = (void**)realloc(pnew, new_nelements * sizeof(void*));
        if (pnew)
        {
            pLines->pData = (Line**)pnew;
            pLines->Capacity = new_nelements;
        }
    }
    pLines->pData[pLines->Size] = pLine;
    pLines->Size++;
}