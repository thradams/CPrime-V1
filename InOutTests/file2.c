
struct Item
{
	int i;
};


struct Item* Item_Create() /*@default*/
{
    struct Item* p = (struct Item*) malloc(sizeof * p);
    if (p)
    {
        p->i = 0;
    }
    return p;
}
void Item_Delete(struct Item* p) /*@default*/
{
    if (p)
    {
        free((void*)p);
    }
}

struct Items
{
	struct Item * /*@auto*/ * /*@auto*/ /*@size(Size)@*/ pData;
	int Size;
	int Capacity;
};


void Items_PushBack(struct Items* pItems, struct Item* pItem) /*@default*/
{
    if (pItems->Size + 1 > pItems->Capacity)
    {
        int n = pItems->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        struct Item** pnew = pItems->pData;
        pnew = (struct Item**)Realloc(pnew, n * sizeof(struct Item*));
        if (pnew)
        {
            pItems->pData = pnew;
            pItems->Capacity = n;
        }
    }
    pItems->pData[pItems->Size] = pItem;
    pItems->Size++;
}
void Items_Destroy(struct Items* pItems) /*@default*/
{
    for (int i = 0; i < pItems->Size; i++)
    {
        Item_Delete(pItems->pData[i]);
    }
    free((void*)pItems->pData);
}


int main(int argc, char **argv)
{
	struct Items items =/*@default*/ {0};

	Items_PushBack(&items, Item_Create());
	Items_PushBack(&items, Item_Create());
	Items_PushBack(&items, Item_Create());

	for (int i = 0; i < items.Size; i++)
	{
		printf("%d\n", items.pData[i]->i);
	}

	Items_Destroy(&items);
	return 0;
}
