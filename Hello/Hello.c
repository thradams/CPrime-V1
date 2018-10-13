
#include "config.h"

struct Item* Item_Create() /*default*/
{
    struct Item* p = (struct Item*) malloc(sizeof * p);
    if (p)
    {
        p->i = 0;
    }
    return p;
}
void Item_Delete(struct Item* p) /*default*/
{
    if (p)
    {
        free((void*)p);
    }
}


void Items_Destroy(struct Items *p) /*default*/
{
    for (int i = 0; i < p->Size; i++)
    {
        Item_Delete(p->pData[i]);
    }
    free((void*)p->pData);
}


