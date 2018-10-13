#pragma once

struct Item
{
	int i;
};



struct Items
{
	struct Item * /*auto*/ * /*auto [Size]*/ pData;
	int Size;
	int Capacity;
};
