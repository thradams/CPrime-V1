
struct Item
{
	int i;
	struct Item* /*@auto*/ pNext;
};

void Item_Delete(struct Item* pItem) /*@default*/
{
    if (pItem)
    {
        Item_Delete(pItem->pNext);
        free((void*)pItem);
    }
}

struct Items
{
	struct Item* /*@auto*/ pHead, *pTail;
};

void Items_Destroy(struct Items* pItems) /*@default*/
{
    Item_Delete(pItems->pHead);
}

void Items_PushBack(struct Items* pItems, struct Item* pItem) /*@default*/
{
    if (pItems->pHead == 0)
    {
        pItems->pHead = pItem;
    }
    else
    {
        pItems->pTail->pNext = pItem;
    }
    pItems->pTail = pItem; 
}
