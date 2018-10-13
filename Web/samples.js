var sample = {};

sample["Especial functions"] =
 `

typedef char * /*auto*/ String;
struct X
{
    String Name;
    int i;
};

struct X * X_Create() /*default*/;
void X_Init(struct X * p) /*default*/;
void X_Destroy(struct X * p) /*default*/;
void X_Delete(struct X * p) /*default*/;

int main()
{
    X x = /*default*/{0};
    return 1;
}
`;

sample["Decopling"] =
`
// -- header file -- 

typedef char * /*auto*/ String;

struct X
{
    String Name;
    int i;
};

struct Y
{
  int i;
  struct X x; //try comment this line
}

void Y_Init(struct Y * p);
void Y_Destroy(struct Y * p);

int main()
{
    return 1;
}

//-- implementation file --

void Y_Init(struct Y * p) /*default*/
{
    p->i = 0;
    p->x.Name = 0;
    p->x.i = 0;
}

void Y_Destroy(struct Y * p) /*default*/
{
    free((void*)p->x.Name);
}

`
sample["Dynamic Array of int"] =
    `
struct Items
{
	int * /*auto [Size]*/ pData;
	int Size;
	int Capacity;
};


void Items_PushBack(Items* pItems, int i) /*default*/;
void Items_Destroy(Items* pItems) /*default*/;


int main(int argc, char **argv)
{
	Items items = /*default*/{0};

	Items_PushBack(&items, 1);
	Items_PushBack(&items, 2);
	Items_PushBack(&items, 3);

	for (int i = 0; i < items.Size; i++)
	{
		printf("%d\\n", items.pData[i]);
	}

	Items_Destroy(&items);
	return 0;
}

`;

sample["Dynamic Array of Item*"] =
 `
struct Item
{
	int i;
};


struct Item* Item_Create() /*default*/;
void Item_Delete(struct Item* p) /*default*/;

struct Items
{
	struct Item * /*auto*/ * /*auto [Size]*/ pData;
	int Size;
	int Capacity;
};


void Items_PushBack(struct Items* pItems, struct Item* pItem) /*default*/;
void Items_Destroy(struct Items* pItems) /*default*/;


int main(int argc, char **argv)
{
	struct Items items = /*default*/{0};

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
    struct Item* /*auto*/ pNext;
};

void Item_Delete(struct Item* pItem) /*default*/;

struct Items
{
    struct Item* /*auto*/ pHead,* pTail;
};

void Items_Destroy(struct Items* pItems) /*default*/;
void Items_PushBack(struct Items* pItems, struct Item* pItem) /*default*/;

`;

sample["Initialization"] =
`
struct Point
{
  int x /*= 1*/;
  int y /*= 2*/;
};

struct Line
{
  struct Point start, end;
};

int main()
{
  struct Point pt = /*default*/{0};
  struct Line ln = /*default*/{0};
}
`;

sample["Polimorphism"] =
`
struct Box
{
    int id /*= 1*/;
};

struct Box* Box_Create() /*default*/;
void Box_Delete(struct Box* pBox) /*default*/;

void Box_Draw(struct Box* pBox)
{
    printf("Box");
}

struct Circle
{
    int id /*= 2*/;
};
struct Circle* Circle_Create() /*default*/;
void Circle_Delete(struct Circle* pCircle) /*default*/;

void Circle_Draw(struct Circle* pCircle)
{
    printf("Circle");
}

//Shape is a pointer to Box or Circle
struct /*Box | Circle*/ Shape
{
    int id;
};

void Shape_Delete(struct Shape* pShape) /*default*/;

void Shape_Draw(struct Shape* pShape) /*default*/;

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

