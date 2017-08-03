#include <stdio.h>
#include <stdlib.h>
//typedef struct X X;
typedef enum E
{
    A
} E;

typedef struct X
{
    E e;
    int i;
} X;

X* X_Create();
void X_Delete(X* pX);

typedef struct Array(X*_auto) {X**pData; int Size, Capacity;}  Items;
int  Items_Reserve(Items* pItems, int newSize);
void Items_Destroy(Items* pItems);
void Items_Add(Items* pItems, X* pX);

int main()
{
    Items items = _default{NULL, 0, 0};
    
    Items_Add(&items, X_Create());
    for (int i = 0; i < items.Size; i++)
    {
        //items.pData[i]->e
    }
    Items_Destroy(&items);
    return 1;
}
 
#pragma region instatiations


X* X_Create() _default
{
    X *p = (X*) malloc(sizeof * p);
    if (p != NULL) {
        p->e = 0;
        p->i = 0;
    }
    return p;
}
void X_Delete(X* pX) _default
{
    if (pX != NULL) {
        free(pX);
    }
}


int  Items_Reserve(Items* pItems, int newSize) _default
{
    int iResult = 0;
    if (newSize > pItems->Capacity)
    {
        X** pNew = pItems->pData;
        pNew = (X**)realloc(pNew, newSize * sizeof(X*));
        if (pNew != NULL)
        {
            pItems->pData = pNew;
            pItems->Capacity = newSize;
            iResult = newSize;
        }
    }
    return iResult;
}
void Items_Destroy(Items* pItems) _default
{
    for (int i = 0 ; i < pItems->Size; i++)
    {
        X_Delete(pItems->pData[i]);
    }
    free(pItems->pData);
}
void Items_Add(Items* pItems, X* pX) _default
{
    if (Items_Reserve(pItems, pItems->Size + 1) > 0)
    {
        pItems->pData[pItems->Size] = pX;
        pItems->Size++;
    }
}

#pragma endregion
