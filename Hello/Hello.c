#include "config.h"
#include <stdlib.h>
#include <stdio.h>

struct Item
{
    int  i;
};


struct Item* Item_Create() _default
{
    struct Item* p = (struct Item*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->i = 0;
    }
    return p;
}

void Item_Delete(struct Item* p) _default
{
    if (p != NULL)
    {
        free((void*)p);
    }
}


struct Items
{
    struct Item * _auto * _auto _size(Size) pData;
    int Size;
    int Capacity;
};

void Items_Reserve(struct Items* pItems, int n) _default
{
    if (n > pItems->Capacity)
    {
        struct Item** pnew = pItems->pData;
        pnew = (struct Item**)realloc(pnew, n * sizeof(struct Item*));
        if (pnew)
        {
            pItems->pData = pnew;
            pItems->Capacity = n;
        }
    }
}



void Items_PushBack(struct Items* pItems, struct Item* pItem) _default
{
    if (pItems->Size + 1 > pItems->Capacity)
    {
        int n = pItems->Capacity * 2;
        if (n == 0)
        {
          n = 1;
        }
        Items_Reserve(pItems, n);
    }
    pItems->pData[pItems->Size] = pItem;
    pItems->Size++;
}

void Items_Destroy(struct Items* pItems) _default
{
    for (int i = 0; i < pItems->Size; i++)
    {
        Item_Delete(pItems->pData[i]);
    }
    free((void*)pItems->pData);
}


int main(int argc, char **argv)
{
    struct Items items = { 0 };

    for (int i = 0; i < 10; i++)
    {
        Items_PushBack(&items, Item_Create());
        printf("%d %d\n", items.Size, items.Capacity);
    }

    
    for (int i = 0; i < items.Size; i++)
    {
        printf("%d \n", items.pData[i]->i);
    }

    Items_Destroy(&items);
    return 0;
}
