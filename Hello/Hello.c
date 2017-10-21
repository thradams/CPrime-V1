#include "config.h"

#include <stdlib.h>
#include <stdbool.h>



struct Item
{
    int i;
};

struct Items
{
    int* pData;
    int Size;
    int Capacity;
};



void Items_Reserve(struct Items* pItems, int n) _default
{
    if (n > pItems->Capacity)
    {
        int* pnew = pItems->pData;
        pnew = (int*)realloc(pnew, n * sizeof(int));
        if (pnew)
        {
            pItems->pData = pnew;
            pItems->Capacity = n;
        }
    }
}

void Items_PushBack(struct Items* pItems, int v) _default
{
    if (pItems->Size + 1 > pItems->Capacity)
    {
        Items_Reserve(pItems, pItems->Size + 1);
    }
    pItems->pData[pItems->Size] = v;
    pItems->Size++;
}

int main(int argc, char **argv)
{
    struct Items items = _default {0};
    Items_PushBack(&items, 1);
    return 0;
}
