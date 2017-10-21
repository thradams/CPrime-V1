#include "config.h"

void free(void*);

typedef char * _auto String;

struct Item
{
    int  * _auto i;
};


void Item_Destroy(struct Item* p) _default
{
    free((void*)p->i);
}

void Item_Delete(struct Item* p) _default
{
    if (p)
    {
        Item_Destroy(p);
        free((void*)p);
    }
}


struct Items
{
    struct Item * _auto * _auto _size(Size) pData;
    int Size;
    int Capacity;
};

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
    return 0;
}
