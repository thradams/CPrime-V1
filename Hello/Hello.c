#include "config.h"
typedef char * _auto String;

void String_Destroy(String* p) 
{
    free(*p);
}

//void String_Copy(String* p)
//{
  //  free(*p);
//}
typedef struct

{
    String*_auto _size(Size) pData;
    int Size;
    int Capacity;
} StrArray;

void StrArray_Init(StrArray* p, int n) _default
{
    p->pData = 0;
    p->Size = 0;
    p->Capacity = 0;
}

void StrArray_Reserve(StrArray* p, int n) _default
{
    if (n > p->Capacity)
    {
        String* pnew = p->pData;
        pnew = (String*)realloc(pnew, n * sizeof(String));
        if (pnew)
        {
            p->pData = pnew;
            p->Capacity = n;
        }
    }
}

void StrArray_PushBack(StrArray* p, const char* psz) 
{
    if (p->Size + 1 > p->Capacity)
    {
        int n = p->Capacity * 2;
        if (n == 0)
        {
          n = 1;
        }
        StrArray_Reserve(p, n);
    }
    String_Set(&p->pData[p->Size], psz);
    p->Size++;
}


void StrArray_Destroy(StrArray* p) _default
{
    for (int i = 0; i < p->Size; i++)
    {
        String_Destroy(p->pData[i]);
    }
    free((void*)p->pData);
}