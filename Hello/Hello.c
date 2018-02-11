#include "config.h"


struct Box
{
  int i _defval(1);
};

struct Box* Box_Create() _default
{
    struct Box* p = (struct Box*) malloc(sizeof * p);
    if (p)
    {
        p->i = 1;
    }
    return p;
}

struct Circle
{
  int i _defval(2);
};

struct _union(Box | Circle)  Shape
{
  int id;
} Shape ;
 
#pragma region cprime Shape
inline struct Circle* Shape_As_Circle(struct Shape* p) { return p->id == 2 ? (struct Circle*) p : 0;}
inline struct Shape* Circle_As_Shape(struct Circle* p) { return (struct Shape*) p; }
inline struct Box* Shape_As_Box(struct Shape* p) { return p->id == 1 ? (struct Box*) p : 0;}
inline struct Shape* Box_As_Shape(struct Box* p) { return (struct Shape*) p; }
#pragma endregion cprime







struct Items
{
	struct Shape ** data;
	int Size;
	int Capacity;
};


void Items_PushBack(struct Items* pItems, struct Shape* pItem) _default
{
    if (pItems->Size + 1 > pItems->Capacity)
    {
        int n = pItems->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        struct Shape** pnew = pItems->data;
        pnew = (struct Shape**)realloc(pnew, n * sizeof(struct Shape*));
        if (pnew)
        {
            pItems->data = pnew;
            pItems->Capacity = n;
        }
    }
    pItems->data[pItems->Size] = pItem;
    pItems->Size++;
}


int main()
{
	struct Items items = { 0 };
	Items_PushBack(&items, (struct Shape*)Box_Create());
}
























