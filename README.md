# C'

Let´s do pair programming!

![robot](/robots.jpg)
(Picture courtesy of my nephew Bethina)

## What is C' ?
C'(pronounced c prime) is a robot that can help you generate and maintain C source code.

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

I the struct X is changed then the C' will update the implementation for you.
The robot uses the name of the function return, arguments and all AST to decide what to do.

## Table Functions x Types


|         | Any Type  | Vector | List  | enum  |   |
|---------|-----------|--------|-------|-------|---|
|Init     |      x    | x      | x     |       |   |
|Destroy  |      x    | x      | x     |       |   |
|Create   |      x    | x      | x     |       |   |
|Delete   |      x    | x      | x     |       |   |
|Swap     |      -    | -      | -     |       |   |
|Clear    |           |        | -     |       |   |
|Reserve  |           | x      |       |       |   |
|PushBack |           | x      | -     |       |   |
|PopBack  |           | -      | -     |       |   |
|PopFront |           | -      | -     |       |   |
|Top      |           | -      | -     |       |   |
|Back     |           | -      | -     |       |   |
|ToString |           | -      | -     |   -   |   |

 Legend: 'x' = implemented  '-' = missing but considered
 
## Using the compiler

Download binaries here:
https://github.com/thradams/CPrime/releases

Open the command line and try some samples:

```c
cp hello.c -o hello2.c
```
This will compile hello.c to hello2.c

## Include directories (Configuration file)

Use #pragma dir and configuration files.
See [config files](config.md) for some configuration files.

Command line:
```c
cp -config config.h hello.c -o hello2.c
```


# Keywords

 * __auto
 * __default
 * __defval(X)
 * __size(X)

# Things to try:


## type cp to see the documentation

```
C' Version Oct  6 2017
https://github.com/thradams/CPrime

Syntax: cp [options] [file ...]

Examples: cp hello.c
          cp -config config.h hello.c
          cp -config config.h hello.c -o hello.c
          cp -config config.h -P hello.c
          cp -E hello.c
          cp -P hello.c
          cp -A hello.c

Options:
-config FILE                          Configuration file.
-help                                 Print this message.
-o FILE                               Sets ouput file name.
-E                                    Preprocess to console.
-P                                    Preprocess to file.
-A                                    Output AST to file.
-r                                    Reverts generation.

```

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
 
## Dynamic arrays

```c


struct Items
{
    int * _auto  pData;
    int Size;
    int Capacity;
};

void Items_Reserve(struct Items* pItems, int n) _default
{
    if (n > pItems->Capacity)
    {
        int* pnew = pItems->pData;
        pnew = (int*)realloc(pnew, n * sizeof(int));
        if (pnew)
        {
            pItems->pData = pnew;
            pItems->Capacity = n;
        }
    }
}

void Items_PushBack(struct Items* pItems, int v) _default
{
    if (pItems->Size + 1 > pItems->Capacity)
    {
        Items_Reserve(pItems, pItems->Size + 1);
    }
    pItems->pData[pItems->Size] = v;
    pItems->Size++;
}

void Items_Destroy(struct Items* pItems) _default
{
    free((void*)pItems->pData);
}


int main(int argc, char **argv)
{
    struct Items items = { 0 };

    Items_PushBack(&items, 1);
    Items_PushBack(&items, 2);
    Items_PushBack(&items, 3);

    for (int i = 0; i < items.Size; i++)
    {
        printf("%d\n", items.pData[i]);
    }

    Items_Destroy(&items);
    return 0;
}

```

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
Destroying the variable you also destroy and free the pointed object.

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


I have posted on twitter GIFs that have some samples
of code generation.

https://twitter.com/thradams

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

Use the \_union("Type1 | Type2") to define a abstract type that
can point to Type1 Type2 etc...

```c
typedef struct _union("Car | Circle") Other Other;
typedef struct \_union("Box Circle Triangle Other") Shape Shape;
```

Shape can be Box Circle Triangle or Other.
Other can be Car, so Shape can be Car as well.

```c

#include <stdlib.h>
#include <stdio.h>

enum
{
    Other_ID,
    Circle_ID,
    Car_ID,
    Triangle_ID,
    Box_ID,
};


typedef struct Box {
    int i;
} Box;

struct Circle {
    int i;
} ;

 struct Car {
    int i;
} ;

typedef struct {
    int i;
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


Triangle* Triangle_Create() //_default
{
    Triangle *p = (Triangle*) malloc(sizeof * p);
    if (p != NULL)
    {
        p->i = Triangle_ID;
    }
    return p;
}

typedef struct _union("Car | Circle") Other Other;

typedef struct _union("Box Circle Triangle Other") Shape Shape;

void Shape_Delete(struct Shape* p) _default
{
    switch (*((int*)p))
    {
        case Circle_ID: Circle_Delete((struct Circle*)p); break; 
        case Car_ID: Car_Delete((struct Car*)p); break; 
        case Triangle_ID: Triangle_Delete((Triangle*)p); break; 
        case Box_ID: Box_Delete((Box*)p); break; 
    }
}

void Shape_Draw(struct Shape* p) _default
{
    switch (*((int*)p))
    {
        case Circle_ID: Circle_Draw((struct Circle*)p); break; 
        case Car_ID: Car_Draw((struct Car*)p); break; 
        case Triangle_ID: Triangle_Draw((Triangle*)p); break; 
        case Box_ID: Box_Draw((Box*)p); break; 
    }
}

int main(int argc, char **argv)
{
    Shape* p = (struct Shape*)Triangle_Create();
    Shape_Draw(p);
    Shape_Delete(p);
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




