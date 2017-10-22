#include "config.h"

struct Items
{
    int * _auto  pData;
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
        int n = pItems->Capacity * 2;
        if (n == 0)
        {
          n = 1;
        }
        Items_Reserve(pItems, n);
    }
    pItems->pData[pItems->Size] = v;
    pItems->Size++;
}

void Items_Destroy(struct Items* pItems) _default
{
    free((void*)pItems->pData);
}


int main(int argc, char **argv)
{
    struct Items items = { 0 };

    Items_PushBack(&items, 1);
    Items_PushBack(&items, 2);
    Items_PushBack(&items, 3);

    for (int i = 0; i < items.Size; i++)
    {
        printf("%d\n", items.pData[i]);
    }

    Items_Destroy(&items);
    return 0;
}
