#include <stdlib.h>

typedef struct Point
{
    int x _defval(1), y _defval(2);
} Point;

typedef struct
{
    Point start;
    Point end;
    //Point *_auto  pPoint;
} Line;


void Line_Delete(Line* p) _default
{
    if (p != NULL) {
        free(p);
    }

}
Line* Line_Create() _default
{
    Line *p = (Line*) malloc(sizeof * p);
    if (p != NULL) {
            p->start.x = 1;
            p->start.y = 2;
            p->end.x = 1;
            p->end.y = 2;
    }
    return p;

}


typedef struct Array(Line*_auto) {Line**pData; int Size, Capacity;} Lines;

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

void Lines_Destroy(Lines* pLines) _default
{
    for (int i =0 ; i < pLines->Size; i++)
    {
        Line *pCurrent = pLines->pData[i];
        Line_Delete(pCurrent);
    }

}
//
int main()
{
    Lines lines = _default{NULL, 0, 0};
    //
    Lines_Add(&lines, Line_Create());
    Lines_Destroy(&lines);
}