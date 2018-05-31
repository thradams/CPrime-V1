var sample = {};

sample["Especial functions"] =
 `
typedef char * auto String;
struct X
{
    String Name;
    int i;
};

X * X_Create() default;
void X_Init(X * p) default;
void X_Destroy(X * p) default;
void X_Delete(X * p) default;

int main()
{
    X x = {};
    return 1;
}
`;

sample["Dynamic Array"] =
 `
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
		printf("%d\\n", items.pData[i]->i);
	}

	Items_Destroy(&items);
	return 0;
}

`;

sample["Linked list"] =
`
struct Item
{
    int i;
    struct Item* auto pNext;
};

void Item_Delete(Item* pItem) default;

struct Items
{
    Item* auto pHead,* pTail;
};

void Items_Destroy(Items* pItems) default;
void Items_PushBack(Items* pItems, Item* pItem) default;

`;

sample["Initialization"] =
`struct Point
{
  int x = 1;
  int y = 2;
};

struct Line
{
  Point start, end;
};

int main()
{
  Point pt = {};
  Line ln = {};
}
`;

sample["Polimorphism"] =
`
struct Box
{
    int id = 1;
};

Box* Box_Create() default;
void Box_Delete(Box* pBox) default;

void Box_Draw(Box* pBox)
{
    printf("Box");
}

struct Circle
{
    int id = 2;
};
Circle* Circle_Create() default;
void Circle_Delete(Circle* pCircle) default;

void Circle_Draw(Circle* pCircle)
{
    printf("Circle");
}

struct _union(Box | Circle) Shape
{
    int id;
};

void Shape_Delete(Shape* pShape) default;
void Shape_Draw(Shape* pShape) default;

`;



sample["Lambdas"] =
    `
void Run(void (*callback)(void*), void* data);

int main()
{  
  Run([](void* data){
  
    printf("first");
    Run([](void* data){
      printf("second");
    }, 0);     
  }, 0);
}
`;

