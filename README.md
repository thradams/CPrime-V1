# C'

Let´s do pair programming!

![robot](/robots.jpg)
(Picture courtesy of my nephew Bethina)

## What is C' ?
C' (pronounced c prime) is a tool to help C programmers to write and maintain C code.
The tool edit the file in place like a refactoring tool. You can think on it as a pair programming with a robot.
Some implementation and maintenance, like destructor for data structures, is delegated for the robot and you are free to think in the program's logic instead of code something that can be automatically generated.

## How it works?

You can delegate to the robot the implementation of some functions.

Sample
```c
struct X
{
  int i;
};
```
To generate a initialization function for this struct just type:

```c
void X_Init(struct X* pX) _default;
```
When you compile this code you get:

```c
void X_Init(struct X* pX) _default
{
   pX->i= 0;
}
```

If the struct X is changed then the C' will update the implementation for you.
The robot uses the name of the function return, arguments and all AST to decide what to do.

Basic features:
https://www.youtube.com/watch?v=cFHL6cf1n_k&feature=youtu.be

## Using the compiler

Download binaries here:
https://github.com/thradams/CPrime/releases

Open the command line and try some samples:

```c
cprime hello.c -o hello2.c
```
This will compile hello.c to hello2.c

## Include directories (Configuration file)

Because C' is a full parser it requires the include dir.
See [config files](config.md) for some configuration files.

### Command line to use the config file:

```c
cprime -config config.h hello.c -o hello2.c
```

### Command line help Help
```
C' Version Oct  6 2017
https://github.com/thradams/CPrime

Syntax: cprime [options] [file ...]

Examples: cprime hello.c
          cprime -config config.h hello.c
          cprime -config config.h hello.c -o hello.c
          cprime -config config.h -P hello.c
          cprime -E hello.c
          cprime -P hello.c
          cprime -A hello.c

Options:
-config FILE                          Configuration file.
-help                                 Print this message.
-o FILE                               Sets ouput file name.
-E                                    Preprocess to console.
-P                                    Preprocess to file.
-A                                    Output AST to file.
-r                                    Reverts generation.

```

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

Use the \_union(Type1 | Type2) to define a abstract type that
can point to Type1 Type2 etc...

```c
#include "config.h"
#include <stdlib.h>
#include <stdio.h>

#define TYPEOF(X) (((struct { int i; } *)(X))->i)

enum
{
    Other_ID,
    Circle_ID,
    Car_ID,
    Triangle_ID,
    Box_ID,
};


typedef struct Box {
    int i _defval( Box_ID);
} Box;

struct Circle {
    int i _defval( Circle_ID);
};

struct Car {
    int i;
};

typedef struct {
    int i _defval(Triangle_ID);
} Triangle;

void Car_Draw(struct Car* p) {
}

void Car_Delete(struct Car* p) _default
{
    if (p != NULL)
    {
        free((void*)p);
    }

}

void Box_Draw(struct Box* p)
{
}

struct Box* Box_Create(void) _default
{
    struct Box* p = (struct Box*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->i =  Box_ID;
    }
    return p;

}

void Box_Delete(struct Box* p) _default
{
    if (p != NULL)
    {
        free((void*)p);
    }

}
void Circle_Draw(struct Circle* p)
{
}
void Circle_Delete(struct Circle* p) _default
{
    if (p != NULL)
    {
        free((void*)p);
    }

}
void Triangle_Draw(Triangle* p)
{
}
void Triangle_Delete(Triangle* p) _default
{
    if (p != NULL)
    {
        free((void*)p);
    }

}


Triangle* Triangle_Create() _default
{
    Triangle *p = (Triangle*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->i = Triangle_ID;
    }
    return p;

}

typedef struct _union(Car | Circle) Other Other;

typedef struct _union(Box | Circle | Triangle | Other) Shape Shape;

void Shape_Delete(Shape* p) _default
{
    switch (TYPEOF(p))
    {
        case Circle_ID:
            Circle_Delete((struct Circle*)p);
        break;
        case Car_ID:
            Car_Delete((struct Car*)p);
        break;
        case Triangle_ID:
            Triangle_Delete((Triangle*)p);
        break;
        case Box_ID:
            Box_Delete((Box*)p);
        break;
    default:
       break;
    }

}

void Shape_Draw(Shape* p) _default
{
    switch (TYPEOF(p))
    {
        case Circle_ID:
            Circle_Draw((struct Circle*)p);
        break;
        case Car_ID:
            Car_Draw((struct Car*)p);
        break;
        case Triangle_ID:
            Triangle_Draw((Triangle*)p);
        break;
        case Box_ID:
            Box_Draw((Box*)p);
        break;
    default:
       break;
    }

}

typedef struct
{
    Shape* _auto * _auto _size(Size) pItems;
    int Size;
    int Capacity;
} Shapes;

void Shapes_Destroy(Shapes* shapes) _default
{
    for (int i = 0; i < shapes->Size; i++)
    {
        Shape_Delete(shapes->pItems[i]);
    }
    free((void*)shapes->pItems);

}

void Shapes_Reserve(Shapes* shapes, int n) _default
{
    if (n > shapes->Capacity)
    {
        Shape** pnew = shapes->pItems;
        pnew = (Shape**)realloc(pnew, n * sizeof(Shape*));
        if (pnew)
        {
            shapes->pItems = pnew;
            shapes->Capacity = n;
        }
    }

}

void Shapes_PushBack(Shapes* shapes, Shape* pShape) _default
{
    if (shapes->Size + 1 > shapes->Capacity)
    {
        int n = shapes->Capacity * 2;
        if (n == 0)
        {
          n = 1;
        }
        Shapes_Reserve(shapes, n);
    }
    shapes->pItems[shapes->Size] = pShape;
    shapes->Size++;

}


int main(int argc, char **argv)
{
    Shape* p = (struct Shape*)Triangle_Create();
    
    Shapes shapes = { 0 };
    Shapes_PushBack(&shapes, (Shape*)Triangle_Create());
    Shapes_PushBack(&shapes, (Shape*)Box_Create());
    
    for (int i = 0; i < shapes.Size; i++)
    {
        Shape_Draw(shapes.pItems[i]);
    }
    Shapes_Destroy(&shapes);
    return 0;
}
```

## More details

The Create function uses the Init function if present.

The Delete function uses the Destroy function if present.

You can override any function removing default. For instance,
you can create your custom Destroy and the Delete function
will call your customized Destroy.

If you have typedef X for typedef Y  for typedef Z then the functions will search first X_Init then Y_Init etc.

This tool can be extended in the future with a template language without breaking compatibility with C.
For instance, template functions , metaclasses can be defined in a separated file. The C' will read these
files to learn how to generate code. 

More complex tasks like these Init/Destroy etc can be done using "plugins" for the compiler.



## Old Videos (experimental features considered)


https://www.youtube.com/edit?o=U&video_id=LmUebDRGE1A

Initializers

https://www.youtube.com/watch?v=lIRLijA_n2Q&t=19s

https://www.youtube.com/edit?o=U&video_id=mMHyeDZ0iA8

Build-in function instanciation destroy , create, delete

https://www.youtube.com/watch?v=yaa6uhHi2Xk

Build-in enum to string

https://www.youtube.com/watch?v=2qvCglaRNDU




