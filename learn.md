# Learn about generated code

## Features

### Static initialization

```c
typedef struct 
{
  int x, y;
} Point;

int main()
{  
  Point pt = _default {}
}

```

```c
typedef struct 
{
  int x = 1;
  int y = 2;
} Point;

int main()
{  
  Point pt = _default {}
}

```
If your struct has only empty initializers the generated code is
default {0}, otherwise the initialization list is expanded for its C89 version.
(designed initializers are considered, but they are less portable)

The default is used to tell the compiler to keep the initialization 
list updated.
 
## Dynamic arrays (like c++ vector)


```c
#include <stdlib.h>
#include <stdio.h>

struct Item
{
    int  i;
};


struct Item* Item_Create() _default
{
    struct Item* p = (struct Item*) malloc(sizeof * p);
    if (p)
    {
        p->i = 0;
    }
    return p;
}

void Item_Delete(struct Item* p) _default
{
    if (p)
    {
        free((void*)p);
    }
}


struct Items
{
    struct Item * _auto * _auto _size(Size) pData;
    int Size;
    int Capacity;
};

void Items_Reserve(struct Items* pItems, int n) _default
{
    if (n > pItems->Capacity)
    {
        struct Item** pnew = pItems->pData;
        pnew = (struct Item**)realloc(pnew, n * sizeof(struct Item*));
        if (pnew)
        {
            pItems->pData = pnew;
            pItems->Capacity = n;
        }
    }
}

void Items_PushBack(struct Items* pItems, struct Item* pItem) _default
{
    if (pItems->Size + 1 > pItems->Capacity)
    {
        Items_Reserve(pItems, pItems->Size + 1);
    }
    pItems->pData[pItems->Size] = pItem;
    pItems->Size++;
}

void Items_Destroy(struct Items* pItems) _default
{
    for (int i = 0; i < pItems->Size; i++)
    {
        Item_Delete(pItems->pData[i]);
    }
    free((void*)pItems->pData);
}


int main(int argc, char **argv)
{
    struct Items items = { 0 };

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

```

## constructor / destructor / create / delete / _auto

The generated functions are based on name patterns X_Init, X_Create, X_Destroy, X_Delete.

Where X can be typedef or struct name.

The auto modifier tells the compiler that the variable is owner
of the pointed object.
Destroying the auto pointer  you also destroy the pointed object and free its memory.

```c

typedef char * _auto String;

struct Person
{
    String Name;
    int age /*= -1*/;
    _Bool b /*= true*/;
};

struct Person* Person_Create();
void Person_Delete(struct Person* person);
 
int main()
{
    struct Person person = _default {0};
    struct Person* pPerson = Person_Create();
    Person_Delete(pPerson);
    return 0;
}

struct Person* Person_Create() _default;

//Remove Destroy and see what happens with Delete
//Create Init and see what happens with Create
//void Person_Init(struct Person* person) _default;
//Remove _auto from String and see what happens

void Person_Destroy(struct Person* person) _default;
void Person_Delete(struct Person* person) _default;
```
Diferent name patterns can be configured in the future.

Other designs have been considered:

```c
void X_init(X* p) _init;
void X_dtor(X* p) _destroy;
or
void X_init(X* p) _cp("init");
void X_destructor(X* p) _cp("destroy");
```

Simple linked list:



```c
struct Node {
	struct Node* _auto pNext;
};

typedef struct
{
        //Note that only pHead is auto. 
	struct Node* _auto pHead, pTail;
} List;

struct Node* Node_Create() _default;
void Node_Delete(struct Node* pNode) _default;
void List_Destroy(List* pList) _default;
```

If you want to compile the generated code in a tradicional C compiler you must
define empty macros _auto, _default.

I use the option /FI from microsoft compiler for this task.
https://msdn.microsoft.com/en-us/library/8c5ztk84.aspx


## auto auto and __size (new)

```c
struct Item
{
    int  i;
};


void Item_Delete(struct Item* p) _default
{
    if (p)
    {
        free((void*)p);
    }
}


struct Items
{
    struct Item * _auto * _auto _size(Size) pData;
    int Size;
    int Capacity;
};

void Items_Destroy(struct Items* pItems) _default
{
    for (int i = 0; i < pItems->Size; i++)
    {
        Item_Delete(pItems->pData[i]);
    }
    free((void*)pItems->pData);
}

```

## Polimorphism

https://www.youtube.com/watch?v=vzouZGBV8YQ&feature=youtu.be

Use the \_union(Type1 | Type2) to define a abstract type that
can point to Type1 Type2 etc...

```c

struct Box
{
	int id _defval(1);
};

struct Box* Box_Create() _default
{
    struct Box* p = (struct Box*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->id = 1;
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
void Box_Draw(struct Box* pBox)
{
	printf("Box\n");
}

struct Circle
{
	int id _defval(2);
};
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
void Circle_Draw(struct Circle* pCircle)
{
	printf("Circle\n");
}

struct _union(Box | Circle) Shape
{
	int id;
};

void  Shape_Delete(struct Shape* pShape) _default
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
void Shape_Draw(struct Shape* pShape) _default
{
    switch (pShape->id)
    {
        case 2:
            Circle_Draw((struct Circle*)pShape);
        break;
        case 1:
            Box_Draw((struct Box*)pShape);
        break;
        default:
        break;
    }
}

struct Items
{
	struct Shape * _auto * _auto _size(Size) data;
	int Size;
	int Capacity;
};

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
void Items_PushBack(struct Items* pItems, struct Shape* p) _default
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
    pItems->data[pItems->Size] = p;
    pItems->Size++;
}
void Items_Destroy(struct Items* pItems) _default
{
    for (int i = 0; i < pItems->Size; i++)
    {
        Shape_Delete(pItems->data[i]);
    }
    free((void*)pItems->data);
}

int main()
{
	struct Shape* pShape = Box_Create();
	struct Items items = { 0 };
	Items_PushBack(&items, pShape);
	Items_PushBack(&items, Circle_Create());

	for (int i = 0; i < items.Size; i++)
	{
		Shape_Draw(items.data[i]);
	}
	
	Items_Destroy(&items);


}


```

