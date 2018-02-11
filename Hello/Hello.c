#include "config.h"
#include <stdio.h>

struct Shape;

struct Box
{
  int i _defval(1);
  struct Shape* _auto pNext;
};

struct Box* Box_Create() _default
{
    struct Box* p = (struct Box*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->i = 1;
        p->pNext = NULL;
    }
    return p;
}
void Box_Delete(struct Box* pBox) -_default;
struct Circle
{
  int i _defval(2);
  struct Shape* _auto  pNext;
};

struct _union(Box | Circle)  Shape
{
  int id;
  struct Shape* _auto  pNext;
} Shape ;
 
#pragma region cprime Shape
inline struct Circle* Shape_As_Circle(struct Shape* p) { return p->id == 2 ? (struct Circle*) p : 0;}
inline struct Shape* Circle_As_Shape(struct Circle* p) { return (struct Shape*) p; }
inline struct Box* Shape_As_Box(struct Shape* p) { return p->id == 1 ? (struct Box*) p : 0;}
inline struct Shape* Box_As_Shape(struct Box* p) { return (struct Shape*) p; }
#pragma endregion cprime




void Shape_Delete(struct Shape* pShape) _default
{
    if (pShape != NULL)
    {
            switch (pShape->id)
            {
                case 2:
                    Circle_Delete((struct Circle*)pShape);
                break;
                case 1:
                    Box_Delete((struct Box*)pShape);
                break;
                default:
                break;
            }
    }
}






struct Items
{
	struct Shape * _auto pHead;	
	struct Shape * pTail;
};

void Items_Destroy(struct Items* pItems) _default
{
    Shape_Delete(pItems->pHead);
}

void Items_PushBack(struct Items* pItems, struct Shape* pItem) _default
{
    if (pItems->pHead == NULL)
    {
        pItems->pHead = pItem;
    }
    else
    {
        pItems->pTail->pNext = pItem;
    }
    pItems->pTail = pItem; 
}


int main()
{
	struct Items items = { 0 };
	Items_PushBack(&items, (struct Shape*)Box_Create());
	Items_PushBack(&items, (struct Shape*)Box_Create());
	Items_Destroy(&items);
}
























