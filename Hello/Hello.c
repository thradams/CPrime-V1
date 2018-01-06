
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

struct Box
{
	int id _defval(3);
};

struct Box* Box_Create();
void Box_Delete(struct Box* pBox);

void Box_Draw(struct Box* pBox)
{
	printf("box draw\n");
}

struct Circle
{
	int id _defval(2);
};

struct Circle* Circle_Create();
void Circle_Delete(struct Circle* pCircle);


void Circle_Draw(struct Circle* pCircle)
{
	printf("circle draw\n");
}

struct _union(Box | Circle) Shape
{
	int id;
};

void Shape_Delete(struct Shape* pShape);
void Shape_Draw(struct Shape* pShape);

struct Items
{
	struct Shape * _auto * _auto _size(Size) data;
	int Size;
	int Capacity;
};

void Items_Reserve(struct Items* pItems, int n);
void Items_PushBack(struct Items* pItems, struct Shape* pShape);
void Items_Destroy(struct Items* p);

int main()
{
	struct Items items = { 0 };

	Items_PushBack(&items, Box_Create());
	Items_PushBack(&items, Circle_Create());

	for (int i = 0; i < items.Size; i++)
	{
		Shape_Draw(items.data[i]);
	}

	Items_Destroy(&items);
}


#pragma region implementation

struct Box* Box_Create() _default
{
    struct Box* p = (struct Box*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->id = 3;
    }
    return p;
}
void Box_Delete(struct Box* pBox) _default
{
    if (pBox != NULL)
    {
        free((void*)pBox);
    }
}

struct Circle* Circle_Create() _default
{
    struct Circle* p = (struct Circle*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->id = 2;
    }
    return p;
}

void Circle_Delete(struct Circle* pCircle) _default
{
    if (pCircle != NULL)
    {
        free((void*)pCircle);
    }
}

void Shape_Delete(struct Shape* pShape) _default
{
    if (pShape != NULL)
    {
            switch (pShape->id)
            {
                case 2:
                    Circle_Delete((struct Circle*)pShape);
                break;
                case 3:
                    Box_Delete((struct Box*)pShape);
                break;
                default:
                break;
            }
    }
}
void Shape_Draw(struct Shape* pShape) _default
{
    switch (pShape->id)
    {
        case 2:
            Circle_Draw((struct Circle*)pShape);
        break;
        case 3:
            Box_Draw((struct Box*)pShape);
        break;
        default:
        break;
    }
}

void Items_Reserve(struct Items* pItems, int n) _default
{
    if (n > pItems->Capacity)
    {
        struct Shape** pnew = pItems->data;
        pnew = (struct Shape**)realloc(pnew, n * sizeof(struct Shape*));
        if (pnew)
        {
            pItems->data = pnew;
            pItems->Capacity = n;
        }
    }
}
void Items_PushBack(struct Items* pItems, struct Shape* pShape) _default
{
    if (pItems->Size + 1 > pItems->Capacity)
    {
        int n = pItems->Capacity * 2;
        if (n == 0)
        {
            n = 1;
        }
        Items_Reserve(pItems, n);
    }
    pItems->data[pItems->Size] = pShape;
    pItems->Size++;
}
void Items_Destroy(struct Items* p) _default
{
    for (int i = 0; i < p->Size; i++)
    {
        Shape_Delete(p->data[i]);
    }
    free((void*)p->data);
}
#pragma endregion 
