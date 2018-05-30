
struct Item
{
	int i;
	Item* auto pNext;
};

void Item_Delete(Item* pItem) default;

struct Items
{
	Item* auto pHead, *pTail;
};

void Items_Destroy(Items* pItems) default;

void Items_PushBack(Items* pItems, Item* pItem) default;
