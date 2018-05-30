
struct Item
{
	int i;
};


Item* Item_Create() default;
void Item_Delete(Item* p) default;

struct Items
{
	Item * auto * auto sizeof(Size) pData;
	int Size;
	int Capacity;
};


void Items_PushBack(Items* pItems, Item* pItem) default;
void Items_Destroy(Items* pItems) default;


int main(int argc, char **argv)
{
	Items items = {};

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

