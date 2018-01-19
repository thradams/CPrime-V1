# C'

Let´s do pair programming!

![robot](/robots.jpg)
(Picture courtesy of my niece Bethina)

## Description

C' (pronounced c prime) is a tool to help C programmers to write and maintain C code.
The tool edit the file in place like a refactoring tool. You can think on it as a pair programming with a robot.
Some implementation and maintenance, like destructor for data structures, are delegated for the robot and you are free to think in the program's logic instead of code something that can be automatically generated.

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

Other functions like init, delete and destroy also can be generated.

Video of basic features:

https://www.youtube.com/watch?v=cFHL6cf1n_k&feature=youtu.be

# Next steps

[Learn more](learn.md) about the generated code.

[Using](using.md) the compiler.

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


## Background & Motives

I work professionally with C++ since 2000 keeping my knowledge about C++ updated. After 2014 I noticed that my interest for the C language was gradually increasing. 

It is hard to summarize the reasons for that, but I can say that the rise of complexity and fancy libraries and styles of C++ are not adding value in the software I write.  I still like C++ and it is possible to use C++ compilers in way that meet my expectations of simplicity and maintenance. However, I think I can have a more portable, fast and easy to maintaing and teach code with C.
In 2012, I opened a topic in com.lang.C++.moderated about the possibility of to have “smart pointers” inside the C++ type system and later in 2015 I watched the Herb Sutter presentation cppcon “Writing Good C++14 By Default" where he talks about memory ownership checked statically.  After this point I became very motivated to implement the checked ownership analysis in the C language as part of the type system and I started to write my C parser in C. 

During the development of this parser and static analysis, I had some difficulties with the C language that have already begin addressed by C++, like to generate special member functions. I was doing constructors and destructor by hand and wondering how they could be designed and used in C. 

At some point I decided that I should address the problem to work better with C before to do the static analysis and then I renamed the project to C’ cprime.  Because I want a tool to be useful now (not something experimental) I spent some time to solve the problem of generating C code from C code including the preprocessed parts. This allowed me to use existing C compilers and IDEs.
C’ can generate destructors for structs and can have owner pointers in the type system. The motivation for static analysis still there and it is also related with code generation. More motivations like containers and polymorphism are included in the C’ as well.


## Current Status & Goals

The C’ can be used today as command line tool to generate and maintain code. You can remove the usage of the tool at any time and use the generated code as normal C code. So the evaluation of the tool is totally uncompromised. I am already using the tool to generate itself. One of the current goals is to keep the syntax compatible with C compilers adding macros. This allows the code generation in place. In other words, this is not like to have a modified C language that generates C files. The annotations required are added in a way to keep the C language and IDEs with auto-complete working normally without compromising productivity and avoiding adding more compilation/debugging steps. This goal motivated the logo and the idea of pair-programming with a robot.
 

## Roadmap

The improvements on C’ will focus in stability of basic features. I am also planning to add lambdas in the C language to allow replace C++ in other kind of projects where lambdas are used.

At some point I want to include static analysis again and check the onwership and null pointers as part of the type system. 



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




