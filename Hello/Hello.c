
struct Item
{
	int  i;
};


struct Items
{
	struct Item * /*@auto*/ * /*@auto*//*@size(Size)@*/    pData;
	int Size;
	int Capacity;
};
