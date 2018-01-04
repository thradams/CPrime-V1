#include "config.h"
#include <stdio.h>
struct Box
{
	int id;
};

struct Circle
{
	int id;
};

struct _union(Box | Circle) Shape
{
	int id;
};

struct X
{
	struct Shape * _auto pShape;
};

void X_Destroy(struct X* pX) _default
{
	if (pX->pShape != NULL)
	{
		switch (pX->pShape->id)
		{
		case Circle_ID:
			Circle_Destroy((struct Circle*)pX->pShape);
			break;
		case Box_ID:
			Box_Destroy((struct Box*)pX->pShape);
			break;
		default:
			break;
		}
		free((void*)pX->pShape);
	}
}

int main()
{
}